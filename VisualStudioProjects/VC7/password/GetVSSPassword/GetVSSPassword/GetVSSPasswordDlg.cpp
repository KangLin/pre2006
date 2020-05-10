// GetVSSPasswordDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "GetVSSPassword.h"
#include "GetVSSPasswordDlg.h"

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


// CGetVSSPasswordDlg �Ի���




CGetVSSPasswordDlg::CGetVSSPasswordDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGetVSSPasswordDlg::IDD, pParent)
	, m_szPassword(_T(""))
	, m_szEnPassword(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGetVSSPasswordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_PASSWORD, m_szPassword);
	DDX_Text(pDX, IDC_ENPASSWORD, m_szEnPassword);
}

BEGIN_MESSAGE_MAP(CGetVSSPasswordDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CGetVSSPasswordDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CGetVSSPasswordDlg ��Ϣ�������

BOOL CGetVSSPasswordDlg::OnInitDialog()
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

void CGetVSSPasswordDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CGetVSSPasswordDlg::OnPaint()
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
HCURSOR CGetVSSPasswordDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CGetVSSPasswordDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	//OnOK();
#define LEN 100
	TCHAR szPassword[LEN];
	TCHAR szEncryptPassword[LEN];
	UpdateData();
	memset(szPassword, 0, sizeof(TCHAR) * LEN);
	_tcscpy(szEncryptPassword, m_szEnPassword);
	GetPassword(szEncryptPassword, szPassword);
	m_szPassword = szPassword;
	UpdateData(FALSE);
}

int CGetVSSPasswordDlg::HexToInt(char c)
{
	if(c < 'A' && c > 'F')
	{
		c = c + 32;
	} // ���� if(c < 'A' && c > 'F')
	if(c < 'a')
	{
		return c - '0';
	}
	else
	{
		return c - 'a' + 10;
	}
}

int CGetVSSPasswordDlg::GetPassword(LPCTSTR lpcszEncryptPassword, LPTSTR lpszPassword)
{
	const char incstr[16] = "BrianDavidHarry";
    int i;
    int j;
    int k;
    long c1;
    long c2;
    long c4;
    int c3;
	
    WORD a;
    WORD b;
    WORD c;
    WORD d;
    WORD e;
    int num;
	
	a = HexToInt(lpcszEncryptPassword[2])*16 * 16 * 16 + HexToInt(lpcszEncryptPassword[3])*16 * 16 + HexToInt(lpcszEncryptPassword[0])*16 + HexToInt(lpcszEncryptPassword[1]);
	c3 = 'Z' - '0' + 1;
	
	for(i = 0; i < 15; i++)
    {
		lpszPassword[i] = 0;
		b = 0;
		for(j = 0; j < 15 - i; j++)
        {
            c = incstr[j]; 
            c = c ^ 0x96;
			c = c * (j + 1 + i);
            b += c;
        } // ���� for(j = 0; j < 15 - i; j++)
		if(i == 0 && b == a)
        {
            printf("password is null\n");
            return 0;
        } // ���� if(i == 0 && b == a)
        d = a - b;
        num = 0;
        c2 = 1;
		for(j = 0; j < i; j++)
        {
			num = num + j + 1;
			c2 = c3 * c2;
        } // ���� for(j = 0; j < i; j++)
		if(num > 0)
        {
            c1 = 0;            
			if((d / num) > 154 && (d / num) < 250)
            {
				memset(lpszPassword, '0', i);
				Sleep(100);
                do{
                    c4 = 1;
					for(j = 1; j < i - 1; j++)
                    {
                        c4 = c4 * c3;
						if(c1 % c4 == 0)
                            lpszPassword[j]='0';
                        else
                        {
                            lpszPassword[j]++;
                            break;
                        } // ���� if(c1 % c4 == 0)
                    } // ���� for(j = 1; j < i - 1; j++)
                    b = 0;
					for(k = 1; k < i; k++)
                    {
                        c = lpszPassword[k]; 
                        c = c ^ 0x96;
						c = c * (k + 1);
                        b += c;
                    } // ���� for(k = 1; k < i; k++)
					e = d - b;
                    
					if((e ^ 0x96) >= '0' && (e ^ 0x96) <= 'Z')
                    {
						lpszPassword[0] = (e ^ 0x96);
						TRACE(_T("%s\n"), lpszPassword);
                        return i;
                    } // ���� if((e ^ 0x96) >= '0' && (e ^ 0x96) <= 'Z')
                    c1++;
                }while(c1<c2);                
            } // ���� if((d / num) > 154 && (d / num) < 250)
        } // ���� if(num > 0)
    } // ���� for(i = 0; i < 15; i++)
    return 0;    
}