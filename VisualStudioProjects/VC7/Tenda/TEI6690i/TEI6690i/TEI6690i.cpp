// TEI6690i.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "TEI6690i.h"
#include "Logon.h"
#include "Test.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

BOOL InitializeSockets()
{
	try
	{
		//Initialize the sockets
		WORD wVersionRequested;
		WSADATA wsaData;
		int err;
 
		wVersionRequested = MAKEWORD( 2, 2 );
 
		err = WSAStartup( wVersionRequested, &wsaData );
		if (err!=0)
			/* Tell the user that we could not find a usable */
			/* WinSock DLL.                                  */
			return FALSE;
 
		/* Confirm that the WinSock DLL supports 2.2.*/
		/* Note that if the DLL supports versions greater    */
		/* than 2.2 in addition to 2.2, it will still return */
		/* 2.2 in wVersion since that is the version we      */
		/* requested.                                        */
 
		if (LOBYTE(wsaData.wVersion)!=2 || HIBYTE(wsaData.wVersion)!=2)
		{
			/* Tell the user that we could not find a usable */
			/* WinSock DLL.                                  */
			WSACleanup();
			return FALSE;
		}

		return TRUE;
	}
	catch(...)
	{		
		TRACE(_T("初始化 Socket 失败。"));
		return FALSE;
	}
}

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

	if(!::AfxSocketInit()) //InitializeSockets())
	{
		TRACE(_T("WinSock 初始化失败。"));
		_tprintf(_T("WinSock 初始化失败。"));
		return FALSE;
	}

	// TODO: 在此处为应用程序的行为编写代码。
	CTest t;
	t.StartTest();

	return nRetCode;
}

