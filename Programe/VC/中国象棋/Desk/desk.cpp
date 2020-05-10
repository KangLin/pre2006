/*******************************************************************************************************
�ļ�����desk.cpp
��  �ܣ�ʵ�����ӡ�����
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2005-1-2
ʱ  �䣺11:16:10

FileName��desk.cpp
Function��
Compiler��Visual C++ 6.0
Author��  KangLin
          Copyright 2005 KangLin
Date��    2005-1-2
Time��    11:16:10
*******************************************************************************************************/
// desk.cpp : implementation file
//

#include "stdafx.h"
#include "..\�й�����.h"
#include "..\mainfrm.h"
#include "desk.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDesk
IMPLEMENT_DYNCREATE(CDesk, CWnd)

CDesk::CDesk()
{
}

CDesk::~CDesk()
{
}


BEGIN_MESSAGE_MAP(CDesk, CWnd)
    //{{AFX_MSG_MAP(CDesk)
    ON_WM_CREATE()
    //}}AFX_MSG_MAP
//    ON_WM_CLOSE()
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDesk message handlers

int CDesk::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;
    
    // TODO: Add your specialized creation code here
    m_LeftChair.Create(NULL/*_T("static")*/, NULL, 
        WS_CHILD | WS_VISIBLE | SS_NOTIFY, 
        CRect(10, 26, 42, 58), this, IDC_LEFTCHAIR);
    m_LeftChair.SetChairNo(m_DeskNo * 2 - 1);
    SetLeftUser();
    
    m_RightChair.Create(NULL/*_T("static")*/, NULL, 
        WS_CHILD | WS_VISIBLE | SS_NOTIFY,
        CRect(126, 26, 158, 58), this, IDC_RIGHTCHAIR);
    m_RightChair.SetChairNo(m_DeskNo * 2);
    SetRightUser();
    
    m_Desk.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_CENTERIMAGE, CRect(52, 10, 116, 74), this, NULL);
    CBitmap m_bmpDesk;  //����ͼƬ
    m_bmpDesk.LoadBitmap(IDB_DESK);
    m_Desk.SetBitmap(&m_bmpDesk);
    SetDeskText();
    //m_bmpBK.LoadBitmap(IDB_DESKCHAIR);
   
    m_LeftHand.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_CENTERIMAGE, CRect(0, 16, 32, 48), &m_Desk, NULL);
    m_RightHand.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | SS_BITMAP | SS_CENTERIMAGE, CRect(32, 16, 74, 48), &m_Desk, NULL);
    
    return 0;
}

int CDesk::Create(int x, int y, CWnd* pParentWnd, int nID)
{
    return CWnd::Create(NULL, 
                   _T("����"), 
                   WS_CHILD | WS_VISIBLE, // | WS_DLGFRAME, 
                   CRect(
                   x, 
                   y,
                   x + DESK_WIDTH_ENUM,
                   y + DESK_HEIGHT_ENUM
                   ),
                   pParentWnd,
                   nID);
}

/*******************************************************************************************************
��������SetLeftUser
��  �ܣ�����������ӵ��û���������ͼƬ
��  ����
         LPCSTR lpszUserName��������ӵ��û���,Ĭ��ΪNULL,��ʾ����Ϊ������.
         HICON hIcon������ͼƬ,Ĭ��ΪNULL,Ϊ����ͼƬ.
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-18
ʱ  �䣺9:27:28
*******************************************************************************************************/
BOOL CDesk::SetLeftUser(LPCSTR lpszUserName, HICON hIcon)
{
    BOOL br;
    if(hIcon)
    {
        br = m_LeftChair.SetChairInfo(lpszUserName, hIcon);
    }
    else
    {
        br = m_LeftChair.SetChairInfo(lpszUserName, IDB_LEFTCHAIR);
    }
    if(br)
    {
        //��Ϊ�����Ǵ�CStaticEx������,��Ϊ͸��ʱ,���ػ汳��,����Ҫ�丸�����ػ�
        CRect rect;
        GetWindowRect(&rect);
        this->GetParent()->ScreenToClient(&rect);
        this->GetParent()->InvalidateRect(&rect);
    }
    else
    {
        TRACE(_T("%s(%d) : ������Ӽ���ͼ�����\n"), __FILE__, __LINE__);
        return FALSE;
    }
    return TRUE;
}

