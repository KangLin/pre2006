#pragma once
#include "manageconnect.h"

class CManageClient : public CManageConnect
{
public:
	CManageClient(void);
	virtual ~CManageClient(void);

	//增加一个连接
	virtual int AddConnect(CSocket * pSocket);
};
