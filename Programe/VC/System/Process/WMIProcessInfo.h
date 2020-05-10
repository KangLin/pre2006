/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    WMIProcessInfo.h
\brief   用WMI方法得到进程信息
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年9月10日  15:59:09
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#pragma once

#include "..\..\..\..\VisualStudioProjects\VC7\socmca\socmca\WMI\WMI.h"
#include <vector>

#ifdef PROCESS_EXPORTS
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif

class DllExport CWMIProcessInfo :	public CWMI
{
public:
	CWMIProcessInfo(void);
	virtual ~CWMIProcessInfo(void);
	virtual int OnEnum(IWbemClassObject * pclsObj);

	typedef struct _PROCESS_INFORMATION
	{
		_tstring szCaption;
		_tstring szCommandLine;
		_tstring szCreationClassName;
		//time CreateionDate;
		_tstring szCSCreationClassName;
		_tstring szCSName;
		_tstring szDescription;
		_tstring szExecutablePath;
		UINT16 ExecutionState;
		_tstring szHandle;
		UINT32 HandleCount;
		//time InstallDate;
		UINT64 KernelModeTime;
		UINT32 MaximumWorkingSetSize;
		UINT32 MinimumWorkingSetSize;
		_tstring szName;
		_tstring szOSCreationClassName;
		_tstring szOSName;
		UINT64 OtherOperationCount;
		UINT64 OtherTransferCount;
		UINT32 PageFaults;
		UINT32 PageFileUsage;
		UINT32 ParentProcessID;
		UINT32 PeakPageFileUsage;
		UINT32 PeakVirtualSize;
		UINT32 PeakWorkingSetSize;
		UINT32 Priority;
		UINT64 PrivatePageCount;
		UINT32 ProcessID;
		UINT32 QuotaNonPagedPoolUsage;
		UINT32 QuotaPagedPoolUsage;
		UINT32 QuotaPeakNonPagedPoolUsage;
		UINT32 QuotaPeakPagedPoolUsage;
		UINT64 ReadOperationCount;
		UINT64 ReadTransferCount;
		UINT32 SessionId;
		//time TerminationDate;
		UINT32 ThreadCount;
		UINT64 UserModeTime;
		UINT64 VirtualSize;
		_tstring WindowsVersion;
		UINT64 WorkingSetSize;
		UINT64 WriteOperationCount;
		UINT64 WriteTransferCount;
	}PROCESS_INFORMATION, *PPROCESS_INFORMATION;

	int GetProcessInformation(vector < PROCESS_INFORMATION > *pInfo, LPCTSTR szIP = _T("."), LPCTSTR szUserName = NULL, LPCTSTR szPassword = NULL);

private:
	vector<PROCESS_INFORMATION>* m_pProcessInformation;
};
