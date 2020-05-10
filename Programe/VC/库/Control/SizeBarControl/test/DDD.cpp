// DDD.cpp : implementation file
//

#include "stdafx.h"
#include "test.h"
#include "DDD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDDD dialog


CDDD::CDDD(CWnd* pParent /*=NULL*/)
	: CDialog(CDDD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDDD)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDDD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDDD)
	DDX_Control(pDX, IDOK, m_ok);
	DDX_Control(pDX, IDCANCEL, m_cancel);
	DDX_Control(pDX, IDC_BUTTON1, m_button);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDDD, CDialog)
	//{{AFX_MSG_MAP(CDDD)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDDD message handlers

void CDDD::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	CRect rect;
	if(m_button.GetSafeHwnd())
	{
		m_button.GetWindowRect(&rect);
		int w = rect.right - rect.left;
		int h = rect.bottom - rect.top;
		rect.top = cy / 2;
		rect.left = cx / 2;
		rect.bottom = rect.top + h;
		rect.right = rect.left + w;
		m_button.MoveWindow(&rect);
	}
}
