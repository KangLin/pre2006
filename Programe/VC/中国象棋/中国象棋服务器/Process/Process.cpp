/*******************************************************************************************************
文件名：Process.cpp
功  能：服务器的处理
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-12-30
时  间：16:22:41

FileName：Process.cpp
Function：
Compiler：Visual C++ 6.0
Author：  KangLin
          Copyright 2004 KangLin
Date：    2004-12-30
Time：    16:22:41
*******************************************************************************************************/

#include "stdafx.h"
#include "Process.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProcess::CProcess()
{

}

CProcess::~CProcess()
{

}

/*******************************************************************************************************
函数名：SetSocket
功  能：
参  数：
         CUDPSocket *pSock：
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-3
时  间：17:17:53
*******************************************************************************************************/
void CProcess::SetSocket(CUDPSocket *pSock)
{
    m_sckCommand = pSock;
}

/*******************************************************************************************************
函数名：SetConnection
功  能：设置记录连接
参  数：
         CAdoConnection *pconn：记录连接指针
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-1
时  间：16:23:55
*******************************************************************************************************/
void CProcess::SetConnection(CAdoConnection *pconn)
{
    m_pAdoConn = pconn;
    m_AdoRecSet.SetAdoConnection(m_pAdoConn);
}

/*******************************************************************************************************
函数名：SetCommand
功  能：设置命令
参  数：
         CCommand *pCmd：命令指针
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-29
时  间：17:43:54
*******************************************************************************************************/
void CProcess::SetCommand(CCommand *pCmd)
{
    m_pCmd = pCmd;
}

/*******************************************************************************************************
函数名：SendData
功  能：发送数据
参  数：
         LPVOID lpBuf：数据
         INT iLen：数据的长度
返回值：成功返回 TRUE,否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-28
时  间：11:33:57
*******************************************************************************************************/
BOOL CProcess::SendData(LPVOID lpBuf, INT iLen)
{
    return m_sckCommand->SendDataTo(lpBuf, iLen, m_uPort, m_szIP);
}

/*******************************************************************************************************
函数名：SendData
功  能：发送数据
参  数：
         CCommand cmd：
返回值：成功返回 TRUE,否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-28
时  间：19:37:05
*******************************************************************************************************/
BOOL CProcess::SendData(CCommand& cmd)
{
    return SendData(cmd.GetDataRef(), cmd.GetLength());
}

/*******************************************************************************************************
函数名：SendData
功  能：发送数据
参  数：
         CCommand *pcmd：
返回值：成功返回 TRUE,否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-1
时  间：17:55:05
*******************************************************************************************************/
BOOL CProcess::SendData(CCommand *pcmd)
{
    return SendData(pcmd->GetDataRef(), pcmd->GetLength());
}

/*******************************************************************************************************
函数名：SendData
功  能：向指定的用户发送数据
参  数：
         LPCTSTR lpszUserName：用户名
         CCommand &cmd：数据
返回值：成功返回 TRUE,否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-30
时  间：15:58:05
*******************************************************************************************************/
BOOL CProcess::SendData(LPCTSTR lpszUserName, CCommand &cmd)
{
    return SendData(lpszUserName, cmd.GetDataRef(), cmd.GetLength());
}

/*******************************************************************************************************
函数名：SendData
功  能：向指定的用户发送数据
参  数：
         LPCTSTR lpszUserName：用户名
         LPVOID lpData：数据
         int iLen：数据长度
返回值：成功返回 TRUE,否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-28
时  间：13:06:20
*******************************************************************************************************/
BOOL CProcess::SendData(LPCTSTR lpszUserName, LPVOID lpData, int iLen)
{
    CString szSQL;
    szSQL = _T("Select 外部IP, 外部Port From Info Where 用户名 = '");
    szSQL += lpszUserName;
    szSQL += _T("'");
    CAdoRecordSet AdoRecSet;
    AdoRecSet.SetAdoConnection(m_pAdoConn);
    AdoRecSet.Open(szSQL);
    CString szIP;
    long lPort;
    if(!AdoRecSet.GetCollect(_T("外部IP"), szIP))
    {
        ASSERT(0);//无此用户
        return FALSE;
    }
    if(!AdoRecSet.GetCollect(_T("外部Port"), lPort))
    {
        ASSERT(0);//无此用户
        return FALSE;
    }
    return m_sckCommand->SendDataTo(lpData, iLen, lPort, szIP);
}

/*******************************************************************************************************
函数名：SendDataToAllUser
功  能：向所有已登录的用户发送信息。不向发送用户发送。
        如果 lpszSendUserName 为NULL，则向所有登录用户发送信息
参  数：
         CCommand &cmd：要发送的信息
         LPCTSTR lpszSendUserName：发送信息的用户名
                   如果此值为NULL，则向所有登录用户发送信息
返回值：成功返回 TRUE,否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-30
时  间：16:03:34
*******************************************************************************************************/
BOOL CProcess::SendDataToAllUser(CCommand &cmd, LPCTSTR lpszSendUserName)
{
    return SendDataToAllUser(cmd.GetDataRef(), cmd.GetLength(), lpszSendUserName);
}

