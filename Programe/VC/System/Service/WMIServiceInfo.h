/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    WMIServiceInfo.h
\brief   用WMI方法得到服务
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年9月10日  15:47:48
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/
#pragma once

#include "..\..\..\..\VisualStudioProjects\VC7\socmca\socmca\WMI\WMI.h"
#include "..\..\NetManage\Commonality\type.h"
#include <time.h>
#include <vector>
using namespace std;

#ifdef SYSTEMINFO_EXPORTS
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif

class DllExport CWMIServiceInfo : public CWMI
{
public:
	CWMIServiceInfo(void);
	virtual ~CWMIServiceInfo(void);

	virtual int OnEnum(IWbemClassObject * pclsObj);

	typedef struct _WMI_SERVICE_INFO
	{
		BOOL bAcceptPause;        //是否接受暂停
		BOOL bAcceptStop;         //是否接受停止
		_tstring szCaption;       //服务标题
		UINT32 CheckPoint;
		_tstring szCreationClassName;
		_tstring szDescription;   //服务的描述
		BOOL bDesktopInteract;    //是否与桌面交互
		_tstring szDisplayName;   //显示名称
		_tstring szErrorControl;  //错误控制
		UINT32 ExitCode;          //退出代码
		//time InstallDate;
		_tstring szName;          //服务名称
		_tstring szPathName;      //服务二进制文件路径
		UINT32 ProcessId;         //进程ID
		UINT32 ServiceSpecificExitCode;
		_tstring szServiceType;   //服务类型
		BOOL bStarted;
		_tstring szStartMode;     //服务开始模式
		_tstring szStartName;     //
		_tstring szState;         //服务当前状态
		_tstring szStatus;
		_tstring szSystemCreationClassName;
		_tstring szSystemName;    //系统名
		UINT32 TagId;
		UINT32 WaitHint;
	}WMI_SERVICE_INFO,*PWMI_SERVICE_INFO;

	int GetServiceInformation(vector < WMI_SERVICE_INFO > * pInfo, LPCTSTR szIP = _T("."), LPCTSTR szUserName = NULL, LPCTSTR szPassword = NULL);

private:
	vector<WMI_SERVICE_INFO>* m_pServiceInfo;
};
