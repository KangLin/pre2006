#include "stdafx.h"
#include "WMIWin32OperationSystem.h"

CWMIWin32OperationSystem::CWMIWin32OperationSystem()
{
	m_pWin32OperationSystem = NULL;
}

CWMIWin32OperationSystem::~CWMIWin32OperationSystem()
{
}

int CWMIWin32OperationSystem::OnEnum(IWbemClassObject * pclsObj)
{
	ASSERT(m_pWin32OperationSystem);

	int nRet = S_OK;

	ASSERT(pclsObj != NULL);

	VARIANT vtProp;
	VariantInit(&vtProp);
	HRESULT hr = S_OK;
	hr = pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pWin32OperationSystem->szName = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"Version", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pWin32OperationSystem->szVersion = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pWin32OperationSystem->szManufacture = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"Csname", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pWin32OperationSystem->szComputerName = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"SerialNumber", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pWin32OperationSystem->szSerialNumber = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"Organization", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pWin32OperationSystem->szOrganization = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"RegisteredUser", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pWin32OperationSystem->szRegisteredUser = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"Status", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pWin32OperationSystem->szStatus = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"SystemDevice", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pWin32OperationSystem->szSystemDevice = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"SystemDirectory", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pWin32OperationSystem->szSystemDirectory = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"SystemDrive", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pWin32OperationSystem->szSystemDrive = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"WindowsDirectory", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pWin32OperationSystem->szWindowsDirectory = vtProp.bstrVal;
	}

	VariantClear(&vtProp);
	return nRet;
}

int CWMIWin32OperationSystem::GetWin32OperationSystem(CWMIWin32OperationSystem::PWIN32_OPERATION_SYSTEM_INFORMATION pWin32OperationSystem, LPCTSTR szIP, LPCTSTR szUserName, LPCTSTR szPassword)
{
	int nRet = S_OK;
	ASSERT(pWin32OperationSystem);
	if(NULL == pWin32OperationSystem)
	{
		return S_FALSE;
	}// ½áÊø if(NULL == pWin32OperationSystem)

	m_pWin32OperationSystem = pWin32OperationSystem;

	_tstring szHost(_T("\\\\"));
	szHost = szHost + szIP + _T("\\ROOT\\CIMV2");

	if(ConnectServer(_T(""), szUserName, szPassword, szHost.c_str()))
	{
		return S_FALSE;
	}// ½áÊø if(ConnectServer(_T(""), szUserName, szPassword, szHost.c_str()))

	nRet = ExecQuery(_T("Select * from Win32_OperatingSystem"));
	m_pWin32OperationSystem = NULL;
	return nRet;
}