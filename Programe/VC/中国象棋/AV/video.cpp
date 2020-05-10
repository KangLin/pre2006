/*******************************************************************************************************
文件名：video.cpp
功  能：完成视频、音频的发送、接收。
算  法：
        1、本地请求视频、音频连接
		   1.1、当本地点击视频时，在 OnVideoClick 中调用  Initializtion() 初始化视频控件、音频、及其 Socket
		   1.2、把本地用户名、IP、VIDEOPORT、AUDIOPORT 用 CMainFrame::m_sckCommand 发送 请求视频连接 命令到服务器
		   1.3、如果对方同意视频，则调用 Start
		   1.4、如果对方不同意，则调用 End 结束视频、音频及其 Socket
		2、远程请求视频、音频连接
		   1.1、由 CMainFrame::m_sckCommand 调用 Connect 函数
		   1.2、如果不同意，则用 CMainFrame::m_sckCommand 发送 不同意视频连接 命令
		   1.3、如果同意连接，则调用 Initializtion() 初始化视频控件、音频、及其 Socket
		   1.4、并用 CMainFrame::m_sckCommand 发送 同意视频连接 命令，
		        并发送用户名、本地IP、VIDEOPORT、AUDIOPORT
		   1.5、调用 Start 开始视频、音频
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-12-18
时  间：15:44:25

FileName：video.cpp
Function：
Compiler：Visual C++ 6.0
Author：  KangLin
          Copyright 2004 KangLin
Date：    2004-12-18
Time：    15:44:25
*******************************************************************************************************/
// video.cpp : implementation file
//

#include "stdafx.h"
#include "..\中国象棋.h"
#include "video.h"
#include "..\MainFrm.h"
#include "VideoConnectDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVideo dialog

IMPLEMENT_DYNCREATE(CVideo, CDialog)

CVideo::CVideo(CWnd* pParent /*=NULL*/)
	: CDialog(CVideo::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVideo)
	//}}AFX_DATA_INIT

	m_StartVideo = FALSE;
}

CVideo::~CVideo()
{
    TRACE(_T("%s(%d) : CVideo::~CVideo\n"), __FILE__, __LINE__);
    m_sckAudio.Close();
    m_sckVideo.Close();
}

void CVideo::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CVideo)
    DDX_Control(pDX, IDC_DISPLAYVIDEO, m_ctrlDisplayVideo);
    //}}AFX_DATA_MAP
    DDX_Control(pDX, IDC_COMBO_USERNAME, m_cmbUser);
}


BEGIN_MESSAGE_MAP(CVideo, CDialog)
	//{{AFX_MSG_MAP(CVideo)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTONVIDEO, OnVideoClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideo message handlers

void CVideo::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	if(m_ctrlDisplayVideo.GetSafeHwnd())
	{		
		m_ctrlDisplayVideo.MoveWindow(0, 0, cx, cy * 7 / 16 -  5);
		//m_ctrlVideo.MoveWindow(0, cy *  7 / 16 + 5, cx, cy * 7 / 16 - 5);
		m_butVideo.MoveWindow(cx / 2, cy * 15 / 16 - 25, cx / 2, 40);
        m_cmbUser.MoveWindow(0, cy * 15 / 16 - 25 / 2, cx / 2, 40);
	}
	if(m_ctrlVideo.GetSafeHwnd())
	{
		m_ctrlVideo.MoveWindow(0, cy * 7 / 16 + 5, cx, cy * 7 / 16 - 5);
	}
}

int CVideo::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_butVideo.Create(_T("视频"), WS_CHILD | WS_VISIBLE, CRect(0, 0, 100, 50), this, IDC_BUTTONVIDEO);

	m_butVideo.SetIcon(IDI_VIDEO);
	m_butVideo.SetRounded(TRUE);
    m_butVideo.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_butVideo.SetTooltipText(_T("开始视频"));

	return 0;
}

void CVideo::OnVideoClick()
{
	m_StartVideo = m_StartVideo ? FALSE : TRUE;
	if(m_StartVideo)
	{
		m_butVideo.SetTooltipText(_T("结束视频"));
		
		Initializtion();
	}
	else
	{
		m_butVideo.SetTooltipText(_T("开始视频"));
		
		End();
	}
}

