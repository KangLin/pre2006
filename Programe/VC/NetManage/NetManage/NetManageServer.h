#pragma once

#include ".\Dll.h"
#include "..\Commonality\ManageServer.h"

class CNetManageServer : public CManageServer
{
public:
	CNetManageServer(void);
	~CNetManageServer(void);
	
	int SetDLL(CDll * pDll);

	//�������������
	virtual int ProcessCommand(CCommand & cmd, PCONNECT pConnect = NULL);

private:
	CDll* m_pDll;

};
