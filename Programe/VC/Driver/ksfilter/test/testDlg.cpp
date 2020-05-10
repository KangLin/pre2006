// testDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "test.h"
#include "testDlg.h"
#include "stdafx.h"
#include "instdrv.h"
#ifdef _TEST_
#include "..\ksfilter\Array.h"
#endif
#include <winioctl.h>
#include "..\..\..\System\File\FileEx.h"
#include "..\KSFilterControl\KSFilterControl.h"

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


// CtestDlg 对话框




CtestDlg::CtestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CtestDlg::IDD, pParent)
	, m_szPath(_T(""))
	, m_szFileName(_T(""))
	, m_szRemoveFile(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PATH, m_szPath);
	DDX_Text(pDX, IDC_SETFILE, m_szFileName);
	DDX_Text(pDX, IDC_EDIT3, m_szRemoveFile);
}

BEGIN_MESSAGE_MAP(CtestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON3, &CtestDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON1, &CtestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CtestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON4, &CtestDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CtestDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CtestDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CtestDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CtestDlg::OnBnClickedButton8)
END_MESSAGE_MAP()


// CtestDlg 消息处理程序

BOOL CtestDlg::OnInitDialog()
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

void CtestDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CtestDlg::OnPaint()
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
HCURSOR CtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CtestDlg::OnBnClickedButton3()
{
	CFileDialog fileDlg(TRUE);
	if(fileDlg.DoModal() == IDOK)
	{
		m_szPath = fileDlg.GetPathName();
		UpdateData(FALSE);
	} // 结束 if(fileDlg.DoModal() == IDOK)
}

void CtestDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	LoadDeviceDriver(_T("KSFilter"), m_szPath);
}

void CtestDlg::OnBnClickedButton2()
{
	UnloadDeviceDriver(_T("KSFilter"));
}

#ifdef _TEST_
ARRAYHEAD gArray;

int callBack(PDATASTRUCT pDestination, PDATASTRUCT pSource)
{
	return _tcscmp(*pDestination, *pSource);
}

int clearData(PDATASTRUCT pDestination)
{
	DATASTRUCT d =* pDestination;
	delete [] d;
	return 0;
}
#endif

void CtestDlg::OnBnClickedButton4()
{
	CKSFilterControl ctrl;
	if(!ctrl.Open())
	{
		return;
	} // 结束 if(!ctrl.Open())

	CFileEx f;
	f.GetModuleFileName();
	_tstring szTmp = f.GetFilePath();
	szTmp += _T("\\config.txt");
	ctrl.SaveConfig(szTmp.c_str());

	ctrl.Close();
	//TCHAR * pCh;
	//InitialArray(&gArray);
	//pCh = new TCHAR[3];
	//_tcscpy(pCh, _T("cfg"));
	//InsertElementArray(&gArray, &pCh, callBack);
	//pCh = new TCHAR[3];
	//_tcscpy(pCh, _T("dd"));
	//InsertElementArray(&gArray, &pCh, callBack);
	//pCh = new TCHAR[3];
	//_tcscpy(pCh, _T("ar"));
	//InsertElementArray(&gArray, &pCh, callBack);
	//pCh = new TCHAR[3];
	//_tcscpy(pCh, _T("kb"));
	//InsertElementArray(&gArray, &pCh, callBack);
	//pCh = new TCHAR[3];
	//_tcscpy(pCh, _T("zf"));
	//InsertElementArray(&gArray, &pCh, callBack);
	//pCh = new TCHAR[3];
	//_tcscpy(pCh, _T("hd"));
	//InsertElementArray(&gArray, &pCh, callBack);
	//pCh = new TCHAR[3];
	//_tcscpy(pCh, _T("bd"));
	//InsertElementArray(&gArray, &pCh, callBack);
	//pCh = new TCHAR[3];
	//_tcscpy(pCh, _T("ta"));
	//InsertElementArray(&gArray, &pCh, callBack);
	//pCh = new TCHAR[3];
	//_tcscpy(pCh, _T("f"));
	//InsertElementArray(&gArray, &pCh, callBack);
	//pCh = new TCHAR[3];
	//_tcscpy(pCh, _T("m"));
	//InsertElementArray(&gArray, &pCh, callBack);
	//pCh = new TCHAR[3];
	//_tcscpy(pCh, _T("t"));
	//InsertElementArray(&gArray, &pCh, callBack);
	//pCh = new TCHAR[3];
	//_tcscpy(pCh, _T("ta"));
	//DeleteElementArray(&gArray, &pCh, callBack, clearData);
	//pCh = new TCHAR[3];
	//_tcscpy(pCh, _T("cfg"));
	//DeleteElementArray(&gArray, &pCh, callBack, clearData);
	//ClearArray(&gArray, clearData);
}

void CtestDlg::OnBnClickedButton5()
{

	UpdateData();
	

	CKSFilterControl ctrl;
	if(!ctrl.Open())
	{
		return;
	} // 结束 if(!ctrl.Open())

	ctrl.SetProtectFile(m_szFileName);

	ctrl.Close();
}

void CtestDlg::OnBnClickedButton6()
{
	
	UpdateData();
	

	CKSFilterControl ctrl;
	if(!ctrl.Open())
	{
		return;
	} // 结束 if(!ctrl.OpenDevice())

	ctrl.RemoveProtectFile(m_szRemoveFile);

	ctrl.Close();
}

void CtestDlg::OnBnClickedButton7()
{
	CKSFilterControl ctrl;
	if(!ctrl.Open())
	{
		return;
	} // 结束 if(!ctrl.Open())
	CFileEx f;
	f.GetModuleFileName();
	_tstring szTmp = f.GetFilePath();
	szTmp += _T("\\config.txt");
	ctrl.LoadConfig(szTmp.c_str());

	ctrl.Close();
}

void CtestDlg::OnBnClickedButton8()
{
	CFileDialog fd(TRUE, NULL, NULL, OFN_ALLOWMULTISELECT);
	if(IDOK == fd.DoModal())
	{
		m_szFileName = fd.GetPathName();
		UpdateData(FALSE);
	} // 结束 if(IDOK == fd.DoModal())
}