/*******************************************************************************************************
��������SetLeftUser
��  �ܣ�����������ӵ��û���������ͼƬ
��  ����
         LPCSTR lpszUserName��������ӵ��û���,Ĭ��ΪNULL,��ʾ����Ϊ������.
         CString szFile��ͼƬ���ļ�·��
����ֵ���ɹ����� TRUE�����򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-31
ʱ  �䣺20:20:38
*******************************************************************************************************/
BOOL CDesk::SetLeftUser(LPCSTR lpszUserName, CString szFile)
{
    BOOL br;
    if(szFile != "")
    {
        br = m_LeftChair.SetChairInfo(lpszUserName, szFile);
    }
    else
    {
        br = m_LeftChair.SetChairInfo(lpszUserName, IDB_LEFTCHAIR);
    }
    if(br)
    {
        //��Ϊ�����Ǵ�CStaticEx������,��Ϊ͸��ʱ,���ػ汳��,����Ҫ�丸�����ػ�
        CRect rect;
        GetWindowRect(&rect);
        this->GetParent()->ScreenToClient(&rect);
        this->GetParent()->InvalidateRect(&rect);
    }
    else
    {
        TRACE(_T("%s(%d) : ������Ӽ���ͼ�����\n"), __FILE__, __LINE__);
        return FALSE;
    }
    return TRUE;
}

/*******************************************************************************************************
��������SetRightUser
��  �ܣ������ұ����ӵ��û���������ͼƬ
��  ����
         LPCSTR lpszUserName���ұ����ӵ��û���,Ĭ��ΪNULL,��ʾ����Ϊ������.
         CString szFile��ͼƬ�ļ���·��
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-31
ʱ  �䣺20:21:37
*******************************************************************************************************/
BOOL CDesk::SetRightUser(LPCSTR lpszUserName, CString szFile)
{
    BOOL br;
    if(szFile != "")
    {
        br = m_RightChair.SetChairInfo(lpszUserName, szFile);
    }
    else
    {
        br = m_RightChair.SetChairInfo(lpszUserName, IDB_RIGHTCHAIR);
    }
    if(br)
    {
        //��Ϊ�����Ǵ�CStaticEx������,��Ϊ͸��ʱ,���ػ汳��,����Ҫ�丸�����ػ�
        CRect rect;
        GetWindowRect(&rect);
        this->GetParent()->ScreenToClient(&rect);
        this->GetParent()->InvalidateRect(&rect);
    }
    else
    {
        TRACE(_T("%s(%d) : �ұ����Ӽ���ͼ�����\n"), __FILE__, __LINE__);
        return FALSE;
    }
    return TRUE;
}

/*******************************************************************************************************
��������SetRightUser
��  �ܣ������ұ����ӵ��û���������ͼƬ
��  ����
         LPCSTR lpszUserName���ұ����ӵ��û���,Ĭ��ΪNULL,��ʾ����Ϊ������.
         HICON hIcon������ͼƬ,Ĭ��ΪNULL,Ϊ����ͼƬ.
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-18
ʱ  �䣺9:24:07
*******************************************************************************************************/
BOOL CDesk::SetRightUser(LPCSTR lpszUserName, HICON hIcon)
{
    BOOL br;
    if(hIcon)
    {
        br = m_RightChair.SetChairInfo(lpszUserName, hIcon);
    }
    else
    {
        br = m_RightChair.SetChairInfo(lpszUserName, IDB_RIGHTCHAIR);
    }
    if(br)
    {
        //��Ϊ�����Ǵ�CStaticEx������,��Ϊ͸��ʱ,���ػ汳��,����Ҫ�丸�����ػ�
        CRect rect;
        GetWindowRect(&rect);
        this->GetParent()->ScreenToClient(&rect);
        this->GetParent()->InvalidateRect(&rect);
    }
    else
    {
        TRACE(_T("%s(%d) : �ұ����Ӽ���ͼ�����\n"), __FILE__, __LINE__);
        return FALSE;
    }
    return TRUE;
}

/*******************************************************************************************************
��������SetDeskText
��  �ܣ��������ӵ�ToolTip����
��  ����
         LPCSTR lpszText��ToolTip����
����ֵ��TRUE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-18
ʱ  �䣺9:23:34
*******************************************************************************************************/
BOOL CDesk::SetDeskText(LPCSTR lpszText)
{
    if(lpszText == NULL)
    {
        CString str;
        str.Format(_T("%d������"), m_DeskNo);
        m_Desk.SetToolTipText(str);
    }
    else
    {
        m_Desk.SetToolTipText(lpszText);
    }
    return TRUE;
}

