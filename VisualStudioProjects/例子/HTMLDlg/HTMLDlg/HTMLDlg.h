// HTMLDlg.h : HTMLDlg Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CHTMLDlgApp:
// �йش����ʵ�֣������ HTMLDlg.cpp
//

class CHTMLDlgApp : public CWinApp
{
public:
	CHTMLDlgApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CHTMLDlgApp theApp;