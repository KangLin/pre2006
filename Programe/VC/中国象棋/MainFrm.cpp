/*******************************************************************************************************
�ļ�����MainFrm.cpp
��  �ܣ������
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-12-18
ʱ  �䣺19:40:36

FileName��MainFrm.cpp
Compiler��Visual C++ 6.0
Author��  KangLin
          Copyright 2004 KangLin
Date��    2004-12-18
Time��    19:40:36
*******************************************************************************************************/
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "�й�����.h"

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
    //�������� ---��  ��--- ɾ���� 2004-12-16 : 13:50:51
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
    //�������� ---��  ��--- ɾ���� 2004-12-16 : 13:50:51
    //------------------------------------------------------------------------*/

    if (!m_wndStatusBar.Create(this) ||
        !m_wndStatusBar.SetIndicators(indicators,
          sizeof(indicators)/sizeof(UINT)))
    {
        TRACE0("Failed to create status bar\n");
        return -1;      // fail to create
    }

    m_wndStatusBar.SetPaneInfo(6, NULL, SBPS_NORMAL, 50);//����ʱ���
    SetTimer(0, 1000, NULL);//��ʾʱ��

    //------------------------------------------------------------------------
    //��������� ===������=== ���ܵ�����
    //

    INT i = 0, j = 0;
    m_ToolBar.CreateEx(this);

    m_ToolBar.SetButtonNumber(14); //���Ӱ�ť����ʱ,Ҫ�ı������

    m_ToolBar.SetImage();
    
    j = m_ToolBar.AddIcon(IDI_LOGON);  
    m_ToolBar.SetButton(i++, IDM_FILE_LOGON, j, _T("��¼"));
    j = m_ToolBar.AddIcon(IDI_EXIT);
    m_ToolBar.SetButton(i++, ID_APP_EXIT, j, _T("�˳�"));

    CBitmap bmp;
    bmp.LoadBitmap(IDB_HELP);
    j = m_ToolBar.AddBitmap(&bmp, RGB(255, 255, 255));
    m_ToolBar.SetButton(i++, ID_APP_ABOUT, j, _T("����"));
    
    m_ToolBar.AddSeparator(i++);    
    j = m_ToolBar.AddIcon(IDI_TEXTMESSAGE);
    m_ToolBar.SetButton(i++, IDM_TEXTMESSAGE, j, _T("��Ϣ"));

    bmp.Detach();
    bmp.LoadBitmap(IDB_DESKCHAIR);
    j = m_ToolBar.AddBitmap(&bmp, RGB(255, 255, 255));
    m_ToolBar.SetButton(i++, IDM_DESK, j, _T("����"));
    j = m_ToolBar.AddIcon(IDR_MAINFRAME);
    m_ToolBar.SetButton(i++, IDM_CHESS, j, _T("����"));
     
    m_ToolBar.AddSeparator(i++);
    bmp.Detach();
    bmp.LoadBitmap(IDB_START);
    j = m_ToolBar.AddBitmap(&bmp, RGB(255, 255, 255));
    m_ToolBar.SetButton(i++, IDM_CHESS_START, j, _T("��ʼ"));
    j = m_ToolBar.AddIcon(IDI_TIME);
    m_ToolBar.SetButton(i++, IDM_CHESS_SET, j, _T("����"));
    bmp.Detach();
    bmp.LoadBitmap(IDB_STANDOFF);
    j = m_ToolBar.AddBitmap(&bmp, RGB(255, 255, 255));
    m_ToolBar.SetButton(i++, IDM_CHESS_STANDOFF, j, _T("���"));
    bmp.Detach();
    bmp.LoadBitmap(IDB_GIVEUP);
    j = m_ToolBar.AddBitmap(&bmp, RGB(255, 255, 255));
    m_ToolBar.SetButton(i++, IDM_CHESS_GIVEUP, j, _T("����"));
    bmp.Detach();
    bmp.LoadBitmap(IDB_REPENT);
    j = m_ToolBar.AddBitmap(&bmp, RGB(255, 255, 255));
    m_ToolBar.SetButton(i++, IDM_CHESS_REPENT, j, _T("����"));
    bmp.Detach();
    bmp.LoadBitmap(IDB_STOP);
    j = m_ToolBar.AddBitmap(&bmp, RGB(255, 255, 255));
    m_ToolBar.SetButton(i++, IDM_CHESS_CLOSE, j, _T("����"));
    m_ToolBar.SetSize(40, 40);
    m_ToolBar.EnableDocking(CBRS_ALIGN_ANY);
    EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&m_ToolBar);

     //
    //��������� ===������=== ���ܵ�����
    //------------------------------------------------------------------------


    //------------------------------------------------------------------------
    //��������� ===������Ϣ���=== ���ܵ�����
    //

    CRect rect, DockRect;
    this->GetClientRect(&rect);
    if(!m_ControlBar.Create(_T("��Ϣ"), this, CSize(rect.Width() / 3, rect.Height() / 2), TRUE,0))
    {
        TRACE(_T("m_ControlBar.Createʧ��.\n"));
        return -1;
    }
    m_ControlBar.EnableDocking(CBRS_ALIGN_ANY);
    DockControlBar(&m_ControlBar, AFX_IDW_DOCKBAR_RIGHT);//ͣ�������

    m_TabCtrl.Create(WS_VISIBLE | WS_CHILD, CRect(0, 0, 0, 0), &m_ControlBar, NULL);

    m_UserInfo.Create(IDD_USERINFO, &m_TabCtrl);
    m_TabCtrl.AddPage(&m_UserInfo, _T("�û���Ϣ"));
    
    m_TextMessage.Create(IDD_TEXTMESSAGE, &m_TabCtrl);
    m_TextMessage.ShowWindow(SW_HIDE);
    m_TabCtrl.AddPage(&m_TextMessage, _T("������Ϣ"));
   
    m_Video.Create(IDD_VIDEO, &m_TabCtrl);
    m_TabCtrl.AddPage(&m_Video, _T("��Ƶ"));
  
    //�����ı���Ϣ�е��û����б��û���Ϣ��
    m_UserInfo.m_pUserName = &m_TextMessage.m_ctrUserName;
    m_UserInfo.m_pVideoUser = &m_Video.m_cmbUser;
   
    m_TabCtrl.UpdateWindow();

    //
    //��������� ===������Ϣ���=== ���ܵ�����
    //------------------------------------------------------------------------

    //Socket
    m_sckCommand.Inital(this, ReceiveThread, 0, FALSE);