BOOL CDesk::SetLeftHand(HICON hIcon)
{
    if(hIcon)
    {
        if(!m_LeftHand.m_BKPicture.CreateFromIcon(hIcon))
        {
            TRACE(_T("%s(%d) : ���Ӽ���ͼ�����\n"), __FILE__, __LINE__);
            return FALSE;
        }
    }
    else
    {
        m_LeftHand.m_BKPicture.m_pPict = NULL;
    }

    Invalidate();
    return TRUE;
}

BOOL CDesk::SetRightHand(HICON hIcon)
{
    if(hIcon)
    {
        if(!m_RightHand.m_BKPicture.CreateFromIcon(hIcon))
        {
            TRACE(_T("%s(%d) : ���Ӽ���ͼ�����\n"), __FILE__, __LINE__);
            return FALSE;
        }
    }
    else
    {
        m_RightHand.m_BKPicture.m_pPict = NULL;
    }
    Invalidate();
    return TRUE;
}

/*******************************************************************************************************
��������SetDeskNumber
��  �ܣ��������Ӻ�,�������Ҫ�� Create ǰ����.
��  ����
         int iDeskNum�����Ӻ�
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-19
ʱ  �䣺21:30:25
*******************************************************************************************************/
void CDesk::SetDeskNumber(int iDeskNum)
{
    m_DeskNo = iDeskNum;
}

/////////////////////////////////////////////////////////////////////////////
// CChair
IMPLEMENT_DYNCREATE(CChair, CStaticEx)

CChair::CChair()
{
}

CChair::~CChair()
{
}

/*******************************************************************************************************
��������SetChairNo
��  �ܣ��������Ӻ�
��  ����
         int No�����Ӻ�
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-2
ʱ  �䣺9:53:53
*******************************************************************************************************/
BOOL CChair::SetChairNo(int No)
{
    m_iChairNo = No;
    return TRUE;
}

/*******************************************************************************************************
��������SetChairInfo
��  �ܣ�����������Ϣ���û�����ͷ��
��  ����
         LPCSTR lpszUserName���û���
         LPCSTR lpszImageFile��ͷ���ļ���
����ֵ���ɹ����� TRUE�����򷵻� FALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-2
ʱ  �䣺10:49:03
*******************************************************************************************************/
BOOL CChair::SetChairInfo(LPCSTR lpszUserName, LPCSTR lpszImageFile)
{
    ASSERT(lpszImageFile);
    CString szChair;
    szChair.Format(_T("%d"), m_iChairNo);
    if(lpszUserName == NULL)
    {
        SetTransparence();
        SetToolTipText(szChair + _T("�ţ�������"));
    }
    else
    {
        m_szUserName = lpszUserName;
        SetToolTipText(lpszUserName);
    }
    
    if(!m_BKPicture.Load(lpszImageFile))
    {
        TRACE(_T("%s(%d) : ���Ӽ���ͼƬ�ļ�����\n"), __FILE__, __LINE__);
        return FALSE;
    }
    this->Invalidate();   
    return TRUE;
}

/*******************************************************************************************************
��������SetChairInfo
��  �ܣ�����������Ϣ���û�����ͷ��
��  ����
         LPCSTR lpszUserName���û���
         HICON hIcon��ͷ��ͼ����
����ֵ���ɹ����� TRUE�����򷵻� FALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-2
ʱ  �䣺10:48:59
*******************************************************************************************************/
BOOL CChair::SetChairInfo(LPCSTR lpszUserName, HICON hIcon)
{
    ASSERT(hIcon);
    CString szChair;
    szChair.Format(_T("%d"), m_iChairNo);
    if(lpszUserName == NULL)
    {
        SetTransparence();
        SetToolTipText(szChair + _T("�ţ�������"));
    }
    else
    {
        m_szUserName = lpszUserName;
        SetToolTipText(lpszUserName);
    }
    if(!m_BKPicture.CreateFromIcon(hIcon))
    {
        TRACE(_T("%s(%d) : ���Ӽ���ͼ�����\n"), __FILE__, __LINE__);
        return FALSE;
    }
    Invalidate();
    
    return TRUE;
}

