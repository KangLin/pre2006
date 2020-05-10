/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    WMI.h
\brief   详细描述
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年6月30日  11:24:17
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#pragma once

#include <Wbemidl.h>
#include <wincred.h>
#include <comutil.h>
#include <atlbase.h>
#include <atlcom.h>

class CWMI
{
public:
	typedef int(*PROCFUN)(IWbemClassObject * pclsObj);
	
public:
	CWMI(void);
	~CWMI(void);

	int ConnectServer(LPCTSTR pszDomain, LPCTSTR pszUser, LPCTSTR pszPasswd, LPCTSTR pszResource);
	int ExecQuery(LPCTSTR pszQuery, PROCFUN fun = NULL);
	virtual int OnEnum(IWbemClassObject * pclsObj);

private:
	CComPtr < IWbemLocator > m_pLoc;
	CComPtr < IWbemServices > m_pSvc;
	
	TCHAR m_szDomain[CREDUI_MAX_DOMAIN_TARGET_LENGTH + 1];
	TCHAR m_szUser[CREDUI_MAX_USERNAME_LENGTH + 1];
	TCHAR m_szPasswd[CREDUI_MAX_PASSWORD_LENGTH + 1];

	int InitCOM();
	int SetProxyBlanket(IUnknown * pProxy);
};
