// LogonDlg.cpp : implementation file
//


#include "stdafx.h"
#include "..\中国象棋.h"
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
    //设置服务器地址
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
函数名：Receive
功  能：处理服务器发回的登录数据
参  数：
         CCommand* pCmd：数据
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-29
时  间：19:36:56
*******************************************************************************************************/
void CLogonDlg::Receive(CCommand* pCmd)
{
    long cmd;
    cmd = pCmd->GetLongPara();
    switch(cmd)
    {    
    case g_cmdLogonSuccess:              //成功登录
        TRACE(_T("%s(%d) : 成功登录\n"), __FILE__, __LINE__);
        ((CChessApp*)AfxGetApp())->m_gszUserName = m_szUserName;//设置用户名
        AfxGetMainWnd()->SetWindowText(_T("中国象棋 - ") + m_szUserName);
        CDialog::OnOK();
        break;
    case g_cmdLogonPasswordError:        //密码错误
        TRACE(_T("%s(%d) : 密码错误\n"), __FILE__, __LINE__);
        MessageBox(_T("密码错误"), _T("登录"), MB_OK | MB_ICONWARNING);
        break;
    case g_cmdLogonNoUser:               //无此用户
        TRACE(_T("%s(%d) : 无此用户。是否进行注册？\n"), __FILE__, __LINE__);
        if(::MessageBox(NULL, _T("无此用户。是否进行注册？"), _T("登录"), MB_YESNO | MB_ICONWARNING) == IDYES)
        {
            //注册新用户
            OnRegist();
        }
        break;
    case g_cmdLogonVersionUpdate:        //有新的版本
        TRACE(_T("%s(%d) : 有新的版本\n"), __FILE__, __LINE__);
        break;
    case g_cmdLogonDownNewVersion:       //必须下载新的客户端版本
        TRACE(_T("%s(%d) : 必须下载新的客户端版本\n"), __FILE__, __LINE__);
        break;
    default:
        break;
    }    
    TRACE(_T("%s(%d) : ClogonDlg::Receive当前线程ID：%x\n"), __FILE__, __LINE__, ::GetCurrentThreadId());
}

/*******************************************************************************************************
函数名：OnOK
功  能：向服务器发送数据
参  数：无
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-29
时  间：19:37:27
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
        MessageBox(_T("验证码输入法不正确。请重新输入。"), _T("输入错误"), MB_OK | MB_ICONERROR);
        return;
    }

    if(m_szUserName.IsEmpty() || m_szPassword.IsEmpty())
    {
        MessageBox(_T("没输入用户名或密码。请重新输入。"), _T("输入错误"), MB_OK | MB_ICONERROR);
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
        MessageBox(_T("用户名或密码不能为空格。请重新输入。"), _T("输入错误"), MB_OK | MB_ICONERROR);
        return;
    }
#endif

    //向服务器发送登录信息
    //设置服务器地址
    m_pParent->SetServerAddress(m_szRemoteIP, m_uPort);
    CCommand command;
    command.SetCommand(g_cmdLogon);//登录命令
    command.AddPara(m_szUserName); //用户名
    command.AddPara(m_szPassword); //密码
    //增加:本地IP,本地Port

    //版本
    command.AddPara(MAKEWORD(g_wVerMajor, g_wVerMinor));
    m_pParent->SendData(&command);
    TRACE(_T("%s(%d) : CLogon::OnOK当前线程ID：%x\n"), __FILE__, __LINE__, ::GetCurrentThreadId());

}

/*******************************************************************************************************
函数名：RegistReceive
功  能：处理服务器发回的注册数据
参  数：
         CCommand *pCmd：数据
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-1
时  间：12:31:41
*******************************************************************************************************/
void CLogonDlg::RegistReceive(CCommand *pCmd)
{
    if(m_pRegist)
    {
        m_pRegist->Receive(pCmd);
    }
}
