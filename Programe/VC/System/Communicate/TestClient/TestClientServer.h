#pragma once


#include "..\..\..\NetManage\Commonality\ManageServer.h"

class CTestClientServer : public CManageServer
{
public:
	CTestClientServer(void);
	~CTestClientServer(void);

	virtual int AddClient(Network::CSocket * pSock);

	//处理解包后的命令，其派生类要重载此函数，以完成特定功能
	virtual int ProcessCommand(CCommand & cmd, PCONNECT pConnect = NULL);

	virtual bool ProcessWriteEvent(Network::CSocket * pSock);
private:
	Network::CSocket* m_pSocket;
};
