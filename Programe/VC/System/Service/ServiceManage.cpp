/*!
\warning Copyright (C) 2007 KangLin Studio;All rights reserved.
\file    ServiceManage.cpp
\brief   服务管理类实现文件
\version 1.0
\author  KangLin (kl222@126.com)
\date    2007-6-5 13:40:14
\par     Compiler:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#include "StdAfx.h"
#include "ServiceManage.h"
#include "Instdrv.h"
#include <tchar.h>

#ifndef ASSERT
#define ASSERT _ASSERT
#endif

CServiceManage::CServiceManage(void)
{
	m_hSchSCManager = NULL;
	SetManager();
}

CServiceManage::~CServiceManage(void)
{
	if(m_hSchSCManager)
	{
		CloseServiceHandle(m_hSchSCManager);
	} // 结束 if(m_hSchSCManager)
}

/*!
\brief   设置服务名
\param   LPCTSTR lpszName：服务名
\return  类型为 BOOL 。成功返回TRUE,否则返回FALSE
\version 1.0
\author  KangLin
\date    2007-6-5 13:41:22
*/
BOOL CServiceManage::SetServiceName(LPCTSTR lpszName)
{
	ASSERT(lpszName);
	if(NULL == lpszName)
	{
		return FALSE;
	} // 结束 if(NULL == lpszName)
	m_szServiceName = lpszName;
	return TRUE;
}

/*!
\brief   设置服务管理器
\param   LPCTSTR pszMachine：管理器的主机IP
\return  类型为 BOOL 。成功返回TURE,否则返回FALSE
\version 1.0
\author  KangLin
\date    2007-6-5 13:42:00
*/
BOOL CServiceManage::SetManager(LPCTSTR pszMachine)
{
	BOOL bRet = TRUE;
	if(m_hSchSCManager)
	{
		CloseServiceHandle(m_hSchSCManager);
	} // 结束 if(m_hSchSCManager)
	m_hSchSCManager = OpenSCManager(pszMachine, NULL, SC_MANAGER_ALL_ACCESS);
	if(m_hSchSCManager == NULL)
	{
		bRet = FALSE;
	} // 结束 if(m_hSchSCManager == NULL)
	return bRet;
}

/*!
\brief   安装指定的服务到服务管理器中
\param   LPCTSTR pszPath    ：服务执行文件的全路径
\param   DWORD dwServiceType：服务类型
		 \li SERVICE_FILE_SYSTEM_DRIVER
		 \li SERVICE_KERNEL_DRIVER
		 \li SERVICE_WIN32_OWN_PROCESS
		 \li SERVICE_WIN32_SHARE_PROCESS
		 \li SERVICE_INTERACTIVE_PROCESS
\param   DWORD dwStartType  ：开始类型
		 \li SERVICE_AUTO_START
		 \li SERVICE_BOOT_START
		 \li SERVICE_DEMAND_START
		 \li SERVICE_DISABLED
		 \li SERVICE_SYSTEM_START
\return  类型为 BOOL 。成功返回TRUE,否则返回FALSE.
\version 1.0
\author  康  林
\date    2007-6-12 21:03:45
*/
BOOL CServiceManage::Install(LPCTSTR pszPath, DWORD dwServiceType, DWORD dwStartType)
{
	BOOL bRet = TRUE;
	ASSERT(m_hSchSCManager);
	bRet = InstallDriver(m_hSchSCManager, m_szServiceName.c_str(), pszPath, dwServiceType, dwStartType);
	return bRet;
}

/*!
\brief   从服务管理器中移除服务
\param   无
\return  类型为 BOOL 。成功返回TRUE,否则返回FALSE
\version 1.0
\author  KangLin
\date    2007-6-5 13:43:31
*/
BOOL CServiceManage::Remove()
{
	BOOL bRet = TRUE;
	bRet = RemoveDriver(m_hSchSCManager, m_szServiceName.c_str());
	return bRet;
}

/*!
\brief   案装并开始服务
\param   LPCTSTR pszPath：服务路径
\return  类型为 BOOL 。成功返回TRUE,否则返回FALSE
\version 1.0
\author  KangLin
\date    2007-6-5 13:44:38
*/
BOOL CServiceManage::Load(LPCTSTR pszPath)
{
	BOOL bRet = TRUE;
	bRet = LoadDeviceDriver(m_szServiceName.c_str(), pszPath);
	return bRet;
}

/*!
\brief   停止并卸载服务
\param   无
\return  类型为 BOOL 。成功返回TRUE,否则返回FALSE
\version 1.0
\author  KangLin
\date    2007-6-5 13:45:17
*/
BOOL CServiceManage::UnLoad()
{
	BOOL bRet = TRUE;
	bRet = UnloadDeviceDriver(m_szServiceName.c_str());
	return bRet;
}

/*!
\brief   开始服务
\param   无
\return  类型为 BOOL 。成功返回TRUE,否则返回FALSE
\version 1.0
\author  KangLin
\date    2007-6-5 13:46:20
*/
BOOL CServiceManage::Start()
{
	BOOL bRet = TRUE;
	bRet = StartDriver(m_hSchSCManager, m_szServiceName.c_str());
	return bRet;
}

/*!
\brief   停止服务
\param   无
\return  类型为 BOOL 。成功返回TRUE,否则返回FALSE
\version 1.0
\author  KangLin
\date    2007-6-5 13:46:42
*/
BOOL CServiceManage::Stop()
{
	BOOL bRet = TRUE;
	bRet = StopDriver(m_hSchSCManager, m_szServiceName.c_str());
	return bRet;
}

BOOL CServiceManage::QueryStatus(LPSERVICE_STATUS pStatus)
{
	BOOL bRet = FALSE;
	SC_HANDLE hService = ::OpenService(m_hSchSCManager, m_szServiceName.c_str(), SERVICE_ALL_ACCESS);
	if(NULL == hService)
	{
		return FALSE;
	} // 结束 if(NULL == hService)
	bRet = ::QueryServiceStatus(m_hSchSCManager, pStatus);
	::CloseServiceHandle(hService);
	return bRet;
}