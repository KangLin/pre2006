// 6618.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "6618.h"
#include "6618Test.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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

	CString sztmp;
	C6618Test test;
	sztmp = _T("                  TEI480T/490T 产测程序");
	test.SetVerInfo(sztmp);
	test.SetVerNum(_T("4"), _T("0"));
	test.SetTime(CTime(2005, 12, 21, 0, 0, 0));
	test.StartTest();

	return nRetCode;
}