/*******************************************************************************************************
函数名：VideoConnect
描  述：对方 请求视频连接 命令。显示连接对话框。
参  数：
        CCommand& cmd：
返回值：
版  本：1.0.0.1
作  者：康  林
时  间：2005-7-3 10:16:16
*******************************************************************************************************/
BOOL CVideo::VideoConnect(CCommand& cmd)
{
    CString szUser, szUserName, szIP;
    UINT uPort;
    szUser = cmd.GetPara();
    szUserName = ((CChessApp* )AfxGetApp())->m_gszUserName; //本方用户名
    uPort = cmd.GetLongPara();
    szIP = cmd.GetPara();
	int iR;
    iR = MessageBox(szUser + _T("，请求连接？"), _T("视频连接请求"), MB_YESNO | MB_ICONQUESTION);
    if(iR = IDOK)
    {
        m_uRemoteVideoPort = uPort;
        m_szRemoteIP = szIP;
        m_cmbUser.SetWindowText(szUser);
        m_butVideo.SetTooltipText(_T("结束视频"));
        Initializtion(TRUE);
        //发送握手命令
        CCommand cmd;
        cmd.SetCommand(g_cmdVideoHand);
        VideoSendData(cmd);
    }
    else //不同意连接
    {
        CCommand cmd;
        cmd.SetCommand(g_cmdNoVideo);
        cmd.AddPara(szUserName);  //本方用户名
        cmd.AddPara(szUser);      //对方用户名
        SendDataToServer(cmd);
        return FALSE;
    } // 结束 if(iR = IDOK)
	return TRUE;
}

/*******************************************************************************************************
函数名：AudioConnect
描  述：对方 请求音频连接 命令。显示连接对话框。
参  数：
        CCommand& cmd：
返回值：
版  本：1.0.0.1
作  者：康  林
时  间：2005-7-3 10:16:37
*******************************************************************************************************/
BOOL CVideo::AudioConnect(CCommand& cmd)
{
    CString szUser, szUserName, szIP;
    UINT uPort;
    szUser = cmd.GetPara();
    szUserName = ((CChessApp* )AfxGetApp())->m_gszUserName; //本方用户名
    uPort = cmd.GetLongPara();
    szIP = cmd.GetPara();
	int iR;
    iR = MessageBox(szUser + _T("，请求连接？"), _T("音频连接请求"), MB_YESNO | MB_ICONQUESTION);
    if(iR = IDOK)
    {
        m_uRemoteVideoPort = uPort;
        m_szRemoteIP = szIP;
        m_cmbUser.SetWindowText(szUser);        
        Initializtion(TRUE);
        //发送握手命令
        CCommand cmd;
        cmd.SetCommand(g_cmdAudioHand);
        VideoSendData(cmd);
    }
    else //不同意连接
    {
        CCommand cmd;
        cmd.SetCommand(g_cmdNoAudio);
        cmd.AddPara(szUserName);  //本方用户名
        cmd.AddPara(szUser);      //对方用户名
        SendDataToServer(cmd);
        return FALSE;
    } // 结束 if(iR = IDOK)
	return TRUE;
}

