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
		Network::CSocket * pSocket;  //!< ���ӵ�Socket
		CReceiveData * pReceive;     //!< �ӷ�������ָ��
		CSend * pSend;               //!< ����������ָ��
	} CONNECT, *PCONNECT;

	//����һ��Socket
	virtual int AddClient(Network::CSocket * pSock);
	//ɾ��һ��Socket
	virtual int RemoveClient(Network::CSocket * pSock);
	virtual int CheckTimeouts();
	//����Socket���¼�
	virtual bool ProcessReadEvent(Network::CSocket * pSock);
	//����Socketд�¼�
	virtual bool ProcessWriteEvent(Network::CSocket * pSock);
	
	//�������������
	virtual int ProcessCommand(CCommand & cmd, PCONNECT pConnect = NULL);
	//��������
	virtual int Send(Network::CSocket * pSock, CCommand * pCmd);

protected:
	list<PCONNECT> m_Connect;
};

#endif //__MANAGESERVER_H_KL_2007_08_21__