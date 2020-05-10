// TestDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"
#include "..\FilterControl\RegisterFilterControl.h"
#include "..\FilterControl\ProcessFilterControl.h"
#include "..\..\..\System\File\FileEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CTestDlg 对话框




CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestDlg::IDD, pParent)
	, m_szPath(_T(""))
	, m_szRemove(_T(""))
	, m_szAdd(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_szPath);
	DDX_Text(pDX, IDC_EDIT3, m_szRemove);
	DDX_Text(pDX, IDC_EDIT2, m_szAdd);
}

BEGIN_MESSAGE_MAP(CTestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CTestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CTestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CTestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CTestDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CTestDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CTestDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CTestDlg::OnBnClickedButton7)
END_MESSAGE_MAP()


// CTestDlg 消息处理程序

BOOL CTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

#define _REGISTER_

void CTestDlg::OnBnClickedButton1()
{
	UpdateData();
#ifdef _PROCESS_
	CProcessFilterControl rmc;
#endif // 结束 #ifdef _PROCESS_
#ifdef _REGISTER_
	CRegisterFilterControl rmc;
#endif
	rmc.Load(m_szPath);
	if(rmc.Open())
	{
		rmc.Hook();
		rmc.Close();
	} // 结束 if(rmc.Open())
}

void CTestDlg::OnBnClickedButton2()
{
#ifdef _PROCESS_
	CProcessFilterControl rmc;
#endif // 结束 #ifdef _PROCESS_
#ifdef _REGISTER_
		CRegisterFilterControl rmc;
#endif
	if(rmc.Open())
	{
		rmc.UnHook();
		rmc.Close();
	} // 结束 (rmc.Open())
	rmc.UnLoad();
}

void CTestDlg::OnBnClickedButton3()
{
	CFileDialog fd(true);
	if(fd.DoModal() == IDOK)
	{
		m_szPath = fd.GetPathName();
		UpdateData(false);
	} // 结束 if(fd.DoModal() == IDOK)
}

void CTestDlg::OnBnClickedButton4()
{
	UpdateData();
#ifdef _PROCESS_
	CProcessFilterControl rmc;
#endif // 结束 #ifdef _PROCESS_
#ifdef _REGISTER_
		CRegisterFilterControl rmc;
#endif
	if(rmc.Open())
	{
		rmc.SetProtectContent(m_szAdd);
		rmc.Close();
	} // 结束 (rmc.Open())
}

void CTestDlg::OnBnClickedButton5()
{
	UpdateData();
#ifdef _PROCESS_
	CProcessFilterControl rmc;
#endif // 结束 #ifdef _PROCESS_
#ifdef _REGISTER_
		CRegisterFilterControl rmc;
#endif
	if(rmc.Open())
	{
		rmc.RemoveProtectContent(m_szRemove);
		rmc.Close();
	} // 结束 (rmc.Open())
}

void CTestDlg::OnBnClickedButton6()
{
#ifdef _PROCESS_
	CProcessFilterControl rmc;
#endif // 结束 #ifdef _PROCESS_
#ifdef _REGISTER_
		CRegisterFilterControl rmc;
#endif
	if(rmc.Open())
	{
		CFileEx f;
		f.GetModuleFileName();
		_tstring szTmp = f.GetFilePath();
		szTmp += _T("\\config.txt");
		rmc.LoadConfig(szTmp.c_str());
		rmc.Close();
	} // 结束 (rmc.Open())
}

void CTestDlg::OnBnClickedButton7()
{
#ifdef _PROCESS_
	CProcessFilterControl rmc;
#endif // 结束 #ifdef _PROCESS_
#ifdef _REGISTER_
		CRegisterFilterControl rmc;
#endif
	if(rmc.Open())
	{
		CFileEx f;
		f.GetModuleFileName();
		_tstring szTmp = f.GetFilePath();
		szTmp += _T("\\config.txt");
		rmc.SaveConfig(szTmp.c_str());
		rmc.Close();
	} // 结束 (rmc.Open())
}