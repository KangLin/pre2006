#pragma once

#include "testitem.h"
#include "SetTestSock.h"
#include < vector > 

using namespace std;

class CCheckPort :	public CTestItem
{
public:
	CCheckPort(void);
	virtual ~CCheckPort(void);
	virtual int DoTest(void);

	int Ping(CString szIP, UINT uSeq);

private:
	CTestSocket m_Sock;
	UINT m_TimeOut;
	int m_nPingNum;
	int m_nIPNum;
	vector < CString > m_szIP;
};
