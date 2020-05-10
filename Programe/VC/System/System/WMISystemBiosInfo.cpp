#include "StdAfx.h"
#include "wmiSystemBiosInfo.h"

CWMISystemBiosInfo::CWMISystemBiosInfo(void)
{
	m_pInfo = NULL;
}

CWMISystemBiosInfo::~CWMISystemBiosInfo(void)
{
}

int CWMISystemBiosInfo::OnEnum(IWbemClassObject * pclsObj)
{
	int nRet = S_OK;

	VARIANT vtProp;
	VariantInit(&vtProp);
	HRESULT hr = S_OK;
	/*hr = pclsObj->Get(L"BuildNumber", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pInfo->szBuildNumber = vtProp.bstrVal;
	}*/

	hr = pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pInfo->szCaption = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"CodeSet", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pInfo->szCodeSet = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"CurrentLanguage", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pInfo->szCurrentLanguage = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"Description", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pInfo->szDescription = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"IdentificationCode", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pInfo->szIdentificationCode = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"LanguageEdition", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pInfo->szLanguageEdition = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pInfo->szManufacturer = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pInfo->szName = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"OtherTargetOS", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pInfo->szOtherTargetOS = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"PrimaryBIOS", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pInfo->PrimaryBIOS = vtProp.boolVal;
	}

	hr = pclsObj->Get(L"SerialNumber", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pInfo->szSerialNumber = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"SMBIOSBIOSVersion", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pInfo->szSMBIOSBIOSVersion = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"SMBIOSMajorVersion", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pInfo->SMBIOSMajorVersion = vtProp.iVal;
	}

	hr = pclsObj->Get(L"SMBIOSMinorVersion", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pInfo->SMBIOSMinorVersion = vtProp.iVal;
	}

	hr = pclsObj->Get(L"SMBIOSPresent", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pInfo->SMBIOSPresent = vtProp.boolVal;
	}

	hr = pclsObj->Get(L"SoftwareElementID", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pInfo->szSoftwareElementID = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"SoftwareElementState", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pInfo->SoftwareElementState = vtProp.iVal;
	}

	hr = pclsObj->Get(L"Status", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pInfo->szStatus = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"TargetOperatingSystem", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pInfo->TargetOperatingSystem = vtProp.iVal;
	}

	hr = pclsObj->Get(L"Version", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pInfo->szVersion = vtProp.bstrVal;
	}

	VariantClear(&vtProp);
	return nRet;
}

int CWMISystemBiosInfo::GetSystemBiosInfo(PSYSTEM_BIOS_INFO pInfo, LPCTSTR szIP, LPCTSTR szUserName, LPCTSTR szPassword)
{
	ASSERT(pInfo);
	if(NULL == pInfo)
	{
		return S_FALSE;
	}// ½áÊø if(NULL == pInfo)
	m_pInfo = pInfo;

	_tstring szHost(_T("\\\\"));
	szHost = szHost + szIP + _T("\\ROOT\\CIMV2");

	if(ConnectServer(_T(""), szUserName, szPassword, szHost.c_str()))
	{
		return S_FALSE;
	}// ½áÊø if(ConnectServer(_T(""), szUserName, szPassword, szHost.c_str()))

	int nRet = ExecQuery(_T("Select * from Win32_bios"));
	m_pInfo = NULL;
	return nRet;
}