/*******************************************************************************************************
��������SetChairInfo
��  �ܣ�����������Ϣ���û�����ͷ��
��  ����
         LPCSTR lpszUserName���û���
         UINT uResID��λͼ��Դ��
����ֵ���ɹ����� TRUE�����򷵻� FALSE��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-2
ʱ  �䣺11:05:05
*******************************************************************************************************/
BOOL CChair::SetChairInfo(LPCSTR lpszUserName, UINT uResID)
{
    CString szChair;
    szChair.Format(_T("%d"), m_iChairNo);
    if(lpszUserName == NULL)
    {
        SetTransparence();
        SetToolTipText(szChair + _T("�ţ�������"));
    }
    else
    {
        m_szUserName = lpszUserName;
        SetToolTipText(lpszUserName);        
    }
    SetBitmap(uResID);
    Invalidate();

    return TRUE;
}

BEGIN_MESSAGE_MAP(CChair, CStaticEx)
    //{{AFX_MSG_MAP(CChair)
    ON_WM_LBUTTONUP()
    ON_WM_RBUTTONUP()
	//}}AFX_MSG_MAP
    ON_COMMAND(IDM_CHAIR_USERINFO, OnChairUserinfo)
    ON_COMMAND(IDM_CHAIR_SENDMESSAGE, OnChairSendmessage)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChair message handlers

void CChair::OnLButtonUp(UINT nFlags, CPoint point) 
{
    if(m_szUserName != "")
    {
        TRACE(_T("%s(%d) : ����λ������\n"), __FILE__, __LINE__);
        return;
    }
    CMainFrame* pwnd = (CMainFrame*)AfxGetMainWnd();
    if(pwnd->m_pChessView)
    {
        if(MessageBox(_T("�����������������壬�������������ԭ���������������������Ƿ�����������"),
            _T("��������"), MB_YESNO |MB_ICONWARNING ) == IDNO )
        {
            return;
        }
        pwnd->m_pChessView->Exit();        
    }
    if(!pwnd->ActiveOrCreateChess())
    {
        TRACE(_T("%s(%d) : ������ͼ����ʧ��\n"), __FILE__, __LINE__);
        return;
    }
    CChessApp* pApp = (CChessApp*) AfxGetApp();
    CCommand cmd;
    cmd.SetCommand(g_cmdSetDown);
    cmd.AddPara(pApp->m_gszUserName);
    cmd.AddPara(m_iChairNo);
    pwnd->m_pChessView->SendDataToServer(cmd);

    TRACE(_T("%s(%d) : CChair::LButtonUp\n"), __FILE__, __LINE__);
    CStaticEx::OnLButtonUp(nFlags, point);
}

void CChair::OnRButtonUp(UINT nFlags, CPoint point) 
{
    if(m_szUserName.IsEmpty())
    {
        return;
    }
    if(m_szUserName == "")
    {
        return;
    }
    CMenu menu;
    if (!menu.LoadMenu(IDM_CHAIR))
        return ;
    
    CMenu* pSubMenu = menu.GetSubMenu(0);
    if (!pSubMenu) 
        return ;
    
    // ʹ��һ���˵���Ŀ��Ĭ�ϵ�(������)
    ::SetMenuDefaultItem(pSubMenu->m_hMenu, 0, TRUE);
    
    CPoint mouse;
    GetCursorPos(&mouse);
    //::SetForegroundWindow(this->GetSafeHwnd());	
    ::TrackPopupMenu(pSubMenu->m_hMenu, 0, mouse.x, mouse.y, 0,
        this->GetSafeHwnd(), NULL);
    
    CStaticEx::OnRButtonUp(nFlags, point);
}

void CChair::OnChairUserinfo()
{
    ((CMainFrame* )AfxGetMainWnd())->m_TabCtrl.SetActivePage(0);
    ((CMainFrame * )AfxGetMainWnd())->m_UserInfo.FindUser(m_szUserName);
    ((CMainFrame* )AfxGetMainWnd())->m_TabCtrl.UpdateWindow();
}

void CChair::OnChairSendmessage()
{
    ((CMainFrame * )AfxGetMainWnd())->m_TabCtrl.SetActivePage(1);
    ((CMainFrame * )AfxGetMainWnd())->m_TextMessage.m_ctrUserName.SelectString(-1, m_szUserName);
    ((CMainFrame * )AfxGetMainWnd())->m_TextMessage.m_reSend.SetFocus();
}
