// process\ProcessHide.cpp : implementation file
//

#include "stdafx.h"
#include "..\NetManageView.h"
#include "ProcessHide.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CProcessHide

IMPLEMENT_DYNAMIC(CProcessHide, CWnd)

CProcessHide::CProcessHide()
{

}

CProcessHide::~CProcessHide()
{
}


BEGIN_MESSAGE_MAP(CProcessHide, CWnd)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CProcessHide message handlers


int CProcessHide::ProcessCommand(CCommand & cmd)
{
	int nRet = 0;

	return nRet;
}

int CProcessHide::OnInitialUpdate(CNetManageViewDoc * pDocument)
{
	ASSERT(pDocument);
	m_pDocument = pDocument;
	return S_OK;
}
void CProcessHide::OnPaint()
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
