/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    WMIWin32OperationSystem.h
\brief   用ＷＭＩ方式得到Win32操作系统的信息
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年9月10日  15:54:18
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#pragma once

#include "..\..\..\..\VisualStudioProjects\VC7\socmca\socmca\WMI\WMI.h"
#include "..\..\NetManage\Commonality\type.h"


#ifdef SYSTEMINFO_EXPORTS
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif

class DllExport CWMIWin32OperationSystem : public CWMI
{
public:
	CWMIWin32OperationSystem(void);
	virtual ~CWMIWin32OperationSystem(void);

	virtual int OnEnum(IWbemClassObject * pclsObj);

	typedef struct _WIN32_OPERATION_SYSTEM_INFOMATION
	{
		_tstring szName;              //操作系统名
		_tstring szVersion;           //版本号
		_tstring szManufacture;       //厂商
		_tstring szComputerName;      //计算机名
		_tstring szSerialNumber;      //序列号
		_tstring szOrganization;      //组织
		_tstring szRegisteredUser;    //注册用户
		_tstring szStatus;            //状态
		_tstring szSystemDevice;      //系统设备
		_tstring szSystemDirectory;   //系统目录
		_tstring szSystemDrive;       //系统驱动
		_tstring szWindowsDirectory;  //WINDOWS目录
	} WIN32_OPERATION_SYSTEM_INFORMATION, *PWIN32_OPERATION_SYSTEM_INFORMATION;

	virtual int GetWin32OperationSystem(PWIN32_OPERATION_SYSTEM_INFORMATION pWin32OperationSystem, LPCTSTR szIP = _T("."), LPCTSTR szUserName = NULL, LPCTSTR szPassword = NULL);

private:
	PWIN32_OPERATION_SYSTEM_INFORMATION m_pWin32OperationSystem;
};
