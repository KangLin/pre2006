
#include "..\stdafx.h"

#pragma once


// CTestSocket ÃüÁîÄ¿±ê

class CTestSocket : public CSocket
{
public:
	CTestSocket();
	virtual ~CTestSocket();

	BOOL SetTimeOut(UINT uTimeOut);

private:
	int m_nTimerID;
public:
	BOOL KillTimeOut(void);
	virtual BOOL OnMessagePending();
};


