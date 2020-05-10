// VideoConnectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\ÖÐ¹úÏóÆå.h"
#include "VideoConnectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVideoConnectDlg dialog


CVideoConnectDlg::CVideoConnectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CVideoConnectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVideoConnectDlg)
	m_szUserName = _T("");
	//}}AFX_DATA_INIT
}


void CVideoConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVideoConnectDlg)
	DDX_Control(pDX, IDC_EDITVIDEOCONNECTUSERNAME, m_ctrUserName);
	DDX_Text(pDX, IDC_EDITVIDEOCONNECTUSERNAME, m_szUserName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVideoConnectDlg, CDialog)
	//{{AFX_MSG_MAP(CVideoConnectDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideoConnectDlg message handlers
