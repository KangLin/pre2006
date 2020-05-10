/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    WMIComputerSystem.h
\brief   ��WMI�����õ��������Ϣ
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��9��8��  15:58:13
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/
#pragma once

#include "..\..\..\..\VisualStudioProjects\VC7\socmca\socmca\WMI\WMI.h"
#include <string>
using namespace std;

#ifdef SYSTEMINFO_EXPORTS
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif

class DllExport CWMIComputerSystem : public CWMI
{
public:
	CWMIComputerSystem(void);
	virtual ~CWMIComputerSystem(void);

	virtual int OnEnum(IWbemClassObject * pclsObj);

	typedef struct _COMPUTER_SYSTEM_INFORMATION
	{
		_tstring szCaption;
		_tstring szManufacturer;
		_tstring szModel;
		_tstring szSystemType;
		_tstring szDomain;
		_tstring szUserName;
		_tstring szBootupState;
		_tstring szInitialLoadInfo;
		_tstring szLastLoadInfo;
		_tstring szName;
		_tstring szNameFormat;
		_tstring szPrimaryOwnerContact;
		_tstring szPrimaryOwnerName;
		_tstring szWorkgroup;
	}COMPUTER_SYSTEM_INFORMATION, *PCOMPUTER_SYSTEM_INFORMATION;

	int GetComputerSystemInformation(PCOMPUTER_SYSTEM_INFORMATION pComputerSystemInformation, LPCTSTR szIP = _T("."), LPCTSTR szUserName = NULL, LPCTSTR szPassword = NULL);

private:
	PCOMPUTER_SYSTEM_INFORMATION m_pComputerSystem;
};
