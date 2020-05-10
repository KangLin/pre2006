#pragma once

#include "..\TestItem.h"
#include "..\NET\SetTestSock.h"
#include < vector > 

using namespace std;

class CCheckPort :	public CTestItem
{
public:
	CCheckPort(void);
	virtual ~CCheckPort(void);
	virtual int DoTest(void);

	int Ping(CString szIP, UINT uSeq);

protected:
	CTestSocket m_Sock;
	UINT m_TimeOut;
	int m_nPingNum; //每个端品PING的次数
	int m_nIPNum;   //端口数
	vector < CString > m_szIP;

};
