// Connect.cpp : Implementation of CConnect
#include "stdafx.h"
#include "AddIn.h"
#include "Connect.h"
#include "..\..\Syntax\Export.h"
#include "..\..\AutoDisplayConstOrMacro\Export.h"
#include ".\connect.h"

extern CAddInModule _AtlModule;

// When run, the Add-in wizard prepared the registry for the Add-in.
// At a later time, if the Add-in becomes unavailable for reasons such as:
//   1) You moved this project to a computer other than which is was originally created on.
//   2) You chose 'Yes' when presented with a message asking if you wish to remove the Add-in.
//   3) Registry corruption.
// you will need to re-register the Add-in by building the MyAddin21Setup project 
// by right clicking the project in the Solution Explorer, then choosing install.


// CConnect
STDMETHODIMP CConnect::OnConnection(IDispatch *pApplication, AddInDesignerObjects::ext_ConnectMode ConnectMode, IDispatch *pAddInInst, SAFEARRAY ** /*custom*/ )
{
	HRESULT hr = S_OK;
	pApplication->QueryInterface(__uuidof(EnvDTE::_DTE), (LPVOID*)&m_pDTE);
	pAddInInst->QueryInterface(__uuidof(EnvDTE::AddIn), (LPVOID * )&m_pAddInInstance);

	m_OtherTools.Inital(m_pDTE);
	m_CLanguage.Inital(m_pDTE);

	if(ConnectMode == 5) //5 == AddInDesignerObjects::ext_cm_UISetup
	{
		LoadCommand() ? hr = S_OK : hr = S_FALSE;
	}

	if(!m_bAutoConstAndMarco)
	{
		if(SetHook())
		{
			m_bAutoConstAndMarco = TRUE;
		} // 结束 if(SetHook())
	} // 结束 if(!m_bAutoConstAndMarco)
	return hr;
}

