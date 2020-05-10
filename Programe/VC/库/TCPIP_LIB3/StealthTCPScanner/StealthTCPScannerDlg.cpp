// StealthTCPScannerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "StealthTCPScanner.h"
#include "StealthTCPScannerDlg.h"

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
// CStealthTCPScannerDlg dialog

CStealthTCPScannerDlg::CStealthTCPScannerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CStealthTCPScannerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CStealthTCPScannerDlg)
	m_URL = _T("");
	m_ScanDelay = 20;
	m_EndPort = 0;
	m_AutoScroll = TRUE;
	m_StartPort = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStealthTCPScannerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CStealthTCPScannerDlg)
	DDX_Control(pDX, IDC_TCPLIST, m_TCPList);
	DDX_Control(pDX, IDC_DESTINATIONIP, m_DestinationIP);
	DDX_Control(pDX, IDC_INTERFACELIST, m_InterfaceList);
	DDX_Text(pDX, IDC_ADDRESS, m_URL);
	DDX_Text(pDX, IDC_DELAY, m_ScanDelay);
	DDV_MinMaxLong(pDX, m_ScanDelay, 0, 1000);
	DDX_Text(pDX, IDC_ENDPORT, m_EndPort);
	DDV_MinMaxLong(pDX, m_EndPort, 0, 65535);
	DDX_Check(pDX, IDC_SCROLL, m_AutoScroll);
	DDX_Text(pDX, IDC_STARTPORT, m_StartPort);
	DDV_MinMaxLong(pDX, m_StartPort, 0, 65535);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CStealthTCPScannerDlg, CDialog)
	//{{AFX_MSG_MAP(CStealthTCPScannerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_SCAN, OnScan)
	ON_BN_CLICKED(IDC_QUIT, OnQuit)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CStealthTCPScannerDlg message handlers

BOOL CStealthTCPScannerDlg::OnInitDialog()
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
	
	m_Socket=new CClientSocket(&m_TCPList,m_AutoScroll);

	if (!((CSpoofSocket*)m_Socket)->InitializeSockets())
	{
		delete m_Socket;
		return FALSE;
	}

	//Build socket list
	return BuildInterfaceList();  // return TRUE  unless you set the focus to a control
}

void CStealthTCPScannerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CStealthTCPScannerDlg::OnPaint() 
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
HCURSOR CStealthTCPScannerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CStealthTCPScannerDlg::BuildInterfaceList()
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
			//Only if not a loopback interface
			if (!pInter->IsLoopback())
			{
				//Get the interface
				LPSTR lpInterface;
				lpInterface=pInter->LongToString(pInter->GetAddress());

				//Add it to the list
				m_InterfaceList.AddString(lpInterface);
			}

			//Get next interface
			bQuit=!pInter->MoveNext();
		}

		delete pInter;
		return TRUE;
	}

	delete pInter;
	return FALSE;
}

void CStealthTCPScannerDlg::OnScan() 
{
	if (UpdateData(TRUE))
		if (m_InterfaceList.GetCurSel()!=LB_ERR)
			Scan();
		else
			MessageBox("Please choose an interface!","Error",MB_OK);
}

BOOL CStealthTCPScannerDlg::Scan()
{
	if (!ConvertAddress())
		return FALSE;

	if (!CreateSocket())
		return FALSE;
	
	//Bind the socket
	CString strBind;
	m_InterfaceList.GetText(m_InterfaceList.GetCurSel(),strBind);

	//Request a scan from the socket
	m_Socket->Scan(strBind.GetBuffer(0),IPCtrlToSTR(&m_DestinationIP),m_StartPort,m_EndPort,m_ScanDelay);

	return TRUE;
}

BOOL CStealthTCPScannerDlg::ConvertAddress()
{
	if (m_URL=="")
		return TRUE;

	long lAddr;

	lAddr=m_Socket->ResolveDNS(m_URL);

	if (lAddr)
	{
		//Correct
		m_DestinationIP.SetAddress(htonl(lAddr));

		//Clear the address
		m_URL="";
	}
	else
		//Display error
		MessageBox("Couldn't resolve host name","Error",MB_OK);

	return lAddr;
}

LPSTR CStealthTCPScannerDlg::IPCtrlToSTR(CIPAddressCtrl* ctrl)
{
	//Converts the control address to textual address
	//Convert bytes to string
	BYTE bOctet1;
	BYTE bOctet2;
	BYTE bOctet3;
	BYTE bOctet4;

	//Get the value and blank values
	int iBlank;
	iBlank=ctrl->GetAddress(bOctet1,bOctet2,bOctet3,bOctet4);

	if (iBlank!=4)
		//Not filled
		return NULL;
	else
	{
		in_addr iAddr;
		iAddr.S_un.S_un_b.s_b1=bOctet1;
		iAddr.S_un.S_un_b.s_b2=bOctet2;
		iAddr.S_un.S_un_b.s_b3=bOctet3;
		iAddr.S_un.S_un_b.s_b4=bOctet4;

		return inet_ntoa(iAddr);
	}
}

void CStealthTCPScannerDlg::OnQuit() 
{
	//Quit
	EndDialog(0);
}

BOOL CStealthTCPScannerDlg::CreateSocket()
{
	//Delete the old socket
	delete m_Socket;

	//Recreate
	m_Socket=new CClientSocket(&m_TCPList,m_AutoScroll);
	m_Socket->SetRaw(TRUE);
	return m_Socket->Create();
}

void CStealthTCPScannerDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	//Delete all
	((CSpoofSocket*)m_Socket)->ShutdownSockets();
	
	//No need to delete	
}
