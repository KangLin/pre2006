// TestProcessDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TestProcess.h"
#include "TestProcessDlg.h"
#include "..\ProcessInformation.h"
#include "..\..\..\..\System\Process\WMIProcessInfo.h"
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


// CTestProcessDlg 对话框




CTestProcessDlg::CTestProcessDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestProcessDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestProcessDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestProcessDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CTestProcessDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CTestProcessDlg 消息处理程序

BOOL CTestProcessDlg::OnInitDialog()
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

void CTestProcessDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CTestProcessDlg::OnPaint()
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
HCURSOR CTestProcessDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestProcessDlg::OnBnClickedOk()
{
	_tstring szName;
	CProcessInformation pi;
	vector < CProcessInformation::PROCESS_MODULE_INFO > info;
	szName = pi.GetAllProcessModuleInfo(&info);
	_tsetlocale(LC_ALL, _T(".OCP"));
	CStdioFile file(_T("bb.txt"), CFile::modeCreate | CFile::modeWrite);
	vector < CProcessInformation::PROCESS_MODULE_INFO > ::iterator it;
	for(it = info.begin(); it != info.end(); it++)
	{
		CProcessInformation::PPROCESS_MODULE_INFO procinfo;
		procinfo = &(*it);
		file.WriteString(_T("进程名:"));
		file.WriteString(procinfo->szProcessName.c_str());
		file.WriteString(_T("\r\n"));

		file.WriteString(_T("模块:"));

		vector < CProcessInformation::MODULEINFO > ::iterator itModule;
		for(itModule = procinfo->Module.begin(); itModule != procinfo->Module.end(); itModule++)
		{
			CProcessInformation::PMODULEINFO module;
			module = &(*itModule);
			file.WriteString(module->szExePath.c_str());
			file.WriteString(_T("\r\n"));
		}// 结束 for(itModule = procinfo->Module.begin(); itModule != procinfo->Module.end(); itModule++)
		file.WriteString(_T("\r\n"));
	}// 结束 for(it = info.begin(); it != info.end(); it++)
	file.Close();
	TRACE(_T("%s\n"), szName.c_str());

	CWMIProcessInfo wmi;
	vector<CWMIProcessInfo::PROCESS_INFORMATION> procInfo;
	wmi.GetProcessInformation(&procInfo, _T("192.168.101.123"), _T("administrator"), _T("sz2007"));

}
