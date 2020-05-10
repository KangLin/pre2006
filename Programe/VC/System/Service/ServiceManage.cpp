/*!
\warning Copyright (C) 2007 KangLin Studio;All rights reserved.
\file    ServiceManage.cpp
\brief   ���������ʵ���ļ�
\version 1.0
\author  KangLin (kl222@126.com)
\date    2007-6-5 13:40:14
\par     Compiler:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
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
	} // ���� if(m_hSchSCManager)
}

/*!
\brief   ���÷�����
\param   LPCTSTR lpszName��������
\return  ����Ϊ BOOL ���ɹ�����TRUE,���򷵻�FALSE
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
	} // ���� if(NULL == lpszName)
	m_szServiceName = lpszName;
	return TRUE;
}

/*!
\brief   ���÷��������
\param   LPCTSTR pszMachine��������������IP
\return  ����Ϊ BOOL ���ɹ�����TURE,���򷵻�FALSE
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
	} // ���� if(m_hSchSCManager)
	m_hSchSCManager = OpenSCManager(pszMachine, NULL, SC_MANAGER_ALL_ACCESS);
	if(m_hSchSCManager == NULL)
	{
		bRet = FALSE;
	} // ���� if(m_hSchSCManager == NULL)
	return bRet;
}

/*!
\brief   ��װָ���ķ��񵽷����������
\param   LPCTSTR pszPath    ������ִ���ļ���ȫ·��
\param   DWORD dwServiceType����������
		 \li SERVICE_FILE_SYSTEM_DRIVER
		 \li SERVICE_KERNEL_DRIVER
		 \li SERVICE_WIN32_OWN_PROCESS
		 \li SERVICE_WIN32_SHARE_PROCESS
		 \li SERVICE_INTERACTIVE_PROCESS
\param   DWORD dwStartType  ����ʼ����
		 \li SERVICE_AUTO_START
		 \li SERVICE_BOOT_START
		 \li SERVICE_DEMAND_START
		 \li SERVICE_DISABLED
		 \li SERVICE_SYSTEM_START
\return  ����Ϊ BOOL ���ɹ�����TRUE,���򷵻�FALSE.
\version 1.0
\author  ��  ��
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
\brief   �ӷ�����������Ƴ�����
\param   ��
\return  ����Ϊ BOOL ���ɹ�����TRUE,���򷵻�FALSE
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
\brief   ��װ����ʼ����
\param   LPCTSTR pszPath������·��
\return  ����Ϊ BOOL ���ɹ�����TRUE,���򷵻�FALSE
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
\brief   ֹͣ��ж�ط���
\param   ��
\return  ����Ϊ BOOL ���ɹ�����TRUE,���򷵻�FALSE
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
\brief   ��ʼ����
\param   ��
\return  ����Ϊ BOOL ���ɹ�����TRUE,���򷵻�FALSE
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
\brief   ֹͣ����
\param   ��
\return  ����Ϊ BOOL ���ɹ�����TRUE,���򷵻�FALSE
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
	} // ���� if(NULL == hService)
	bRet = ::QueryServiceStatus(m_hSchSCManager, pStatus);
	::CloseServiceHandle(hService);
	return bRet;
}