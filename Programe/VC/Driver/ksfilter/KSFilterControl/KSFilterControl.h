/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    KSFilterControl.h
\brief   用于控制 KSFilter 设备的库
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年5月13日  10:38:44
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/


#ifndef __KSFilterControl_H_KL_2007_05_12__
#define __KSFilterControl_H_KL_2007_05_12__

#pragma once

#include "..\..\..\System\Service\DeviceManage.h"
#include "..\..\..\System\Service\ServiceManage.h"

//! CKSFilterControl 类
/*!
	用于控制 KSFilter 设备的库。
*/
class CKSFilterControl: public CServiceManage, public CDeviceManage
{
public:
	/*!
		构造函数
	*/
	CKSFilterControl();
	~CKSFilterControl();/*!<析构函数*/

	BOOL SetProtectFile(LPCTSTR szFile);
	BOOL RemoveProtectFile(LPCTSTR szFile);

	BOOL LoadConfig(LPCTSTR lpszFile = NULL);
	BOOL SaveConfig(LPCTSTR lpszFile = NULL);
};

#endif //__KSFilterControl_H_KL_2007_05_12__