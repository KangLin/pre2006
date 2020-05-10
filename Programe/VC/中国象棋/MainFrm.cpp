/*******************************************************************************************************
文件名：MainFrm.cpp
功  能：主框架
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-12-18
时  间：19:40:36

FileName：MainFrm.cpp
Compiler：Visual C++ 6.0
Author：  KangLin
          Copyright 2004 KangLin
Date：    2004-12-18
Time：    19:40:36
*******************************************************************************************************/
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "中国象棋.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CMDIFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CMDIFrameWnd)
    //{{AFX_MSG_MAP(CMainFrame)
    ON_WM_CREATE()
    ON_COMMAND(IDM_CHESS, OnChess)
    ON_COMMAND(IDM_DESK, OnDesk)
    ON_UPDATE_COMMAND_UI(IDM_CHESS, OnUpdateChess)
    ON_COMMAND(IDM_TEXTMESSAGE, OnTextmessage)
    ON_UPDATE_COMMAND_UI(IDM_TEXTMESSAGE, OnUpdateTextmessage)
    ON_WM_TIMER()
    ON_UPDATE_COMMAND_UI(IDM_DESK, OnUpdateDesk)
    ON_COMMAND(IDM_FILE_LOGON, OnFileLogon)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
    ID_SEPARATOR,           // status line indicator
    ID_INDICATOR_CAPS,
    ID_INDICATOR_NUM,
    ID_INDICATOR_SCRL,
    ID_INDICATOR_OVR,
    ID_INDICATOR_REC,
    ID_SEPARATOR,           // status line indicator
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
    // TODO: add member initialization code here
    m_pLogon = NULL;
    m_pDeskView = NULL;
    m_pChessView = NULL;
    m_iView = DESK_ENUM;
}

