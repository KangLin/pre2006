// MicrosoftDevelopmentEnvironmentExtendToolsSerialNo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error �ڰ������� PCH �Ĵ��ļ�֮ǰ������stdafx.h��
#endif

#include "resource.h"		// ������


// CMicrosoftDevelopmentEnvironmentExtendToolsSerialNoApp:
// �йش����ʵ�֣������ MicrosoftDevelopmentEnvironmentExtendToolsSerialNo.cpp
//

class CMicrosoftDevelopmentEnvironmentExtendToolsSerialNoApp : public CWinApp
{
public:
	CMicrosoftDevelopmentEnvironmentExtendToolsSerialNoApp();

// ��д
	public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMicrosoftDevelopmentEnvironmentExtendToolsSerialNoApp theApp;
