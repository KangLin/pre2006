// PasswordManage.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CPasswordManageApp:
// �йش����ʵ�֣������ PasswordManage.cpp
//

class CPasswordManageApp : public CWinApp
{
public:
	CPasswordManageApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CPasswordManageApp theApp;