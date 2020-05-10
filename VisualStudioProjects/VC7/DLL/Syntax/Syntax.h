/*******************************************************************************************************
文件名：Syntax.h : Syntax DLL 的主头文件
功  能：C 语言代码格式化
版  本：1.0.0.1
作  者：康  林
        版权所有  保留所有权利
E_Mail：kl222@126.com
日  期：2005-5-5
时  间：7:50:23
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10

FileName：Syntax.h
Function：Format C/C++ Code.
Version ：1.0.0.1
Author  ：KangLin
          Copyright 2005 KangLin
E_Mail  ：kl222@126.com
Date    ：2005-5-5
Time    ：7:50:24
Compiler：Microsoft Development Environment 7.10 —— C/C++ 7.10
*******************************************************************************************************/

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif
#include <comdef.h>
#include "resource.h" // 主符号
#include "CSyntax.h"
#include "Dialog.h"

// CSyntaxApp
// 有关此类实现的信息，请参阅 Syntax.cpp
//

class CSyntaxApp : public CWinApp
{
public:
	CSyntaxApp();
	~CSyntaxApp()
	{
		TRACE(_T("%s(%d) : ~CSyntaxApp 退出。\n"), __FILE__, __LINE__);
	}

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};