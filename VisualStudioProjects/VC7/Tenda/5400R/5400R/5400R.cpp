// 5400R.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "5400R.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <string>
#include "..\..\TestTemplet\Test.h"
#include "5400RTest.h"

// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// 初始化 MFC 并在失败时显示错误
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: 更改错误代码以符合您的需要
		_tprintf(_T("致命错误: MFC 初始化失败\n"));
		return 1;
	}

	if(!::AfxSocketInit()) //初始化 Socket
	{
		_tprintf(_T("WinSock 初始化失败。"));
		return FALSE;
	}

	C5400RTest test;
	string sztmp;
	sztmp = _T("                    5400R产品测试程序");
	test.SetVerInfo(sztmp.c_str());
	test.SetTime(CTime(2005, 12, 13, 0, 0, 0));
	test.StartTest();

	return nRetCode;
}
