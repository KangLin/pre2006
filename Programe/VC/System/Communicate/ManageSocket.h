/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    ManageSocket.h
\brief   Socket 管理类，用于管理 Socket
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年7月5日  11:01:49
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#pragma once

#include ".\socket.h"
#include <vector>
#include <list>
using namespace std;

class CManageSocket
{
public:
	CManageSocket(void);
	virtual ~CManageSocket(void);

	int AddLister(Network::CSocketListener * sock, Network::CSocketServer * server);
	int RemoveLister(Network::CSocketListener * sock);
	int AddConncet(Network::CSocket * sock, Network::CSocketServer * server);
	int RemoveConnect(Network::CSocket * sock);

	int OnRun();

private:
	//Socket 信息结构
	typedef struct _SOCKETINFO
	{
		union
		{
			Network::CSocket          * Connect;   //工作 Socket
			Network::CSocketListener  * Listener;  //监听 Socket
		} Sock;
		bool IsLister;                             //决定上面的联合体是用哪个成员。
												   //TRUE，是监听 Socket，否则为工作 Socket

		HANDLE hEvent;                             //事件对象
		Network::CSocketServer        * Service;   //与Socket相关的服务
	}SOCKETINFO, *PSOCKETINFO;

	//线程信息结构
	typedef struct _THREADINFO
	{
		//hEvents[0] 为线程退出信号事件，WSAEventSelect 信号从 hEvents[1] 开始
		HANDLE hEvents[WSA_MAXIMUM_WAIT_EVENTS];  //记录当前线程要等待的事件对象的句柄
		//int nSocketCount;                         // 记录当前线程处理的套节字的数量 <=  WSA_MAXIMUM_WAIT_EVENTS
		vector < PSOCKETINFO > socket;            //本线程处理的 Socket
		CRITICAL_SECTION cs;                      //关键代码段变量，为的是同步对本结构的访问
		BOOL* pbExit;
	}THREADINFO, *PTHREADINFO;

	//线程池结构
	typedef struct _THREADPOLLINFO
	{
		BOOL bIsLister;
		list < PTHREADINFO > m_Thread;            //监听线程池
		CRITICAL_SECTION cs;                      //关键代码段变量，为的是同步对本结构的访问
	}THREADPOLLINFO, *PTHREADPOLLINFO;

	//传递给处理线程(ProcessThread)的参数结构
	typedef struct _PARAMETER
	{
		CManageSocket * pManageSocket;
		PTHREADINFO pThread;
		HANDLE* phEvent;
		PTHREADPOLLINFO pPool;
	}PARAMETER, *PPARAMETER;

	//处理 Socket
	int AddSocketObj(PTHREADINFO pThread, PSOCKETINFO pSocket);
	int RemoveSocketObj(PTHREADINFO pThread, PSOCKETINFO pSocket);
	int FreeSocketObj(PSOCKETINFO pSocket);
	int RebuildArray(PTHREADINFO pThread);

	//处理线程
	int FreeThreadObj(PTHREADINFO pThread);
	PTHREADINFO AddThread(PTHREADPOLLINFO pPool);
	int RemoveThread(PTHREADPOLLINFO pPool, PTHREADINFO pThread);

	//处理线程池
	int AddSocketObj(PTHREADPOLLINFO pPool, PSOCKETINFO pSocket);
	int FreePool(PTHREADPOLLINFO pPool);

	int HandleIO(PTHREADINFO pThread, PSOCKETINFO pSocket);
	static DWORD ProcessThread(LPVOID lpPara);

private:
	THREADPOLLINFO m_ListerThreadPool;            //监听线程池
	THREADPOLLINFO m_IOThreadPool;                //IO处理线程池

	HANDLE m_hOnRunExit;                          //OnRun 函数退出事件
	int m_dwOnRunDelay;

	///////////////////////////////////////////////////////////////////////////////////////////////
	//                                    计数器
	///////////////////////////////////////////////////////////////////////////////////////////////
	LONG m_TotalListerThreadNumber;               //监听线程总个数
	LONG m_CurrentListerThreadNumber;             //当前监听线程个数
	LONG m_TotalIOThreadNumber;                   //IO处理线程总个数
	LONG m_CurrentIOThreadNumber;                 //当前IO处理线程个数

	LONG m_TotalConnectNumber;                    //总共连接的次数
	LONG m_CurrentConnectNumber;                  //当前连接的个数
	LONG m_CurrentListerNumber;                   //当前监听数
	LONG m_TotalListerNumber;


	///////////////////////////////////////////////////////////////////////////////////////////////
	//                                 Lister 处理线程
	///////////////////////////////////////////////////////////////////////////////////////////////
	typedef struct _LISTERINFO
	{
		PTHREADINFO pThread;
		PSOCKETINFO pSocket;
		Network::CSocket * Connect;
	}LISTERINFO, *PLISTERINFO;
	list < PLISTERINFO > m_lstLister;
	CRITICAL_SECTION m_csLister;                  //关键代码段变量，为的是同步m_lstLister的访问
	HANDLE m_hLister;                             //通知 ProcessListerThread 有新加入项
	BOOL * m_pbExitListerThread;                  //指示类已析构

	int AddLister(PLISTERINFO lpListerInfo);      //在m_lstLister中加入一新项
	PLISTERINFO GetLister();                      //得到m_lstLister队列中的最前一项，并把它从列中删除。

	//处理新增加的 lister Socket
	static DWORD ProcessListerThread(LPVOID lpPara);

};
