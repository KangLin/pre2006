// TEI6608S.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "TEI6608S.h"
#include ".\6608STest.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		return 1;
	}

	if(!::AfxSocketInit()) //��ʼ�� Socket
	{
		_tprintf(_T("WinSock ��ʼ��ʧ�ܡ�"));
		return FALSE;
	}
	
	CString szInfo;
	szInfo = _T("                     TEI6608S�������");

	C6608STest test;
	test.SetVerInfo(szInfo);
	test.SetVerNum(_T("3"), _T("2"));
	test.SetTime(CTime(2005, 12, 21, 0, 0, 0));

	test.StartTest();

	return nRetCode;
}