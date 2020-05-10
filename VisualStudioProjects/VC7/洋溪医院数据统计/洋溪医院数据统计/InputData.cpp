// InputData.cpp : 实现文件
//

#include "stdafx.h"
#include "洋溪医院数据统计.h"
#include "InputData.h"
#include ".\inputdata.h"


// CInputData 对话框

IMPLEMENT_DYNAMIC(CInputData, CDialog)
CInputData::CInputData(CWnd* pParent /*=NULL*/)
	: CDialog(CInputData::IDD, pParent)
{
    m_hIcon = ::AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

CInputData::~CInputData()
{
}

void CInputData::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_STATIC_GROUP, m_Group);
    DDX_Control(pDX, IDC_COMBO_DOCTOR, m_cbDoctor);
}

BEGIN_MESSAGE_MAP(CInputData, CDialog)
    ON_WM_SIZE()
    ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


// CInputData 消息处理程序

BOOL CInputData::OnInitDialog()
{
    CDialog::OnInitDialog();

    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void CInputData::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CDialog::OnShowWindow(bShow, nStatus);

    ShowWindow(SW_SHOWMAXIMIZED);
}

void CInputData::OnSize(UINT nType, int cx, int cy)
{
    CDialog::OnSize(nType, cx, cy);
    if(m_Group.GetSafeHwnd() != NULL)
    {
        CRect gRect, rect;
        m_Group.GetWindowRect(&gRect);
        ScreenToClient(&gRect);
        rect.top = gRect.top;
        rect.left = (cx - gRect.Width()) / 2;
        rect.bottom = gRect.bottom;
        rect.right = cx - rect.left;
        m_Group.MoveWindow(&rect);        
    } //结束 if(m_Group.GetSafeHwnd())
}


