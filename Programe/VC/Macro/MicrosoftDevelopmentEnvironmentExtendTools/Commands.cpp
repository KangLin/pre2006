// Commands.cpp : implementation file
//

#include "stdafx.h"
#include ".\SetHook.h"
#include "MicrosoftDevelopmentEnvironmentExtendTools.h"
#include "Commands.h"
#include <comdef.h>
#include "helper.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CComPtr < IApplication > g_pApp; 
extern BOOL g_bAutoFormatCCode; 

/////////////////////////////////////////////////////////////////////////////
// CCommands

CCommands::CCommands()
{
	m_pApplication = NULL;
	m_pApplicationEventsObj = NULL;
	m_pDebuggerEventsObj = NULL;
	m_bAutoDisplayMarcoOrConst = FALSE; 
}

CCommands::~CCommands()
{
	ASSERT (m_pApplication != NULL);
	m_pApplication->Release();
}

void CCommands::SetApplicationObject(IApplication* pApplication)
{
	// This function assumes pApplication has already been AddRef'd
	//  for us, which CDSAddIn did in its QueryInterface call
	//  just before it called us.
	m_pApplication = pApplication;

	// Create Application event handlers
	XApplicationEventsObj::CreateInstance(&m_pApplicationEventsObj);
	m_pApplicationEventsObj->AddRef();
	m_pApplicationEventsObj->Connect(m_pApplication);
	m_pApplicationEventsObj->m_pCommands = this;

	// Create Debugger event handler
	CComPtr<IDispatch> pDebugger;
	if (SUCCEEDED(m_pApplication->get_Debugger(&pDebugger)) 
		&& pDebugger != NULL)
	{
		XDebuggerEventsObj::CreateInstance(&m_pDebuggerEventsObj);
		m_pDebuggerEventsObj->AddRef();
		m_pDebuggerEventsObj->Connect(pDebugger);
		m_pDebuggerEventsObj->m_pCommands = this;
	}
}

void CCommands::UnadviseFromEvents()
{
	ASSERT (m_pApplicationEventsObj != NULL);
	m_pApplicationEventsObj->Disconnect(m_pApplication);
	m_pApplicationEventsObj->Release();
	m_pApplicationEventsObj = NULL;

	if (m_pDebuggerEventsObj != NULL)
	{
		// Since we were able to connect to the Debugger events, we
		//  should be able to access the Debugger object again to
		//  unadvise from its events (thus the VERIFY_OK below--see stdafx.h).
		CComPtr<IDispatch> pDebugger;
		VERIFY_OK(m_pApplication->get_Debugger(&pDebugger));
		ASSERT (pDebugger != NULL);
		m_pDebuggerEventsObj->Disconnect(pDebugger);
		m_pDebuggerEventsObj->Release();
		m_pDebuggerEventsObj = NULL;
	}
}


/////////////////////////////////////////////////////////////////////////////
// Event handlers

// TODO: Fill out the implementation for those events you wish handle
//  Use m_pCommands->GetApplicationObject() to access the Developer
//  Studio Application object

// Application events

HRESULT CCommands::XApplicationEvents::BeforeBuildStart()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::BuildFinish(long nNumErrors, long nNumWarnings)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::BeforeApplicationShutDown()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::DocumentOpen(IDispatch* theDocument)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::BeforeDocumentClose(IDispatch* theDocument)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::DocumentSave(IDispatch* theDocument)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::NewDocument(IDispatch* theDocument)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::WindowActivate(IDispatch* theWindow)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::WindowDeactivate(IDispatch* theWindow)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::WorkspaceOpen()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::WorkspaceClose()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

HRESULT CCommands::XApplicationEvents::NewWorkspace()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}

// Debugger event

HRESULT CCommands::XDebuggerEvents::BreakpointHit(IDispatch* pBreakpoint)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return S_OK;
}


/////////////////////////////////////////////////////////////////////////////
// CCommands methods

STDMETHODIMP CCommands::AutoDispayMarcoOrConst() 
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// TODO: Replace this with the actual code to execute this command
	//  Use m_pApplication to access the Developer Studio Application object,
	//  and VERIFY_OK to see error strings in DEBUG builds of your add-in
	//  (see stdafx.h)

	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));
	
	if(m_bAutoDisplayMarcoOrConst)
	{
		MessageBox(NULL, _T("卸载宏、常量自动提示器"), _T("宏、常量自动提示器"), MB_OK);
		UnHook();
	}
	else
	{
		MessageBox(NULL, _T("安装宏、常量自动提示器"), _T("宏、常量自动提示器"), MB_OK);
		SetHook();
	}
	m_bAutoDisplayMarcoOrConst = !m_bAutoDisplayMarcoOrConst;	
	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
	
	return S_OK;
}

STDMETHODIMP CCommands::SwitchHCpp()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
		
		ITextDocument* pDoc = GetDispatchProperty<ITextDocument*>
		(m_pApplication, _T("ActiveDocument"), IID_ITextDocument);
	if (pDoc)
	{
		CString strFullName = GetStringProperty(pDoc, _T("FullName"));
		pDoc->Release();
		if (ExtensionIs(strFullName, _T("h")))
		{
			strFullName = ChangeFileExt(strFullName, _T("cpp"));
			DoActivateDoc(strFullName);
		}
		else if (ExtensionIs(strFullName, _T("cpp")))
		{
			strFullName = ChangeFileExt(strFullName, _T("h"));
			DoActivateDoc(strFullName);
		}
	}

	return S_OK;
}

