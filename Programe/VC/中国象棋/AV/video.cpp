/*******************************************************************************************************
�ļ�����video.cpp
��  �ܣ������Ƶ����Ƶ�ķ��͡����ա�
��  ����
        1������������Ƶ����Ƶ����
		   1.1�������ص����Ƶʱ���� OnVideoClick �е���  Initializtion() ��ʼ����Ƶ�ؼ�����Ƶ������ Socket
		   1.2���ѱ����û�����IP��VIDEOPORT��AUDIOPORT �� CMainFrame::m_sckCommand ���� ������Ƶ���� ���������
		   1.3������Է�ͬ����Ƶ������� Start
		   1.4������Է���ͬ�⣬����� End ������Ƶ����Ƶ���� Socket
		2��Զ��������Ƶ����Ƶ����
		   1.1���� CMainFrame::m_sckCommand ���� Connect ����
		   1.2�������ͬ�⣬���� CMainFrame::m_sckCommand ���� ��ͬ����Ƶ���� ����
		   1.3�����ͬ�����ӣ������ Initializtion() ��ʼ����Ƶ�ؼ�����Ƶ������ Socket
		   1.4������ CMainFrame::m_sckCommand ���� ͬ����Ƶ���� ���
		        �������û���������IP��VIDEOPORT��AUDIOPORT
		   1.5������ Start ��ʼ��Ƶ����Ƶ
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-12-18
ʱ  �䣺15:44:25

FileName��video.cpp
Function��
Compiler��Visual C++ 6.0
Author��  KangLin
          Copyright 2004 KangLin
Date��    2004-12-18
Time��    15:44:25
*******************************************************************************************************/
// video.cpp : implementation file
//

#include "stdafx.h"
#include "..\�й�����.h"
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
	m_butVideo.Create(_T("��Ƶ"), WS_CHILD | WS_VISIBLE, CRect(0, 0, 100, 50), this, IDC_BUTTONVIDEO);

	m_butVideo.SetIcon(IDI_VIDEO);
	m_butVideo.SetRounded(TRUE);
    m_butVideo.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_butVideo.SetTooltipText(_T("��ʼ��Ƶ"));

	return 0;
}

void CVideo::OnVideoClick()
{
	m_StartVideo = m_StartVideo ? FALSE : TRUE;
	if(m_StartVideo)
	{
		m_butVideo.SetTooltipText(_T("������Ƶ"));
		
		Initializtion();
	}
	else
	{
		m_butVideo.SetTooltipText(_T("��ʼ��Ƶ"));
		
		End();
	}
}

/*******************************************************************************************************
��������VideoConnect
��  �����Է� ������Ƶ���� �����ʾ���ӶԻ���
��  ����
        CCommand& cmd��
����ֵ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-7-3 10:16:16
*******************************************************************************************************/
BOOL CVideo::VideoConnect(CCommand& cmd)
{
    CString szUser, szUserName, szIP;
    UINT uPort;
    szUser = cmd.GetPara();
    szUserName = ((CChessApp* )AfxGetApp())->m_gszUserName; //�����û���
    uPort = cmd.GetLongPara();
    szIP = cmd.GetPara();
	int iR;
    iR = MessageBox(szUser + _T("���������ӣ�"), _T("��Ƶ��������"), MB_YESNO | MB_ICONQUESTION);
    if(iR = IDOK)
    {
        m_uRemoteVideoPort = uPort;
        m_szRemoteIP = szIP;
        m_cmbUser.SetWindowText(szUser);
        m_butVideo.SetTooltipText(_T("������Ƶ"));
        Initializtion(TRUE);
        //������������
        CCommand cmd;
        cmd.SetCommand(g_cmdVideoHand);
        VideoSendData(cmd);
    }
    else //��ͬ������
    {
        CCommand cmd;
        cmd.SetCommand(g_cmdNoVideo);
        cmd.AddPara(szUserName);  //�����û���
        cmd.AddPara(szUser);      //�Է��û���
        SendDataToServer(cmd);
        return FALSE;
    } // ���� if(iR = IDOK)
	return TRUE;
}

