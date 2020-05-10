/*!
\warning Copyright (C) 2007 KangLin Studio;All rights reserved.
\file    DeviceManage.h
\brief   �豸�������ͷ�ļ�
\par     ʹ�÷�����
		 \li �����豸����SetDeviceName
		 \li ���豸  ��Open
		 \li ���Ʋ���  ��DeviceIoControl
		 \li �ر��豸  ��Close
\version 1.0
\author  KangLin (kl222@126.com)
\date    2007-6-5 13:39:10
\par     Compiler:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/

#ifndef __DEVICEMANAGE_H_KL_2007_06_05__
#define __DEVICEMANAGE_H_KL_2007_06_05__

#pragma once
#include <windows.h>
#include <string>
using namespace std;

#ifdef UNICODE
#define _tstring wstring
#else
#define _tstring string
#endif

class CDeviceManage
{
public:
	CDeviceManage(void);
	~CDeviceManage(void);

	BOOL SetDeviceName(LPCTSTR lpszName);

	BOOL Open();
	BOOL Close();
	BOOL DeviceIoControl(DWORD dwIoControlCode,
		LPVOID lpInBuffer,
		DWORD nInBufferSize,
		LPVOID lpOutBuffer,
		DWORD nOutBufferSize,
		LPDWORD lpBytesReturned,
		LPOVERLAPPED lpOverlapped = NULL
		);
	BOOL DeviceIoControl( DWORD dwIoControlCode,
		LPVOID lpInBuffer = NULL,
		DWORD nInBufferSize = 0,
		LPVOID lpOutBuffer = NULL,
		DWORD nOutBufferSize = 0);

protected:
	HANDLE m_hDev;

private:
	_tstring m_szDeviceName;
};

#endif //__DEVICEMANAGE_H_KL_2007_06_05__