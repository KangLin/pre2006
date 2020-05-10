/*******************************************************************************************************
�ļ�����Process.cpp
��  �ܣ��������Ĵ���
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-12-30
ʱ  �䣺16:22:41

FileName��Process.cpp
Function��
Compiler��Visual C++ 6.0
Author��  KangLin
          Copyright 2004 KangLin
Date��    2004-12-30
Time��    16:22:41
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
��������SetSocket
��  �ܣ�
��  ����
         CUDPSocket *pSock��
����ֵ��
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-3
ʱ  �䣺17:17:53
*******************************************************************************************************/
void CProcess::SetSocket(CUDPSocket *pSock)
{
    m_sckCommand = pSock;
}

/*******************************************************************************************************
��������SetConnection
��  �ܣ����ü�¼����
��  ����
         CAdoConnection *pconn����¼����ָ��
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-1
ʱ  �䣺16:23:55
*******************************************************************************************************/
void CProcess::SetConnection(CAdoConnection *pconn)
{
    m_pAdoConn = pconn;
    m_AdoRecSet.SetAdoConnection(m_pAdoConn);
}

/*******************************************************************************************************
��������SetCommand
��  �ܣ���������
��  ����
         CCommand *pCmd������ָ��
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-29
ʱ  �䣺17:43:54
*******************************************************************************************************/
void CProcess::SetCommand(CCommand *pCmd)
{
    m_pCmd = pCmd;
}

/*******************************************************************************************************
��������SendData
��  �ܣ���������
��  ����
         LPVOID lpBuf������
         INT iLen�����ݵĳ���
����ֵ���ɹ����� TRUE,���򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-28
ʱ  �䣺11:33:57
*******************************************************************************************************/
BOOL CProcess::SendData(LPVOID lpBuf, INT iLen)
{
    return m_sckCommand->SendDataTo(lpBuf, iLen, m_uPort, m_szIP);
}

/*******************************************************************************************************
��������SendData
��  �ܣ���������
��  ����
         CCommand cmd��
����ֵ���ɹ����� TRUE,���򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-28
ʱ  �䣺19:37:05
*******************************************************************************************************/
BOOL CProcess::SendData(CCommand& cmd)
{
    return SendData(cmd.GetDataRef(), cmd.GetLength());
}

/*******************************************************************************************************
��������SendData
��  �ܣ���������
��  ����
         CCommand *pcmd��
����ֵ���ɹ����� TRUE,���򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-1
ʱ  �䣺17:55:05
*******************************************************************************************************/
BOOL CProcess::SendData(CCommand *pcmd)
{
    return SendData(pcmd->GetDataRef(), pcmd->GetLength());
}

/*******************************************************************************************************
��������SendData
��  �ܣ���ָ�����û���������
��  ����
         LPCTSTR lpszUserName���û���
         CCommand &cmd������
����ֵ���ɹ����� TRUE,���򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-30
ʱ  �䣺15:58:05
*******************************************************************************************************/
BOOL CProcess::SendData(LPCTSTR lpszUserName, CCommand &cmd)
{
    return SendData(lpszUserName, cmd.GetDataRef(), cmd.GetLength());
}

/*******************************************************************************************************
��������SendData
��  �ܣ���ָ�����û���������
��  ����
         LPCTSTR lpszUserName���û���
         LPVOID lpData������
         int iLen�����ݳ���
����ֵ���ɹ����� TRUE,���򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-28
ʱ  �䣺13:06:20
*******************************************************************************************************/
BOOL CProcess::SendData(LPCTSTR lpszUserName, LPVOID lpData, int iLen)
{
    CString szSQL;
    szSQL = _T("Select �ⲿIP, �ⲿPort From Info Where �û��� = '");
    szSQL += lpszUserName;
    szSQL += _T("'");
    CAdoRecordSet AdoRecSet;
    AdoRecSet.SetAdoConnection(m_pAdoConn);
    AdoRecSet.Open(szSQL);
    CString szIP;
    long lPort;
    if(!AdoRecSet.GetCollect(_T("�ⲿIP"), szIP))
    {
        ASSERT(0);//�޴��û�
        return FALSE;
    }
    if(!AdoRecSet.GetCollect(_T("�ⲿPort"), lPort))
    {
        ASSERT(0);//�޴��û�
        return FALSE;
    }
    return m_sckCommand->SendDataTo(lpData, iLen, lPort, szIP);
}

/*******************************************************************************************************
��������SendDataToAllUser
��  �ܣ��������ѵ�¼���û�������Ϣ���������û����͡�
        ��� lpszSendUserName ΪNULL���������е�¼�û�������Ϣ
��  ����
         CCommand &cmd��Ҫ���͵���Ϣ
         LPCTSTR lpszSendUserName��������Ϣ���û���
                   �����ֵΪNULL���������е�¼�û�������Ϣ
����ֵ���ɹ����� TRUE,���򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-30
ʱ  �䣺16:03:34
*******************************************************************************************************/
BOOL CProcess::SendDataToAllUser(CCommand &cmd, LPCTSTR lpszSendUserName)
{
    return SendDataToAllUser(cmd.GetDataRef(), cmd.GetLength(), lpszSendUserName);
}

