// ScanSocket.h: interface for the CScanSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SCANSOCKET_H__20CC50E5_D182_44EE_B3DD_472296ED090A__INCLUDED_)
#define AFX_SCANSOCKET_H__20CC50E5_D182_44EE_B3DD_472296ED090A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\ICMPSocketAsync.h"

#define PORT_SIZE 65536/8

class CUDPScanerDlg;

class CScanSocket : public CICMPSocketAsync
{
public:
	BOOL GetBit(unsigned short usPos);
	void ResetList();
	void SetDestinationIP(long lIP);
	CScanSocket(CUDPScanerDlg* dlg);
	virtual ~CScanSocket();

protected:
	NO_OnSocketAccept
	NO_OnSocketConnect
	NO_OnSocketClose
	NO_OnSocketOOB
	NO_OnSocketWrite

	virtual BOOL OnSocketTimeout();
	virtual BOOL OnSocketReceive(int iErrorCode);
private:
	void SetBit(unsigned short usPos);
	char* m_Port;
	long m_DestinationIP;
	CUDPScanerDlg* m_UDP;
};

#endif // !defined(AFX_SCANSOCKET_H__20CC50E5_D182_44EE_B3DD_472296ED090A__INCLUDED_)
