#pragma once


#include "..\..\..\NetManage\Commonality\ManageServer.h"

class CTestClientServer : public CManageServer
{
public:
	CTestClientServer(void);
	~CTestClientServer(void);

	virtual int AddClient(Network::CSocket * pSock);

	//��������������������Ҫ���ش˺�����������ض�����
	virtual int ProcessCommand(CCommand & cmd, PCONNECT pConnect = NULL);

	virtual bool ProcessWriteEvent(Network::CSocket * pSock);
private:
	Network::CSocket* m_pSocket;
};
