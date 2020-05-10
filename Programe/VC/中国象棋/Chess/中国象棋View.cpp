// 中国象棋View.cpp : implementation of the CChessView class
//

#include "stdafx.h"
#include "..\中国象棋.h"
#include "..\MainFrm.h"
#include "..\中国象棋Doc.h"
#include "中国象棋View.h"
#include "..\SetDlg\SetDlg.h"
#include "..\ShowResult\ShowResult.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChessView

IMPLEMENT_DYNCREATE(CChessView, CFormView)

BEGIN_MESSAGE_MAP(CChessView, CFormView)
	//{{AFX_MSG_MAP(CChessView)
	ON_WM_CREATE()
	ON_COMMAND(IDM_CHESS_CLOSE, OnChessClose)
	ON_COMMAND(IDM_CHESS_GIVEUP, OnChessGiveup)
	ON_COMMAND(IDM_CHESS_REPENT, OnChessRepent)
	ON_COMMAND(IDM_CHESS_SET, OnChessSet)
	ON_COMMAND(IDM_CHESS_STANDOFF, OnChessStandoff)
	ON_COMMAND(IDM_CHESS_START, OnChessStart)
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_UPDATE_COMMAND_UI(IDM_CHESS_GIVEUP, OnUpdateChessGiveup)
	ON_UPDATE_COMMAND_UI(IDM_CHESS_REPENT, OnUpdateChessRepent)
	ON_UPDATE_COMMAND_UI(IDM_CHESS_SET, OnUpdateChessSet)
	ON_UPDATE_COMMAND_UI(IDM_CHESS_STANDOFF, OnUpdateChessStandoff)
	ON_UPDATE_COMMAND_UI(IDM_CHESS_START, OnUpdateChessStart)
	ON_UPDATE_COMMAND_UI(IDM_CHESS_CLOSE, OnUpdateChessClose)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChessView construction/destruction

CChessView::CChessView()
	: CFormView(CChessView::IDD)
{
	//{{AFX_DATA_INIT(CChessView)
    //}}AFX_DATA_INIT

    m_bStandOff = TRUE;
    m_bRepent = TRUE;

    m_bmpBK.LoadBitmap(IDB_SKY);
    m_CurState = NO;
    m_RemoteState = NO;
    m_szRemoteUserName = _T("");

    m_Sets.bSet = FALSE;
    m_Sets.dwStep = 5;
    m_Sets.uAdd = 5;
    m_Sets.uInc = 5;
    //增加:其它的设置参数

    memcpy(&m_tmpSets, &m_Sets, sizeof(Sets));
}

CChessView::~CChessView()
{

#ifdef _DEBUG
    Sleep(500);
#else
    Sleep(3000);
#endif
    TRACE(_T("%s(%d) : CChessView::~CChessView\n"), __FILE__, __LINE__);
    m_sckChess.Close();
}

void CChessView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChessView)
	DDX_Control(pDX, IDC_BLACKUSERNAME, m_ctrBlackUserName);
	DDX_Control(pDX, IDC_REDUSERNAME, m_ctrRedUserName);
	DDX_Control(pDX, IDC_XQ, m_ctrXQ);
	//}}AFX_DATA_MAP
}

BOOL CChessView::PreCreateWindow(CREATESTRUCT& cs)
{
	//  Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CChessView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();
}

#ifdef _DEBUG
void CChessView::AssertValid() const
{
	CFormView::AssertValid();
}

void CChessView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CChessDoc* CChessView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChessDoc)));
	return (CChessDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChessView message handlers

int CChessView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	//  Add your specialized creation code here
    //设置窗口标题
    GetParent()->SetWindowText(_T("象棋"));
    m_pChessApp = (CChessApp*)AfxGetApp();
	//设置主框架中象棋视图指针
    m_pMainWnd = (CMainFrame*)AfxGetMainWnd();
    m_pMainWnd->m_pChessView = this;
    m_pMainWnd->GetServerAddress(&m_szServerIP, &m_uServerPort);
    //socket
    m_sckChess.Inital(this, ReceiveThread, 0, FALSE);
    CCommand cmd;
    cmd.SetCommand(g_cmdChessSock);
    cmd.AddPara(m_pChessApp->m_gszUserName);
    SendDataToServer(cmd);

    m_TiShiRemote.Create(this);
    m_TiShiRemote.SetBitmap(IDB_RSHUAI);
    m_TiShi.Create(this);
    m_TiShi.SetBitmap(IDB_BSHUAI);

	return 0;
}

void CChessView::OnDestroy() 
{
	CFormView::OnDestroy();
	
	//  Add your message handler code here
	TRACE(_T("%s(%d) : CChessView::Destory\n"), __FILE__, __LINE__);
    Close();
    //设置主框架中象棋视图指针
    m_pMainWnd->m_pChessView = NULL;
    m_pMainWnd->m_iView = CMainFrame::DESK_ENUM;
}

