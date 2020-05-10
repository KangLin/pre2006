/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：CLanguage.cpp
描  述：C 语言工具
函数列表：
        SwitchCPPToH
		IncludeFile
版  本：1.0.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2005年7月28日
时  间：13:58:46
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10
*******************************************************************************************************/
#include "StdAfx.h"
#include ".\clanguage.h"
#include "..\..\Syntax\Export.h"
#include < string > 
using namespace std;

CCLanguage::CCLanguage(void)
{
}

CCLanguage::~CCLanguage(void)
{
}

BOOL CCLanguage::Inital(EnvDTE::_DTE * pDTE)
{
	BOOL hr = S_OK;
	m_pDTE = pDTE;
	return TRUE;
}

/*******************************************************************************************************
函数名：GetDocument
描  述：得到文档
参  数：
        void：无
返回值：BOOL
版  本：1.0.0.1
作  者：康  林
时  间：2005年7月28日 13:59:07
*******************************************************************************************************/
BOOL CCLanguage::GetDocument(void)
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
描  述：得到 TextSelection 对象
参  数：
        void：无
返回值：类型为 BOOL。成功返回 TRUE，否则返回 FALSE。
版  本：1.0.0.1
作  者：康  林
时  间：2005年7月30日 16:37:28
*******************************************************************************************************/
BOOL CCLanguage::GetSelection(void)
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

/*******************************************************************************************************
函数名：SwitchCPPToH
描  述：头文件与实现文件互换
参  数：
        void：无
返回值：类型为 BOOL 。
版  本：1.0.0.1
作  者：康  林
时  间：2005年7月30日 16:45:08
*******************************************************************************************************/
BOOL CCLanguage::SwitchCPPToH(void)
{
	if(!GetDocument())
	{
		return FALSE;
	} // 结束 if(!GetDocument())
	CComBSTR szFullName;
	if(FAILED(m_pDoc->get_FullName(&szFullName)))
	{
		return FALSE;
	} // 结束 if(FAILED(m_pDoc->get_FullName(&szFullName)))
	//增加:还没写完，头文件与实现文件互换
	
	return 0;
}

/*******************************************************************************************************
函数名：IncludeFile
描  述：插入头文件
参  数：
        void：无
返回值：类型为 BOOL 。
版  本：1.0.0.1
作  者：康  林
时  间：2005年7月30日 16:45:31
*******************************************************************************************************/
BOOL CCLanguage::IncludeFile(void)
{
    if(!GetSelection())
	{
		return FALSE;
	} // 结束 if(!GetSelection())
	CComBSTR szFullName;
	if(FAILED(m_pDoc->get_Language(&szFullName)))
	{
		return FALSE;
	} // 结束 if(FAILED(m_pDoc->get_Language(&szFullName)))
	if(szFullName != EnvDTE::dsCPP)
	{
		return FALSE;
	} // 结束 if(szFullName != EnvDTE::dsCPP)
	szFullName.Empty();
    if(FAILED(m_pDoc->get_FullName(&szFullName)))
	{
		return FALSE;
	} // 结束 if(FAILED(m_pDoc->get_FullName(&szFullName)))
	TCHAR lpszFile [MAX_PATH];
	USES_CONVERSION;
	if(GetIncludeFile(lpszFile, W2CT(szFullName)) <= 0)
	{
		return FALSE;
	} // 结束 if(GetIncludeFile(lpszFile, W2CT(szFullName)) <= 0)
	CComBSTR szText;
    m_pSel->SelectLine();
	if(FAILED(m_pSel->get_Text(&szText)))
	{
		return FALSE;
	} // 结束 if(FAILED(m_pSel->get_Text(&szText)))

	//增加: 去掉前、后导空格
    CComBSTR lpszText;
	TrimString(szText, &lpszText);
	if(wcscmp(lpszText, L""))
	{
	   m_pSel->StartOfLine(EnvDTE::vsStartOfLineOptionsFirstColumn, VARIANT_FALSE);
	   m_pSel->NewLine(1);
	   m_pSel->LineUp(VARIANT_FALSE, 1);
	} // 结束 if(wcscmp(szText, L""))
	CComBSTR szInput(_T("#include \""));
	szInput += lpszFile;
	szInput += _T("\"");
	m_pSel->Insert(szInput, EnvDTE::vsInsertFlagsInsertAtStart);
	
	return 0;
}