// StringDLL.h : StringDLL DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ������


// CStringDLLApp
// �йش���ʵ�ֵ���Ϣ������� StringDLL.cpp
//

class CStringDLLApp : public CWinApp
{
public:
	CStringDLLApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
