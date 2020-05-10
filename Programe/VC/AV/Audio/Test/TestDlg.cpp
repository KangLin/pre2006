// TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"
#include <vfw.h>
#include "..\..\compress\compress.h"
  
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

#pragma comment(lib, "vfw32")

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
// CTestDlg dialog

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTestDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


void CTestDlg::OnDestroy() 
{
	CDialog::OnDestroy();
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTestDlg)
	DDX_Control(pDX, IDC_DESTINATIONS, m_Destination);
	DDX_Control(pDX, IDC_LISTCONTROL, m_ListControl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	//{{AFX_MSG_MAP(CTestDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_STARTRECOR, OnStartrecor)
	ON_BN_CLICKED(IDC_STOPRECORD, OnStoprecord)
	ON_BN_CLICKED(IDC_STARTPLAY, OnStartplay)
	ON_BN_CLICKED(IDC_PAUSE, OnPause)
	ON_BN_CLICKED(IDC_CLOSEDEV, OnClosedev)
	ON_BN_CLICKED(IDC_CLOSERECORDDEV, OnCloserecorddev)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTestDlg message handlers

void CTestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestDlg::OnPaint() 
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
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

BOOL CTestDlg::OnInitDialog()
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

	m_pData = NULL;
	m_lDataLen = 0;
	m_WaveIn.OpenDev(this);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

CTestDlg::~CTestDlg()
{
	delete m_pData;	//要到最后释放
}

void CTestDlg::OnStartrecor() 
{
	delete m_pData;
	m_pData = new char;
	if(!m_pData)
		TRACE(_T("m_pData分配内在失败\n"));
	m_lDataLen = 0;
    m_WaveIn.StartRecord();	
}

void CTestDlg::OnStoprecord() 
{
	m_WaveIn.StopRecord();	
}

void CTestDlg::OnStartplay() 
{
     m_WaveOut.Play(m_pData, m_lDataLen);
}

void CTestDlg::OnPause() 
{
	m_WaveOut.Pause();
}

void CTestDlg::OnClosedev() 
{
	m_WaveOut.CloseDev();
}

/*******************************************************************************************************
函数名：OnWaveInDataProc
功  能：录音数据处理的外部函数
参  数：
         char* lpData：录音数据
         DWORD dwSize：录音数据的大小
         LPVOID lpParameter：从CWaveIn::OpenDev中传入的用户数据,一般为类指针
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2004-11-19
时  间：9:16:35
*******************************************************************************************************/
extern "C" void WINAPI OnWaveInDataProc(char* lpData, DWORD dwSize, LPVOID lpParameter)
{
	TRACE(_T("音频大小%d\n"), dwSize);
	CTestDlg* dlg = (CTestDlg*)lpParameter;
	if(!dlg->m_pData )
		return;
    dlg->m_pData = (char*)realloc(dlg->m_pData, dlg->m_lDataLen + dwSize);
	memcpy(dlg->m_pData + dlg->m_lDataLen, lpData, dwSize);
	dlg->m_lDataLen += dwSize;
	TRACE("已录数据长度:%d\n",dlg->m_lDataLen );
}

void CTestDlg::OnCloserecorddev() 
{
m_WaveIn.CloseDev();	
}

void CTestDlg::OnButton1() 
{
	CMixer mixer;
	int iNum;
	iNum = mixer.GetNumDevs();
	TRACE(_T("系统中混频器的数量:%d\n"), iNum);
	MIXERCAPS mxcap;
	mixer.GetDevCaps(0, &mxcap);
	TRACE(_T("混频器描述:%s\ncDestinations:%d\n"), mxcap.szPname, mxcap.cDestinations);
	char str[100];
	itoa(mxcap.cDestinations, str, 10);
	m_Destination.SetWindowText(str);

	HMIXER hMixer;
	mixerOpen(&hMixer, -1, NULL, NULL, MIXER_OBJECTF_MIXER);
	for(int i = 0; i < mxcap.cDestinations ; i++)
	{
		MIXERLINE mixerline;
		mixerline.cbStruct = sizeof(MIXERLINE);
		mixerline.dwDestination = i;
		mixer.GetLineInfo((HMIXEROBJ)hMixer, &mixerline, MIXER_GETLINEINFOF_DESTINATION);
		mixer.GetLineInfo((HMIXEROBJ)hMixer, &mixerline, MIXER_GETLINEINFOF_SOURCE);
		MIXERCONTROL *mixercontrol = new MIXERCONTROL;
		mixercontrol->cbStruct = sizeof(MIXERCONTROL);
		MIXERLINECONTROLS mixerlinecontrols;
		mixerlinecontrols.cbStruct = sizeof(MIXERLINECONTROLS);// + sizeof(MIXERCONTROL) * mixerline.cControls;
		mixerlinecontrols.dwLineID = mixerline.dwLineID;
		mixerlinecontrols.cControls = 1;
		mixerlinecontrols.cbmxctrl = sizeof(MIXERCONTROL);
		mixerlinecontrols.pamxctrl = mixercontrol;
		mixerlinecontrols.dwControlType = MIXERCONTROL_CONTROLTYPE_VOLUME;
		//mixer.GetLineControls((HMIXEROBJ)hMixer, &mixerlinecontrols, MIXER_GETLINECONTROLSF_ALL);
		delete []mixercontrol;
	}

	this->UpdateData();
}
