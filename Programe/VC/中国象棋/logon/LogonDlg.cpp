// LogonDlg.cpp : implementation file
//


#include "stdafx.h"
#include "..\�й�����.h"
#include "..\mainfrm.h"
#include "LogonDlg.h"
#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogonDlg dialog


CLogonDlg::CLogonDlg(CWnd* pParent /*=NULL*/)
    : CDialog(CLogonDlg::IDD, pParent)
{
    //{{AFX_DATA_INIT(CLogonDlg)
    m_szPassword = _T("");
    m_uPort = g_SERVERPORT;
    m_uValidate = 0;
    m_uValidateCode = Rand();
    m_szRemoteIP = _T("127.0.0.1");
    //}}AFX_DATA_INIT
    if(((CChessApp*)AfxGetApp())->m_gszUserName.IsEmpty())
    {
        m_szUserName = _T("");
    }
    else
    {
        m_szUserName = ((CChessApp*)AfxGetApp())->m_gszUserName;
    }
    m_pRegist = NULL;
}


void CLogonDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    //{{AFX_DATA_MAP(CLogonDlg)
    DDX_Control(pDX, IDC_EDITVALIDATECODE, m_ctrValidate);
    DDX_Text(pDX, IDC_EDITPASSWORD, m_szPassword);
    DDX_Text(pDX, IDC_EDITREMOTEPORT, m_uPort);
    DDX_Text(pDX, IDC_EDITUSERNAME, m_szUserName);
    DDX_Text(pDX, IDC_EDITVALIDATE, m_uValidate);
    DDX_Text(pDX, IDC_EDITVALIDATECODE, m_uValidateCode);
    DDX_Text(pDX, IDC_EDITREMOTEIP, m_szRemoteIP);
    //}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogonDlg, CDialog)
    //{{AFX_MSG_MAP(CLogonDlg)
    ON_BN_CLICKED(IDC_REGIST, OnRegist)
    //}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogonDlg message handlers

BOOL CLogonDlg::OnInitDialog() 
{
    CDialog::OnInitDialog();
    
    // TODO: Add extra initialization here
    m_pParent = (CMainFrame*)GetParent();
    
    return TRUE;  // return TRUE unless you set the focus to a control
                  // EXCEPTION: OCX Property Pages should return FALSE
}

UINT CLogonDlg::Rand()
{
    srand( (unsigned)time( NULL ) );

    return rand();
    
    double upperbound = 9999, lowerbound = 1000;
    return (UINT)floor((upperbound - lowerbound + 1) * rand() + lowerbound);    
}

void CLogonDlg::OnRegist() 
{
    UpdateData();
    //���÷�������ַ
    m_pParent->SetServerAddress(m_szRemoteIP, m_uPort);
    CRegistDlg rd;
    m_pRegist = new CRegistDlg;
    if( m_pRegist->DoModal() == IDCANCEL )
    {
        return;
    }
    m_szUserName = m_pRegist->m_szUserName;
    m_szPassword = m_pRegist->m_szPassword;
    delete m_pRegist;
    m_pRegist = NULL;
    UpdateData(FALSE);
    OnOK();
}

/*******************************************************************************************************
��������Receive
��  �ܣ�������������صĵ�¼����
��  ����
         CCommand* pCmd������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-29
ʱ  �䣺19:36:56
*******************************************************************************************************/
void CLogonDlg::Receive(CCommand* pCmd)
{
    long cmd;
    cmd = pCmd->GetLongPara();
    switch(cmd)
    {    
    case g_cmdLogonSuccess:              //�ɹ���¼
        TRACE(_T("%s(%d) : �ɹ���¼\n"), __FILE__, __LINE__);
        ((CChessApp*)AfxGetApp())->m_gszUserName = m_szUserName;//�����û���
        AfxGetMainWnd()->SetWindowText(_T("�й����� - ") + m_szUserName);
        CDialog::OnOK();
        break;
    case g_cmdLogonPasswordError:        //�������
        TRACE(_T("%s(%d) : �������\n"), __FILE__, __LINE__);
        MessageBox(_T("�������"), _T("��¼"), MB_OK | MB_ICONWARNING);
        break;
    case g_cmdLogonNoUser:               //�޴��û�
        TRACE(_T("%s(%d) : �޴��û����Ƿ����ע�᣿\n"), __FILE__, __LINE__);
        if(::MessageBox(NULL, _T("�޴��û����Ƿ����ע�᣿"), _T("��¼"), MB_YESNO | MB_ICONWARNING) == IDYES)
        {
            //ע�����û�
            OnRegist();
        }
        break;
    case g_cmdLogonVersionUpdate:        //���µİ汾
        TRACE(_T("%s(%d) : ���µİ汾\n"), __FILE__, __LINE__);
        break;
    case g_cmdLogonDownNewVersion:       //���������µĿͻ��˰汾
        TRACE(_T("%s(%d) : ���������µĿͻ��˰汾\n"), __FILE__, __LINE__);
        break;
    default:
        break;
    }    
    TRACE(_T("%s(%d) : ClogonDlg::Receive��ǰ�߳�ID��%x\n"), __FILE__, __LINE__, ::GetCurrentThreadId());
}

/*******************************************************************************************************
��������OnOK
��  �ܣ����������������
��  ������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-29
ʱ  �䣺19:37:27
*******************************************************************************************************/
void CLogonDlg::OnOK() 
{
    // TODO: Add extra validation here
    this->UpdateData();

#ifndef _DEBUG
    if(m_uValidate != m_uValidateCode )
    {
        m_uValidateCode = Rand();
        TRACE(_T("%d\n"), m_uValidateCode);
        UpdateData(FALSE);
        MessageBox(_T("��֤�����뷨����ȷ�����������롣"), _T("�������"), MB_OK | MB_ICONERROR);
        return;
    }

    if(m_szUserName.IsEmpty() || m_szPassword.IsEmpty())
    {
        MessageBox(_T("û�����û��������롣���������롣"), _T("�������"), MB_OK | MB_ICONERROR);
        return;
    }
    
    CString szUser;
    CString szPassword;
    szUser = m_szUserName;
    szPassword = m_szPassword;
    szUser.TrimLeft();    
    szPassword.TrimLeft();
    
    if(szUser == "" || szPassword == "")
    {
        MessageBox(_T("�û��������벻��Ϊ�ո����������롣"), _T("�������"), MB_OK | MB_ICONERROR);
        return;
    }
#endif

    //����������͵�¼��Ϣ
    //���÷�������ַ
    m_pParent->SetServerAddress(m_szRemoteIP, m_uPort);
    CCommand command;
    command.SetCommand(g_cmdLogon);//��¼����
    command.AddPara(m_szUserName); //�û���
    command.AddPara(m_szPassword); //����
    //����:����IP,����Port

    //�汾
    command.AddPara(MAKEWORD(g_wVerMajor, g_wVerMinor));
    m_pParent->SendData(&command);
    TRACE(_T("%s(%d) : CLogon::OnOK��ǰ�߳�ID��%x\n"), __FILE__, __LINE__, ::GetCurrentThreadId());

}

/*******************************************************************************************************
��������RegistReceive
��  �ܣ�������������ص�ע������
��  ����
         CCommand *pCmd������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-1
ʱ  �䣺12:31:41
*******************************************************************************************************/
void CLogonDlg::RegistReceive(CCommand *pCmd)
{
    if(m_pRegist)
    {
        m_pRegist->Receive(pCmd);
    }
}
