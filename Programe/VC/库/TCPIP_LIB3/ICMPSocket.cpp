// ICMPSocket.cpp: implementation of the CICMPSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ICMPSocket.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define CIC_LOGNAME "CICMPSocket"

CICMPSocket::CICMPSocket() : CSpoofSocket()
{
	try
	{
		SetName(CIC_LOGNAME);

		//Our data structures
		m_Data=NULL;

		m_ICMPHeader=NULL;
		m_IPHeader=NULL;
		m_ICMPIPHeader=NULL;
	}
	ERROR_HANDLER("CICMPSocket")
}

CICMPSocket::~CICMPSocket()
{
	try
	{
		if (m_Data)
			delete [] m_Data;

		if (m_IPHeader)
			delete m_IPHeader;

		if (m_ICMPHeader)
			delete m_ICMPHeader;

		if (m_ICMPIPHeader)
			delete m_ICMPIPHeader;
	}
	ERROR_HANDLER("~CICMPSocket")
}

BOOL CICMPSocket::Create()
{
	try
	{
		SetProtocol(IPPROTO_ICMP);

		//Create the socket
		return CSpoofSocket::Create(IPPROTO_ICMP);
	}
	ERROR_HANDLER_RETURN("Create",FALSE)
}

BOOL CICMPSocket::SendUnreachable(LPCSTR lpDestinationAddress,unsigned char cType)
{
	try
	{
		return Send(lpDestinationAddress,ICMP_Unreachable,cType);
	}
	ERROR_HANDLER_RETURN("SendUnreachable",FALSE)
}

LPICMPHeader CICMPSocket::ConstructICMP()
{
	try
	{
		//Constructs a basic ICMP header
		LPICMPHeader lpHead;
		lpHead=new ICMPHeader;

		//Set all as zeros
		memset(lpHead,0,ICMPHeaderLength);

		//Set the timestamp
		lpHead->ICMP_Originate_Timestamp=GetTickCount();

		//Return it
		return lpHead;
	}
	ERROR_HANDLER_RETURN("ConstructICMP",FALSE)
}

BOOL CICMPSocket::SendTime(LPCSTR lpDestinationAddress, unsigned char cType)
{
	try
	{
		return Send(lpDestinationAddress,ICMP_Time,cType);
	}
	ERROR_HANDLER_RETURN("SendTime",FALSE)
}

BOOL CICMPSocket::Send(LPCSTR lpDestinationAddress, unsigned char cICMP, unsigned char cType)
{
	try
	{
		//Generic ICMP send
		LPICMPHeader lpHead;
		lpHead=ConstructICMP();

		if (!lpHead)
		{
			ReportError("Send","Failed to construct ICMP header!");
			return FALSE;
		}

		lpHead->ICMPType=cICMP;
		lpHead->ICMPCode=cType;

		//And the checksum
		lpHead->ICMPChecksum=CalculateChecksum((unsigned short*)lpHead,ICMPHeaderLength);

		//Send it
		BOOL bSend;
		bSend=CSpoofSocket::Send(lpDestinationAddress,(char*)lpHead,ICMPHeaderLength);

		//Clear up
		delete lpHead;

		return bSend;
	}
	ERROR_HANDLER_RETURN("Send",FALSE)
}

BOOL CICMPSocket::SendParameter(LPCSTR lpDestinationAddress, unsigned char cError)
{
	try
	{
		LPICMPHeader lpHead;
		lpHead=ConstructICMP();

		if (!lpHead)
		{
			ReportError("SendParameter","Failed to construct ICMP header!");
			return FALSE;
		}

		lpHead->ICMPType=ICMP_Parameter;
		lpHead->ICMPCode=ICMP_Parameter_ERROR;
		lpHead->sICMP.sUC.uc1=cError;

		//And the checksum
		lpHead->ICMPChecksum=CalculateChecksum((unsigned short*)lpHead,ICMPHeaderLength);

		//Send it
		BOOL bSend;
		bSend=CSpoofSocket::Send(lpDestinationAddress,(char*)lpHead,ICMPHeaderLength);

		//Clear up
		delete lpHead;

		return bSend;
	}
	ERROR_HANDLER_RETURN("SendParameter",FALSE)
}

BOOL CICMPSocket::SendQuench(LPCSTR lpDestinationAddress)
{
	try
	{
		return Send(lpDestinationAddress,ICMP_Quench,0);
	}
	ERROR_HANDLER_RETURN("SendQuench",FALSE)
}

