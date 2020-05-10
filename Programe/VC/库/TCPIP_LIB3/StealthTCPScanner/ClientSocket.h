// ClientSocket.h: interface for the CClientSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTSOCKET_H__4BC89B30_1C8E_4022_B1A9_806ED855D346__INCLUDED_)
#define AFX_CLIENTSOCKET_H__4BC89B30_1C8E_4022_B1A9_806ED855D346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\SniffSocket.h"

class CTCPSocket;

class CClientSocket : public CSniffSocket  
{
public:
	//Viola do the scan
	BOOL Scan(LPSTR lpSourceAddress,LPSTR lpDestinationAddress,unsigned short usStartPort,unsigned short usEndPort,long lDelay);

	//Do we need to capture outgoing traffic as well
	void CaptureOutgoing(BOOL bCapture);

	//Bind to a specific address
	virtual BOOL Bind(LPCSTR lpSourceAddress,int iPort=0);

	//ctor and dtor
	CClientSocket(CListBox* pList,BOOL bAutoScroll);
	virtual ~CClientSocket();
protected:
	//Our sniff handler
	virtual BOOL OnSocketReceive(int iErrorCode);

	//Set timeout
	virtual BOOL OnSocketTimeout();

private:
	//Preform a scan (can only scan 100 at a time)
	BOOL ActualScan(LPSTR lpDestinationAddress, unsigned short usStartPort, unsigned short usEndPort, long lDelay);

	//Analyze the headers
	void AnalyzeTCP(char* cTCPBuffer);

	//The list box
	CListBox* m_pList;

	//The address
	LPSTR m_lpAddress;

	//Do we need to capture outgoing traffic
	BOOL m_bOutgoing;

	//The string version of the scanned address
	LPSTR m_lpScannedAddress;

	//The scanned address
	long m_lScannedAddress;

	//Our last port scanned
	unsigned short m_usLastPortScanned;

	//Our last port to scan
	unsigned short m_usLastPort;

	//Our last port detected
	unsigned short m_usLastPortDetected;

	//Socket delay
	long m_lDelay;

	//Time out count
	long m_lTimeoutCount;

	//Do we have autoscroll
	BOOL m_bAutoScroll;

	//Our scan socket
	CTCPSocket* m_pSocket;
};

#endif // !defined(AFX_CLIENTSOCKET_H__4BC89B30_1C8E_4022_B1A9_806ED855D346__INCLUDED_)
