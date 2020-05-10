/*******************************************************************************************************
版权所有 (C) 2007 康林工作室；保留所有权利。
文件名：Events.cpp
描  述：键盘输入事件的处理
版  本：1.0.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2007年5月5日
时  间：14:25:16
编译器：Microsoft Visual Studio 8.0 —— C/C++ 8.0
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
函数名：BeforeKeyPress
描  述：键盘输入前事件。
参  数：
        BSTR bstrKey：输入的键
返回值：类型为 BOOL 。要取消输入的键返回TRUE，接受输入的键返回FALSE。
版  本：1.0.0.1
作  者：康  林
时  间：2006年10月20日 12:51:18
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
		} // 结束 if(g_LocalIncludeTiShi.WriteSelection(CIncludeTiShi::LOCAL) == 0)
		if(0 == g_SystemIncludeTiShi.WriteSelection(CIncludeTiShi::SYSTEM))
		{
			return TRUE;
		} // 结束 if(0 == g_SystemIncludeTiShi.WriteSelection(CIncludeTiShi::SYSTEM))
		break;
	default:
		break;
	}

	return FALSE;
}

/*******************************************************************************************************
函数名：AfterKeyPress
描  述：键盘输入后事件。
参  数：
        BSTR bstrKey：输入的键
返回值：类型为 LONG 。成功返回0，否则返回非零。
版  本：1.0.0.1
作  者：康  林
*******************************************************************************************************/
LONG __stdcall AfterKeyPress(BSTR bstrKey)
{

	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	static BOOL bState = FALSE;
	if(bState)
	{
		return 1;
	}// 结束 if(bState)
	bState = TRUE;
	static int nCount = 0;
	nCount++;
	TRACE(_T("键盘输入个数:%d\n"), nCount);

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
		} // 结束 if(g_LocalIncludeTiShi.WriteSelection(CIncludeTiShi::LOCAL) == 0)
		if(0 == g_SystemIncludeTiShi.WriteSelection(CIncludeTiShi::SYSTEM))
		{
			return TRUE;
		} // 结束 if(0 == g_SystemIncludeTiShi.WriteSelection(CIncludeTiShi::SYSTEM))
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
	TRACE(_T("AfterKeyPress 出错。\n"));
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
