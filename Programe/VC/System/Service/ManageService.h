/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    ManageService.h
\brief   ���ڹ������İ�װ����ʼ��ֹͣ��ж��
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��5��31��  15:25:41
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/
#pragma once
#include <string>
using namespace std;

#ifdef _UNICODE
#define _tstring wstring
#else
#define _tstring string
#endif // ���� #ifdef

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