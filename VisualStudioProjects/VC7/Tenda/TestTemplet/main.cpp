// TEI6690i.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Logon.h"
#include "Test.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR * argv[], TCHAR * envp[])
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
		TRACE(_T("WinSock ��ʼ��ʧ�ܡ�"));
		return FALSE;
	}

	//����:���ð汾��Ϣ
	CString szInfo;
	szInfo =_T("                        ���Գ���");
	
	//����:ʵ����������Ŀ(��newʵ����������Ŀ),���� CTest.AddItem ���뵽 CTest ��ȥ
	CTest t;
	t.SetVerInfo(szInfo);
	t.StartTest();

	return nRetCode;
}
