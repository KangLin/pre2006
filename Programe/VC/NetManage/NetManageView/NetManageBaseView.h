#pragma once

#include "..\Commonality\command.h"
#include ".\NetManageViewDoc.h"

// CNetManageBaseView view

class CNetManageBaseView : public CView
{
	DECLARE_DYNCREATE(CNetManageBaseView)

protected:
	CNetManageBaseView();           // protected constructor used by dynamic creation
	virtual ~CNetManageBaseView();

public:
	CNetManageViewDoc * GetDocument() const;

	virtual void OnDraw(CDC* pDC);      // overridden to draw this view
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

	//派生类中一定要实现这个虚拟函数
	virtual int ProcessCommand(CCommand & cmd);

protected:
	DECLARE_MESSAGE_MAP()
};


#ifndef _DEBUG  // debug version in NetManageViewView.cpp
inline CNetManageViewDoc* CNetManageBaseView::GetDocument() const
{ return reinterpret_cast<CNetManageViewDoc*>(m_pDocument); }
#endif