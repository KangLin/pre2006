/*******************************************************************************************************
文件名：desk.cpp
功  能：实现桌子、椅子
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2005-1-2
时  间：11:16:10

FileName：desk.cpp
Function：
Compiler：Visual C++ 6.0
Author：  KangLin
          Copyright 2005 KangLin
Date：    2005-1-2
Time：    11:16:10
*******************************************************************************************************/
// desk.cpp : implementation file
//

#include "stdafx.h"
#include "..\中国象棋.h"
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
    CBitmap m_bmpDesk;  //桌面图片
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
                   _T("桌子"), 
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
函数名：SetLeftUser
功  能：设置左边椅子的用户名和形象图片
参  数：
         LPCSTR lpszUserName：左边椅子的用户名,默认为NULL,提示文字为请入座.
         HICON hIcon：形象图片,默认为NULL,为椅子图片.
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-18
时  间：9:27:28
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
        //因为本类是从CStaticEx派生的,当为透明时,不重绘背景,所以要其父窗口重绘
        CRect rect;
        GetWindowRect(&rect);
        this->GetParent()->ScreenToClient(&rect);
        this->GetParent()->InvalidateRect(&rect);
    }
    else
    {
        TRACE(_T("%s(%d) : 左边椅子加载图标出错\n"), __FILE__, __LINE__);
        return FALSE;
    }
    return TRUE;
}

