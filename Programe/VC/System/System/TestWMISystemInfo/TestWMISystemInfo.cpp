// TestWMISystemInfo.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "..\WMIWin32OperationSystem.h"

#include "..\WMIComputerSystem.h"
#include "..\..\Service\WMIServiceInfo.h"
#include "..\WMIProcessor.h"
#include "..\WMISystemBiosInfo.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CWMIWin32OperationSystem wmi;
	CWMIWin32OperationSystem::WIN32_OPERATION_SYSTEM_INFORMATION Win32OperationSystem;
	if(wmi.GetWin32OperationSystem(&Win32OperationSystem/*, _T("192.168.101.123"), _T("administrator"), _T("sz2007")*/) == S_OK)
	{

	}// 结束 if(wmi.GetWin32OperationSystem(&Win32OperationSystem, _T("192.168.101.123"), _T("administrator"), _T("sz2007")) == S_OK)

	CWMIComputerSystem wmiComputerSystem;
	CWMIComputerSystem::COMPUTER_SYSTEM_INFORMATION ComputerSystemInformation;
	if(wmiComputerSystem.GetComputerSystemInformation(&ComputerSystemInformation/*, _T("192.168.101.123"), _T("administrator"), _T("sz2007")*/) == S_OK)
	{

	}// 结束 if(wmiComputerSystem.GetComputerSystemInformation(&ComputerSystemInformation, _T("192.168.101.123"), _T("administrator"), _T("sz2007")) == S_OK)

	CWMIServiceInfo wmiService;
	vector<CWMIServiceInfo::WMI_SERVICE_INFO> ServiceInfo;
	if(wmiService.GetServiceInformation(&ServiceInfo/*, _T("192.168.101.123"), _T("administrator"), _T("sz2007")*/) == S_OK)
	{

	}// 结束 if(wmiService.GetServiceInformation(&ServiceInfo, _T("192.168.101.123"), _T("administrator"), _T("sz2007")) == S_OK)

	CWMIProcessor wmiProcessor;
	CWMIProcessor::PROCESSOR_INFO processorInfo;
	if(wmiProcessor.GetProcessorInformation(&processorInfo/*, _T("192.168.101.123"), _T("administrator"), _T("sz2007")*/) == S_OK)
	{

	}// 结束 if(wmiProcessor.GetProcessorInformation(&processorInfo, _T("192.168.101.123"), _T("administrator"), _T("sz2007")) == S_OK)

	CWMISystemBiosInfo wmiSystemBiosInfo;
	CWMISystemBiosInfo::SYSTEM_BIOS_INFO systemBiosInfo;
	if(wmiSystemBiosInfo.GetSystemBiosInfo(&systemBiosInfo /*, _T("192.168.101.123"), _T("administrator"), _T("sz2007")*/) == S_OK)
	{

	} // 结束 if(wmiSystemBiosInfo.GetSystemBiosInfo(&systemBiosInfo ) == S_OK)
	return 0;
}

