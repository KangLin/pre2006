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
��������GetDocument
��  �����õ��ĵ�����
��  ����
        void����
����ֵ������Ϊ BOOL ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��30�� 16:47:17
*******************************************************************************************************/
BOOL CDelete::GetDocument(void)
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
BOOL CDelete::GetSelection(void)
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
