#include "StdAfx.h"
#include "WMISystemInfo.h"

CWMISystemInfo::CWMISystemInfo(void)
{
	if(m_Wmi.ConnectServer(_T(""), NULL, NULL, _T("\\\\.\\ROOT\\CIMV2")))
	{
		CTException e(_T("ConnectServer error"));
		throw e;
	}// ½áÊø if(m_Wmi.ConnectServer(_T(""), NULL, NULL, _T("\\\\.\\ROOT\\CIMV2")))
}

CWMISystemInfo::~CWMISystemInfo(void)
{
}

int CWMISystemInfo::GetWin32OperationSystem(CWMISystemInfo::PWIN32_OPERATION_SYSTEM pWin32OperationSystem)
{
	int nRet = S_OK;
	
	m_Wmi.ExecQuery(_T("Select * from Win32_OperatingSystem"), Win32OperationSystem);
	return nRet;
}