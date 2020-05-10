// MemoryView.cpp : implementation file
//

#include "stdafx.h"
#include "NetManageView.h"
#include "MemoryView.h"

#ifdef _DEBUG
#ifdef DEBUG_NEW
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

// CMemoryView

IMPLEMENT_DYNCREATE(CMemoryView, CNetManageBaseView)

CMemoryView::CMemoryView()
{

}

CMemoryView::~CMemoryView()
{
}

BEGIN_MESSAGE_MAP(CMemoryView, CNetManageBaseView)
END_MESSAGE_MAP()


// CMemoryView drawing

void CMemoryView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CMemoryView diagnostics

#ifdef _DEBUG
void CMemoryView::AssertValid() const
{
	CNetManageBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CMemoryView::Dump(CDumpContext& dc) const
{
	CNetManageBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CMemoryView message handlers
int CMemoryView::ProcessCommand(CCommand & cmd)
{
	int nRet = S_OK;

	return nRet;
}
