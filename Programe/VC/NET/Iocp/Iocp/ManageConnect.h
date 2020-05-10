#pragma once
#include "manage.h"
#include "Connect.h"
#include "Sock.h"
#include <vector>
using namespace std;

class CManageConnect : public CManage
{
public:
	CManageConnect(void);
	virtual ~CManageConnect(void);

	//增加一个连接
	virtual int AddConnect(CSocket * pSocket);
	//删除指定的连接
	virtual int RemoveConnect(CSocket * pSocket);
	//清除所有连接
	virtual int ClearConnect();

	virtual int Initalize();

	//得到当前连接数
	virtual LONG GetConnectNumber();
	//得到总的连接数
	virtual LONG GetTotalConnectNumber();

protected:
	LONG m_ConnectNumber;       //当前连接数
	LONG m_TotalConnectNumber;  //总连接数

	vector < CConnect * > m_Connect;
	CRITICAL_SECTION m_csConnect;

	int Lock();
	int UnLock();

	static DWORD WorkThread(void * pPara);
};
