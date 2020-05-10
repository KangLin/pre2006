// License.cpp : implementation file
//

#include "stdafx.h"
#include "showdialog.h"
#include "..\..\..\File\FileEx.h"
#include "License.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLicense dialog


CLicense::CLicense(CWnd* pParent /*=NULL*/)
	: CDialog(CLicense::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLicense)
	m_bAgree = 1;
	m_m_bShow = TRUE;
	//}}AFX_DATA_INIT
	m_hIcon = AfxGetApp()->LoadIcon(IDI_KL);
}


void CLicense::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLicense)
	DDX_Control(pDX, IDC_RICHTEXTCTRL1, m_RichText); 
	DDX_Radio(pDX, IDC_RADIO1, m_bAgree);
	DDX_Check(pDX, IDC_CHECK1, m_m_bShow);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLicense, CDialog)
	//{{AFX_MSG_MAP(CLicense)
	ON_BN_CLICKED(IDC_RADIO1, OnRadio1)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLicense message handlers

BOOL CLicense::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    // ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

    // TODO:  �ڴ���Ӷ���ĳ�ʼ��
    COleVariant vt((short)0, VT_I2); 
    TCHAR szFile[MAX_PATH];
    CString szPath, szTitle;
    TRY
    {
        CFileEx fe;
        fe.GetModuleFileName(szFile);
        fe.GetFilePath(szPath);
        m_RichText.LoadFile(szPath + _T("\\License.rtf"), vt);
    }
    CATCH(CException, e)
    {
        e->ReportError();
    }
    END_CATCH
    CButton *pbut;
    pbut = (CButton*)this->GetDlgItem(IDOK);
    pbut->EnableWindow(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLicense::OnRadio1()
{
	CButton* pbut; 
    pbut = (CButton*)this->GetDlgItem(IDOK);
    pbut->EnableWindow();
}

void CLicense::OnRadio2() 
{
    CButton *pbut;
    pbut = (CButton*)this->GetDlgItem(IDOK);
    pbut->EnableWindow(FALSE);
}