void CChessView::OnDraw(CDC* pDC) 
{
    //背景图片
    CDC dc;
    dc.CreateCompatibleDC(pDC);
    dc.SelectObject(&m_bmpBK);
    BITMAP bmp;
    m_bmpBK.GetBitmap(&bmp);
    CRect rect;
    GetClientRect(&rect);
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, bmp.bmWidth, bmp.bmHeight, SRCCOPY);
}

void CChessView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);   
    
	if(m_ctrXQ.GetSafeHwnd() && m_ctrRedUserName.GetSafeHwnd() && m_TiShi.GetSafeHwnd())
    {
        int Height = 10;
        int iWidth, iHeight;
        CRect rect;
        SetLocateUserName();
        m_ctrRedUserName.GetWindowRect(&rect);
        this->ScreenToClient(&rect);
        //m_ctrBlackUserName.MoveWindow(&rect);
        iWidth = rect.Width();
        iHeight = rect.Height() + Height * 2;

        int w;
        w = (cy - iHeight * 2) * 10 / 11;
        m_ctrXQ.MoveWindow(cx - w, iHeight, w, cy - iHeight * 2);

        m_ctrRedUserName.MoveWindow(cx - w / 2 - rect.Width() / 2, Height, rect.Width(), rect.Height());
        m_ctrBlackUserName.MoveWindow(cx - w / 2 - rect.Width() / 2, cy - iHeight + Height, rect.Width(), rect.Height()); 

        m_TiShiRemote.GetWindowRect(&rect);
        ScreenToClient(&rect);
        int width, height;
        width = rect.Width();
        height = rect.Height();
        rect.top = iHeight;
        rect.left = 3;
        rect.bottom = rect.top + height;
        rect.right = rect.left + width;
        m_TiShiRemote.MoveWindow(&rect);

        rect.top = cy - iHeight - height;
        rect.bottom = rect.top + height;
        //rect.right = rect.left + width;
        m_TiShi.MoveWindow(&rect);
    }
	
}

/*******************************************************************************************************
函数名：SetRemoteUserName
功  能：设置对方用户名,并显示对方用户名
参  数：
         LPCSTR szUser：对方用户名
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-17
时  间：21:44:04
*******************************************************************************************************/
void CChessView::SetRemoteUserName(LPCSTR szUser)
{
    ASSERT(szUser);
    m_szRemoteUserName = szUser;
    if(m_ctrRedUserName.GetSafeHwnd())
    {
        m_ctrRedUserName.SetWindowText(m_szRemoteUserName);
        if(m_szRemoteUserName == _T(""))
        {
            m_ctrRedUserName.ShowWindow(SW_HIDE);
        }
        else
        {
            m_ctrRedUserName.ShowWindow(SW_SHOW);
        } //结束 if(m_szRemoteUserName == _T(""))
    }
}

/*******************************************************************************************************
函数名：SetLocateUserName
功  能：设置本方用户名,并显示用户名
参  数：无
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-17
时  间：21:49:50
*******************************************************************************************************/
void CChessView::SetLocateUserName()
{   
    if(m_pChessApp->m_gszUserName.IsEmpty())
    {
        m_ctrBlackUserName.ShowWindow(SW_HIDE);
        return;
    }
    if(m_pChessApp->m_gszUserName == _T(""))
    {
        m_ctrBlackUserName.ShowWindow(SW_HIDE);
        return;
    }
    if(m_ctrBlackUserName.GetSafeHwnd())
    {
        m_ctrBlackUserName.SetWindowText(m_pChessApp->m_gszUserName);
        m_ctrBlackUserName.ShowWindow(SW_SHOW);
    }
}

/*******************************************************************************************************
函数名：SendDataToServer
功  能：向服务器发送数据
参  数：
         CCommand &cmd：数据
返回值：成功返回 TRUE，否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-3
时  间：16:15:28
*******************************************************************************************************/
BOOL CChessView::SendDataToServer(CCommand &cmd)
{
    return SendDataToServer(cmd.GetDataRef(), cmd.GetLength());
}

/*******************************************************************************************************
函数名：SendDataToServer
功  能：
参  数：
         LPVOID lpData：数据
         INT iLen：数据的长度
返回值：成功返回 TRUE，否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-3
时  间：16:15:52
*******************************************************************************************************/
BOOL CChessView::SendDataToServer(LPVOID lpData, INT iLen)
{
    return m_sckChess.SendDataTo(lpData, iLen, m_uServerPort, m_szServerIP);
}

/*******************************************************************************************************
函数名：SetRemoteAddress
功  能：设置对方象棋控件的地址
参  数：
         CString szIP：对方IP
         UINT uPort：对方Port
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-3
时  间：16:20:04
*******************************************************************************************************/
BOOL CChessView::SetRemoteAddress(CString szIP, UINT uPort)
{
    m_szRemoteIP = szIP;
    m_uRemotePort = uPort;
    return TRUE;
}

