#pragma once
#include "connect.h"

class CService : public CConnect
{
public:
	CService(CSocket * pSocket);
	virtual ~CService(void);

	//������յ����������ݰ�
	virtual int OnRecv(void * pBuf, int * pnLen);
	//�������ݰ�
	virtual int OnSend(void * pBuf, int nLen);
};
