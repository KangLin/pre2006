#include "stdafx.h"
#include ".\1226.h"

C1226::C1226(void)
{
	m_pHttpConn = NULL;
}

C1226::~C1226(void)
{
}

int C1226::DoTest()
{
	LPCTSTR lpszURL;
	CString strServerName;
	CString strObject;
	INTERNET_PORT nPort;
	DWORD dwServiceType;

	if(!AfxParseURL(lpszURL, dwServiceType, strServerName, strObject, nPort) || 
		dwServiceType != INTERNET_SERVICE_HTTP)
	{
		cerr << _T("Error: can only use URLs beginning with http://") << endl;
		return 1;
	}

	m_pHttpConn = m_intSession.GetHttpConnection(strServerName, nPort);
	CHttpFile * pFile = m_pHttpConn->OpenRequest("POST", strObject);
	pFile->SendRequest();

	
}
