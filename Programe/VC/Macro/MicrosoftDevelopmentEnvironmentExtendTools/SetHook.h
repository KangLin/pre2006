#pragma once

#include "MicrosoftDevelopmentEnvironmentExtendTools.h"
#include "..\..\..\..\VisualStudioProjects\VC7\DLL\Syntax\CSyntax.h"
#include <ATLBASE.H>
#include <afxcom_.h>
#include "helper.h"

#define INITSEL(ret) \
    if(g_pApp == NULL) \
	{ \
		TRACE(_T("%s(%d) : pApp 未赋值\n"), __FILE__, __LINE__); \
		return (ret); \
	} \
	ITextDocument* pDoc = GetDispatchProperty<ITextDocument*> \
		(g_pApp, _T("ActiveDocument"), IID_ITextDocument); \
	if(pDoc == NULL)\
	{ \
		return (ret); \
	} /* 结束 if(pDoc == NULL) */ \
	ITextSelection* pSel = GetDispatchProperty<ITextSelection*> \
		(pDoc, _T("Selection"), IID_ITextSelection); \
	if(NULL == pSel) \
	{ \
	    pDoc->Release(); \
		return (ret); \
	} /* 结束 if(NULL == pSel) */ 

#define ENDSEL \
	pSel->Release(); \
	pDoc->Release();

void Init();
extern "C" BOOL _stdcall SetKeyHook(IApplication *pApplication = NULL); 
extern "C" BOOL _stdcall UnKeyHook();
LRESULT CALLBACK KeyboardProc(int nCode,   //指定是否需要处理该消息
    WPARAM wParam,                         //虚拟键值
    LPARAM lParam
    );
LRESULT CALLBACK GetMsgProc(int nCode,        // hook code
							WPARAM wParam,  // 移除标志
							LPARAM lParam   // 消息的地址
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