void CCommands::DoActivateDoc(LPCTSTR FullName)
{
	USES_CONVERSION;

	// If already opened in Document List, then Activate it
	IDocuments* pDocs = GetDispatchProperty<IDocuments*>
		(m_pApplication, _T("Documents"), IID_IDocuments);
	bool bActived = false;
	if (pDocs)
	{
		long lCount = GetEnumCount(pDocs);
		for (long i=0; i<lCount; i++)
		{
			IGenericDocument* pDoc = GetEnumItem<IDocuments, IGenericDocument>
				(pDocs, i+1, IID_IGenericDocument);
			if (pDoc)
			{
				CString strFullName = GetStringProperty(pDoc, _T("FullName"));
				if (strFullName.CompareNoCase(FullName)==0)
				{
					pDoc->put_Active(VARIANT_TRUE);
					bActived = true;
				}
				pDoc->Release();
			}
			if (bActived) break;
		}

		if (!bActived)   // Not Found, open a new Document
		{
			LPDISPATCH pDisp = NULL;
			_variant_t varType(_T("Text"));
			_variant_t varReadOnly(false);
			CComBSTR bstrFullName(FullName);
			HRESULT hr = pDocs->Open(bstrFullName, varType, varReadOnly, &pDisp);
			if (SUCCEEDED(hr) && pDisp!=NULL)
			{
				IGenericDocument* pDoc = InterfaceAs<IGenericDocument>(pDisp, IID_IGenericDocument);
				if (pDoc)
				{
					pDoc->put_Active(VARIANT_TRUE);
					pDoc->Release();
				}
				pDisp->Release();
			}
		}
		pDocs->Release();
	}
}

STDMETHODIMP CCommands::OpenRCAsText()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
		IBuildProject* pProj = GetDispatchProperty<IBuildProject*>
		(m_pApplication, _T("ActiveProject"), IID_IBuildProject);
	if (pProj)
	{
		CString strPathName = GetStringProperty(pProj, _T("FullName"));
		pProj->Release();
		if (!strPathName.IsEmpty())
		{
			strPathName = ChangeFileExt(strPathName, _T("rc"));
			IDocuments* pDocs = GetDispatchProperty<IDocuments*>
				(m_pApplication, _T("Documents"), IID_IDocuments);
			if (pDocs)
			{
				LPDISPATCH pDisp = NULL;
				_variant_t varType(_T("Text"));
				_variant_t varReadOnly(false);
				CComBSTR bstrPathName(strPathName);
				HRESULT hr = pDocs->Open(bstrPathName, varType, varReadOnly, &pDisp);
				if (SUCCEEDED(hr) && pDisp!=NULL)
				{
					IGenericDocument* pDoc = InterfaceAs<IGenericDocument>(pDisp, IID_IGenericDocument);
					pDisp->Release();
					if (pDoc)
					{
						pDoc->put_Active(VARIANT_TRUE);
						pDoc->Release();
					}
				}
				pDocs->Release();
			}
		}
	}
	
	return S_OK;
}

STDMETHODIMP CCommands::IncludeFile()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	ITextDocument* pDoc = GetDispatchProperty<ITextDocument*>
		(m_pApplication, _T("ActiveDocument"), IID_ITextDocument);
	if(!pDoc)
	{
		return S_OK;
	} // 结束 if(pDoc)
	ITextSelection* pSel = GetDispatchProperty<ITextSelection*>
		(pDoc, _T("Selection"), IID_ITextSelection);
	if(!pSel)
	{
		pDoc->Release();
		return S_OK;
	} // 结束 if(pSel)

	InvokeMethod(pSel, _T("SelectLine"));
	CString szText;
	szText = GetStringProperty(pSel, _T("Text"));
	szText.TrimLeft();
	if(_tcscmp(szText, _T("")))
	{
		InvokeMethod(pSel, _T("StartOfLine"));
		InvokeMethod(pSel, _T("NewLine"));
        InvokeMethod(pSel, _T("LineUp"));
	}
	else
	{
		InvokeMethod(pSel, _T("StartOfLine"));
	}

	//得到文档的文件名
	CString szDocName;
	szDocName = GetStringProperty(pDoc, _T("FullName"));
	CRelativePath rp;
	rp.m_szSource = szDocName;
	if(rp.DoModal() == IDOK)
	{
		CString szVar;
		szVar = _T("#include \"") + rp.m_szRelative + _T("\""); 
		PutDispatchProperty(pSel, _T("Text"), szVar);		
	} // 结束 if(rp.DoModal() == IDOK)

	pSel->Release();
	pDoc->Release();
	return S_OK;
}

STDMETHODIMP CCommands::AutoFormatCCode()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_FALSE));
	if(g_bAutoFormatCCode)
	{
		::MessageBox(NULL, _T("停止自动格式化 C 代码"), _T("自动格式化 C 代码"), MB_OK); 
	}
	else
	{		
		::MessageBox(NULL, _T("启用自动格式化 C 代码"), _T("自动格式化 C 代码"), MB_OK); 
	} // 结束 if(g_bAutoFormatCCode)
	g_bAutoFormatCCode = !g_bAutoFormatCCode; 
	VERIFY_OK(m_pApplication->EnableModeless(VARIANT_TRUE));
	return S_OK;
}