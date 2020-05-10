/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    KSFilterControl.h
\brief   ���ڿ��� KSFilter �豸�Ŀ�
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��5��13��  10:38:44
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/


#ifndef __KSFilterControl_H_KL_2007_05_12__
#define __KSFilterControl_H_KL_2007_05_12__

#pragma once

#include "..\..\..\System\Service\DeviceManage.h"
#include "..\..\..\System\Service\ServiceManage.h"

//! CKSFilterControl ��
/*!
	���ڿ��� KSFilter �豸�Ŀ⡣
*/
class CKSFilterControl: public CServiceManage, public CDeviceManage
{
public:
	/*!
		���캯��
	*/
	CKSFilterControl();
	~CKSFilterControl();/*!<��������*/

	BOOL SetProtectFile(LPCTSTR szFile);
	BOOL RemoveProtectFile(LPCTSTR szFile);

	BOOL LoadConfig(LPCTSTR lpszFile = NULL);
	BOOL SaveConfig(LPCTSTR lpszFile = NULL);
};

#endif //__KSFilterControl_H_KL_2007_05_12__