/*******************************************************************************************************
函数名：SetLeftUser
功  能：设置左边椅子的用户名和形象图片
参  数：
         LPCSTR lpszUserName：左边椅子的用户名,默认为NULL,提示文字为请入座.
         CString szFile：图片的文件路径
返回值：成功返回 TRUE，否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-31
时  间：20:20:38
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
        //因为本类是从CStaticEx派生的,当为透明时,不重绘背景,所以要其父窗口重绘
        CRect rect;
        GetWindowRect(&rect);
        this->GetParent()->ScreenToClient(&rect);
        this->GetParent()->InvalidateRect(&rect);
    }
    else
    {
        TRACE(_T("%s(%d) : 左边椅子加载图标出错\n"), __FILE__, __LINE__);
        return FALSE;
    }
    return TRUE;
}

/*******************************************************************************************************
函数名：SetRightUser
功  能：设置右边椅子的用户名和形象图片
参  数：
         LPCSTR lpszUserName：右边椅子的用户名,默认为NULL,提示文字为请入座.
         CString szFile：图片文件的路径
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-31
时  间：20:21:37
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
        //因为本类是从CStaticEx派生的,当为透明时,不重绘背景,所以要其父窗口重绘
        CRect rect;
        GetWindowRect(&rect);
        this->GetParent()->ScreenToClient(&rect);
        this->GetParent()->InvalidateRect(&rect);
    }
    else
    {
        TRACE(_T("%s(%d) : 右边椅子加载图标出错\n"), __FILE__, __LINE__);
        return FALSE;
    }
    return TRUE;
}

/*******************************************************************************************************
函数名：SetRightUser
功  能：设置右边椅子的用户名和形象图片
参  数：
         LPCSTR lpszUserName：右边椅子的用户名,默认为NULL,提示文字为请入座.
         HICON hIcon：形象图片,默认为NULL,为椅子图片.
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-18
时  间：9:24:07
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
        //因为本类是从CStaticEx派生的,当为透明时,不重绘背景,所以要其父窗口重绘
        CRect rect;
        GetWindowRect(&rect);
        this->GetParent()->ScreenToClient(&rect);
        this->GetParent()->InvalidateRect(&rect);
    }
    else
    {
        TRACE(_T("%s(%d) : 右边椅子加载图标出错\n"), __FILE__, __LINE__);
        return FALSE;
    }
    return TRUE;
}

/*******************************************************************************************************
函数名：SetDeskText
功  能：设置桌子的ToolTip文字
参  数：
         LPCSTR lpszText：ToolTip文字
返回值：TRUE
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-18
时  间：9:23:34
*******************************************************************************************************/
BOOL CDesk::SetDeskText(LPCSTR lpszText)
{
    if(lpszText == NULL)
    {
        CString str;
        str.Format(_T("%d号桌子"), m_DeskNo);
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
            TRACE(_T("%s(%d) : 椅子加载图标出错\n"), __FILE__, __LINE__);
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
            TRACE(_T("%s(%d) : 椅子加载图标出错\n"), __FILE__, __LINE__);
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
函数名：SetDeskNumber
功  能：设置桌子号,这个函数要在 Create 前调用.
参  数：
         int iDeskNum：桌子号
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-19
时  间：21:30:25
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
函数名：SetChairNo
功  能：设置椅子号
参  数：
         int No：椅子号
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-2
时  间：9:53:53
*******************************************************************************************************/
BOOL CChair::SetChairNo(int No)
{
    m_iChairNo = No;
    return TRUE;
}

/*******************************************************************************************************
函数名：SetChairInfo
功  能：设置椅子信息。用户名、头像
参  数：
         LPCSTR lpszUserName：用户名
         LPCSTR lpszImageFile：头像文件名
返回值：成功返回 TRUE，否则返回 FALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-2
时  间：10:49:03
*******************************************************************************************************/
BOOL CChair::SetChairInfo(LPCSTR lpszUserName, LPCSTR lpszImageFile)
{
    ASSERT(lpszImageFile);
    CString szChair;
    szChair.Format(_T("%d"), m_iChairNo);
    if(lpszUserName == NULL)
    {
        SetTransparence();
        SetToolTipText(szChair + _T("号，请入座"));
    }
    else
    {
        m_szUserName = lpszUserName;
        SetToolTipText(lpszUserName);
    }
    
    if(!m_BKPicture.Load(lpszImageFile))
    {
        TRACE(_T("%s(%d) : 椅子加载图片文件错误\n"), __FILE__, __LINE__);
        return FALSE;
    }
    this->Invalidate();   
    return TRUE;
}

/*******************************************************************************************************
函数名：SetChairInfo
功  能：设置椅子信息。用户名、头像
参  数：
         LPCSTR lpszUserName：用户名
         HICON hIcon：头像图标句柄
返回值：成功返回 TRUE，否则返回 FALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-2
时  间：10:48:59
*******************************************************************************************************/
BOOL CChair::SetChairInfo(LPCSTR lpszUserName, HICON hIcon)
{
    ASSERT(hIcon);
    CString szChair;
    szChair.Format(_T("%d"), m_iChairNo);
    if(lpszUserName == NULL)
    {
        SetTransparence();
        SetToolTipText(szChair + _T("号，请入座"));
    }
    else
    {
        m_szUserName = lpszUserName;
        SetToolTipText(lpszUserName);
    }
    if(!m_BKPicture.CreateFromIcon(hIcon))
    {
        TRACE(_T("%s(%d) : 椅子加载图标出错\n"), __FILE__, __LINE__);
        return FALSE;
    }
    Invalidate();
    
    return TRUE;
}

/*******************************************************************************************************
函数名：SetChairInfo
功  能：设置椅子信息。用户名、头像
参  数：
         LPCSTR lpszUserName：用户名
         UINT uResID：位图资源号
返回值：成功返回 TRUE，否则返回 FALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-2
时  间：11:05:05
*******************************************************************************************************/
BOOL CChair::SetChairInfo(LPCSTR lpszUserName, UINT uResID)
{
    CString szChair;
    szChair.Format(_T("%d"), m_iChairNo);
    if(lpszUserName == NULL)
    {
        SetTransparence();
        SetToolTipText(szChair + _T("号，请入座"));
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
        TRACE(_T("%s(%d) : 此座位已有人\n"), __FILE__, __LINE__);
        return;
    }
    CMainFrame* pwnd = (CMainFrame*)AfxGetMainWnd();
    if(pwnd->m_pChessView)
    {
        if(MessageBox(_T("你已入坐，正在下棋，如果重新入坐，原来的棋局以你认输结束。是否重新入坐？"),
            _T("重新入坐"), MB_YESNO |MB_ICONWARNING ) == IDNO )
        {
            return;
        }
        pwnd->m_pChessView->Exit();        
    }
    if(!pwnd->ActiveOrCreateChess())
    {
        TRACE(_T("%s(%d) : 象棋视图建立失败\n"), __FILE__, __LINE__);
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
    
    // 使第一个菜单项目是默认的(粗体字)
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