/*******************************************************************************************************
函数名：SendData
功  能：向对方象棋控件发送数据
参  数：
         CCommand &cmd：数据
返回值：成功返回 TRUE，否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-3
时  间：16:13:45
*******************************************************************************************************/
BOOL CChessView::SendData(CCommand &cmd)
{
    return SendData(cmd.GetDataRef(), cmd.GetLength());
}

/*******************************************************************************************************
函数名：SendData
功  能：向对方象棋控件发送数据
参  数：
         LPVOID lpData：数据
         INT iLen：数据的长度
返回值：成功返回 TRUE，否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-3
时  间：16:11:31
*******************************************************************************************************/
BOOL CChessView::SendData(LPVOID lpData, INT iLen)
{
    return m_sckChess.SendDataTo(lpData, iLen, m_uRemotePort, m_szRemoteIP);
}

DWORD _stdcall CChessView::ReceiveThread(LPVOID lpParameter)
{
    TRACE(_T("%s(%d) : CChess::ReceiveThread,线程号:%x\n"), __FILE__, __LINE__, ::GetCurrentThreadId());
    UDPSOCKREMOTEINFO* p = (UDPSOCKREMOTEINFO*)lpParameter;
    CString szRemoteIP(p->szRemoteIP);
    UINT uRemotePort = p->uRemotePort;
    CCommand command(p->pBuf, p->iLen);            //设置命令对象
    CChessView* pParent = (CChessView*) p->pParent;//转换成父窗口指针
    ::SetEvent(*(p->phEvent));

    //增加:接收到的命令处理
    long cmd;
    cmd = command.GetCommand();
    switch (cmd)
    {
    case g_cmdHand:              //握手
        TRACE(_T("%s(%d) : 象棋握手\n"), __FILE__, __LINE__);
        pParent->Hand(command);
        break;
    case g_cmdReceivedPara:      //确定设置参数
        pParent->ReceivedPara(command);
        break;
    case g_cmdChairInfo:         //椅子信息
        pParent->m_pMainWnd->m_pDeskView->SetChair(&command);
        break;
    case g_cmdSetDown:           //入坐
        pParent->SetDown(command);
        break;
    case g_cmdOtherSetDown:      //对方入坐
        pParent->OtherSetDown(command);
        break;
    case g_cmdStart:             //同意开始下棋
        pParent->Start(command);
        break;
    case g_cmdPlayChess:
        pParent->PlayChess(command);
        break;
    case g_cmdChess:             //正在走棋
        pParent->WalkChess(command);
        break;
    case g_cmdRepent:            //悔棋
        pParent->RepentChess();
        break;
    case g_cmdReceiveRepent:     //接受悔棋
        pParent->ReceiveRepent(command);
        break;
    case g_cmdStandOff:          //请求和棋
        pParent->StandOff();
        break;
    case g_cmdReceivedStandOff:  //接受和棋
        pParent->ReceivedStandOff(&command, TRUE);
        break;
    case g_cmdGiveup:            //认输
        pParent->Giveup();
        break;
    }
    return 0;
}

/*******************************************************************************************************
函数名：OnChessClose
描  述：退出象棋
参  数：无
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-11 13:26:58
*******************************************************************************************************/
void CChessView::OnChessClose() 
{
    if(m_CurState == PLAYCHESS)
    {
        INT iR = MessageBox(_T("正在下棋，如果你退出，则以你认输而结束。是否退出？"), _T("退出象棋"), MB_OKCANCEL | MB_ICONQUESTION);
        if(iR == IDCANCEL)
        {
            return;
        }
        else
        {
            OnChessGiveup();
        }//结束 if(iR == IDCANCEL)
    } //结束 if(m_CurState == PLAYCHESS)
    Exit();
}

void CChessView::OnUpdateChessClose(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

/*******************************************************************************************************
函数名：OnChessGiveup
描  述：认输
参  数：无
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-11 13:27:26
*******************************************************************************************************/
void CChessView::OnChessGiveup() 
{
    CCommand cmd;
    cmd.SetCommand(g_cmdGiveup);
    cmd.AddPara(m_pChessApp->m_gszUserName);  //认输方
    cmd.AddPara(m_szRemoteUserName);          //赢方
    cmd.AddPara(m_Sets.uAdd);                 //加分值
    cmd.AddPara(m_Sets.uInc);                 //减分值
    //增加:其它的设置参数
    SendDataToServer(cmd);
    SendData(cmd);
    
    ReStart();
    m_TiShiRemote.AddWin();

}

void CChessView::OnUpdateChessGiveup(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_CurState & PLAYCHESS);
}

/*******************************************************************************************************
函数名：OnChessRepent
描  述：悔棋
参  数：无
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-11 13:27:40
*******************************************************************************************************/
void CChessView::OnChessRepent() 
{
    CCommand cmd;
    cmd.SetCommand(g_cmdRepent);
    SendData(cmd);
    m_bRepent = FALSE;
}

