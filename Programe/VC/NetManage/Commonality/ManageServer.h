#ifndef __MANAGESERVER_H_KL_2007_08_21__
#define __MANAGESERVER_H_KL_2007_08_21__

#pragma once

#include "..\..\System\Communicate\socket.h"
#include "..\Commonality\data.h"

class CManageServer : public Network::CSocketServer
{
public:
	CManageServer(void);
	virtual ~CManageServer(void);

	typedef struct _CONNECT
	{
		Network::CSocket * pSocket;  //!< 连接的Socket
		CReceiveData * pReceive;     //!< 接发数据类指针
		CSend * pSend;               //!< 发送数据类指针
	} CONNECT, *PCONNECT;

	//增加一个Socket
	virtual int AddClient(Network::CSocket * pSock);
	//删除一个Socket
	virtual int RemoveClient(Network::CSocket * pSock);
	virtual int CheckTimeouts();
	//处理Socket读事件
	virtual bool ProcessReadEvent(Network::CSocket * pSock);
	//处理Socket写事件
	virtual bool ProcessWriteEvent(Network::CSocket * pSock);
	
	//处理解包后的命令
	virtual int ProcessCommand(CCommand & cmd, PCONNECT pConnect = NULL);
	//发送命令
	virtual int Send(Network::CSocket * pSock, CCommand * pCmd);

protected:
	list<PCONNECT> m_Connect;
};

#endif //__MANAGESERVER_H_KL_2007_08_21__