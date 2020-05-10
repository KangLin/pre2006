// �й����������Doc.cpp : implementation of the CChessDoc class
//

#include "stdafx.h"
#include "�й����������.h"
#include "�й����������Doc.h"
#include "�й����������view.h"
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
    //��������� ===�������ӱ�=== ���ܵ�����
    //

    //ɾ�����ӱ�
    CString szSQL(_T("DROP Table Chair"));
    m_AdoRecSet.Open(szSQL);
    //�������ӱ�
    szSQL = _T("Create Table Chair (ChairNo INTEGER, UserName Text, Hand INTEGER)"/*CHARACTER(50))"*/);
    if(!m_AdoRecSet.Open(szSQL))
    {
        ASSERT(0);//���ӱ���ʧ��
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
    //��������� ===�������ӱ�=== ���ܵ�����
    //------------------------------------------------------------------------
    
	//Sock
	m_sckCommand.Inital(this, ReceiveThread, g_SERVERPORT, TRUE, OverTimeThread);

 	return TRUE;
}

void CChessDoc::OnCloseDocument() 
{
	//ɾ�����ӱ�
    CString szSQL(_T("DROP Table Chair"));
    m_AdoRecSet.Open(szSQL);

    szSQL = _T("Update UserInfo Set ״̬ = 'δ��¼' Where ״̬ <> 'δ��¼'");
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
    CChessDoc * pParent = (CChessDoc * )p->pParent;  //ת��Ϊ������    
    process.m_szIP = p->szRemoteIP;                  //�ͻ���IP
    process.m_uPort = p->uRemotePort;                //�ͻ���Port
    CCommand command(p->pBuf, p->iLen);              //���ƽ��յ�����
    ::SetEvent(*(p->phEvent));                       //�����¼�����Ϊ���ź�

	process.SetConnection(&pParent->m_AdoConn);
    process.SetSocket(&pParent->m_sckCommand);
    
	//�Խ��յ����ݽ��д���
    long cmd;
	cmd = command.GetCommand();
    process.SetCommand(&command);
    switch(cmd)
	{
    case g_cmdExit:             //�û��˳�
        process.Exit();
        break;
	case g_cmdLogon:            //��¼
		process.Logon();
		break;
    case g_cmdRegist:           //ע��
        process.Regist();
        break;
    case g_cmdSendTextMessage:  //�����ı���Ϣ
        process.SendTextMessage();
        break;
    case g_cmdSetDown:          //����
        process.SetDown();
        break;
    case g_cmdStart:            //ͬ�⿪ʼ����
        process.Start();
        break;
    case g_cmdStandOff:         //���
        process.StandOff();
        break;
    case g_cmdLeaveChair:       //�뿪����
        process.LeaveChair();
        break;
    case g_cmdGiveup:           //����
        process.Giveup();
        break;
    case g_cmdVideoConn:        //��Ƶ����
        process.VideoConn();
        break;
    case g_cmdAudioConn:        //��Ƶ����
        process.AudioConn();
        break;
    case g_cmdAgreeVideoConn:   //ͬ����Ƶ����
        process.AgreeVideoConn();
        break;
    case g_cmdAgreeAudioConn:   //ͬ����Ƶ����
        process.AgreeAudioConn();
        break;
    case g_cmdNoVideo:          //��ͬ����Ƶ����
        process.NoAgreeVideo();
        break;
    case g_cmdNoAudio:          //��ͬ����Ƶ����
        process.NoAgreeAudio();
        break;
	}
	
	return 0;
}

DWORD _stdcall CChessDoc::OverTimeThread(LPVOID lpParameter)
{
    UDPSOCKREMOTEINFO* p = (UDPSOCKREMOTEINFO* )lpParameter;
    CChessDoc* pParent = (CChessDoc* )p->pParent;
    TRACE(_T("%s(%d) : ��ʱ\n"), __FILE__, __LINE__);
    return 0;
}

