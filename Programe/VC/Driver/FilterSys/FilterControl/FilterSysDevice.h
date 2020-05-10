/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    FilterSysDevice.h
\brief   对驱动设备的控制类
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年6月12日  22:51:19
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/
#pragma once

#include "..\..\..\System\Service\ServiceManage.h"
#include "..\..\..\System\Service\DeviceManage.h"

class CFilterSysDevice : public CServiceManage, public CDeviceManage
{
public:
	CFilterSysDevice(void);
	~CFilterSysDevice(void);
};
