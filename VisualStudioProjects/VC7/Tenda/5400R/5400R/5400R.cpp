// 5400R.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "5400R.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <string>
#include "..\..\TestTemplet\Test.h"
#include "5400RTest.h"

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

	C5400RTest test;
	string sztmp;
	sztmp = _T("                    5400R��Ʒ���Գ���");
	test.SetVerInfo(sztmp.c_str());
	test.SetTime(CTime(2005, 12, 13, 0, 0, 0));
	test.StartTest();

	return nRetCode;
}
