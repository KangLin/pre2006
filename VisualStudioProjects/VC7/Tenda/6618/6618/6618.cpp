// 6618.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "6618.h"
#include "6618Test.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

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

	if(!::AfxSocketInit()) //��ʼ�� Socket
	{
		_tprintf(_T("WinSock ��ʼ��ʧ�ܡ�"));
		return FALSE;
	}

	CString sztmp;
	C6618Test test;
	sztmp = _T("                  TEI480T/490T �������");
	test.SetVerInfo(sztmp);
	test.SetVerNum(_T("4"), _T("0"));
	test.SetTime(CTime(2005, 12, 21, 0, 0, 0));
	test.StartTest();

	return nRetCode;
}
