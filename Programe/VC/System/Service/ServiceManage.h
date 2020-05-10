/*!
\warning Copyright (C) 2007 KangLin Studio;All rights reserved.
\file    ServiceManage.h
\brief   ���������ͷ�ļ�
\version 1.0
\author  KangLin (kl222@126.com)
\date    2007-6-5 13:40:37
\par     Compiler:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/

#pragma once

#include <Windows.h>
#include <Winsvc.h>
#include <string>
using namespace std;

#ifdef UNICODE
#define _tstring wstring
#else
#define _tstring string
#endif

class CServiceManage
{
public:
	CServiceManage(void);
	~CServiceManage(void);

	BOOL SetServiceName(LPCTSTR lpszName);
	BOOL SetManager(LPCTSTR pszMachine = NULL);

	BOOL Install(LPCTSTR pszPath = NULL, DWORD dwServiceType = SERVICE_KERNEL_DRIVER, DWORD dwStartType = SERVICE_DEMAND_START);
	BOOL Remove();

	BOOL Load(LPCTSTR pszPath = NULL);
	BOOL UnLoad();

	BOOL Start();
	BOOL Stop();

	BOOL QueryStatus(LPSERVICE_STATUS pStatus);

private:
	SC_HANDLE m_hSchSCManager;
	_tstring m_szServiceName;
};