void CChessView::OnUpdateChessRepent(CCmdUI* pCmdUI) 
{
    pCmdUI->Enable((m_CurState & PLAYCHESS) && m_bRepent);
}

/*******************************************************************************************************
函数名：OnChessSet
描  述：设置下棋参数
参  数：无
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-11 13:27:53
*******************************************************************************************************/
void CChessView::OnChessSet() 
{
    CSetDlg sd;
    sd.m_uAddPoint = m_Sets.uAdd;
    sd.m_dwStep = m_Sets.dwStep;
    sd.m_uIncPoint = m_Sets.uInc;
    //增加:其它的设置参数

    if(sd.DoModal() == IDOK)
    {
        m_tmpSets.bSet = TRUE;
        m_tmpSets.uAdd = sd.m_uAddPoint;
        m_tmpSets.dwStep = sd.m_dwStep;
        m_tmpSets.uInc = sd.m_uIncPoint;
    } //结束 if(sd.DoModal() == IDOK)
}

void CChessView::OnUpdateChessSet(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!(m_CurState & (PLAYCHESS | START)));
}

/*******************************************************************************************************
函数名：OnChessStandoff
描  述：求和
参  数：无
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-11 13:31:56
*******************************************************************************************************/
void CChessView::OnChessStandoff() 
{
    CCommand cmd;
    cmd.SetCommand(g_cmdStandOff);
    SendData(cmd);
    m_bStandOff = FALSE;
}

void CChessView::OnUpdateChessStandoff(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable((m_CurState & PLAYCHESS) && m_bStandOff);
}

/*******************************************************************************************************
函数名：OnChessStart
描  述：开始
参  数：无
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-11 13:32:36
*******************************************************************************************************/
void CChessView::OnChessStart() 
{    
    CCommand cmd;
    cmd.SetCommand(g_cmdStart);
    cmd.AddPara(m_pChessApp->m_gszUserName);
    cmd.AddPara(m_szRemoteUserName);
    SendDataToServer(cmd);
}

void CChessView::OnUpdateChessStart(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!(m_CurState & (PLAYCHESS | START)));
}

/*******************************************************************************************************
函数名：SetDown
功  能：入坐命令处理
参  数：
         CCommand& cmd：命令参数(对面状态)
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-4
时  间：17:15:39
*******************************************************************************************************/
void CChessView::SetDown(CCommand& cmd)
{
    CString szUser;
    CString szExIP, szExPort, szExChessPort;
    CString szIP, szPort, szChessPort;
    long command;
    command = cmd.GetLongPara();
    m_ctrXQ.EnableWindow(FALSE);
    if(command == g_cmdOtherNoMan) //对方没入坐
    {
        m_ctrXQ.SetQiPangLayout(CXQ::NoQi);
        m_ctrXQ.ShowWindow(SW_SHOW);
        //TRACE(_T("%s(%d) : 对方没入坐\n"), __FILE__, __LINE__);
        return;
    }
    m_szRemoteUserName = cmd.GetPara();
    szExIP = cmd.GetPara();
    szExPort = cmd.GetPara();
    szIP = cmd.GetPara();
    szPort = cmd.GetPara();
    szExChessPort = cmd.GetPara();
    szChessPort = cmd.GetPara();
    switch(command)
    {
    case g_cmdOtherNoMan: //对方没入坐
        m_ctrXQ.SetQiPangLayout(CXQ::NoQi);
        break;
    case g_cmdOtherSetDown: //对方入坐,但没开始
        m_ctrXQ.SetQiPangLayout(CXQ::NoQi);
        m_RemoteState = SETDOWN;
        //TRACE(_T("%s(%d) : 对方入坐\n"), __FILE__, __LINE__);
        break;
    case g_cmdOtherStart:   //对方入坐且开始
        m_RemoteState = START;
        m_ctrXQ.SetQiPangLayout(CXQ::OnlyTopRed);
        //TRACE(_T("%s(%d) : 对方入坐并开始\n"), __FILE__, __LINE__);
        break;
    default:
        return;
    }
    SetRemoteUserName(m_szRemoteUserName);
    m_ctrXQ.ShowWindow(SW_SHOW);
    m_CurState = SETDOWN;
    /*TRACE(_T("%s(%d) : 外部IP=%s,外部Port=%s,内部IP=%s,内部Port=%s,外部ChessPort=%s,InChessPort=%s\n"),
        __FILE__, __LINE__, szExIP, szExPort,szIP, szPort,szExChessPort, szChessPort);//*/

}

