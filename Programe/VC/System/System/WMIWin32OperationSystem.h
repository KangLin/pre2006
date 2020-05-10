/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    WMIWin32OperationSystem.h
\brief   �ãףͣɷ�ʽ�õ�Win32����ϵͳ����Ϣ
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��9��10��  15:54:18
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/

#pragma once

#include "..\..\..\..\VisualStudioProjects\VC7\socmca\socmca\WMI\WMI.h"
#include "..\..\NetManage\Commonality\type.h"


#ifdef SYSTEMINFO_EXPORTS
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif

class DllExport CWMIWin32OperationSystem : public CWMI
{
public:
	CWMIWin32OperationSystem(void);
	virtual ~CWMIWin32OperationSystem(void);

	virtual int OnEnum(IWbemClassObject * pclsObj);

	typedef struct _WIN32_OPERATION_SYSTEM_INFOMATION
	{
		_tstring szName;              //����ϵͳ��
		_tstring szVersion;           //�汾��
		_tstring szManufacture;       //����
		_tstring szComputerName;      //�������
		_tstring szSerialNumber;      //���к�
		_tstring szOrganization;      //��֯
		_tstring szRegisteredUser;    //ע���û�
		_tstring szStatus;            //״̬
		_tstring szSystemDevice;      //ϵͳ�豸
		_tstring szSystemDirectory;   //ϵͳĿ¼
		_tstring szSystemDrive;       //ϵͳ����
		_tstring szWindowsDirectory;  //WINDOWSĿ¼
	} WIN32_OPERATION_SYSTEM_INFORMATION, *PWIN32_OPERATION_SYSTEM_INFORMATION;

	virtual int GetWin32OperationSystem(PWIN32_OPERATION_SYSTEM_INFORMATION pWin32OperationSystem, LPCTSTR szIP = _T("."), LPCTSTR szUserName = NULL, LPCTSTR szPassword = NULL);

private:
	PWIN32_OPERATION_SYSTEM_INFORMATION m_pWin32OperationSystem;
};
