// ClientSocket.cpp: implementation of the CClientSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
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

#define MAX_SOCKETS 10
#define TIMEOUT 2000
#define MAX_TIMEOUT 10

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClientSocket::CClientSocket(CListBox* pList,BOOL bAutoScroll) : CSniffSocket()
{
	//Init our vars
	m_pList=pList;
	m_lpAddress=NULL;
	m_lpScannedAddress=NULL;
	m_lScannedAddress=0;
	m_bOutgoing=FALSE;
	m_pSocket=NULL;

	m_bAutoScroll=bAutoScroll;
}

CClientSocket::~CClientSocket()
{
	//Delete the bind address
	free(m_lpAddress);

	//Free the scan address
	free(m_lpScannedAddress);
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
	if (ipHeader.Protocol==IPPROTO_TCP && strcmp(lpAddress,m_lpAddress) && ipHeader.sourceIPAddress==m_lScannedAddress)
	{
		//Find the size of IP header (may have options)
		unsigned long ulIPHeaderSize;
		ulIPHeaderSize=(ipHeader.HeaderLength_Version & 0x0f)*4;

		//Read the protocol header (ignore IP options)
		unsigned long lPos;
		lPos=ulIPHeaderSize;

		//And check is it the scan ?
		AnalyzeTCP(cBuffer+lPos);
	}

	//Read all the data
	//I'm sure however wants to use this will add his packet analyzer
	//Password sniffer here, have fun

	return TRUE;
}

void CClientSocket::AnalyzeTCP(char *cTCPBuffer)
{
	//Kill the timer
	KillTimer();

	//Read the ICMP header
	TCPHeader tcpHeader;
	memcpy(&tcpHeader,cTCPBuffer,TCPHeaderLength);

	if (htons(tcpHeader.SourcePort)>m_usLastPortDetected)
		m_usLastPortDetected=htons(tcpHeader.SourcePort);

	//Check the flag
	//0x14 is Syn+Rst
	if (tcpHeader.Flags!=0x14)
	{
		//Convert to strings
		char cTCP[10];
		ltoa(htons(tcpHeader.SourcePort),cTCP,10);

		m_pList->AddString(cTCP);

		if (m_bAutoScroll)
			m_pList->SetTopIndex(m_pList->GetCount()-5);
	}

	//Check the port
	if (m_usLastPortDetected==m_usLastPort)
	{
		//Stop the sniffer
		Sniff(FALSE);

		m_pList->AddString("Done!");
	}
	//Check if we should continue the scan
	else if (m_usLastPortDetected==m_usLastPortScanned)
		//Redo the scan
		ActualScan(m_lpScannedAddress,m_usLastPortScanned+1,m_usLastPort,m_lDelay);
	else
		//Set the timeout
		CAsyncSocket::SetTimeout(TIMEOUT);
}



void CClientSocket::CaptureOutgoing(BOOL bCapture)
{
	m_bOutgoing=bCapture;
}

BOOL CClientSocket::Scan(LPSTR lpSourceAddress,LPSTR lpDestinationAddress, unsigned short usStartPort, unsigned short usEndPort, long lDelay)
{	
	//Preform the scan
	if (!Bind(lpSourceAddress))
		return FALSE;

	//Save the scanned address (deleted in destructor)
	m_lScannedAddress=inet_addr(lpDestinationAddress);

	//And the string form
	free(m_lpScannedAddress);
	m_lpScannedAddress=strdup(lpDestinationAddress);

	//Sniff
	if (!Sniff(TRUE))
		return FALSE;

	//Incase of a final timeout
	m_usLastPortDetected=usStartPort;

	//Save the last port
	m_usLastPort=usEndPort;
	
	//Save the delay
	m_lDelay=lDelay;

	//No timeout yet
	m_lTimeoutCount=0;

	//Start sending
	ActualScan(lpDestinationAddress,usStartPort,usEndPort,lDelay);
}

BOOL CClientSocket::ActualScan(LPSTR lpDestinationAddress, unsigned short usStartPort, unsigned short usEndPort, long lDelay)
{
	//Create the socket
	//Create a TCP socket
	m_pSocket=new CTCPSocket;
	m_pSocket->SetRaw(TRUE);

	if (!m_pSocket->Create())
	{
		delete m_pSocket;
		m_pSocket=NULL;

		return FALSE;
	}

	m_pSocket->SetSourceAddress(m_lpAddress);

	//Preform the actual scan here
	for (int iCount=usStartPort;iCount<=usEndPort;iCount++)
	{
		if (lDelay)
			Sleep(lDelay);

		m_pSocket->Connect(0,lpDestinationAddress,iCount);

		//Check we aren't pass the hundread
		if (!((iCount-usStartPort+1)%MAX_SOCKETS))
		{
			m_usLastPortScanned=iCount;
			break;
		}
	}

	//Delete the socket
	delete m_pSocket;

	//Set the timeout
	CAsyncSocket::SetTimeout(TIMEOUT);
}

BOOL CClientSocket::OnSocketTimeout()
{
	KillTimer();

	if (m_lTimeoutCount==MAX_TIMEOUT)
	{
		m_pList->AddString("Timeout limit exceeded!");
		m_pList->AddString("Probably behind a firewall!");
	}
	else
	{
		//Create the timeout string
		CString strTime;
		strTime="Timeout at: ";

		//Convert the last port
		char cPort[7];
		ltoa(m_usLastPortDetected,cPort,10);

		//Add it to the string
		strTime+=cPort;
		strTime+=" ,resuming!";

		//Rescan where we left!!
		m_pList->AddString(strTime);

		//Do the scan
		ActualScan(m_lpScannedAddress,m_usLastPortDetected+1,m_usLastPort,m_lDelay);

		++m_lTimeoutCount;
	}

	if (m_bAutoScroll)
		m_pList->SetTopIndex(m_pList->GetCount()-5);

	return TRUE;
}