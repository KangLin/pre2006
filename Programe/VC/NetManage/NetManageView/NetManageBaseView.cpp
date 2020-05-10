// NetManageBaseView.cpp : implementation file
//

#include "stdafx.h"
#include "NetManageView.h"
#include "NetManageBaseView.h"


#ifdef _DEBUG
#ifdef DEBUG_NEW
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

// CNetManageBaseView

IMPLEMENT_DYNCREATE(CNetManageBaseView, CView)

CNetManageBaseView::CNetManageBaseView()
{

}

CNetManageBaseView::~CNetManageBaseView()
{
}

BEGIN_MESSAGE_MAP(CNetManageBaseView, CView)
END_MESSAGE_MAP()


// CNetManageBaseView drawing

void CNetManageBaseView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CNetManageBaseView diagnostics

#ifdef _DEBUG
void CNetManageBaseView::AssertValid() const
{
	CView::AssertValid();
}

#ifndef _WIN32_WCE
void CNetManageBaseView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}
#endif

CNetManageViewDoc* CNetManageBaseView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNetManageViewDoc)));
	return (CNetManageViewDoc*)m_pDocument;
}
#endif //_DEBUG





// CNetManageBaseView message handlers
int CNetManageBaseView::ProcessCommand(CCommand & cmd)
{
	int nRet = S_OK;

	TRACE(_T("派生类一定要实现此函数\n"));
	ASSERT(FALSE);

	return nRet;
}
