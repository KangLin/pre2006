// InputData.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "��ϪҽԺ����ͳ��.h"
#include "InputData.h"
#include ".\inputdata.h"


// CInputData �Ի���

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


// CInputData ��Ϣ�������

BOOL CInputData::OnInitDialog()
{
    CDialog::OnInitDialog();

    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
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
    } //���� if(m_Group.GetSafeHwnd())
}


