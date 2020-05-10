#include "StdAfx.h"
#include ".\delete.h"

CDelete::CDelete(void)
{
}

CDelete::~CDelete(void)
{
}

BOOL CDelete::DeleteCommand(void)
{
	return 0;
}


BOOL CDelete::Inital(EnvDTE::_DTE * pDTE)
{
	BOOL hr = S_OK;
	m_pDTE = pDTE;
	return TRUE;
}

/*******************************************************************************************************
函数名：GetDocument
描  述：得到文档对象
参  数：
        void：无
返回值：类型为 BOOL 。
版  本：1.0.0.1
作  者：康  林
时  间：2005年7月30日 16:47:17
*******************************************************************************************************/
BOOL CDelete::GetDocument(void)
{
	if(!m_pDTE)
	{
		return FALSE;
	} // 结束 if(!m_pDTE)
	m_pDoc = NULL;
	if(FAILED(m_pDTE->get_ActiveDocument(&m_pDoc)) || !m_pDoc)
	{
		return FALSE;
	} // 结束 if(FAILED(m_pDTE->get_ActiveDocument(&m_pDoc)) || !m_pDoc)
  
	return TRUE;
}

/*******************************************************************************************************
函数名：GetSelection
描  述：得到 TextSelectioin 对象
参  数：
        void：无
返回值：类型为 BOOL 。
版  本：1.0.0.1
作  者：康  林
时  间：2005年7月30日 16:47:27
*******************************************************************************************************/
BOOL CDelete::GetSelection(void)
{
	if(!m_pDTE)
	{
		return FALSE;
	} // 结束 if(!m_pDTE)
	if(!GetDocument())
	{
		return FALSE;
	} // 结束 if(!GetDocument())
	m_pSel = NULL;
	if(FAILED((m_pDoc->get_Selection((IDispatch * *)&m_pSel))) || !m_pSel)
	{
		return FALSE;
	} // 结束 if(FAILED((m_pDoc->get_Selection((IDispatch * *)&m_pSel))) || !m_pSel)
	return TRUE;
}
