/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    WMIServiceInfo.h
\brief   ��WMI�����õ�����
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��9��10��  15:47:48
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/
#pragma once

#include "..\..\..\..\VisualStudioProjects\VC7\socmca\socmca\WMI\WMI.h"
#include "..\..\NetManage\Commonality\type.h"
#include <time.h>
#include <vector>
using namespace std;

#ifdef SYSTEMINFO_EXPORTS
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif

class DllExport CWMIServiceInfo : public CWMI
{
public:
	CWMIServiceInfo(void);
	virtual ~CWMIServiceInfo(void);

	virtual int OnEnum(IWbemClassObject * pclsObj);

	typedef struct _WMI_SERVICE_INFO
	{
		BOOL bAcceptPause;        //�Ƿ������ͣ
		BOOL bAcceptStop;         //�Ƿ����ֹͣ
		_tstring szCaption;       //�������
		UINT32 CheckPoint;
		_tstring szCreationClassName;
		_tstring szDescription;   //���������
		BOOL bDesktopInteract;    //�Ƿ������潻��
		_tstring szDisplayName;   //��ʾ����
		_tstring szErrorControl;  //�������
		UINT32 ExitCode;          //�˳�����
		//time InstallDate;
		_tstring szName;          //��������
		_tstring szPathName;      //����������ļ�·��
		UINT32 ProcessId;         //����ID
		UINT32 ServiceSpecificExitCode;
		_tstring szServiceType;   //��������
		BOOL bStarted;
		_tstring szStartMode;     //����ʼģʽ
		_tstring szStartName;     //
		_tstring szState;         //����ǰ״̬
		_tstring szStatus;
		_tstring szSystemCreationClassName;
		_tstring szSystemName;    //ϵͳ��
		UINT32 TagId;
		UINT32 WaitHint;
	}WMI_SERVICE_INFO,*PWMI_SERVICE_INFO;

	int GetServiceInformation(vector < WMI_SERVICE_INFO > * pInfo, LPCTSTR szIP = _T("."), LPCTSTR szUserName = NULL, LPCTSTR szPassword = NULL);

private:
	vector<WMI_SERVICE_INFO>* m_pServiceInfo;
};
