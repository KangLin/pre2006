/*******************************************************************************************************
��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
�ļ�����CLanguage.cpp
��  ����C ���Թ���
�����б�
        SwitchCPPToH
		IncludeFile
��  ����1.0.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2005��7��28��
ʱ  �䣺13:58:46
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10
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
��������GetDocument
��  �����õ��ĵ�
��  ����
        void����
����ֵ��BOOL
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��28�� 13:59:07
*******************************************************************************************************/
BOOL CCLanguage::GetDocument(void)
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
��  �����õ� TextSelection ����
��  ����
        void����
����ֵ������Ϊ BOOL���ɹ����� TRUE�����򷵻� FALSE��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��30�� 16:37:28
*******************************************************************************************************/
BOOL CCLanguage::GetSelection(void)
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

/*******************************************************************************************************
��������SwitchCPPToH
��  ����ͷ�ļ���ʵ���ļ�����
��  ����
        void����
����ֵ������Ϊ BOOL ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��30�� 16:45:08
*******************************************************************************************************/
BOOL CCLanguage::SwitchCPPToH(void)
{
	if(!GetDocument())
	{
		return FALSE;
	} // ���� if(!GetDocument())
	CComBSTR szFullName;
	if(FAILED(m_pDoc->get_FullName(&szFullName)))
	{
		return FALSE;
	} // ���� if(FAILED(m_pDoc->get_FullName(&szFullName)))
	//����:��ûд�꣬ͷ�ļ���ʵ���ļ�����
	
	return 0;
}

/*******************************************************************************************************
��������IncludeFile
��  ��������ͷ�ļ�
��  ����
        void����
����ֵ������Ϊ BOOL ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005��7��30�� 16:45:31
*******************************************************************************************************/
BOOL CCLanguage::IncludeFile(void)
{
    if(!GetSelection())
	{
		return FALSE;
	} // ���� if(!GetSelection())
	CComBSTR szFullName;
	if(FAILED(m_pDoc->get_Language(&szFullName)))
	{
		return FALSE;
	} // ���� if(FAILED(m_pDoc->get_Language(&szFullName)))
	if(szFullName != EnvDTE::dsCPP)
	{
		return FALSE;
	} // ���� if(szFullName != EnvDTE::dsCPP)
	szFullName.Empty();
    if(FAILED(m_pDoc->get_FullName(&szFullName)))
	{
		return FALSE;
	} // ���� if(FAILED(m_pDoc->get_FullName(&szFullName)))
	TCHAR lpszFile [MAX_PATH];
	USES_CONVERSION;
	if(GetIncludeFile(lpszFile, W2CT(szFullName)) <= 0)
	{
		return FALSE;
	} // ���� if(GetIncludeFile(lpszFile, W2CT(szFullName)) <= 0)
	CComBSTR szText;
    m_pSel->SelectLine();
	if(FAILED(m_pSel->get_Text(&szText)))
	{
		return FALSE;
	} // ���� if(FAILED(m_pSel->get_Text(&szText)))

	//����: ȥ��ǰ���󵼿ո�
    CComBSTR lpszText;
	TrimString(szText, &lpszText);
	if(wcscmp(lpszText, L""))
	{
	   m_pSel->StartOfLine(EnvDTE::vsStartOfLineOptionsFirstColumn, VARIANT_FALSE);
	   m_pSel->NewLine(1);
	   m_pSel->LineUp(VARIANT_FALSE, 1);
	} // ���� if(wcscmp(szText, L""))
	CComBSTR szInput(_T("#include \""));
	szInput += lpszFile;
	szInput += _T("\"");
	m_pSel->Insert(szInput, EnvDTE::vsInsertFlagsInsertAtStart);
	
	return 0;
}