CMainFrame::~CMainFrame()
{
#ifdef _DEBUG
    Sleep(500);
#else
    Sleep(3000);
#endif
    TRACE(_T("%s(%d) : CMainFrame::~CMainFrame\n"), __FILE__, __LINE__);
    m_sckCommand.Close();
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CMDIFrameWnd::OnCreate(lpCreateStruct) == -1)
        return -1;
   
    /*------------------------------------------------------------------------
    //以下是由 ---康  林--- 删除于 2004-12-16 : 13:50:51
    //

    if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
        | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
        !m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
    {
        TRACE0("Failed to create toolbar\n");
        return -1;      // fail to create
    }
    m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
    EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&m_wndToolBar);
    //
    //以上是由 ---康  林--- 删除于 2004-12-16 : 13:50:51
    //------------------------------------------------------------------------*/

    if (!m_wndStatusBar.Create(this) ||
        !m_wndStatusBar.SetIndicators(indicators,
          sizeof(indicators)/sizeof(UINT)))
    {
        TRACE0("Failed to create status bar\n");
        return -1;      // fail to create
    }

    m_wndStatusBar.SetPaneInfo(6, NULL, SBPS_NORMAL, 50);//设置时间格
    SetTimer(0, 1000, NULL);//显示时间

    //------------------------------------------------------------------------
    //以下是完成 ===工具条=== 功能的语句块
    //

    INT i = 0, j = 0;
    m_ToolBar.CreateEx(this);

    m_ToolBar.SetButtonNumber(14); //增加按钮个数时,要改变其参数

    m_ToolBar.SetImage();
    
    j = m_ToolBar.AddIcon(IDI_LOGON);  
    m_ToolBar.SetButton(i++, IDM_FILE_LOGON, j, _T("登录"));
    j = m_ToolBar.AddIcon(IDI_EXIT);
    m_ToolBar.SetButton(i++, ID_APP_EXIT, j, _T("退出"));

    CBitmap bmp;
    bmp.LoadBitmap(IDB_HELP);
    j = m_ToolBar.AddBitmap(&bmp, RGB(255, 255, 255));
    m_ToolBar.SetButton(i++, ID_APP_ABOUT, j, _T("关于"));
    
    m_ToolBar.AddSeparator(i++);    
    j = m_ToolBar.AddIcon(IDI_TEXTMESSAGE);
    m_ToolBar.SetButton(i++, IDM_TEXTMESSAGE, j, _T("信息"));

    bmp.Detach();
    bmp.LoadBitmap(IDB_DESKCHAIR);
    j = m_ToolBar.AddBitmap(&bmp, RGB(255, 255, 255));
    m_ToolBar.SetButton(i++, IDM_DESK, j, _T("桌子"));
    j = m_ToolBar.AddIcon(IDR_MAINFRAME);
    m_ToolBar.SetButton(i++, IDM_CHESS, j, _T("象棋"));
     
    m_ToolBar.AddSeparator(i++);
    bmp.Detach();
    bmp.LoadBitmap(IDB_START);
    j = m_ToolBar.AddBitmap(&bmp, RGB(255, 255, 255));
    m_ToolBar.SetButton(i++, IDM_CHESS_START, j, _T("开始"));
    j = m_ToolBar.AddIcon(IDI_TIME);
    m_ToolBar.SetButton(i++, IDM_CHESS_SET, j, _T("设置"));
    bmp.Detach();
    bmp.LoadBitmap(IDB_STANDOFF);
    j = m_ToolBar.AddBitmap(&bmp, RGB(255, 255, 255));
    m_ToolBar.SetButton(i++, IDM_CHESS_STANDOFF, j, _T("求和"));
    bmp.Detach();
    bmp.LoadBitmap(IDB_GIVEUP);
    j = m_ToolBar.AddBitmap(&bmp, RGB(255, 255, 255));
    m_ToolBar.SetButton(i++, IDM_CHESS_GIVEUP, j, _T("认输"));
    bmp.Detach();
    bmp.LoadBitmap(IDB_REPENT);
    j = m_ToolBar.AddBitmap(&bmp, RGB(255, 255, 255));
    m_ToolBar.SetButton(i++, IDM_CHESS_REPENT, j, _T("悔棋"));
    bmp.Detach();
    bmp.LoadBitmap(IDB_STOP);
    j = m_ToolBar.AddBitmap(&bmp, RGB(255, 255, 255));
    m_ToolBar.SetButton(i++, IDM_CHESS_CLOSE, j, _T("结束"));
    m_ToolBar.SetSize(40, 40);
    m_ToolBar.EnableDocking(CBRS_ALIGN_ANY);
    EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&m_ToolBar);

     //
    //以上是完成 ===工具条=== 功能的语句块
    //------------------------------------------------------------------------


    //------------------------------------------------------------------------
    //以下是完成 ===设置信息框架=== 功能的语句块
    //

    CRect rect, DockRect;
    this->GetClientRect(&rect);
    if(!m_ControlBar.Create(_T("信息"), this, CSize(rect.Width() / 3, rect.Height() / 2), TRUE,0))
    {
        TRACE(_T("m_ControlBar.Create失败.\n"));
        return -1;
    }
    m_ControlBar.EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&m_ControlBar, AFX_IDW_DOCKBAR_RIGHT);//停靠在左边

    m_TabCtrl.Create(WS_VISIBLE | WS_CHILD, CRect(0, 0, 0, 0), &m_ControlBar, NULL);

    m_UserInfo.Create(IDD_USERINFO, &m_TabCtrl);
    m_TabCtrl.AddPage(&m_UserInfo, _T("用户信息"));
    
    m_TextMessage.Create(IDD_TEXTMESSAGE, &m_TabCtrl);
    m_TextMessage.ShowWindow(SW_HIDE);
    m_TabCtrl.AddPage(&m_TextMessage, _T("发送消息"));
   
    m_Video.Create(IDD_VIDEO, &m_TabCtrl);
    m_TabCtrl.AddPage(&m_Video, _T("视频"));
  
    //设置文本信息中的用户名列表到用户信息中
    m_UserInfo.m_pUserName = &m_TextMessage.m_ctrUserName;
    m_UserInfo.m_pVideoUser = &m_Video.m_cmbUser;
   
    m_TabCtrl.UpdateWindow();

    //
    //以上是完成 ===设置信息框架=== 功能的语句块
    //------------------------------------------------------------------------

    //Socket
    m_sckCommand.Inital(this, ReceiveThread, 0, FALSE);

