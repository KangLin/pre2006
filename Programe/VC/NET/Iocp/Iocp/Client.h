#pragma once
#include "connect.h"

class CClient :	public CConnect
{
public:
	CClient(CSocket * pSocket);
	virtual ~CClient(void);

	//������յ����������ݰ�
	virtual int OnRecv(void * pBuf, int * pnLen);
	//�������ݰ�
	virtual int OnSend(void * pBuf, int nLen);
};
