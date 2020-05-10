/*******************************************************************************************************
��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
�ļ�����Events.cpp
��  �������������¼��Ĵ���
��  ����1.0.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2007��5��5��
ʱ  �䣺14:25:16
��������Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*******************************************************************************************************/

#include "stdafx.h"
#include "Events.h"
#include "KeyInput.h"
#include "IncludeFile.h"
#include "ComFun\ComFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace EnvDTE;
using namespace EnvDTE80;
using namespace VCProjectEngineLibrary;

extern CComPtr < EnvDTE::_DTE > g_pDTE;
extern CSystemIncludeTiShi g_SystemIncludeTiShi;
extern CLocalIncludeTiShi g_LocalIncludeTiShi;

/*******************************************************************************************************
��������BeforeKeyPress
��  ������������ǰ�¼���
��  ����
        BSTR bstrKey������ļ�
����ֵ������Ϊ BOOL ��Ҫȡ������ļ�����TRUE����������ļ�����FALSE��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��10��20�� 12:51:18
*******************************************************************************************************/
BOOL __stdcall BeforeKeyPress(BSTR bstrKey)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	TCHAR cInput;
	_tcsncpy(&cInput, bstrKey, 1);
	switch (cInput)
	{
	case _T('\xD'):
		TRACE(_T("ENTER Input\n"));
		if(g_LocalIncludeTiShi.WriteSelection(CIncludeTiShi::LOCAL) == 0)
		{
			return TRUE;
		} // ���� if(g_LocalIncludeTiShi.WriteSelection(CIncludeTiShi::LOCAL) == 0)
		if(0 == g_SystemIncludeTiShi.WriteSelection(CIncludeTiShi::SYSTEM))
		{
			return TRUE;
		} // ���� if(0 == g_SystemIncludeTiShi.WriteSelection(CIncludeTiShi::SYSTEM))
		break;
	default:
		break;
	}

	return FALSE;
}

/*******************************************************************************************************
��������AfterKeyPress
��  ��������������¼���
��  ����
        BSTR bstrKey������ļ�
����ֵ������Ϊ LONG ���ɹ�����0�����򷵻ط��㡣
��  ����1.0.0.1
��  �ߣ���  ��
*******************************************************************************************************/
LONG __stdcall AfterKeyPress(BSTR bstrKey)
{

	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	static BOOL bState = FALSE;
	if(bState)
	{
		return 1;
	}// ���� if(bState)
	bState = TRUE;
	static int nCount = 0;
	nCount++;
	TRACE(_T("�����������:%d\n"), nCount);

	HRESULT hr;
	//g_SystemIncludeTiShi.Show(hParent);
	CComPtr < EnvDTE::TextSelection > pSel;
	IfFailGoCheck(GetTextSelect(&pSel), pSel);
	TCHAR cInput;
	_tcsncpy(&cInput, bstrKey, 1);
	switch (cInput)
	{
	case _T('('):
	case _T('['):
	case _T('{'):
		AddBracket(cInput, pSel);
		break;
	case _T('\"'):
	case _T('<'):
		AddIncludeFile(cInput, pSel);
		break;
	case _T('>'):
		g_SystemIncludeTiShi.WriteSelection(CIncludeTiShi::SYSTEM);
		break;
	case _T('\e'):
		TRACE(_T("%s(%d) : Escapes Input.\n"), __FILE__, __LINE__);
		if(g_LocalIncludeTiShi.WriteSelection(CIncludeTiShi::LOCAL) == 0)
		{
			return TRUE;
		} // ���� if(g_LocalIncludeTiShi.WriteSelection(CIncludeTiShi::LOCAL) == 0)
		if(0 == g_SystemIncludeTiShi.WriteSelection(CIncludeTiShi::SYSTEM))
		{
			return TRUE;
		} // ���� if(0 == g_SystemIncludeTiShi.WriteSelection(CIncludeTiShi::SYSTEM))
		break;
	default:
		g_LocalIncludeTiShi.Move(cInput);
		g_SystemIncludeTiShi.Move(cInput);
		break;
	}

	bState = FALSE;
	return 0;

Error:
	bState = FALSE;
	TRACE(_T("AfterKeyPress ����\n"));
	return hr;
}

LONG __stdcall Sol_Open()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	g_LocalIncludeTiShi.Load();
	return 0;
}

LONG __stdcall Sol_AfterClosing()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return 0;
}

LONG __stdcall Sol_BeforeClosing()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	g_LocalIncludeTiShi.Clean();
	return 0;
}

LONG __stdcall Sol_Renamed(BSTR oldName)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return 0;
}

LONG __stdcall Sol_ProjectAdded(EnvDTE::Project*pProject)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CComPtr<EnvDTE::Project> pPro;
	pPro=pProject;

	return 0;
}

LONG __stdcall Sol_ProjectRemoved(EnvDTE::Project * pProject)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return 0;
}

LONG __stdcall Sol_ProjectRenamed(EnvDTE::Project * pProject)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return 0;
}

LONG __stdcall Pro_ItemAdded(EnvDTE::ProjectItem * pItem)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	g_LocalIncludeTiShi.IsIncludeFile(pItem);
	g_LocalIncludeTiShi.SaveDatabase();
	return 0;
}

LONG __stdcall Pro_ItemRemoved(EnvDTE::ProjectItem * pItem)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return 0;
}

LONG __stdcall Pro_ItemRenamed(EnvDTE::ProjectItem * pItem)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	return 0;
}
