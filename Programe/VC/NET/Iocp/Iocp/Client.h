#pragma once
#include "connect.h"

class CClient :	public CConnect
{
public:
	CClient(CSocket * pSocket);
	virtual ~CClient(void);

	//处理接收到的完整数据包
	virtual int OnRecv(void * pBuf, int * pnLen);
	//发送数据包
	virtual int OnSend(void * pBuf, int nLen);
};