/*******************************************************************************************************
函数名：Initializtion
描  述：初始化视频控件、音频、及Socket。并且向服务器发送连接请求命令。
参  数：
        BOOL bAgree：如果为 TRUE，同意连接，FALSE，请求连接。默认为 TRUE
返回值：成功返回 TRUE，否则返回 FALSE
版  本：1.0.0.1
作  者：康  林
时  间：2005-7-3 10:20:51
*******************************************************************************************************/
BOOL CVideo::Initializtion(BOOL bAgree)
{
    //得到服务器的地址和端口
    CMainFrame* m_pMainWnd = (CMainFrame*)AfxGetMainWnd();
    m_pMainWnd->GetServerAddress(&m_szServerIP, &m_uServerPort);

	//初始化视频控件
    if(m_ctrlVideo.GetSafeHwnd() == NULL)
    {
        if(m_ctrlVideo.Create(_T("本地视频"), WS_CHILD | WS_VISIBLE, CRect(0, 0, 100, 100), this, IDC_VIDEOCONTROL))
        {
            //视频 Socket
            if(!m_sckVideo.Inital(this, VideoReceiveThread))
            {
                return FALSE;
            } // 结束 if(!m_sckVideo.Inital(this, VideoReceiveThread))
            //向服务器发送连接信息
            CCommand cmd;
            if(!bAgree)
            {
                cmd.SetCommand(g_cmdVideoConn);
            }
            else
            {
                cmd.SetCommand(g_cmdAgreeVideoConn);
            } // 结束 if(!bAgree)

            CString szUser;
            m_cmbUser.GetWindowText(szUser);
            if(szUser == "" || szUser == ((CChessApp * )AfxGetApp())->m_gszUserName)
            {
                End();
                MessageBox(_T("没有选择对方，请选取用户。"), _T("请选取用户"));
                return FALSE;
            } // 结束 if(szUser == "" || szUser == ((CChessApp * )AfxGetApp())->m_gszUserName)
            cmd.AddPara(szUser);
            cmd.AddPara(((CChessApp * )AfxGetApp())->m_gszUserName);
            m_sckVideo.SendDataTo(cmd.GetDataRef(), cmd.GetLength(), m_uServerPort, m_szServerIP);
        }
    } // 结束 if(m_ctrlVideo.GetSafeHwnd() == NULL)

	//增加:初始化音频

	//音频 Socket	
	if(!m_sckAudio.Inital(this, AudioReceiveThread))
    {
        return FALSE;
    } // 结束 if(!m_sckAudio.Inital(this, AudioReceiveThread))
    //向服务器发送连接信息
    CCommand cmd;
    if(!bAgree)
    {
        cmd.SetCommand(g_cmdAudioConn); 
    }
    else
    {
        cmd.SetCommand(g_cmdAgreeAudioConn);
    } // 结束 if(!bAgree)
    
    cmd.AddPara(((CChessApp * )AfxGetApp())->m_gszUserName);
    CString szUser;
    m_cmbUser.GetWindowText(szUser);
    if(szUser == "" || ((CChessApp * )AfxGetApp())->m_gszUserName)
    {
        //增加:关闭音频
        End();
        MessageBox(_T("没有选择对方，请选取用户。"), _T("请选取用户"));
        return FALSE;
    } // 结束 if(szUser == "" || ((CChessApp * )AfxGetApp())->m_gszUserName)
    cmd.AddPara(szUser);
    m_sckAudio.SendDataTo(cmd.GetDataRef(), cmd.GetLength(), m_uServerPort, m_szServerIP);
    return TRUE;
}

/*******************************************************************************************************
函数名：StartVideo
描  述：对方同意视频连接。
        开始视频。
		此函数是由 CMainFrame::m_sckCommand 接收到服务器的 同意视频连接 命令后调用。
参  数：
        CCommand& cmd：
返回值：成功返回TRUE，否则返回FALSE
版  本：1.0.0.1
作  者：康  林
时  间：2005-7-3 11:05:57
*******************************************************************************************************/
BOOL CVideo::StartVideo(CCommand& cmd)
{
    m_cmbUser.SetWindowText(cmd.GetPara());
	//设置远程IP、PORT
   	m_uRemoteVideoPort = cmd.GetLongPara();
    m_szRemoteIP = cmd.GetPara();
    ((CMainFrame*)AfxGetMainWnd())->m_TabCtrl.SetActivePage(2);
	//开始视频捕获、
    return m_ctrlVideo.StartCapture();

}

/*******************************************************************************************************
函数名：StartAudio
描  述：对方同意音频连接。
        开始音频。
		此函数是由 CMainFrame::m_sckCommand 接收到服务器的 同意视频连接 命令后调用。
参  数：
        CCommand& cmd：
返回值：
版  本：1.0.0.1
作  者：康  林
时  间：2005-7-3 11:14:39
*******************************************************************************************************/
BOOL CVideo::StartAudio(CCommand& cmd)
{
    m_cmbUser.SetWindowText(cmd.GetPara());
	//设置远程IP、PORT
   	m_uRemoteAudioPort = cmd.GetLongPara();
    m_szRemoteIP = cmd.GetPara();
    //增加:开始音频
    return FALSE;
}

