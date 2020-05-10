// ClientSocket.h: interface for the CClientSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENTSOCKET_H__4BC89B30_1C8E_4022_B1A9_806ED855D346__INCLUDED_)
#define AFX_CLIENTSOCKET_H__4BC89B30_1C8E_4022_B1A9_806ED855D346__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\SniffSocket.h"

class CClientSocket : public CSniffSocket  
{
public:
	//Do we need to capture outgoing traffic as well
	void CaptureOutgoing(BOOL bCapture);

	//Bind to a specific address
	virtual BOOL Bind(LPCSTR lpSourceAddress,int iPort=0);

	//ctor and dtor
	CClientSocket(CListBox* pList);
	virtual ~CClientSocket();
protected:
	virtual BOOL OnSocketReceive(int iErrorCode);
private:
	//Analyze the headers
	void AnalyzeTCP(char* cTCPBuffer);
	void AnalyzeUDP(char* cUDPBuffer);
	void AnalyzeICMP(char* cICMPBuffer);

	//The list box
	CListBox* m_pList;

	//The address
	LPSTR m_lpAddress;

	//Do we need to capture outgoing traffic
	BOOL m_bOutgoing;
};

#endif // !defined(AFX_CLIENTSOCKET_H__4BC89B30_1C8E_4022_B1A9_806ED855D346__INCLUDED_)