/*******************************************************************************************************
函数名：LoadCommand
描  述：加载命令
参  数：
        void：无
返回值：类型为 BOOL 。成功返回 TRUE，否则返回 FALSE。
版  本：1.0.0.1
作  者：康  林
时  间：2005年7月30日 16:58:05
*******************************************************************************************************/
BOOL CConnect::LoadCommand(void)
{
	
	CComPtr < EnvDTE::Commands > pCommands;          //命令对象
	CComPtr < Office::_CommandBars > pCommandBars;   //命令条对象	
	CComPtr < Office::CommandBar > pCommandBar;
	CComPtr < Office::CommandBar > pMenuBar;         //菜单条
	CComPtr < Office::CommandBar > pMenuControlBar;  //本程序的菜单项

	IfFailRetrun(m_pDTE->get_CommandBars(&pCommandBars), pCommandBars);
	IfFailRetrun(pCommandBars->get_ActiveMenuBar(&pMenuBar), pMenuBar);
	IfFailRetrun(m_pDTE->get_Commands(&pCommands), pCommands);
	IfFailRetrun(pCommands->AddCommandBar(CComBSTR(_T("扩展工具集(&X)")), EnvDTE::vsCommandBarTypeMenu, pMenuBar, 4, (IDispatch**)&pMenuControlBar), pMenuControlBar);

	pMenuBar = NULL;
	IfFailRetrun(pCommands->AddCommandBar(CComBSTR(_T("帮助")), EnvDTE::vsCommandBarTypeMenu, pMenuControlBar, 1, (IDispatch**)&pMenuBar), pMenuBar);
	AddCommand(pCommands, _T("AboutExtendTools"), _T("关于微软开发环境扩展工具集"), _T("关于微软开发环境扩展工具集"), 49, pMenuBar);
	AddCommand(pCommands, _T("Help"), _T("帮助"), _T("帮助"), 49, pMenuBar);

	pMenuBar = NULL;
	IfFailRetrun(pCommands->AddCommandBar(CComBSTR(_T("工具栏")), EnvDTE::vsCommandBarTypeMenu, pMenuControlBar, 1, (IDispatch**)&pMenuBar), pMenuBar);
	AddCommand(pCommands, _T("OtherTools"), _T("其它工具"), _T("其它工具"), 0, pMenuBar);
	AddCommand(pCommands, _T("HyperLink"), _T("超链接"), _T("超链接"), 0, pMenuBar);
	AddCommand(pCommands, _T("CTools"), _T("C 语言工具"), _T("C 语言工具"), 0, pMenuBar);
	AddCommand(pCommands, _T("Comments"), _T("显示注释工具栏"), _T("显示注释工具栏"), 0, pMenuBar);

	pMenuBar = NULL;
	IfFailRetrun(pCommands->AddCommandBar(CComBSTR(_T("设置")), EnvDTE::vsCommandBarTypeMenu, pMenuControlBar, 1, (IDispatch**)&pMenuBar), pMenuBar);        
	AddCommand(pCommands, _T("OtherSettings"), _T("设置"), _T("设置"), 548, pMenuBar);

	pMenuBar = NULL;
	IfFailRetrun(pCommands->AddCommandBar(CComBSTR(_T("其它工具")), EnvDTE::vsCommandBarTypeMenu, pMenuControlBar, 1, (IDispatch**)&pMenuBar), pMenuBar);
	pCommandBar = NULL;
	IfFailRetrun(pCommands->AddCommandBar(CComBSTR(_T("其它工具")), EnvDTE::vsCommandBarTypeToolbar, NULL, 1, (IDispatch * *)&pCommandBar), pCommandBar);
	AddCommand(pCommands, _T("GetFileRelativePath"), _T("得到文件相对路径，路径复制到剪切板中"), _T("得到文件相对路径，路径复制到剪切板中"), 249, pMenuBar, pCommandBar);
	AddCommand(pCommands, _T("GetDate"), _T("得到当前日期"), _T("得到当前日期"), 83, pMenuBar, pCommandBar);
	AddCommand(pCommands, _T("GetTime"), _T("得到当前时间"), _T("得到当前时间"), 33, pMenuBar, pCommandBar);

	pMenuBar = NULL;
	IfFailRetrun(pCommands->AddCommandBar(CComBSTR(_T("超链接")), EnvDTE::vsCommandBarTypeMenu, pMenuControlBar, 1, (IDispatch * *)&pMenuBar), pMenuBar);
	pCommandBar = NULL;
	IfFailRetrun(pCommands->AddCommandBar(CComBSTR(_T("超链接")), EnvDTE::vsCommandBarTypeToolbar, NULL, 1, (IDispatch * *)&pCommandBar), pCommandBar);
	pCommandBar->put_Visible(VARIANT_TRUE);
	AddCommand(pCommands, _T("CreateHyperlink"), _T("建立超链接"), _T("建立超链接"), 340, pMenuBar, pCommandBar);
	AddCommand(pCommands, _T("GoHyperlink"), _T("转到超链接"), _T("转到超链接"), 136, pMenuBar, pCommandBar);
	AddCommand(pCommands, _T("CreateBookMark"), _T("插入书签"), _T("插入书签"), 233, pMenuBar, pCommandBar);

	pMenuBar = NULL;
	IfFailRetrun(pCommands->AddCommandBar(CComBSTR(_T("C 语言工具")), EnvDTE::vsCommandBarTypeMenu, pMenuControlBar, 1, (IDispatch**)&pMenuBar), pMenuBar);
	pCommandBar = NULL;
	IfFailRetrun(pCommands->AddCommandBar(CComBSTR(_T("C 语言工具")), EnvDTE::vsCommandBarTypeToolbar, NULL, 1, (IDispatch * *)&pCommandBar), pCommandBar);
	pCommandBar->put_Visible(VARIANT_TRUE);
	AddCommand(pCommands, _T("AutoDispConstOrMacro"), _T("自动提示常量或宏"), _T("自动提示常量或宏"), 180, pMenuBar);
	AddCommand(pCommands, _T("AutoFomatVCCode"), _T("自动格式化 C 代码"), _T("自动格式化 C 代码"), 253, pMenuBar);
	AddCommand(pCommands, _T("ModifyEndLineComment"), _T("自动修改程序块结束行的注释"), _T("自动修改程序块结束行的注释"), 162, pMenuBar);
	AddCommand(pCommands, _T("UncommentTRACE"), _T("取消注释的 TRACE 语句"), _T("取消注释的 TRACE 语句"), 663, pMenuBar, pCommandBar);
	AddCommand(pCommands, _T("CommentTRACE"), _T("注释 TRACE 语句"), _T("注释 TRACE 语句"), 662, pMenuBar, pCommandBar);
	AddCommand(pCommands, _T("IncludeFile"), _T("添加头文件"), _T("添加头文件"), 246, pMenuBar, pCommandBar);
	AddCommand(pCommands, _T("SwitchCppToH"), _T("实现文件(CPP)与头文件(H)互相切换"), _T("实现文件(CPP)与头文件(H)互相切换"), 173, pMenuBar, pCommandBar);

	pMenuBar = NULL;
	IfFailRetrun(pCommands->AddCommandBar(CComBSTR(_T("注释")), EnvDTE::vsCommandBarTypeMenu, pMenuControlBar, 1, (IDispatch**)&pMenuBar), pMenuBar);
	pCommandBar = NULL;
	IfFailRetrun(pCommands->AddCommandBar(CComBSTR(_T("注释")), EnvDTE::vsCommandBarTypeToolbar, NULL, 1, (IDispatch**)&pCommandBar), pCommandBar);
	pCommandBar->put_Visible(VARIANT_TRUE);
	AddCommand(pCommands, _T("Modify"), _T("修改信息"), _T("修改信息"), 47, pMenuBar, pCommandBar);
	AddCommand(pCommands, _T("AddEndIf"), _T("增加块结束注释"), _T("增加块结束注释"), 288, pMenuBar, pCommandBar);
	AddCommand(pCommands, _T("AlignComment1"), _T("自动对齐语句后的注释"), _T("自动对齐语句后的注释(以最远处为对齐点)"), 15, pMenuBar, pCommandBar);
	AddCommand(pCommands, _T("AlignComment"), _T("自动对齐语句后的注释"), _T("自动对齐语句后的注释"), 14, pMenuBar, pCommandBar);
	AddCommand(pCommands, _T("FunctionComment"), _T("增加函数注释"), _T("增加函数注释"), 593, pMenuBar, pCommandBar);

	return TRUE;
}

