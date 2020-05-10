// TCPSocket.cpp: implementation of the CTCPSocket class.
//
//////////////////////////////////////////////////////////////////////
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
#include "TCPSocket.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define CTCPSocket_LOGNAME "CTCPSocket"
#define CTCPOptions_LOGNAME "CTCPOptions"

CTCPSocket::CTCPSocket() : CSpoofSocket()
{
	try
	{
		SetName(CTCPSocket_LOGNAME);

		InitializeTCP();
	}
	ERROR_HANDLER("CTCPSocket")
}

CTCPSocket::CTCPSocket(SOCKET sok) : CSpoofSocket(sok)
{
	try
	{
		SetName(CTCPSocket_LOGNAME);

		InitializeTCP();
	}
	ERROR_HANDLER("CTCPSocket")
}

CTCPSocket::~CTCPSocket() 
{
}

BOOL CTCPSocket::Create()
{
	try
	{
		SetProtocol(IPPROTO_TCP);
		return CSpoofSocket::Create(IPPROTO_IP);
	}
	ERROR_HANDLER_RETURN("Create",FALSE)
}

BOOL CTCPSocket::Connect(int iSourcePort, LPCSTR lpDestinationAddress, int iDestinationPort)
{
	try
	{
		if (isRaw())
		{
			//Let's try our first attack
			LPTCPHeader lpHead;

			//Header length
			int iHeaderLength;
			iHeaderLength=TCPHeaderLength;

			//If we have TCP options
			if (m_Options)
				iHeaderLength+=m_TCPOptions->GetBufferLength();

			//Create the header
			lpHead=ConstructTCPHeader(iSourcePort,iDestinationPort,iHeaderLength);

			//Set the flags
			SetHeaderFlag(lpHead,TCPFlag_ACK);
			
			//Result 
			BOOL bResult;

			//Construct diffrently if we have options
			if (m_Options)
			{
				char* buf;
				buf=new char[iHeaderLength];

				//Copy header
				memcpy(buf,lpHead,TCPHeaderLength);
			
				//Copy options
				memcpy(buf+TCPHeaderLength,m_TCPOptions->GetBuffer(),m_TCPOptions->GetBufferLength());

				//Checksum it
				lpHead->Checksum=CalculatePseudoChecksum(buf,iHeaderLength,lpDestinationAddress,iHeaderLength);
				
				//Recopy header
				memcpy(buf,lpHead,TCPHeaderLength);

				//Send the data
				bResult=CSpoofSocket::Send(lpDestinationAddress,buf,iHeaderLength);

				//Dispose
				delete buf;
			}
			else
			{
				lpHead->Checksum=CalculatePseudoChecksum((char*)lpHead,TCPHeaderLength,lpDestinationAddress,TCPHeaderLength);

				//Send the data
				bResult=CSpoofSocket::Send(lpDestinationAddress,(char*)lpHead,TCPHeaderLength);
			}

			//Set the last error
			SetLastError("Connect");

			//Dispose the header
			delete lpHead;

			return bResult;
		}
		else
		{
			//Set async notification
			int iResult;
			
			//Create the address
			sockaddr_in soSrc;
		
			//Set to 0
			memset(&soSrc,0,sizeof(soSrc));
			soSrc.sin_family=AF_INET;
			soSrc.sin_addr.s_addr=inet_addr(lpDestinationAddress);
			soSrc.sin_port=htons(iDestinationPort);

			iResult=connect(getHandle(),(sockaddr*)&soSrc,sizeof(soSrc));
			SetLastError("Connect");
			
			return iResult!=SOCKET_ERROR;
		}
	}
	ERROR_HANDLER_RETURN("Connect",FALSE)
}

LPTCPHeader CTCPSocket::ConstructTCPHeader(int iSourcePort, int iDestinationPort,int iHeaderLength)
{
	try
	{
		//Construct the header
		LPTCPHeader lpHead=new _TCPHeader;
		
		//Set source and destination port
		lpHead->SourcePort=htons(iSourcePort);
		lpHead->DestinationPort=htons(iDestinationPort);

		//No checksums yet
		lpHead->Checksum=0;

		//Set windows to 3.0k
		lpHead->Windows=htons(512);

		//Set the packet number
		lpHead->AcknowledgeNumber=0;

		//And the sequence
		lpHead->SequenceNumber=htonl(m_Sequence++);

		//Data offset
		lpHead->DataOffset=(iHeaderLength/4) << 4;

		//Flags
		lpHead->Flags=0;

		//Urgent pointer
		lpHead->UrgentPointer=0;

		//Return it to the user
		return lpHead;
	}
	ERROR_HANDLER_RETURN("ConstructTCPHeader",NULL)
}

unsigned int CTCPSocket::m_Sequence=(unsigned int)GetCurrentProcessId();

void CTCPSocket::SetHeaderFlag(LPTCPHeader lpHead, int iFlag)
{
	//Logical or
	lpHead->Flags|=iFlag;	
}

void CTCPOptions::Reset()
{
	try
	{
		CIPOptions::Reset();
	}
	ERROR_HANDLER("Reset")
}

void CTCPOptions::SetAutoPad(BOOL bAutoPAD)
{
	try
	{
		CIPOptions::SetAutoPad(bAutoPAD);
	}
	ERROR_HANDLER("SetAutoPad")
}

