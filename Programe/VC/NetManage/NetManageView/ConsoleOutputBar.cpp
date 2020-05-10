// outputbar.cpp : implementation of the COutputBar class
//

#include "stdafx.h"
#include "NetManageView.h"
#include "consoleoutputbar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

const int nBorderSize = 1;
/////////////////////////////////////////////////////////////////////////////
// COutputBar

BEGIN_MESSAGE_MAP(CConsoleOutputBar, CBCGPDockingControlBar)
	//{{AFX_MSG_MAP(COutputBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COutputBar construction/destruction

CConsoleOutputBar::CConsoleOutputBar()
{
	// TODO: add one-time construction code here
}

CConsoleOutputBar::~CConsoleOutputBar()
{
}

/////////////////////////////////////////////////////////////////////////////
// COutputBar message handlers

int CConsoleOutputBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CBCGPDockingControlBar::OnCreate(lpCreateStruct) == -1)
		return -1;

	SetFont(this->GetParent()->GetFont());
	CDC * pDC = GetDC();
	pDC->SelectObject(this->GetParent()->GetFont());

	CRect rectDummy;
	rectDummy.SetRectEmpty ();

	if(!m_Cmd.CreateEx(NULL, NULL, NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL, CRect(0, 0, 0, 0), this, NULL))
	{
		TRACE(_T("Failed to create console output view\n"));
		return - 1;
	} // ½áÊø if(!m_Cmd.CreateEx(NULL, NULL, NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL, CRect(0, 0, 0, 0), this, NULL))
	
	return 0;
}

void CConsoleOutputBar::OnSize(UINT nType, int cx, int cy) 
{
	CBCGPDockingControlBar::OnSize(nType, cx, cy);

	m_Cmd.SetWindowPos(NULL, nBorderSize, nBorderSize,
		cx - 2 * nBorderSize, cy - 2 * nBorderSize,
		SWP_NOACTIVATE | SWP_NOZORDER);
}

void CConsoleOutputBar::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CRect rectList;
	m_Cmd.GetWindowRect(rectList);
	ScreenToClient (rectList);

	rectList.InflateRect (1, 1);
	dc.Draw3dRect (rectList,	::GetSysColor (COLOR_3DSHADOW), 
		::GetSysColor (COLOR_3DSHADOW));
}

BOOL CConsoleOutputBar::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN || pMsg->message == WM_CHAR || pMsg->message == WM_KEYUP)
	{
		m_Cmd.SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
	}// ½áÊø if(pMsg->message == WM_KEYDOWN || pMsg->message == WM_CHAR || pMsg->message == WM_UP)

	return CBCGPDockingControlBar::PreTranslateMessage(pMsg);
}
