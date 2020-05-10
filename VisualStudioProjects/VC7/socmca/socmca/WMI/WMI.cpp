/*******************************************************************************************************
��Ȩ���� (C) 2006 ���ֹ����ң���������Ȩ����
�ļ�����WMI.cpp
��  ����WMIʵ�֡�
��  ����1����ɶԲ�ѯ����ֵ����ĺ��������������ַ�����
			1.1������һ�� PROCFUN ���͵Ļص�������
			1.2������һ���࣬ʵ�� OnEnum ������
			�������ַ�������ͬʱʹ�á� �����÷���һ��
		2������һ������CWMI wmi;
		3�����ӡ�wmi.ConnectServer
		4����ѯ��wmi.ExecQuery

		���ӣ�
		���ز�ѯ��
			CWMI wmi;
			if(wmi.ConnectServer(_T(""), NULL, NULL, _T("\\\\.\\ROOT\\CIMV2")))
			{
				return 1;
			} // ���� if(wmi.ConnectServer(_T(""), NULL, NULL, _T("ROOT\\CIMV2")))
			wmi.ExecQuery(_T("Select * from Win32_OperatingSystem"), fun);
		Զ��������ѯ��
			CWMI wmi;
			if(wmi.ConnectServer(_T(""), _T("administrator", _T("123456"), _T("\\\\192.168.1.155\\ROOT\\CIMV2")))
			{
				return 1;
			}
			wmi.ExecQuery(_T("Select * from Win32_OperatingSystem"), fun);
��  ����1.0
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2006��10��16��
ʱ  �䣺11:46:12
��������Microsoft Visual Studio 8.0 ���� C/C++ 8.0
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
��������InitCOM
��  ������ʼ��COM,������COM��ȫ���𡣵õ�����WMI��
��  ������
����ֵ������Ϊ int ���ɹ�����0�����򷵻ط��㡣
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2006��10��16�� 9:29:52
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
��������SetProxyBlanket
��  �������ð�ȫ����
��  ����
        IUnknown * pProxy����ȫ����
����ֵ������Ϊ int ���ɹ�����0�����򷵻ط��㡣
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2006��10��16�� 10:55:10
*******************************************************************************************************/
int CWMI::SetProxyBlanket(IUnknown * pProxy)
{
	ASSERT(pProxy != NULL);
	if(pProxy == NULL)
	{
		return 1;
	}// ���� if(pProxy == NULL)

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
��������ConnectServer
��  �������ӵ�����
��  ����
        LPCTSTR pszDomain  ������
		LPCTSTR pszUser    ���û���
		LPCTSTR pszPasswd  ������
		LPCTSTR pszResource��Ҫ���ʵ���Դ
����ֵ������Ϊ int ���ɹ�����0�����򷵻ط��㡣
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2006��10��16�� 10:32:31
*******************************************************************************************************/
int CWMI::ConnectServer(LPCTSTR pszDomain, LPCTSTR pszUser, LPCTSTR pszPasswd, LPCTSTR pszResource)
{
	ASSERT(m_pLoc != NULL);
	if(NULL == m_pLoc)
	{
		return 1;
	}// ���� if(NULL == m_pLoc)

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
	} // ���� if(pszDomain)	
	if(pszUser)
	{
		_tcscpy(m_szUser, pszUser);
	} // ���� if(pszUser)
	if(pszPasswd)
	{
		_tcscpy(m_szPasswd, pszPasswd);
	} // ���� if(pszPasswd)

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
��������ExecQuery
��  ����ִ�в�ѯ��
��  ����
        LPCTSTR pszQuery����ѯ��䡣
		PROCFUN fun     �������ѯ����ֵ��
����ֵ������Ϊ int ���ɹ�����0�����򷵻ط��㡣
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2006��10��16�� 10:57:12
*******************************************************************************************************/
int CWMI::ExecQuery(LPCTSTR pszQuery, PROCFUN fun)
{
	ASSERT(m_pSvc != NULL);
	if(NULL == m_pSvc)
	{
		return 1;
	}// ���� if(NULL == m_pSvc)

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
		}// ���� (e.g. Kerberos)

		CComPtr < IWbemClassObject > pclsObj;
		ULONG uReturn = 0;
		HRESULT hr = pEnumerator->Next(WBEM_INFINITE, 1,
			&pclsObj, &uReturn);
		if(FAILED(hr))
		{
			return 4;
		} // ���� if(FAILED(hr))
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
		} // ���� if(fun)
	} // ���� while(pEnumerator)
	return 0;
}

/*******************************************************************************************************
��������OnEnum
��  ����ö�ٲ�ѯ����ֵ������һ�����غ������������������о���ʵ�֡�����ֻ��һ��ʾ����
��  ����
        IWbemClassObject * pclsObj��
����ֵ������Ϊ int ���ɹ�����0�����򷵻ط��㡣
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2006��10��16�� 11:15:02
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