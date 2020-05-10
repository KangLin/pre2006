// �й�����View.cpp : implementation of the CChessView class
//

#include "stdafx.h"
#include "..\�й�����.h"
#include "..\MainFrm.h"
#include "..\�й�����Doc.h"
#include "�й�����View.h"
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
    //����:���������ò���

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
    //���ô��ڱ���
    GetParent()->SetWindowText(_T("����"));
    m_pChessApp = (CChessApp*)AfxGetApp();
	//�����������������ͼָ��
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
    //�����������������ͼָ��
    m_pMainWnd->m_pChessView = NULL;
    m_pMainWnd->m_iView = CMainFrame::DESK_ENUM;
}

void CChessView::OnDraw(CDC* pDC) 
{
    //����ͼƬ
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
��������SetRemoteUserName
��  �ܣ����öԷ��û���,����ʾ�Է��û���
��  ����
         LPCSTR szUser���Է��û���
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-17
ʱ  �䣺21:44:04
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
        } //���� if(m_szRemoteUserName == _T(""))
    }
}

/*******************************************************************************************************
��������SetLocateUserName
��  �ܣ����ñ����û���,����ʾ�û���
��  ������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-17
ʱ  �䣺21:49:50
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
��������SendDataToServer
��  �ܣ����������������
��  ����
         CCommand &cmd������
����ֵ���ɹ����� TRUE�����򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-3
ʱ  �䣺16:15:28
*******************************************************************************************************/
BOOL CChessView::SendDataToServer(CCommand &cmd)
{
    return SendDataToServer(cmd.GetDataRef(), cmd.GetLength());
}

/*******************************************************************************************************
��������SendDataToServer
��  �ܣ�
��  ����
         LPVOID lpData������
         INT iLen�����ݵĳ���
����ֵ���ɹ����� TRUE�����򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-3
ʱ  �䣺16:15:52
*******************************************************************************************************/
BOOL CChessView::SendDataToServer(LPVOID lpData, INT iLen)
{
    return m_sckChess.SendDataTo(lpData, iLen, m_uServerPort, m_szServerIP);
}

/*******************************************************************************************************
��������SetRemoteAddress
��  �ܣ����öԷ�����ؼ��ĵ�ַ
��  ����
         CString szIP���Է�IP
         UINT uPort���Է�Port
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-3
ʱ  �䣺16:20:04
*******************************************************************************************************/
BOOL CChessView::SetRemoteAddress(CString szIP, UINT uPort)
{
    m_szRemoteIP = szIP;
    m_uRemotePort = uPort;
    return TRUE;
}

/*******************************************************************************************************
��������SendData
��  �ܣ���Է�����ؼ���������
��  ����
         CCommand &cmd������
����ֵ���ɹ����� TRUE�����򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-3
ʱ  �䣺16:13:45
*******************************************************************************************************/
BOOL CChessView::SendData(CCommand &cmd)
{
    return SendData(cmd.GetDataRef(), cmd.GetLength());
}

/*******************************************************************************************************
��������SendData
��  �ܣ���Է�����ؼ���������
��  ����
         LPVOID lpData������
         INT iLen�����ݵĳ���
����ֵ���ɹ����� TRUE�����򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-3
ʱ  �䣺16:11:31
*******************************************************************************************************/
BOOL CChessView::SendData(LPVOID lpData, INT iLen)
{
    return m_sckChess.SendDataTo(lpData, iLen, m_uRemotePort, m_szRemoteIP);
}

DWORD _stdcall CChessView::ReceiveThread(LPVOID lpParameter)
{
    TRACE(_T("%s(%d) : CChess::ReceiveThread,�̺߳�:%x\n"), __FILE__, __LINE__, ::GetCurrentThreadId());
    UDPSOCKREMOTEINFO* p = (UDPSOCKREMOTEINFO*)lpParameter;
    CString szRemoteIP(p->szRemoteIP);
    UINT uRemotePort = p->uRemotePort;
    CCommand command(p->pBuf, p->iLen);            //�����������
    CChessView* pParent = (CChessView*) p->pParent;//ת���ɸ�����ָ��
    ::SetEvent(*(p->phEvent));

    //����:���յ��������
    long cmd;
    cmd = command.GetCommand();
    switch (cmd)
    {
    case g_cmdHand:              //����
        TRACE(_T("%s(%d) : ��������\n"), __FILE__, __LINE__);
        pParent->Hand(command);
        break;
    case g_cmdReceivedPara:      //ȷ�����ò���
        pParent->ReceivedPara(command);
        break;
    case g_cmdChairInfo:         //������Ϣ
        pParent->m_pMainWnd->m_pDeskView->SetChair(&command);
        break;
    case g_cmdSetDown:           //����
        pParent->SetDown(command);
        break;
    case g_cmdOtherSetDown:      //�Է�����
        pParent->OtherSetDown(command);
        break;
    case g_cmdStart:             //ͬ�⿪ʼ����
        pParent->Start(command);
        break;
    case g_cmdPlayChess:
        pParent->PlayChess(command);
        break;
    case g_cmdChess:             //��������
        pParent->WalkChess(command);
        break;
    case g_cmdRepent:            //����
        pParent->RepentChess();
        break;
    case g_cmdReceiveRepent:     //���ܻ���
        pParent->ReceiveRepent(command);
        break;
    case g_cmdStandOff:          //�������
        pParent->StandOff();
        break;
    case g_cmdReceivedStandOff:  //���ܺ���
        pParent->ReceivedStandOff(&command, TRUE);
        break;
    case g_cmdGiveup:            //����
        pParent->Giveup();
        break;
    }
    return 0;
}

