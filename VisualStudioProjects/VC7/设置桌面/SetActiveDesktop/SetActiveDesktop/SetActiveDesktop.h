// SetActiveDesktop.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSetActiveDesktopApp:
// �йش����ʵ�֣������ SetActiveDesktop.cpp
//

class CSetActiveDesktopApp : public CWinApp
{
public:
	CSetActiveDesktopApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSetActiveDesktopApp theApp;