/*******************************************************************************************************
函数名：OtherSetDown
功  能：处理对方入坐命令
参  数：
         CCommand &cmd：命令参数(用户名)
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-4
时  间：17:26:30
*******************************************************************************************************/
void CChessView::OtherSetDown(CCommand &cmd)
{
    CString szUserName;    //用户名
    CString szExIP;        //外部IP
    CString szExPort;      //外部Pport
    CString szIP;          //内部IP
    CString szPort;        //内部Port
    CString szExChessPort; //外部象棋Port
    CString szChessPort;   //内部象棋Port

    szUserName = cmd.GetPara();
    szExIP = cmd.GetPara();
    szExPort = cmd.GetPara();
    szIP = cmd.GetPara();
    szPort = cmd.GetPara();
    szExChessPort = cmd.GetPara();
    szChessPort = cmd.GetPara();
 
    SetRemoteUserName(szUserName);
    //增加：IP、Port
    m_RemoteState = SETDOWN;
    //TRACE(_T("%s(%d) : 对方入坐\n"), __FILE__, __LINE__);
}

/*******************************************************************************************************
函数名：Close
功  能：关闭
参  数：无
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-4
时  间：9:51:32
*******************************************************************************************************/
void CChessView::Close()
{
    CCommand cmd;
    //离开坐位
    cmd.SetCommand(g_cmdLeaveChair);
    cmd.AddPara(m_pChessApp->m_gszUserName);
    cmd.AddPara(m_lChairNo);
    cmd.AddPara(m_szRemoteUserName);
    ASSERT(AfxIsValidAddress(m_pMainWnd, sizeof(m_pMainWnd)));
    ASSERT(IsWindow(m_pMainWnd->GetSafeHwnd()));
    m_pMainWnd->SendData(&cmd);
    //SendDataToServer(cmd);
    
    TRACE(_T("%s(%d) : %s 离开坐位 %d\n"), __FILE__, __LINE__, m_pChessApp->m_gszUserName, m_lChairNo);
}

/*******************************************************************************************************
函数名：Exit
功  能：退出视图
参  数：无
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-4
时  间：9:51:28
*******************************************************************************************************/
void CChessView::Exit()
{
	GetParent()->SendMessage(WM_CLOSE);    
}

void CChessView::LeaveChair(CCommand & cmd)
{
    CString szUser;
    szUser = cmd.GetPara();
    if(szUser == m_szRemoteUserName)
    {
        MessageBox(m_szRemoteUserName + _T(" 离开坐位。"), _T("离开坐位"), MB_ICONINFORMATION);
        SetRemoteUserName(_T(""));
    } //结束 if(szUser == m_szRemoteUserName)
}

/*******************************************************************************************************
函数名：OtherExit
功  能：处理对方退出
参  数：
         CCommand &cmd：对方用户名
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-5
时  间：11:56:06
*******************************************************************************************************/
void CChessView::OtherExit(CCommand &cmd)
{
    CString szUser;
    szUser = cmd.GetPara();
    if(szUser != m_szRemoteUserName) //不是对方用户退出
    {
        TRACE(_T("%s(%d) : 不是对方用户退出\n"), __FILE__, __LINE__);
        return;
    }
    //增加:处理对方用户退出
    MessageBox(m_szRemoteUserName + _T(" 退出。"), _T(" 退出"), MB_ICONINFORMATION);
    m_szRemoteUserName = _T("");
    SetRemoteUserName(m_szRemoteUserName);
}

/*******************************************************************************************************
函数名：Start
功  能：同意开始
参  数：
         Command &cmd：
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-19
时  间：18:01:25
*******************************************************************************************************/
void CChessView::Start(CCommand &cmd)
{
    CString szUser, szUserName;
    szUser = cmd.GetPara(); //先走方
    szUserName = cmd.GetPara();
    if(szUser == m_szRemoteUserName)
    {
        if(szUserName != _T(""))
        {
            m_ctrXQ.SetQiPangLayout(CXQ::TopRedAndBottomBlack);
            m_ctrXQ.EnableWindow(FALSE);
            m_ctrXQ.SetStartSide(CXQ::RedReadly);
        }
        else
        {
            m_ctrXQ.SetQiPangLayout(CXQ::OnlyTopRed);
        } //结束 if(szUserName != _T(""))
        m_RemoteState = START;
       
    } //结束 if(szUser == m_szRemoteUserName)
    if(szUser == m_pChessApp->m_gszUserName)
    {
        if(szUserName != _T(""))
        {
            m_ctrXQ.SetQiPangLayout(CXQ::TopBlackAndBottomRed);
            m_ctrXQ.SetStartSide(CXQ::BlackReadly);
            m_ctrXQ.EnableWindow(TRUE);
        }
        else
        {
            m_ctrXQ.SetQiPangLayout(CXQ::OnlyBottomRed);
        } //结束 if(szUserName != _T(""))
        m_CurState = START;
    } //结束 if(szUser == m_pChessApp->m_gszUserName)
    //TRACE(_T("%s(%d) : %s 同意开始下棋\n"), __FILE__, __LINE__, szUser);
}

