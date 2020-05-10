/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    ProcessInformation.h
\brief   得到进程信息类头文件
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年8月15日  16:48:21
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
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
\brief   得到进程的信息类
\version 1.0
\author  康  林
\date    2007-8-15 16:49:27
*/
class DllExport CProcessInformation
{
public:
	CProcessInformation();
	virtual ~CProcessInformation();

	typedef struct _MODULEINFO                  //!模块信息结构
	{
		_tstring szModuleName;                  //!<模块名
		DWORD dwGlbUsege;                       //!<模块全局引用数
		DWORD dwProcUsage;                      //!<模块在本进程中的引用数
		BYTE * dwBaseAddr;                      //!<基址
		DWORD dwSize;                           //!<模块尺寸
		_tstring szExePath;                     //!<模块全路径
	} MODULEINFO, *PMODULEINFO; 

	typedef struct _PROCESS_MODULE_INFO         //!进程信息(包括模块)结构
	{
		_tstring szProcessName;                 //!<进程名
		DWORD dwProcessID;                      //!<进程ID
		DWORD dwParentID;                       //!<父ID
		DWORD dwPriority;                       //!<优先级
		DWORD dwUsage;                          //!<进程引用数
		DWORD dwThreadCount;                    //!<线程数
		DWORD dwModuleCount;                    //!<模块数
		vector<MODULEINFO> Module;              //!<模块信息
	} PROCESS_MODULE_INFO,*PPROCESS_MODULE_INFO;  

	typedef struct _PROCESS_INFO                //!进程信息结构
	{
		_tstring szProcessName;                 //!<进程名
		_tstring szProcessPath;                 //!进程的全路径
		DWORD dwProcessID;                      //!<进程ID
		DWORD dwParentID;                       //!<父ID
		DWORD dwPriority;                       //!<优先级
		DWORD dwUsage;                          //!<进程引用数
		DWORD dwThreadCount;                    //!<线程数
	} PROCESS_INFO, *PPROCESS_INFO;  

	//得到指定进程的模块名
	virtual _tstring GetProcessName(DWORD dwPID);
	//得到指定进程的全路径
	virtual _tstring GetProcessPath(DWORD dwPID);
	//得到指定进程（包括模块）所有信息
	virtual int GetProcessModuleInfo(DWORD dwPID, PPROCESS_MODULE_INFO pInfo);
	//得到所有进程（包括模块）的信息
	virtual int GetAllProcessModuleInfo(vector<PROCESS_MODULE_INFO> *Info);
	//得到指定进程信息
	virtual int GetProcessInfo(DWORD dwPID, PPROCESS_INFO pInfo);
	//得到所有进程信息
	virtual int GetAllProcessInfo(vector<PROCESS_INFO> *pInfo);

};

#endif //__PROCESS_H_KL_2007_07_02__