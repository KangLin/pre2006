// StringDLL.cpp : ���� DLL �ĳ�ʼ�����̡�
//

#include "stdafx.h"
#include "StringDLL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//	ע�⣡
//
//		����� DLL ��̬���ӵ� MFC
//		DLL���Ӵ� DLL ������
//		���� MFC ���κκ����ں�������ǰ��
//		��������� AFX_MANAGE_STATE �ꡣ
//
//		����:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// �˴�Ϊ��ͨ������
//		}
//
//		�˺������κ� MFC ����
//		������ÿ��������ʮ����Ҫ������ζ��
//		��������Ϊ�����еĵ�һ�����
//		���֣������������ж������������
//		������Ϊ���ǵĹ��캯���������� MFC
//		DLL ���á�
//
//		�й�������ϸ��Ϣ��
//		����� MFC ����˵�� 33 �� 58��
//

// CStringDLLApp

BEGIN_MESSAGE_MAP(CStringDLLApp, CWinApp)
END_MESSAGE_MAP()


// CStringDLLApp ����

CStringDLLApp::CStringDLLApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CStringDLLApp ����

CStringDLLApp theApp;


// CStringDLLApp ��ʼ��

BOOL CStringDLLApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

void Shows(CComBSTR * pbszIn, CComBSTR * pbszOut)
{
	USES_CONVERSION;
	LPCTSTR lpszIn = W2CT(*pbszIn);//ָ��
	ATLTRACE(_T("�����ַ�����%s\n"), lpszIn);
	while(*lpszIn != NULL)
	{
		if(*lpszIn == _T('��'))
		{
			TRACE(_T("OK"));
		} // ���� if(*lpszIn == _T('��'))
		TRACE(_T("%c\n"), *lpszIn);
		lpszIn++;
	} // ���� while(lpszIn != NULL)
	ATLTRACE(_T("�����ַ����ĳ��ȣ�LPCTSTR����%d\n"), _tcslen(lpszIn));
    ATLTRACE(_T("�����ַ����ĳ��ȣ�CComBSTR����%d\n"), pbszIn->Length());
	LPTSTR lpszOut = new TCHAR[_tcslen(lpszIn) + sizeof(TCHAR)];
	_tcscpy(lpszOut, lpszIn);
	pbszOut->Empty(); //���
	*pbszOut = lpszOut; //���
	delete []lpszOut;
	return;
}

//�д�,������VB����ʱ,��ֵʱ,û�е���CComBSTR�������캯��,��ֻ�Ǹ��ӵ�CComBSTR��.����VB���ַ����й�
void ShowIn(CComBSTR pbszIn, CComBSTR* pbszOut)
{
	
		USES_CONVERSION;
	LPCTSTR lpszIn = W2CT(pbszIn);//ֵ����
    ATLTRACE(_T("�����ַ�����%s\n"), lpszIn);
	ATLTRACE(_T("�����ַ����ĳ��ȣ�LPCTSTR����%d\n"), _tcslen(lpszIn));
    ATLTRACE(_T("�����ַ����ĳ��ȣ�CComBSTR����%d\n"), pbszIn.Length());
	LPTSTR lpszOut = new TCHAR[_tcslen(lpszIn) + sizeof(TCHAR)];
	_tcscpy(lpszOut, lpszIn);
	pbszOut->Empty(); //���
	*pbszOut = lpszOut; //���
	delete []lpszOut;
	return;

}

//�д�,����������CComBSTR��ֱ���޸�
void ShowInOut(CComBSTR* pbszIn, CComBSTR* pbszOut)
{
	USES_CONVERSION;
	LPTSTR lpszIn = W2T(*pbszIn);//ֵ����
    ATLTRACE(_T("�����ַ�����%s\n"), lpszIn);
	ATLTRACE(_T("�����ַ����ĳ��ȣ�LPCTSTR����%d\n"), _tcslen(lpszIn));
    ATLTRACE(_T("�����ַ����ĳ��ȣ�CComBSTR����%d\n"), pbszIn->Length());
	LPTSTR lpszOut = new TCHAR[_tcslen(lpszIn) + sizeof(TCHAR)];
	*(lpszIn + _tcslen(lpszIn) / 2) = (TCHAR)0;
	pbszOut->Empty(); //���
	*pbszOut = lpszOut; //���
	delete []lpszOut;
	return;
}

void ShowBSTR(BSTR bszIn, BSTR * pbszOut)
{
	USES_CONVERSION;
	LPTSTR lpszIn = W2T(bszIn); //ֵ����
	ATLTRACE(_T("�����ַ�����%s\n"), lpszIn);
	ATLTRACE(_T("�����ַ����ĳ��ȣ�LPCTSTR����%d\n"), _tcslen(lpszIn));
	ATLTRACE(_T("�����ַ����ĳ��ȣ�CComBSTR����%d\n"), ::SysStringLen(bszIn));
	LPTSTR lpszOut = new TCHAR[_tcslen(lpszIn) + sizeof(TCHAR)];
	
	::SysFreeString(*pbszOut);
	*pbszOut = T2BSTR(lpszIn);

	//*pbszOut = lpszOut; //���
	delete []lpszOut;
	return;
}

void ShowL(BSTR bszIn)
{
	ATLTRACE(_T("%s\n"), bszIn);
	ATLTRACE(_T("%d\n"), ::SysStringByteLen(bszIn));
    ATLTRACE(_T("%d\n"), ::SysStringLen(bszIn));
	CComBSTR szOut(_T("Text"));	
	ATLTRACE(_T("%s\n"), szOut);
}