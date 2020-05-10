// TEI6690i.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "TEI6690i.h"
#include "Logon.h"
#include "Test.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

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
		TRACE(_T("��ʼ�� Socket ʧ�ܡ�"));
		return FALSE;
	}
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: ���Ĵ�������Է���������Ҫ
		_tprintf(_T("��������: MFC ��ʼ��ʧ��\n"));
		return 1;
	}

	if(!::AfxSocketInit()) //InitializeSockets())
	{
		TRACE(_T("WinSock ��ʼ��ʧ�ܡ�"));
		_tprintf(_T("WinSock ��ʼ��ʧ�ܡ�"));
		return FALSE;
	}

	// TODO: �ڴ˴�ΪӦ�ó������Ϊ��д���롣
	CTest t;
	t.StartTest();

	return nRetCode;
}

