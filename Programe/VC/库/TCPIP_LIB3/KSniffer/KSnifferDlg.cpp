// KSnifferDlg.cpp : implementation file
//

#include "stdafx.h"
#include "KSniffer.h"
#include "KSnifferDlg.h"
#include "ClientSocket.h"

#include "..\Interfaces.h"

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
// CKSnifferDlg dialog

CKSnifferDlg::CKSnifferDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CKSnifferDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CKSnifferDlg)
	m_Sniff = FALSE;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CKSnifferDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CKSnifferDlg)
	DDX_Control(pDX, IDC_DATALIST, m_DataList);
	DDX_Control(pDX, IDC_INTERFACELIST, m_InterfaceList);
	DDX_Check(pDX, IDC_SNIFFCHECK, m_Sniff);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CKSnifferDlg, CDialog)
	//{{AFX_MSG_MAP(CKSnifferDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	ON_BN_CLICKED(ID_SNIFF, OnSniff)
	ON_BN_CLICKED(IDC_SNIFFCHECK, OnSniffcheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CKSnifferDlg message handlers

BOOL CKSnifferDlg::OnInitDialog()
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
	
	//Initialize the socket
	m_Socket=new CClientSocket(&m_DataList);

	if (((CSpoofSocket*)m_Socket)->InitializeSockets())
	{
		m_Socket->SetRaw(TRUE);
		m_Socket->Create();
	}
	else
	{
		delete m_Socket;
		return FALSE;
	}

	//Build socket list
	return BuildInterfaceList(); // return TRUE  unless you set the focus to a control
}

void CKSnifferDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CKSnifferDlg::OnPaint() 
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
HCURSOR CKSnifferDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CKSnifferDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	//Delete all
	((CSpoofSocket*)m_Socket)->ShutdownSockets();
	
	//No need to delete
}

BOOL CKSnifferDlg::BuildInterfaceList()
{
	//Get the list of interfaces
	CInterfaces* pInter;
	pInter=new CInterfaces;

	//Only if we have the interfaces
	if (pInter->GetInterfaces())
	{
		//Build the list
		BOOL bQuit;
		bQuit=FALSE;

		while (!bQuit)
		{
			//Get the interface
			LPSTR lpInterface;
			lpInterface=pInter->LongToString(pInter->GetAddress());

			//Add it to the list
			m_InterfaceList.AddString(lpInterface);

			//Get next interface
			bQuit=!pInter->MoveNext();
		}

		delete pInter;
		return TRUE;
	}

	delete pInter;
	return FALSE;
}

void CKSnifferDlg::OnSniff() 
{
	CString strInterface;
	m_InterfaceList.GetText(m_InterfaceList.GetCurSel(),strInterface);

	//Get the string
	//Bind to an interface
	if (m_Socket->Bind(strInterface))
		//Sniff
		m_Socket->Sniff(TRUE);
}

void CKSnifferDlg::OnSniffcheck() 
{
	UpdateData(TRUE);
	m_Socket->CaptureOutgoing(m_Sniff);
}
