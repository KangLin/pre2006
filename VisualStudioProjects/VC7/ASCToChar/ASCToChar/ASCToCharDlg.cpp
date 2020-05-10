// ASCToCharDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "ASCToChar.h"
#include "ASCToCharDlg.h"
#include "charConver.h"

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


// CASCToCharDlg 对话框




CASCToCharDlg::CASCToCharDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CASCToCharDlg::IDD, pParent)
	, m_szInput(_T(""))
	, m_szOutput(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CASCToCharDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_szInput);
	DDX_Text(pDX, IDC_EDIT2, m_szOutput);
}

BEGIN_MESSAGE_MAP(CASCToCharDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CASCToCharDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_STRING, &CASCToCharDlg::OnBnClickedButtonString)
END_MESSAGE_MAP()


// CASCToCharDlg 消息处理程序

BOOL CASCToCharDlg::OnInitDialog()
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

void CASCToCharDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CASCToCharDlg::OnPaint()
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
HCURSOR CASCToCharDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*******************************************************************************************************
函数名：OnBnClickedOk
描  述：ACSII 字符串到字符串的转换
参  数：无
返回值：类型为 void 。
版  本：1.0.0.1
作  者：康  林
*******************************************************************************************************/
void CASCToCharDlg::OnBnClickedOk()
{
	UpdateData();
	char * pszTmp, *pOut;
	int nLen;
	nLen = m_szInput.GetLength() + 1;
	pszTmp = new char[nLen];
	if(pszTmp == NULL)
	{
		return;
	}// 结束 if(pszTmp == NULL)
	memset(pszTmp, 0, nLen);
	strcpy(pszTmp, (char * )(LPCTSTR)m_szInput);
	pOut = ASCToString(pszTmp);
	m_szOutput = pOut;
	delete []pOut;
	delete []pszTmp;
	UpdateData(FALSE);
}

/*******************************************************************************************************
函数名：OnBnClickedButtonString
描  述：字符串到 ASCII 字符串的转换
参  数：无
返回值：类型为 void 。
版  本：1.0.0.1
作  者：康  林
*******************************************************************************************************/
void CASCToCharDlg::OnBnClickedButtonString()
{
	UpdateData();
	char * pszTmp, *pOut;
	int nLen;
	nLen = m_szOutput.GetLength() + 1;
	pszTmp = new char[nLen];
	if(pszTmp == NULL)
	{
		return;
	}// 结束 if(pszTmp == NULL)
	memset(pszTmp, 0, nLen);
	strcpy(pszTmp, (char * )(LPCTSTR)m_szOutput);
	pOut = CharToASCII(pszTmp);
	m_szInput = pOut;

	delete []pszTmp;
	delete []pOut;
	UpdateData(FALSE);
}
