/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：OtherTools.h
描  述：其它工具
函数列表：
        GetRelativePath
版  本：1.0.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2005年7月30日
时  间：16:48:36
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10
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