/*******************************************************************************************************
��������OnChessClose
��  �����˳�����
��  ������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-11 13:26:58
*******************************************************************************************************/
void CChessView::OnChessClose() 
{
    if(m_CurState == PLAYCHESS)
    {
        INT iR = MessageBox(_T("�������壬������˳���������������������Ƿ��˳���"), _T("�˳�����"), MB_OKCANCEL | MB_ICONQUESTION);
        if(iR == IDCANCEL)
        {
            return;
        }
        else
        {
            OnChessGiveup();
        }//���� if(iR == IDCANCEL)
    } //���� if(m_CurState == PLAYCHESS)
    Exit();
}

void CChessView::OnUpdateChessClose(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

/*******************************************************************************************************
��������OnChessGiveup
��  ��������
��  ������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-11 13:27:26
*******************************************************************************************************/
void CChessView::OnChessGiveup() 
{
    CCommand cmd;
    cmd.SetCommand(g_cmdGiveup);
    cmd.AddPara(m_pChessApp->m_gszUserName);  //���䷽
    cmd.AddPara(m_szRemoteUserName);          //Ӯ��
    cmd.AddPara(m_Sets.uAdd);                 //�ӷ�ֵ
    cmd.AddPara(m_Sets.uInc);                 //����ֵ
    //����:���������ò���
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
��������OnChessRepent
��  ��������
��  ������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-11 13:27:40
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
��������OnChessSet
��  ���������������
��  ������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-11 13:27:53
*******************************************************************************************************/
void CChessView::OnChessSet() 
{
    CSetDlg sd;
    sd.m_uAddPoint = m_Sets.uAdd;
    sd.m_dwStep = m_Sets.dwStep;
    sd.m_uIncPoint = m_Sets.uInc;
    //����:���������ò���

    if(sd.DoModal() == IDOK)
    {
        m_tmpSets.bSet = TRUE;
        m_tmpSets.uAdd = sd.m_uAddPoint;
        m_tmpSets.dwStep = sd.m_dwStep;
        m_tmpSets.uInc = sd.m_uIncPoint;
    } //���� if(sd.DoModal() == IDOK)
}

void CChessView::OnUpdateChessSet(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(!(m_CurState & (PLAYCHESS | START)));
}

/*******************************************************************************************************
��������OnChessStandoff
��  �������
��  ������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-11 13:31:56
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
��������OnChessStart
��  ������ʼ
��  ������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-11 13:32:36
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
��������SetDown
��  �ܣ����������
��  ����
         CCommand& cmd���������(����״̬)
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-4
ʱ  �䣺17:15:39
*******************************************************************************************************/
void CChessView::SetDown(CCommand& cmd)
{
    CString szUser;
    CString szExIP, szExPort, szExChessPort;
    CString szIP, szPort, szChessPort;
    long command;
    command = cmd.GetLongPara();
    m_ctrXQ.EnableWindow(FALSE);
    if(command == g_cmdOtherNoMan) //�Է�û����
    {
        m_ctrXQ.SetQiPangLayout(CXQ::NoQi);
        m_ctrXQ.ShowWindow(SW_SHOW);
        //TRACE(_T("%s(%d) : �Է�û����\n"), __FILE__, __LINE__);
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
    case g_cmdOtherNoMan: //�Է�û����
        m_ctrXQ.SetQiPangLayout(CXQ::NoQi);
        break;
    case g_cmdOtherSetDown: //�Է�����,��û��ʼ
        m_ctrXQ.SetQiPangLayout(CXQ::NoQi);
        m_RemoteState = SETDOWN;
        //TRACE(_T("%s(%d) : �Է�����\n"), __FILE__, __LINE__);
        break;
    case g_cmdOtherStart:   //�Է������ҿ�ʼ
        m_RemoteState = START;
        m_ctrXQ.SetQiPangLayout(CXQ::OnlyTopRed);
        //TRACE(_T("%s(%d) : �Է���������ʼ\n"), __FILE__, __LINE__);
        break;
    default:
        return;
    }
    SetRemoteUserName(m_szRemoteUserName);
    m_ctrXQ.ShowWindow(SW_SHOW);
    m_CurState = SETDOWN;
    /*TRACE(_T("%s(%d) : �ⲿIP=%s,�ⲿPort=%s,�ڲ�IP=%s,�ڲ�Port=%s,�ⲿChessPort=%s,InChessPort=%s\n"),
        __FILE__, __LINE__, szExIP, szExPort,szIP, szPort,szExChessPort, szChessPort);//*/

}

/*******************************************************************************************************
��������OtherSetDown
��  �ܣ�����Է���������
��  ����
         CCommand &cmd���������(�û���)
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-4
ʱ  �䣺17:26:30
*******************************************************************************************************/
void CChessView::OtherSetDown(CCommand &cmd)
{
    CString szUserName;    //�û���
    CString szExIP;        //�ⲿIP
    CString szExPort;      //�ⲿPport
    CString szIP;          //�ڲ�IP
    CString szPort;        //�ڲ�Port
    CString szExChessPort; //�ⲿ����Port
    CString szChessPort;   //�ڲ�����Port

    szUserName = cmd.GetPara();
    szExIP = cmd.GetPara();
    szExPort = cmd.GetPara();
    szIP = cmd.GetPara();
    szPort = cmd.GetPara();
    szExChessPort = cmd.GetPara();
    szChessPort = cmd.GetPara();
 
    SetRemoteUserName(szUserName);
    //���ӣ�IP��Port
    m_RemoteState = SETDOWN;
    //TRACE(_T("%s(%d) : �Է�����\n"), __FILE__, __LINE__);
}

/*******************************************************************************************************
��������Close
��  �ܣ��ر�
��  ������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-4
ʱ  �䣺9:51:32
*******************************************************************************************************/
void CChessView::Close()
{
    CCommand cmd;
    //�뿪��λ
    cmd.SetCommand(g_cmdLeaveChair);
    cmd.AddPara(m_pChessApp->m_gszUserName);
    cmd.AddPara(m_lChairNo);
    cmd.AddPara(m_szRemoteUserName);
    ASSERT(AfxIsValidAddress(m_pMainWnd, sizeof(m_pMainWnd)));
    ASSERT(IsWindow(m_pMainWnd->GetSafeHwnd()));
    m_pMainWnd->SendData(&cmd);
    //SendDataToServer(cmd);
    
    TRACE(_T("%s(%d) : %s �뿪��λ %d\n"), __FILE__, __LINE__, m_pChessApp->m_gszUserName, m_lChairNo);
}

/*******************************************************************************************************
��������Exit
��  �ܣ��˳���ͼ
��  ������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-4
ʱ  �䣺9:51:28
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
        MessageBox(m_szRemoteUserName + _T(" �뿪��λ��"), _T("�뿪��λ"), MB_ICONINFORMATION);
        SetRemoteUserName(_T(""));
    } //���� if(szUser == m_szRemoteUserName)
}

/*******************************************************************************************************
��������OtherExit
��  �ܣ�����Է��˳�
��  ����
         CCommand &cmd���Է��û���
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-5
ʱ  �䣺11:56:06
*******************************************************************************************************/
void CChessView::OtherExit(CCommand &cmd)
{
    CString szUser;
    szUser = cmd.GetPara();
    if(szUser != m_szRemoteUserName) //���ǶԷ��û��˳�
    {
        TRACE(_T("%s(%d) : ���ǶԷ��û��˳�\n"), __FILE__, __LINE__);
        return;
    }
    //����:����Է��û��˳�
    MessageBox(m_szRemoteUserName + _T(" �˳���"), _T(" �˳�"), MB_ICONINFORMATION);
    m_szRemoteUserName = _T("");
    SetRemoteUserName(m_szRemoteUserName);
}

/*******************************************************************************************************
��������Start
��  �ܣ�ͬ�⿪ʼ
��  ����
         Command &cmd��
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-19
ʱ  �䣺18:01:25
*******************************************************************************************************/
void CChessView::Start(CCommand &cmd)
{
    CString szUser, szUserName;
    szUser = cmd.GetPara(); //���߷�
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
        } //���� if(szUserName != _T(""))
        m_RemoteState = START;
       
    } //���� if(szUser == m_szRemoteUserName)
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
        } //���� if(szUserName != _T(""))
        m_CurState = START;
    } //���� if(szUser == m_pChessApp->m_gszUserName)
    //TRACE(_T("%s(%d) : %s ͬ�⿪ʼ����\n"), __FILE__, __LINE__, szUser);
}

