#pragma once

#include "MicrosoftDevelopmentEnvironmentExtendTools.h"
#include "..\..\..\..\VisualStudioProjects\VC7\DLL\Syntax\CSyntax.h"
#include <ATLBASE.H>
#include <afxcom_.h>
#include "helper.h"

#define INITSEL(ret) \
    if(g_pApp == NULL) \
	{ \
		TRACE(_T("%s(%d) : pApp δ��ֵ\n"), __FILE__, __LINE__); \
		return (ret); \
	} \
	ITextDocument* pDoc = GetDispatchProperty<ITextDocument*> \
		(g_pApp, _T("ActiveDocument"), IID_ITextDocument); \
	if(pDoc == NULL)\
	{ \
		return (ret); \
	} /* ���� if(pDoc == NULL) */ \
	ITextSelection* pSel = GetDispatchProperty<ITextSelection*> \
		(pDoc, _T("Selection"), IID_ITextSelection); \
	if(NULL == pSel) \
	{ \
	    pDoc->Release(); \
		return (ret); \
	} /* ���� if(NULL == pSel) */ 

#define ENDSEL \
	pSel->Release(); \
	pDoc->Release();

void Init();
extern "C" BOOL _stdcall SetKeyHook(IApplication *pApplication = NULL); 
extern "C" BOOL _stdcall UnKeyHook();
LRESULT CALLBACK KeyboardProc(int nCode,   //ָ���Ƿ���Ҫ�������Ϣ
    WPARAM wParam,                         //�����ֵ
    LPARAM lParam
    );
LRESULT CALLBACK GetMsgProc(int nCode,        // hook code
							WPARAM wParam,  // �Ƴ���־
							LPARAM lParam   // ��Ϣ�ĵ�ַ
							);

enum KeyAction
{
	KEYENTRY,
	KEYUP,
	KEYDOWN
};
int InsertText(LPCTSTR lpszText);
int KeyDownEvents();
int ModifyEndBracketComment(LPCTSTR szText, LONG iLine);
int EntryEvents();
LONG AddRightBracket();
LONG AutoAddBracket(LPCTSTR szText);
int AddEndBracketComment();
int AddBracket(TCHAR ch);
