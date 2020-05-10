// CKeyInput.cpp : 实现文件
//

#include "stdafx.h"
#include "KeyInput.h"
#include "CKeyInput.h"
#include ".\ckeyinput.h"


// CKeyInput

IMPLEMENT_DYNCREATE(CKeyInput, CCmdTarget)
CKeyInput::CKeyInput()
{
	EnableAutomation();
    EnableConnections();
	
	// 为了使应用程序在 OLE 自动化对象处于活动状态时保持
	// 运行，构造函数调用 AfxOleLockApp。
    g_pKeyInput = this;
	g_hKeyHook = ::SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)KeyboardProc, AfxGetInstanceHandle(), ::GetCurrentThreadId());
    TRACE(_T("%s(%d) : 安装键盘钩子\n"), __FILE__, __LINE__);
	AfxOleLockApp();
}

CKeyInput::~CKeyInput()
{
	// 为了在用 OLE 自动化创建所有对象后终止应用程序，
	// 析构函数调用 AfxOleUnlockApp。
	
	AfxOleUnlockApp();
    UnhookWindowsHookEx(g_hKeyHook);
}


void CKeyInput::OnFinalRelease()
{
	// 释放了对自动化对象的最后一个引用后，将调用
	// OnFinalRelease。基类将自动
	// 删除该对象。在调用该基类之前，请添加您的
	// 对象所需的附加清除代码。

	CCmdTarget::OnFinalRelease();
}


BEGIN_MESSAGE_MAP(CKeyInput, CCmdTarget)
END_MESSAGE_MAP()


BEGIN_DISPATCH_MAP(CKeyInput, CCmdTarget)
END_DISPATCH_MAP()


BEGIN_INTERFACE_MAP(CKeyInput, CCmdTarget)
	INTERFACE_PART(CKeyInput, IID_IKeyInput, Dispatch)
    INTERFACE_PART(CKeyInput, IID_IConnectionPointContainer, ConnPtContainer)
END_INTERFACE_MAP()

BEGIN_CONNECTION_MAP(CKeyInput, CCmdTarget)
    CONNECTION_PART(CKeyInput, IID_IKeyEvents, KeyEventsConnPt)
END_CONNECTION_MAP()

// {7C6F1364-8C73-4335-B6FD-C61D53681573}
IMPLEMENT_OLECREATE_FLAGS(CKeyInput, "KeyInput.KeyInput", afxRegApartmentThreading, 0x7c6f1364, 0x8c73, 0x4335, 0xb6, 0xfd, 0xc6, 0x1d, 0x53, 0x68, 0x15, 0x73)


// CKeyInput 消息处理程序

void CKeyInput::FireEventV(DISPID dispid, BYTE* pbParams,
	va_list argList)
{
	COleDispatchDriver driver;

	POSITION pos = m_xKeyEventsConnPt.GetStartPosition();
	LPDISPATCH pDispatch;
	while (pos != NULL)
	{
		pDispatch = (LPDISPATCH)m_xKeyEventsConnPt.GetNextConnection(pos);
		if(pDispatch != NULL)
		{
			driver.AttachDispatch(pDispatch, FALSE);
			TRY
				driver.InvokeHelperV(dispid, DISPATCH_METHOD, VT_EMPTY, NULL,
					pbParams, argList);
			END_TRY
			driver.DetachDispatch();
		}
	}
}

void AFX_CDECL CKeyInput::FireEvent(DISPID dispid, BYTE* pbParams, ...)
{
	va_list argList;
	va_start(argList, pbParams);
	FireEventV(dispid, pbParams, argList);
	va_end(argList);
}

LRESULT CALLBACK KeyboardProc(int nCode,   //指定是否需要处理该消息
    WPARAM wParam,                         //虚拟键值
    LPARAM lParam
    )
{
    MessageBox(NULL, _T("OK"), NULL, MB_OK);

    return CallNextHookEx(g_hKeyHook, nCode, wParam, lParam);
}

void CKeyInput::a(void)
{
    
}
