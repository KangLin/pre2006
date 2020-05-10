#include "StdAfx.h"
#include "WMIProcessor.h"

CWMIProcessor::CWMIProcessor(void)
{
	m_pProcessorInfo = NULL;
}

CWMIProcessor::~CWMIProcessor(void)
{
}

int CWMIProcessor::OnEnum(IWbemClassObject * pclsObj)
{
	ASSERT(m_pProcessorInfo);

	int nRet = S_OK;

	ASSERT(pclsObj != NULL);

	VARIANT vtProp;
	VariantInit(&vtProp);
	HRESULT hr = S_OK;
	hr = pclsObj->Get(L"AddressWidth", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->AddressWidth = vtProp.iVal;
	}

	hr = pclsObj->Get(L"Architecture", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->Architecture = vtProp.iVal;
	}

	hr = pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->szCaption = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"ConfigManagerErrorCode", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->ConfigManagerErrorCode = vtProp.intVal;
	}

	hr = pclsObj->Get(L"ConfigManagerUserConfig", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->ConfigManagerUserConfig = vtProp.boolVal;
	}

	hr = pclsObj->Get(L"CpuStatus", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->CpuStatus = vtProp.iVal;
	}

	hr = pclsObj->Get(L"CreationClassName", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->szCreationClassName = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"CurrentClockSpeed", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->CurrentClockSpeed = vtProp.intVal;
	}

	hr = pclsObj->Get(L"CurrentVoltage", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->CurrentVoltage = vtProp.iVal;
	}

	hr = pclsObj->Get(L"DataWidth", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->DataWidth = vtProp.iVal;
	}

	hr = pclsObj->Get(L"Description", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->szDescription = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"DeviceID", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->szDeviceID = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"ErrorCleared", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->ErrorCleared = vtProp.boolVal;
	}

	hr = pclsObj->Get(L"ErrorDescription", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->szErrorDescription = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"ExtClock", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->ExtClock = vtProp.intVal;
	}

	hr = pclsObj->Get(L"Family", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->Family = vtProp.iVal;
	}

	hr = pclsObj->Get(L"L2CacheSize", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->L2CacheSize = vtProp.intVal;
	}

	hr = pclsObj->Get(L"L2CacheSpeed", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->L2CacheSpeed = vtProp.intVal;
	}

	hr = pclsObj->Get(L"LastErrorCode", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->LastErrorCode = vtProp.intVal;
	}

	hr = pclsObj->Get(L"Level", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->Level = vtProp.iVal;
	}

	hr = pclsObj->Get(L"LoadPercentage", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->LoadPercentage = vtProp.iVal;
	}

	hr = pclsObj->Get(L"Manufacturer", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->szManufacturer = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"MaxClockSpeed", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->MaxClockSpeed = vtProp.intVal;
	}

	hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->szName = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"OtherFamilyDescription", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->szOtherFamilyDescription = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"PNPDeviceID", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->szPNPDeviceID = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"PowerManagementSupported", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->PowerManagementSupported = vtProp.boolVal;
	}

	hr = pclsObj->Get(L"ProcessorId", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->szProcessorID = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"ProcessorType", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->MaxClockSpeed = vtProp.iVal;
	}

	hr = pclsObj->Get(L"Role", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->szRole = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"SocketDesignation", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->szSocketDesignation = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"Status", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->szStatus = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"StatusInfo", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->StatusInfo = vtProp.iVal;
	}

	hr = pclsObj->Get(L"Stepping", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->szStepping = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"SystemCreationClassName", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->szSystemCreationClassName = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"SystemName", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->szSystemName = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"UniqueId", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->szUniqueID = vtProp.bstrVal;
	}


	hr = pclsObj->Get(L"UpgradeMethod", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->UpgradeMethod = vtProp.iVal;
	}


	hr = pclsObj->Get(L"Version", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->szVersion = vtProp.bstrVal;
	}


	hr = pclsObj->Get(L"VoltageCaps", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		m_pProcessorInfo->VoltageCaps = vtProp.intVal;
	}


	VariantClear(&vtProp);
	return nRet;
}

int CWMIProcessor::GetProcessorInformation(PPROCESSOR_INFO pInfo, LPCTSTR szIP, LPCTSTR szUserName, LPCTSTR szPassword)
{
	int nRet = S_OK;
	ASSERT(pInfo);
	if(NULL == pInfo)
	{
		return S_FALSE;
	}// ½áÊø if(NULL == pComputerSystemInformation)

	m_pProcessorInfo = pInfo;
	_tstring szHost(_T("\\\\"));
	szHost = szHost + szIP + _T("\\ROOT\\CIMV2");

	if(ConnectServer(_T(""), szUserName, szPassword, szHost.c_str()))
	{
		return S_FALSE;
	}// ½áÊø if(ConnectServer(_T(""), szUserName, szPassword, szHost.c_str()))

	nRet = ExecQuery(_T("Select * from Win32_processor"));
	m_pProcessorInfo = NULL;
	return nRet;
}