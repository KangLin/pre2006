// TiShiTest.h : TiShiTest Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h�� 
#endif

#include "resource.h"       // ������


// CTiShiTestApp:
// �йش����ʵ�֣������ TiShiTest.cpp
//

class CTiShiTestApp : public CWinApp
{
public:
	CTiShiTestApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTiShiTestApp theApp;
