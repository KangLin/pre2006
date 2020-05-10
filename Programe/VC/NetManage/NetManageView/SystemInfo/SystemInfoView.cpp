// SystemInfo.cpp : implementation file
//

#include "stdafx.h"
#include "..\NetManageView.h"
#include "SystemInfoView.h"


#ifdef _DEBUG
#ifdef DEBUG_NEW
#define new DEBUG_NEW
#endif
#endif

// CSystemInfo

IMPLEMENT_DYNCREATE(CSystemInfoView, CNetManageBaseView)

CSystemInfoView::CSystemInfoView()
{

}

CSystemInfoView::~CSystemInfoView()
{
}

BEGIN_MESSAGE_MAP(CSystemInfoView, CNetManageBaseView)
END_MESSAGE_MAP()


// CSystemInfo drawing

void CSystemInfoView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CSystemInfo diagnostics

#ifdef _DEBUG
void CSystemInfoView::AssertValid() const
{
	CNetManageBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CSystemInfoView::Dump(CDumpContext& dc) const
{
	CNetManageBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CSystemInfo message handlers
int CSystemInfoView::ProcessCommand(CCommand & cmd)
{
	int nRet = S_OK;

	return nRet;
}