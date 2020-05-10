// WinsocketexpDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Winsocketexp.h"
#include "WinsocketexpDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinsocketexpDlg dialog

CWinsocketexpDlg::CWinsocketexpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWinsocketexpDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWinsocketexpDlg)
	m_szSend = _T("");
	m_szLocatIP = _T("127.0.0.1");
	m_szRemoteIP = _T("127.0.0.1");
	m_nRemotePort = 2000;
	m_nLocatePort = 2000;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CWinsocketexpDlg::DoDataExchange(CDataExchange* pDX)
{
	TRACE(_T("DoDataExchange.\n"));
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWinsocketexpDlg)
	DDX_Control(pDX, IDC_LIST_SEND, m_ctrListSend);
	DDX_Control(pDX, IDC_EDITSEND, m_ctrSend);
	DDX_Control(pDX, IDC_LIST1, m_ctrLstRecive);
	DDX_Text(pDX, IDC_EDITSEND, m_szSend);
	DDX_Text(pDX, IDC_EDITLOCATEIP, m_szLocatIP);
	DDX_Text(pDX, IDC_EDITREMOTIP, m_szRemoteIP);
	DDX_Text(pDX, IDC_EDITREMOTPORT, m_nRemotePort);
	DDX_Text(pDX, IDC_EDITLOCATPORT, m_nLocatePort);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWinsocketexpDlg, CDialog)
	//{{AFX_MSG_MAP(CWinsocketexpDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONSEND, OnButtonsend)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTONCONNECT, OnButtonconnect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWinsocketexpDlg message handlers

BOOL CWinsocketexpDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWinsocketexpDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CWinsocketexpDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CWinsocketexpDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWinsocketexpDlg::OnButtonconnect() 
{
	m_udpSocket.Close();
	this->UpdateData();
	m_udpSocket.Inital(this, NULL, m_nLocatePort);
}

void CWinsocketexpDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	m_udpSocket.Close();
	TRACE(_T("关闭udpSocket\n"));
}

void CWinsocketexpDlg::OnButtonsend() 
{
	char sztmp[1024];
	this->UpdateData();
	//m_udpSocket.SendTo((LPVOID)(LPCSTR)m_szSend, m_szSend.GetLength() + 1, m_nRemotePort, m_szRemoteIP);
	m_udpSocket.SendDataTo((LPVOID)(LPCSTR)m_szSend, m_szSend.GetLength() + 1, m_nRemotePort, m_szRemoteIP);
	sprintf(sztmp, _T("%s:%d >> %s"), m_szRemoteIP, m_nRemotePort,m_szSend);
	m_ctrListSend.AddString(sztmp);
    m_ctrSend.SetWindowText("");
	TRACE(_T("CWinSocketexDlg::OnButtonsend的当前线程ID:%x\n"), GetCurrentThreadId());
	
}

