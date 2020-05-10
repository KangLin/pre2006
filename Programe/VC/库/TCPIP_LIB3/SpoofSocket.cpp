// SpoofSocket.cpp : implementation file
//
/*
 *
 *
 *  Copyright (c) 2000 Barak Weichselbaum <barak@komodia.com>
 *  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *
 * Contact info:
 * Site: http://www.komodia.com
 * Email: barak@komodia.com
 */

#include "stdafx.h"
#include "BinaryTree.h"
#include "SpoofSocket.h"

/////////////////////////////////////////////////////////////////////////////
// CSpoofSocket

#define CSpoofSocket_LOGNAME "CSpoofSocket"
#define CIPOptions_LOGNAME "CIPOptions"

CSpoofSocket::CSpoofSocket() : CSpoofBase()
{
	try
	{
		SetName(CSpoofSocket_LOGNAME);
		InitializeIP();
	}
	ERROR_HANDLER("CSpoofSocket")
}

CSpoofSocket::CSpoofSocket(SOCKET sok) : CSpoofBase()
{
	//Check it's a valid socket
	if (sok!=INVALID_SOCKET)
		ReportError("CSpoofSocket","Received invalid socket!");
	else
		try
		{
			SetName(CSpoofSocket_LOGNAME);
			AssignSocket(sok);
		}
		ERROR_HANDLER("CSpoofSocket")
}

CSpoofSocket::~CSpoofSocket()
{
	try
	{
		//Delete options
		SetOptions(FALSE);

		Close();
	}
	ERROR_HANDLER("~CSpoofSocket")
}

/////////////////////////////////////////////////////////////////////////////
// CSpoofSocket member functions

BOOL CSpoofSocket::Create(int iProtocol)
{
	try
	{
		//Here we create the raw socket
		if (m_Raw || iProtocol==IPPROTO_ICMP)
			m_SpoofSocket=socket(AF_INET,SOCK_RAW,iProtocol);//iProtocol);
		else
			if (iProtocol==IPPROTO_TCP)
				m_SpoofSocket=socket(AF_INET,SOCK_STREAM,iProtocol);
			else if (iProtocol==IPPROTO_UDP)
				m_SpoofSocket=socket(AF_INET,SOCK_DGRAM,iProtocol);

		//Check for socket validity
		if (m_SpoofSocket==INVALID_SOCKET)
		{
			//Error
			SetLastError("Create");
			return FALSE;
		}

		if (m_Raw)
		{
			//Set that the application will send the IP header
			unsigned int iTrue=1;

			if(setsockopt(m_SpoofSocket,IPPROTO_IP,IP_HDRINCL,(char*)&iTrue,sizeof(iTrue))==SOCKET_ERROR)
			{
				//Check for options error
				SetLastError("Create");
				return FALSE;
			}
		}

		return TRUE;
	}
	ERROR_HANDLER_RETURN("Create",FALSE)
}