/*******************************************************************************************************
��������PlayChess
��  �ܣ���ʽ��ʼ����ʱ�ĳ�ʼ������
��  ������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-19
ʱ  �䣺17:22:33
*******************************************************************************************************/
void CChessView::PlayChess(CCommand &cmd)
{
    CString szUser, szUserName;
    CString szIP, szIP1;
    UINT uPort, uPort1;
    szUser = cmd.GetPara();        //���߷�
    szIP = cmd.GetPara();
    uPort = _ttol(cmd.GetPara());
    szUserName = cmd.GetPara();    //���߷�
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
    } //���� if(szUser == m_szRemoteUserName)
    if(szUser == m_pChessApp->m_gszUserName)
    {
        m_ctrXQ.SetStartSide(CXQ::BlackReadly);
    } //���� if(szUser == m_pChessApp->m_gszUserName)
    if(szUserName == m_szRemoteUserName)
    {
        m_szRemoteIP = szIP1;
        m_uRemotePort = uPort1;
        //TRACE(_T("%s(%d) : szIP:%s, uPort:%d\n"), __FILE__, __LINE__, szIP1, uPort1);
        SendHand();
    } //���� if(szUserName == m_szRemoteUserName)
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
��������SendHand
��  ��������������Ϣ��ͬʱ����������Ϣ
��  ������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-10 17:23:39
*******************************************************************************************************/
void CChessView::SendHand()
{
    CCommand cmd;
    cmd.SetCommand(g_cmdHand);
    cmd.AddPara(m_tmpSets.bSet);
    cmd.AddPara(m_tmpSets.dwStep);
    cmd.AddPara(m_tmpSets.uAdd);
    cmd.AddPara(m_tmpSets.uInc);
    //����:���������ò���

    SendData(cmd);
}

