// 中国象棋服务器Doc.cpp : implementation of the CChessDoc class
//

#include "stdafx.h"
#include "中国象棋服务器.h"
#include "中国象棋服务器Doc.h"
#include "中国象棋服务器view.h"
#include "..\command\command.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChessDoc

IMPLEMENT_DYNCREATE(CChessDoc, CDocument)

BEGIN_MESSAGE_MAP(CChessDoc, CDocument)
	//{{AFX_MSG_MAP(CChessDoc)
	ON_COMMAND(IDM_USERINFO, OnUserinfo)
	ON_COMMAND(IDM_INFO, OnInfo)
	ON_COMMAND(IDM_CHAIR, OnChair)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChessDoc construction/destruction

CChessDoc::CChessDoc()
{
	// TODO: add one-time construction code here

}

CChessDoc::~CChessDoc()
{
    m_AdoConn.Close();
}

BOOL CChessDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	m_AdoConn.ConnectAccess(_T("CChessDB.mdb"));
	m_AdoRecSet.SetAdoConnection(&m_AdoConn);
	m_AdoRecSet.SetCursorLocation(adUseClient);

    //------------------------------------------------------------------------
    //以下是完成 ===生成椅子表=== 功能的语句块
    //

    //删除椅子表
    CString szSQL(_T("DROP Table Chair"));
    m_AdoRecSet.Open(szSQL);
    //生成椅子表
    szSQL = _T("Create Table Chair (ChairNo INTEGER, UserName Text, Hand INTEGER)"/*CHARACTER(50))"*/);
    if(!m_AdoRecSet.Open(szSQL))
    {
        ASSERT(0);//椅子表建立失败
        return FALSE;
    }
    for(int i = 1; i <= g_DESKNUMBER * 2; i++)
    {
        CString sztmp;
        sztmp.Format(_T("%d"), i);
        szSQL = _T("Insert into Chair(ChairNo, Hand) Values('") + sztmp + _T("', 0)");
        m_AdoRecSet.Open(szSQL);
    }

    //
    //以上是完成 ===生成椅子表=== 功能的语句块
    //------------------------------------------------------------------------
    
	//Sock
	m_sckCommand.Inital(this, ReceiveThread, g_SERVERPORT, TRUE, OverTimeThread);

 	return TRUE;
}

void CChessDoc::OnCloseDocument() 
{
	//删除椅子表
    CString szSQL(_T("DROP Table Chair"));
    m_AdoRecSet.Open(szSQL);

    szSQL = _T("Update UserInfo Set 状态 = '未登录' Where 状态 <> '未登录'");
    m_AdoRecSet.Open(szSQL);

    m_AdoConn.Close();  
	CDocument::OnCloseDocument();
}

/////////////////////////////////////////////////////////////////////////////
// CChessDoc serialization

void CChessDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CChessDoc diagnostics

#ifdef _DEBUG
void CChessDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CChessDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChessDoc commands

void CChessDoc::OnUserinfo() 
{
	// TODO: Add your command handler code here
	m_AdoRecSet.Open(_T("select * from UserInfo"));
	this->UpdateAllViews(NULL);
}

void CChessDoc::OnInfo() 
{
	m_AdoRecSet.Open(_T("Select * From Info"));
	this->UpdateAllViews(NULL);
}

void CChessDoc::OnChair() 
{
	m_AdoRecSet.Open(_T("Select * From Chair"));
	this->UpdateAllViews(NULL);
}

DWORD _stdcall CChessDoc::ReceiveThread(LPVOID lpParameter)
{
    CProcess process;
    TRACE(_T("%s(%d) :  CMainFrame::ReceiveThread\n"), __FILE__, __LINE__);
	UDPSOCKREMOTEINFO* p = (UDPSOCKREMOTEINFO*)lpParameter;
    CChessDoc * pParent = (CChessDoc * )p->pParent;  //转换为父对象    
    process.m_szIP = p->szRemoteIP;                  //客户端IP
    process.m_uPort = p->uRemotePort;                //客户端Port
    CCommand command(p->pBuf, p->iLen);              //复制接收的数据
    ::SetEvent(*(p->phEvent));                       //设置事件对象为有信号

	process.SetConnection(&pParent->m_AdoConn);
    process.SetSocket(&pParent->m_sckCommand);
    
	//对接收的数据进行处理
    long cmd;
	cmd = command.GetCommand();
    process.SetCommand(&command);
    switch(cmd)
	{
    case g_cmdExit:             //用户退出
        process.Exit();
        break;
	case g_cmdLogon:            //登录
		process.Logon();
		break;
    case g_cmdRegist:           //注册
        process.Regist();
        break;
    case g_cmdSendTextMessage:  //发送文本消息
        process.SendTextMessage();
        break;
    case g_cmdSetDown:          //入坐
        process.SetDown();
        break;
    case g_cmdStart:            //同意开始下棋
        process.Start();
        break;
    case g_cmdStandOff:         //求和
        process.StandOff();
        break;
    case g_cmdLeaveChair:       //离开椅子
        process.LeaveChair();
        break;
    case g_cmdGiveup:           //认输
        process.Giveup();
        break;
    case g_cmdVideoConn:        //视频连接
        process.VideoConn();
        break;
    case g_cmdAudioConn:        //音频连接
        process.AudioConn();
        break;
    case g_cmdAgreeVideoConn:   //同意视频连接
        process.AgreeVideoConn();
        break;
    case g_cmdAgreeAudioConn:   //同意音频连接
        process.AgreeAudioConn();
        break;
    case g_cmdNoVideo:          //不同意视频连接
        process.NoAgreeVideo();
        break;
    case g_cmdNoAudio:          //不同意音频连接
        process.NoAgreeAudio();
        break;
	}
	
	return 0;
}

DWORD _stdcall CChessDoc::OverTimeThread(LPVOID lpParameter)
{
    UDPSOCKREMOTEINFO* p = (UDPSOCKREMOTEINFO* )lpParameter;
    CChessDoc* pParent = (CChessDoc* )p->pParent;
    TRACE(_T("%s(%d) : 超时\n"), __FILE__, __LINE__);
    return 0;
}