BOOL CVideo::NoAudio(CCommand& cmd)
{
    CString szUser, szUserName;
    szUser = cmd.GetPara(); //拒绝方
    szUserName = cmd.GetPara();
    MessageBox(szUser + _T(" 拒绝音频请求。"), _T("拒绝请求"));
    End();
    return FALSE;
}

BOOL CVideo::NoVideo(CCommand& cmd)
{
    CString szUser, szUserName;
    szUser = cmd.GetPara(); //拒绝方
    szUserName = cmd.GetPara();
    MessageBox(szUser + _T(" 拒绝视频请求。"), _T("拒绝请求"));
    End();
    return FALSE;
}

/*******************************************************************************************************
函数名：End
功  能：结束视频、音频及其 Socket
参  数：无
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-18
时  间：16:36:37
*******************************************************************************************************/
void CVideo::End()
{
    if(m_ctrlVideo.GetSafeHwnd())
    {
        //停止视频捕获
        m_ctrlVideo.StopCapture();
        m_ctrlVideo.DestroyWindow();
    } // 结束 if(m_ctrlVideo.GetSafeHwnd())
	    
	//关闭 Socket
	m_sckVideo.Close();
	m_sckAudio.Close();
}

/*******************************************************************************************************
函数名：AudioReceiveThread
功  能：音频接收线程
参  数：
         LPVOID lpParameter：
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-18
时  间：15:10:00
*******************************************************************************************************/
DWORD _stdcall CVideo::AudioReceiveThread(LPVOID lpParameter)
{
    TRACE(_T("%s(%d) : 接收到音频数据\n"), __FILE__, __LINE__);
	UDPSOCKREMOTEINFO* p = (UDPSOCKREMOTEINFO*)lpParameter;

	CVideo* m_pParent = (CVideo*) p->pParent; //转换为父对象
	
	
	//增加：对接收的音频数据进行处理
	//...........
	//
	//m_pParent->m_ctrlDisplayVideo.Display(p->pBuf, p->iLen);
    
	::SetEvent(*(p->phEvent));   //设置事件对象为有信号
	return 0;
}

/*******************************************************************************************************
函数名：VideoReceiveThread
功  能：视频接收线程
参  数：
         LPVOID lpParameter：
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-18
时  间：15:10:26
*******************************************************************************************************/
DWORD _stdcall CVideo::VideoReceiveThread(LPVOID lpParameter)
{
	TRACE(_T("%s(%d) : 接收到视频数据\n"), __FILE__, __LINE__);
	UDPSOCKREMOTEINFO* p = (UDPSOCKREMOTEINFO*)lpParameter;

	/*******************************************************************************************************
	CString szRemoteIP(p->szRemoteIP);
	UINT uRemotePort = p->uRemotePort;
	int iLen = p->iLen;            //复制接收的数据
	LPVOID buf = new BYTE[iLen];
	memcpy(buf, p->pBuf, iLen);   
	*******************************************************************************************************/
	CVideo* m_pParent = (CVideo*) p->pParent; //转换为父对象	
	
	//显示接收的数据
	m_pParent->m_ctrlDisplayVideo.Display((BSTR*)p->pBuf, p->iLen);
    
	::SetEvent(*(p->phEvent));   //设置事件对象为有信号
    //delete []buf;
	return 0;
}

BEGIN_EVENTSINK_MAP(CVideo, CDialog)
    //{{AFX_EVENTSINK_MAP(CVideo)
	ON_EVENT(CVideo, IDC_VIDEOCONTROL, 1 /* DisplayVideo */, OnDisplayVideo, VTS_PBSTR VTS_I4)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CVideo::OnDisplayVideo(BSTR FAR* lpData, long dwSize) 
{
	//m_sckVideo.SendDataTo(lpData, dwSize, m_uRemoteVideoPort, m_szRemoteIP);
	m_sckVideo.SendTo(lpData, dwSize, m_uRemoteVideoPort, m_szRemoteIP);
}


