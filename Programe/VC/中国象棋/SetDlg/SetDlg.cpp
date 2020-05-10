// SetDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SetDlg.h"
#include ".\setdlg.h"


// CSetDlg �Ի���

IMPLEMENT_DYNAMIC(CSetDlg, CDialog)
CSetDlg::CSetDlg(CWnd* pParent /*=NULL*/)
: CDialog(CSetDlg::IDD, pParent)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_CHESSTYPE);
    m_dwStep = 0;
    m_uAddPoint = 0;
    m_uIncPoint = 0;
    m_iFunction = Setting;
}

CSetDlg::~CSetDlg()
{
}

void CSetDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_TIME_STEP, m_dwStep);
    DDX_Text(pDX, IDC_EDIT_POINT, m_uAddPoint);
    DDX_Text(pDX, IDC_EDIT_INCPOINT, m_uIncPoint);
}


BEGIN_MESSAGE_MAP(CSetDlg, CDialog)
END_MESSAGE_MAP()


// CSetDlg ��Ϣ�������

BOOL CSetDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
  
    //���ô���ͼ��
    SetIcon(m_hIcon, false);
    SetIcon(m_hIcon, true);

    switch(m_iFunction)
    {
    case Setting:
        SetWindowText(_T("�����������"));
        break;
    case ReceiveSet:
        SetWindowText(_T("�Է������������������"));
        break;
    }
    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
}