/*******************************************************************************************************
函数名：PlayChess
功  能：正式开始下棋时的初始化工作
参  数：无
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-19
时  间：17:22:33
*******************************************************************************************************/
void CChessView::PlayChess(CCommand &cmd)
{
    CString szUser, szUserName;
    CString szIP, szIP1;
    UINT uPort, uPort1;
    szUser = cmd.GetPara();        //先走方
    szIP = cmd.GetPara();
    uPort = _ttol(cmd.GetPara());
    szUserName = cmd.GetPara();    //后走方
    szIP1 = cmd.GetPara();
    uPort1 = _ttol(cmd.GetPara());
    
    m_CurState = PLAYCHESS;
    m_RemoteState = PLAYCHESS;
    if(szUser == m_szRemoteUserName)
    {
        m_ctrXQ.SetStartSide(CXQ::RedReadly);
        m_szRemoteIP = szIP;
        m_uRemotePort = uPort;
        //TRACE(_T("%s(%d) : szIP:%s, uPort:%d\n"), __FILE__, __LINE__, szIP, uPort);
        SendHand();
    } //结束 if(szUser == m_szRemoteUserName)
    if(szUser == m_pChessApp->m_gszUserName)
    {
        m_ctrXQ.SetStartSide(CXQ::BlackReadly);
    } //结束 if(szUser == m_pChessApp->m_gszUserName)
    if(szUserName == m_szRemoteUserName)
    {
        m_szRemoteIP = szIP1;
        m_uRemotePort = uPort1;
        //TRACE(_T("%s(%d) : szIP:%s, uPort:%d\n"), __FILE__, __LINE__, szIP1, uPort1);
        SendHand();
    } //结束 if(szUserName == m_szRemoteUserName)
    if(m_ctrXQ.GetStartSide() == CXQ::BlackReadly)
    {
        m_TiShi.SetBitmap(IDB_RSHUAI);
        m_TiShiRemote.SetBitmap(IDB_BSHUAI);
        m_TiShi.ShowWindow(SW_SHOW);
        //Sleep(1000);
        m_ctrXQ.SetEnabled(TRUE);
    }
    else
    {
        m_TiShi.SetBitmap(IDB_BSHUAI);
        m_TiShiRemote.SetBitmap(IDB_RSHUAI);
        m_TiShiRemote.ShowWindow(SW_SHOW);
    }
}

/*******************************************************************************************************
函数名：SendHand
描  述：发送握手信息。同时发送设置信息
参  数：无
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-10 17:23:39
*******************************************************************************************************/
void CChessView::SendHand()
{
    CCommand cmd;
    cmd.SetCommand(g_cmdHand);
    cmd.AddPara(m_tmpSets.bSet);
    cmd.AddPara(m_tmpSets.dwStep);
    cmd.AddPara(m_tmpSets.uAdd);
    cmd.AddPara(m_tmpSets.uInc);
    //增加:其它的设置参数

    SendData(cmd);
}

/*******************************************************************************************************
函数名：Hand
描  述：处理握手命令
参  数：
         CCommand& cmd：命令参数数据包
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-10 17:26:56
*******************************************************************************************************/
void CChessView::Hand(CCommand& cmd)
{
    BOOL bSet;
    LONG dwStep;
    UINT uAdd, uInc;
    bSet = _ttol(cmd.GetPara());
    dwStep = _ttol(cmd.GetPara());
    uAdd = _ttoi(cmd.GetPara());
    uInc = _ttoi(cmd.GetPara());
    //增加:其它的设置参数

    if(bSet)
    {
        CSetDlg sd;
        sd.m_dwStep = dwStep;
        sd.m_uAddPoint = uAdd;
        sd.m_uIncPoint = uInc;
        sd.m_iFunction = CSetDlg::ReceiveSet;
        if(sd.DoModal() == IDOK)
        {
            m_Sets.dwStep = dwStep;
            m_Sets.uAdd = uAdd;
            m_Sets.uInc = uInc;
            //发送接收确定命令
            CCommand cmd;
            cmd.SetCommand(g_cmdReceivedPara);
            SendData(cmd);
        } //结束 if(sd.DoModal() == IDOK)
    } //结束 if(bSet)
}

void CChessView::ReceivedPara(CCommand & cmd)
{
    MessageBox(m_szRemoteUserName + _T(" 接受了参数设置"), _T(" 接受了参数设置"));
    memcpy(&m_Sets, &m_tmpSets, sizeof(Sets));
}

/*******************************************************************************************************
函数名：WalkChess
描  述：走棋,用于接收对方走棋
参  数：
         CCommand & cmd：命令
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-10 8:53:24
*******************************************************************************************************/
void CChessView::WalkChess(CCommand & cmd)
{
    int i, j;
    i = _ttol(cmd.GetPara());
    j = _ttol(cmd.GetPara());
    m_ctrXQ.Walk(i, j);
    if(m_ctrXQ.GetCurrentSide() == CXQ::RedReadly
        || m_ctrXQ.GetCurrentSide() == CXQ::BlackReadly)
    {
       ShowTiShi();
       m_ctrXQ.SetEnabled(TRUE);
    } //结束 if(m_ctrXQ.GetStartSide() == CXQ::RedReadly || m_ctrXQ.GetStartSide() == CXQ::BlackReadly)
}

