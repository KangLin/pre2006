/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：CLanguage.h
描  述：C 语言工具
版  本：1.0.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2005年7月30日
时  间：16:48:54
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10
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