#ifndef _DEBUG
    //��¼
    m_pLogon = new CLogonDlg;
    if(m_pLogon->DoModal() == IDCANCEL)
    {
        delete m_pLogon;
        return -1;
    }
    delete m_pLogon;
    m_pLogon = NULL;
#endif

    SetWindowText(_T("�й����� - ") + ((CChessApp * )AfxGetApp())->m_gszUserName); //���ô��ڱ���
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
��������Exit
��  �ܣ��������
��  ������
����ֵ���ɹ����� TRUE, ���򷵻� FALSE.
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-1
ʱ  �䣺20:01:36
*******************************************************************************************************/
BOOL CMainFrame::Exit()
{
    if(!((CChessApp*)AfxGetApp())->m_gszUserName.IsEmpty())
    {
        TRACE(_T("%s(%d) : �й�����ر�\n"), __FILE__, __LINE__);
        CCommand cmd;
        cmd.SetCommand(g_cmdExit);
        cmd.AddPara(((CChessApp*)AfxGetApp())->m_gszUserName);
        SendData(&cmd);
    }
    return TRUE;
}

/*******************************************************************************************************
��������GetView
��  �ܣ��õ�ָ����ͼ��ָ��
��  ����
         CRuntimeClass* pViewClass����ͼ��
����ֵ���ɹ�������ͼ��ָ�룬ʧ�ܷ���NULL
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-31
ʱ  �䣺18:28:45
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
��������ActiveOrCreateChess
��  �ܣ������򼤻�������ͼ��
��  ������
����ֵ���ɹ�����TRUE,���򷵻�FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-3
ʱ  �䣺16:49:19
*******************************************************************************************************/
BOOL CMainFrame::ActiveOrCreateChess()
{
    m_iView = CHESS_ENUM;
    return CreateOrActive(((CChessApp*)AfxGetApp())->m_ChessDocTemp, RUNTIME_CLASS(CChessView));
}

/*******************************************************************************************************
��������CreateOrActive
��  �ܣ������򼤻���ͼ�������ͼ�ѽ����򼤻��������
��  ����
         CDocTemplate* pTemplate���ĵ�ģ��
         CRuntimeClass* pViewClass��Ҫ�����򼤻����ͼ
����ֵ���ɹ�����TRUE,���򷵻�FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-16
ʱ  �䣺15:13:33
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
��������SetServerAddress
��  �ܣ����÷������ĵ�ַ�Ͷ˿�,��CLogonDlg������
��  ����
         CString szServerIP����������IP
         UINT uServerPort����������Port
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-23
ʱ  �䣺14:32:25
*******************************************************************************************************/
void CMainFrame::SetServerAddress(CString szServerIP, UINT uServerPort)
{
    m_szServerIP = szServerIP;
    m_uServerPort = uServerPort;
}

/*******************************************************************************************************
��������GetServerAddress
��  �ܣ��õ���������ַ
��  ����
         CString &szServerIP��������IP
         UINT &uServerPort��������Port
����ֵ���ɹ����� TRUE,ʧ�ܷ��� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-3
ʱ  �䣺10:51:33
*******************************************************************************************************/
BOOL CMainFrame::GetServerAddress(CString* szServerIP, UINT* uServerPort)
{
    if(m_szServerIP.IsEmpty())
    {
        TRACE(_T("%s(%d) : ��������ַδ����\n"), __FILE__, __LINE__);
        return FALSE;
    }
    if(m_szServerIP == "")
    {
        TRACE(_T("%s(%d) : ��������ַδ����\n"), __FILE__, __LINE__);
        return FALSE;
    }
    
    *szServerIP = m_szServerIP;
    *uServerPort = m_uServerPort;
    return TRUE;
}