BEGIN_EVENTSINK_MAP(CChessView, CFormView)
ON_EVENT(CChessView, IDC_XQ, 1, MoveChessXq, VTS_I2 VTS_I2 VTS_I4)
END_EVENTSINK_MAP()

void CChessView::MoveChessXq(short x, short y, long chess)
{
    short i, j;
    m_ctrXQ.InterConvertCoordinate(x, y, &i, &j);
    CCommand cmd;
    cmd.SetCommand(g_cmdChess);
    cmd.AddPara(i);
    cmd.AddPara(j);
    SendData(cmd);
    if(m_ctrXQ.GetCurrentSide() == CXQ::RedWalked
        || m_ctrXQ.GetCurrentSide() == CXQ::BlackWalked)
    {
       m_ctrXQ.SetEnabled(FALSE);
       ShowTiShi();
    } //结束 if(m_ctrXQ.GetStartSide() == CXQ::RedWalked || m_ctrXQ.GetStartSide() == CXQ::BlackWalked)
}

/*******************************************************************************************************
函数名：ShowTiShi
描  述：走棋时是否显示提示框
参  数：无
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-10 9:06:01
*******************************************************************************************************/
void CChessView::ShowTiShi()
{
    if(m_TiShi.IsWindowVisible())
    {
        m_TiShi.ShowWindow(SW_HIDE);
        m_TiShiRemote.ShowWindow(SW_SHOW);
    }
    else
    {
        m_TiShi.ShowWindow(SW_SHOW);
        m_TiShiRemote.ShowWindow(SW_HIDE);
    }//结束 if(m_TiShi.IsWindowVisible())
}

/*******************************************************************************************************
函数名：RepentChess
描  述：处理悔棋命令
参  数：
         CCommand& cmd：悔棋命令参数
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-11 7:21:24
*******************************************************************************************************/
void CChessView::RepentChess()
{
    int iR;
    CCommand cmd;

    cmd.SetCommand(g_cmdReceiveRepent);
    iR = MessageBox(m_szRemoteUserName + _T(" 请求悔棋？"), _T("悔棋"), MB_YESNO);
    if(iR == IDYES)
    {
        if(m_ctrXQ.GetEnabled())
        {
            m_ctrXQ.PreviouStep();
        }
        else
        {
            m_ctrXQ.PreviouStep();
            m_ctrXQ.PreviouStep();
        } //结束 if(m_ctrXQ.GetEnabled())
       
        //对方走棋
        m_ctrXQ.SetEnabled(FALSE);
        m_TiShi.ShowWindow(SW_HIDE);
        m_TiShiRemote.ShowWindow(SW_SHOW);

        cmd.AddPara(TRUE);
    }
    else
    {
        cmd.AddPara(FALSE);
    } //结束 if(iR == IDYES)

    SendData(cmd);
}

/*******************************************************************************************************
函数名：ReceiveRepent
描  述：接受悔棋命令
参  数：
         CCommand & cmd：接受悔棋命令参数
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-11 7:20:54
*******************************************************************************************************/
void CChessView::ReceiveRepent(CCommand & cmd)
{
    m_bRepent = TRUE;

    long iR = cmd.GetLongPara();
    if(iR)
    {
        MessageBox(m_szRemoteUserName + _T(" 接受悔棋"), _T("接受悔棋"));
    }
    else
    {
        MessageBox(m_szRemoteUserName + _T(" 不接受悔棋"), _T("接受悔棋"));
        return;
    }//结束 if(iR)
    
    if(m_ctrXQ.GetEnabled())
    {
        m_ctrXQ.PreviouStep();
        m_ctrXQ.PreviouStep();
    }
    else
    {        
        m_ctrXQ.PreviouStep();
    } //结束 if(m_ctrXQ.GetEnabled())
   
    //本方走棋
    m_TiShi.ShowWindow(SW_SHOW);
    m_TiShiRemote.ShowWindow(SW_HIDE);
    m_ctrXQ.SetEnabled(TRUE);
}

/*******************************************************************************************************
函数名：OverTime
描  述：超时处理
参  数：无
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-11 8:53:32
*******************************************************************************************************/
void CChessView::OverTime(LONG span)
{
    if(m_TiShiRemote.IsWindowVisible())
    {
        return;
    } //结束 if(m_RemoteTiShi.IsWindowVisible())

    switch(span)
    {
    case 0:
        OnChessGiveup();
        MessageBox(_T("你已经超时。"), _T("超时"));
        break;
    case 1:
        PromptSound(_T("IDW_1"));
        break;
    case 2:
        PromptSound(_T("IDW_2"));
        break;
    case 3:
        PromptSound(_T("IDW_3"));
        break;
    case 4:
        PromptSound(_T("IDW_4"));
        break;
    case 5:
        PromptSound(_T("IDW_5"));
        break;
    case 6:
        PromptSound(_T("IDW_6"));
        break;
    case 7:
        PromptSound(_T("IDW_7"));
        break;
    case 8:
        PromptSound(_T("IDW_8"));
        break;
    case 9:
        PromptSound(_T("IDW_9"));
        break;
    case 10:
        PromptSound(_T("IDW_10"));
        break;
    } //结束 switch(tmStep.GetTotalSeconds())
}