/*******************************************************************************************************
��������AudioConnect
��  �����Է� ������Ƶ���� �����ʾ���ӶԻ���
��  ����
        CCommand& cmd��
����ֵ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-7-3 10:16:37
*******************************************************************************************************/
BOOL CVideo::AudioConnect(CCommand& cmd)
{
    CString szUser, szUserName, szIP;
    UINT uPort;
    szUser = cmd.GetPara();
    szUserName = ((CChessApp* )AfxGetApp())->m_gszUserName; //�����û���
    uPort = cmd.GetLongPara();
    szIP = cmd.GetPara();
	int iR;
    iR = MessageBox(szUser + _T("���������ӣ�"), _T("��Ƶ��������"), MB_YESNO | MB_ICONQUESTION);
    if(iR = IDOK)
    {
        m_uRemoteVideoPort = uPort;
        m_szRemoteIP = szIP;
        m_cmbUser.SetWindowText(szUser);        
        Initializtion(TRUE);
        //������������
        CCommand cmd;
        cmd.SetCommand(g_cmdAudioHand);
        VideoSendData(cmd);
    }
    else //��ͬ������
    {
        CCommand cmd;
        cmd.SetCommand(g_cmdNoAudio);
        cmd.AddPara(szUserName);  //�����û���
        cmd.AddPara(szUser);      //�Է��û���
        SendDataToServer(cmd);
        return FALSE;
    } // ���� if(iR = IDOK)
	return TRUE;
}

/*******************************************************************************************************
��������Initializtion
��  ������ʼ����Ƶ�ؼ�����Ƶ����Socket����������������������������
��  ����
        BOOL bAgree�����Ϊ TRUE��ͬ�����ӣ�FALSE���������ӡ�Ĭ��Ϊ TRUE
����ֵ���ɹ����� TRUE�����򷵻� FALSE
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-7-3 10:20:51
*******************************************************************************************************/
BOOL CVideo::Initializtion(BOOL bAgree)
{
    //�õ��������ĵ�ַ�Ͷ˿�
    CMainFrame* m_pMainWnd = (CMainFrame*)AfxGetMainWnd();
    m_pMainWnd->GetServerAddress(&m_szServerIP, &m_uServerPort);

	//��ʼ����Ƶ�ؼ�
    if(m_ctrlVideo.GetSafeHwnd() == NULL)
    {
        if(m_ctrlVideo.Create(_T("������Ƶ"), WS_CHILD | WS_VISIBLE, CRect(0, 0, 100, 100), this, IDC_VIDEOCONTROL))
        {
            //��Ƶ Socket
            if(!m_sckVideo.Inital(this, VideoReceiveThread))
            {
                return FALSE;
            } // ���� if(!m_sckVideo.Inital(this, VideoReceiveThread))
            //�����������������Ϣ
            CCommand cmd;
            if(!bAgree)
            {
                cmd.SetCommand(g_cmdVideoConn);
            }
            else
            {
                cmd.SetCommand(g_cmdAgreeVideoConn);
            } // ���� if(!bAgree)

            CString szUser;
            m_cmbUser.GetWindowText(szUser);
            if(szUser == "" || szUser == ((CChessApp * )AfxGetApp())->m_gszUserName)
            {
                End();
                MessageBox(_T("û��ѡ��Է�����ѡȡ�û���"), _T("��ѡȡ�û�"));
                return FALSE;
            } // ���� if(szUser == "" || szUser == ((CChessApp * )AfxGetApp())->m_gszUserName)
            cmd.AddPara(szUser);
            cmd.AddPara(((CChessApp * )AfxGetApp())->m_gszUserName);
            m_sckVideo.SendDataTo(cmd.GetDataRef(), cmd.GetLength(), m_uServerPort, m_szServerIP);
        }
    } // ���� if(m_ctrlVideo.GetSafeHwnd() == NULL)

	//����:��ʼ����Ƶ

	//��Ƶ Socket	
	if(!m_sckAudio.Inital(this, AudioReceiveThread))
    {
        return FALSE;
    } // ���� if(!m_sckAudio.Inital(this, AudioReceiveThread))
    //�����������������Ϣ
    CCommand cmd;
    if(!bAgree)
    {
        cmd.SetCommand(g_cmdAudioConn); 
    }
    else
    {
        cmd.SetCommand(g_cmdAgreeAudioConn);
    } // ���� if(!bAgree)
    
    cmd.AddPara(((CChessApp * )AfxGetApp())->m_gszUserName);
    CString szUser;
    m_cmbUser.GetWindowText(szUser);
    if(szUser == "" || ((CChessApp * )AfxGetApp())->m_gszUserName)
    {
        //����:�ر���Ƶ
        End();
        MessageBox(_T("û��ѡ��Է�����ѡȡ�û���"), _T("��ѡȡ�û�"));
        return FALSE;
    } // ���� if(szUser == "" || ((CChessApp * )AfxGetApp())->m_gszUserName)
    cmd.AddPara(szUser);
    m_sckAudio.SendDataTo(cmd.GetDataRef(), cmd.GetLength(), m_uServerPort, m_szServerIP);
    return TRUE;
}