BOOL CSpoofSocket::Send(LPCSTR lpDestinationAddress,char* buf,int bufLength,unsigned short usDestinationPort)
{
	try
	{
		//Quit if not ok
		if (!CheckSocketValid())
			return FALSE;

		//Define the target address
		sockaddr_in m_TargetAddress;
		memset(&m_TargetAddress,0,sizeof(m_TargetAddress));

		m_TargetAddress.sin_family=AF_INET;
		m_TargetAddress.sin_addr.s_addr=inet_addr(lpDestinationAddress);
		m_TargetAddress.sin_port=htons(usDestinationPort);

		//packet send status ?
		int iResult;

		//Only if allowing raw headers !!
		if (m_Raw)
		{
			//Header length
			unsigned char ucHeaderLength=IpHeaderLength;

			if (m_Options)
				ucHeaderLength+=m_IPOptions->GetBufferLength();
			
			//First construct the packet
			LPIpHeader lpHead=ConstructIPHeader(m_Protocol,IpFragFlag_DONT_FRAG,m_TTL,GetCurrentProcessId(),ucHeaderLength);

			//Set the address
			SetIPHeaderAddress(lpHead,m_SourceAddress,lpDestinationAddress);

			//Now add some more options
			int iTotalLength;
			iTotalLength=ucHeaderLength+bufLength;

			//Set the header
			lpHead->TotalLength=htons(iTotalLength);

			//Need to construct a new packet
			char* newBuf=new char[iTotalLength];

			//Copy two buffers
			memcpy(newBuf,lpHead,IpHeaderLength);

			//Do we need to copy options ?
			if (m_Options)
				memcpy(newBuf+IpHeaderLength,m_IPOptions->GetBuffer(),m_IPOptions->GetBufferLength());

			//Only if not null
			if (buf)
				memcpy(newBuf+ucHeaderLength,buf,bufLength);
			
			//Calculate the checksum
			lpHead->CheckSum=CalculateChecksum((unsigned short*)newBuf,iTotalLength);

			//Recopy the ip
			memcpy(newBuf,lpHead,IpHeaderLength);
			
			//Send the data
			iResult=sendto(getHandle(),(const char*)newBuf,iTotalLength,0,(sockaddr*)&m_TargetAddress,sizeof(m_TargetAddress));

			//Dispose of the buffer
			delete newBuf;

			//Dispose the header
			delete lpHead;
		}
		else
		{
			iResult=!SOCKET_ERROR;

			//Insert options
			//if (m_Options)
				//if (setsockopt(getHandle(),IPPROTO_IP,IP_OPTIONS,m_IPOptions->GetBuffer(),m_IPOptions->GetBufferLength())==SOCKET_ERROR)
					//Error
					//iResult=SOCKET_ERROR;
				//else
				//	;
			//else
				//No options
				//iResult=setsockopt(getHandle(),IPPROTO_IP,IP_OPTIONS,NULL,0);

			//Check if we had an error
			if (iResult!=SOCKET_ERROR)
				//Use regular send !!!
				iResult=sendto(getHandle(),(const char*)buf,bufLength,0,(sockaddr*)&m_TargetAddress,sizeof(m_TargetAddress));
		}

		if (iResult==SOCKET_ERROR)
			//Set the error
			SetLastError("Send");

		return iResult!=SOCKET_ERROR;
	}
	ERROR_HANDLER_RETURN("Send",FALSE)
}

LPIpHeader CSpoofSocket::ConstructIPHeader(unsigned char  ucProtocol,
										   unsigned short usFragmentationFlags,
										   unsigned char  ucTTL,
										   unsigned short usIdentification,
										   unsigned char  ucHeaderLength)
{
	try
	{
		//Need to construct the IP header
		LPIpHeader lpHead=new _IpHeader;

		//Header length (in 32 bits)
		lpHead->HeaderLength_Version=ucHeaderLength/4 + IpVersion*16;

		//Protocol
		lpHead->Protocol=ucProtocol;

		//Fragmentation flags
		lpHead->FragmentationFlags=htons(usFragmentationFlags);

		//Time to live
		lpHead->TTL=ucTTL;

		//Checksum - set to 0
		lpHead->CheckSum=0;

		//Identification
		lpHead->Identification=htons(usIdentification);

		//Precedence
		lpHead->TypeOfService=IpService_ROUTINE;

		//Return IP to user
		return lpHead;
	}
	ERROR_HANDLER_RETURN("ConstructIPHeader",NULL)
}

void CSpoofSocket::SetIPHeaderAddress(LPIpHeader lpHead, LPCSTR lpSourceAddress, LPCSTR lpDestinationAddress)
{
	try
	{
		//We need to place the header
		
		//If source is NULL then we need to use default source
		if (!lpSourceAddress)
		{
			//We will implement it
		}
		else
			//Use sockets2
			lpHead->sourceIPAddress=inet_addr(lpSourceAddress);

		//Place destination address
		lpHead->destIPAddress=inet_addr(lpDestinationAddress);

		//Done
	}
	ERROR_HANDLER("SetIPHeaderAddress")
}

BOOL CSpoofSocket::ValidSocket()
{
	return m_SpoofSocket!=INVALID_SOCKET;
}

unsigned short CSpoofSocket::CalculateChecksum(unsigned short *usBuf, int iSize)
{
	try
	{
		unsigned long usChksum=0;

		//Calculate the checksum
		while (iSize>1)
		{
			usChksum+=*usBuf++;
			iSize-=sizeof(unsigned short);
		}

		//If we have one char left
		if (iSize)
			usChksum+=*(unsigned char*)usBuf;

		//Complete the calculations
		usChksum=(usChksum >> 16) + (usChksum & 0xffff);
		usChksum+=(usChksum >> 16);

		//Return the value (inversed)
		return (unsigned short)(~usChksum);
	}
	ERROR_HANDLER_RETURN("CalculateChecksum",0)
}


