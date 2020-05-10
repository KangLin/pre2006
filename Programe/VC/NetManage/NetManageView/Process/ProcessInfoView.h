/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    ProcessInfoView.h
\brief   所有进程信息的窗口，在这个窗口里描述了所有进程信息。
\version 1.0.0.1
\author  康  林 (kl222@126.com)
\date    2007年8月21日  9:03:32
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#ifndef __PROCESSINFOVIEW_H_KL_2007_08_24__
#define __PROCESSINFOVIEW_H_KL_2007_08_24__

#pragma once


// CProcessInfoView

class CProcessInfoView : public CWnd
{
	DECLARE_DYNAMIC(CProcessInfoView)

public:
	CProcessInfoView();
	virtual ~CProcessInfoView();

protected:
	DECLARE_MESSAGE_MAP()

public:
	CBCGPListCtrl m_lstProcess;

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	int OnInitialUpdate(CNetManageViewDoc * pDocument);

	virtual int ProcessCommand(CCommand & cmd);

private:
	CNetManageViewDoc * m_pDocument; //当前文档
};

#endif //__PROCESSINFOVIEW_H_KL_2007_08_24__
