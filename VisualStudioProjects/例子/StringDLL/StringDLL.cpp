// StringDLL.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "StringDLL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//
//	注意！
//
//		如果此 DLL 动态链接到 MFC
//		DLL，从此 DLL 导出并
//		调入 MFC 的任何函数在函数的最前面
//		都必须添加 AFX_MANAGE_STATE 宏。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CStringDLLApp

BEGIN_MESSAGE_MAP(CStringDLLApp, CWinApp)
END_MESSAGE_MAP()


// CStringDLLApp 构造

CStringDLLApp::CStringDLLApp()
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CStringDLLApp 对象

CStringDLLApp theApp;


// CStringDLLApp 初始化

BOOL CStringDLLApp::InitInstance()
{
	CWinApp::InitInstance();

	return TRUE;
}

void Shows(CComBSTR * pbszIn, CComBSTR * pbszOut)
{
	USES_CONVERSION;
	LPCTSTR lpszIn = W2CT(*pbszIn);//指针
	ATLTRACE(_T("输入字符串：%s\n"), lpszIn);
	while(*lpszIn != NULL)
	{
		if(*lpszIn == _T('中'))
		{
			TRACE(_T("OK"));
		} // 结束 if(*lpszIn == _T('中'))
		TRACE(_T("%c\n"), *lpszIn);
		lpszIn++;
	} // 结束 while(lpszIn != NULL)
	ATLTRACE(_T("输入字符串的长度（LPCTSTR）：%d\n"), _tcslen(lpszIn));
    ATLTRACE(_T("输入字符串的长度（CComBSTR）：%d\n"), pbszIn->Length());
	LPTSTR lpszOut = new TCHAR[_tcslen(lpszIn) + sizeof(TCHAR)];
	_tcscpy(lpszOut, lpszIn);
	pbszOut->Empty(); //清空
	*pbszOut = lpszOut; //输出
	delete []lpszOut;
	return;
}

//有错,可能是VB调用时,传值时,没有调用CComBSTR拷贝构造函数,而只是附加到CComBSTR上.这与VB中字符串有关
void ShowIn(CComBSTR pbszIn, CComBSTR* pbszOut)
{
	
		USES_CONVERSION;
	LPCTSTR lpszIn = W2CT(pbszIn);//值传递
    ATLTRACE(_T("输入字符串：%s\n"), lpszIn);
	ATLTRACE(_T("输入字符串的长度（LPCTSTR）：%d\n"), _tcslen(lpszIn));
    ATLTRACE(_T("输入字符串的长度（CComBSTR）：%d\n"), pbszIn.Length());
	LPTSTR lpszOut = new TCHAR[_tcslen(lpszIn) + sizeof(TCHAR)];
	_tcscpy(lpszOut, lpszIn);
	pbszOut->Empty(); //清空
	*pbszOut = lpszOut; //输出
	delete []lpszOut;
	return;

}

//有错,不能在输入CComBSTR中直接修改
void ShowInOut(CComBSTR* pbszIn, CComBSTR* pbszOut)
{
	USES_CONVERSION;
	LPTSTR lpszIn = W2T(*pbszIn);//值传递
    ATLTRACE(_T("输入字符串：%s\n"), lpszIn);
	ATLTRACE(_T("输入字符串的长度（LPCTSTR）：%d\n"), _tcslen(lpszIn));
    ATLTRACE(_T("输入字符串的长度（CComBSTR）：%d\n"), pbszIn->Length());
	LPTSTR lpszOut = new TCHAR[_tcslen(lpszIn) + sizeof(TCHAR)];
	*(lpszIn + _tcslen(lpszIn) / 2) = (TCHAR)0;
	pbszOut->Empty(); //清空
	*pbszOut = lpszOut; //输出
	delete []lpszOut;
	return;
}

void ShowBSTR(BSTR bszIn, BSTR * pbszOut)
{
	USES_CONVERSION;
	LPTSTR lpszIn = W2T(bszIn); //值传递
	ATLTRACE(_T("输入字符串：%s\n"), lpszIn);
	ATLTRACE(_T("输入字符串的长度（LPCTSTR）：%d\n"), _tcslen(lpszIn));
	ATLTRACE(_T("输入字符串的长度（CComBSTR）：%d\n"), ::SysStringLen(bszIn));
	LPTSTR lpszOut = new TCHAR[_tcslen(lpszIn) + sizeof(TCHAR)];
	
	::SysFreeString(*pbszOut);
	*pbszOut = T2BSTR(lpszIn);

	//*pbszOut = lpszOut; //输出
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