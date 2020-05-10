/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    ProcessModuleInfo.h
\brief   ��ϸ����
\version 1.0.0.1
\author  ��  �� (kl222@126.com)
\date    2007��8��23��  22:53:32
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/

#pragma once

#include "..\..\plus\Process\ProcessCommand.h"

// CProcessModuleInfo

class CProcessModuleInfo : public CWnd
{
	DECLARE_DYNAMIC(CProcessModuleInfo)

public:
	CProcessModuleInfo();
	virtual ~CProcessModuleInfo();

	CComboBox m_ComboBox;
	CBCGPListCtrl m_lstModule;

protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSelectChange();

	int OnInitialUpdate(CNetManageViewDoc * pDocument);
	virtual int ProcessCommand(CCommand & cmd);


private:
	CNetManageViewDoc * m_pDocument;
	vector<CProcessInformation::PROCESS_MODULE_INFO> m_Info;

	
};