void CTCPOptions::AddOption_ENDLIST()
{
	try
	{
		//Add option end list
		tOptionType OT;

		//Get the option
		OT=TCPOptions_END;

		//Add it to buffer
		AddToBuffer((char*)&OT,sizeof(OT));
	}
	ERROR_HANDLER("AddOption_ENDLIST")
}

int CTCPOptions::GetBufferLength()
{
	try
	{
		return CIPOptions::GetBufferLength();
	}
	ERROR_HANDLER_RETURN("GetBufferLength",0)
}

const char* CTCPOptions::GetBuffer()
{
	try
	{
		return CIPOptions::GetBuffer();
	}
	ERROR_HANDLER_RETURN("GetBuffer",NULL)
}

void CTCPOptions::AddOption_Nothing()
{
	try
	{
		//Add option do nothing
		tOptionType OT;

		//Get the option
		OT=TCPOptions_NO_OPERATION;

		//Add it to buffer
		AddToBuffer((char*)&OT,sizeof(OT));
	}
	ERROR_HANDLER("AddOption_Nothing")
}

CTCPOptions::CTCPOptions() : CIPOptions()
{
	try
	{
		SetName(CTCPOptions_LOGNAME);
	}
	ERROR_HANDLER("CTCPOptions")
}

CTCPOptions::~CTCPOptions()
{
}

void CTCPOptions::AddOption_SegmentSize(unsigned short usMax)
{
	try
	{
		//Add option Max segment
		tOptionType OT;

		//Get the option
		OT=TCPOptions_MAX_Segment;

		//Add it to buffer
		AddToBuffer((char*)&OT,sizeof(OT));

		//Add length
		OT=TCPOptions_MAX_Segment_Length;
		AddToBuffer((char*)&OT,sizeof(OT));

		//Add segment size
		unsigned short usOT;
		usOT=htons(usMax);

		AddToBuffer((char*)&usOT,sizeof(usOT));
	}
	ERROR_HANDLER("AddOption_SegmentSize")
}

void CTCPSocket::SetTCPOptions(BOOL bOptions)
{
	try
	{
		//Do we want options, normaly not
		m_Options=bOptions;

		if (m_TCPOptions)
		{
			delete m_TCPOptions;
			m_TCPOptions=NULL;
		}

		if (bOptions)
			m_TCPOptions=new CTCPOptions;
	}
	ERROR_HANDLER("SetTCPOptions")
}

CTCPOptions* CTCPSocket::GetTCPOptions()
{
	return m_TCPOptions;
}

BOOL CTCPSocket::CreateRegular()
{
	try
	{
		SetProtocol(IPPROTO_TCP);
		return CSpoofSocket::Create(IPPROTO_TCP);
	}
	ERROR_HANDLER_RETURN("CreateRegular",FALSE)
}

BOOL CTCPSocket::Listen(int iBackLog)
{
	try
	{
		int iResult;
		iResult=listen(getHandle(),iBackLog);

		if (iResult)
			SetLastError("Listen");

		return !iResult;
	}
	ERROR_HANDLER_RETURN("Listen",FALSE)
}


CTCPSocket* CTCPSocket::Accept()
{
	try
	{
		//First accept the socket
		SOCKET sok;
		
		//Where we are connected to
		sockaddr_in saConnected;
		
		//Size of the structure
		int iTmp;
		iTmp=sizeof(saConnected);

		//Accept it
		sok=accept(getHandle(),(sockaddr*)&saConnected,&iTmp);

		if (sok!=INVALID_SOCKET)
		{
			//Create the new tcp socket
			CTCPSocket* tSok;
			tSok=new CTCPSocket(sok);

			//Set the address
			tSok->m_ConnectedTo=saConnected;

			return tSok;
		}
		else
		{
			//Error
			SetLastError("Accept");
			return NULL;
		}
	}
	ERROR_HANDLER_RETURN("Accept",NULL)
}

void CTCPSocket::InitializeTCP()
{
	try
	{
		//No options
		m_TCPOptions=NULL;

		SetTCPOptions(FALSE);
	}
	ERROR_HANDLER("InitializeTCP")
}

BOOL CTCPSocket::Accept(CTCPSocket *tSok)
{
	try
	{
		//First accept the socket
		SOCKET sok;
		
		//Where we are connected to
		sockaddr_in saConnected;
		
		//Size of the structure
		int iTmp;
		iTmp=sizeof(saConnected);

		//Accept it
		sok=accept(getHandle(),(sockaddr*)&saConnected,&iTmp);

		if (sok!=INVALID_SOCKET)
		{
			//Set the socket data
			tSok->m_ConnectedTo=saConnected;
			tSok->AssignSocket(sok);
			tSok->Accepted();

			return TRUE;
		}
		else
		{
			//Error
			SetLastError("Accept");
			return FALSE;
		}
	}
	ERROR_HANDLER_RETURN("Accept",FALSE)
}

BOOL CTCPSocket::Send(char *buf,int bufLen)
{
	try
	{
		//Send the data
		int iResult;

		//And send it
		iResult=send(getHandle(),buf,bufLen,NULL);

		return iResult;
	}
	ERROR_HANDLER_RETURN("Send",FALSE)
}

void CTCPSocket::Accepted()
{
}
