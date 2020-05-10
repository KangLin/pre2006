/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    WMIComputerSystem.h
\brief   用WMI方法得到计算机信息
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年9月8日  15:58:13
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/
#pragma once

#include "..\..\..\..\VisualStudioProjects\VC7\socmca\socmca\WMI\WMI.h"
#include <string>
using namespace std;

#ifdef SYSTEMINFO_EXPORTS
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif

class DllExport CWMIComputerSystem : public CWMI
{
public:
	CWMIComputerSystem(void);
	virtual ~CWMIComputerSystem(void);

	virtual int OnEnum(IWbemClassObject * pclsObj);

	typedef struct _COMPUTER_SYSTEM_INFORMATION
	{
		_tstring szCaption;
		_tstring szManufacturer;
		_tstring szModel;
		_tstring szSystemType;
		_tstring szDomain;
		_tstring szUserName;
		_tstring szBootupState;
		_tstring szInitialLoadInfo;
		_tstring szLastLoadInfo;
		_tstring szName;
		_tstring szNameFormat;
		_tstring szPrimaryOwnerContact;
		_tstring szPrimaryOwnerName;
		_tstring szWorkgroup;
	}COMPUTER_SYSTEM_INFORMATION, *PCOMPUTER_SYSTEM_INFORMATION;

	int GetComputerSystemInformation(PCOMPUTER_SYSTEM_INFORMATION pComputerSystemInformation, LPCTSTR szIP = _T("."), LPCTSTR szUserName = NULL, LPCTSTR szPassword = NULL);

private:
	PCOMPUTER_SYSTEM_INFORMATION m_pComputerSystem;
};
