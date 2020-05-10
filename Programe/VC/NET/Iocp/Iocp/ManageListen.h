#pragma once
#include "manage.h"
#include "ListenSock.h"
#include "ManageNet.h"
#include <vector>
using namespace std;

#define MAX_Listen_NUMBER 64      //监听SOCKET最大数

class CManageNet;
class CManageListen : public CManage
{
public:
	CManageListen(CManageNet * pMngNet);
	virtual ~CManageListen(void);

	virtual int Initalize();

	//增加监听
	virtual int AddListen(int nPort);
	//删除监听
	virtual int RemoveListen(int nFD);
	//清除所有监听
	virtual int ClearListen();

	//得到当前监听数
	virtual LONG GetListenNumber();
	//得到总的监听数
	virtual LONG GetTotalListenNumber();

	//处理IO
	virtual int HandleIO(int nPos);

	//事件数据
	HANDLE m_hEvent[MAX_Listen_NUMBER];
	//重整事件数组
	int RebuildArray();

protected:
	vector<CListenSocket *> m_Listen;

	CManageNet * m_ManageNet;
	HANDLE m_hThreadListen;       //监听线程句柄
	LONG m_nLiseterNumber;        //监听数
	LONG m_nTotalNumber;          //监听总数

	CRITICAL_SECTION m_csListen;  //访问m_Listen监界量
	int Lock();
	int UnLock();

	static DWORD ListenWorkThread(void * pPara);
};
