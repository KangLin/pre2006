// TestSoftWare.h : TestSoftWare Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CTestSoftWareApp:
// �йش����ʵ�֣������ TestSoftWare.cpp
//

class CTestSoftWareApp : public CWinApp
{
public:
	CTestSoftWareApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTestSoftWareApp theApp;
