// AddInMod.cpp : implementation file
//

#include "stdafx.h"
#include ".\ShowDialog\ShowDialog.h"
#include "MicrosoftDevelopmentEnvironmentExtendTools.h"
#include "SetHook.h"
#include "DSAddIn.h"
#include "Commands.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern BOOL g_bAutoFormatCCode;

// This is called when the user first loads the add-in, and on start-up
//  of each subsequent Developer Studio session
STDMETHODIMP CDSAddIn::OnConnection(IApplication* pApp, VARIANT_BOOL bFirstTime,
		long dwCookie, VARIANT_BOOL* OnConnection)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// Store info passed to us
	IApplication* pApplication = NULL;
	if (FAILED(pApp->QueryInterface(IID_IApplication, (void**) &pApplication))
		|| pApplication == NULL)
	{
		*OnConnection = VARIANT_FALSE;
		return S_OK;
	}

	m_pApplication = pApplication;
	m_pApplication->AddRef();
	
	m_dwCookie = dwCookie;

	// Create command dispatch, send info back to DevStudio
	CCommandsObj::CreateInstance(&m_pCommands);
	m_pCommands->AddRef();

	// The QueryInterface above AddRef'd the Application object.  It will
	//  be Release'd in CCommand's destructor.
	m_pCommands->SetApplicationObject(pApplication);

	// (see stdafx.h for the definition of VERIFY_OK)

	VERIFY_OK(pApplication->SetAddInInfo((long) AfxGetInstanceHandle(),
		(LPDISPATCH) m_pCommands, IDR_TOOLBAR_MEDIUM, IDR_TOOLBAR_LARGE, m_dwCookie));

	m_bFirstTime = (VARIANT_TRUE == bFirstTime) ? true : false;
	// Inform DevStudio of the commands we implement
	
#ifndef _DEBUG
#pragma message ("编译了显示许可证")
	if(!ShowLicense())
	{
		*OnConnection = VARIANT_FALSE;
		return S_OK;
	}
#endif

	// TODO: 在此加命令按钮
	//  one for each command your add-in will add.
    if(!AddCommand(_T("SwitchHCpp"), IDS_CMD_SWITCHHCPP, _T("SwitchHCpp"), 1, _T("Ctrl+Shift+S"))
	|| !AddCommand(_T("ResourceAsText"), IDS_CMD_RESOURCEASTEXT, _T("OpenRCAsText"), 2, _T("Alt+R"))
	|| !AddCommand(_T("IncludeFile"), IDS_CMD_INCLUDEFILE, _T("IncludeFile"), 3, _T("Ctrl+Shift+H"))
	|| !AddCommand(_T("AutoDisplayMarcoOrConst"), IDS_CMD_AUTODISPLAYMARCOORCONST, _T("AutoDispayMarcoOrConst"), 0)
	|| !AddCommand(_T("AutoFormatCCode"), IDS_CMD_AUTOFOMATCCODE, _T("AutoFormatCCode"), 4)
	  )
	{
        *OnConnection = VARIANT_FALSE;
		return S_OK;
	}
	
	if(!m_pCommands->m_bAutoDisplayMarcoOrConst)
	{
		//设置宏、常量自动提示器
		m_pCommands->m_bAutoDisplayMarcoOrConst = TRUE; 
		SetHook(); 
		TRACE(_T("%s(%d) : OnConnection\n"), __FILE__, __LINE__);
	}
	if(!g_bAutoFormatCCode)
	{
		SetKeyHook(m_pApplication); 
		
		TRACE(_T("%s(%d) : 给 pApp 赋值\n"), __FILE__, __LINE__); 
	}

	*OnConnection = VARIANT_TRUE;
	return S_OK;
}

// This is called on shut-down, and also when the user unloads the add-in
STDMETHODIMP CDSAddIn::OnDisconnection(VARIANT_BOOL bLastTime)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	m_pCommands->UnadviseFromEvents(); 
	m_pCommands->Release();
	m_pCommands = NULL;    
	
	UnKeyHook();
	UnHook();	//卸载宏、常量自动提示器
	
	m_pApplication->Release();
	m_pApplication = NULL; 
	TRACE(_T("%s(%d) : OnDisconnection\n"), __FILE__, __LINE__);
	return S_OK;
}

/*******************************************************************************************************
函数名：AddCommand
功  能：增加命令按钮
参  数：
         LPCTSTR lpszCmdName：命令名
         UINT ID_STRING：命令描述
         LPCTSTR lpszMethod：方法名
         UINT nImage：图标
		 LPCTSTR lpszKey：快捷键
返回值：成功返回 TRUE,否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2005-7-5
时  间：18:58:18
*******************************************************************************************************/
BOOL CDSAddIn::AddCommand(LPCTSTR lpszCmdName, UINT ID_STRING, LPCTSTR lpszMethod, UINT nImage, LPCTSTR lpszKey)
{
    // The command name should not be localized to other languages.  The 
	//  tooltip, command description, and other strings related to this
	//  command are stored in the string table (IDS_CMD_STRING) and should
	//  be localized.
	LPCTSTR szCommand = lpszCmdName;    //命令
	VARIANT_BOOL bRet;
	CString strCmdString;
	strCmdString.LoadString(ID_STRING); //命令描述
	strCmdString = szCommand + strCmdString;
	CComBSTR bszCmdString(strCmdString);
	CComBSTR bszMethod(lpszMethod);     //方法名
	CComBSTR bszCmdName(szCommand);
	VERIFY_OK(m_pApplication->AddCommand(bszCmdString, bszMethod, nImage, m_dwCookie, &bRet));
	if (bRet == VARIANT_FALSE)
	{
		// AddCommand failed because a command with this name already
		//  exists.  You may try adding your command under a different name.
		//  Or, you can fail to load as we will do here.
		
		return FALSE;
	}

	// Add toolbar buttons only if this is the first time the add-in
	//  is being loaded.  Toolbar buttons are automatically remembered
	//  by Developer Studio from session to session, so we should only
	//  add the toolbar buttons once.
	if (m_bFirstTime)
	{
		VERIFY_OK(m_pApplication->
			AddCommandBarButton(dsGlyph, bszCmdName, m_dwCookie));
	}

	if(lpszKey)
	{
		CString szKey = lpszKey;
		CComBSTR bszKeystroke(szKey);
		CComBSTR bszEditor("Main");
		VERIFY(SUCCEEDED(m_pApplication->
			AddKeyBinding(bszKeystroke, bszCmdName,  bszEditor)));

	}
	return TRUE;
}