BOOL CICMPSocket::SendRedirect(LPCSTR lpDestinationAddress, unsigned char cType, LPCSTR lpGatewayAddress)
{
	try
	{
		LPICMPHeader lpHead;
		lpHead=ConstructICMP();

		if (!lpHead)
		{
			ReportError("SendRedirect","Failed to construct ICMP header!");
			return FALSE;
		}

		lpHead->ICMPType=ICMP_Redirect;
		lpHead->ICMPCode=cType;
		lpHead->sICMP.sUL=inet_addr(lpGatewayAddress);

		//And the checksum
		lpHead->ICMPChecksum=CalculateChecksum((unsigned short*)lpHead,ICMPHeaderLength);

		//Send it
		BOOL bSend;
		bSend=CSpoofSocket::Send(lpDestinationAddress,(char*)lpHead,ICMPHeaderLength);

		//Clear up
		delete lpHead;

		return bSend;
	}
	ERROR_HANDLER_RETURN("SendRedirect",FALSE)
}

BOOL CICMPSocket::SendEcho(LPCSTR lpDestinationAddress, BOOL bReply, unsigned short usIdentifier, unsigned short usSequence, unsigned long ulData)
{
	try
	{
		LPICMPHeader lpHead;
		lpHead=ConstructICMP();
		
		if (!lpHead)
		{
			ReportError("SendEcho","Failed to construct ICMP header!");
			return FALSE;
		}

		//Check if echo or reply
		if (bReply)
			lpHead->ICMPType=ICMP_Echo_Reply;
		else
			lpHead->ICMPType=ICMP_Echo;

		lpHead->ICMPCode=0;
		lpHead->sICMP.sUS.us1=htons(usIdentifier);
		lpHead->sICMP.sUS.us2=htons(usSequence);
		lpHead->ICMP_Originate_Timestamp=htonl(ulData);

		//And the checksum
		lpHead->ICMPChecksum=CalculateChecksum((unsigned short*)lpHead,ICMPHeaderLength);

		//Send it
		BOOL bSend;
		bSend=CSpoofSocket::Send(lpDestinationAddress,(char*)lpHead,ICMPHeaderLength);

		//Clear up
		delete lpHead;

		return bSend;
	}
	ERROR_HANDLER_RETURN("SendEcho",FALSE)
}

BOOL CICMPSocket::SendTimestamp(LPCSTR lpDestinationAddress, BOOL bReply, unsigned short usIdentifier, unsigned short usSequence, unsigned long ulOriginateTimestamp, unsigned long ulReceiveTimestamp, unsigned long ulTransmitTimestamp)
{
	try
	{
		LPICMPHeader lpHead;
		lpHead=ConstructICMP();

		if (!lpHead)
		{
			ReportError("SendTimestamp","Failed to construct ICMP header!");
			return FALSE;
		}

		//Check if echo or reply
		if (bReply)
			lpHead->ICMPType=ICMP_Timestamp_Reply;
		else
			lpHead->ICMPType=ICMP_Timestamp;

		lpHead->ICMPCode=0;
		lpHead->sICMP.sUS.us1=htons(usIdentifier);
		lpHead->sICMP.sUS.us2=htons(usSequence);
		lpHead->ICMP_Originate_Timestamp=htonl(ulOriginateTimestamp);
		lpHead->ICMP_Receive_Timestamp=htonl(ulReceiveTimestamp);
		lpHead->ICMP_Transmit_Timestamp=htonl(ulTransmitTimestamp);

		//And the checksum
		lpHead->ICMPChecksum=CalculateChecksum((unsigned short*)lpHead,ICMPHeaderLength);

		//Send it
		BOOL bSend;
		bSend=CSpoofSocket::Send(lpDestinationAddress,(char*)lpHead,ICMPHeaderLength);

		//Clear up
		delete lpHead;

		return bSend;
	}
	ERROR_HANDLER_RETURN("SendTimestamp",FALSE)
}

BOOL CICMPSocket::SendInformation(LPCSTR lpDestinationAddress, BOOL bReply, unsigned short usIdentifier, unsigned short usSequence)
{
	try
	{
		LPICMPHeader lpHead;
		lpHead=ConstructICMP();

		if (!lpHead)
		{
			ReportError("SendInformation","Failed to construct ICMP header!");
			return FALSE;
		}

		//Check if echo or reply
		if (bReply)
			lpHead->ICMPType=ICMP_Information_Reply;
		else
			lpHead->ICMPType=ICMP_Information;

		lpHead->ICMPCode=0;
		lpHead->sICMP.sUS.us1=htons(usIdentifier);
		lpHead->sICMP.sUS.us2=htons(usSequence);
		
		//And the checksum
		//Using only first 8 bytes
		lpHead->ICMPChecksum=CalculateChecksum((unsigned short*)lpHead,ICMP_Information_SIZE);

		//Send it
		BOOL bSend;
		bSend=CSpoofSocket::Send(lpDestinationAddress,(char*)lpHead,ICMP_Information_SIZE);

		//Clear up
		delete lpHead;

		return bSend;
	}
	ERROR_HANDLER_RETURN("SendTimestamp",FALSE)
}


