// ScanSocket.cpp: implementation of the CScanSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UDPScaner.h"
#include "ScanSocket.h"

#include "UDPScanerDlg.h"
#include "..\UDPSocket.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CScanSocket::CScanSocket(CUDPScanerDlg* dlg) : CICMPSocketAsync()
{
	m_UDP=dlg;

	//Create port list
	m_Port=new char[PORT_SIZE];

	//Reset the list
	ResetList();
}

CScanSocket::~CScanSocket()
{
	delete [] m_Port;

	CICMPSocket::~CICMPSocket();
}

BOOL CScanSocket::OnSocketReceive(int iErrorCode)
{
	//First check if no error code
	if (iErrorCode)
		return TRUE;

	//Let parent proccess
	if (CICMPSocketAsync::OnSocketReceive(iErrorCode))
		//Check that this is the correct responce
		if (GetLastICMPHeader()->ICMPType==ICMP_Unreachable && GetLastIPHeader()->sourceIPAddress==m_DestinationIP)
		{
			//Get the destination port
			UDPHeader udp;
			memcpy(&udp,GetLastICMPData(),ICMP_DATA_SIZE);

			SetBit(htons(udp.DestinationPort));
			
			//Reset timer
			SetTimeout(5000);

			return TRUE;
		}
		
	return FALSE;
}

void CScanSocket::SetDestinationIP(long lIP)
{
	m_DestinationIP=lIP;
}

void CScanSocket::ResetList()
{
	memset(m_Port,0,PORT_SIZE);
}

void CScanSocket::SetBit(unsigned short usPos)
{
	unsigned short usTmp;
	usTmp=usPos/8;

	//Set the bit
	*(m_Port+usTmp)|=1 << (usPos%8);
}

BOOL CScanSocket::GetBit(unsigned short usPos)
{
	unsigned short usTmp;
	usTmp=usPos/8;

	//Get the bit
	return *(m_Port+usTmp) & (1 << (usPos%8));
}

BOOL CScanSocket::OnSocketTimeout()
{
	//Disable timer
	CAsyncSocket::KillTimer();

	//Call the dialog report
	m_UDP->Report();

	//Took care of it
	return FALSE;
}