/*******************************************************************************************************
函数名：SendDataToAllUser
功  能：向所有已登录的用户发送信息。不向发送用户发送。
        如果 lpszSendUserName 为NULL，则向所有登录用户发送信息
参  数：
         LPVOID lpData：要发送的信息
         int iLen：要发送的信息的长度
         LPCTSTR lpszSendUserName：发送信息的用户名。
                   如果此值为NULL，则向所有登录用户发送信息
返回值：成功返回 TRUE,否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-30
时  间：16:19:45
*******************************************************************************************************/
BOOL CProcess::SendDataToAllUser(LPVOID lpData, int iLen, LPCTSTR lpszSendUserName)
{
    CString szSQL(_T("Select 用户名 From UserInfo Where 状态 <> '未登录'"));
    CAdoRecordSet AdoRecSet;
    AdoRecSet.SetAdoConnection(m_pAdoConn);
    if(!AdoRecSet.Open(szSQL))
    {
        /*TRACE(_T("%s(%d) : 向所有已登录用户发送信息,查找用户出错\n"), __FILE__, __LINE__);*/
        return FALSE;
    }
    int iCount = AdoRecSet.GetRecordCount();
    for(int i = 0; i < iCount; i++)
    {
        AdoRecSet.GetCollect(_T("用户名"), szSQL);
        /*TRACE(_T("%s(%d) : %s\n"), __FILE__, __LINE__, szSQL);*/
        if(lpszSendUserName)
        {
            if(szSQL != lpszSendUserName)
            {
                SendData(szSQL, lpData, iLen);
            }
        }
        else
        {
            SendData(szSQL, lpData, iLen);
        }
        AdoRecSet.MoveNext();
    }
    return TRUE;
}

/*******************************************************************************************************
函数名：Update
功  能：更新表中的字段
参  数：
         LPCTSTR lpUpdate：字段表达式
         LPCTSTR lpCondition：条件
         ENUM_TABLE eTable：表
返回值：成功返回 TRUE,否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-28
时  间：15:22:06
*******************************************************************************************************/
BOOL CProcess::Update(LPCTSTR lpUpdate, LPCTSTR lpCondition, ENUM_TABLE eTable)
{
    CString szSQL;
    szSQL = _T("Update ");
    switch(eTable)
    {
    case tabInfo:
        szSQL += _T("Info");
        break;
    case tabUserInfo:
        szSQL += _T("UserInfo");
        break;
    case tabChair:
        szSQL += _T("Chair");
        break;
    }
    szSQL += _T(" Set ");
    szSQL += lpUpdate;
    if(lpCondition)
    {
        szSQL += _T(" Where ");
        szSQL += lpCondition;
    }
    CAdoRecordSet AdoRecSet;
    AdoRecSet.SetAdoConnection(m_pAdoConn);
    return AdoRecSet.Open(szSQL);
}

/*******************************************************************************************************
函数名：Search
功  能：查找表中的指定字段
参  数：
         LPCTSTR lpszFields：字段
         LPCTSTR lpszCondition：条件
         ENUM_TABLE eTable：表
返回值：成功返回 TRUE,否则返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-30
时  间：10:53:31
*******************************************************************************************************/
BOOL CProcess::Search(LPCTSTR lpszFields, LPCTSTR lpszCondition, ENUM_TABLE eTable)
{
    CString szSQL(_T("Select "));
    szSQL += lpszFields;
    szSQL += _T(" From ");
    switch(eTable)
    {
    case tabInfo:
        szSQL += _T("Info");
        break;
    case tabUserInfo:
        szSQL += _T("UserInfo");
        break;
    case tabChair:
        szSQL += _T("Chair");
        break;
    }
    if(lpszCondition)
    {
        szSQL += _T(" Where ");
        szSQL += lpszCondition;
    }
    return m_AdoRecSet.Open(szSQL);
}

/*******************************************************************************************************
函数名：Logon
功  能：登录命令的处理
参  数：无
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-28
时  间：11:35:35
*******************************************************************************************************/
void CProcess::Logon()
{
    CString szUser;
    CString szPassword;
    CString szIP;
    UINT uPort;
    DWORD dwVer;//版本号
    szUser = m_pCmd->GetPara();
    szPassword = m_pCmd->GetPara();
    //增加:本地IP、Port
    
    dwVer = m_pCmd->GetLongPara();
    /*TRACE(_T("%s(%d) : 版本号:主版本号:%d;次版本号:%d\n"), __FILE__, __LINE__, LOWORD(dwVer), HIWORD (dwVer));*/
    /*TRACE(_T("%s(%d) : 用户名:%s:密码:%s\n"), __FILE__, __LINE__, szUser, szPassword);*/
    //查找用户
    CString szSQL;
    szSQL = "Select 密码 From Info where 用户名 = '";
    szSQL += szUser;
    szSQL += _T("'");
    m_AdoRecSet.Open(szSQL);
   
    CString password; 
    m_AdoRecSet.GetCollect(_T("密码"), password);
    /*TRACE(_T("%s(%d) : password:%s\n"), __FILE__, __LINE__, password);*/

    CCommand command;
    //登录命令
    command.SetCommand(g_cmdLogon);
    if(password.IsEmpty())//用户不存在
    {
        //参数:无此用户
        /*TRACE(_T("%s(%d) : 用户不存在, 参数\n"), __FILE__, __LINE__);*/
        command.AddPara(g_cmdLogonNoUser);
        SendData(command);
        return;
    }
    if(password != szPassword)
    {
        //密码错误
        /*TRACE(_T("%s(%d) : 密码错误\n"), __FILE__, __LINE__);*/
        command.AddPara(g_cmdLogonPasswordError);
        SendData(command);        
    }
    else//密码正确
    {
        /*TRACE(_T("%s(%d) : 密码正确\n"), __FILE__, __LINE__);*/
        //参数:密码正确
        command.AddPara(g_cmdLogonSuccess);
        SendData(command);

        CString szCondition;
        szSQL = _T("状态");
        szCondition = _T("用户名 = '");
        szCondition += szUser;
        szCondition += _T("'");
        Search(szSQL, szCondition);
        m_AdoRecSet.GetCollect(_T("状态"), szSQL);

        //修改数据库
        if(szSQL == _T("未登录"))
        {
            /*TRACE(_T("%s(%d) : 用户已登录;状态:%s\n"), __FILE__, __LINE__, szSQL);*/
            Update(_T("状态 = '已登录'"), szCondition); 
        }
        CString szUpdate;
        szUpdate =_T("外部IP = '");
        szUpdate += m_szIP;
        szUpdate += _T("', ");
        szUpdate += _T("外部Port = ");
        CString sztmp;
        sztmp.Format(_T("%d"), m_uPort);
        szUpdate += sztmp;
        //增加:内部IP,内部Port
        Update(szUpdate, szCondition, tabInfo); 

        //向所有已登录的用户发送新用户登录信息
        SendLogonUserInfoToAllLogonedUser(szUser);

        //向登录用户发送所有已登录用户的信息
        SendAllLogonedUserInfo();

        //向登录用户发送椅子的信息
        SendChairInfo();
        
        //增加:检查是否有新的版本
    }
}