/*******************************************************************************************************
函数名：AddCommand
描 述：增加命令
参  数：
        EnvDTE::Commands * pCommands：命令
		LPCTSTR szCommandName       ：命令名
		LPCTSTR szButtonText        ：命令按钮上的文本
		LPCTSTR szToolTip           ：ToolTip 文本
		long nIcon                  ：命令按钮图标
		IDispatch * pOwner          ：工具条控件
		IDispatch * pOwner1         ：菜单控件
返回值：HRESULT
版  本：2005.8.0.0
作  者：康  林
时  间：2005年7月27日 17:03:38
*******************************************************************************************************/
HRESULT CConnect::AddCommand(EnvDTE::Commands * pCommands, LPCTSTR szCommandName, LPCTSTR szButtonText, LPCTSTR szToolTip, long nIcon, IDispatch * pOwner, IDispatch * pOwner1)
{
	// When run, the Add-in wizard prepared the registry for the Add-in.
    // At a later time, the Add-in or its commands may become unavailable for reasons such as:
    //   1) You moved this project to a computer other than which is was originally created on.
    //   2) You chose 'Yes' when presented with a message asking if you wish to remove the Add-in.
    //   3) You add new commands or modify commands already defined.
    // You will need to re-register the Add-in by building the MicrosoftDevelopmentEnvironmentExtendToolsSetup project,
    // right-clicking the project in the Solution Explorer, and then choosing install.
    // Alternatively, you could execute the ReCreateCommands.reg file the Add-in Wizard generated in 
    // the project directory, or run 'devenv /setup' from a command prompt.
	
	ATLASSERT(pOwner != NULL);
	CComPtr < EnvDTE::Command > pCreatedCommand;
	CComPtr < Office::CommandBarControl > pCommandBarControl;
	HRESULT hr = S_OK;
	if(SUCCEEDED(pCommands->AddNamedCommand(m_pAddInInstance, CComBSTR(szCommandName), CComBSTR(szButtonText), CComBSTR(szToolTip), VARIANT_TRUE, nIcon, NULL, EnvDTE::vsCommandStatusSupported + EnvDTE::vsCommandStatusEnabled, &pCreatedCommand)) && pCreatedCommand)
	{
		if(FAILED(pCreatedCommand->AddControl(pOwner, 1, &pCommandBarControl)))
		{
			ATLTRACE(_T("%s(%d) : %s\n"), __FILE__, __LINE__, szCommandName);
		} // 结束 if(FAILED(pCreatedCommand->AddControl(pOwner, 1, &pCommandBarControl)))
		if(pOwner1)
		{
			pCommandBarControl = NULL;			
			CComPtr < Office::_CommandBarButton > pCommandBarButton;			
			if(SUCCEEDED(pCreatedCommand->AddControl(pOwner1, 1, (Office::CommandBarControl**)&pCommandBarButton)) && pCommandBarButton)
			{
				pCommandBarButton->put_Style(Office::msoButtonIcon);
			} // 结束 if(SUCCEEDED(pCreatedCommand->AddControl(pOwner1, 1, (Office::CommandBarControl * *)&pCommandBarButton)) && pCommandBarButton)
		} // 结束 if(SUCCEEDED(pCreatedCommand->AddControl(pOwner, 1, &pCommandBarControl)) && pCommandBarControl)
	}
	else
	{
		ATLTRACE(_T("%s(%d) : %s\n"), __FILE__, __LINE__, szCommandName);
		hr = S_FALSE;
	} // 结束 if(SUCCEEDED(pCommand->AddNamedCommand(m_pAddInInstance, CComBSTR(szCommandName), CComBSTR(szButtonText), CComBSTR(szToolTip), VARIANT_TRUE, nIcon, NULL, EnvDTE::vsCommandStatusSupported + EnvDTE::vsCommandStatusEnabled, &pCreatedCommand)) && pCreatedCommand)
	
	return hr;
}

