// UDPScanerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ScanSocket.h"
#include "UDPScaner.h"
#include "UDPScanerDlg.h"

#include "..\UDPSocket.h"

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
// CUDPScanerDlg dialog

CUDPScanerDlg::CUDPScanerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUDPScanerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUDPScanerDlg)
	m_EndPort = 0;
	m_StartPort = 0;
	m_ScanDelay = 20;
	m_AutoScroll = TRUE;
	m_Loop = 5;
	m_URL = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_ICMP=NULL;
	m_UDP=NULL;
}

void CUDPScanerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUDPScanerDlg)
	DDX_Control(pDX, IDC_UDPLIST, m_UDPList);
	DDX_Control(pDX, IDC_DESTINATIONIP, m_DestinationIP);
	DDX_Text(pDX, IDC_ENDPORT, m_EndPort);
	DDV_MinMaxInt(pDX, m_EndPort, 0, 65535);
	DDX_Text(pDX, IDC_STARTPORT, m_StartPort);
	DDV_MinMaxInt(pDX, m_StartPort, 0, 65535);
	DDX_Text(pDX, IDC_DELAY, m_ScanDelay);
	DDV_MinMaxInt(pDX, m_ScanDelay, 0, 1000);
	DDX_Check(pDX, IDC_SCROLL, m_AutoScroll);
	DDX_Text(pDX, IDC_LOOP, m_Loop);
	DDV_MinMaxInt(pDX, m_Loop, 1, 100);
	DDX_Text(pDX, IDC_ADDRESS, m_URL);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUDPScanerDlg, CDialog)
	//{{AFX_MSG_MAP(CUDPScanerDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_QUIT, OnQuit)
	ON_BN_CLICKED(IDC_SCAN, OnScan)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUDPScanerDlg message handlers

BOOL CUDPScanerDlg::OnInitDialog()
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

void CUDPScanerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CUDPScanerDlg::OnPaint() 
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
HCURSOR CUDPScanerDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CUDPScanerDlg::OnQuit() 
{
	//Quit
	EndDialog(0);
}

void CUDPScanerDlg::OnScan() 
{
	//First validate data
	if (UpdateData(TRUE))
		Scan();
}

BOOL CUDPScanerDlg::Scan()
{
	//First if no ICMP create it
	if (!m_ICMP)
	{
		m_ICMP=new CScanSocket(this);
		m_ICMP->SetInstance(AfxGetInstanceHandle());
		m_ICMP->SetRaw(TRUE);
		m_ICMP->Create();

		//Let OS know we are alive
		m_ICMP->SendEcho("127.0.0.1",FALSE,0,0,0);
	}

	//If no UDP create it
	if (!m_UDP)
	{
		m_UDP=new CUDPSocket;
		m_UDP->Create();
	}

	//Check if we have a raw address
	if (!ConvertAddress())
		return FALSE;

	//Convert the address
	char* cTmp;
	cTmp=IPCtrlToSTR(&m_DestinationIP);

	if (!cTmp)
	{
		MessageBox("Invalid address","Error");
		return FALSE;
	}

	memcpy(m_cDestinationIP,cTmp,16);

	m_ICMP->SetDestinationIP(inet_addr(m_cDestinationIP));

	//Add scanning message
	char tmp[40]="Scanning: ";

	strcat(tmp,m_cDestinationIP);
	m_UDPList.AddString(tmp);

	//Update display
	UpdateData(FALSE);

	//Reset list
	m_ICMP->ResetList();

	//Set loop count
	m_LoopCount=m_Loop;

	//Scan 
	return ICMPScan();
}

CUDPScanerDlg::~CUDPScanerDlg()
{
}

void CUDPScanerDlg::OnClose() 
{
	if (m_ICMP)
		delete m_ICMP;

	if (m_UDP)
		delete m_UDP;

	CDialog::OnClose();
}

LPSTR CUDPScanerDlg::IPCtrlToSTR(CIPAddressCtrl* ctrl)
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

void CUDPScanerDlg::Report()
{
	if (!m_LoopCount)
	{
		for (int iCount=m_StartPort;iCount<=m_EndPort;iCount++)
			if (!m_ICMP->GetBit(iCount))
			{
				//Convert it to string
				char tmp[6];
 
				ltoa(iCount,tmp,10);
 
				m_UDPList.AddString(tmp);
			}

		if (m_AutoScroll)
			m_UDPList.SetTopIndex(m_UDPList.GetCount()-5);

		//Add done notice
		m_UDPList.AddString("Done scanning");
	}
	else
		ICMPScan();
}

BOOL CUDPScanerDlg::ICMPScan()
{
	//Scan
	int iCount;

	for (iCount=m_StartPort;iCount<=m_EndPort;iCount++)
		//Only if not scaned
		if (!m_ICMP->GetBit(iCount))
		{
			if (m_ScanDelay)
				Sleep(m_ScanDelay);

			m_UDP->Send(0,m_cDestinationIP,iCount,NULL,NULL);
		}

	//Decrement the count
	--m_LoopCount;

	//And set the scan timeout
	m_ICMP->SetTimeout(SLEEP_TIMEOUT);

	//Return OK
	return TRUE;
}


BOOL CUDPScanerDlg::ConvertAddress()
{
	if (m_URL=="")
		return TRUE;

	long lAddr;

	lAddr=m_ICMP->ResolveDNS(m_URL);

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
