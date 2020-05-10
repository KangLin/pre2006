/*******************************************************************************************************
�ļ�����Process.h
��  �ܣ��������Ĵ���
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-12-30
ʱ  �䣺16:22:53

FileName��Process.h
Function��
Compiler��Visual C++ 6.0
Author��  KangLin
          Copyright 2004 KangLin
Date��    2004-12-30
Time��    16:22:53
*******************************************************************************************************/

#if !defined(AFX_PROCESS_H__DD61E983_80C3_4DF7_99AA_D97205CD824B__INCLUDED_)
#define AFX_PROCESS_H__DD61E983_80C3_4DF7_99AA_D97205CD824B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\..\��\database\ado\ado.h"
#include "..\..\command\command.h"

class CProcess  
{
private:
    CAdoRecordSet m_AdoRecSet;  //��¼��
    CAdoConnection* m_pAdoConn; //����
    LPVOID m_lpData;            //ָ����յ����ݵ�ָ��
    int m_iDataLen;             //���յ����ݵĴ�С
    CCommand* m_pCmd;           //����
    CUDPSocket* m_sckCommand;   //Socket

    typedef enum{
        tabInfo = 0,
        tabUserInfo = 1,
        tabChair = 2
    } ENUM_TABLE;

    //�������ѵ�¼���û������µ�¼�û�����Ϣ
    void SendLogonUserInfoToAllLogonedUser(LPCTSTR szUserName, BOOL bUser = FALSE);
    //���µ�¼�û����������ѵ�¼�û�����Ϣ
    void SendAllLogonedUserInfo();
    //����������Ϣ
	void SendChairInfo(BOOL bAll = FALSE);

    //��ͻ��˷�������
    BOOL SendData(LPVOID lpBuf, INT iLen);  
    BOOL SendData(CCommand& cmd);
   	BOOL SendData(CCommand* pcmd);

    //��ָ���û���������
    BOOL SendData(LPCTSTR lpszUserName, LPVOID lpData, int iLen);
	BOOL SendData(LPCTSTR lpszUserName, CCommand& cmd);
    //�������ѵ�¼���û���������
    BOOL SendDataToAllUser(LPVOID lpData, int iLen, LPCTSTR lpszSendUserName = NULL);
    BOOL SendDataToAllUser(CCommand &cmd, LPCTSTR lpszSendUserName = NULL);
    
    //�õ���ǰ�û���Ϣ
    BOOL GetUserInfo(CCommand* pCmd);
    //�õ�ָ����������Ϣ
    BOOL GetChairInfo(int iChairNo, CCommand* pCmd);

    //�������ݿ�
    BOOL Update(LPCTSTR  lpUpdate, LPCTSTR lpCondition, ENUM_TABLE eTable = tabUserInfo);
    //��������
	BOOL Search(LPCTSTR lpszFields, LPCTSTR lpszCondition, ENUM_TABLE eTable = tabUserInfo);

public:
    //��������
    //�����������
    void StandOff(void);
    void Start();            //ͬ�⿪ʼ����
	void LeaveChair();       //�뿪����
	void SetDown();          //����
	void SendTextMessage();  //ת��������Ϣ
	void Regist();           //ע��
	void Logon();            //��¼����
    void Giveup();           //����
    void Exit();             //�˳�
    void VideoConn();        //��Ƶ��������
    void AudioConn();        //��Ƶ��������
    void AgreeVideoConn();   //ͬ����Ƶ����
    void AgreeAudioConn();   //ͬ����Ƶ����
    void NoAgreeVideo();     //��ͬ����Ƶ����
    void NoAgreeAudio();     //��ͬ����Ƶ����

	void SetConnection(CAdoConnection* pconn);
    void SetCommand(CCommand* pCmd);
	void SetSocket(CUDPSocket* pSock);

	CString m_szIP;          //�ͻ��˵�IP
    UINT m_uPort;            //�ͻ��˵�Port

	CProcess();
	virtual ~CProcess();   
};

#endif // !defined(AFX_PROCESS_H__DD61E983_80C3_4DF7_99AA_D97205CD824B__INCLUDED_)