STDMETHODIMP CConnect::OnDisconnection(AddInDesignerObjects::ext_DisconnectMode /*RemoveMode*/, SAFEARRAY ** /*custom*/ )
{
	
	m_pDTE = NULL;
	UnHook();
	m_bAutoConstAndMarco = FALSE;
    	
	return S_OK;
}

STDMETHODIMP CConnect::OnAddInsUpdate (SAFEARRAY ** /*custom*/ )
{
	return S_OK;
}

STDMETHODIMP CConnect::OnStartupComplete (SAFEARRAY ** /*custom*/ )
{
	return S_OK;
}

STDMETHODIMP CConnect::OnBeginShutdown (SAFEARRAY ** /*custom*/ )
{
	return S_OK;
}

STDMETHODIMP CConnect::QueryStatus(BSTR bstrCmdName, EnvDTE::vsCommandStatusTextWanted NeededText, EnvDTE::vsCommandStatus *pStatusOption, VARIANT *pvarCommandText)
{
	if(NeededText == EnvDTE::vsCommandStatusTextWantedNone)
	{
		*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusEnabled + EnvDTE::vsCommandStatusSupported);
		if(CmpBSTR(bstrCmdName, _T("AutoDispConstOrMacro")))
		{
			if(m_bAutoConstAndMarco)
			{
				*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusEnabled + EnvDTE::vsCommandStatusSupported + EnvDTE::vsCommandStatusLatched); 
			}
			else
			{
				*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusEnabled + EnvDTE::vsCommandStatusSupported);
			} // 结束 if(AutoDispConstOrMacro)
		} // 结束 if(CmpBSTR(bstrCmdName, _T("AutoDispConstOrMacro")))
		SetToolBarStatus(bstrCmdName, _T("OtherTools"), _T("其它工具"), pStatusOption);
		SetToolBarStatus(bstrCmdName, _T("HyperLink"), _T("超链接"), pStatusOption);
		SetToolBarStatus(bstrCmdName, _T("CTools"), _T("C 语言工具"), pStatusOption);
		SetToolBarStatus(bstrCmdName, _T("Comments"), _T("注释"), pStatusOption);
	}
	return S_OK;
}

