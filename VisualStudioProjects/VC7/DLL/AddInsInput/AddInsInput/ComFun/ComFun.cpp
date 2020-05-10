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
函数名：GetTextSelect
描  述：得到 TestSelect 对象
参  数：
        EnvDTE::TextSelection ** ppSel：
返回值：类型为 HRESULT 。
版  本：1.0.0.1
作  者：康  林
时  间：2006年10月24日 8:58:35
*******************************************************************************************************/
HRESULT GetTextSelect(EnvDTE::TextSelection ** ppSel)
{
	HRESULT hr = S_FALSE;

	if(NULL == g_pDTE)
	{
		return S_FALSE;
	}// 结束 if(NULL == g_pDTE)

	CComPtr < EnvDTE::Document > pDoc;

	ASSERT(g_pDTE);
	IfFailGoCheck(g_pDTE->get_ActiveDocument(&pDoc), pDoc);
	IfFailGoCheck(pDoc->get_Selection((IDispatch ** )ppSel), *ppSel);
		
Error:
	return hr;
}

/*******************************************************************************************************
函数名：GetDocument
描  述：得到当前活动文档对象
参  数：
        EnvDTE::Document ** ppDoc：
返回值：类型为 HRESULT 。
版  本：1.0.0.1
作  者：康  林
时  间：2006年10月24日 8:58:59
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
