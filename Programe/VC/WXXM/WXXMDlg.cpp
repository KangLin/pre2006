// WXXMDlg.cpp : implementation file
//

#include "stdafx.h"
#include "WXXM.h"
#include "WXXMDlg.h"

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
// CWXXMDlg dialog
IMPLEMENT_DYNAMIC(CWXXMDlg, CDialog)

CWXXMDlg::CWXXMDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CWXXMDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWXXMDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
    m_hKeyPromptDll = NULL;
}

void CWXXMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWXXMDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CWXXMDlg, CDialog)
	//{{AFX_MSG_MAP(CWXXMDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDM_ABOUT, OnAbout)
	ON_COMMAND(IDM_EXIT, OnExit)
	ON_WM_CREATE()
	ON_WM_CLOSE()
	ON_COMMAND(IDM_OPEN, OnOpen)
	ON_COMMAND(IDM_KEYPROMPT, OnKeyprompt)
	ON_MESSAGE(IDM_TRAYICON, OnTrayNotifiy)
	ON_UPDATE_COMMAND_UI(IDM_KEYPROMPT, OnUpdateKeyprompt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWXXMDlg message handlers

BOOL CWXXMDlg::OnInitDialog()
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

    StartKeyPrompt();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CWXXMDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CWXXMDlg::OnPaint() 
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
HCURSOR CWXXMDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CWXXMDlg::OnAbout() 
{
	CAboutDlg ad;
	ad.DoModal();
}

void CWXXMDlg::OnExit() 
{
	m_bRun = FALSE;
	SendMessage(WM_CLOSE);
}

int CWXXMDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_bRun = TRUE;
	m_pTrayIcon = new CTrayIcon(IDM_TRAYICON);
	m_pTrayIcon->SetNotificationWnd(this, IDM_TRAYICON);
	m_pTrayIcon->SetIcon(IDR_MAINFRAME);
    
	return 0;
}

LRESULT CWXXMDlg::OnTrayNotifiy(WPARAM wID, LPARAM lEvent)
{
	return m_pTrayIcon->OnTrayNotifiy(wID, lEvent);
}

void CWXXMDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bRun)
	{
		ShowWindow(SW_HIDE);
		return;
	}

    StopKeyPrompt();
    m_pTrayIcon->SetIcon(NULL);
   	CDialog::OnClose();
}

void CWXXMDlg::OnOpen() 
{
	ShowWindow(SW_NORMAL);
	this->SetForegroundWindow();
}

void CWXXMDlg::OnKeyprompt() 
{
	if(m_hKeyPromptDll)
		StopKeyPrompt();
	else
		StartKeyPrompt();
}

BOOL CWXXMDlg::StartKeyPrompt()
{
	FARPROC start;
	if(m_hKeyPromptDll != NULL)
		return FALSE;
	m_hKeyPromptDll = ::LoadLibrary("soundprompt.dll");
	if(m_hKeyPromptDll == NULL)
    {
        TRACE(_T("%s(%d) : ���ؿ� SoundPrompt ʧ�ܡ�\n"), __FILE__, __LINE__);
        return FALSE;
    } // ���� if(m_hKeyPromptDll == NULL)
		
	start = ::GetProcAddress(m_hKeyPromptDll, "InstallHook");
    if(start == NULL)
    {
        TRACE(_T("%s(%d) : ���뺯�� InstallHook ʧ�ܡ�\n"), __FILE__, __LINE__);
        return FALSE;
    } // ���� if(start == NULL)
	start();
	return TRUE;
}				

BOOL CWXXMDlg::StopKeyPrompt()
{
	FARPROC stop;
	if(m_hKeyPromptDll == NULL)
    {
        return FALSE;
    } // ���� if(m_hKeyPromptDll == NULL)
		
	stop = ::GetProcAddress(m_hKeyPromptDll, "UnInstallHook");
	stop();
	::FreeLibrary(m_hKeyPromptDll);
	m_hKeyPromptDll = NULL;
	return TRUE;
}

void CWXXMDlg::OnUpdateKeyprompt(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck();
	//pCmdUI->SetCheck((m_hKeyPromptDll) ? 0 : 1);
}
