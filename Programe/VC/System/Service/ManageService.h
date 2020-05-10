/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    ManageService.h
\brief   用于管理服务的安装、开始、停止、卸载
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年5月31日  15:25:41
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/
#pragma once
#include <string>
using namespace std;

#ifdef _UNICODE
#define _tstring wstring
#else
#define _tstring string
#endif // 结束 #ifdef

class CServiceManage
{
public:
	CServiceManage();
	~CServiceManage();

	BOOL OpenSCManager(LPCTSTR lpMachineName = NULL, LPCTSTR lpDatabaseName = NULL, DWORD dwDesiredAccess = SC_MANAGER_ALL_ACCESS);
	BOOL CloseSCManager();

	BOOL SetServiceName(LPCTSTR lpServiceName) {m_strServiceName = lpServiceName; return TRUE;}

	BOOL InstallService(IN LPCTSTR ServiceExe, IN LPCTSTR ServiceName = NULL, DWORD dwServiceType = SERVICE_WIN32_OWN_PROCESS, DWORD dwStartType = SERVICE_AUTO_START);
	BOOL StartService(IN LPCTSTR ServiceName = NULL);
	BOOL StopService(IN LPCTSTR ServiceName = NULL);
	BOOL RemoveService(IN LPCTSTR ServiceName = NULL);

private:
	SC_HANDLE m_hSchSCManager;
	_tstring m_strServiceName;
};