/*******************************************************************************************************
函数名：GetUserInfo
功  能：得到当前记录集中的用户信息
参  数：
         CCommand *pCmd：命令
返回值：成功返回 TRUE, 否则返回 FALSE.
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-31
时  间：15:28:02
*******************************************************************************************************/
BOOL CProcess::GetUserInfo(CCommand *pCmd)
{
    CString sztmp;    
    m_AdoRecSet.GetCollect(_T("用户名"), sztmp);
    pCmd->AddPara (sztmp);
    m_AdoRecSet.GetCollect(_T("下棋总盘数"), sztmp);
    pCmd->AddPara (sztmp);
    m_AdoRecSet.GetCollect(_T("赢的盘数"), sztmp);
    pCmd->AddPara (sztmp);
    m_AdoRecSet.GetCollect(_T("输的盘数"), sztmp);
    pCmd->AddPara (sztmp);
    m_AdoRecSet.GetCollect(_T("和的盘数"), sztmp);
    pCmd->AddPara (sztmp);
    m_AdoRecSet.GetCollect(_T("积分"), sztmp);
    pCmd->AddPara (sztmp);
    m_AdoRecSet.GetCollect(_T("性别"), sztmp);
    pCmd->AddPara (sztmp);
    m_AdoRecSet.GetCollect(_T("状态"), sztmp);
    pCmd->AddPara (sztmp);
    m_AdoRecSet.GetCollect(_T("头像"), sztmp);
    pCmd->AddPara (sztmp);
    return TRUE;
}

/*******************************************************************************************************
函数名：SendLogonUserInfoToAllLogonedUser
功  能：向所有已登录的用户发送指定用户的信息
参  数：
         LPCTSTR szUserName：用户名
         BOOL bUser: 是否也向指定的用户发送，默认为 FALSE。
                     FALSE：不向指定用户发送
                     TRUE：向指定的用户发送
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-30
时  间：15:34:57
*******************************************************************************************************/
void CProcess::SendLogonUserInfoToAllLogonedUser(LPCTSTR szUserName, BOOL bUser)
{
    CString szSQL;
    szSQL = _T("Select * From UserInfo Where 用户名 = '");
    szSQL += szUserName;
    szSQL += _T("'");
    m_AdoRecSet.Open(szSQL);
    CCommand cmd;
    cmd.SetCommand(g_cmdUserInfo);
    GetUserInfo(&cmd);
    if(bUser)
    {
        SendDataToAllUser(cmd);
    }
    else
    {
        SendDataToAllUser(cmd, szUserName);
    }
}

/*******************************************************************************************************
函数名：SendAllLogonedUserInfo
功  能：向新登录用户发送所有已登录用户的信息
参  数：
         LPCTSTR lpszUser：新登录用户名
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-30
时  间：17:00:59
*******************************************************************************************************/
void CProcess::SendAllLogonedUserInfo()
{
    CCommand cmd;
    //发送表头
    cmd.SetCommand(g_cmdUserInfoHead);
    cmd.AddPara(_T("用户名"));
    cmd.AddPara(_T("下棋总盘数"));
    cmd.AddPara(_T("赢的盘数"));
    cmd.AddPara(_T("输的盘数"));
    cmd.AddPara(_T("和的盘数"));
    cmd.AddPara(_T("积分"));
    cmd.AddPara(_T("性别"));
    cmd.AddPara(_T("状态"));
    cmd.AddPara(_T("头像"));
    SendData(cmd);
    //发送已登录用户的信息
    CString szSQL;
    szSQL = _T("Select * From UserInfo Where 状态 <> '未登录'");
    m_AdoRecSet.Open(szSQL);
 
    int iCount = m_AdoRecSet.GetRecordCount();
    for(int i = 0; i < iCount; i++)
    {
        cmd.SetCommand(g_cmdUserInfo);
        GetUserInfo(&cmd);
        SendData(cmd);
        m_AdoRecSet.MoveNext();
    }
}

/*******************************************************************************************************
函数名：GetChairInfo
功  能：得到指定椅子信息
参  数：
         int iChairNo：椅子号
         CCommand* pCmd：
返回值：成功返回 TRUE,失败返回 FALSE
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-3
时  间：20:04:10
*******************************************************************************************************/
BOOL CProcess::GetChairInfo(int iChairNo, CCommand* pCmd)
{
    CString sztmp;
    sztmp.Format(_T("%d"), iChairNo);
    CString szSQL(_T("Seletc UserName Form Chair Where ChairNo = "));
    szSQL += sztmp;
    CAdoRecordSet AdoRecSet;
    AdoRecSet.SetAdoConnection(m_pAdoConn);
    if(AdoRecSet.Open(szSQL))
    {
        ASSERT(0);
        return FALSE;
    }
    if(AdoRecSet.GetCollect(_T("UserName"), szSQL))
    {
        ASSERT(0);
        return FALSE;
    }
    pCmd->AddPara(szSQL);    //用户名
    pCmd->AddPara(iChairNo); //椅子号
    return TRUE;
}

