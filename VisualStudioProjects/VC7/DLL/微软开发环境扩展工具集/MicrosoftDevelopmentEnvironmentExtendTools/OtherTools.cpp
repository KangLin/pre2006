/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：OtherTools.cpp
描  述：其它工具
函数列表：
        GetRelativePath
版  本：1.0.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2005年7月30日
时  间：16:47:49
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10
*******************************************************************************************************/
#include "StdAfx.h"
#include ".\othertools.h"
#include "..\..\Syntax\Export.h"

COtherTools::COtherTools(void)
{
}

COtherTools::~COtherTools(void)
{
}

/*******************************************************************************************************
函数名：GetRelativePath
描  述：得到相对路径，并把它复制到剪切板。
参  数：
        void：无
返回值：类型为 BOOL 。
版  本：1.0.0.1
作  者：康  林
时  间：2005年7月30日 16:46:37
*******************************************************************************************************/
BOOL COtherTools::GetRelativePath(void)
{	
    CComBSTR szFullName;
	if(!GetDocument())
	{
		return FALSE;
	} // 结束 if(!GetDocument())
	if(FAILED((m_pDoc->get_FullName(&szFullName))))
	{
		return FALSE;
	} // 结束 if(FAILED((m_pDoc->get_FullName(&szFullName))))
    USES_CONVERSION;
	return ::GetRelativePath(NULL, szFullName);
}

BOOL COtherTools::Inital(EnvDTE::_DTE * pDTE)
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
BOOL COtherTools::GetDocument(void)
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
BOOL COtherTools::GetSelection(void)
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
