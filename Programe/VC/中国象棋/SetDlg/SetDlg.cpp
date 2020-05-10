// SetDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SetDlg.h"
#include ".\setdlg.h"


// CSetDlg 对话框

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


// CSetDlg 消息处理程序

BOOL CSetDlg::OnInitDialog()
{
    CDialog::OnInitDialog();
  
    //设置窗口图标
    SetIcon(m_hIcon, false);
    SetIcon(m_hIcon, true);

    switch(m_iFunction)
    {
    case Setting:
        SetWindowText(_T("设置下棋参数"));
        break;
    case ReceiveSet:
        SetWindowText(_T("对方设置了如下下棋参数"));
        break;
    }
    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}
