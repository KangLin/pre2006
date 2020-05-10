/*******************************************************************************************************
版权所有 (C) 2006 康林工作室；保留所有权利。
文件名：WMI.cpp
描  述：WMI实现。
用  法：1、完成对查询到的值处理的函数。有下面两种方法：
			1.1、定义一个 PROCFUN 类型的回调函数。
			1.2、派生一个类，实现 OnEnum 函数。
			以上两种方法不能同时使用。 建议用方法一。
		2、定义一个对象。CWMI wmi;
		3、连接。wmi.ConnectServer
		4、查询。wmi.ExecQuery

		例子：
		本地查询：
			CWMI wmi;
			if(wmi.ConnectServer(_T(""), NULL, NULL, _T("\\\\.\\ROOT\\CIMV2")))
			{
				return 1;
			} // 结束 if(wmi.ConnectServer(_T(""), NULL, NULL, _T("ROOT\\CIMV2")))
			wmi.ExecQuery(_T("Select * from Win32_OperatingSystem"), fun);
		远程主机查询：
			CWMI wmi;
			if(wmi.ConnectServer(_T(""), _T("administrator", _T("123456"), _T("\\\\192.168.1.155\\ROOT\\CIMV2")))
			{
				return 1;
			}
			wmi.ExecQuery(_T("Select * from Win32_OperatingSystem"), fun);
版  本：1.0
作  者：康  林
E_Mail：kl222@126.com
日  期：2006年10月16日
时  间：11:46:12
编译器：Microsoft Visual Studio 8.0 —— C/C++ 8.0
*******************************************************************************************************/

#include "stdafx.h"
#include "..\..\..\..\..\Programe\VC\NetManage\Commonality\type.h"
#include "WMI.h"
#include <iostream>
using namespace std;

#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "comsuppw.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CWMI::CWMI(void)
{
	m_pLoc = NULL;
	m_pSvc = NULL;

	SecureZeroMemory(m_szDomain, sizeof(m_szDomain));
	SecureZeroMemory(m_szUser, sizeof(m_szUser));
	SecureZeroMemory(m_szPasswd, sizeof(m_szPasswd));

	InitCOM();
}

CWMI::~CWMI(void)
{
	m_pLoc = NULL;
	m_pSvc = NULL;
	CoUninitialize();
}

/*******************************************************************************************************
函数名：InitCOM
描  述：初始化COM,并设置COM安全级别。得到本地WMI。
参  数：无
返回值：类型为 int 。成功返回0，否则返回非零。
版  本：1.0
作  者：康  林
时  间：2006年10月16日 9:29:52
*******************************************************************************************************/
int CWMI::InitCOM()
{
	HRESULT hres;

	// Step 1: --------------------------------------------------
	// Initialize COM. ------------------------------------------
	hres =  CoInitializeEx(0, COINIT_MULTITHREADED); 
	if (FAILED(hres))
	{
		TRACE(_T("Failed to initialize COM library. Error code = 0x%x\n"), hres);
		return 1;                  // Program has failed.
	}

	// Step 2: --------------------------------------------------
	// Set general COM security levels --------------------------
	// Note: If you are using Windows 2000, you need to specify -
	// the default authentication credentials for a user by using
	// a SOLE_AUTHENTICATION_LIST structure in the pAuthList ----
	// parameter of CoInitializeSecurity ------------------------
	hres =  CoInitializeSecurity(
		NULL, 
		-1,                          // COM authentication
		NULL,                        // Authentication services
		NULL,                        // Reserved
		RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
		RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
		NULL,                        // Authentication info
		EOAC_NONE,                   // Additional capabilities 
		NULL                         // Reserved
		);
	if (FAILED(hres))
	{
		if(hres!=RPC_E_TOO_LATE )
		{
			TRACE(_T("Failed to CoInitializeSecurity. Error code = 0x%x\n"), hres);
			return 2;                    // Program has failed.
		}
	}

	// Step 3: ---------------------------------------------------
	// Obtain the initial locator to WMI -------------------------
	hres = CoCreateInstance(
		CLSID_WbemLocator,
		0, 
		CLSCTX_INPROC_SERVER,
		IID_IWbemLocator, (LPVOID * )&m_pLoc);
	if (FAILED(hres))
	{
		TRACE(_T("Failed to CoCreateInstance. Error code = 0x%x\n"), hres);
		return 3;                 // Program has failed.
	}

	return 0;
}

