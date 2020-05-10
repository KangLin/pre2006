#pragma once
#include "Sock.h"
#include "RecvData.h"
#include "SendData.h"
#include "Sock.h"

class CConnect
{
public:
	CConnect(CSocket * pSocket);
	virtual ~CConnect(void);

	//处理IO事件
	virtual int OnHandleIOEvent(void * pPara = NULL);
	//处理接收事件
	virtual int OnProcessRecvEvent();
	//处理发送事件
	virtual int OnProcessWriteEvent();

	//处理接收到的完整数据包，用户要继承并实现这个函数
	virtual int OnRecv(void * pBuf, int nLen);
	//发送数据包，用户要继承并实现这个函数
	virtual int OnSend(void * pBuf, int nLen);

	CSocket * m_pSocket;        //SOCK指针

protected:
	CRecvData * m_pRecvData;    //接收的数据
	CSendData * m_pSendData;    //发送的数据
};