BOOL CSpoofSocket::Bind(LPCSTR lpSourceAddress,int iPort)
{
	try
	{
		//Quit if not ok
		if (!CheckSocketValid())
			return FALSE;

		//Create the local address
		sockaddr_in soSrc;

		//Set to 0
		memset(&soSrc,0,sizeof(soSrc));
		soSrc.sin_family=AF_INET;
		soSrc.sin_addr.s_addr=inet_addr(lpSourceAddress);
		soSrc.sin_port=htons(iPort);

		//Now we need to bind it
		if (bind(getHandle(),(sockaddr*)&soSrc,sizeof(soSrc)))
		{
			//Error
			SetLastError("Bind");
			return FALSE;
		}

		//If already has a source address then don't change it
		if (!m_SourceAddress)
			m_SourceAddress=lpSourceAddress;

		return TRUE;
	}
	ERROR_HANDLER_RETURN("Bind",FALSE)
}

SOCKET CSpoofSocket::getHandle()
{
	return m_SpoofSocket;
}

BOOL CSpoofSocket::CheckSocketValid()
{
	try
	{
		//Check if socket is invalid
		if (!ValidSocket())
		{
			SetLastError("CheckSocketValid",WSAESHUTDOWN);
			return FALSE;
		}

		//OK
		return TRUE;
	}
	ERROR_HANDLER_RETURN("CheckSocketValid",FALSE)
}

BOOL CSpoofSocket::Close()
{
	try
	{
		//Close the socket
		//Quit if not ok
		if (!CheckSocketValid())
			return FALSE;

		//Close it
		if (closesocket(getHandle())==SOCKET_ERROR)
		{
			//Error in closing ?
			SetLastError("Close");
			return FALSE;
		}

		//Set the socket to invalid
		m_SpoofSocket=INVALID_SOCKET;

		return TRUE;
	}
	ERROR_HANDLER_RETURN("Close",FALSE)
}


void CSpoofSocket::SetProtocol(int iProtocol)
{
	m_Protocol=iProtocol;
}

void CSpoofSocket::SetSourceAddress(LPCSTR lpSourceAddress)
{
	try
	{
		//Set the source address, in case we want to spoof it
		m_SourceAddress=lpSourceAddress;
	}
	ERROR_HANDLER("SetSourceAddress")
}

unsigned short CSpoofSocket::CalculatePseudoChecksum(char *buf, int BufLength,LPCSTR lpDestinationAddress,int iPacketLength)
{
	try
	{
		//Calculate the checksum
		LPPseudoHeader lpPseudo;
		lpPseudo=new PseudoHeader;

		lpPseudo->DestinationAddress=inet_addr(lpDestinationAddress);
		lpPseudo->SourceAddress=inet_addr(m_SourceAddress);
		lpPseudo->Zeros=0;
		lpPseudo->PTCL=m_Protocol;
		lpPseudo->Length=htons(iPacketLength);

		//Calculate checksum of all
		int iTotalLength;
		iTotalLength=PseudoHeaderLength+BufLength;

		char* tmpBuf;
		tmpBuf=new char[iTotalLength];

		//Copy pseudo
		memcpy(tmpBuf,lpPseudo,PseudoHeaderLength);

		//Copy header
		memcpy(tmpBuf+PseudoHeaderLength,buf,BufLength);

		//Calculate the checksum
		unsigned short usChecksum;
		usChecksum=CalculateChecksum((unsigned short*)tmpBuf,iTotalLength);

		//Delete all
		delete tmpBuf;
		delete lpPseudo;

		//Return checksum
		return usChecksum;
	}
	ERROR_HANDLER_RETURN("CalculatePseudoChecksum",0)
}

void CSpoofSocket::SetTTL(unsigned char ucTTL)
{
	try
	{
		if (m_Raw)
		{
			//Set the ttl
			m_TTL=ucTTL;
		}
		else
			setsockopt(getHandle(),IPPROTO_IP,IP_TTL,(const char*)&ucTTL,sizeof(ucTTL));
	}
	ERROR_HANDLER("SetTTL")
}

void CSpoofSocket::SetRaw(BOOL bRaw)
{
	//Do we want to create raw socket (YES!!)
	m_Raw=bRaw;
}

