/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    FilterSysDevice.h
\brief   �������豸�Ŀ�����
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��6��12��  22:51:19
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
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