/*******************************************************************************************************
��������SendData
��  �ܣ����������������
��  ����
         LPVOID lpData��Ҫ���͵�����
         UINT iLen��Ҫ���͵����ݵĳ���
����ֵ���ɹ����� TRUE,���򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-23
ʱ  �䣺14:31:35
*******************************************************************************************************/
BOOL CMainFrame::SendData(LPVOID lpData, UINT iLen)
{
    return m_sckCommand.SendDataTo(lpData, iLen, m_uServerPort, m_szServerIP);
}

/*******************************************************************************************************
��������SendData
��  �ܣ����������������
��  ����
         CCommand *pcmd���������
����ֵ���ɹ����� TRUE,���򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-29
ʱ  �䣺19:33:34
*******************************************************************************************************/
BOOL CMainFrame::SendData(CCommand *pcmd)
{
    return SendData(pcmd->GetDataRef(), pcmd->GetLength());
}

/*******************************************************************************************************
��������ReceiveThread
��  �ܣ�������������߳�
��  ����
         LPVOID lpParameter������
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-28
ʱ  �䣺15:33:30
*******************************************************************************************************/
DWORD _stdcall CMainFrame::ReceiveThread(LPVOID lpParameter)
{
    TRACE(_T("%s(%d) : CMainFrame::ReceiveThread,�̺߳�:%x\n"), __FILE__, __LINE__, ::GetCurrentThreadId());
    UDPSOCKREMOTEINFO* p = (UDPSOCKREMOTEINFO*)lpParameter;
    CString szRemoteIP(p->szRemoteIP);
    UINT uRemotePort = p->uRemotePort;
    CCommand command(p->pBuf, p->iLen);            //�����������
    CMainFrame* pParent = (CMainFrame*) p->pParent;//ת���ɸ�����ָ��
    ::SetEvent(*(p->phEvent));

    //����:���յ��������
    long cmd;
    cmd = command.GetCommand();
    switch(cmd)
    {
    case g_cmdSetDown:          //����
        pParent->m_pChessView->SetDown(command);
        break;
    case g_cmdOtherSetDown:     //�Է�����
        pParent->m_pChessView->OtherSetDown(command);
        break;
    case g_cmdStart:            //ͬ�⿪ʼ����
        if(pParent->m_pChessView)
        {
            pParent->m_pChessView->Start(command);
        }
        break;
    case g_cmdPlayChess:        //ͬ�⿪ʼ����
        pParent->m_pChessView->PlayChess(command);
        break;
    case g_cmdReceiveGiveup:    //�Է�����
        if(pParent->m_pChessView)
        {
            pParent->m_pChessView->ReceiveGiveup(command);
        } //���� if(pParent->m_pChessView)
        break;
    case g_cmdExit:             //�û��˳�����
        pParent->m_UserInfo.DeleteUserInfo(&command);
        if(pParent->m_pChessView)
        {
            pParent->m_pChessView->OtherExit(command);
        }
        break;
    case g_cmdLogon:
        if(pParent->m_pLogon)   //������ʾ��¼�Ի���
        {
            pParent->m_pLogon->Receive(&command);
        }
        break;
    case g_cmdUserInfoHead:     //�û���Ϣͷ
        pParent->m_UserInfo.SetListHead(&command);
        break;
    case  g_cmdUserInfo:        //�û�����Ϣ
        pParent->m_UserInfo.AddUserInfo(&command);
        break;
    case g_cmdChairInfo:        //������Ϣ
        if(pParent->m_pDeskView)
        {
            pParent->m_pDeskView->SetChair(&command);
        }
        break;
    case g_cmdLeaveChair:       //�뿪����
        if(pParent->m_pChessView)
        {
            pParent->m_pChessView->LeaveChair(command);
        }
        break;
    case g_cmdRegist:           //ע��
        if(pParent->m_pLogon)
        {
            pParent->m_pLogon->RegistReceive(&command);
        }
        break;
    case g_cmdSendTextMessage:  //�����ı���Ϣ
        pParent->m_TextMessage.SetReceiveText(command.GetPara());
        break;
    case g_cmdVideoConn:        //������Ƶ����
        pParent->m_Video.VideoConnect(command);
        break;
    case g_cmdAudioConn:        //������Ƶ����
        pParent->m_Video.AudioConnect(command);
        break;
    case g_cmdAgreeVideoConn:   //ͬ����Ƶ����
        pParent->m_Video.StartVideo(command);
        break;
    case g_cmdAgreeAudioConn:   //ͬ����Ƶ����
        pParent->m_Video.StartAudio(command);
        break;
    case g_cmdNoVideo:          //��ͬ��������Ƶ
        pParent->m_Video.NoVideo(command);
        break;
    case g_cmdNoAudio:          //��ͬ��������Ƶ
        pParent->m_Video.NoAudio(command);
        break;
    }

    return 0;
}