STDMETHODIMP CConnect::Exec(BSTR bstrCmdName, EnvDTE::vsCommandExecOption ExecuteOption, VARIANT * /*pvarVariantIn*/, VARIANT * /*pvarVariantOut*/, VARIANT_BOOL *pvbHandled)
{
	*pvbHandled = VARIANT_FALSE;
	if(ExecuteOption == EnvDTE::vsCommandExecOptionDoDefault)
	{
		if(CmpBSTR(bstrCmdName, _T("IncludeFile")))
		{
			m_CLanguage.IncludeFile();
		} // 结束 if(CmpBSTR(bstrCmdName, _T("IncludeFile")))
		if(CmpBSTR(bstrCmdName, _T("AutoDispConstOrMacro")))
		{
			if(m_bAutoConstAndMarco)
			{
				if(UnHook())
				{
					m_bAutoConstAndMarco = FALSE;
					MessageBox(NULL, _T("停止自动常量、宏提示器"), _T("微软开发环境扩展工具集 —— 康林工作室"), MB_OK);
				} // 结束 if(UnHook())
			}
            else
			{
				if(SetHook())
				{
					m_bAutoConstAndMarco = TRUE;
					MessageBox(NULL, _T("启用自动常量、宏提示器"), _T("微软开发环境扩展工具集 —— 康林工作室"), MB_OK);
				} // 结束 if(SetHook())
			} // 结束 if(m_bAutoConstAndMarco)
		} // 结束 if(CmpBSTR(bstrCmdName, _T("AutoDispConstOrMacro")))

		if(CmpBSTR(bstrCmdName, _T("GetFileRelativePath")))
		{
			m_OtherTools.GetRelativePath();
		} // 结束 if(CmpBSTR(bstrCmdName, _T("GetFileRelativePath")))

		SetToolBarExec(bstrCmdName, _T("OtherTools"), _T("其它工具"));
		SetToolBarExec(bstrCmdName, _T("HyperLink"), _T("超链接"));
		SetToolBarExec(bstrCmdName, _T("CTools"), _T("C 语言工具"));
		SetToolBarExec(bstrCmdName, _T("Comments"), _T("注释"));

		if(CmpBSTR(bstrCmdName, _T("Help")))
		{
			ShowHelp();
		} // 结束 if(CmpBSTR(bstrName, _T("About")))
		if(CmpBSTR(bstrCmdName, _T("AboutExtendTools")))
		{
			ShowVersion();
		} // 结束 if(CmpBSTR(bstrCmdName, _T("AboutExtendTools")))

		*pvbHandled = VARIANT_TRUE;
		return S_OK;		
	}
	return S_OK;
}

BOOL CConnect::CmpBSTR(BSTR bstrCmdName, LPCTSTR lpszName)
{
	CComBSTR szName(_T("MicrosoftDevelopmentEnvironmentExtendTools.Connect."));
	szName.Append(lpszName);
	if(!_wcsicmp(bstrCmdName, szName))
	{
		return TRUE; 
	}
    else
	{
		return FALSE;
	} // 结束 if(!_wcsicmp(bstrCmdName, szName))
}

