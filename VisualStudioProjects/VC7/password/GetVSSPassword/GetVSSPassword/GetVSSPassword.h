// GetVSSPassword.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CGetVSSPasswordApp:
// �йش����ʵ�֣������ GetVSSPassword.cpp
//

class CGetVSSPasswordApp : public CWinApp
{
public:
	CGetVSSPasswordApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CGetVSSPasswordApp theApp;