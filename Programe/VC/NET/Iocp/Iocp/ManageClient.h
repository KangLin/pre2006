#pragma once
#include "manageconnect.h"

class CManageClient : public CManageConnect
{
public:
	CManageClient(void);
	virtual ~CManageClient(void);

	//����һ������
	virtual int AddConnect(CSocket * pSocket);
};