/*******************************************************************************************************
函数名：SetToolBarStatus
描  述：设置工具栏菜单项的状态
参  数：
        BSTR bstrCmdName                       ：
		LPCTSTR szCommandName                  ：
		LPCSTR szIndex                         ：
		EnvDTE::vsCommandStatus * pStatusOption：
返回值：HRESULT
版  本：2005.8.0.0
作  者：康  林
时  间：2005年7月27日 18:04:21
*******************************************************************************************************/
HRESULT CConnect::SetToolBarStatus(BSTR bstrCmdName, LPCTSTR szCommandName, LPCSTR szIndex, EnvDTE::vsCommandStatus * pStatusOption)
{
	HRESULT hr = S_FALSE;

	CComBSTR szName(_T("MicrosoftDevelopmentEnvironmentExtendTools.Connect."));
	szName.Append(szCommandName);
	if(!_wcsicmp(bstrCmdName, szName))
	{
		CComPtr < Office::_CommandBars > pCommandBars; //命令条对象	
		CComPtr < Office::CommandBar > pCommandBar;
		if(SUCCEEDED(m_pDTE->get_CommandBars(&pCommandBars)))
		{
			if(SUCCEEDED(pCommandBars->get_Item(CComVariant(szIndex), &pCommandBar)))
			{
				VARIANT_BOOL var;
				if(SUCCEEDED(pCommandBar->get_Visible(&var)))
				{
					if(var == VARIANT_TRUE)
					{
						*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusEnabled + EnvDTE::vsCommandStatusSupported + EnvDTE::vsCommandStatusLatched);
					}
					else
					{
						*pStatusOption = (EnvDTE::vsCommandStatus)(EnvDTE::vsCommandStatusEnabled + EnvDTE::vsCommandStatusSupported);
					} // 结束 if(var == VARIANT_TRUE)
					hr = S_OK;
				} // 结束 if(SUCCEEDE(pCommandBar->get_Visible(&var)))
			} // 结束 if(SUCCEEDED(pCommandBars->get_Item(CComVariant(szIndex), &pCommandBar)))
			pCommandBar = NULL;
		} // 结束 if(SUCCEEDED(m_pDTE->get_CommandBars(&pCommandBars)))
		pCommandBars = NULL;
	} // 结束 if(!_wcsicmp(bstrCmdName, szName))	
	return hr;
}

/*******************************************************************************************************
函数名：SetToolBarExec
描  述：执行工具栏菜单点击操作
参  数：
        BSTR bstrCmdName     ：命令
		LPCTSTR szCommandName：
		LPCSTR szIndex       ：
返回值：HRESULT
版  本：2005.8.0.0
作  者：康  林
时  间：2005年7月27日 18:23:31
*******************************************************************************************************/
HRESULT CConnect::SetToolBarExec(BSTR bstrCmdName, LPCTSTR szCommandName, LPCSTR szIndex)
{
	HRESULT hr = S_FALSE;

	CComBSTR szName(_T("MicrosoftDevelopmentEnvironmentExtendTools.Connect."));
	szName.Append(szCommandName);
	if(!_wcsicmp(bstrCmdName, szName))
	{
		CComPtr < Office::_CommandBars > pCommandBars; //命令条对象	
		CComPtr < Office::CommandBar > pCommandBar;
		if(SUCCEEDED(m_pDTE->get_CommandBars(&pCommandBars)))
		{
			if(SUCCEEDED(pCommandBars->get_Item(CComVariant(szIndex), &pCommandBar)))
			{
				VARIANT_BOOL var;
				if(SUCCEEDED(pCommandBar->get_Visible(&var)))
				{
					if(var == VARIANT_TRUE)
					{
						pCommandBar->put_Visible(VARIANT_FALSE);
					}
					else
					{
						pCommandBar->put_Visible(VARIANT_TRUE);
					} // 结束 if(var == VARIANT_TRUE)
					hr = S_OK;
				} // 结束 if(SUCCEEDE(pCommandBar->get_Visible(&var)))
			} // 结束 if(SUCCEEDED(pCommandBars->get_Item(CComVariant(szIndex), &pCommandBar)))
			pCommandBar.Release();
		} // 结束 if(SUCCEEDED(m_pDTE->get_CommandBars(&pCommandBars)))
		pCommandBars.Release();
	} // 结束 if(!_wcsicmp(bstrCmdName, szName))
	return hr;
}


