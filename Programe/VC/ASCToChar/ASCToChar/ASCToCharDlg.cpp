// ASCToCharDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ASCToChar.h"
#include "ASCToCharDlg.h"
#include "charConver.h"

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


// CASCToCharDlg �Ի���




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


// CASCToCharDlg ��Ϣ�������

BOOL CASCToCharDlg::OnInitDialog()
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CASCToCharDlg::OnPaint()
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
HCURSOR CASCToCharDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


/*******************************************************************************************************
��������OnBnClickedOk
��  ����ACSII �ַ������ַ�����ת��
��  ������
����ֵ������Ϊ void ��
��  ����1.0.0.1
��  �ߣ���  ��
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
	}// ���� if(pszTmp == NULL)
	memset(pszTmp, 0, nLen);
	strcpy(pszTmp, (char * )(LPCTSTR)m_szInput);
	pOut = ASCToString(pszTmp);
	m_szOutput = pOut;
	delete []pOut;
	delete []pszTmp;
	UpdateData(FALSE);
}

/*******************************************************************************************************
��������OnBnClickedButtonString
��  �����ַ����� ASCII �ַ�����ת��
��  ������
����ֵ������Ϊ void ��
��  ����1.0.0.1
��  �ߣ���  ��
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
	}// ���� if(pszTmp == NULL)
	memset(pszTmp, 0, nLen);
	strcpy(pszTmp, (char * )(LPCTSTR)m_szOutput);
	pOut = CharToASCII(pszTmp);
	m_szInput = pOut;

	delete []pszTmp;
	delete []pOut;
	UpdateData(FALSE);
}
