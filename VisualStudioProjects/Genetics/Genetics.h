// Genetics.h : Genetics Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CGeneticsApp:
// �йش����ʵ�֣������ Genetics.cpp
//

class CGeneticsApp : public CWinApp
{
public:
	CGeneticsApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CGeneticsApp theApp;