/*******************************************************************************************************
函数名：SendChairInfo
功  能：向登录用户发送椅子信息
参  数：无无
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-3
时  间：20:03:18
*******************************************************************************************************/
void CProcess::SendChairInfo(BOOL bAll)
{
    CString szSQL(_T("Select * From Chair"));
    CString szhand;
    m_AdoRecSet.Open(szSQL);
    CCommand cmd;
    int iCount;
    iCount = m_AdoRecSet.GetRecordCount();
    for(int i = 0; i < iCount; i++)
    {
        cmd.SetCommand(g_cmdChairInfo);
        m_AdoRecSet.GetCollect(_T("UserName"), szSQL);
        m_AdoRecSet.GetCollect(_T("Hand"), szhand);
        if(szSQL != _T(""))
        {
            cmd.AddPara(szSQL); //用户名
            cmd.AddPara(i + 1); //椅子号
            cmd.AddPara(szhand);
            if(bAll)
            {
                SendDataToAllUser(cmd);
            }
            else
            {
                SendData(cmd);
            }
        }
        m_AdoRecSet.MoveNext();
    }
}

/*******************************************************************************************************
函数名：LeaveChair
功  能：离开椅子
参  数：无
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-3
时  间：21:10:25
*******************************************************************************************************/
void CProcess::LeaveChair()
{
    CString szUser, szUserName;
    CString szChairNo;
    szUser = m_pCmd->GetPara(); //离开方用户名
    szChairNo = m_pCmd->GetPara();
    szUserName = m_pCmd->GetPara(); //对方用户名
    CString szSQL;    
    CString szCondition;

    szSQL = _T("UserName = '', Hand = 0");
    szCondition = _T("ChairNo = ");
    szCondition += szChairNo;
    Update(szSQL, szCondition, tabChair);
    szSQL = _T("椅子号 = 0, 状态 = '已登录'");
    szCondition = _T("用户名 = '") + szUser + _T("'");
    Update(szSQL, szCondition);
    //发送椅子信息
    CCommand cmd;
    cmd.SetCommand(g_cmdChairInfo);
    cmd.AddPara("");        //用户名
    cmd.AddPara(szChairNo); //椅子号
    cmd.AddPara(0);
    SendDataToAllUser(cmd);
    //通知所有用户
    SendLogonUserInfoToAllLogonedUser(szUser, TRUE);

    if(szUserName != _T(""))
    {
        cmd.SetCommand(g_cmdLeaveChair);
        cmd.AddPara(szUser);         //离开方用户名
        SendData(szUserName, cmd);
    }
    /*TRACE(_T("%s(%d) : 用户 %s 离开椅子 %s\n"), __FILE__, __LINE__, szUser, szChairNo);*/
}

/*******************************************************************************************************
函数名：Exit
功  能：用户退出
参  数：无
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-31
时  间：12:40:47
*******************************************************************************************************/
void CProcess::Exit()
{
    CString szUser;
    CString szSQL;
    CString szCondition;
    szUser = m_pCmd->GetPara();
    //更新数据库
    szSQL = _T("状态 = '未登录'");
    szCondition = _T("用户名 = '") + szUser + _T("'");
    Update(szSQL, szCondition);
    //向所有用户发送此用户退出命令
    CCommand cmd;
    cmd.SetCommand(g_cmdExit);
    cmd.AddPara(szUser);
    SendDataToAllUser(cmd, szUser);
    /*TRACE(_T("%s(%d) : 用户 %s 退出\n"), __FILE__, __LINE__, szUser);*/
}

/*******************************************************************************************************
函数名：Regist
功  能：用户注册
参  数：无
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-1
时  间：14:17:49
*******************************************************************************************************/
void CProcess::Regist()
{
    CString szUserName;
    CString szPassword;
    CString szSex;
    CString szAge;
    CString szImage;
    szUserName = m_pCmd->GetPara();
    szPassword = m_pCmd->GetPara();
    szSex = m_pCmd->GetPara();
    szAge = m_pCmd->GetPara();
    szImage = m_pCmd->GetPara();
    /*TRACE(_T("%s(%d) : 用户名:%s密码:%s性别:%s年龄:%s头像:%s\n"), __FILE__, __LINE__, szUserName, szPassword, szSex, szAge, szImage);*/

    CString szSQL(_T("Select 用户名 From Info Where 用户名 = '"));
    szSQL = szSQL + szUserName + _T("'");
    m_AdoRecSet.Open(szSQL);
    CString sztmp;
    m_AdoRecSet.GetCollect(_T("用户名"), sztmp);
    CCommand cmd;
    cmd.SetCommand(g_cmdRegist);
    if(!sztmp.IsEmpty())
    {
        /*TRACE(_T("%s(%d) : 用户 %s 已存在\n"), __FILE__, __LINE__, szUserName);*/
        cmd.AddPara(g_cmdRegistHadUser);
    }
    else
    {
        //更新数据库
        szSQL = _T("Insert Into Info (用户名, 密码) Values('") \
            + szUserName  + _T("','") + szPassword + _T("')");
        m_AdoRecSet.Open(szSQL);
        szSQL = _T("Insert Into UserInfo (用户名, 性别, 年龄, 头像) Values('") \
            + szUserName + _T("', '") + szSex + _T("', '") \
            + szAge + _T("', '") + szImage + _T("')");
        m_AdoRecSet.Open(szSQL);
        cmd.AddPara(g_cmdRegistSuccess);
    }
    SendData(cmd);
}

