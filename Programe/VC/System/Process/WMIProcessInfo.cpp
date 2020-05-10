#include "StdAfx.h"
#include "WMIProcessInfo.h"

CWMIProcessInfo::CWMIProcessInfo(void)
{
	m_pProcessInformation = NULL;
}

CWMIProcessInfo::~CWMIProcessInfo(void)
{
}

int CWMIProcessInfo::OnEnum(IWbemClassObject * pclsObj)
{

	ASSERT(m_pProcessInformation);

	int nRet = S_OK;

	ASSERT(pclsObj != NULL);

	PROCESS_INFORMATION info;

	VARIANT vtProp;
	VariantInit(&vtProp);
	HRESULT hr = S_OK;
	hr = pclsObj->Get(L"Caption", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.szCaption = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"CommandLine", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.szCommandLine = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"CreationClassName", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.szCreationClassName = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"CSCreationClassName", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.szCSCreationClassName = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"CSName", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.szCSName = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"Description", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.szDescription = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"ExecutablePath", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.szExecutablePath = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"ExecutionState", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.ExecutionState = vtProp.iVal;
	}

	hr = pclsObj->Get(L"Handle", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.szHandle = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"HandleCount", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.HandleCount = vtProp.intVal;
	}

	/*hr = pclsObj->Get(L"InstallDate", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
	info.InstallDate = vtProp.date;
	}*/

	hr = pclsObj->Get(L"KernelModeTime", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.KernelModeTime = vtProp.intVal;
	}

	hr = pclsObj->Get(L"MaximumWorkingSetSize", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.MaximumWorkingSetSize = vtProp.intVal;
	}

	hr = pclsObj->Get(L"MinimumWorkingSetSize", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.MinimumWorkingSetSize = vtProp.intVal;
	}

	hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.szName = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"OSCreationClassName", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.szOSCreationClassName = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"OSName", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.szOSName = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"OtherOperationCount", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.OtherOperationCount = vtProp.llVal;
	}

	hr = pclsObj->Get(L"OtherTransferCount", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.OtherTransferCount = vtProp.llVal;
	}

	hr = pclsObj->Get(L"PageFaults", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.PageFaults = vtProp.intVal;
	}

	hr = pclsObj->Get(L"PageFileUsage", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.PageFileUsage = vtProp.intVal;
	}

	hr = pclsObj->Get(L"ParentProcessID", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.ParentProcessID = vtProp.intVal;
	}

	hr = pclsObj->Get(L"PeakPageFileUsage", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.PeakPageFileUsage = vtProp.intVal;
	}

	hr = pclsObj->Get(L"PeakVirtualSize", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.PeakVirtualSize = vtProp.intVal;
	}

	hr = pclsObj->Get(L"PeakWorkingSetSize", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.PeakWorkingSetSize = vtProp.intVal;
	}

	hr = pclsObj->Get(L"Priority", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.Priority = vtProp.intVal;
	}

	hr = pclsObj->Get(L"PrivatePageCount", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.PrivatePageCount = vtProp.llVal;
	}

	hr = pclsObj->Get(L"ProcessID", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.ProcessID = vtProp.intVal;
	}

	hr = pclsObj->Get(L"QuotaNonPagedPoolUsage", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.QuotaNonPagedPoolUsage = vtProp.intVal;
	}

	hr = pclsObj->Get(L"QuotaPagedPoolUsage", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.QuotaPagedPoolUsage = vtProp.intVal;
	}

	hr = pclsObj->Get(L"QuotaPeakNonPagedPoolUsage", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.QuotaPeakNonPagedPoolUsage = vtProp.intVal;
	}

	hr = pclsObj->Get(L"QuotaPeakPagedPoolUsage", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.QuotaPeakPagedPoolUsage = vtProp.intVal;
	}

	hr = pclsObj->Get(L"ReadOperationCount", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.ReadOperationCount = vtProp.llVal;
	}

	hr = pclsObj->Get(L"ReadTransferCount", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.ReadTransferCount = vtProp.llVal;
	}

	hr = pclsObj->Get(L"SessionId", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.SessionId = vtProp.intVal;
	}
	

	hr = pclsObj->Get(L"ThreadCount", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.ThreadCount = vtProp.intVal;
	}

	hr = pclsObj->Get(L"UserModeTime", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.UserModeTime = vtProp.llVal;
	}

	hr = pclsObj->Get(L"VirtualSize", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.VirtualSize = vtProp.llVal;
	}

	hr = pclsObj->Get(L"WindowsVersion", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.WindowsVersion = vtProp.bstrVal;
	}

	hr = pclsObj->Get(L"WorkingSetSize", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.WorkingSetSize = vtProp.llVal;
	}

	hr = pclsObj->Get(L"WriteOperationCount", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.WriteOperationCount = vtProp.llVal;
	}
	hr = pclsObj->Get(L"WriteTransferCount", 0, &vtProp, 0, 0);
	if(SUCCEEDED(hr))
	{
		info.WriteTransferCount = vtProp.llVal;
	}

	VariantClear(&vtProp);
	m_pProcessInformation->push_back(info);

	return nRet;
}

int CWMIProcessInfo::GetProcessInformation(vector < PROCESS_INFORMATION > *pInfo, LPCTSTR szIP, LPCTSTR szUserName, LPCTSTR szPassword)
{
	int nRet = S_OK;
	ASSERT(pInfo);
	if(NULL == pInfo)
	{
		return S_FALSE;
	}// ½áÊø if(NULL == pInfo)

	m_pProcessInformation = pInfo;
	_tstring szHost(_T("\\\\"));
	szHost = szHost + szIP + _T("\\ROOT\\CIMV2");

	if(ConnectServer(_T(""), szUserName, szPassword, szHost.c_str()))
	{
		return S_FALSE;
	}// ½áÊø if(ConnectServer(_T(""), szUserName, szPassword, szHost.c_str()))

	nRet = ExecQuery(_T("Select * from Win32_Process"));
	m_pProcessInformation = NULL;
	return nRet;
}