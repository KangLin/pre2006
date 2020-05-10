// TEI6690i.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Logon.h"
#include "Test.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR * argv[], TCHAR * envp[])
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
		TRACE(_T("WinSock 初始化失败。"));
		return FALSE;
	}

	//增加:设置版本信息
	CString szInfo;
	szInfo =_T("                        测试程序");
	
	//增加:实例化测试项目(用new实例化测试项目),并用 CTest.AddItem 加入到 CTest 中去
	CTest t;
	t.SetVerInfo(szInfo);
	t.StartTest();

	return nRetCode;
}
