/*******************************************************************************************************
��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
�ļ�����OtherTools.h
��  ������������
�����б�
        GetRelativePath
��  ����1.0.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2005��7��30��
ʱ  �䣺16:48:36
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10
*******************************************************************************************************/
#pragma once
#include "stdafx.h"

class COtherTools
{
public:
	COtherTools(void);
	~COtherTools(void);

	BOOL GetRelativePath(void);
	
private:
	CComPtr < EnvDTE::_DTE > m_pDTE;
    CComPtr < EnvDTE::TextSelection > m_pSel;
	CComPtr < EnvDTE::Document > m_pDoc;
	
public:
	BOOL Inital(EnvDTE::_DTE * pDTE);
	BOOL GetDocument(void);
	BOOL GetSelection(void);
};
