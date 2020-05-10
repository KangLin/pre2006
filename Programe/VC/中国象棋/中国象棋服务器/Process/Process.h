/*******************************************************************************************************
文件名：Process.h
功  能：服务器的处理
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-12-30
时  间：16:22:53

FileName：Process.h
Function：
Compiler：Visual C++ 6.0
Author：  KangLin
          Copyright 2004 KangLin
Date：    2004-12-30
Time：    16:22:53
*******************************************************************************************************/

#if !defined(AFX_PROCESS_H__DD61E983_80C3_4DF7_99AA_D97205CD824B__INCLUDED_)
#define AFX_PROCESS_H__DD61E983_80C3_4DF7_99AA_D97205CD824B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\..\库\database\ado\ado.h"
#include "..\..\command\command.h"

class CProcess  
{
private:
    CAdoRecordSet m_AdoRecSet;  //记录集
    CAdoConnection* m_pAdoConn; //连接
    LPVOID m_lpData;            //指向接收的数据的指针
    int m_iDataLen;             //接收的数据的大小
    CCommand* m_pCmd;           //命令
    CUDPSocket* m_sckCommand;   //Socket

    typedef enum{
        tabInfo = 0,
        tabUserInfo = 1,
        tabChair = 2
    } ENUM_TABLE;

    //向所有已登录的用户发送新登录用户的信息
    void SendLogonUserInfoToAllLogonedUser(LPCTSTR szUserName, BOOL bUser = FALSE);
    //向新登录用户发送所有已登录用户的信息
    void SendAllLogonedUserInfo();
    //发送椅子信息
	void SendChairInfo(BOOL bAll = FALSE);

    //向客户端发送数据
    BOOL SendData(LPVOID lpBuf, INT iLen);  
    BOOL SendData(CCommand& cmd);
   	BOOL SendData(CCommand* pcmd);

    //向指的用户发送数据
    BOOL SendData(LPCTSTR lpszUserName, LPVOID lpData, int iLen);
	BOOL SendData(LPCTSTR lpszUserName, CCommand& cmd);
    //向所有已登录的用户发送数据
    BOOL SendDataToAllUser(LPVOID lpData, int iLen, LPCTSTR lpszSendUserName = NULL);
    BOOL SendDataToAllUser(CCommand &cmd, LPCTSTR lpszSendUserName = NULL);
    
    //得到当前用户信息
    BOOL GetUserInfo(CCommand* pCmd);
    //得到指定的椅子信息
    BOOL GetChairInfo(int iChairNo, CCommand* pCmd);

    //更新数据库
    BOOL Update(LPCTSTR  lpUpdate, LPCTSTR lpCondition, ENUM_TABLE eTable = tabUserInfo);
    //查找数据
	BOOL Search(LPCTSTR lpszFields, LPCTSTR lpszCondition, ENUM_TABLE eTable = tabUserInfo);

public:
    //处理命令
    //处理求和命令
    void StandOff(void);
    void Start();            //同意开始下棋
	void LeaveChair();       //离开椅子
	void SetDown();          //入坐
	void SendTextMessage();  //转发发送消息
	void Regist();           //注册
	void Logon();            //登录命令
    void Giveup();           //认输
    void Exit();             //退出
    void VideoConn();        //视频连接请求
    void AudioConn();        //音频连接请求
    void AgreeVideoConn();   //同意视频连接
    void AgreeAudioConn();   //同意音频连接
    void NoAgreeVideo();     //不同意视频连接
    void NoAgreeAudio();     //不同间音频连接

	void SetConnection(CAdoConnection* pconn);
    void SetCommand(CCommand* pCmd);
	void SetSocket(CUDPSocket* pSock);

	CString m_szIP;          //客户端的IP
    UINT m_uPort;            //客户端的Port

	CProcess();
	virtual ~CProcess();   
};

#endif // !defined(AFX_PROCESS_H__DD61E983_80C3_4DF7_99AA_D97205CD824B__INCLUDED_)
