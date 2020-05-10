/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    WMI.h
\brief   ��ϸ����
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��6��30��  11:24:17
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
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
