/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    ProcessView.h
\brief   进程信息视图，这个视图中包括了所有进程信息的子视图。如：CProcessInfoView、CProcessModuleInfo等
\version 1.0.0.1
\author  康  林 (kl222@126.com)
\date    2007年8月21日  9:01:57
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#ifndef __PROCESSVIEW_H_KL_2007_08_24__
#define __PROCESSVIEW_H_KL_2007_08_24__

#pragma once

#include "ProcessInfoView.h"
#include "ProcessModuleInfo.h"
#include "..\NetManageBaseView.h"
#include "ProcessHide.h"
#include "ProcessHideList.h"

// CProcess view

class CProcessView : public CNetManageBaseView
{
	DECLARE_DYNCREATE(CProcessView)

protected:
	CProcessView();           // protected constructor used by dynamic creation
	virtual ~CProcessView();

public:
	virtual void OnDraw(CDC * pDC);      // overridden to draw this view
	CNetManageViewDoc * GetDocument() const;

#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	DECLARE_MESSAGE_MAP()

	virtual int ProcessCommand(CCommand & cmd);

private:
	CBCGPTabWnd m_tabWnd;

public:
	CProcessInfoView m_ProcessInfo;
	CProcessModuleInfo m_ProcessModuleInfo;
	CProcessHide m_ProcessHide;
	CProcessHideList m_ProcessHideList;

	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnInitialUpdate();

protected:
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
};

#ifndef _DEBUG  // debug version in NetManageViewView.cpp
inline CNetManageViewDoc * CProcessView::GetDocument()const
{ return reinterpret_cast<CNetManageViewDoc*>(m_pDocument); }
#endif

#endif //__PROCESSVIEW_H_KL_2007_08_24__