/*******************************************************************************************************
��������StartVideo
��  �����Է�ͬ����Ƶ���ӡ�
        ��ʼ��Ƶ��
		�˺������� CMainFrame::m_sckCommand ���յ��������� ͬ����Ƶ���� �������á�
��  ����
        CCommand& cmd��
����ֵ���ɹ�����TRUE�����򷵻�FALSE
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-7-3 11:05:57
*******************************************************************************************************/
BOOL CVideo::StartVideo(CCommand& cmd)
{
    m_cmbUser.SetWindowText(cmd.GetPara());
	//����Զ��IP��PORT
   	m_uRemoteVideoPort = cmd.GetLongPara();
    m_szRemoteIP = cmd.GetPara();
    ((CMainFrame*)AfxGetMainWnd())->m_TabCtrl.SetActivePage(2);
	//��ʼ��Ƶ����
    return m_ctrlVideo.StartCapture();

}

/*******************************************************************************************************
��������StartAudio
��  �����Է�ͬ����Ƶ���ӡ�
        ��ʼ��Ƶ��
		�˺������� CMainFrame::m_sckCommand ���յ��������� ͬ����Ƶ���� �������á�
��  ����
        CCommand& cmd��
����ֵ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-7-3 11:14:39
*******************************************************************************************************/
BOOL CVideo::StartAudio(CCommand& cmd)
{
    m_cmbUser.SetWindowText(cmd.GetPara());
	//����Զ��IP��PORT
   	m_uRemoteAudioPort = cmd.GetLongPara();
    m_szRemoteIP = cmd.GetPara();
    //����:��ʼ��Ƶ
    return FALSE;
}

BOOL CVideo::NoAudio(CCommand& cmd)
{
    CString szUser, szUserName;
    szUser = cmd.GetPara(); //�ܾ���
    szUserName = cmd.GetPara();
    MessageBox(szUser + _T(" �ܾ���Ƶ����"), _T("�ܾ�����"));
    End();
    return FALSE;
}

BOOL CVideo::NoVideo(CCommand& cmd)
{
    CString szUser, szUserName;
    szUser = cmd.GetPara(); //�ܾ���
    szUserName = cmd.GetPara();
    MessageBox(szUser + _T(" �ܾ���Ƶ����"), _T("�ܾ�����"));
    End();
    return FALSE;
}

/*******************************************************************************************************
��������End
��  �ܣ�������Ƶ����Ƶ���� Socket
��  ������
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-18
ʱ  �䣺16:36:37
*******************************************************************************************************/
void CVideo::End()
{
    if(m_ctrlVideo.GetSafeHwnd())
    {
        //ֹͣ��Ƶ����
        m_ctrlVideo.StopCapture();
        m_ctrlVideo.DestroyWindow();
    } // ���� if(m_ctrlVideo.GetSafeHwnd())
	    
	//�ر� Socket
	m_sckVideo.Close();
	m_sckAudio.Close();
}

/*******************************************************************************************************
��������AudioReceiveThread
��  �ܣ���Ƶ�����߳�
��  ����
         LPVOID lpParameter��
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-18
ʱ  �䣺15:10:00
*******************************************************************************************************/
DWORD _stdcall CVideo::AudioReceiveThread(LPVOID lpParameter)
{
    TRACE(_T("%s(%d) : ���յ���Ƶ����\n"), __FILE__, __LINE__);
	UDPSOCKREMOTEINFO* p = (UDPSOCKREMOTEINFO*)lpParameter;

	CVideo* m_pParent = (CVideo*) p->pParent; //ת��Ϊ������
	
	
	//���ӣ��Խ��յ���Ƶ���ݽ��д���
	//...........
	//
	//m_pParent->m_ctrlDisplayVideo.Display(p->pBuf, p->iLen);
    
	::SetEvent(*(p->phEvent));   //�����¼�����Ϊ���ź�
	return 0;
}

