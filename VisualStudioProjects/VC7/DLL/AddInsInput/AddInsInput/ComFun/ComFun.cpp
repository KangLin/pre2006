#include "stdafx.h"
#include "..\stdafx.h"
#include "ComFun.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace EnvDTE;
using namespace EnvDTE80;
using namespace VCProjectEngineLibrary;

extern CComPtr < EnvDTE::_DTE > g_pDTE;

/*******************************************************************************************************
��������GetTextSelect
��  �����õ� TestSelect ����
��  ����
        EnvDTE::TextSelection ** ppSel��
����ֵ������Ϊ HRESULT ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��10��24�� 8:58:35
*******************************************************************************************************/
HRESULT GetTextSelect(EnvDTE::TextSelection ** ppSel)
{
	HRESULT hr = S_FALSE;

	if(NULL == g_pDTE)
	{
		return S_FALSE;
	}// ���� if(NULL == g_pDTE)

	CComPtr < EnvDTE::Document > pDoc;

	ASSERT(g_pDTE);
	IfFailGoCheck(g_pDTE->get_ActiveDocument(&pDoc), pDoc);
	IfFailGoCheck(pDoc->get_Selection((IDispatch ** )ppSel), *ppSel);
		
Error:
	return hr;
}

/*******************************************************************************************************
��������GetDocument
��  �����õ���ǰ��ĵ�����
��  ����
        EnvDTE::Document ** ppDoc��
����ֵ������Ϊ HRESULT ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2006��10��24�� 8:58:59
*******************************************************************************************************/
HRESULT GetDocument(EnvDTE::Document ** ppDoc)
{
	return g_pDTE->get_ActiveDocument(ppDoc);
}

HRESULT GetEditPoint(EnvDTE::EditPoint **ppEditPoint)
{
	HRESULT hr;
	CComPtr<EnvDTE::TextPoint> pTp;
	CComPtr<EnvDTE::TextSelection> pSel;
	IfFailGoCheck(GetTextSelect(&pSel), pSel);
	IfFailGoCheck(pSel->get_ActivePoint((EnvDTE::VirtualPoint **)&pTp), pTp);
	IfFailGoCheck(pTp->CreateEditPoint(ppEditPoint), *ppEditPoint);
	
Error:
	return hr;

}