/*******************************************************************************************************
函数名：SetProxyBlanket
描  述：设置安全代理
参  数：
        IUnknown * pProxy：安全代理
返回值：类型为 int 。成功返回0，否则返回非零。
版  本：1.0
作  者：康  林
时  间：2006年10月16日 10:55:10
*******************************************************************************************************/
int CWMI::SetProxyBlanket(IUnknown * pProxy)
{
	ASSERT(pProxy != NULL);
	if(pProxy == NULL)
	{
		return 1;
	}// 结束 if(pProxy == NULL)

	HRESULT hres;

	SEC_WINNT_AUTH_IDENTITY id;
	SecureZeroMemory(&id, sizeof(id));
	id.Domain = (unsigned short * )m_szDomain;
	id.DomainLength = _tcslen(m_szDomain);
	id.User = (unsigned short * )m_szUser;
	id.UserLength = _tcslen(m_szUser);
	id.Password = (unsigned short * )m_szPasswd;
	id.PasswordLength = _tcslen(m_szPasswd);
	id.Flags = SEC_WINNT_AUTH_IDENTITY_UNICODE;

	hres = CoSetProxyBlanket(
		pProxy,                       // Indicates the proxy to set
		RPC_C_AUTHN_WINNT,            // RPC_C_AUTHN_xxx
		RPC_C_AUTHZ_NONE,             // RPC_C_AUTHZ_xxx
		NULL,                         // Server principal name 
		RPC_C_AUTHN_LEVEL_CALL,       // RPC_C_AUTHN_LEVEL_xxx 
		RPC_C_IMP_LEVEL_IMPERSONATE,  // RPC_C_IMP_LEVEL_xxx
		&id,                          // client identity
		EOAC_NONE                     // proxy capabilities 
		);

    if (FAILED(hres))
    {
		TRACE(_T("Failed to CoSetProxyBlanket. Error code = 0x%x\n"), hres);
		return 2;               // Program has failed.
    }
	return 0;
}

/*******************************************************************************************************
函数名：ConnectServer
描  述：连接到服务
参  数：
        LPCTSTR pszDomain  ：域名
		LPCTSTR pszUser    ：用户名
		LPCTSTR pszPasswd  ：密码
		LPCTSTR pszResource：要访问的资源
返回值：类型为 int 。成功返回0，否则返回非零。
版  本：1.0
作  者：康  林
时  间：2006年10月16日 10:32:31
*******************************************************************************************************/
int CWMI::ConnectServer(LPCTSTR pszDomain, LPCTSTR pszUser, LPCTSTR pszPasswd, LPCTSTR pszResource)
{
	ASSERT(m_pLoc != NULL);
	if(NULL == m_pLoc)
	{
		return 1;
	}// 结束 if(NULL == m_pLoc)

	HRESULT hres;
	// Connect to the remote root\cimv2 namespace
    // and obtain pointer pSvc to make IWbemServices calls.
    //---------------------------------------------------------
    // change the computerName and domain 
    // strings below to the full computer name and domain 
	// of the remote computer
	if(pszDomain)
	{
		_tcscpy(m_szDomain, pszDomain);
	} // 结束 if(pszDomain)	
	if(pszUser)
	{
		_tcscpy(m_szUser, pszUser);
	} // 结束 if(pszUser)
	if(pszPasswd)
	{
		_tcscpy(m_szPasswd, pszPasswd);
	} // 结束 if(pszPasswd)

	m_pSvc = NULL;
	if(pszPasswd == NULL && pszUser == NULL)
	{		
		hres = m_pLoc->ConnectServer(
			_bstr_t(pszResource), // Object path of WMI namespace
			NULL,                    // User name. NULL = current user
			NULL,                    // User password. NULL = current
			0,                       // Locale. NULL indicates current
			NULL,                    // Security flags.
			0,                       // Authority (e.g. Kerberos)
			0,                       // Context object 
			&m_pSvc                    // pointer to IWbemServices proxy
			);
	}
	else
	{
		hres = m_pLoc->ConnectServer(
			_bstr_t(pszResource),
			_bstr_t(m_szUser),              // User name
			_bstr_t(m_szPasswd),            // User password
			_bstr_t(L"MS_409"),             // Locale             
			NULL,                           // Security flags
			_bstr_t(L"ntlmdomain:domain"),  // Authority        
			0,                              // Context object 
			&m_pSvc                         // IWbemServices proxy
			);
	}
	if (FAILED(hres))
    {
		TRACE(_T("Failed to ConnectServer. Error code = 0x%x\n"), hres);
		return 2;                // Program has failed.
    }

	return SetProxyBlanket(m_pSvc);
}