/*******************************************************************************************************
��������Hand
��  ����������������
��  ����
         CCommand& cmd������������ݰ�
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-10 17:26:56
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
    //����:���������ò���

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
            //���ͽ���ȷ������
            CCommand cmd;
            cmd.SetCommand(g_cmdReceivedPara);
            SendData(cmd);
        } //���� if(sd.DoModal() == IDOK)
    } //���� if(bSet)
}

void CChessView::ReceivedPara(CCommand & cmd)
{
    MessageBox(m_szRemoteUserName + _T(" �����˲�������"), _T(" �����˲�������"));
    memcpy(&m_Sets, &m_tmpSets, sizeof(Sets));
}

/*******************************************************************************************************
��������WalkChess
��  ��������,���ڽ��նԷ�����
��  ����
         CCommand & cmd������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-10 8:53:24
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
    } //���� if(m_ctrXQ.GetStartSide() == CXQ::RedReadly || m_ctrXQ.GetStartSide() == CXQ::BlackReadly)
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
    } //���� if(m_ctrXQ.GetStartSide() == CXQ::RedWalked || m_ctrXQ.GetStartSide() == CXQ::BlackWalked)
}

/*******************************************************************************************************
��������ShowTiShi
��  ��������ʱ�Ƿ���ʾ��ʾ��
��  ������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-10 9:06:01
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
    }//���� if(m_TiShi.IsWindowVisible())
}

/*******************************************************************************************************
��������RepentChess
��  ���������������
��  ����
         CCommand& cmd�������������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-11 7:21:24
*******************************************************************************************************/
void CChessView::RepentChess()
{
    int iR;
    CCommand cmd;

    cmd.SetCommand(g_cmdReceiveRepent);
    iR = MessageBox(m_szRemoteUserName + _T(" ������壿"), _T("����"), MB_YESNO);
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
        } //���� if(m_ctrXQ.GetEnabled())
       
        //�Է�����
        m_ctrXQ.SetEnabled(FALSE);
        m_TiShi.ShowWindow(SW_HIDE);
        m_TiShiRemote.ShowWindow(SW_SHOW);

        cmd.AddPara(TRUE);
    }
    else
    {
        cmd.AddPara(FALSE);
    } //���� if(iR == IDYES)

    SendData(cmd);
}