void CSpoofSocket::SetOptions(BOOL bOptions)
{
	try
	{
		//Do we want options, normaly not
		m_Options=bOptions;

		if (m_IPOptions)
		{
			delete m_IPOptions;
			m_IPOptions=NULL;
		}

		if (bOptions)
			m_IPOptions=new CIPOptions;
	}
	ERROR_HANDLER("SetOptions")
}

CIPOptions::CIPOptions()
{
	try
	{
		SetName(CIPOptions_LOGNAME);

		//Initialize our buffer
		m_Buffer=new char[IPOption_SIZE];

		//Set our buffer to nothing
		Reset();

		//Set auto pad
		m_AutoPAD=TRUE;
	}
	ERROR_HANDLER("CIPOptions")
}

CIPOptions::~CIPOptions()
{
	try
	{
		delete m_Buffer;
	}
	ERROR_HANDLER("~CIPOptions")
}

void CIPOptions::AddOption_Nothing()
{
	try
	{
		//Add option do nothing
		tOptionType OT;

		//Get the option
		OT=GetOption(IPOption_DONT_COPY,IPOption_CONTROL,IPOption_NO_OPERATION);

		//Add it to buffer
		AddToBuffer((char*)&OT,sizeof(OT));
	}
	ERROR_HANDLER("AddOption_Nothing")
}

tOptionType CIPOptions::GetOption(unsigned char CopyFlag, unsigned char ClassFlag, unsigned char TypeFlag)
{
	//Return a single option type
	return CopyFlag | ClassFlag | TypeFlag;
}

void CIPOptions::AddToBuffer(char *buf, int BufLength)
{
	if (m_BufferLength<IPOption_SIZE)
	{
		//Add our option to the buffer
		memcpy(m_Buffer+m_BufferLength,buf,BufLength);
		m_BufferLength+=BufLength;
	}
}

const char* CIPOptions::GetBuffer()
{
	return m_Buffer;
}

int CIPOptions::GetBufferLength()
{
	try
	{
		//Check if auto pad or not
		if (m_AutoPAD)
			if (m_BufferLength/IPOption_WRAPSIZE==(m_BufferLength/IPOption_WRAPSIZE)*IPOption_WRAPSIZE && m_BufferLength>=IPOption_WRAPSIZE)
				return m_BufferLength;
			else
				return int((float)m_BufferLength/IPOption_WRAPSIZE+1)*IPOption_WRAPSIZE;
		else
			return m_BufferLength;
	}
	ERROR_HANDLER_RETURN("GetBufferLength",0)
}

void CIPOptions::AddOption_ENDLIST()
{
	try
	{
		//End the list of options
		tOptionType OT;

		//Get the option
		OT=GetOption(IPOption_DONT_COPY,IPOption_CONTROL,IPOption_END_OPTION);

		//Add it to buffer
		AddToBuffer((char*)&OT,sizeof(OT));
	}
	ERROR_HANDLER("AddOption_ENDLIST")
}

void CIPOptions::SetAutoPad(BOOL bAutoPAD)
{
	m_AutoPAD=bAutoPAD;
}

CIPOptions* CSpoofSocket::GetOptions()
{
	return m_IPOptions;
}

void CIPOptions::Reset()
{
	try
	{
		//Set all to zeros
		memset(m_Buffer,0,IPOption_SIZE);

		//Our buffer length
		m_BufferLength=0;
	}
	ERROR_HANDLER("Reset")
}

void CIPOptions::AddOption_Security(unsigned short usType)
{
	try
	{
		//Add option security
		tOptionType OT;

		//Get the option
		OT=GetOption(IPOption_COPY,IPOption_CONTROL,IPOption_SECURITY);

		//Add it to buffer
		AddToBuffer((char*)&OT,sizeof(OT));

		//Add length
		OT=IPOption_SECURITY_LENGTH;
		AddToBuffer((char*)&OT,sizeof(OT));

		//Add options
		AddToBuffer((char*)&usType,sizeof(usType));

		//Add zeros
		unsigned short usZeros=0;
		unsigned char ucZeros=0;

		//A hacker would enumarate these values, according to the RFC
		//Compartments
		AddToBuffer((char*)&usZeros,sizeof(usZeros));

		//Handling restrictions
		AddToBuffer((char*)&usZeros,sizeof(usZeros));


		//Transmition control code (TCC)
		AddToBuffer((char*)&usZeros,sizeof(usZeros));
		AddToBuffer((char*)&ucZeros,sizeof(ucZeros));

		//Done
	}
	ERROR_HANDLER("AddOption_Security")
}

