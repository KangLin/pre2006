// KeyInput.h : KeyInput DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������


// CKeyInputApp
// �йش���ʵ�ֵ���Ϣ������� KeyInput.cpp
//

class CKeyInputApp : public CWinApp
{
public:
	CKeyInputApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
