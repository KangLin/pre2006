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
		} // ���� if(SetHook())
	} // ���� if(!m_bAutoConstAndMarco)
	return hr;
}

/*******************************************************************************************************
��������LoadCommand
��  ������������
��  ����
        void����
����ֵ������Ϊ BOOL ���ɹ����� TRUE�����򷵻� FALSE��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��30�� 16:58:05
*******************************************************************************************************/
BOOL CConnect::LoadCommand(void)
{
	
	CComPtr < EnvDTE::Commands > pCommands;          //�������
	CComPtr < Office::_CommandBars > pCommandBars;   //����������	
	CComPtr < Office::CommandBar > pCommandBar;
	CComPtr < Office::CommandBar > pMenuBar;         //�˵���
	CComPtr < Office::CommandBar > pMenuControlBar;  //������Ĳ˵���

	IfFailRetrun(m_pDTE->get_CommandBars(&pCommandBars), pCommandBars);
	IfFailRetrun(pCommandBars->get_ActiveMenuBar(&pMenuBar), pMenuBar);
	IfFailRetrun(m_pDTE->get_Commands(&pCommands), pCommands);
	IfFailRetrun(pCommands->AddCommandBar(CComBSTR(_T("��չ���߼�(&X)")), EnvDTE::vsCommandBarTypeMenu, pMenuBar, 4, (IDispatch**)&pMenuControlBar), pMenuControlBar);

	pMenuBar = NULL;
	IfFailRetrun(pCommands->AddCommandBar(CComBSTR(_T("����")), EnvDTE::vsCommandBarTypeMenu, pMenuControlBar, 1, (IDispatch**)&pMenuBar), pMenuBar);
	AddCommand(pCommands, _T("AboutExtendTools"), _T("����΢����������չ���߼�"), _T("����΢����������չ���߼�"), 49, pMenuBar);
	AddCommand(pCommands, _T("Help"), _T("����"), _T("����"), 49, pMenuBar);

	pMenuBar = NULL;
	IfFailRetrun(pCommands->AddCommandBar(CComBSTR(_T("������")), EnvDTE::vsCommandBarTypeMenu, pMenuControlBar, 1, (IDispatch**)&pMenuBar), pMenuBar);
	AddCommand(pCommands, _T("OtherTools"), _T("��������"), _T("��������"), 0, pMenuBar);
	AddCommand(pCommands, _T("HyperLink"), _T("������"), _T("������"), 0, pMenuBar);
	AddCommand(pCommands, _T("CTools"), _T("C ���Թ���"), _T("C ���Թ���"), 0, pMenuBar);
	AddCommand(pCommands, _T("Comments"), _T("��ʾע�͹�����"), _T("��ʾע�͹�����"), 0, pMenuBar);

	pMenuBar = NULL;
	IfFailRetrun(pCommands->AddCommandBar(CComBSTR(_T("����")), EnvDTE::vsCommandBarTypeMenu, pMenuControlBar, 1, (IDispatch**)&pMenuBar), pMenuBar);        
	AddCommand(pCommands, _T("OtherSettings"), _T("����"), _T("����"), 548, pMenuBar);

	pMenuBar = NULL;
	IfFailRetrun(pCommands->AddCommandBar(CComBSTR(_T("��������")), EnvDTE::vsCommandBarTypeMenu, pMenuControlBar, 1, (IDispatch**)&pMenuBar), pMenuBar);
	pCommandBar = NULL;
	IfFailRetrun(pCommands->AddCommandBar(CComBSTR(_T("��������")), EnvDTE::vsCommandBarTypeToolbar, NULL, 1, (IDispatch * *)&pCommandBar), pCommandBar);
	AddCommand(pCommands, _T("GetFileRelativePath"), _T("�õ��ļ����·����·�����Ƶ����а���"), _T("�õ��ļ����·����·�����Ƶ����а���"), 249, pMenuBar, pCommandBar);
	AddCommand(pCommands, _T("GetDate"), _T("�õ���ǰ����"), _T("�õ���ǰ����"), 83, pMenuBar, pCommandBar);
	AddCommand(pCommands, _T("GetTime"), _T("�õ���ǰʱ��"), _T("�õ���ǰʱ��"), 33, pMenuBar, pCommandBar);

	pMenuBar = NULL;
	IfFailRetrun(pCommands->AddCommandBar(CComBSTR(_T("������")), EnvDTE::vsCommandBarTypeMenu, pMenuControlBar, 1, (IDispatch * *)&pMenuBar), pMenuBar);
	pCommandBar = NULL;
	IfFailRetrun(pCommands->AddCommandBar(CComBSTR(_T("������")), EnvDTE::vsCommandBarTypeToolbar, NULL, 1, (IDispatch * *)&pCommandBar), pCommandBar);
	pCommandBar->put_Visible(VARIANT_TRUE);
	AddCommand(pCommands, _T("CreateHyperlink"), _T("����������"), _T("����������"), 340, pMenuBar, pCommandBar);
	AddCommand(pCommands, _T("GoHyperlink"), _T("ת��������"), _T("ת��������"), 136, pMenuBar, pCommandBar);
	AddCommand(pCommands, _T("CreateBookMark"), _T("������ǩ"), _T("������ǩ"), 233, pMenuBar, pCommandBar);

	pMenuBar = NULL;
	IfFailRetrun(pCommands->AddCommandBar(CComBSTR(_T("C ���Թ���")), EnvDTE::vsCommandBarTypeMenu, pMenuControlBar, 1, (IDispatch**)&pMenuBar), pMenuBar);
	pCommandBar = NULL;
	IfFailRetrun(pCommands->AddCommandBar(CComBSTR(_T("C ���Թ���")), EnvDTE::vsCommandBarTypeToolbar, NULL, 1, (IDispatch * *)&pCommandBar), pCommandBar);
	pCommandBar->put_Visible(VARIANT_TRUE);
	AddCommand(pCommands, _T("AutoDispConstOrMacro"), _T("�Զ���ʾ�������"), _T("�Զ���ʾ�������"), 180, pMenuBar);
	AddCommand(pCommands, _T("AutoFomatVCCode"), _T("�Զ���ʽ�� C ����"), _T("�Զ���ʽ�� C ����"), 253, pMenuBar);
	AddCommand(pCommands, _T("ModifyEndLineComment"), _T("�Զ��޸ĳ��������е�ע��"), _T("�Զ��޸ĳ��������е�ע��"), 162, pMenuBar);
	AddCommand(pCommands, _T("UncommentTRACE"), _T("ȡ��ע�͵� TRACE ���"), _T("ȡ��ע�͵� TRACE ���"), 663, pMenuBar, pCommandBar);
	AddCommand(pCommands, _T("CommentTRACE"), _T("ע�� TRACE ���"), _T("ע�� TRACE ���"), 662, pMenuBar, pCommandBar);
	AddCommand(pCommands, _T("IncludeFile"), _T("���ͷ�ļ�"), _T("���ͷ�ļ�"), 246, pMenuBar, pCommandBar);
	AddCommand(pCommands, _T("SwitchCppToH"), _T("ʵ���ļ�(CPP)��ͷ�ļ�(H)�����л�"), _T("ʵ���ļ�(CPP)��ͷ�ļ�(H)�����л�"), 173, pMenuBar, pCommandBar);

	pMenuBar = NULL;
	IfFailRetrun(pCommands->AddCommandBar(CComBSTR(_T("ע��")), EnvDTE::vsCommandBarTypeMenu, pMenuControlBar, 1, (IDispatch**)&pMenuBar), pMenuBar);
	pCommandBar = NULL;
	IfFailRetrun(pCommands->AddCommandBar(CComBSTR(_T("ע��")), EnvDTE::vsCommandBarTypeToolbar, NULL, 1, (IDispatch**)&pCommandBar), pCommandBar);
	pCommandBar->put_Visible(VARIANT_TRUE);
	AddCommand(pCommands, _T("Modify"), _T("�޸���Ϣ"), _T("�޸���Ϣ"), 47, pMenuBar, pCommandBar);
	AddCommand(pCommands, _T("AddEndIf"), _T("���ӿ����ע��"), _T("���ӿ����ע��"), 288, pMenuBar, pCommandBar);
	AddCommand(pCommands, _T("AlignComment1"), _T("�Զ����������ע��"), _T("�Զ����������ע��(����Զ��Ϊ�����)"), 15, pMenuBar, pCommandBar);
	AddCommand(pCommands, _T("AlignComment"), _T("�Զ����������ע��"), _T("�Զ����������ע��"), 14, pMenuBar, pCommandBar);
	AddCommand(pCommands, _T("FunctionComment"), _T("���Ӻ���ע��"), _T("���Ӻ���ע��"), 593, pMenuBar, pCommandBar);

	return TRUE;
}

