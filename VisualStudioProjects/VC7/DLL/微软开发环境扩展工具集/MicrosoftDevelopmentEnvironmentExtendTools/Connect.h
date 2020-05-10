// Connect.h : Declaration of the CConnect

#pragma once
#include "resource.h"       // main symbols
#include "othertools.h"
#include "CLanguage.h"

// CConnect
class ATL_NO_VTABLE CConnect : 
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CConnect, &CLSID_Connect>,
		public IDispatchImpl<EnvDTE::IDTCommandTarget, &EnvDTE::IID_IDTCommandTarget, &EnvDTE::LIBID_EnvDTE, 7, 0>,
	public IDispatchImpl<AddInDesignerObjects::_IDTExtensibility2, &AddInDesignerObjects::IID__IDTExtensibility2, &AddInDesignerObjects::LIBID_AddInDesignerObjects, 1, 0>
{
public:
	CConnect()
	{
		m_bAutoConstAndMarco = FALSE;
	}

DECLARE_REGISTRY_RESOURCEID(IDR_ADDIN)
DECLARE_NOT_AGGREGATABLE(CConnect)


BEGIN_COM_MAP(CConnect)
	COM_INTERFACE_ENTRY(AddInDesignerObjects::IDTExtensibility2)
	COM_INTERFACE_ENTRY(EnvDTE::IDTCommandTarget)
	COM_INTERFACE_ENTRY2(IDispatch, AddInDesignerObjects::IDTExtensibility2)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}
	
	void FinalRelease() 
	{
	}

public:
	//IDTExtensibility2 implementation:
	STDMETHOD(OnConnection)(IDispatch * Application, AddInDesignerObjects::ext_ConnectMode ConnectMode, IDispatch *AddInInst, SAFEARRAY **custom);
	STDMETHOD(OnDisconnection)(AddInDesignerObjects::ext_DisconnectMode RemoveMode, SAFEARRAY **custom );
	STDMETHOD(OnAddInsUpdate)(SAFEARRAY **custom );
	STDMETHOD(OnStartupComplete)(SAFEARRAY **custom );
	STDMETHOD(OnBeginShutdown)(SAFEARRAY **custom );
	
	//IDTCommandTarget implementation:
	STDMETHOD(QueryStatus)(BSTR CmdName, EnvDTE::vsCommandStatusTextWanted NeededText, EnvDTE::vsCommandStatus *StatusOption, VARIANT *CommandText);
	STDMETHOD(Exec)(BSTR CmdName, EnvDTE::vsCommandExecOption ExecuteOption, VARIANT *VariantIn, VARIANT *VariantOut, VARIANT_BOOL *Handled);

	CComPtr<EnvDTE::_DTE> m_pDTE;
	CComPtr<EnvDTE::AddIn> m_pAddInInstance;
	
private:
	// º”‘ÿ√¸¡Ó
	BOOL LoadCommand(void);
	HRESULT AddCommand(EnvDTE::Commands * pCommands, LPCTSTR szCommandName, LPCTSTR szButtonText, LPCTSTR szToolTip, long nIcon, IDispatch * pOwner = NULL, IDispatch * pOwner1 = NULL);
    HRESULT SetToolBarStatus(BSTR bstrCmdName, LPCTSTR szCommandName, LPCSTR szIndex, EnvDTE::vsCommandStatus * pStatusOption);
	HRESULT SetToolBarExec(BSTR bstrCmdName, LPCTSTR szCommandName, LPCSTR szIndex);
	BOOL CmpBSTR(BSTR bstrCmdName, LPCTSTR lpszName);

	BOOL m_bAutoConstAndMarco;
	COtherTools m_OtherTools;
	CCLanguage m_CLanguage;
	
	
};

OBJECT_ENTRY_AUTO(__uuidof(Connect), CConnect)