/*******************************************************************************************************
��������SendDataToAllUser
��  �ܣ��������ѵ�¼���û�������Ϣ���������û����͡�
        ��� lpszSendUserName ΪNULL���������е�¼�û�������Ϣ
��  ����
         LPVOID lpData��Ҫ���͵���Ϣ
         int iLen��Ҫ���͵���Ϣ�ĳ���
         LPCTSTR lpszSendUserName��������Ϣ���û�����
                   �����ֵΪNULL���������е�¼�û�������Ϣ
����ֵ���ɹ����� TRUE,���򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-30
ʱ  �䣺16:19:45
*******************************************************************************************************/
BOOL CProcess::SendDataToAllUser(LPVOID lpData, int iLen, LPCTSTR lpszSendUserName)
{
    CString szSQL(_T("Select �û��� From UserInfo Where ״̬ <> 'δ��¼'"));
    CAdoRecordSet AdoRecSet;
    AdoRecSet.SetAdoConnection(m_pAdoConn);
    if(!AdoRecSet.Open(szSQL))
    {
        /*TRACE(_T("%s(%d) : �������ѵ�¼�û�������Ϣ,�����û�����\n"), __FILE__, __LINE__);*/
        return FALSE;
    }
    int iCount = AdoRecSet.GetRecordCount();
    for(int i = 0; i < iCount; i++)
    {
        AdoRecSet.GetCollect(_T("�û���"), szSQL);
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
��������Update
��  �ܣ����±��е��ֶ�
��  ����
         LPCTSTR lpUpdate���ֶα��ʽ
         LPCTSTR lpCondition������
         ENUM_TABLE eTable����
����ֵ���ɹ����� TRUE,���򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-28
ʱ  �䣺15:22:06
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
��������Search
��  �ܣ����ұ��е�ָ���ֶ�
��  ����
         LPCTSTR lpszFields���ֶ�
         LPCTSTR lpszCondition������
         ENUM_TABLE eTable����
����ֵ���ɹ����� TRUE,���򷵻� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-30
ʱ  �䣺10:53:31
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
��������Logon
��  �ܣ���¼����Ĵ���
��  ������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-28
ʱ  �䣺11:35:35
*******************************************************************************************************/
void CProcess::Logon()
{
    CString szUser;
    CString szPassword;
    CString szIP;
    UINT uPort;
    DWORD dwVer;//�汾��
    szUser = m_pCmd->GetPara();
    szPassword = m_pCmd->GetPara();
    //����:����IP��Port
    
    dwVer = m_pCmd->GetLongPara();
    /*TRACE(_T("%s(%d) : �汾��:���汾��:%d;�ΰ汾��:%d\n"), __FILE__, __LINE__, LOWORD(dwVer), HIWORD (dwVer));*/
    /*TRACE(_T("%s(%d) : �û���:%s:����:%s\n"), __FILE__, __LINE__, szUser, szPassword);*/
    //�����û�
    CString szSQL;
    szSQL = "Select ���� From Info where �û��� = '";
    szSQL += szUser;
    szSQL += _T("'");
    m_AdoRecSet.Open(szSQL);
   
    CString password; 
    m_AdoRecSet.GetCollect(_T("����"), password);
    /*TRACE(_T("%s(%d) : password:%s\n"), __FILE__, __LINE__, password);*/

    CCommand command;
    //��¼����
    command.SetCommand(g_cmdLogon);
    if(password.IsEmpty())//�û�������
    {
        //����:�޴��û�
        /*TRACE(_T("%s(%d) : �û�������, ����\n"), __FILE__, __LINE__);*/
        command.AddPara(g_cmdLogonNoUser);
        SendData(command);
        return;
    }
    if(password != szPassword)
    {
        //�������
        /*TRACE(_T("%s(%d) : �������\n"), __FILE__, __LINE__);*/
        command.AddPara(g_cmdLogonPasswordError);
        SendData(command);        
    }
    else//������ȷ
    {
        /*TRACE(_T("%s(%d) : ������ȷ\n"), __FILE__, __LINE__);*/
        //����:������ȷ
        command.AddPara(g_cmdLogonSuccess);
        SendData(command);

        CString szCondition;
        szSQL = _T("״̬");
        szCondition = _T("�û��� = '");
        szCondition += szUser;
        szCondition += _T("'");
        Search(szSQL, szCondition);
        m_AdoRecSet.GetCollect(_T("״̬"), szSQL);

        //�޸����ݿ�
        if(szSQL == _T("δ��¼"))
        {
            /*TRACE(_T("%s(%d) : �û��ѵ�¼;״̬:%s\n"), __FILE__, __LINE__, szSQL);*/
            Update(_T("״̬ = '�ѵ�¼'"), szCondition); 
        }
        CString szUpdate;
        szUpdate =_T("�ⲿIP = '");
        szUpdate += m_szIP;
        szUpdate += _T("', ");
        szUpdate += _T("�ⲿPort = ");
        CString sztmp;
        sztmp.Format(_T("%d"), m_uPort);
        szUpdate += sztmp;
        //����:�ڲ�IP,�ڲ�Port
        Update(szUpdate, szCondition, tabInfo); 

        //�������ѵ�¼���û��������û���¼��Ϣ
        SendLogonUserInfoToAllLogonedUser(szUser);

        //���¼�û����������ѵ�¼�û�����Ϣ
        SendAllLogonedUserInfo();

        //���¼�û��������ӵ���Ϣ
        SendChairInfo();
        
        //����:����Ƿ����µİ汾
    }
}

/*******************************************************************************************************
��������GetUserInfo
��  �ܣ��õ���ǰ��¼���е��û���Ϣ
��  ����
         CCommand *pCmd������
����ֵ���ɹ����� TRUE, ���򷵻� FALSE.
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-31
ʱ  �䣺15:28:02
*******************************************************************************************************/
BOOL CProcess::GetUserInfo(CCommand *pCmd)
{
    CString sztmp;    
    m_AdoRecSet.GetCollect(_T("�û���"), sztmp);
    pCmd->AddPara (sztmp);
    m_AdoRecSet.GetCollect(_T("����������"), sztmp);
    pCmd->AddPara (sztmp);
    m_AdoRecSet.GetCollect(_T("Ӯ������"), sztmp);
    pCmd->AddPara (sztmp);
    m_AdoRecSet.GetCollect(_T("�������"), sztmp);
    pCmd->AddPara (sztmp);
    m_AdoRecSet.GetCollect(_T("�͵�����"), sztmp);
    pCmd->AddPara (sztmp);
    m_AdoRecSet.GetCollect(_T("����"), sztmp);
    pCmd->AddPara (sztmp);
    m_AdoRecSet.GetCollect(_T("�Ա�"), sztmp);
    pCmd->AddPara (sztmp);
    m_AdoRecSet.GetCollect(_T("״̬"), sztmp);
    pCmd->AddPara (sztmp);
    m_AdoRecSet.GetCollect(_T("ͷ��"), sztmp);
    pCmd->AddPara (sztmp);
    return TRUE;
}

/*******************************************************************************************************
��������SendLogonUserInfoToAllLogonedUser
��  �ܣ��������ѵ�¼���û�����ָ���û�����Ϣ
��  ����
         LPCTSTR szUserName���û���
         BOOL bUser: �Ƿ�Ҳ��ָ�����û����ͣ�Ĭ��Ϊ FALSE��
                     FALSE������ָ���û�����
                     TRUE����ָ�����û�����
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-30
ʱ  �䣺15:34:57
*******************************************************************************************************/
void CProcess::SendLogonUserInfoToAllLogonedUser(LPCTSTR szUserName, BOOL bUser)
{
    CString szSQL;
    szSQL = _T("Select * From UserInfo Where �û��� = '");
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
��������SendAllLogonedUserInfo
��  �ܣ����µ�¼�û����������ѵ�¼�û�����Ϣ
��  ����
         LPCTSTR lpszUser���µ�¼�û���
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-30
ʱ  �䣺17:00:59
*******************************************************************************************************/
void CProcess::SendAllLogonedUserInfo()
{
    CCommand cmd;
    //���ͱ�ͷ
    cmd.SetCommand(g_cmdUserInfoHead);
    cmd.AddPara(_T("�û���"));
    cmd.AddPara(_T("����������"));
    cmd.AddPara(_T("Ӯ������"));
    cmd.AddPara(_T("�������"));
    cmd.AddPara(_T("�͵�����"));
    cmd.AddPara(_T("����"));
    cmd.AddPara(_T("�Ա�"));
    cmd.AddPara(_T("״̬"));
    cmd.AddPara(_T("ͷ��"));
    SendData(cmd);
    //�����ѵ�¼�û�����Ϣ
    CString szSQL;
    szSQL = _T("Select * From UserInfo Where ״̬ <> 'δ��¼'");
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
��������GetChairInfo
��  �ܣ��õ�ָ��������Ϣ
��  ����
         int iChairNo�����Ӻ�
         CCommand* pCmd��
����ֵ���ɹ����� TRUE,ʧ�ܷ��� FALSE
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-3
ʱ  �䣺20:04:10
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
    pCmd->AddPara(szSQL);    //�û���
    pCmd->AddPara(iChairNo); //���Ӻ�
    return TRUE;
}

/*******************************************************************************************************
��������SendChairInfo
��  �ܣ����¼�û�����������Ϣ
��  ��������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-3
ʱ  �䣺20:03:18
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
            cmd.AddPara(szSQL); //�û���
            cmd.AddPara(i + 1); //���Ӻ�
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
��������LeaveChair
��  �ܣ��뿪����
��  ������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-3
ʱ  �䣺21:10:25
*******************************************************************************************************/
void CProcess::LeaveChair()
{
    CString szUser, szUserName;
    CString szChairNo;
    szUser = m_pCmd->GetPara(); //�뿪���û���
    szChairNo = m_pCmd->GetPara();
    szUserName = m_pCmd->GetPara(); //�Է��û���
    CString szSQL;    
    CString szCondition;

    szSQL = _T("UserName = '', Hand = 0");
    szCondition = _T("ChairNo = ");
    szCondition += szChairNo;
    Update(szSQL, szCondition, tabChair);
    szSQL = _T("���Ӻ� = 0, ״̬ = '�ѵ�¼'");
    szCondition = _T("�û��� = '") + szUser + _T("'");
    Update(szSQL, szCondition);
    //����������Ϣ
    CCommand cmd;
    cmd.SetCommand(g_cmdChairInfo);
    cmd.AddPara("");        //�û���
    cmd.AddPara(szChairNo); //���Ӻ�
    cmd.AddPara(0);
    SendDataToAllUser(cmd);
    //֪ͨ�����û�
    SendLogonUserInfoToAllLogonedUser(szUser, TRUE);

    if(szUserName != _T(""))
    {
        cmd.SetCommand(g_cmdLeaveChair);
        cmd.AddPara(szUser);         //�뿪���û���
        SendData(szUserName, cmd);
    }
    /*TRACE(_T("%s(%d) : �û� %s �뿪���� %s\n"), __FILE__, __LINE__, szUser, szChairNo);*/
}

/*******************************************************************************************************
��������Exit
��  �ܣ��û��˳�
��  ������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2004-12-31
ʱ  �䣺12:40:47
*******************************************************************************************************/
void CProcess::Exit()
{
    CString szUser;
    CString szSQL;
    CString szCondition;
    szUser = m_pCmd->GetPara();
    //�������ݿ�
    szSQL = _T("״̬ = 'δ��¼'");
    szCondition = _T("�û��� = '") + szUser + _T("'");
    Update(szSQL, szCondition);
    //�������û����ʹ��û��˳�����
    CCommand cmd;
    cmd.SetCommand(g_cmdExit);
    cmd.AddPara(szUser);
    SendDataToAllUser(cmd, szUser);
    /*TRACE(_T("%s(%d) : �û� %s �˳�\n"), __FILE__, __LINE__, szUser);*/
}

/*******************************************************************************************************
��������Regist
��  �ܣ��û�ע��
��  ������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-1
ʱ  �䣺14:17:49
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
    /*TRACE(_T("%s(%d) : �û���:%s����:%s�Ա�:%s����:%sͷ��:%s\n"), __FILE__, __LINE__, szUserName, szPassword, szSex, szAge, szImage);*/

    CString szSQL(_T("Select �û��� From Info Where �û��� = '"));
    szSQL = szSQL + szUserName + _T("'");
    m_AdoRecSet.Open(szSQL);
    CString sztmp;
    m_AdoRecSet.GetCollect(_T("�û���"), sztmp);
    CCommand cmd;
    cmd.SetCommand(g_cmdRegist);
    if(!sztmp.IsEmpty())
    {
        /*TRACE(_T("%s(%d) : �û� %s �Ѵ���\n"), __FILE__, __LINE__, szUserName);*/
        cmd.AddPara(g_cmdRegistHadUser);
    }
    else
    {
        //�������ݿ�
        szSQL = _T("Insert Into Info (�û���, ����) Values('") \
            + szUserName  + _T("','") + szPassword + _T("')");
        m_AdoRecSet.Open(szSQL);
        szSQL = _T("Insert Into UserInfo (�û���, �Ա�, ����, ͷ��) Values('") \
            + szUserName + _T("', '") + szSex + _T("', '") \
            + szAge + _T("', '") + szImage + _T("')");
        m_AdoRecSet.Open(szSQL);
        cmd.AddPara(g_cmdRegistSuccess);
    }
    SendData(cmd);
}

/*******************************************************************************************************
��������SendTextMessage
��  �ܣ�ת���ı���Ϣ
��  ������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-1
ʱ  �䣺17:50:05
*******************************************************************************************************/
void CProcess::SendTextMessage()
{
    CString szSendUser; //������Ϣ��
    CString szUser;     //������Ϣ��
    CString szText;     //�ı���Ϣ
    szSendUser = m_pCmd->GetPara();
    szUser = m_pCmd->GetPara();
    szText = m_pCmd->GetPara();
    m_pCmd->SetCommand(g_cmdSendTextMessage);
    m_pCmd->AddPara(szText);
    szText = szUser;
    szText.MakeLower();
    if(szText == _T("������") || szText == _T("all"))
    {
        SendDataToAllUser(*m_pCmd, szSendUser);
    }
    else
    {
        SendData(szUser, *m_pCmd);
    }
}

/*******************************************************************************************************
��������SetDown
��  �ܣ��û�����
��  ������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-3
ʱ  �䣺16:58:00
*******************************************************************************************************/
void CProcess::SetDown()
{
    CCommand cmd;
    CString szUser;
    CString szChairNo;
    CString szInPort;
    szUser = m_pCmd->GetPara();    //�û���
    szChairNo = m_pCmd->GetPara(); //���Ӻ�
    szInPort = m_pCmd->GetPara();  //�ⲿ�˿ں�
    /*TRACE(_T("%s(%d) : �û���:%s,���Ӻ�:%s\n"), __FILE__, __LINE__, szUser, szChairNo);*/
    CString szSQL(_T("Select UserName From Chair Where ChairNo = "));
    szSQL += szChairNo;
    m_AdoRecSet.Open(szSQL);
    CString szOtherUser;
    m_AdoRecSet.GetCollect(_T("UserName"), szOtherUser);
    cmd.SetCommand(g_cmdSetDown);
    if(szOtherUser != _T(""))
    {
        /*TRACE(_T("%s(%d) : ����λ������\n"), __FILE__, __LINE__);*/
        cmd.AddPara(g_cmdHadMan);
        SendData(cmd);
        return;
    }

    //------------------------------------------------------------------------
    //��������� ===�޸����ݿ�=== ���ܵ�����
    //

    //������Ϣ
    szSQL = _T("UserName = '") + szUser + _T("'");
    CString szCondition(_T("ChairNo ="));
    szCondition += szChairNo;
    Update(szSQL, szCondition, tabChair);
    //�û���Ϣ
    szSQL = _T("���Ӻ� = ") + szChairNo + _T(", ״̬ = '����'");
    szCondition = _T("�û��� = '") + szUser + _T("'");
    Update(szSQL, szCondition);
    //����socket���ⲿport
    CString szPort, szLocatePort;
    szPort.Format(_T("%d"), m_uPort);
    szLocatePort.Format(_T("%d"), szInPort);
    szSQL = _T("ChessPort =") + szPort + _T(", InChessPort = ") + szLocatePort;
    szCondition = _T("�û��� = '") + szUser + _T("'");
    Update(szSQL, szCondition, tabInfo);

    //
    //��������� ===�޸����ݿ�=== ���ܵ�����
    //------------------------------------------------------------------------
    

    //����������Ϣ
    cmd.SetCommand(g_cmdChairInfo);
    cmd.AddPara(szUser);    //�û���
    cmd.AddPara(szChairNo); //���Ӻ�
    cmd.AddPara(0);
    SendDataToAllUser(cmd);
    /*TRACE(_T("%s(%d) : ��������������Ϣ.�û���=%s,���Ӻ�=%s\n"), __FILE__, __LINE__, szUser, szChairNo);*/

    //������������
    cmd.SetCommand(g_cmdSetDown);
    //���ҶԷ�״̬,����������
    //1���Է�û����
    //2������������
    //   2.1���Է�������,��û��ͬ�⿪ʼ
    //   2.2���Է�������,��ͬ�⿪ʼ
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
        /*TRACE(_T("%s(%d) : �Է�û����\n"), __FILE__, __LINE__);*/
        cmd.AddPara(g_cmdOtherNoMan);
        SendData(cmd);
    }
    else
    {
        if(szOtherUser == _T(""))
        {
            /*TRACE(_T("%s(%d) : �Է�û����\n"), __FILE__, __LINE__);*/
            cmd.AddPara(g_cmdOtherNoMan);
            SendData(cmd);
        }
        else //��������
        {
            szSQL = _T("״̬");
            szCondition = _T("�û��� = '") + szOtherUser + _T("'");
            Search(szSQL, szCondition);
            CString szState;
            m_AdoRecSet.GetCollect(_T("״̬"), szState);
            if(szState == _T("����"))
            {
                cmd.AddPara(g_cmdOtherSetDown);
                /*TRACE(_T("%s(%d) : ����������û��ʼ\n"), __FILE__, __LINE__);*/
            }
            if(szState == _T("��ʼ"))
            {
                cmd.AddPara(g_cmdOtherStart);
                /*TRACE(_T("%s(%d) : ������������ͬ�⿪ʼ\n"), __FILE__, __LINE__);*/
            }
            cmd.AddPara (szOtherUser); //�Է��û���
            //����Է��ĵ�ַ
            CString szExIP, szExPort, szIP, szPort, szExChessPort, szChessPort;
            szSQL = _T("�ⲿIP, �ⲿPort, �ڲ�IP, �ڲ�Port, ChessPort");
            szCondition = _T("�û��� = '") + szOtherUser + _T("'");
            Search(szSQL, szCondition, tabInfo);
            m_AdoRecSet.GetCollect(_T("�ⲿIP"), szExIP);
            m_AdoRecSet.GetCollect(_T("�ڲ�IP"), szIP);
            m_AdoRecSet.GetCollect(_T("�ⲿPort"), szExPort);
            m_AdoRecSet.GetCollect(_T("�ڲ�Port"), szPort);
            m_AdoRecSet.GetCollect(_T("ChessPort"), szExChessPort);
            m_AdoRecSet.GetCollect(_T("InChessPort"), szChessPort);
            cmd.AddPara (szExIP);       //�ⲿIP
            cmd.AddPara(szExPort);      //�ⲿPport
            cmd.AddPara(szIP);          //�ڲ�IP
            cmd.AddPara(szPort);        //�ڲ�Port
            cmd.AddPara(szExChessPort); //�ⲿ����Port
            cmd.AddPara(szChessPort);   //�ڲ�����Port

            SendData(cmd);

            //��Է��û�֪ͨ���û�����
            cmd.SetCommand(g_cmdOtherSetDown);
            cmd.AddPara(szUser);        //�û���
            szSQL = _T("�ⲿIP, �ⲿPort, �ڲ�IP, �ڲ�Port, ChessPort");
            szCondition = _T("�û��� = '") + szUser + _T("'");
            Search(szSQL, szCondition, tabInfo);
            m_AdoRecSet.GetCollect(_T("�ⲿIP"), szExIP);
            m_AdoRecSet.GetCollect(_T("�ڲ�IP"), szIP);
            m_AdoRecSet.GetCollect(_T("�ⲿPort"), szExPort);
            m_AdoRecSet.GetCollect(_T("�ڲ�Port"), szPort);
            m_AdoRecSet.GetCollect(_T("ChessPort"), szExChessPort);
            m_AdoRecSet.GetCollect(_T("InChessPort"), szChessPort);
            cmd.AddPara (szExIP);       //�ⲿIP
            cmd.AddPara(szExPort);      //�ⲿPport
            cmd.AddPara(szIP);          //�ڲ�IP
            cmd.AddPara(szPort);        //�ڲ�Port
            cmd.AddPara(szExChessPort); //�ⲿ����Port
            cmd.AddPara(szChessPort);   //�ڲ�����Port

            SendData(szOtherUser, cmd);
        }
    }
    
    //֪ͨ�����û�
    SendLogonUserInfoToAllLogonedUser(szUser, TRUE);    
}

/*******************************************************************************************************
��������Start
��  �ܣ�����ͬ�⿪ʼ��������
��  ������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-19
ʱ  �䣺17:37:35
*******************************************************************************************************/
void CProcess::Start()
{
    CString szUser, szUserName;
    szUser = m_pCmd->GetPara();      //ͬ�ⷽ�û���
    szUserName = m_pCmd->GetPara();  //�Է��û���
    /*TRACE(_T("%s(%d) : %s ͬ���� %s ��ʼ����\n"), __FILE__, __LINE__, szUser, szUserName);*/
    CString szSQL, szCondition;
  
    //�Է��Ƿ�����
    if(szUserName != _T(""))
    {
        szSQL = _T("״̬");
        szCondition = _T("�û��� = '") + szUserName + _T("'");
        Search(szSQL, szCondition);
        m_AdoRecSet.GetCollect(_T("״̬"), szSQL);
    }
    else //�Է�û����
    {
        szSQL = _T("״̬ = '��ʼ'");
        szCondition = _T("�û��� = '") + szUser + _T("'");
        Update(szSQL, szCondition);
        CCommand cmd;
        cmd.SetCommand(g_cmdStart);
        cmd.AddPara(szUser);
        SendData(szUser, cmd);
        //֪ͨ�����û�
        SendLogonUserInfoToAllLogonedUser(szUser, TRUE);

        //����������Ϣ
        szSQL = _T("���Ӻ�");
        szCondition = _T("�û��� = '") + szUser + _T("'");
        Search(szSQL, szCondition);
        m_AdoRecSet.GetCollect(_T("���Ӻ�"), szSQL);

        szCondition = _T("ChairNo = ") + szSQL;
        szSQL = _T("Hand = 1");
        Update(szSQL, szCondition, tabChair);
        SendChairInfo(TRUE);

        return;
    }
    //�Է�����
    //�鿴�Է�״̬
    if(szSQL == _T("��ʼ"))
    {
        //�޸����ݿ�
        szSQL = _T("״̬ = '����'");
        szCondition = _T("�û��� = '") + szUser + _T("'");
        Update(szSQL, szCondition);
        szCondition = _T("�û��� = '") + szUserName + _T("'");
        Update(szSQL, szCondition);
        //֪ͨ�����û�
        SendLogonUserInfoToAllLogonedUser(szUserName, TRUE);
        SendLogonUserInfoToAllLogonedUser(szUser, TRUE);
        CCommand cmd;
        cmd.SetCommand(g_cmdStart);
        cmd.AddPara(szUserName);   //���߷�
        cmd.AddPara(szUser);       //���߷�
        SendData(szUser, cmd);
        SendData(szUserName, cmd);

        CString szIP, szPort;
        cmd.SetCommand(g_cmdPlayChess);
        cmd.AddPara(szUserName);   //���߷�
        szSQL = _T(" �ⲿIP,ChessPort ");
        szCondition = _T("�û��� = '") + szUserName + _T("'");
        Search(szSQL, szCondition, tabInfo);
        m_AdoRecSet.GetCollect(_T("�ⲿIP"), szIP);
        m_AdoRecSet.GetCollect(_T("ChessPort"), szPort);
        cmd.AddPara(szIP);
        cmd.AddPara(szPort);
       
        cmd.AddPara(szUser);       //���߷�
        szCondition = _T("�û��� = '") + szUser + _T("'");
        Search(szSQL, szCondition, tabInfo);
        m_AdoRecSet.GetCollect(_T("�ⲿIP"), szIP);
        m_AdoRecSet.GetCollect(_T("ChessPort"), szPort);
        cmd.AddPara(szIP);
        cmd.AddPara(szPort);

        SendData(szUser, cmd);
        SendData(szUserName, cmd);
    }
    else
    {
        szSQL = _T("״̬ = '��ʼ'");
        szCondition = _T("�û��� = '") + szUser + _T("'");
        Update(szSQL, szCondition);
        //֪ͨ�����û�
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

    //����������Ϣ
    szSQL = _T("���Ӻ�");
    szCondition = _T("�û��� = '") + szUser + _T("'");
    Search(szSQL, szCondition);
    m_AdoRecSet.GetCollect(_T("���Ӻ�"), szSQL);

    szCondition = _T("ChairNo = ") + szSQL;
    szSQL = _T("Hand = 1");
    Update(szSQL, szCondition, tabChair);
    SendChairInfo(TRUE);
}

/*******************************************************************************************************
��������StandOff
��  ���������������
��  ����
         void����
����ֵ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-11 16:44:24
*******************************************************************************************************/
void CProcess::StandOff(void)
{
    CString szUser, szSQL, szCondition;
    TCHAR sztmp[10];
    szUser = m_pCmd->GetPara();
    long iStandOff, iTotal;
    szSQL = _T("�͵�����,����������");
    szCondition = _T("�û��� = '") + szUser + ("'");
    Search(szSQL, szCondition);
    m_AdoRecSet.GetCollect(_T("�͵�����"), iStandOff);
    m_AdoRecSet.GetCollect(_T("����������"), iTotal);
    szSQL = _T("״̬ = '����', �͵����� = ");
    _ltot(iStandOff + 1, sztmp, 10);
    szSQL = szSQL + sztmp;
    szSQL += _T(",���������� = ");
    _ltot(iTotal + 1, sztmp, 10);
    szSQL = szSQL + sztmp;
    Update(szSQL, szCondition);
}

/*******************************************************************************************************
��������Giveup
��  ����������������
��  ������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-6-11 22:11:31
*******************************************************************************************************/
void CProcess::Giveup()
{
    CString szLoss, szWin, szSQL, szCondition;
    long Add, Inc, Total, Win, Loss, Integral;
    TCHAR tmp[10];
    CCommand cmd;
    cmd.SetCommand(g_cmdReceiveGiveup);

    szLoss = m_pCmd->GetPara();   //���䷽
    szWin = m_pCmd->GetPara();    //Ӯ��
    Add = m_pCmd->GetLongPara();  //�ӷ�ֵ
    Inc = m_pCmd->GetLongPara();  //����ֵ
    //����:���������ò���

    szSQL = _T("����������,�������,����");
    szCondition = _T("�û��� = '") + szLoss + ("'");
    Search(szSQL, szCondition);
    m_AdoRecSet.GetCollect(_T("����������"), Total);
    m_AdoRecSet.GetCollect(_T("�������"), Loss);
    m_AdoRecSet.GetCollect(_T("����"), Integral);
    Total++;
    Integral -= Inc;
    Loss++;
    szSQL = _T("���������� = ");
    _ltot(Total, tmp, 10);
    szSQL += tmp;
    szSQL += _T(",������� = ");
    _ltot(Loss, tmp, 10);
    szSQL += tmp;
    szSQL += _T(",���� = ");
    _ltot(Integral, tmp, 10);
    szSQL += tmp;
    szSQL += _T(",״̬ = '����'");
    Update(szSQL, szCondition);
    SendLogonUserInfoToAllLogonedUser(szLoss, TRUE);
    
    cmd.AddPara(szLoss);
    cmd.AddPara(Integral);
   
    szSQL = _T("����������,Ӯ������,����");
    szCondition = _T("�û��� = '") + szWin + ("'");
    Search(szSQL, szCondition);
    m_AdoRecSet.GetCollect(_T("����������"), Total);
    m_AdoRecSet.GetCollect(_T("Ӯ������"), Win);
    m_AdoRecSet.GetCollect(_T("����"), Integral);
    Total++;
    Integral += Add;
    Win++;
    szSQL = _T("���������� = ");
    _ltot(Total, tmp, 10);
    szSQL += tmp;
    szSQL += _T(",Ӯ������ = ");
    _ltot(Win, tmp, 10);
    szSQL += tmp;
    szSQL += _T(",���� = ");
    _ltot(Integral, tmp, 10);
    szSQL += tmp;
    szSQL += _T(",״̬ = '����'");
    Update(szSQL, szCondition);
    SendLogonUserInfoToAllLogonedUser(szWin, TRUE);
    
    cmd.AddPara(szWin);
    cmd.AddPara(Win);
    SendData(szWin, cmd);
    SendData(szLoss, cmd);

    //����������Ϣ
    szSQL = _T("���Ӻ�");
    szCondition = _T("�û��� = '") + szWin + _T("'");
    Search(szSQL, szCondition);
    m_AdoRecSet.GetCollect(_T("���Ӻ�"), szSQL);

    szCondition = _T("ChairNo = ") + szSQL;
    szSQL = _T("Hand = 0");
    Update(szSQL, szCondition, tabChair);

    szSQL = _T("���Ӻ�");
    szCondition = _T("�û��� = '") + szLoss + _T("'");
    Search(szSQL, szCondition);
    m_AdoRecSet.GetCollect(_T("���Ӻ�"), szSQL);

    szCondition = _T("ChairNo = ") + szSQL;
    szSQL = _T("Hand = 0");
    Update(szSQL, szCondition, tabChair);
    
    SendChairInfo(TRUE);

}

/*******************************************************************************************************
��������VideoConn
��  ����������Ƶ����
��  ������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-7-3 11:15:24
*******************************************************************************************************/
void CProcess::VideoConn()
{
    CString szUser, szUserName, szPort, szSQL, szCondition;
    szUser = m_pCmd->GetPara();
    szUserName = m_pCmd->GetPara();
    szPort.Format(_T("%d"), m_uPort);
    //�޸����ݿ�
    szSQL = _T("VidoPort = ") + szPort;
    szCondition = _T("�û��� = '") + szUser + _T("'");
    Update(szSQL, szCondition, tabInfo);
    CCommand cmd;
    cmd.SetCommand(g_cmdVideoConn);
    cmd.AddPara(szUser);
    cmd.AddPara(m_uPort);
    cmd.AddPara(m_szIP);
    SendData(szUserName, cmd);
}

/*******************************************************************************************************
��������AudioConn
��  ����������Ƶ����
��  ������
����ֵ��
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-7-3 11:15:42
*******************************************************************************************************/
void CProcess::AudioConn()
{
    CString szUser, szUserName, szPort, szSQL, szCondition;
    szUser = m_pCmd->GetPara();
    szUserName = m_pCmd->GetPara();
    szPort.Format(_T("%d"), m_uPort);
    //�޸����ݿ�
    szSQL = _T("AudioPort = ") + szPort;
    szCondition = _T("�û��� = '") + szUser + _T("'");
    Update(szSQL, szCondition, tabInfo);
    CCommand cmd;
    cmd.SetCommand(g_cmdAudioConn);
    cmd.AddPara(szUser);
    cmd.AddPara(m_uPort);
    cmd.AddPara(m_szIP);
    SendData(szUserName, cmd);
}

/*******************************************************************************************************
��������AgreeAudioConn
��  ����ͬ����Ƶ����
��  ������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-7-3 11:16:00
*******************************************************************************************************/
void CProcess::AgreeAudioConn()
{
    CString szUser, szUserName, szPort, szSQL, szCondition;
    szUser = m_pCmd->GetPara();
    szUserName = m_pCmd->GetPara();
    szPort.Format(_T("%d"), m_uPort);
    //�޸����ݿ�
    szSQL = _T("AudioPort = ") + szPort;
    szCondition = _T("�û��� = '") + szUser + _T("'");
    Update(szSQL, szCondition, tabInfo);
    CCommand cmd;
    cmd.SetCommand(g_cmdAgreeAudioConn);
    cmd.AddPara(szUser);
    cmd.AddPara(m_uPort);
    cmd.AddPara(m_szIP);
    SendData(szUserName, cmd);
}

/*******************************************************************************************************
��������AgreeVideoConn
��  ����ͬ����Ƶ����
��  ������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-7-3 11:16:15
*******************************************************************************************************/
void CProcess::AgreeVideoConn()
{
    CString szUser, szUserName, szPort, szSQL, szCondition;
    szUser = m_pCmd->GetPara();
    szUserName = m_pCmd->GetPara();
    szPort.Format(_T("%d"), m_uPort);
    //�޸����ݿ�
    szSQL = _T("VidoPort = ") + szPort;
    szCondition = _T("�û��� = '") + szUser + _T("'");
    Update(szSQL, szCondition, tabInfo);
    CCommand cmd;
    cmd.SetCommand(g_cmdAgreeVideoConn);
    cmd.AddPara(szUser);
    cmd.AddPara(m_uPort);
    cmd.AddPara(m_szIP);
    SendData(szUserName, cmd);
}

/*******************************************************************************************************
��������NoAgreeAudio
��  ������ͬ����Ƶ����
��  ������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-7-3 11:16:27
*******************************************************************************************************/
void CProcess::NoAgreeAudio()
{
    CString szUser, szUserName;
    szUser = m_pCmd->GetPara(); //�ܾ���Ƶ����
    szUserName = m_pCmd->GetPara();
    CCommand cmd;
    cmd.SetCommand(g_cmdNoAudio);
    cmd.AddPara(szUser);
    cmd.AddPara(szUserName);
    SendData(szUserName, cmd);
}

/*******************************************************************************************************
��������NoAgreeVideo
��  ������ͬ����Ƶ����
��  ������
����ֵ����
��  ����1.0.0.1
��  �ߣ���  ��
ʱ  �䣺2005-7-3 11:16:40
*******************************************************************************************************/
void CProcess::NoAgreeVideo()
{
    CString szUser, szUserName;
    szUser = m_pCmd->GetPara(); //�ܾ���Ƶ����
    szUserName = m_pCmd->GetPara();
    CCommand cmd;
    cmd.SetCommand(g_cmdNoVideo);
    cmd.AddPara(szUser);
    cmd.AddPara(szUserName);
    SendData(szUserName, cmd);
}