/*******************************************************************************************************
��������AddCommand
�� ������������
��  ����
        EnvDTE::Commands * pCommands������
		LPCTSTR szCommandName       ��������
		LPCTSTR szButtonText        �����ť�ϵ��ı�
		LPCTSTR szToolTip           ��ToolTip �ı�
		long nIcon                  �����ťͼ��
		IDispatch * pOwner          ���������ؼ�
		IDispatch * pOwner1         ���˵��ؼ�
����ֵ��HRESULT
��  ����2005.8.0.0
��  �ߣ���  ��
ʱ  �䣺2005��7��27�� 17:03:38
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
		} // ���� if(FAILED(pCreatedCommand->AddControl(pOwner, 1, &pCommandBarControl)))
		if(pOwner1)
		{
			pCommandBarControl = NULL;			
			CComPtr < Office::_CommandBarButton > pCommandBarButton;			
			if(SUCCEEDED(pCreatedCommand->AddControl(pOwner1, 1, (Office::CommandBarControl**)&pCommandBarButton)) && pCommandBarButton)
			{
				pCommandBarButton->put_Style(Office::msoButtonIcon);
			} // ���� if(SUCCEEDED(pCreatedCommand->AddControl(pOwner1, 1, (Office::CommandBarControl * *)&pCommandBarButton)) && pCommandBarButton)
		} // ���� if(SUCCEEDED(pCreatedCommand->AddControl(pOwner, 1, &pCommandBarControl)) && pCommandBarControl)
	}
	else
	{
		ATLTRACE(_T("%s(%d) : %s\n"), __FILE__, __LINE__, szCommandName);
		hr = S_FALSE;
	} // ���� if(SUCCEEDED(pCommand->AddNamedCommand(m_pAddInInstance, CComBSTR(szCommandName), CComBSTR(szButtonText), CComBSTR(szToolTip), VARIANT_TRUE, nIcon, NULL, EnvDTE::vsCommandStatusSupported + EnvDTE::vsCommandStatusEnabled, &pCreatedCommand)) && pCreatedCommand)
	
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
			} // ���� if(AutoDispConstOrMacro)
		} // ���� if(CmpBSTR(bstrCmdName, _T("AutoDispConstOrMacro")))
		SetToolBarStatus(bstrCmdName, _T("OtherTools"), _T("��������"), pStatusOption);
		SetToolBarStatus(bstrCmdName, _T("HyperLink"), _T("������"), pStatusOption);
		SetToolBarStatus(bstrCmdName, _T("CTools"), _T("C ���Թ���"), pStatusOption);
		SetToolBarStatus(bstrCmdName, _T("Comments"), _T("ע��"), pStatusOption);
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
		} // ���� if(CmpBSTR(bstrCmdName, _T("IncludeFile")))
		if(CmpBSTR(bstrCmdName, _T("AutoDispConstOrMacro")))
		{
			if(m_bAutoConstAndMarco)
			{
				if(UnHook())
				{
					m_bAutoConstAndMarco = FALSE;
					MessageBox(NULL, _T("ֹͣ�Զ�����������ʾ��"), _T("΢����������չ���߼� ���� ���ֹ�����"), MB_OK);
				} // ���� if(UnHook())
			}
            else
			{
				if(SetHook())
				{
					m_bAutoConstAndMarco = TRUE;
					MessageBox(NULL, _T("�����Զ�����������ʾ��"), _T("΢����������չ���߼� ���� ���ֹ�����"), MB_OK);
				} // ���� if(SetHook())
			} // ���� if(m_bAutoConstAndMarco)
		} // ���� if(CmpBSTR(bstrCmdName, _T("AutoDispConstOrMacro")))

		if(CmpBSTR(bstrCmdName, _T("GetFileRelativePath")))
		{
			m_OtherTools.GetRelativePath();
		} // ���� if(CmpBSTR(bstrCmdName, _T("GetFileRelativePath")))

		SetToolBarExec(bstrCmdName, _T("OtherTools"), _T("��������"));
		SetToolBarExec(bstrCmdName, _T("HyperLink"), _T("������"));
		SetToolBarExec(bstrCmdName, _T("CTools"), _T("C ���Թ���"));
		SetToolBarExec(bstrCmdName, _T("Comments"), _T("ע��"));

		if(CmpBSTR(bstrCmdName, _T("Help")))
		{
			ShowHelp();
		} // ���� if(CmpBSTR(bstrName, _T("About")))
		if(CmpBSTR(bstrCmdName, _T("AboutExtendTools")))
		{
			ShowVersion();
		} // ���� if(CmpBSTR(bstrCmdName, _T("AboutExtendTools")))

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
	} // ���� if(!_wcsicmp(bstrCmdName, szName))
}

/*******************************************************************************************************
��������SetToolBarStatus
��  �������ù������˵����״̬
��  ����
        BSTR bstrCmdName                       ��
		LPCTSTR szCommandName                  ��
		LPCSTR szIndex                         ��
		EnvDTE::vsCommandStatus * pStatusOption��
����ֵ��HRESULT
��  ����2005.8.0.0
��  �ߣ���  ��
ʱ  �䣺2005��7��27�� 18:04:21
*******************************************************************************************************/
HRESULT CConnect::SetToolBarStatus(BSTR bstrCmdName, LPCTSTR szCommandName, LPCSTR szIndex, EnvDTE::vsCommandStatus * pStatusOption)
{
	HRESULT hr = S_FALSE;

	CComBSTR szName(_T("MicrosoftDevelopmentEnvironmentExtendTools.Connect."));
	szName.Append(szCommandName);
	if(!_wcsicmp(bstrCmdName, szName))
	{
		CComPtr < Office::_CommandBars > pCommandBars; //����������	
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
					} // ���� if(var == VARIANT_TRUE)
					hr = S_OK;
				} // ���� if(SUCCEEDE(pCommandBar->get_Visible(&var)))
			} // ���� if(SUCCEEDED(pCommandBars->get_Item(CComVariant(szIndex), &pCommandBar)))
			pCommandBar = NULL;
		} // ���� if(SUCCEEDED(m_pDTE->get_CommandBars(&pCommandBars)))
		pCommandBars = NULL;
	} // ���� if(!_wcsicmp(bstrCmdName, szName))	
	return hr;
}

