/*******************************************************************************************************
��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
�ļ�����OtherTools.cpp
��  ������������
�����б�
        GetRelativePath
��  ����1.0.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2005��7��30��
ʱ  �䣺16:47:49
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10
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
��������GetRelativePath
��  �����õ����·�������������Ƶ����а塣
��  ����
        void����
����ֵ������Ϊ BOOL ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��30�� 16:46:37
*******************************************************************************************************/
BOOL COtherTools::GetRelativePath(void)
{	
    CComBSTR szFullName;
	if(!GetDocument())
	{
		return FALSE;
	} // ���� if(!GetDocument())
	if(FAILED((m_pDoc->get_FullName(&szFullName))))
	{
		return FALSE;
	} // ���� if(FAILED((m_pDoc->get_FullName(&szFullName))))
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
��������GetDocument
��  �����õ��ĵ�����
��  ����
        void����
����ֵ������Ϊ BOOL ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��30�� 16:47:17
*******************************************************************************************************/
BOOL COtherTools::GetDocument(void)
{
	if(!m_pDTE)
	{
		return FALSE;
	} // ���� if(!m_pDTE)
	m_pDoc = NULL;
	if(FAILED(m_pDTE->get_ActiveDocument(&m_pDoc)) || !m_pDoc)
	{
		return FALSE;
	} // ���� if(FAILED(m_pDTE->get_ActiveDocument(&m_pDoc)) || !m_pDoc)
  
	return TRUE;
}

/*******************************************************************************************************
��������GetSelection
��  �����õ� TextSelectioin ����
��  ����
        void����
����ֵ������Ϊ BOOL ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��30�� 16:47:27
*******************************************************************************************************/
BOOL COtherTools::GetSelection(void)
{
	if(!m_pDTE)
	{
		return FALSE;
	} // ���� if(!m_pDTE)
	if(!GetDocument())
	{
		return FALSE;
	} // ���� if(!GetDocument())
	m_pSel = NULL;
	if(FAILED((m_pDoc->get_Selection((IDispatch * *)&m_pSel))) || !m_pSel)
	{
		return FALSE;
	} // ���� if(FAILED((m_pDoc->get_Selection((IDispatch * *)&m_pSel))) || !m_pSel)
	return TRUE;
}
