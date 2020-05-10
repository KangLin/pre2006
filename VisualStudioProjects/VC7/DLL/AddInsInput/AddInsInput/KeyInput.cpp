/*******************************************************************************************************
版权所有 (C) 2007 康林工作室；保留所有权利。
文件名：KeyInput.cpp
描  述：处理键盘输入事件的相关函数
版  本：1.0.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2007年5月5日
时  间：14:26:22
编译器：Microsoft Visual Studio 8.0 —— C/C++ 8.0
*******************************************************************************************************/

#include "stdafx.h"
#include "KeyInput.h"
#include "IncludeFile.h"
#include "addinsinput.h"
#include <atlrx.h>
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
函数名：AddBracket
描  述：自动增加右边括号
参  数：
        TCHAR cIn                   ：输入的括号
		EnvDTE::TextSelection * pSel：
返回值：类型为 int 。成功返回0，否则返回非零。
版  本：1.0.0.1
作  者：康  林
时  间：2006年10月20日 9:02:41
*******************************************************************************************************/
int AddBracket(TCHAR cIn, EnvDTE::TextSelection * pSel)
{
	HRESULT hr;
	int nRet = 0;
	TCHAR c;
	switch(cIn)
	{
	case _T('('):
		c = _T(')');
		break;
	case _T('['):
		c = _T(']');
		break;
	case _T('{'):
		c = _T('}');
		break;
	default:
		break;
	}// 结束 switch(c)

	CComBSTR bstrText;
	CComPtr<EnvDTE::EditPoint> pEp;
	//IfFailGo(pSel->CharRight(VARIANT_TRUE, 1));
	IfFailGoCheck(GetEditPoint(&pEp), pEp);
	//得到下一个字符
	IfFailGo(pEp->GetText(CComVariant(1), &bstrText));
	//IfFailGo(pSel->get_Text(&bstrText));
	//是否插入一个相应的符号
	//后一个字符为空格或制表符时
	if(!_tcsncmp(bstrText, _T(" "), 1) || !_tcsncmp(bstrText, _T("\t"), 1))
	{
		//IfFailGo(pSel->CharLeft(VARIANT_TRUE, 1));
		//IfFailGo(pSel->put_Text(CComBSTR(1, &c)));
		IfFailGo(pSel->Insert(CComBSTR(1, &c), EnvDTE::vsInsertFlagsCollapseToStart));
		//IfFailGo(pSel->CharLeft(VARIANT_FALSE, 1));
	}
	else if(!_tcsncmp(bstrText, _T("\r"), 1)) //行尾
	{
		//IfFailGo(pSel->CharLeft(VARIANT_FALSE, 1));
		//IfFailGo(pSel->put_Text(CComBSTR(1, &c)));
		IfFailGo(pSel->Insert(CComBSTR(1, &c), EnvDTE::vsInsertFlagsCollapseToStart));
		//IfFailGo(pSel->CharLeft(VARIANT_FALSE, 1));
	}
	else if(!_tcsncmp(bstrText, _T("\0"), 1)) //文档尾
	{
		//IfFailGo(pSel->CharLeft(VARIANT_TRUE, 1));
		IfFailGo(pSel->Insert(CComBSTR(1, &c), EnvDTE::vsInsertFlagsCollapseToStart));
	}
	return nRet;

Error:
	ASSERT(FALSE);
	return nRet;
}

int AddIncludeFile(TCHAR c, EnvDTE::TextSelection * pSel)
{
	CString szText;
	CComBSTR bstrText;
	HRESULT hr;
	CAtlRegExp < > reInclude;
	CAtlREMatchContext < > mcInclude;
	CString szParse(_T("{#include[ \t]*"));
	szParse += c;
	szParse += _T("}");

	CComPtr < EnvDTE::TextPoint > pTP;

	IfFailGoCheck(pSel->get_BottomPoint((EnvDTE::VirtualPoint ** )&pTP), pTP);
	IfFailGo(pSel->StartOfLine(EnvDTE::vsStartOfLineOptionsFirstText, VARIANT_TRUE));
	IfFailGo(pSel->get_Text(&bstrText));
	szText = bstrText;
	IfFailGo(pSel->MoveToPoint(pTP, VARIANT_FALSE));
	
	REParseError status = reInclude.Parse(szParse);
	if(REPARSE_ERROR_OK != status)
	{
		TRACE(_T("%s(%d) : AddIncludeFile:解析出错。\n"), __FILE__, __LINE__);
		return 1;
	}

	if(!reInclude.Match(szText, &mcInclude))
	{
		TRACE(_T("%s(%d) : AddIncludeFile:匹配出错。\n"), __FILE__, __LINE__);
		return 1;
	}
	if(mcInclude.m_uNumGroups == 1)
	{
		//显示提示框
		TRACE(_T("%s(%d) : Show TiShi.\n"), __FILE__, __LINE__);
		//如果提示框已经显示了，则表明输入有错
		switch(c)
		{
		case _T('\"'):
			if(g_LocalIncludeTiShi.IsShow())
			{
				g_LocalIncludeTiShi.WriteSelection(CIncludeTiShi::LOCAL);
			}
			else
			{
				g_LocalIncludeTiShi.Show();
			}	// 结束 if(g_LocalIncludeTiShi.IsShow())
			break;
		case _T('<'):
			if(g_SystemIncludeTiShi.Show())
			{
				TRACE(_T("%s(%d) : 输入有误。\n"), __FILE__, __LINE__);
			} // 结束 if(g_SystemIncludeTiShi.Show())
			break;
		default:
			break;
		} // 结束 switch(c)
	} // 结束 if(mcInclude.m_uNumGroups == 1)

	return 0;

Error:
	return 1;
}