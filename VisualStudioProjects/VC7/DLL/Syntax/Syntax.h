/*******************************************************************************************************
�ļ�����Syntax.h : Syntax DLL ����ͷ�ļ�
��  �ܣ�C ���Դ����ʽ��
��  ����1.0.0.1
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
E_Mail��kl222@126.com
��  �ڣ�2005-5-5
ʱ  �䣺7:50:23
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10

FileName��Syntax.h
Function��Format C/C++ Code.
Version ��1.0.0.1
Author  ��KangLin
          Copyright 2005 KangLin
E_Mail  ��kl222@126.com
Date    ��2005-5-5
Time    ��7:50:24
Compiler��Microsoft Development Environment 7.10 ���� C/C++ 7.10
*******************************************************************************************************/

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif
#include <comdef.h>
#include "resource.h" // ������
#include "CSyntax.h"
#include "Dialog.h"

// CSyntaxApp
// �йش���ʵ�ֵ���Ϣ������� Syntax.cpp
//

class CSyntaxApp : public CWinApp
{
public:
	CSyntaxApp();
	~CSyntaxApp()
	{
		TRACE(_T("%s(%d) : ~CSyntaxApp �˳���\n"), __FILE__, __LINE__);
	}

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};