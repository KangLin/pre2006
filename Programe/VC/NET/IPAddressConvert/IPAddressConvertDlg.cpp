// IPAddressConvertDlg.cpp : implementation file
//

#include "stdafx.h"
#include "IPAddressConvert.h"
#include "IPAddressConvertDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma  comment(lib, "ws2_32.lib")

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
// CIPAddressConvertDlg dialog

CIPAddressConvertDlg::CIPAddressConvertDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CIPAddressConvertDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CIPAddressConvertDlg)
	m_szIP = _T("");
	m_dwIP = 0;
	m_szHexIP = _T("");
	m_nSelect = 0;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIPAddressConvertDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CIPAddressConvertDlg)
	DDX_Text(pDX, IDC_EDIT_STRING_IP, m_szIP);
	DDX_Text(pDX, IDC_EDIT_DWORD_IP, m_dwIP);
	DDX_Text(pDX, IDC_EDIT_HEX_IP, m_szHexIP);
	DDX_Radio(pDX, IDC_RADIO1, m_nSelect);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CIPAddressConvertDlg, CDialog)
	//{{AFX_MSG_MAP(CIPAddressConvertDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CIPAddressConvertDlg message handlers

BOOL CIPAddressConvertDlg::OnInitDialog()
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

void CIPAddressConvertDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CIPAddressConvertDlg::OnPaint() 
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
HCURSOR CIPAddressConvertDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CIPAddressConvertDlg::OnOK() 
{
	UpdateData();

	switch(m_nSelect)
	{
	case 0:
		IPFormString();
		break;
	case 1:
		IPFromDWORD();
		break;
	case 2:
		IPFormHex();
		break;
	default:
		break;
	}

	UpdateData(FALSE);
}

int CIPAddressConvertDlg::IPFormString()
{
	m_dwIP = ntohl(inet_addr(m_szIP));
	m_szHexIP.Format(_T("%X"), m_dwIP);
	return 0;
}

int CIPAddressConvertDlg::IPDWORDToString()
{
	in_addr dwAddr;
	dwAddr.s_addr = htonl(m_dwIP);
	m_szIP = inet_ntoa(dwAddr);
	return 0;
}

int CIPAddressConvertDlg::IPFromDWORD()
{
	IPDWORDToString();
	m_szHexIP.Format(_T("%X"), m_dwIP);
	return 0;
}

int CIPAddressConvertDlg::IPFormHex()
{
	m_dwIP = HexStrToDWORD((LPTSTR)(LPCTSTR)m_szHexIP, m_szHexIP.GetLength());
	IPDWORDToString();
	return IPFromDWORD();
}

/*******************************************************************************************************
函数名：HexStrToDWORD
描  述：从用字符串表示的十六进制转换为DWORD
参  数：
		char * str：十六进制的数字字符串
		int nSize ：要转换的长度
返回值：类型为 DWORD 。
版  本：1.0
作  者：康  林
时  间：2005年11月4日 21:28:34
*******************************************************************************************************/
DWORD CIPAddressConvertDlg::HexStrToDWORD(char * str, int nSize)
{
    DWORD value=0;
	
	for(int i = 0; i < nSize; ++i)
    {
		if(str[i] >= '0' && str[i] <= '9')
        {
			value <<= 4;
			value += (str[i] - '0');
        }
        else
        {
			value <<= 4;
			if(str[i] >= _T('a') && str[i] <= _T('f'))
			{
				value += (str[i] - _T('a') + 10);
			}				
			else
			{
				if(str[i] >= _T('A') && str[i] <= _T('F'))
				{
					value += (str[i] - _T('A') + 10);
				} // 结束 if(str[i] >= _T('A') && str[i] <= _T('F'))
			} // 结束 if(str[i] >= _T('a') && str[i] <= _T('f'))
        }
    }
	
    return value;
}
