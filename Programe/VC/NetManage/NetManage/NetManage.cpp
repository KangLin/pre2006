// NetManage.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "NetManage.h"
#include "Global.h"

#include "..\..\System\Communicate\TcpSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// The one and only application object

CWinApp theApp;
CGlobal g_GV;

using namespace std;



int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		return 1;
	}

	g_GV.OnDo();

	return nRetCode;
}
