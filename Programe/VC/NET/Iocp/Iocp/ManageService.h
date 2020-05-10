#pragma once
#include "manageconnect.h"

class CManageService : public CManageConnect
{
public:
	CManageService(void);
	virtual ~CManageService(void);

	//增加一个连接
	virtual int AddConnect(CSocket * pSocket);
};
