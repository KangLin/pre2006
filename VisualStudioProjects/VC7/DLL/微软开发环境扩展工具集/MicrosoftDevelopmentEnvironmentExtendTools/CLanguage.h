/*******************************************************************************************************
��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
�ļ�����CLanguage.h
��  ����C ���Թ���
��  ����1.0.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2005��7��30��
ʱ  �䣺16:48:54
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10
*******************************************************************************************************/
#pragma once

class CCLanguage
{
public:
	CCLanguage(void);
	~CCLanguage(void);

private:
	CComPtr < EnvDTE::_DTE > m_pDTE;
    CComPtr < EnvDTE::TextSelection > m_pSel;
	CComPtr < EnvDTE::Document > m_pDoc;
	
public:
	BOOL GetDocument(void);
	BOOL GetSelection(void);
	BOOL Inital(EnvDTE::_DTE * pDTE);
	BOOL SwitchCPPToH(void);
	BOOL IncludeFile(void);
};
