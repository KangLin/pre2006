// TestDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CTestDlg �Ի���




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


// CTestDlg ��Ϣ�������

BOOL CTestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
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
#endif // ���� #ifdef _PROCESS_
#ifdef _REGISTER_
	CRegisterFilterControl rmc;
#endif
	rmc.Load(m_szPath);
	if(rmc.Open())
	{
		rmc.Hook();
		rmc.Close();
	} // ���� if(rmc.Open())
}

void CTestDlg::OnBnClickedButton2()
{
#ifdef _PROCESS_
	CProcessFilterControl rmc;
#endif // ���� #ifdef _PROCESS_
#ifdef _REGISTER_
		CRegisterFilterControl rmc;
#endif
	if(rmc.Open())
	{
		rmc.UnHook();
		rmc.Close();
	} // ���� (rmc.Open())
	rmc.UnLoad();
}

void CTestDlg::OnBnClickedButton3()
{
	CFileDialog fd(true);
	if(fd.DoModal() == IDOK)
	{
		m_szPath = fd.GetPathName();
		UpdateData(false);
	} // ���� if(fd.DoModal() == IDOK)
}

void CTestDlg::OnBnClickedButton4()
{
	UpdateData();
#ifdef _PROCESS_
	CProcessFilterControl rmc;
#endif // ���� #ifdef _PROCESS_
#ifdef _REGISTER_
		CRegisterFilterControl rmc;
#endif
	if(rmc.Open())
	{
		rmc.SetProtectContent(m_szAdd);
		rmc.Close();
	} // ���� (rmc.Open())
}

void CTestDlg::OnBnClickedButton5()
{
	UpdateData();
#ifdef _PROCESS_
	CProcessFilterControl rmc;
#endif // ���� #ifdef _PROCESS_
#ifdef _REGISTER_
		CRegisterFilterControl rmc;
#endif
	if(rmc.Open())
	{
		rmc.RemoveProtectContent(m_szRemove);
		rmc.Close();
	} // ���� (rmc.Open())
}

void CTestDlg::OnBnClickedButton6()
{
#ifdef _PROCESS_
	CProcessFilterControl rmc;
#endif // ���� #ifdef _PROCESS_
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
	} // ���� (rmc.Open())
}

void CTestDlg::OnBnClickedButton7()
{
#ifdef _PROCESS_
	CProcessFilterControl rmc;
#endif // ���� #ifdef _PROCESS_
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
	} // ���� (rmc.Open())
}