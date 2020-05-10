// ProcessModuleInfoView.cpp : implementation file
//

#include "stdafx.h"
#include "NetManageView.h"
#include "ProcessModuleInfoView.h"


// CProcessModuleInfoView

IMPLEMENT_DYNCREATE(CProcessModuleInfoView, CView)

CProcessModuleInfoView::CProcessModuleInfoView()
{

}

CProcessModuleInfoView::~CProcessModuleInfoView()
{
}

BEGIN_MESSAGE_MAP(CProcessModuleInfoView, CView)
END_MESSAGE_MAP()


// CProcessModuleInfoView drawing

void CProcessModuleInfoView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CProcessModuleInfoView diagnostics

#ifdef _DEBUG
void CProcessModuleInfoView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CProcessModuleInfoView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif
#endif //_DEBUG


// CProcessModuleInfoView message handlers