/*******************************************************************************************************
��������SetToolBarExec
��  ����ִ�й������˵��������
��  ����
        BSTR bstrCmdName     ������
		LPCTSTR szCommandName��
		LPCSTR szIndex       ��
����ֵ��HRESULT
��  ����2005.8.0.0
��  �ߣ���  ��
ʱ  �䣺2005��7��27�� 18:23:31
*******************************************************************************************************/
HRESULT CConnect::SetToolBarExec(BSTR bstrCmdName, LPCTSTR szCommandName, LPCSTR szIndex)
{
	HRESULT hr = S_FALSE;

	CComBSTR szName(_T("MicrosoftDevelopmentEnvironmentExtendTools.Connect."));
	szName.Append(szCommandName);
	if(!_wcsicmp(bstrCmdName, szName))
	{
		CComPtr < Office::_CommandBars > pCommandBars; //����������	
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
					} // ���� if(var == VARIANT_TRUE)
					hr = S_OK;
				} // ���� if(SUCCEEDE(pCommandBar->get_Visible(&var)))
			} // ���� if(SUCCEEDED(pCommandBars->get_Item(CComVariant(szIndex), &pCommandBar)))
			pCommandBar.Release();
		} // ���� if(SUCCEEDED(m_pDTE->get_CommandBars(&pCommandBars)))
		pCommandBars.Release();
	} // ���� if(!_wcsicmp(bstrCmdName, szName))
	return hr;
}


