#pragma once
#include "manageconnect.h"

class CManageService : public CManageConnect
{
public:
	CManageService(void);
	virtual ~CManageService(void);

	//����һ������
	virtual int AddConnect(CSocket * pSocket);
};
