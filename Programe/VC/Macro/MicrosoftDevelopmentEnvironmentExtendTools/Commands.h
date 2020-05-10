// Commands.h : header file
//

#if !defined(AFX_COMMANDS_H__521BE306_5FBC_4693_B266_92166DA83CD1__INCLUDED_)
#define AFX_COMMANDS_H__521BE306_5FBC_4693_B266_92166DA83CD1__INCLUDED_

#include "MicrosoftDevelopmentEnvironmentExtendToolsTypes.h"
#include "..\..\..\..\VisualStudioProjects\VC7\DLL\AutoDisplayConstOrMacro\AutoDisplayConstOrMacro.h"
#include "RelativePath.h"

class CCommands : 
	public CComDualImpl<ICommands, &IID_ICommands, &LIBID_MicrosoftDevelopmentEnvironmentExtendTools>, 
	public CComObjectRoot,
	public CComCoClass<CCommands, &CLSID_Commands>
{
protected:
	IApplication* m_pApplication;

public:
	CCommands();
	~CCommands();
	void SetApplicationObject(IApplication* m_pApplication);
	IApplication* GetApplicationObject() { return m_pApplication; }
	void UnadviseFromEvents();

	BEGIN_COM_MAP(CCommands)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(ICommands)
	END_COM_MAP()
	DECLARE_NOT_AGGREGATABLE(CCommands)

protected:
	// This class template is used as the base class for the Application
	//  event handler object and the Debugger event handler object,
	//  which are declared below.
	template <class IEvents, const IID* piidEvents, const GUID* plibid,
		class XEvents, const CLSID* pClsidEvents>
	class XEventHandler :
		public CComDualImpl<IEvents, piidEvents, plibid>,
		public CComObjectRoot,
		public CComCoClass<XEvents, pClsidEvents>
	{
	public:
		BEGIN_COM_MAP(XEvents)
			COM_INTERFACE_ENTRY(IDispatch)
			COM_INTERFACE_ENTRY_IID(*piidEvents, IEvents)
		END_COM_MAP()
		DECLARE_NOT_AGGREGATABLE(XEvents)
		void Connect(IUnknown* pUnk)
		{ VERIFY(SUCCEEDED(AtlAdvise(pUnk, this, *piidEvents, &m_dwAdvise))); }
		void Disconnect(IUnknown* pUnk)
		{ AtlUnadvise(pUnk, *piidEvents, m_dwAdvise); }

		CCommands* m_pCommands;

	protected:
		DWORD m_dwAdvise;
	};

	// This object handles events fired by the Application object
	class XApplicationEvents : public XEventHandler<IApplicationEvents, 
		&IID_IApplicationEvents, &LIBID_MicrosoftDevelopmentEnvironmentExtendTools, 
		XApplicationEvents, &CLSID_ApplicationEvents>
	{
	public:
		// IApplicationEvents methods
		STDMETHOD(BeforeBuildStart)(THIS);
		STDMETHOD(BuildFinish)(THIS_ long nNumErrors, long nNumWarnings);
		STDMETHOD(BeforeApplicationShutDown)(THIS);
		STDMETHOD(DocumentOpen)(THIS_ IDispatch * theDocument);
		STDMETHOD(BeforeDocumentClose)(THIS_ IDispatch * theDocument);
		STDMETHOD(DocumentSave)(THIS_ IDispatch * theDocument);
		STDMETHOD(NewDocument)(THIS_ IDispatch * theDocument);
		STDMETHOD(WindowActivate)(THIS_ IDispatch * theWindow);
		STDMETHOD(WindowDeactivate)(THIS_ IDispatch * theWindow);
		STDMETHOD(WorkspaceOpen)(THIS);
		STDMETHOD(WorkspaceClose)(THIS);
		STDMETHOD(NewWorkspace)(THIS);
	};
	typedef CComObject<XApplicationEvents> XApplicationEventsObj;
	XApplicationEventsObj* m_pApplicationEventsObj;

	// This object handles events fired by the Application object
	class XDebuggerEvents : public XEventHandler<IDebuggerEvents, 
		&IID_IDebuggerEvents, &LIBID_MicrosoftDevelopmentEnvironmentExtendTools, 
		XDebuggerEvents, &CLSID_DebuggerEvents>
	{
	public:
		// IDebuggerEvents method
	    STDMETHOD(BreakpointHit)(THIS_ IDispatch * pBreakpoint);
	};
	typedef CComObject<XDebuggerEvents> XDebuggerEventsObj;
	XDebuggerEventsObj* m_pDebuggerEventsObj;


private:
    void DoActivateDoc(LPCTSTR FullName);

public:
	BOOL m_bAutoDisplayMarcoOrConst; 

// ICommands methods
	//宏、常量自动提示器
	STDMETHOD(AutoDispayMarcoOrConst)(THIS);
	//头文件与实现文件互换
	STDMETHOD(SwitchHCpp)(THIS);
	//用文本打开资源
	STDMETHOD(OpenRCAsText)(THIS);
	//添加头文件
	STDMETHOD(IncludeFile)(THIS); 
	//自动格式化 C 代码
	STDMETHOD(AutoFormatCCode)(THIS);
};

typedef CComObject<CCommands> CCommandsObj;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMMANDS_H__521BE306_5FBC_4693_B266_92166DA83CD1__INCLUDED)