BOOL CVideo::GetHostName()
{
	//////////////////
	// Get host name.
	//
	char hostname[256];
	int res = gethostname(hostname, sizeof(hostname));
	if (res != 0) {
		TRACE("Error: %u\n", WSAGetLastError());
		return -1;
	}
	TRACE("hostname=%s\n", hostname);

	////////////////
	// Get host info for hostname. 
	//
	hostent* pHostent = gethostbyname(hostname);
	if (pHostent==NULL) {
		TRACE("Error: %u\n", WSAGetLastError());
		return -1;
	}

	//////////////////
	// Parse the hostent information returned
	//
	hostent& he = *pHostent;
	TRACE("name=%s\naliases=%s\naddrtype=%d\nlength=%d\n",
		he.h_name, he.h_aliases, he.h_addrtype, he.h_length);
	
	sockaddr_in sa;
	for (int nAdapter=0; he.h_addr_list[nAdapter]; nAdapter++) {
		memcpy ( &sa.sin_addr.s_addr, he.h_addr_list[nAdapter],he.h_length);
      // Output the machines IP Address.
      TRACE("Address: %s\n", inet_ntoa(sa.sin_addr)); // display as string
	}
    return true;
}

/*******************************************************************************************************
函数名：VideoSendData
描  述：发送视频数据
参  数：
        LPVOID lpData：数据
        UINT iLen    ：数据长度
返回值：
版  本：1.0.0.1
作  者：康  林
时  间：2005-7-3 9:57:40
*******************************************************************************************************/
BOOL CVideo::VideoSendData(LPVOID lpData, UINT iLen)
{
    return m_sckVideo.SendDataTo(lpData, iLen, m_uRemoteVideoPort, m_szRemoteIP);
}

/*******************************************************************************************************
函数名：VideoSendData
描  述：发送视频数据
参  数：
        CCommand& cmd：
返回值：
版  本：1.0.0.1
作  者：康  林
时  间：2005-7-3 11:21:55
*******************************************************************************************************/
BOOL CVideo::VideoSendData(CCommand& cmd)
{
     return VideoSendData(cmd.GetDataRef(), cmd.GetLength());
}

/*******************************************************************************************************
函数名：AudioSendData
描  述：发送音频数据
参  数：
        LPVOID lpData：数据
        UINT iLen    ：数据长度
返回值：
版  本：1.0.0.1
作  者：康  林
时  间：2005-7-3 9:58:15
*******************************************************************************************************/
BOOL CVideo::AudioSendData(LPVOID lpData, UINT iLen)
{
    return m_sckAudio.SendDataTo(lpData, iLen, m_uRemoteAudioPort, m_szRemoteIP);
}

/*******************************************************************************************************
函数名：AudioSendData
描  述：发送音频数据
参  数：
        CCommand& cmd：
返回值：
版  本：1.0.0.1
作  者：康  林
时  间：2005-7-3 11:21:44
*******************************************************************************************************/
BOOL CVideo::AudioSendData(CCommand& cmd)
{
    return AudioSendData(cmd.GetDataRef(), cmd.GetLength());
}

/*******************************************************************************************************
函数名：SendDataToServer
描  述：通过服务器 Sock 向服务器发送数据
参  数：
        LPVOID lpData：数据
        UINT iLen    ：数据长度
返回值：成功返回 TRUE，否则返回 FALSE
版  本：1.0.0.1
作  者：康  林
时  间：2005-7-3 11:20:34
*******************************************************************************************************/
BOOL CVideo::SendDataToServer(LPVOID lpData, UINT iLen)
{
    CMainFrame* mFrm = (CMainFrame* )AfxGetMainWnd();
    return mFrm->SendData(lpData, iLen);
}

/*******************************************************************************************************
函数名：SendDataToServer
描  述：通过服务器 Sock 向服务器发送数据
参  数：
        CCommand& cmd：
返回值：成功返回 TRUE，否则返回 FALSE
版  本：1.0.0.1
作  者：康  林
时  间：2005-7-3 11:21:22
*******************************************************************************************************/
BOOL CVideo::SendDataToServer(CCommand& cmd)
{
    return SendDataToServer(cmd.GetDataRef(), cmd.GetLength());
}