/*******************************************************************************************************
�ļ�����tishi.cpp
��  �ܣ�ʱ����ʾ���Զ�ˢ��ʱ��
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2005-1-19
ʱ  �䣺15:21:23

FileName��tishi.cpp
Compiler��Visual C++ 6.0
Author��  KangLin
          Copyright 2005 KangLin
Date��    2005-1-19
Time��    15:21:23
*******************************************************************************************************/
// tishi.cpp : implementation file
//

#include "stdafx.h"
#include "..\�й�����.h"
#include "..\MainFrm.h"
#include "..\�й�����Doc.h"
#include "�й�����View.h"
#include "tishi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTiShi

CTiShi::CTiShi()
{
    m_uWin = 0;
    m_uStandOff = 0;
    m_uTotal = 0;
}

CTiShi::~CTiShi()
{
}


BEGIN_MESSAGE_MAP(CTiShi, CWnd)
	//{{AFX_MSG_MAP(CTiShi)
	ON_WM_CREATE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
    ON_WM_SHOWWINDOW()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTiShi message handlers

int CTiShi::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
   
    CString t;
    t = CTime::GetCurrentTime().Format(_T(" %H:%M:%S"));
    m_Game.Create(_T("��    ʱ: 00:00:00"), WS_VISIBLE | WS_CHILD | WS_DLGFRAME | SS_CENTER, CRect(0, 0, 0, 0), this);
    m_Step.Create(_T("��    ʱ: 00:00:00"), WS_VISIBLE | WS_CHILD | WS_DLGFRAME | SS_CENTER, CRect(0, 0, 0, 0), this);
    m_Total.Create(_T("����ʱ: 00:00:00"), WS_VISIBLE | WS_CHILD | WS_DLGFRAME | SS_CENTER, CRect(0, 0, 0, 0), this);
    m_Num.Create(_T("��    ��: 0000/000"), WS_VISIBLE | WS_CHILD | WS_DLGFRAME | SS_CENTER, CRect(0, 0, 0, 0), this);

    CSize size;
    size = m_Game.GetDC()->GetTextExtent(_T("    ����ʱ:") + t);
    GetDC()->LPtoDP(&size);
    size.cx += 10;
    size.cy += 10;
    TRACE(_T("%s(%d) : ����ߴ�%d,%d\n"), __FILE__, __LINE__, size.cx, size.cy);
    
    int left;
    left = size.cx / 2 - 23;
    m_bmp.Create(NULL, NULL, SS_BITMAP | WS_VISIBLE | WS_CHILD /*| WS_DLGFRAME*/, CRect( left, 0, left + 45, 45), this, NULL);
    m_bmp.SetBitmap(IDB_BSHUAI);
    m_bmp.SetTransparence();
    
    left = 45;
    CRect rect(0, left, size.cx, size.cy + left);
    m_Total.MoveWindow(&rect);
    rect.OffsetRect(0, size.cy);
    m_Game.MoveWindow(&rect);
    rect.OffsetRect(0, size.cy);
    m_Step.MoveWindow(&rect);
    rect.OffsetRect(0, size.cy);
    m_Num.MoveWindow(&rect);
    SetNums();
    
    MoveWindow(0, 0, rect.Width() + 5, rect.Height() * 4 + 5 + 45);

    SetTimer(0, 1000, NULL);
    
    SetStepTime();
	SetGameTime();
	SetTotalTime();

	return 0;
}

BOOL CTiShi::Create(CWnd* pParentWnd) 
{
    m_pParent = (CChessView * )pParentWnd;
	return CWnd::Create(NULL, NULL, 
        WS_CHILD /*| WS_VISIBLE | WS_DLGFRAME*/,
        CRect(0, 0, 0, 0), pParentWnd, NULL, NULL);
}

/*******************************************************************************************************
��������SetBitmap
��  �ܣ�����ͼ��
��  ����
         UINT uID��ͼ����ԴID
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-19
ʱ  �䣺15:17:28
*******************************************************************************************************/
void CTiShi::SetBitmap(UINT uID)
{
    m_bmp.SetBitmap(uID);
}

/*******************************************************************************************************
��������SetTotalTime
��  �ܣ����ù���ʱ����ʼʱ��
��  ������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-19
ʱ  �䣺15:18:07
*******************************************************************************************************/
void CTiShi::SetTotalTime()
{
    m_tmTotal = CTime::GetCurrentTime();
}

/*******************************************************************************************************
��������SetGameTime
��  �ܣ����þ�ʱ����ʼʱ��
��  ������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-19
ʱ  �䣺15:18:41
*******************************************************************************************************/
void CTiShi::SetGameTime()
{
    m_tmGame = CTime::GetCurrentTime();
}

/*******************************************************************************************************
��������SetStepTime
��  �ܣ����ò�ʱ����ʼʱ��
��  ������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-19
ʱ  �䣺15:19:00
*******************************************************************************************************/
void CTiShi::SetStepTime()
{
    m_tmStep = CTime::GetCurrentTime();
}

void CTiShi::OnTimer(UINT nIDEvent) 
{
	CTime curtime;
    curtime = CTime::GetCurrentTime();
    CTimeSpan span;
    span = curtime - m_tmTotal;
    m_Total.SetWindowText(_T("����ʱ:") + span.Format(_T("%H:%M:%S")));
    span = curtime - m_tmGame;
    m_Game.SetWindowText(_T("��    ʱ:") + span.Format(_T("%H:%M:%S")));
    if(this->IsWindowVisible())
    {
        span = curtime - m_tmStep;
        m_Step.SetWindowText(_T("��    ʱ:") + span.Format(_T("%H:%M:%S")));
        CTimeSpan tmStep(0, 0, m_pParent->m_Sets.dwStep, 0);
        tmStep = tmStep - span;
        if(tmStep.GetTotalSeconds() <= 10)
        {
            m_pParent->OverTime(tmStep.GetTotalSeconds());
        } //���� if(tmStep <= 10)
    } //���� if(this->IsWindowVisible())
    
	CWnd::OnTimer(nIDEvent);
}

void CTiShi::OnShowWindow(BOOL bShow, UINT nStatus)
{
    CStatic::OnShowWindow(bShow, nStatus);

    SetStepTime();
}

/*******************************************************************************************************
��������AddWin
��  ����Ӯ������
��  ������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-11 21:10:34
*******************************************************************************************************/
void CTiShi::AddWin()
{
    m_uWin++;
    SetNums();
}

/*******************************************************************************************************
��������AddStandOff
��  �����;�����
��  ������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-11 21:10:22
*******************************************************************************************************/
void CTiShi::AddStandOff()
{
    m_uStandOff++;
    SetNums();
}

/*******************************************************************************************************
��������AddTotal
��  ����������
��  ������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-11 21:10:07
*******************************************************************************************************/
void CTiShi::AddTotal()
{
    m_uTotal++;
    SetNums();
}

/*******************************************************************************************************
��������SetNums
��  ������������
��  ������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-11 21:09:54
*******************************************************************************************************/
void CTiShi::SetNums()
{
    CString sztmp;
    TCHAR tmp[10];
    sztmp = _T("Ӯ:");
    _ltot(m_uWin, tmp, 10);
    sztmp += tmp;
    sztmp += _T("/");
    sztmp += _T("��:");
    _ltot(m_uStandOff, tmp, 10);
    sztmp += tmp;
    sztmp += _T("/����:");
    _ltot(m_uTotal, tmp, 10);
    sztmp+=tmp;
    m_Num.SetWindowText(sztmp);
}