// testDlg.cpp : ʵ���ļ�
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


// CtestDlg �Ի���




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


// CtestDlg ��Ϣ�������

BOOL CtestDlg::OnInitDialog()
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CtestDlg::OnPaint()
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
	} // ���� if(fileDlg.DoModal() == IDOK)
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
	} // ���� if(!ctrl.Open())

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
	} // ���� if(!ctrl.Open())

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
	} // ���� if(!ctrl.OpenDevice())

	ctrl.RemoveProtectFile(m_szRemoveFile);

	ctrl.Close();
}

void CtestDlg::OnBnClickedButton7()
{
	CKSFilterControl ctrl;
	if(!ctrl.Open())
	{
		return;
	} // ���� if(!ctrl.Open())
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
	} // ���� if(IDOK == fd.DoModal())
}
