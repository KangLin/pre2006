#pragma once
#include "manageConnect.h"
#include <vector>
using namespace std;

class CManageIOCPConnect : public CManageConnect
{
public:
	CManageIOCPConnect(void);
	virtual	~CManageIOCPConnect(void);

	//增加一个连接
	virtual int AddConnect(CSocket * pSocket);
	//删除指定的连接
	//virtual int RemoveConnect(CSocket * pSocket);
	//清除所有连接
	//virtual int ClearConnect();
	virtual int Initalize();

	//设置每个处理器上完成端口的线程个数。如果要调用，必须在 Initalize 前调用
	int SetThreadNumber(int nNum = 1);
	int GetThreadNumber();

	BOOL * m_pExit;

private:
	static DWORD CompleteIOWorkThread(void * pPara);

	HANDLE m_hCompletion; //完成端口句柄
	vector < HANDLE > m_hThread;
	int m_nThread;

};
