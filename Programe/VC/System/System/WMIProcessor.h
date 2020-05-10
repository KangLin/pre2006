/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    WMIProcessor.h
\brief   用WMI方法得到处理器的信息
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年9月11日  21:06:35
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/
#pragma once

#include "..\..\..\..\VisualStudioProjects\VC7\socmca\socmca\WMI\WMI.h"


#ifdef SYSTEMINFO_EXPORTS
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif

class DllExport CWMIProcessor : public CWMI
{
public:
	CWMIProcessor(void);
	virtual ~CWMIProcessor(void);

	virtual int OnEnum(IWbemClassObject * pclsObj);

	typedef struct _PROCESSOR_INFO
	{
		INT16 AddressWidth;
		INT16 Architecture;
		_tstring szCaption;
		INT32 ConfigManagerErrorCode;
		BOOL ConfigManagerUserConfig;
		INT16 CpuStatus;
		_tstring szCreationClassName;
		INT32 CurrentClockSpeed;
		INT16 CurrentVoltage;
		INT16 DataWidth;
		_tstring szDescription;
		_tstring szDeviceID;
		BOOL ErrorCleared;
		_tstring szErrorDescription;
		INT32 ExtClock;
		INT16 Family;
		INT32 L2CacheSize;
		INT32 L2CacheSpeed;
		INT32 LastErrorCode;
		INT16 Level;
		INT16 LoadPercentage;
		_tstring szManufacturer;
		INT32 MaxClockSpeed;
		_tstring szName;
		_tstring szOtherFamilyDescription;
		_tstring szPNPDeviceID;
		BOOL PowerManagementSupported;
		_tstring szProcessorID;
		INT16 ProcessorType;
		_tstring szRole;
		_tstring szSocketDesignation;
		_tstring szStatus;
		INT16 StatusInfo;
		_tstring szStepping;
		_tstring szSystemCreationClassName;
		_tstring szSystemName;
		_tstring szUniqueID;
		INT16 UpgradeMethod;
		_tstring szVersion;
		INT32 VoltageCaps;
	}PROCESSOR_INFO,*PPROCESSOR_INFO;

	int GetProcessorInformation(PPROCESSOR_INFO pInfo, LPCTSTR szIP = _T("."), LPCTSTR szUserName = NULL, LPCTSTR szPassword = NULL);

private:
	PPROCESSOR_INFO m_pProcessorInfo;
};
