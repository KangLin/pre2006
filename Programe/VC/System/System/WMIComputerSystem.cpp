#include "StdAfx.h"
#include "WMIComputerSystem.h"

CWMIComputerSystem::CWMIComputerSystem(void)
{
	m_pComputerSystem = NULL;
}

CWMIComputerSystem::~CWMIComputerSystem(void)
{
}

int CWMIComputerSystem::OnEnum(IWbemClassObject * pclsObj)
{
	ASSERT(m_pComputerSystem);

	int nRet = S_OK;

	ASSERT(pclsObj != NULL);

	VARIANT vtProp;
	VariantInit(&vtProp);
	HRESULT hr = S_OK;
	hr = pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pComputerSystem->szCaption = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pComputerSystem->szManufacturer = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"model", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pComputerSystem->szModel = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"SystemType", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pComputerSystem->szSystemType = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"Domain", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pComputerSystem->szDomain = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"UserName", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pComputerSystem->szUserName = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"BootupState", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pComputerSystem->szBootupState = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"InitialLoadInfo", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pComputerSystem->szInitialLoadInfo = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"LastLoadInfo", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pComputerSystem->szLastLoadInfo = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pComputerSystem->szName = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"NameFormat", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pComputerSystem->szNameFormat = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"PrimaryOwnerContact", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pComputerSystem->szPrimaryOwnerContact = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"Workgroup", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pComputerSystem->szWorkgroup = vtProp.bstrVal;
	}

	VariantClear(&vtProp);
	return nRet;
}

int CWMIComputerSystem::GetComputerSystemInformation(CWMIComputerSystem::PCOMPUTER_SYSTEM_INFORMATION pComputerSystemInformation, LPCTSTR szIP, LPCTSTR szUserName, LPCTSTR szPassword)
{
	int nRet = S_OK;
	ASSERT(pComputerSystemInformation);
	if(NULL == pComputerSystemInformation)
	{
		return S_FALSE;
	}// ½áÊø if(NULL == pComputerSystemInformation)

	m_pComputerSystem = pComputerSystemInformation;
	_tstring szHost(_T("\\\\"));
	szHost = szHost + szIP + _T("\\ROOT\\CIMV2");

	if(ConnectServer(_T(""), szUserName, szPassword, szHost.c_str()))
	{
		return S_FALSE;
	}// ½áÊø if(ConnectServer(_T(""), szUserName, szPassword, szHost.c_str()))


	nRet = ExecQuery(_T("Select * from Win32_ComputerSystem"));
	m_pComputerSystem = NULL;
	return nRet;
}