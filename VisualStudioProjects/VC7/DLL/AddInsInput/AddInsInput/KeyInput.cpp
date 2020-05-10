/*******************************************************************************************************
��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
�ļ�����KeyInput.cpp
��  ����������������¼�����غ���
��  ����1.0.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2007��5��5��
ʱ  �䣺14:26:22
��������Microsoft Visual Studio 8.0 ���� C/C++ 8.0
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
��������AddBracket
��  �����Զ������ұ�����
��  ����
        TCHAR cIn                   �����������
		EnvDTE::TextSelection * pSel��
����ֵ������Ϊ int ���ɹ�����0�����򷵻ط��㡣
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��10��20�� 9:02:41
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
	}// ���� switch(c)

	CComBSTR bstrText;
	CComPtr<EnvDTE::EditPoint> pEp;
	//IfFailGo(pSel->CharRight(VARIANT_TRUE, 1));
	IfFailGoCheck(GetEditPoint(&pEp), pEp);
	//�õ���һ���ַ�
	IfFailGo(pEp->GetText(CComVariant(1), &bstrText));
	//IfFailGo(pSel->get_Text(&bstrText));
	//�Ƿ����һ����Ӧ�ķ���
	//��һ���ַ�Ϊ�ո���Ʊ��ʱ
	if(!_tcsncmp(bstrText, _T(" "), 1) || !_tcsncmp(bstrText, _T("\t"), 1))
	{
		//IfFailGo(pSel->CharLeft(VARIANT_TRUE, 1));
		//IfFailGo(pSel->put_Text(CComBSTR(1, &c)));
		IfFailGo(pSel->Insert(CComBSTR(1, &c), EnvDTE::vsInsertFlagsCollapseToStart));
		//IfFailGo(pSel->CharLeft(VARIANT_FALSE, 1));
	}
	else if(!_tcsncmp(bstrText, _T("\r"), 1)) //��β
	{
		//IfFailGo(pSel->CharLeft(VARIANT_FALSE, 1));
		//IfFailGo(pSel->put_Text(CComBSTR(1, &c)));
		IfFailGo(pSel->Insert(CComBSTR(1, &c), EnvDTE::vsInsertFlagsCollapseToStart));
		//IfFailGo(pSel->CharLeft(VARIANT_FALSE, 1));
	}
	else if(!_tcsncmp(bstrText, _T("\0"), 1)) //�ĵ�β
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
		TRACE(_T("%s(%d) : AddIncludeFile:��������\n"), __FILE__, __LINE__);
		return 1;
	}

	if(!reInclude.Match(szText, &mcInclude))
	{
		TRACE(_T("%s(%d) : AddIncludeFile:ƥ�����\n"), __FILE__, __LINE__);
		return 1;
	}
	if(mcInclude.m_uNumGroups == 1)
	{
		//��ʾ��ʾ��
		TRACE(_T("%s(%d) : Show TiShi.\n"), __FILE__, __LINE__);
		//�����ʾ���Ѿ���ʾ�ˣ�����������д�
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
			}	// ���� if(g_LocalIncludeTiShi.IsShow())
			break;
		case _T('<'):
			if(g_SystemIncludeTiShi.Show())
			{
				TRACE(_T("%s(%d) : ��������\n"), __FILE__, __LINE__);
			} // ���� if(g_SystemIncludeTiShi.Show())
			break;
		default:
			break;
		} // ���� switch(c)
	} // ���� if(mcInclude.m_uNumGroups == 1)

	return 0;

Error:
	return 1;
}