#ifndef _DEBUG
    //登录
    m_pLogon = new CLogonDlg;
    if(m_pLogon->DoModal() == IDCANCEL)
    {
        delete m_pLogon;
        return -1;
    }
    delete m_pLogon;
    m_pLogon = NULL;
#endif

    SetWindowText(_T("中国象棋 - ") + ((CChessApp * )AfxGetApp())->m_gszUserName); //设置窗口标题
    return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
    if( !CMDIFrameWnd::PreCreateWindow(cs) )
        return FALSE;
    // TODO: Modify the Window class or styles here by modifying
    //  the CREATESTRUCT cs

    cs.style = WS_OVERLAPPED | WS_CAPTION /*| FWS_ADDTOTITLE*/
        | WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

    return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
    CMDIFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
    CMDIFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers

void CMainFrame::OnTimer(UINT nIDEvent) 
{
    m_wndStatusBar.SetPaneText(6, CTime::GetCurrentTime().Format(_T("%H:%M:%S")));
    CMDIFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::OnTextmessage() 
{
    this->ShowControlBar(&m_ControlBar, !m_ControlBar.IsWindowVisible(), FALSE);
}

void CMainFrame::OnUpdateTextmessage(CCmdUI* pCmdUI) 
{
    pCmdUI->SetCheck(m_ControlBar.IsWindowVisible());    
}

void CMainFrame::OnChess() 
{
    ActiveOrCreateChess();
}

void CMainFrame::OnUpdateChess(CCmdUI* pCmdUI) 
{
    if(m_iView != CHESS_ENUM)
    {
        pCmdUI->SetCheck(FALSE);
    }
    else
    {
        pCmdUI->SetCheck();
    }
    m_pChessView ? pCmdUI->Enable() : pCmdUI->Enable(FALSE);
}

void CMainFrame::OnDesk() 
{
    CreateOrActive(((CChessApp*)AfxGetApp())->m_DeskDocTemp, RUNTIME_CLASS(CDeskView));    
    m_iView = DESK_ENUM;
}

void CMainFrame::OnUpdateDesk(CCmdUI* pCmdUI) 
{
    if(m_iView != DESK_ENUM)
    {
        pCmdUI->SetCheck(FALSE);
    }
    else
    {
        pCmdUI->SetCheck();
    }
}

void CMainFrame::OnClose() 
{
    Exit();
  	CMDIFrameWnd::OnClose();
}

void CMainFrame::OnFileLogon() 
{
    // TODO: Add your command handler code here
    Exit();
    m_pLogon = new CLogonDlg;
    if(m_pLogon->DoModal() == IDCANCEL)
    {
        delete m_pLogon;
        SendMessage(WM_CLOSE);
        return;
    }
    delete m_pLogon;
    m_pLogon = NULL;
}

/*******************************************************************************************************
函数名：Exit
功  能：程序结束
参  数：无
返回值：成功返回 TRUE, 否则返回 FALSE.
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-1
时  间：20:01:36
*******************************************************************************************************/
BOOL CMainFrame::Exit()
{
    if(!((CChessApp*)AfxGetApp())->m_gszUserName.IsEmpty())
    {
        TRACE(_T("%s(%d) : 中国象棋关闭\n"), __FILE__, __LINE__);
        CCommand cmd;
        cmd.SetCommand(g_cmdExit);
        cmd.AddPara(((CChessApp*)AfxGetApp())->m_gszUserName);
        SendData(&cmd);
    }
    return TRUE;
}

/*******************************************************************************************************
函数名：GetView
功  能：得到指定视图的指针
参  数：
         CRuntimeClass* pViewClass：视图类
返回值：成功返回视图类指针，失败返回NULL
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-31
时  间：18:28:45
*******************************************************************************************************/
CView* CMainFrame::GetView(CRuntimeClass* pViewClass)
{
    CMDIChildWnd* pMDIActive = MDIGetActive();
    ASSERT(pMDIActive != NULL);
    CDocument* pDoc = pMDIActive->GetActiveDocument();
    ASSERT(pDoc != NULL);

    CView* pView;
    POSITION pos = pDoc->GetFirstViewPosition();
    while (pos != NULL)
    {
        pView = pDoc->GetNextView(pos);
        if (pView->IsKindOf(pViewClass))
        {
            return pView;
        }
    }
    return NULL;
}

/*******************************************************************************************************
函数名：ActiveOrCreateChess
功  能：建立或激活象棋视图。
参  数：无
返回值：成功返回TRUE,否则返回FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-3
时  间：16:49:19
*******************************************************************************************************/
BOOL CMainFrame::ActiveOrCreateChess()
{
    m_iView = CHESS_ENUM;
    return CreateOrActive(((CChessApp*)AfxGetApp())->m_ChessDocTemp, RUNTIME_CLASS(CChessView));
}

/*******************************************************************************************************
函数名：CreateOrActive
功  能：建立或激活视图。如果视图已建立则激活，否则建立。
参  数：
         CDocTemplate* pTemplate：文档模板
         CRuntimeClass* pViewClass：要建立或激活的视图
返回值：成功返回TRUE,否则返回FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-16
时  间：15:13:33
*******************************************************************************************************/
BOOL CMainFrame::CreateOrActive(CDocTemplate* pTemplate,
    CRuntimeClass* pViewClass)
{
    CMDIChildWnd* pMDIActive = MDIGetActive();
    ASSERT(pMDIActive != NULL);
    CDocument* pDoc = pMDIActive->GetActiveDocument();
    ASSERT(pDoc != NULL);

    CView* pView;
    POSITION pos = pDoc->GetFirstViewPosition();
    while (pos != NULL)
    {
        pView = pDoc->GetNextView(pos);
        if (pView->IsKindOf(pViewClass))
        {
            pView->GetParentFrame()->ActivateFrame();
            return TRUE;
        }
    }

    CMDIChildWnd* pNewFrame
        = (CMDIChildWnd*)(pTemplate->CreateNewFrame(pDoc, NULL));
    if (pNewFrame == NULL)
        return FALSE;     // not created
    ASSERT_KINDOF(CMDIChildWnd, pNewFrame);
    pTemplate->InitialUpdateFrame(pNewFrame, pDoc);
    MDITile(MDITILE_HORIZONTAL);
    pNewFrame->ActivateFrame();
    return TRUE;
}

/*******************************************************************************************************
函数名：SetServerAddress
功  能：设置服务器的地址和端口,在CLogonDlg中设置
参  数：
         CString szServerIP：服务器的IP
         UINT uServerPort：服务器的Port
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-23
时  间：14:32:25
*******************************************************************************************************/
void CMainFrame::SetServerAddress(CString szServerIP, UINT uServerPort)
{
    m_szServerIP = szServerIP;
    m_uServerPort = uServerPort;
}

/*******************************************************************************************************
函数名：GetServerAddress
功  能：得到服务器地址
参  数：
         CString &szServerIP：服务器IP
         UINT &uServerPort：服务器Port
返回值：成功返回 TRUE,失败返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-3
时  间：10:51:33
*******************************************************************************************************/
BOOL CMainFrame::GetServerAddress(CString* szServerIP, UINT* uServerPort)
{
    if(m_szServerIP.IsEmpty())
    {
        TRACE(_T("%s(%d) : 服务器地址未设置\n"), __FILE__, __LINE__);
        return FALSE;
    }
    if(m_szServerIP == "")
    {
        TRACE(_T("%s(%d) : 服务器地址未设置\n"), __FILE__, __LINE__);
        return FALSE;
    }
    
    *szServerIP = m_szServerIP;
    *uServerPort = m_uServerPort;
    return TRUE;
}

/*******************************************************************************************************
函数名：SendData
功  能：向服务器发送数据
参  数：
         LPVOID lpData：要发送的数据
         UINT iLen：要发送的数据的长度
返回值：成功返回 TRUE,否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-23
时  间：14:31:35
*******************************************************************************************************/
BOOL CMainFrame::SendData(LPVOID lpData, UINT iLen)
{
    return m_sckCommand.SendDataTo(lpData, iLen, m_uServerPort, m_szServerIP);
}

/*******************************************************************************************************
函数名：SendData
功  能：向服务器发送数据
参  数：
         CCommand *pcmd：命令对象
返回值：成功返回 TRUE,否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-29
时  间：19:33:34
*******************************************************************************************************/
BOOL CMainFrame::SendData(CCommand *pcmd)
{
    return SendData(pcmd->GetDataRef(), pcmd->GetLength());
}

/*******************************************************************************************************
函数名：ReceiveThread
功  能：处理接收数据线程
参  数：
         LPVOID lpParameter：参数
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-28
时  间：15:33:30
*******************************************************************************************************/
DWORD _stdcall CMainFrame::ReceiveThread(LPVOID lpParameter)
{
    TRACE(_T("%s(%d) : CMainFrame::ReceiveThread,线程号:%x\n"), __FILE__, __LINE__, ::GetCurrentThreadId());
    UDPSOCKREMOTEINFO* p = (UDPSOCKREMOTEINFO*)lpParameter;
    CString szRemoteIP(p->szRemoteIP);
    UINT uRemotePort = p->uRemotePort;
    CCommand command(p->pBuf, p->iLen);            //设置命令对象
    CMainFrame* pParent = (CMainFrame*) p->pParent;//转换成父窗口指针
    ::SetEvent(*(p->phEvent));

    //增加:接收到的命令处理
    long cmd;
    cmd = command.GetCommand();
    switch(cmd)
    {
    case g_cmdSetDown:          //入坐
        pParent->m_pChessView->SetDown(command);
        break;
    case g_cmdOtherSetDown:     //对方入坐
        pParent->m_pChessView->OtherSetDown(command);
        break;
    case g_cmdStart:            //同意开始下棋
        if(pParent->m_pChessView)
        {
            pParent->m_pChessView->Start(command);
        }
        break;
    case g_cmdPlayChess:        //同意开始下棋
        pParent->m_pChessView->PlayChess(command);
        break;
    case g_cmdReceiveGiveup:    //对方认输
        if(pParent->m_pChessView)
        {
            pParent->m_pChessView->ReceiveGiveup(command);
        } //结束 if(pParent->m_pChessView)
        break;
    case g_cmdExit:             //用户退出程序
        pParent->m_UserInfo.DeleteUserInfo(&command);
        if(pParent->m_pChessView)
        {
            pParent->m_pChessView->OtherExit(command);
        }
        break;
    case g_cmdLogon:
        if(pParent->m_pLogon)   //正在显示登录对话框
        {
            pParent->m_pLogon->Receive(&command);
        }
        break;
    case g_cmdUserInfoHead:     //用户信息头
        pParent->m_UserInfo.SetListHead(&command);
        break;
    case  g_cmdUserInfo:        //用户的信息
        pParent->m_UserInfo.AddUserInfo(&command);
        break;
    case g_cmdChairInfo:        //椅子信息
        if(pParent->m_pDeskView)
        {
            pParent->m_pDeskView->SetChair(&command);
        }
        break;
    case g_cmdLeaveChair:       //离开椅子
        if(pParent->m_pChessView)
        {
            pParent->m_pChessView->LeaveChair(command);
        }
        break;
    case g_cmdRegist:           //注册
        if(pParent->m_pLogon)
        {
            pParent->m_pLogon->RegistReceive(&command);
        }
        break;
    case g_cmdSendTextMessage:  //发送文本消息
        pParent->m_TextMessage.SetReceiveText(command.GetPara());
        break;
    case g_cmdVideoConn:        //请求视频连接
        pParent->m_Video.VideoConnect(command);
        break;
    case g_cmdAudioConn:        //请求音频连接
        pParent->m_Video.AudioConnect(command);
        break;
    case g_cmdAgreeVideoConn:   //同意视频连接
        pParent->m_Video.StartVideo(command);
        break;
    case g_cmdAgreeAudioConn:   //同意音频连接
        pParent->m_Video.StartAudio(command);
        break;
    case g_cmdNoVideo:          //不同意连接视频
        pParent->m_Video.NoVideo(command);
        break;
    case g_cmdNoAudio:          //不同意连接音频
        pParent->m_Video.NoAudio(command);
        break;
    }

    return 0;
}
