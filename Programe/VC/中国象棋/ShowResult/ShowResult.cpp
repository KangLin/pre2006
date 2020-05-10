// ShowResult\ShowResult.cpp : 实现文件
//

#include "stdafx.h"
#include "ShowResult.h"
#include ".\showresult.h"


// CShowResult 对话框

IMPLEMENT_DYNAMIC(CShowResult, CDialog)
CShowResult::CShowResult(CWnd* pParent /*=NULL*/)
	: CDialog(CShowResult::IDD, pParent)
    , m_szWin(_T(""))
    , m_szLoss(_T(""))
    , m_iWin(0)
    , m_iLoss(0)
    , m_iAdd(0)
    , m_iInc(0)
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_CHESSTYPE);
}

CShowResult::~CShowResult()
{
}

void CShowResult::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_WIN_USER, m_szWin);
    DDX_Text(pDX, IDC_EDIT_LOSS_USER, m_szLoss);
    DDX_Text(pDX, IDC_EDIT_WIN, m_iWin);
    DDX_Text(pDX, IDC_EDIT_LOSS, m_iLoss);
    DDX_Text(pDX, IDC_EDIT_ADD, m_iAdd);
    DDX_Text(pDX, IDC_EDIT_INC, m_iInc);
}


BEGIN_MESSAGE_MAP(CShowResult, CDialog)
END_MESSAGE_MAP()


// CShowResult 消息处理程序

BOOL CShowResult::OnInitDialog()
{
    CDialog::OnInitDialog();

    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}