void CIPOptions::AddOption_Stream(unsigned short usStreamID)
{
	try
	{
		//Add option security
		tOptionType OT;

		//Get the option
		OT=GetOption(IPOption_COPY,IPOption_CONTROL,IPOption_STREAM);

		//Add it to buffer
		AddToBuffer((char*)&OT,sizeof(OT));

		//Add length
		OT=IPOption_STREAM_LENGTH;
		AddToBuffer((char*)&OT,sizeof(OT));

		//Add options
		unsigned short usnStreamID;
		usnStreamID=htons(usStreamID);

		AddToBuffer((char*)&usnStreamID,sizeof(usnStreamID));
	}
	ERROR_HANDLER("AddOption_Stream")
}

void CIPOptions::AddOption_StrictRoute(tRouting tRoute)
{
	try
	{
		AddOption_Route(IPOption_STRICT_ROUTING,tRoute);
	}
	ERROR_HANDLER("AddOption_StrictRoute")
}

void CIPOptions::AddOption_RecordRoute(int iMaxRoutes)
{
	try
	{
		//Option for strict routine
		//Add option strict route
		tOptionType OT;

		//Get the option
		OT=GetOption(IPOption_DONT_COPY,IPOption_CONTROL,IPOption_RECORD_ROUTE);

		//Add it to buffer
		AddToBuffer((char*)&OT,sizeof(OT));

		//Add the length
		OT=iMaxRoutes*4+IPOption_STRICT_ROUTING_LENGTH;
		AddToBuffer((char*)&OT,sizeof(OT));
		
		//Add the pointer
		OT=IPOption_STRICT_ROUTING_POINTER;
		AddToBuffer((char*)&OT,sizeof(OT));
		
		char cNothing[IPOption_SIZE]="";
		AddToBuffer(cNothing,iMaxRoutes*4);
	}
	ERROR_HANDLER("AddOption_RecordRoute")
}

void CIPOptions::AddOption_Route(tOptionType tRouteType,tRouting tRoute)
{
	try
	{
		//Option for strict routine
		//Add option strict route
		tOptionType OT;

		//Get the option
		OT=GetOption(IPOption_COPY,IPOption_CONTROL,tRouteType);

		//Add it to buffer
		AddToBuffer((char*)&OT,sizeof(OT));

		//Add the length
		OT=tRoute.iRoutes*4+IPOption_STRICT_ROUTING_LENGTH;
		AddToBuffer((char*)&OT,sizeof(OT));
		
		//Add the pointer
		OT=IPOption_STRICT_ROUTING_POINTER;
		AddToBuffer((char*)&OT,sizeof(OT));
		
		//Add the routing table
		AddToBuffer((char*)tRoute.ulRoutes,tRoute.iRoutes*4);
	}
	ERROR_HANDLER("AddOption_Route")
}

void CIPOptions::AddOption_LooseRoute(tRouting tRoute)
{
	try
	{
		AddOption_Route(IPOption_LOOSE_ROUTING,tRoute);
	}
	ERROR_HANDLER("AddOption_LooseRoute")
}

void CIPOptions::AddOption_Timestamp(tOptionType tFlags, int iMaxStamps)
{
	try
	{
		//Add option for timestamp
		tOptionType OT;

		//Get the option
		OT=GetOption(IPOption_DONT_COPY,IPOption_DEBUGGING,IPOption_TIMESTAMP);

		//Add it to buffer
		AddToBuffer((char*)&OT,sizeof(OT));

		//Add the length
		OT=iMaxStamps*IPOption_TIMESTAMP_SIZE+IPOption_TIMESTAMP_LENGTH-1;
		AddToBuffer((char*)&OT,sizeof(OT));
		
		//Add the pointer
		OT=IPOption_TIMESTAMP_LENGTH;
		AddToBuffer((char*)&OT,sizeof(OT));

		//Add the flags
		AddToBuffer((char*)&tFlags,sizeof(tFlags));

		//Add the empty buffer
		char cNothing[IPOption_SIZE]="";
		AddToBuffer(cNothing,iMaxStamps*IPOption_TIMESTAMP_SIZE);
	}
	ERROR_HANDLER("AddOption_Timestamp")
}

BOOL CSpoofSocket::isRaw()
{
	return m_Raw;
}