/*******************************************************************************************************
函数名：SendTextMessage
功  能：转发文本消息
参  数：无
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-1
时  间：17:50:05
*******************************************************************************************************/
void CProcess::SendTextMessage()
{
    CString szSendUser; //发送信息者
    CString szUser;     //接收信息者
    CString szText;     //文本信息
    szSendUser = m_pCmd->GetPara();
    szUser = m_pCmd->GetPara();
    szText = m_pCmd->GetPara();
    m_pCmd->SetCommand(g_cmdSendTextMessage);
    m_pCmd->AddPara(szText);
    szText = szUser;
    szText.MakeLower();
    if(szText == _T("所有人") || szText == _T("all"))
    {
        SendDataToAllUser(*m_pCmd, szSendUser);
    }
    else
    {
        SendData(szUser, *m_pCmd);
    }
}

/*******************************************************************************************************
函数名：SetDown
功  能：用户入坐
参  数：无
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-3
时  间：16:58:00
*******************************************************************************************************/
void CProcess::SetDown()
{
    CCommand cmd;
    CString szUser;
    CString szChairNo;
    CString szInPort;
    szUser = m_pCmd->GetPara();    //用户名
    szChairNo = m_pCmd->GetPara(); //椅子号
    szInPort = m_pCmd->GetPara();  //外部端口号
    /*TRACE(_T("%s(%d) : 用户名:%s,椅子号:%s\n"), __FILE__, __LINE__, szUser, szChairNo);*/
    CString szSQL(_T("Select UserName From Chair Where ChairNo = "));
    szSQL += szChairNo;
    m_AdoRecSet.Open(szSQL);
    CString szOtherUser;
    m_AdoRecSet.GetCollect(_T("UserName"), szOtherUser);
    cmd.SetCommand(g_cmdSetDown);
    if(szOtherUser != _T(""))
    {
        /*TRACE(_T("%s(%d) : 此坐位已有人\n"), __FILE__, __LINE__);*/
        cmd.AddPara(g_cmdHadMan);
        SendData(cmd);
        return;
    }

    //------------------------------------------------------------------------
    //以下是完成 ===修改数据库=== 功能的语句块
    //

    //椅子信息
    szSQL = _T("UserName = '") + szUser + _T("'");
    CString szCondition(_T("ChairNo ="));
    szCondition += szChairNo;
    Update(szSQL, szCondition, tabChair);
    //用户信息
    szSQL = _T("椅子号 = ") + szChairNo + _T(", 状态 = '入坐'");
    szCondition = _T("用户名 = '") + szUser + _T("'");
    Update(szSQL, szCondition);
    //象棋socket的外部port
    CString szPort, szLocatePort;
    szPort.Format(_T("%d"), m_uPort);
    szLocatePort.Format(_T("%d"), szInPort);
    szSQL = _T("ChessPort =") + szPort + _T(", InChessPort = ") + szLocatePort;
    szCondition = _T("用户名 = '") + szUser + _T("'");
    Update(szSQL, szCondition, tabInfo);

    //
    //以上是完成 ===修改数据库=== 功能的语句块
    //------------------------------------------------------------------------
    

    //发送椅子信息
    cmd.SetCommand(g_cmdChairInfo);
    cmd.AddPara(szUser);    //用户名
    cmd.AddPara(szChairNo); //椅子号
    cmd.AddPara(0);
    SendDataToAllUser(cmd);
    /*TRACE(_T("%s(%d) : 入坐发送椅子信息.用户名=%s,椅子号=%s\n"), __FILE__, __LINE__, szUser, szChairNo);*/

    //发送入坐命令
    cmd.SetCommand(g_cmdSetDown);
    //查找对方状态,有如下三种
    //1。对方没入坐
    //2。对面已入坐
    //   2.1。对方已入坐,但没有同意开始
    //   2.2。对方已入坐,并同意开始
    long No;
    No = _ttol(szChairNo);
    if(No % 2 == 0)
    {
        No--;
    }
    else
    {
        No++;
    }
    szChairNo.Empty();
    szChairNo.Format(_T("%d"), No);    
    szSQL = _T("UserName");
    szCondition = (_T("ChairNo ="));
    szCondition += szChairNo;
    Search(szSQL, szCondition, tabChair);
    if(!m_AdoRecSet.GetCollect(_T("UserName"), szOtherUser))
    {
        /*TRACE(_T("%s(%d) : 对方没入坐\n"), __FILE__, __LINE__);*/
        cmd.AddPara(g_cmdOtherNoMan);
        SendData(cmd);
    }
    else
    {
        if(szOtherUser == _T(""))
        {
            /*TRACE(_T("%s(%d) : 对方没入坐\n"), __FILE__, __LINE__);*/
            cmd.AddPara(g_cmdOtherNoMan);
            SendData(cmd);
        }
        else //对面有人
        {
            szSQL = _T("状态");
            szCondition = _T("用户名 = '") + szOtherUser + _T("'");
            Search(szSQL, szCondition);
            CString szState;
            m_AdoRecSet.GetCollect(_T("状态"), szState);
            if(szState == _T("入坐"))
            {
                cmd.AddPara(g_cmdOtherSetDown);
                /*TRACE(_T("%s(%d) : 对面入坐但没开始\n"), __FILE__, __LINE__);*/
            }
            if(szState == _T("开始"))
            {
                cmd.AddPara(g_cmdOtherStart);
                /*TRACE(_T("%s(%d) : 对面入坐但并同意开始\n"), __FILE__, __LINE__);*/
            }
            cmd.AddPara (szOtherUser); //对方用户名
            //加入对方的地址
            CString szExIP, szExPort, szIP, szPort, szExChessPort, szChessPort;
            szSQL = _T("外部IP, 外部Port, 内部IP, 内部Port, ChessPort");
            szCondition = _T("用户名 = '") + szOtherUser + _T("'");
            Search(szSQL, szCondition, tabInfo);
            m_AdoRecSet.GetCollect(_T("外部IP"), szExIP);
            m_AdoRecSet.GetCollect(_T("内部IP"), szIP);
            m_AdoRecSet.GetCollect(_T("外部Port"), szExPort);
            m_AdoRecSet.GetCollect(_T("内部Port"), szPort);
            m_AdoRecSet.GetCollect(_T("ChessPort"), szExChessPort);
            m_AdoRecSet.GetCollect(_T("InChessPort"), szChessPort);
            cmd.AddPara (szExIP);       //外部IP
            cmd.AddPara(szExPort);      //外部Pport
            cmd.AddPara(szIP);          //内部IP
            cmd.AddPara(szPort);        //内部Port
            cmd.AddPara(szExChessPort); //外部象棋Port
            cmd.AddPara(szChessPort);   //内部象棋Port

            SendData(cmd);

            //向对方用户通知本用户入坐
            cmd.SetCommand(g_cmdOtherSetDown);
            cmd.AddPara(szUser);        //用户名
            szSQL = _T("外部IP, 外部Port, 内部IP, 内部Port, ChessPort");
            szCondition = _T("用户名 = '") + szUser + _T("'");
            Search(szSQL, szCondition, tabInfo);
            m_AdoRecSet.GetCollect(_T("外部IP"), szExIP);
            m_AdoRecSet.GetCollect(_T("内部IP"), szIP);
            m_AdoRecSet.GetCollect(_T("外部Port"), szExPort);
            m_AdoRecSet.GetCollect(_T("内部Port"), szPort);
            m_AdoRecSet.GetCollect(_T("ChessPort"), szExChessPort);
            m_AdoRecSet.GetCollect(_T("InChessPort"), szChessPort);
            cmd.AddPara (szExIP);       //外部IP
            cmd.AddPara(szExPort);      //外部Pport
            cmd.AddPara(szIP);          //内部IP
            cmd.AddPara(szPort);        //内部Port
            cmd.AddPara(szExChessPort); //外部象棋Port
            cmd.AddPara(szChessPort);   //内部象棋Port

            SendData(szOtherUser, cmd);
        }
    }
    
    //通知所有用户
    SendLogonUserInfoToAllLogonedUser(szUser, TRUE);    
}

