/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    ProcessInformation.h
\brief   �õ�������Ϣ��ͷ�ļ�
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��8��15��  16:48:21
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/

#ifndef __PROCESS_H_KL_2007_07_02__
#define __PROCESS_H_KL_2007_07_02__

#pragma once

#include "..\..\Commonality\type.h"
#include <vector>
using namespace std;

#ifdef PROCESS_EXPORTS
#define DllExport __declspec(dllexport)
#else
#define DllExport __declspec(dllimport)
#endif

/*!
\class   CProcessInformation
\brief   �õ����̵���Ϣ��
\version 1.0
\author  ��  ��
\date    2007-8-15 16:49:27
*/
class DllExport CProcessInformation
{
public:
	CProcessInformation();
	virtual ~CProcessInformation();

	typedef struct _MODULEINFO                  //!ģ����Ϣ�ṹ
	{
		_tstring szModuleName;                  //!<ģ����
		DWORD dwGlbUsege;                       //!<ģ��ȫ��������
		DWORD dwProcUsage;                      //!<ģ���ڱ������е�������
		BYTE * dwBaseAddr;                      //!<��ַ
		DWORD dwSize;                           //!<ģ��ߴ�
		_tstring szExePath;                     //!<ģ��ȫ·��
	} MODULEINFO, *PMODULEINFO; 

	typedef struct _PROCESS_MODULE_INFO         //!������Ϣ(����ģ��)�ṹ
	{
		_tstring szProcessName;                 //!<������
		DWORD dwProcessID;                      //!<����ID
		DWORD dwParentID;                       //!<��ID
		DWORD dwPriority;                       //!<���ȼ�
		DWORD dwUsage;                          //!<����������
		DWORD dwThreadCount;                    //!<�߳���
		DWORD dwModuleCount;                    //!<ģ����
		vector<MODULEINFO> Module;              //!<ģ����Ϣ
	} PROCESS_MODULE_INFO,*PPROCESS_MODULE_INFO;  

	typedef struct _PROCESS_INFO                //!������Ϣ�ṹ
	{
		_tstring szProcessName;                 //!<������
		_tstring szProcessPath;                 //!���̵�ȫ·��
		DWORD dwProcessID;                      //!<����ID
		DWORD dwParentID;                       //!<��ID
		DWORD dwPriority;                       //!<���ȼ�
		DWORD dwUsage;                          //!<����������
		DWORD dwThreadCount;                    //!<�߳���
	} PROCESS_INFO, *PPROCESS_INFO;  

	//�õ�ָ�����̵�ģ����
	virtual _tstring GetProcessName(DWORD dwPID);
	//�õ�ָ�����̵�ȫ·��
	virtual _tstring GetProcessPath(DWORD dwPID);
	//�õ�ָ�����̣�����ģ�飩������Ϣ
	virtual int GetProcessModuleInfo(DWORD dwPID, PPROCESS_MODULE_INFO pInfo);
	//�õ����н��̣�����ģ�飩����Ϣ
	virtual int GetAllProcessModuleInfo(vector<PROCESS_MODULE_INFO> *Info);
	//�õ�ָ��������Ϣ
	virtual int GetProcessInfo(DWORD dwPID, PPROCESS_INFO pInfo);
	//�õ����н�����Ϣ
	virtual int GetAllProcessInfo(vector<PROCESS_INFO> *pInfo);

};

#endif //__PROCESS_H_KL_2007_07_02__