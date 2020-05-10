/*!
\warning Copyright (C) 2007 KangLin Studio;All rights reserved.
\file    DeviceManage.cpp
\brief   设备管理类的实现文件
\version 1.0
\author  KangLin (kl222@126.com)
\date    2007-6-5 13:39:48
\par     Compiler:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/
#include "StdAfx.h"
#include "DeviceManage.h"
#include <tchar.h>
#include "Instdrv.h"

#ifndef ASSERT
#define ASSERT _ASSERT
#endif

CDeviceManage::CDeviceManage(void)
{
	m_hDev = NULL;
}

CDeviceManage::~CDeviceManage(void)
{
	Close();
}

/*!
\brief   设备设备名
\param   LPCTSTR lpszName：设备名
\return  类型为 BOOL 。成功返回TRUE,否则返回FALSE
\version 1.0
\author  KangLin
\date    2007-6-5 13:47:16
*/
BOOL CDeviceManage::SetDeviceName(LPCTSTR lpszName)
{
	ASSERT(lpszName);
	if(NULL == lpszName)
	{
		return FALSE;
	} // 结束 if(NULL == lpszName)
	m_szDeviceName = lpszName;
	return TRUE;
}

/*!
\brief   打开设备
\param   无
\return  类型为 BOOL 。成功返回TRUE,否则返回FALSE
\version 1.0
\author  KangLin
\date    2007-6-5 13:47:34
*/
BOOL CDeviceManage::Open()
{
	HANDLE h = NULL;
	BOOL bRet = TRUE;
	ASSERT(!m_szDeviceName.empty());
	bRet = OpenDevice(m_szDeviceName.c_str(), &h);
	if(bRet)
	{
		m_hDev = h;
	} // 结束 if(bRet)
	return bRet;
}

/*!
\brief   关闭设备
\param   无
\return  类型为 BOOL 。成功返回TRUE,否则返回FALSE
\version 1.0
\author  KangLin
\date    2007-6-5 13:47:59
*/
BOOL CDeviceManage::Close()
{
	if(m_hDev)
	{
		BOOL bRet = CloseHandle(m_hDev);
		m_hDev = NULL;
		return bRet;
	}// 结束 if(m_hDev)
	return FALSE;
}

/*!
\brief   DeviceIoControl
\param   DWORD dwIoControlCode    ：[in] Control code for the operation. 
\param   LPVOID lpInBuffer        ：[in] Pointer to the input buffer that contains the data required to perform the operation. 
									The format of this data depends on the value of the dwIoControlCode parameter. 
									This parameter can be NULL if dwIoControlCode specifies an operation that does not require input data.
\param   DWORD nInBufferSize      ：[in] Size of the input buffer, in bytes. 
\param   LPVOID lpOutBuffer       ：[out] Pointer to the output buffer that is to receive the data returned by the operation. 
									The format of this data depends on the value of the dwIoControlCode parameter. 
									This parameter can be NULL if dwIoControlCode specifies an operation that does not return data.
\param   DWORD nOutBufferSize     ：[in] Size of the output buffer, in bytes. 
\param   LPDWORD lpBytesReturned  ：[out] Pointer to a variable that receives the size of the data stored in the output buffer, in bytes. 
\param   LPOVERLAPPED lpOverlapped：[in] Pointer to an OVERLAPPED structure. 
\return  类型为 BOOL 。If the function succeeds, the return value is nonzero.
\version 1.0
\author  KangLin
\date    2007-6-5 13:53:21
*/
BOOL CDeviceManage::DeviceIoControl(DWORD dwIoControlCode,
									LPVOID lpInBuffer, DWORD nInBufferSize,
									LPVOID lpOutBuffer, DWORD nOutBufferSize,
									LPDWORD lpBytesReturned,
									LPOVERLAPPED lpOverlapped)
{
	ASSERT(m_hDev);
	return ::DeviceIoControl(m_hDev, dwIoControlCode,
							lpInBuffer, nInBufferSize,
							lpOutBuffer, nOutBufferSize,
							lpBytesReturned,
							lpOverlapped);
}

BOOL CDeviceManage::DeviceIoControl( DWORD dwIoControlCode,
											LPVOID lpInBuffer,
											DWORD nInBufferSize,
											LPVOID lpOutBuffer,
											DWORD nOutBufferSize)
{
	DWORD dwRet = 0;
	return DeviceIoControl(dwIoControlCode, lpInBuffer, nInBufferSize, lpOutBuffer, nOutBufferSize, &dwRet, NULL);
}