// process\ProcessHideList.cpp : implementation file
//

#include "stdafx.h"
#include "..\NetManageView.h"
#include "ProcessHideList.h"


// CProcessHideList

IMPLEMENT_DYNAMIC(CProcessHideList, CWnd)

CProcessHideList::CProcessHideList()
{

}

CProcessHideList::~CProcessHideList()
{
}


BEGIN_MESSAGE_MAP(CProcessHideList, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CProcessHideList message handlers


int CProcessHideList::ProcessCommand(CCommand & cmd)
{
	int nRet = 0;

	return nRet;
}

int CProcessHideList::OnInitialUpdate(CNetManageViewDoc * pDocument)
{
	ASSERT(pDocument);
	m_pDocument = pDocument;
	return S_OK;
}

void CProcessHideList::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CWnd::OnPaint() for painting messages
	TRACE(_T("CProcessHide::OnPaint\n"));
	CPen pen(PS_SOLID, 0, RGB(255, 255, 255));
	CPen * pOldPen = dc.SelectObject(&pen);
	CRect rect;
	GetClientRect(&rect);
	dc.Rectangle(&rect);
	dc.SelectObject(pOldPen);
}