/*******************************************************************************************************
函数名：ExecQuery
描  述：执行查询。
参  数：
        LPCTSTR pszQuery：查询语句。
		PROCFUN fun     ：处理查询到的值。
返回值：类型为 int 。成功返回0，否则返回非零。
版  本：1.0
作  者：康  林
时  间：2006年10月16日 10:57:12
*******************************************************************************************************/
int CWMI::ExecQuery(LPCTSTR pszQuery, PROCFUN fun)
{
	ASSERT(m_pSvc != NULL);
	if(NULL == m_pSvc)
	{
		return 1;
	}// 结束 if(NULL == m_pSvc)

	// Use the IWbemServices pointer to make requests of WMI ----
	HRESULT hres;
	CComPtr < IEnumWbemClassObject > pEnumerator;
    hres = m_pSvc->ExecQuery(
        bstr_t("WQL"), 
		bstr_t(pszQuery),
        WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, 
        NULL,
		&pEnumerator);
	if(FAILED(hres))
	{
		TRACE(_T("Failed to ExecQuery. Error code = 0x%x\n"), hres);
		return 2;               // Program has failed.
    }

	while(pEnumerator)
	{
		
		if(SetProxyBlanket(pEnumerator))
		{
			return 3;
		}// 结束 (e.g. Kerberos)

		CComPtr < IWbemClassObject > pclsObj;
		ULONG uReturn = 0;
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
			&pclsObj, &uReturn);
		if(FAILED(hr))
		{
			return 4;
		} // 结束 if(FAILED(hr))
		if(0 == uReturn)
		{
			return 5;
		}
		if(fun)
		{
			fun(pclsObj); 
		}
		else
		{
			OnEnum(pclsObj);
		} // 结束 if(fun)
	} // 结束 while(pEnumerator)
	return 0;
}

/*******************************************************************************************************
函数名：OnEnum
描  述：枚举查询到的值。这是一个重载函数。可以在派生类中具体实现。这里只是一个示例。
参  数：
        IWbemClassObject * pclsObj：
返回值：类型为 int 。成功返回0，否则返回非零。
版  本：1.0
作  者：康  林
时  间：2006年10月16日 11:15:02
*******************************************************************************************************/
int CWMI::OnEnum(IWbemClassObject * pclsObj)
{
#ifdef _DEBUG
	ASSERT(pclsObj != NULL);

	VARIANT vtProp;
	VariantInit(&vtProp);

	// Get the value of the Name property
	HRESULT hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
	wcout << " OS Name : " << vtProp.bstrVal << endl;

	// Get the value of the FreePhysicalMemory property
	hr = pclsObj->Get(L"FreePhysicalMemory",
		0, &vtProp, 0, 0);
	wcout << " Free physical memory (in kilobytes): "
		<< vtProp.uintVal << endl;
	VariantClear(&vtProp);
#endif
	return 0;
}