/*******************************************************************************************************
函数名：Start
功  能：处理同意开始下棋命令
参  数：无
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-19
时  间：17:37:35
*******************************************************************************************************/
void CProcess::Start()
{
    CString szUser, szUserName;
    szUser = m_pCmd->GetPara();      //同意方用户名
    szUserName = m_pCmd->GetPara();  //对方用户名
    /*TRACE(_T("%s(%d) : %s 同意与 %s 开始下棋\n"), __FILE__, __LINE__, szUser, szUserName);*/
    CString szSQL, szCondition;
  
    //对方是否入坐
    if(szUserName != _T(""))
    {
        szSQL = _T("状态");
        szCondition = _T("用户名 = '") + szUserName + _T("'");
        Search(szSQL, szCondition);
        m_AdoRecSet.GetCollect(_T("状态"), szSQL);
    }
    else //对方没入坐
    {
        szSQL = _T("状态 = '开始'");
        szCondition = _T("用户名 = '") + szUser + _T("'");
        Update(szSQL, szCondition);
        CCommand cmd;
        cmd.SetCommand(g_cmdStart);
        cmd.AddPara(szUser);
        SendData(szUser, cmd);
        //通知所有用户
        SendLogonUserInfoToAllLogonedUser(szUser, TRUE);

        //发送椅子信息
        szSQL = _T("椅子号");
        szCondition = _T("用户名 = '") + szUser + _T("'");
        Search(szSQL, szCondition);
        m_AdoRecSet.GetCollect(_T("椅子号"), szSQL);

        szCondition = _T("ChairNo = ") + szSQL;
        szSQL = _T("Hand = 1");
        Update(szSQL, szCondition, tabChair);
        SendChairInfo(TRUE);

        return;
    }
    //对方入坐
    //查看对方状态
    if(szSQL == _T("开始"))
    {
        //修改数据库
        szSQL = _T("状态 = '下棋'");
        szCondition = _T("用户名 = '") + szUser + _T("'");
        Update(szSQL, szCondition);
        szCondition = _T("用户名 = '") + szUserName + _T("'");
        Update(szSQL, szCondition);
        //通知所有用户
        SendLogonUserInfoToAllLogonedUser(szUserName, TRUE);
        SendLogonUserInfoToAllLogonedUser(szUser, TRUE);
        CCommand cmd;
        cmd.SetCommand(g_cmdStart);
        cmd.AddPara(szUserName);   //先走方
        cmd.AddPara(szUser);       //后走方
        SendData(szUser, cmd);
        SendData(szUserName, cmd);

        CString szIP, szPort;
        cmd.SetCommand(g_cmdPlayChess);
        cmd.AddPara(szUserName);   //先走方
        szSQL = _T(" 外部IP,ChessPort ");
        szCondition = _T("用户名 = '") + szUserName + _T("'");
        Search(szSQL, szCondition, tabInfo);
        m_AdoRecSet.GetCollect(_T("外部IP"), szIP);
        m_AdoRecSet.GetCollect(_T("ChessPort"), szPort);
        cmd.AddPara(szIP);
        cmd.AddPara(szPort);
       
        cmd.AddPara(szUser);       //后走方
        szCondition = _T("用户名 = '") + szUser + _T("'");
        Search(szSQL, szCondition, tabInfo);
        m_AdoRecSet.GetCollect(_T("外部IP"), szIP);
        m_AdoRecSet.GetCollect(_T("ChessPort"), szPort);
        cmd.AddPara(szIP);
        cmd.AddPara(szPort);

        SendData(szUser, cmd);
        SendData(szUserName, cmd);
    }
    else
    {
        szSQL = _T("状态 = '开始'");
        szCondition = _T("用户名 = '") + szUser + _T("'");
        Update(szSQL, szCondition);
        //通知所有用户
        SendLogonUserInfoToAllLogonedUser(szUser, TRUE);
        CCommand cmd;
        cmd.SetCommand(g_cmdStart);
        cmd.AddPara(szUser);
        cmd.AddPara(_T(""));
        SendData(szUser, cmd);

        cmd.SetCommand(g_cmdStart);
        cmd.AddPara(szUser);
        cmd.AddPara(_T(""));
        SendData(szUserName, cmd);        
    }

    //发送椅子信息
    szSQL = _T("椅子号");
    szCondition = _T("用户名 = '") + szUser + _T("'");
    Search(szSQL, szCondition);
    m_AdoRecSet.GetCollect(_T("椅子号"), szSQL);

    szCondition = _T("ChairNo = ") + szSQL;
    szSQL = _T("Hand = 1");
    Update(szSQL, szCondition, tabChair);
    SendChairInfo(TRUE);
}