void CSpoofSocket::InitializeIP()
{
	try
	{
		//Invalid the socket
		m_SpoofSocket=INVALID_SOCKET;

		//More invalids
		m_SourceAddress=NULL;

		//Some defaults
		m_TTL=IP_DEF_TTL;

		//We don't want raw header (so it can work on win 98/NT)
		m_Raw=FALSE;

		//Set our options
		m_IPOptions=NULL;

		//Not connected
		memset(&m_ConnectedTo,0,sizeof(m_ConnectedTo));

		//Set options to false
		SetOptions(FALSE);
	}
	ERROR_HANDLER("InitializeIP")
}

void CSpoofSocket::AssignSocket(SOCKET sok)
{
	try
	{
		//Binds to a socket
		m_SpoofSocket=sok;

		//Set non raw
		SetRaw(FALSE);
	}
	ERROR_HANDLER("AssignSocket")
}

int CSpoofSocket::Receive(char *buf, int bufLen)
{
	try
	{
		if (!ValidSocket())
			return SOCKET_ERROR;

		//Receive data
		int iResult;

		//Receive
		if (m_Protocol!=IPPROTO_TCP)
		{
			sockaddr saConnected;

			int iTmp;
			iTmp=sizeof(saConnected);

			//Accept it
			iResult=recvfrom(getHandle(),buf,bufLen,NULL,&saConnected,&iTmp);

			//If OK set it
			if (iResult!=SOCKET_ERROR)
				memcpy(&m_ConnectedTo,&saConnected,sizeof(saConnected));
		}
		else
			iResult=recv(getHandle(),buf,bufLen,NULL);

		//Check if error
		if (iResult==SOCKET_ERROR)
			//Error
			SetLastError("Receive");

		//Number of bytes received
		return iResult;
	}
	ERROR_HANDLER_RETURN("Receive",SOCKET_ERROR)
}

BOOL CSpoofSocket::ValidAddress(LPCSTR lpAddress)
{
	try
	{
		return inet_addr(lpAddress)!=INADDR_NONE;
	}
	ERROR_HANDLER_RETURN("ValidAddress",FALSE)
}

sockaddr_in CSpoofSocket::pResolveDNS(LPCSTR lpAddress)
{
	//Convert it to the address
	sockaddr_in adr;
	memset(&adr,0,sizeof(adr));

	try
	{
		//Resolve the DNS
		hostent* hp;
		hp=gethostbyname(lpAddress);

		//Check if this address exists
		if (!hp)
			//Error
			SetLastError("pResolveDNS");
		else
			//Copy the data
			memcpy(&adr.sin_addr,hp->h_addr,hp->h_length);

		return adr;
	}
	ERROR_HANDLER_RETURN("pResolveDNS",adr)
}

long CSpoofSocket::ResolveDNS(LPCSTR lpAddress)
{
	try
	{
		//Resolve the DNS
		sockaddr_in tmp;

		tmp=pResolveDNS(lpAddress);

		//Check if valid
		if (tmp.sin_addr.S_un.S_addr==0)
			//Error
			return 0;
		else
			return tmp.sin_addr.S_un.S_addr;
	}
	ERROR_HANDLER_RETURN("ResolveDNS",0)
}

BOOL CSpoofSocket::Sniff(BOOL bSniff)
{
	//Start sniffing
	if (!ValidSocket())
		return FALSE;

	try
	{
		unsigned long ulBytes;
		if (WSAIoctl(getHandle(),SIO_RCVALL,&bSniff,sizeof(bSniff),NULL,0,&ulBytes,NULL,NULL))
		{
			//Error
			SetLastError("Sniff");
			return FALSE;
		}

		return TRUE;
	}
	ERROR_HANDLER_RETURN("Sniff",FALSE)
}

long CSpoofSocket::GetPeerAddress()
{
	//Get the address we are connected to
	return m_ConnectedTo.sin_addr.S_un.S_addr;
}

BOOL CSpoofSocket::Shutdown(SocketShutdown eHow)
{
	if (!CheckSocketValid())
		return FALSE;

	try
	{
		int iHow;

		//Convert the how to a real flag
		if (eHow==ssReceive)
			iHow=SD_RECEIVE;
		else if (eHow==ssSend)
			iHow=SD_SEND;
		else
			iHow=SD_BOTH;

		//Do it
		if (shutdown(getHandle(),iHow))
		{
			SetLastError("Shutdown");
			return FALSE;
		}

		return TRUE;
	}
	ERROR_HANDLER_RETURN("Shutdown",FALSE)
}