/*******************************************************************************************************
��������ReceiveRepent
��  �������ܻ�������
��  ����
         CCommand & cmd�����ܻ����������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-11 7:20:54
*******************************************************************************************************/
void CChessView::ReceiveRepent(CCommand & cmd)
{
    m_bRepent = TRUE;

    long iR = cmd.GetLongPara();
    if(iR)
    {
        MessageBox(m_szRemoteUserName + _T(" ���ܻ���"), _T("���ܻ���"));
    }
    else
    {
        MessageBox(m_szRemoteUserName + _T(" �����ܻ���"), _T("���ܻ���"));
        return;
    }//���� if(iR)
    
    if(m_ctrXQ.GetEnabled())
    {
        m_ctrXQ.PreviouStep();
        m_ctrXQ.PreviouStep();
    }
    else
    {        
        m_ctrXQ.PreviouStep();
    } //���� if(m_ctrXQ.GetEnabled())
   
    //��������
    m_TiShi.ShowWindow(SW_SHOW);
    m_TiShiRemote.ShowWindow(SW_HIDE);
    m_ctrXQ.SetEnabled(TRUE);
}

/*******************************************************************************************************
��������OverTime
��  ������ʱ����
��  ������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-11 8:53:32
*******************************************************************************************************/
void CChessView::OverTime(LONG span)
{
    if(m_TiShiRemote.IsWindowVisible())
    {
        return;
    } //���� if(m_RemoteTiShi.IsWindowVisible())

    switch(span)
    {
    case 0:
        OnChessGiveup();
        MessageBox(_T("���Ѿ���ʱ��"), _T("��ʱ"));
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
    } //���� switch(tmStep.GetTotalSeconds())
}

/*******************************************************************************************************
��������PromptSound
��  ����������Դ�е�����
��  ����
         LPCTSTR ID������ID
����ֵ���ɹ����� TRUE�����򷵻� FALSE��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-11 9:38:34
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
��������ReceiveStandOff
��  �����������
��  ����
         BOOL bTiShi���Ƿ���ʾȷ�����ܵ���ʾ��
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-11 13:36:11
*******************************************************************************************************/
void CChessView::ReceivedStandOff(CCommand* pcmd, BOOL bTiShi)
{
    m_bStandOff = TRUE;

    if(bTiShi && pcmd != NULL)
    {
        long iR = pcmd->GetLongPara();
        if(iR)
        {
            MessageBox(m_szRemoteUserName + _T(" �������"), _T("���"));
        }
        else
        {
            MessageBox(m_szRemoteUserName + _T(" ��ͬ�����"), _T("���"));
            return;
        }//���� if(iR)
        
    } //���� if(bTiShi)
   
    CCommand cmd;
    cmd.SetCommand(g_cmdStandOff);
    cmd.AddPara(m_pChessApp->m_gszUserName);
    SendDataToServer(cmd);

    m_TiShi.AddStandOff();
    m_TiShiRemote.AddStandOff();

    ReStart();

}

/*******************************************************************************************************
��������ReStart
��  ������������
��  ������
����ֵ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-11 22:07:18
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
��������StandOff
��  ������Ͳ���
��  ������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-11 13:40:32
*******************************************************************************************************/
void CChessView::StandOff()
{
    CCommand cmd;
    cmd.SetCommand(g_cmdReceivedStandOff);
    INT iR = MessageBox(m_szRemoteUserName + _T(" ������壬�Ƿ�ͬ�⣿"),
        _T("���"), MB_YESNO | MB_ICONQUESTION);    
    if(iR == IDYES)
    {
        ReceivedStandOff();
        cmd.AddPara(1);
    }
    else
    {
        cmd.AddPara(0);
    } //���� if(iR == IDYES)
    SendData(cmd);
}

/*******************************************************************************************************
��������Giveup
��  �����Է������Ŀͻ��˵Ĵ����ɶԷ��ͻ���ֱ�ӷ������ģ���������������
��  ������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-12 16:55:14
*******************************************************************************************************/
void CChessView::Giveup()
{
    //����:�����Ի���

    m_TiShi.AddWin();
    ReStart();
}

/*******************************************************************************************************
��������ReceiveGiveup
��  �����ӷ��������ص��������û���Ϣ
��  ����
         CCommand& cmd���������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-12 16:54:31
*******************************************************************************************************/
void CChessView::ReceiveGiveup(CCommand& cmd)
{
    CString szWin, szLoss;
    long Win, Loss; //����

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