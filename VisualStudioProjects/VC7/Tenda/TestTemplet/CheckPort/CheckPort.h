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
	int m_nPingNum; //ÿ����ƷPING�Ĵ���
	int m_nIPNum;   //�˿���
	vector < CString > m_szIP;

};
