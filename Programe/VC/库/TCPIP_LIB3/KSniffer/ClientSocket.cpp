// ClientSocket.cpp: implementation of the CClientSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "KSniffer.h"
#include "ClientSocket.h"

//These includes are only to get the header definition
#include "..\TCPSocket.h"
#include "..\UDPSocket.h"
#include "..\ICMPSocket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClientSocket::CClientSocket(CListBox* pList) : CSniffSocket()
{
	m_pList=pList;
	m_lpAddress=NULL;
	m_bOutgoing=FALSE;
}

CClientSocket::~CClientSocket()
{
	free(m_lpAddress);
}

BOOL CClientSocket::Bind(LPCSTR lpSourceAddress,int iPort)
{
	if (!CSpoofSocket::Bind(lpSourceAddress,iPort))
		return FALSE;
	else
	{
		//Check we are no rebinding
		if (m_lpAddress)
			free(m_lpAddress);

		//Save the data
		m_lpAddress=strdup(lpSourceAddress);
		return TRUE;
	}
}

BOOL CClientSocket::OnSocketReceive(int iErrorCode)
{
	int iReceive;

	char cBuffer[2000];

	//First receive the IP address
	IpHeader ipHeader;
	iReceive=Receive(cBuffer,2000);

	if (iReceive==-1)
		return FALSE;

	//Copy the header
	memcpy(&ipHeader,cBuffer,IpHeaderLength);

	//Check the packet is addresses to us
	LPSTR lpAddress=CSpoofSocket::LongToString(ipHeader.sourceIPAddress);

	//Check the data is not from us (altough someone may want to save this data)
	long lCapture;
	if ((lCapture=strcmp(lpAddress,m_lpAddress)) || m_bOutgoing)
	{
		CString strInfo;

		if (!lCapture)
		{
			strInfo="Sending packet to: ";
			strInfo+=CSpoofSocket::LongToString(ipHeader.destIPAddress);
		}
		else
		{
			strInfo="Received packet from: ";
			strInfo+=lpAddress;
		}

		strInfo+=", Protocol:";

		CString strProtocol;
		if (ipHeader.Protocol==IPPROTO_TCP)
			strProtocol="TCP";
		else if (ipHeader.Protocol==IPPROTO_UDP)
			strProtocol="UDP";
		else if (ipHeader.Protocol==IPPROTO_ICMP)
			strProtocol="ICMP";
		else
			strProtocol="Other";

		strInfo+=strProtocol;

		//Print out some data
		m_pList->AddString(strInfo);

		//Find the size of IP header (may have options)
		unsigned long ulIPHeaderSize;
		ulIPHeaderSize=(ipHeader.HeaderLength_Version & 0x0f)*4;

		//Read the protocol header (ignore IP options)
		unsigned long lPos;
		lPos=ulIPHeaderSize;

		if (ipHeader.Protocol==IPPROTO_TCP)
			AnalyzeTCP(cBuffer+lPos);
		else if (ipHeader.Protocol==IPPROTO_UDP)
			AnalyzeUDP(cBuffer+lPos);
		else if (ipHeader.Protocol==IPPROTO_ICMP)
			AnalyzeICMP(cBuffer+lPos);
	}

	//Read all the data
	//I'm sure however wants to use this will add his packet analyzer
	//Password sniffer here, have fun

	return TRUE;
}

void CClientSocket::AnalyzeICMP(char *cICMPBuffer)
{
	//Read the ICMP header
	ICMPHeader icmpHeader;
	memcpy(&icmpHeader,cICMPBuffer,ICMPHeaderLength);

	//Print out the code
	CString strICMP;

	//Convert to strings
	char cICMP[10];
	ltoa(icmpHeader.ICMPType,cICMP,10);

	strICMP="ICMP type: ";
	strICMP+=cICMP;

	//Convert again
	ltoa(icmpHeader.ICMPCode,cICMP,10);

	strICMP+=", code: ";
	strICMP+=cICMP;

	m_pList->AddString(strICMP);
}

void CClientSocket::AnalyzeTCP(char *cTCPBuffer)
{
	//Read the ICMP header
	TCPHeader tcpHeader;
	memcpy(&tcpHeader,cTCPBuffer,TCPHeaderLength);

	//Print out the code
	CString strTCP;

	//Convert to strings
	char cTCP[10];
	ltoa(htons(tcpHeader.SourcePort),cTCP,10);

	strTCP="Source port: ";
	strTCP+=cTCP;

	//Convert again
	ltoa(htons(tcpHeader.DestinationPort),cTCP,10);

	strTCP+=", destination port: ";
	strTCP+=cTCP;

	m_pList->AddString(strTCP);
}

void CClientSocket::AnalyzeUDP(char *cUDPBuffer)
{
	//Read the ICMP header
	UDPHeader udpHeader;
	memcpy(&udpHeader,cUDPBuffer,UDPHeaderLength);

	//Print out the code
	CString strUDP;

	//Convert to strings
	char cUDP[10];
	ltoa(htons(udpHeader.SourcePort),cUDP,10);

	strUDP="Source port: ";
	strUDP+=cUDP;

	//Convert again
	ltoa(htons(udpHeader.DestinationPort),cUDP,10);

	strUDP+=", destination port: ";
	strUDP+=cUDP;

	m_pList->AddString(strUDP);
}

void CClientSocket::CaptureOutgoing(BOOL bCapture)
{
	m_bOutgoing=bCapture;
}
