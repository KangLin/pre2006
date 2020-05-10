// TestProcessDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TestProcess.h"
#include "TestProcessDlg.h"
#include "..\ProcessInformation.h"
#include "..\..\..\..\System\Process\WMIProcessInfo.h"
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


// CTestProcessDlg �Ի���




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


// CTestProcessDlg ��Ϣ�������

BOOL CTestProcessDlg::OnInitDialog()
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestProcessDlg::OnPaint()
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
		file.WriteString(_T("������:"));
		file.WriteString(procinfo->szProcessName.c_str());
		file.WriteString(_T("\r\n"));

		file.WriteString(_T("ģ��:"));

		vector < CProcessInformation::MODULEINFO > ::iterator itModule;
		for(itModule = procinfo->Module.begin(); itModule != procinfo->Module.end(); itModule++)
		{
			CProcessInformation::PMODULEINFO module;
			module = &(*itModule);
			file.WriteString(module->szExePath.c_str());
			file.WriteString(_T("\r\n"));
		}// ���� for(itModule = procinfo->Module.begin(); itModule != procinfo->Module.end(); itModule++)
		file.WriteString(_T("\r\n"));
	}// ���� for(it = info.begin(); it != info.end(); it++)
	file.Close();
	TRACE(_T("%s\n"), szName.c_str());

	CWMIProcessInfo wmi;
	vector<CWMIProcessInfo::PROCESS_INFORMATION> procInfo;
	wmi.GetProcessInformation(&procInfo, _T("192.168.101.123"), _T("administrator"), _T("sz2007"));

}