/*******************************************************************************************************
��������VideoReceiveThread
��  �ܣ���Ƶ�����߳�
��  ����
         LPVOID lpParameter��
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-18
ʱ  �䣺15:10:26
*******************************************************************************************************/
DWORD _stdcall CVideo::VideoReceiveThread(LPVOID lpParameter)
{
	TRACE(_T("%s(%d) : ���յ���Ƶ����\n"), __FILE__, __LINE__);
	UDPSOCKREMOTEINFO* p = (UDPSOCKREMOTEINFO*)lpParameter;

	/*******************************************************************************************************
	CString szRemoteIP(p->szRemoteIP);
	UINT uRemotePort = p->uRemotePort;
	int iLen = p->iLen;            //���ƽ��յ�����
	LPVOID buf = new BYTE[iLen];
	memcpy(buf, p->pBuf, iLen);   
	*******************************************************************************************************/
	CVideo* m_pParent = (CVideo*) p->pParent; //ת��Ϊ������	
	
	//��ʾ���յ�����
	m_pParent->m_ctrlDisplayVideo.Display((BSTR*)p->pBuf, p->iLen);
    
	::SetEvent(*(p->phEvent));   //�����¼�����Ϊ���ź�
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
��������VideoSendData
��  ����������Ƶ����
��  ����
        LPVOID lpData������
        UINT iLen    �����ݳ���
����ֵ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-7-3 9:57:40
*******************************************************************************************************/
BOOL CVideo::VideoSendData(LPVOID lpData, UINT iLen)
{
    return m_sckVideo.SendDataTo(lpData, iLen, m_uRemoteVideoPort, m_szRemoteIP);
}

/*******************************************************************************************************
��������VideoSendData
��  ����������Ƶ����
��  ����
        CCommand& cmd��
����ֵ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-7-3 11:21:55
*******************************************************************************************************/
BOOL CVideo::VideoSendData(CCommand& cmd)
{
     return VideoSendData(cmd.GetDataRef(), cmd.GetLength());
}

/*******************************************************************************************************
��������AudioSendData
��  ����������Ƶ����
��  ����
        LPVOID lpData������
        UINT iLen    �����ݳ���
����ֵ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-7-3 9:58:15
*******************************************************************************************************/
BOOL CVideo::AudioSendData(LPVOID lpData, UINT iLen)
{
    return m_sckAudio.SendDataTo(lpData, iLen, m_uRemoteAudioPort, m_szRemoteIP);
}

/*******************************************************************************************************
��������AudioSendData
��  ����������Ƶ����
��  ����
        CCommand& cmd��
����ֵ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-7-3 11:21:44
*******************************************************************************************************/
BOOL CVideo::AudioSendData(CCommand& cmd)
{
    return AudioSendData(cmd.GetDataRef(), cmd.GetLength());
}

/*******************************************************************************************************
��������SendDataToServer
��  ����ͨ�������� Sock ���������������
��  ����
        LPVOID lpData������
        UINT iLen    �����ݳ���
����ֵ���ɹ����� TRUE�����򷵻� FALSE
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-7-3 11:20:34
*******************************************************************************************************/
BOOL CVideo::SendDataToServer(LPVOID lpData, UINT iLen)
{
    CMainFrame* mFrm = (CMainFrame* )AfxGetMainWnd();
    return mFrm->SendData(lpData, iLen);
}

/*******************************************************************************************************
��������SendDataToServer
��  ����ͨ�������� Sock ���������������
��  ����
        CCommand& cmd��
����ֵ���ɹ����� TRUE�����򷵻� FALSE
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-7-3 11:21:22
*******************************************************************************************************/
BOOL CVideo::SendDataToServer(CCommand& cmd)
{
    return SendDataToServer(cmd.GetDataRef(), cmd.GetLength());
}