/*******************************************************************************************************
函数名：StandOff
描  述：处理求和命令
参  数：
         void：无
返回值：
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-11 16:44:24
*******************************************************************************************************/
void CProcess::StandOff(void)
{
    CString szUser, szSQL, szCondition;
    TCHAR sztmp[10];
    szUser = m_pCmd->GetPara();
    long iStandOff, iTotal;
    szSQL = _T("和的盘数,下棋总盘数");
    szCondition = _T("用户名 = '") + szUser + ("'");
    Search(szSQL, szCondition);
    m_AdoRecSet.GetCollect(_T("和的盘数"), iStandOff);
    m_AdoRecSet.GetCollect(_T("下棋总盘数"), iTotal);
    szSQL = _T("状态 = '入坐', 和的盘数 = ");
    _ltot(iStandOff + 1, sztmp, 10);
    szSQL = szSQL + sztmp;
    szSQL += _T(",下棋总盘数 = ");
    _ltot(iTotal + 1, sztmp, 10);
    szSQL = szSQL + sztmp;
    Update(szSQL, szCondition);
}

/*******************************************************************************************************
函数名：Giveup
描  述：处理认输命令
参  数：无
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-11 22:11:31
*******************************************************************************************************/
void CProcess::Giveup()
{
    CString szLoss, szWin, szSQL, szCondition;
    long Add, Inc, Total, Win, Loss, Integral;
    TCHAR tmp[10];
    CCommand cmd;
    cmd.SetCommand(g_cmdReceiveGiveup);

    szLoss = m_pCmd->GetPara();   //认输方
    szWin = m_pCmd->GetPara();    //赢方
    Add = m_pCmd->GetLongPara();  //加分值
    Inc = m_pCmd->GetLongPara();  //减分值
    //增加:其它的设置参数

    szSQL = _T("下棋总盘数,输的盘数,积分");
    szCondition = _T("用户名 = '") + szLoss + ("'");
    Search(szSQL, szCondition);
    m_AdoRecSet.GetCollect(_T("下棋总盘数"), Total);
    m_AdoRecSet.GetCollect(_T("输的盘数"), Loss);
    m_AdoRecSet.GetCollect(_T("积分"), Integral);
    Total++;
    Integral -= Inc;
    Loss++;
    szSQL = _T("下棋总盘数 = ");
    _ltot(Total, tmp, 10);
    szSQL += tmp;
    szSQL += _T(",输的盘数 = ");
    _ltot(Loss, tmp, 10);
    szSQL += tmp;
    szSQL += _T(",积分 = ");
    _ltot(Integral, tmp, 10);
    szSQL += tmp;
    szSQL += _T(",状态 = '入坐'");
    Update(szSQL, szCondition);
    SendLogonUserInfoToAllLogonedUser(szLoss, TRUE);
    
    cmd.AddPara(szLoss);
    cmd.AddPara(Integral);
   
    szSQL = _T("下棋总盘数,赢的盘数,积分");
    szCondition = _T("用户名 = '") + szWin + ("'");
    Search(szSQL, szCondition);
    m_AdoRecSet.GetCollect(_T("下棋总盘数"), Total);
    m_AdoRecSet.GetCollect(_T("赢的盘数"), Win);
    m_AdoRecSet.GetCollect(_T("积分"), Integral);
    Total++;
    Integral += Add;
    Win++;
    szSQL = _T("下棋总盘数 = ");
    _ltot(Total, tmp, 10);
    szSQL += tmp;
    szSQL += _T(",赢的盘数 = ");
    _ltot(Win, tmp, 10);
    szSQL += tmp;
    szSQL += _T(",积分 = ");
    _ltot(Integral, tmp, 10);
    szSQL += tmp;
    szSQL += _T(",状态 = '入坐'");
    Update(szSQL, szCondition);
    SendLogonUserInfoToAllLogonedUser(szWin, TRUE);
    
    cmd.AddPara(szWin);
    cmd.AddPara(Win);
    SendData(szWin, cmd);
    SendData(szLoss, cmd);

    //发送椅子信息
    szSQL = _T("椅子号");
    szCondition = _T("用户名 = '") + szWin + _T("'");
    Search(szSQL, szCondition);
    m_AdoRecSet.GetCollect(_T("椅子号"), szSQL);

    szCondition = _T("ChairNo = ") + szSQL;
    szSQL = _T("Hand = 0");
    Update(szSQL, szCondition, tabChair);

    szSQL = _T("椅子号");
    szCondition = _T("用户名 = '") + szLoss + _T("'");
    Search(szSQL, szCondition);
    m_AdoRecSet.GetCollect(_T("椅子号"), szSQL);

    szCondition = _T("ChairNo = ") + szSQL;
    szSQL = _T("Hand = 0");
    Update(szSQL, szCondition, tabChair);
    
    SendChairInfo(TRUE);

}

