// ASCToChar.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CASCToCharApp:
// �йش����ʵ�֣������ ASCToChar.cpp
//

class CASCToCharApp : public CWinApp
{
public:
	CASCToCharApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CASCToCharApp theApp;