BOOL CICMPSocket::ProccessICMP(char* buf)
{
	try
	{
		//Here we proccess the input we received
		//Initialize members
		if (!m_IPHeader)
			m_IPHeader=new IpHeader;

		if (!m_ICMPHeader)
			m_ICMPHeader=new ICMPHeader;

		//Create an IP header
		LPIpHeader lpHead;
		lpHead=m_IPHeader;

		//Copy to buffer
		memcpy(lpHead,buf,IpHeaderLength);

		//Let's check for options
		unsigned char ucHeaderSize;
		ucHeaderSize=lpHead->HeaderLength_Version & 15;
		ucHeaderSize*=4;

		//Now check for total packet size
		unsigned short ucPacketSize;
		ucPacketSize=htons(lpHead->TotalLength);

		//Copy data to icmp
		memset(m_ICMPHeader,0,ICMPHeaderLength);

		//How much to copy ?
		unsigned short ucCopy;
		ucCopy=ucPacketSize-ucHeaderSize;
		
		//Save the datasize
		m_DataSize=ucCopy;

		if (ucCopy>ICMPHeaderLength)
			ucCopy=ICMPHeaderLength;

		memcpy(m_ICMPHeader,buf+ucHeaderSize,ucCopy);

		//Now save the original IP
		if (m_ICMPHeader->ICMPType!=ICMP_Echo &&
			m_ICMPHeader->ICMPType!=ICMP_Echo_Reply &&
			m_ICMPHeader->ICMPType!=ICMP_Timestamp &&
			m_ICMPHeader->ICMPType!=ICMP_Timestamp_Reply &&
			m_ICMPHeader->ICMPType!=ICMP_Information &&
			m_ICMPHeader->ICMPType!=ICMP_Information_Reply)
		{
			if (!m_ICMPIPHeader)
				m_ICMPIPHeader=new IpHeader;

			memcpy(m_ICMPIPHeader,buf+ucHeaderSize+ICMP_Unreachable_SIZE,IpHeaderLength);

			//Copy rest of data
			if (!m_Data)
				m_Data=new char[ICMP_DATA_SIZE];

			memcpy(m_Data,buf+ucPacketSize-ICMP_DATA_SIZE,ICMP_DATA_SIZE);
		}

		//Now I need to reverse the header
		ReverseHeader();

		return TRUE;
	}
	ERROR_HANDLER_RETURN("ProccessICMP",FALSE)
}

const LPICMPHeader CICMPSocket::GetLastICMPHeader()
{
	//Return the last header proccessed
	return m_ICMPHeader;
}

const LPIpHeader CICMPSocket::GetLastIPHeader()
{
	return m_IPHeader;
}

unsigned long CICMPSocket::GetLastDataSize()
{
	return m_DataSize;
}

void CICMPSocket::ReverseHeader()
{
	try
	{
		//Reverse timestamps
		if (m_ICMPHeader->ICMPType==ICMP_Timestamp || m_ICMPHeader->ICMPType==ICMP_Timestamp_Reply)
		{
			m_ICMPHeader->ICMP_Originate_Timestamp=htonl(m_ICMPHeader->ICMP_Originate_Timestamp);
			m_ICMPHeader->ICMP_Receive_Timestamp=htonl(m_ICMPHeader->ICMP_Receive_Timestamp);
			m_ICMPHeader->ICMP_Transmit_Timestamp=htonl(m_ICMPHeader->ICMP_Transmit_Timestamp);
		}


		//Reverse ID and Sequence
		if (m_ICMPHeader->ICMPType==ICMP_Echo || m_ICMPHeader->ICMPType==ICMP_Echo_Reply)
		{
			m_ICMPHeader->sICMP.sUS.us1=htons(m_ICMPHeader->sICMP.sUS.us1);
			m_ICMPHeader->sICMP.sUS.us2=htons(m_ICMPHeader->sICMP.sUS.us2);
		}
	}
	ERROR_HANDLER("ReverseHeader")
}

const LPIpHeader CICMPSocket::GetLastICMPIPHeader()
{
	//Get the IP header received via the icmp
	return m_ICMPIPHeader;
}

const char* CICMPSocket::GetLastICMPData()
{
	//Get the data sent via the ICMP
	return m_Data;
}