/*******************************************************************************************************
函数名：VideoConn
描  述：请求视频连接
参  数：无
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-7-3 11:15:24
*******************************************************************************************************/
void CProcess::VideoConn()
{
    CString szUser, szUserName, szPort, szSQL, szCondition;
    szUser = m_pCmd->GetPara();
    szUserName = m_pCmd->GetPara();
    szPort.Format(_T("%d"), m_uPort);
    //修改数据库
    szSQL = _T("VidoPort = ") + szPort;
    szCondition = _T("用户名 = '") + szUser + _T("'");
    Update(szSQL, szCondition, tabInfo);
    CCommand cmd;
    cmd.SetCommand(g_cmdVideoConn);
    cmd.AddPara(szUser);
    cmd.AddPara(m_uPort);
    cmd.AddPara(m_szIP);
    SendData(szUserName, cmd);
}

/*******************************************************************************************************
函数名：AudioConn
描  述：请求音频连接
参  数：无
返回值：
版  本：1.0.0.1
作  者：康  林
时  间：2005-7-3 11:15:42
*******************************************************************************************************/
void CProcess::AudioConn()
{
    CString szUser, szUserName, szPort, szSQL, szCondition;
    szUser = m_pCmd->GetPara();
    szUserName = m_pCmd->GetPara();
    szPort.Format(_T("%d"), m_uPort);
    //修改数据库
    szSQL = _T("AudioPort = ") + szPort;
    szCondition = _T("用户名 = '") + szUser + _T("'");
    Update(szSQL, szCondition, tabInfo);
    CCommand cmd;
    cmd.SetCommand(g_cmdAudioConn);
    cmd.AddPara(szUser);
    cmd.AddPara(m_uPort);
    cmd.AddPara(m_szIP);
    SendData(szUserName, cmd);
}

/*******************************************************************************************************
函数名：AgreeAudioConn
描  述：同意音频连接
参  数：无
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-7-3 11:16:00
*******************************************************************************************************/
void CProcess::AgreeAudioConn()
{
    CString szUser, szUserName, szPort, szSQL, szCondition;
    szUser = m_pCmd->GetPara();
    szUserName = m_pCmd->GetPara();
    szPort.Format(_T("%d"), m_uPort);
    //修改数据库
    szSQL = _T("AudioPort = ") + szPort;
    szCondition = _T("用户名 = '") + szUser + _T("'");
    Update(szSQL, szCondition, tabInfo);
    CCommand cmd;
    cmd.SetCommand(g_cmdAgreeAudioConn);
    cmd.AddPara(szUser);
    cmd.AddPara(m_uPort);
    cmd.AddPara(m_szIP);
    SendData(szUserName, cmd);
}

/*******************************************************************************************************
函数名：AgreeVideoConn
描  述：同意视频连接
参  数：无
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-7-3 11:16:15
*******************************************************************************************************/
void CProcess::AgreeVideoConn()
{
    CString szUser, szUserName, szPort, szSQL, szCondition;
    szUser = m_pCmd->GetPara();
    szUserName = m_pCmd->GetPara();
    szPort.Format(_T("%d"), m_uPort);
    //修改数据库
    szSQL = _T("VidoPort = ") + szPort;
    szCondition = _T("用户名 = '") + szUser + _T("'");
    Update(szSQL, szCondition, tabInfo);
    CCommand cmd;
    cmd.SetCommand(g_cmdAgreeVideoConn);
    cmd.AddPara(szUser);
    cmd.AddPara(m_uPort);
    cmd.AddPara(m_szIP);
    SendData(szUserName, cmd);
}

/*******************************************************************************************************
函数名：NoAgreeAudio
描  述：不同意音频连接
参  数：无
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-7-3 11:16:27
*******************************************************************************************************/
void CProcess::NoAgreeAudio()
{
    CString szUser, szUserName;
    szUser = m_pCmd->GetPara(); //拒绝视频请求
    szUserName = m_pCmd->GetPara();
    CCommand cmd;
    cmd.SetCommand(g_cmdNoAudio);
    cmd.AddPara(szUser);
    cmd.AddPara(szUserName);
    SendData(szUserName, cmd);
}

/*******************************************************************************************************
函数名：NoAgreeVideo
描  述：不同意视频连接
参  数：无
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-7-3 11:16:40
*******************************************************************************************************/
void CProcess::NoAgreeVideo()
{
    CString szUser, szUserName;
    szUser = m_pCmd->GetPara(); //拒绝视频请求
    szUserName = m_pCmd->GetPara();
    CCommand cmd;
    cmd.SetCommand(g_cmdNoVideo);
    cmd.AddPara(szUser);
    cmd.AddPara(szUserName);
    SendData(szUserName, cmd);
}