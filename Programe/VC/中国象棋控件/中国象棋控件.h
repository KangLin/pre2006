/*******************************************************************************************************
�ļ������й�����ؼ�.h
��  �ܣ�
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2005-3-23
ʱ  �䣺12:04:41

FileName���й�����ؼ�.h
Compiler��Visual C++ 6.0
Author  ��KangLin
          Copyright 2005 KangLin
Date    ��2005-3-23
Time    ��12:04:41
*******************************************************************************************************/
#if !defined(AFX__H__189BDB7C_0B14_4E63_AD7E_5315730A8031__INCLUDED_)
#define AFX__H__189BDB7C_0B14_4E63_AD7E_5315730A8031__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// �й�����ؼ�.h : main header file for �й�����ؼ�.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CMyApp : See �й�����ؼ�.cpp for implementation.

class CMyApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX__H__189BDB7C_0B14_4E63_AD7E_5315730A8031__INCLUDED)
