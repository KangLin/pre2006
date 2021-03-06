// SpeechPromptDlg.cpp : implementation file
//

#include "stdafx.h"
#include "SpeechPrompt.h"
#include "SpeechPromptDlg.h"

#include <sapi.h>

#pragma comment(lib,"ole32.lib")  //CoInitialize CoCreateInstance需要调用ole32.dll
#pragma comment(lib,"sapi.lib")   //sapi.lib在SDK的lib目录,必需正确配置


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
// CSpeechPromptDlg dialog

CSpeechPromptDlg::CSpeechPromptDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSpeechPromptDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpeechPromptDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSpeechPromptDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpeechPromptDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CSpeechPromptDlg, CDialog)
	//{{AFX_MSG_MAP(CSpeechPromptDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONINSTALLHOOK, OnButtoninstallhook)
	ON_BN_CLICKED(IDC_BUTTONUNINSTALLHOOK, OnButtonuninstallhook)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpeechPromptDlg message handlers

BOOL CSpeechPromptDlg::OnInitDialog()
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
	m_hDll = NULL;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CSpeechPromptDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CSpeechPromptDlg::OnPaint() 
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
HCURSOR CSpeechPromptDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CSpeechPromptDlg::OnButtoninstallhook() 
{ 
	if(m_hDll)
		return ;
	m_hDll = ::LoadLibrary(_T("SoundPrompt.dll"));
	if(m_hDll == NULL)
		return;
	FARPROC InstallHook = NULL;
	InstallHook = ::GetProcAddress(m_hDll, "InstallHook");
	if(InstallHook)
		InstallHook();
}

void CSpeechPromptDlg::OnButtonuninstallhook() 
{
	if(m_hDll == NULL)
		return;
	FARPROC UninstallHook = NULL;
	UninstallHook = ::GetProcAddress(m_hDll, "UnInstallHook");
	if(UninstallHook)
		UninstallHook();
	::FreeLibrary(m_hDll);
	m_hDll = NULL;

}

void CSpeechPromptDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	OnButtonuninstallhook();	
}

void CSpeechPromptDlg::OnButton1() 
{
	
	ISpVoice * pVoice = NULL;

//COM初始化：
	if (FAILED(::CoInitialize(NULL)))
		return  ;

//获取ISpVoice接口：
	HRESULT hr = CoCreateInstance(CLSID_SpVoice, NULL, CLSCTX_ALL, IID_ISpVoice, (void **)&pVoice);
	if( SUCCEEDED( hr ) )
	{
		hr = pVoice->Speak(L"Hello world", 0, NULL);
		pVoice->Release();
		pVoice = NULL;
	}

//千万不要忘记：
	::CoUninitialize(); 	
	return ;

}
