/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    RegisterMonitorControl.h
\brief   注册表操作控制类的头文件
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年6月7日  13:59:21
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
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