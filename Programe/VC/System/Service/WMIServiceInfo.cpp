#include "StdAfx.h"
#include "wmiServiceInfo.h"

CWMIServiceInfo::CWMIServiceInfo(void)
{
	m_pServiceInfo = NULL;
}

CWMIServiceInfo::~CWMIServiceInfo(void)
{
}

int CWMIServiceInfo::OnEnum(IWbemClassObject * pclsObj)
{
	ASSERT(m_pServiceInfo);

	int nRet = S_OK;

	ASSERT(pclsObj != NULL);

	WMI_SERVICE_INFO info;

	VARIANT vtProp;
	VariantInit(&vtProp);
	HRESULT hr = S_OK;
	hr = pclsObj->Get(L"AcceptPause", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.bAcceptPause = vtProp.boolVal;
	}

	hr = pclsObj->Get(L"AcceptStop", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.bAcceptStop = vtProp.boolVal;
	}

	hr = pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.szCaption = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"CheckPoint", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.CheckPoint = vtProp.intVal;
	}

	hr = pclsObj->Get(L"CreationClassName", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.szCreationClassName = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"Description", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.szDescription = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"DesktopInteract", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.bDesktopInteract = vtProp.boolVal;
	}

	hr = pclsObj->Get(L"DisplayName", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.szDisplayName = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"ErrorControl", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.szErrorControl = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"ExitCode", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.ExitCode = vtProp.intVal;
	}

	/*hr = pclsObj->Get(L"InstallDate", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.InstallDate = vtProp.date;
	}*/

	hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.szName = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"PathName", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.szPathName = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"ProcessId", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.ProcessId = vtProp.intVal;
	}

	hr = pclsObj->Get(L"ServiceSpecificExitCode", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.ServiceSpecificExitCode = vtProp.intVal;
	}

	hr = pclsObj->Get(L"ServiceType", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.szServiceType = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"Started", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.bStarted = vtProp.boolVal;
	}

	hr = pclsObj->Get(L"StartMode", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.szStartMode = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"StartName", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.szStartName = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"State", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.szState = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"Status", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.szStatus = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"SystemCreationClassName", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.szSystemCreationClassName = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"SystemName", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.szSystemName = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"TagId", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.TagId = vtProp.intVal;
	}

	hr = pclsObj->Get(L"WaitHint", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.WaitHint = vtProp.intVal;
	}

	VariantClear(&vtProp);

	m_pServiceInfo->push_back(info);

	return nRet;
}

int CWMIServiceInfo::GetServiceInformation(vector < WMI_SERVICE_INFO > * pInfo, LPCTSTR szIP, LPCTSTR szUserName, LPCTSTR szPassword)
{
	int nRet = S_OK;
	ASSERT(pInfo);
	if(NULL == pInfo)
	{
		return S_FALSE;
	}// ½áÊø if(NULL == pInfo)

	m_pServiceInfo = pInfo;
	_tstring szHost(_T("\\\\"));
	szHost = szHost + szIP + _T("\\ROOT\\CIMV2");

	if(ConnectServer(_T(""), szUserName, szPassword, szHost.c_str()))
	{
		return S_FALSE;
	}// ½áÊø if(ConnectServer(_T(""), szUserName, szPassword, szHost.c_str()))


	nRet = ExecQuery(_T("Select * from Win32_Service"));
	m_pServiceInfo = NULL;
	return nRet;
}