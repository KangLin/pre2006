
#pragma once

// 注意: 我们添加 IID_IKeyInput 支持
//以支持来自 VBA 的类型安全绑定。此 IID 必须同附加到 .IDL 文件中的
//调度接口的 GUID 匹配。

// {87741D4A-7277-4D93-98F0-D116B995FD91}
static const IID IID_IKeyInput =
{ 0x87741D4A, 0x7277, 0x4D93, { 0x98, 0xF0, 0xD1, 0x16, 0xB9, 0x95, 0xFD, 0x91 } };

// {BD08738C-FE72-42b5-AB62-41459C98476F}
static const IID IID_IKeyEvents = 
{ 0xbd08738c, 0xfe72, 0x42b5, { 0xab, 0x62, 0x41, 0x45, 0x9c, 0x98, 0x47, 0x6f } };


// CKeyInput 命令目标

class CKeyInput : public CCmdTarget
{
	DECLARE_DYNCREATE(CKeyInput)

public:
	CKeyInput();
	virtual ~CKeyInput();

	virtual void OnFinalRelease();

    void FireEventV(DISPID dispid, BYTE* pbParams,	va_list argList);

    void FireEvent(DISPID dispid, BYTE* pbParams, ...);

    BEGIN_CONNECTION_PART(CKeyInput, KeyEventsConnPt)
        CONNECTION_IID(IID_IKeyEvents)
    END_CONNECTION_PART(KeyEventsConnPt)

protected:
	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CKeyInput)
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
    DECLARE_CONNECTION_MAP()

public:
    void a(void);
};

HHOOK g_hKeyHook;
CKeyInput* g_pKeyInput;

LRESULT CALLBACK KeyboardProc(int nCode,   //指定是否需要处理该消息
    WPARAM wParam,                         //虚拟键值
    LPARAM lParam
    );

