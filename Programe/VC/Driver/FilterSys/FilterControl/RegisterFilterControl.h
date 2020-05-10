/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    RegisterMonitorControl.h
\brief   ע�������������ͷ�ļ�
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��6��7��  13:59:21
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/

#ifndef __CREGISTERMONITORCONTROL_H_KL_2007_06_04__
#define __CREGISTERMONITORCONTROL_H_KL_2007_06_04__

#pragma once

#include "FilterSysDevice.h"

class CRegisterFilterControl : public CFilterSysDevice
{
public:
	CRegisterFilterControl(void);
	~CRegisterFilterControl(void);

	BOOL Hook();
	BOOL UnHook();

	BOOL SetProtectContent(LPCTSTR pszContent);
	BOOL RemoveProtectContent(LPCTSTR pszContent);

	BOOL LoadConfig(LPCTSTR lpszFile);
	BOOL SaveConfig(LPCTSTR lpszFile);

};

#endif //__CREGISTERMONITORCONTROL_H_KL_2007_06_04__