/*******************************************************************************************************
函数名：PromptSound
描  述：播放资源中的声音
参  数：
         LPCTSTR ID：声音ID
返回值：成功返回 TRUE，否则返回 FALSE。
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-11 9:38:34
*******************************************************************************************************/
BOOL CChessView::PromptSound(LPCTSTR ID)
{
	if(NULL != ID)
	{
		HINSTANCE hInstance = AfxGetInstanceHandle();
		HRSRC hr = FindResource(hInstance, ID, _T("WAVE"));
		HGLOBAL hg = LoadResource(hInstance, hr);
		LPCTSTR lp=(LPCTSTR)LockResource(hg);
		::sndPlaySound(lp, SND_MEMORY | SND_ASYNC);
		FreeResource(hg);
	}
	else
	{
		Beep(1000, 20);
	}
	return true;
}

/*******************************************************************************************************
函数名：ReceiveStandOff
描  述：接受求和
参  数：
         BOOL bTiShi：是否显示确定接受的提示框
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-11 13:36:11
*******************************************************************************************************/
void CChessView::ReceivedStandOff(CCommand* pcmd, BOOL bTiShi)
{
    m_bStandOff = TRUE;

    if(bTiShi && pcmd != NULL)
    {
        long iR = pcmd->GetLongPara();
        if(iR)
        {
            MessageBox(m_szRemoteUserName + _T(" 接受求和"), _T("求和"));
        }
        else
        {
            MessageBox(m_szRemoteUserName + _T(" 不同意求和"), _T("求和"));
            return;
        }//结束 if(iR)
        
    } //结束 if(bTiShi)
   
    CCommand cmd;
    cmd.SetCommand(g_cmdStandOff);
    cmd.AddPara(m_pChessApp->m_gszUserName);
    SendDataToServer(cmd);

    m_TiShi.AddStandOff();
    m_TiShiRemote.AddStandOff();

    ReStart();

}

/*******************************************************************************************************
函数名：ReStart
描  述：重新下棋
参  数：无
返回值：
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-11 22:07:18
*******************************************************************************************************/
void CChessView::ReStart()
{
    m_CurState = SETDOWN;
    m_ctrXQ.ReStart();
    m_ctrXQ.SetEnabled(FALSE);
    m_ctrXQ.SetQiPangLayout(CXQ::NoQi);
    m_TiShi.ShowWindow(SW_HIDE);
    m_TiShi.AddTotal();
    m_TiShiRemote.ShowWindow(SW_HIDE);
    m_TiShiRemote.AddTotal();
}

/*******************************************************************************************************
函数名：StandOff
描  述：求和操作
参  数：无
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-11 13:40:32
*******************************************************************************************************/
void CChessView::StandOff()
{
    CCommand cmd;
    cmd.SetCommand(g_cmdReceivedStandOff);
    INT iR = MessageBox(m_szRemoteUserName + _T(" 请求和棋，是否同意？"),
        _T("求和"), MB_YESNO | MB_ICONQUESTION);    
    if(iR == IDYES)
    {
        ReceivedStandOff();
        cmd.AddPara(1);
    }
    else
    {
        cmd.AddPara(0);
    } //结束 if(iR == IDYES)
    SendData(cmd);
}

/*******************************************************************************************************
函数名：Giveup
描  述：对方认输后的客户端的处理，由对方客户端直接发过来的，不经过服务器。
参  数：无
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-12 16:55:14
*******************************************************************************************************/
void CChessView::Giveup()
{
    //增加:结束对话框

    m_TiShi.AddWin();
    ReStart();
}

/*******************************************************************************************************
函数名：ReceiveGiveup
描  述：从服务器发回的认输后的用户信息
参  数：
         CCommand& cmd：命令参数
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-12 16:54:31
*******************************************************************************************************/
void CChessView::ReceiveGiveup(CCommand& cmd)
{
    CString szWin, szLoss;
    long Win, Loss; //积分

    szLoss = cmd.GetPara();
    Loss = cmd.GetLongPara();
    szWin = cmd.GetPara();
    Win = cmd.GetLongPara();

    CShowResult sr;
    sr.m_szWin = szWin;
    sr.m_szLoss = szLoss;
    sr.m_iWin = Win;
    sr.m_iLoss = Loss;
    sr.m_iAdd = m_Sets.uAdd;
    sr.m_iInc = -m_Sets.uInc;
    sr.DoModal();

}