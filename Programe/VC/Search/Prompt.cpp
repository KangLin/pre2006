// Prompt.cpp : implementation file
//

#include "stdafx.h"
#include "Search.h"
#include "Prompt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrompt dialog


CPrompt::CPrompt(CWnd* pParent /*=NULL*/)
	: CDialog(CPrompt::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrompt)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPrompt::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrompt)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrompt, CDialog)
	//{{AFX_MSG_MAP(CPrompt)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrompt message handlers
