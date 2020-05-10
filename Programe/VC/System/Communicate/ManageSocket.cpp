/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    ManageSocket.cpp
\brief   Socket 管理类，用于管理 Socket
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年7月11日  17:26:20
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/
#include "StdAfx.h"
#include "ManageSocket.h"
#pragma comment(lib, "Ws2_32.lib")


CManageSocket::CManageSocket(void)
{
	m_ListerThreadPool.bIsLister = TRUE;
	m_IOThreadPool.bIsLister = FALSE;
	InitializeCriticalSection(&m_ListerThreadPool.cs);
	InitializeCriticalSection(&m_IOThreadPool.cs);

	m_TotalListerThreadNumber    = 0;
	m_CurrentListerThreadNumber  = 0;
	m_TotalIOThreadNumber        = 0;
	m_CurrentIOThreadNumber      = 0;

	m_CurrentConnectNumber       = 0;
	m_TotalConnectNumber         = 0;
	m_CurrentListerNumber        = 0;
	m_TotalListerNumber          = 0;

	m_dwOnRunDelay               = 1000;
	m_hOnRunExit = CreateEvent(NULL, FALSE, FALSE, NULL);
	if(NULL == m_hOnRunExit)
	{
		TRACE(_T("CreateEvent error\n"));
	} // 结束 if(NULL == m_hOnRunExit)


	//初始化处理 Lister 线程相关变量
	m_pbExitListerThread = NULL;
	InitializeCriticalSection(&m_csLister);
	m_hLister = CreateEvent(NULL, FALSE, FALSE, NULL);
	if(NULL == m_hLister)
	{
		TRACE(_T("CreateEvent error\n"));
	}// 结束 if(NULL == m_hLister)

}

CManageSocket::~CManageSocket(void)
{
	TRACE(_T("~CManageSocket.\n"));
	//退出 OnRun
	SetEvent(m_hOnRunExit);


	//退出 Lister 队列处理线程
	if(m_pbExitListerThread)
	{
		*m_pbExitListerThread = TRUE;
	}// 结束 if(m_pbExitListerThread)
	CloseHandle(m_hLister);
	m_hLister = NULL;

	FreePool(&m_ListerThreadPool);
	FreePool(&m_IOThreadPool);

	DeleteCriticalSection(&m_csLister);

}

int CManageSocket::AddConncet(Network::CSocket * sock, Network::CSocketServer * server)
{
	PSOCKETINFO pSocket = new SOCKETINFO;
	if(NULL == pSocket)
	{
		return S_FALSE;
	}// 结束 if(NULL == pSocket)
	memset(pSocket, 0, sizeof(SOCKETINFO));
	//建立事件
	pSocket->hEvent = WSACreateEvent();
	ASSERT(pSocket->hEvent != WSA_INVALID_EVENT);
	if(WSA_INVALID_EVENT == pSocket->hEvent)
	{
		delete pSocket;
		return S_FALSE;
	} // 结束 if(WSA_INVALID_EVENT == pSocket->hEvent)
	if(WSAEventSelect(sock->GetFd(), pSocket->hEvent, FD_READ | FD_WRITE | FD_CLOSE) == SOCKET_ERROR)
	{
		CloseHandle(pSocket->hEvent);
		delete pSocket;
		return S_FALSE;
	}
	pSocket->Sock.Connect  = sock;
	pSocket->IsLister      = FALSE;
	pSocket->Service       = server;

	::InterlockedIncrement(&m_CurrentConnectNumber);
	::InterlockedIncrement(&m_TotalConnectNumber);

	if(server)
	{
		server->AddClient(sock);
	}// 结束 if(server)

	//加入到线程池中
	return AddSocketObj(&m_IOThreadPool, pSocket);
}

int CManageSocket::RemoveConnect(Network::CSocket * sock)
{
	int nRet = S_FALSE;
	list<PTHREADINFO>::iterator it;
	::EnterCriticalSection(&m_IOThreadPool.cs);
	for(it = m_IOThreadPool.m_Thread.begin(); it != m_IOThreadPool.m_Thread.end(); it++)
	{
		PTHREADINFO pThread = *it;
		vector<PSOCKETINFO>::iterator itSock;
		::EnterCriticalSection(&pThread->cs);
		for(itSock = pThread->socket.begin(); itSock != pThread->socket.end(); itSock++)
		{
			PSOCKETINFO pSocket = *itSock;
			if(pSocket->Sock.Connect == sock && !pSocket->IsLister)
			{
				//注意，位置不能变，否则会发生死锁
				::LeaveCriticalSection(&pThread->cs);
				nRet = RemoveSocketObj(*it, pSocket);
				::LeaveCriticalSection(&m_IOThreadPool.cs);
				return nRet;
			} // 结束 if(pSocket->Sock.Connect == sock && !pSocket->IsLister)
		}// 结束 for(itSock = pThread->socket.begin(); itSock != pThread->socket.end(); itSock++)
		::LeaveCriticalSection(&pThread->cs);
	}// 结束 for(it = m_IOThreadPool.m_Thread.begin(); it != m_IOThreadPool.m_Thread.end(); it++)
	::LeaveCriticalSection(&m_IOThreadPool.cs);

	//如果线程池中没有此 Socket ，则删除它
	delete sock;
	return nRet;
}

int CManageSocket::AddLister(Network::CSocketListener * sock, Network::CSocketServer * server)
{
	static bool bCreateListerThread = FALSE;

	PSOCKETINFO pSocket = new SOCKETINFO;
	if(NULL == pSocket)
	{
		return S_FALSE;
	}// 结束 if(NULL == pSocket)

	if(!bCreateListerThread)
	{
		//建立连接处理线程
		DWORD dwID;
		HANDLE hThreadLister = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ProcessListerThread, this, NULL, &dwID);
		if(NULL == hThreadLister)
		{
			TRACE(_T("CreateThread error\n")); 
		}
		else
		{
			CloseHandle(hThreadLister);
		}// 结束 (NULL, NULL, (LPTHREAD_START_ROUTINE)ProcessListerThread, this, NULL, &dwID)
		bCreateListerThread = TRUE;
	} // 结束 if(!bCreateListerThread)

	memset(pSocket, 0, sizeof(SOCKETINFO));
	//建立事件
	pSocket->hEvent = WSACreateEvent();
	ASSERT(pSocket->hEvent != WSA_INVALID_EVENT);
	if(WSA_INVALID_EVENT == pSocket->hEvent)
	{
		delete pSocket;
		return S_FALSE;
	} // 结束 if(WSA_INVALID_EVENT == pSocket->hEvent)
	if(WSAEventSelect(sock->GetFd(), pSocket->hEvent, FD_ACCEPT | FD_CLOSE) == SOCKET_ERROR)
	{
		CloseHandle(pSocket->hEvent);
		delete pSocket;
		return S_FALSE;
	}
	pSocket->Sock.Listener  = sock;
	pSocket->IsLister       = TRUE;
	pSocket->Service        = server;

	::InterlockedIncrement(&m_CurrentListerNumber);
	::InterlockedIncrement(&m_TotalListerNumber);

	//加入到线程池中
	return AddSocketObj(&m_ListerThreadPool, pSocket);
}

int CManageSocket::RemoveLister(Network::CSocketListener * sock)
{
	int nRet = S_FALSE;
	list<PTHREADINFO>::iterator it;
	::EnterCriticalSection(&m_ListerThreadPool.cs);
	for(it = m_ListerThreadPool.m_Thread.begin(); it != m_ListerThreadPool.m_Thread.end(); it++)
	{
		PTHREADINFO pThread = *it;
		vector<PSOCKETINFO>::iterator itSock;
		::EnterCriticalSection(&pThread->cs);
		for(itSock = pThread->socket.begin(); itSock != pThread->socket.end(); itSock++)
		{
			PSOCKETINFO pSocket = *itSock;
			if(pSocket->Sock.Listener == sock && pSocket->IsLister)
			{
				//注意，位置不能变，否则会发生死锁
				::LeaveCriticalSection(&pThread->cs);
				nRet = RemoveSocketObj(*it, pSocket);
				::LeaveCriticalSection(&m_ListerThreadPool.cs);
				return nRet;
			} // 结束 if(pSocket->Sock.Listener == sock && pSocket->IsLister)
		}// 结束 for(itSock = pThread->socket.begin(); itSock != pThread->socket.end(); itSock++)
		::LeaveCriticalSection(&pThread->cs);
	}// 结束 for(it = m_IOThreadPool.m_Thread.begin(); it != m_IOThreadPool.m_Thread.end(); it++)
	::LeaveCriticalSection(&m_ListerThreadPool.cs);

	//如果线程池中没有此 Socket ，则删除它
	delete sock;
	return nRet;
}

/*!
\brief   增加一个 PSOCKETINFO 对象到指定的线程池
\param   PTHREADPOLLINFO pPool：
\param   PSOCKETINFO pSocket  ：
\return  类型为 int 。
\version 1.0
\author  康  林
\date    2007-7-11 14:25:55
*/
int CManageSocket::AddSocketObj(PTHREADPOLLINFO pPool, PSOCKETINFO pSocket)
{
	int nRet = S_FALSE;
	list < PTHREADINFO >::iterator it;
	::EnterCriticalSection(&pPool->cs);
	for(it = pPool->m_Thread.begin(); it != pPool->m_Thread.end(); it++)
	{
		nRet = AddSocketObj(*it, pSocket);
		if(S_OK == nRet)
		{
			break;
		} // 结束 if(S_OK == nRet)
	}// 结束 for(it = pPool->m_Thread.begin(); it != pPool->m_Thread.end(); it++)
	::LeaveCriticalSection(&pPool->cs);
	if(S_FALSE == nRet)
	{
		PTHREADINFO pThread = AddThread(pPool);
		if(NULL == pThread)
		{
			nRet = S_FALSE; 
		}
		else
		{
			nRet = AddSocketObj(pThread, pSocket);
		} // 结束 if(NULL == pThread)
	} // 结束 if(S_FALSE == nRet)

	return nRet;
}

/*!
\brief   增加一个 PSOCKETINFO 对象到指定的线程
\param   PTHREADINFO pThread：
\param   PSOCKETINFO pSocket：
\return  类型为 int 。
\version 1.0
\author  康  林
\date    2007-7-11 14:28:01
*/
int CManageSocket::AddSocketObj(PTHREADINFO pThread, PSOCKETINFO pSocket)
{
	int nRet = S_OK;
	::EnterCriticalSection(&pThread->cs);
	if(pThread->socket.size() < WSA_MAXIMUM_WAIT_EVENTS - 1)
	{
#ifdef _DEBUG
		TRACE(_T("isLister:%d, hEvent=%X;pSocket Address:%p\n"), pSocket->IsLister, pSocket->hEvent, pSocket);
		if(pSocket->IsLister)
		{
			TRACE(_T("socket:%d\n"), pSocket->Sock.Listener->GetFd());
		}
		else
		{
			TRACE(_T("socket:%d\n"), pSocket->Sock.Connect->GetFd());
		}// 结束 if(pSocket->IsLister)
		TRACE(_T("Socket Number：%d\n"), pThread->socket.size());
#endif

		try
		{
			pThread->socket.push_back(pSocket);
			int nPos = pThread->socket.size();
			pThread->hEvents[nPos] = pSocket->hEvent;

			//为什么只能用事件通知调整，为什么不能象上面一样直接设置？（有时产生得不到事件通知）
			//这是因为线程正在等待前面指定个数的事件，而这个刚加的事件句柄不在这个等待数组个数内（虽然它已加到了数组中），
			//但线程等待的个数没有发生变化，所以要用下面的调整事件通知线程加入了新的事件。
			//这与释放线程中 Socket 产生相反的错误。详见：// <a href = ".\ManageSocket.cpp#在线程中删除"></a>
			//通知调整事件句柄数组
			WSASetEvent(pThread->hEvents[0]);// <a name = "在线程中插入Socket"></a>
		}
		catch(...)
		{
			nRet = S_FALSE;
		};
	}
	else
	{
		nRet = S_FALSE;
	} // 结束 if(pThread->socket.size() < WSA_MAXIMUM_WAIT_EVENTS - 1)
	::LeaveCriticalSection(&pThread->cs);
	return nRet;
}

/*!
\brief   释放 PSOCKETINFO 对象
\param   PSOCKETINFO pSocket：
\return  类型为 int 。
\version 1.0
\author  康  林
\date    2007-7-6 10:56:07
*/
int CManageSocket::FreeSocketObj(PSOCKETINFO pSocket)
{
	int nRet = S_OK;

	ASSERT(pSocket);
	try
	{
		if(pSocket->IsLister)
		{
			delete pSocket->Sock.Listener;
		}
		else
		{
			if(pSocket->Service)
			{
				//移除服务中的客户端
				pSocket->Service->RemoveClient(pSocket->Sock.Connect);
			} // 结束 if(pSocket->Service)
			
			delete pSocket->Sock.Connect;
		}// 结束 if(pSocket->IsLister)
		CloseHandle(pSocket->hEvent);
		// 是否删除服务？不用删除服务，服务由应用程序删除

		delete pSocket;
	}
	catch(...)
	{
		TRACE(_T("FreeSocketObj Error.\n"));
	}
	
	return nRet;
}

/*!
\brief   从指定线程中的 Socket 数组中移去指定的 PSOCKETINFO
\param   CManageSocket::PTHREADINFO pThread：
\param   CManageSocket::PSOCKETINFO pSocket ：
\return  类型为 int 。
\version 1.0
\author  康  林
\date    2007-7-5 19:48:59
*/
int CManageSocket::RemoveSocketObj(CManageSocket::PTHREADINFO pThread, CManageSocket::PSOCKETINFO pSocket)
{
	int nRet = S_OK;

	ASSERT(pThread && pSocket);

	vector<PSOCKETINFO>::iterator it;
	::EnterCriticalSection(&pThread->cs);
	for(it = pThread->socket.begin(); it != pThread->socket.end(); it++)
	{
		PSOCKETINFO p = *it;
		if(p == pSocket)
		{
			pThread->socket.erase(it);
			break;
		} // 结束 if((*it) == pSocket)
	}// 结束 for(it = pThread->socket.begin(); it != pThread->socket.end(); it++)
	::LeaveCriticalSection(&pThread->cs);

	//必须调整事件对象数组，用::WSASetEvent(pThread->hEvents[0])会在同一线程内产生无效句柄的错误
	//如果用事件通知调整，则会产生有无效的句柄错误。这与把 Socket 加入到线程内产生相反的错误:)
	//详见：// <a href = ".\ManageSocket.cpp#在线程中插入Socket"></a>
	RebuildArray(pThread);// <a name = "在线程中删除"></a>

	//通知调整事件句柄数组
	::WSASetEvent(pThread->hEvents[0]);

	// 说明一个连接中断
	if(pSocket->IsLister)
	{
		::InterlockedDecrement(&m_CurrentListerNumber);
	}
	else
	{
		::InterlockedDecrement(&m_CurrentConnectNumber);
	}// 结束 if(pSocket->IsLister)

	nRet = FreeSocketObj(pSocket);

	return nRet;
}

/*!
\brief   重新建立线程对象的 hEvents 数组，因为可能这个线程内的一个 Socket 被删除了，所以要移动所有 hEvents
\param   PTHREADINFO pThread：处理的线程结构对象
\return  类型为 int 。
\version 1.0
\author  康  林
\date    2007-7-5 16:54:16
*/
int CManageSocket::RebuildArray(PTHREADINFO pThread)
{
	int i = 0;

	ASSERT(pThread);

	::EnterCriticalSection(&pThread->cs);
	// 从第1个开始写，第0个用于指示需要重建了
	for(i = 0; i < pThread->socket.size(); i++)
	{
		pThread->hEvents[i + 1] = pThread->socket[i]->hEvent;
	}// 结束 for(i = 0; i < pThread->socket.size(); i++)
	::LeaveCriticalSection(&pThread->cs);

	//重置重建数组事件对象
	if(::WSAResetEvent(pThread->hEvents[0]))
	{
		return S_OK;
	} // 结束 if(::WSAResetEvent(pThread->hEvents[0]))
	return S_FALSE;
}

/*!
\brief   释放 PTHREADINFO
\param   PTHREADINFO pThread：
\return  类型为 int 。
\version 1.0
\author  康  林
\date    2007-7-6 11:01:38
*/
int CManageSocket::FreeThreadObj(PTHREADINFO pThread)
{
	ASSERT(pThread);

	TRACE(_T("Free Thread:%p\n"), pThread);

	//释放 PSOCKETINFO
	vector<PSOCKETINFO>::iterator it;
	::EnterCriticalSection(&pThread->cs);
	for(it = pThread->socket.begin(); it != pThread->socket.end(); it++)
	{
		FreeSocketObj(*it);
	}// 结束 for(it = pThread->socket.begin(); it != pThread->socket.end(); it++)
	pThread->socket.clear();
	::LeaveCriticalSection(&pThread->cs);

	//释放访问 Socket 队列的关键代码段变量
	::DeleteCriticalSection(&pThread->cs);
	//释放hEvent[0]事件对象
	::CloseHandle(pThread->hEvents[0]);
	if(pThread->pbExit)
	{
		*(pThread->pbExit) = TRUE;
	} // 结束 if(pThread->pbExit)
	
	delete pThread;
	return S_OK;
}

/*!
\brief   在一个线程池中增加一个新的线程
\param   CManageSocket::PTHREADPOLLINFO pPool：指定的线程池
\return  类型为 CManageSocket::PTHREADINFO 。新增加的线程对象指针，如果不成功返回 NULL
\version 1.0
\author  康  林
\date    2007-7-9 11:05:19
*/
CManageSocket::PTHREADINFO CManageSocket::AddThread(CManageSocket::PTHREADPOLLINFO pPool)
{
	int nRet = S_OK;
	//新建线程结构
	PTHREADINFO pThread = new THREADINFO;
	if(NULL == pThread)
	{
		return NULL;
	}// 结束 if(NULL == pThread)

	memset(pThread, 0, sizeof(THREADINFO));
	//初始化临界段
	InitializeCriticalSection(&pThread->cs);
	//初始 hEvent[0] 事件对象
	pThread->hEvents[0] = WSACreateEvent(); // CreateEvent(NULL, TRUE, FALSE, NULL);

	//启动新线程
	PARAMETER Para;
	DWORD dwID;
	HANDLE hEvent;
	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if(NULL == hEvent)
	{
		delete pThread;
		return NULL;
	}// 结束 if(NULL == hEvent)
	Para.pManageSocket = this;
	Para.pPool = pPool;
	Para.pThread = pThread;
	Para.phEvent = &hEvent;
	HANDLE hThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ProcessThread, &Para, NULL, &dwID);
	if(hThread)
	{
		if(WAIT_OBJECT_0 == ::WaitForSingleObject(hEvent, INFINITE))
		{
			TRACE(_T("Add new thread to thread pool.\n"));
			//把新线程对象加入到线程池
			::EnterCriticalSection(&pPool->cs);
			try
			{
				pPool->m_Thread.push_back(pThread);
				::LeaveCriticalSection(&pPool->cs);
				//计数
				if(pPool->bIsLister)
				{
					::InterlockedIncrement(&m_TotalListerThreadNumber);
					::InterlockedIncrement(&m_CurrentListerThreadNumber);
				}
				else
				{
					::InterlockedIncrement(&m_TotalIOThreadNumber);
					::InterlockedIncrement(&m_CurrentIOThreadNumber);
				} // 结束 if(pPool->bIsLister)

				return pThread;
			}
			catch(...)
			{
				::LeaveCriticalSection(&pPool->cs);
			}
		} // 结束 if(WAIT_OBJECT_0 == ::WaitForSingleObject(hEvent, INFINITE))
	} // 结束 if(hThread)

	//出错处理：
	//释放资源
	CloseHandle(hEvent);
	if(NULL != hThread)
	{
		CloseHandle(hThread);
	} // 结束 if(NULL != hThread)
	delete pThread;
	return NULL;
}

/*!
\brief   从线程池中移除指定的线程对象(PTHREADINFO)
\param   PTHREADPOLLINFO pPool：线程池
\param   PTHREADINFO pThread ：线程对象
\return  类型为 int 。
\version 1.0
\author  康  林
\date    2007-7-6 10:52:00
*/
int CManageSocket::RemoveThread(PTHREADPOLLINFO pPool, PTHREADINFO pThread)
{
	int nRet = S_OK;
	list < PTHREADINFO > ::iterator it;

	ASSERT(pPool && pThread);

	::EnterCriticalSection(&pPool->cs);
	for(it = pPool->m_Thread.begin(); it != pPool->m_Thread.end(); it++)
	{
		if(*it == pThread)
		{
			//释放线程对象
			FreeThreadObj(pThread);
			//从列表中删除它
			pPool->m_Thread.erase(it);
			//计数
			if(pPool->bIsLister)
			{
				::InterlockedDecrement(&m_CurrentListerThreadNumber);
			}
			else
			{
				::InterlockedDecrement(&m_CurrentIOThreadNumber);
			} // 结束 if(pPool->bIsLister)
			//离开临界区
			::LeaveCriticalSection(&pPool->cs);
			return S_OK;
		} // 结束 if(*it == pThread)
	}// 结束 for(it = pPool->m_Thread.begin(); it != pPool->m_Thread.end(); it++)
	::LeaveCriticalSection(&pPool->cs);

	//释放线程对象
	FreeThreadObj(pThread);
	
	return nRet;
}

/*!
\brief   释放线程池
\param   PTHREADPOLLINFO pPool：
\return  类型为 int 。
\version 1.0
\author  康  林
\date    2007-7-12 17:13:38
*/
int CManageSocket::FreePool(PTHREADPOLLINFO pPool)
{
	int nRet = S_OK;
	int nSize = 0;
	::EnterCriticalSection(&pPool->cs);
	nSize = pPool->m_Thread.size();
	::LeaveCriticalSection(&pPool->cs);
	while(nSize > 0)
	{
		::EnterCriticalSection(&pPool->cs);
		PTHREADINFO pThread = pPool->m_Thread.front();
		//pPool->m_Thread.pop_front();
		::LeaveCriticalSection(&pPool->cs);

		RemoveThread(pPool, pThread);

		//vector<PSOCKETINFO>::iterator itSock;
		//::EnterCriticalSection(&pThread->cs);
		//for(itSock = pThread->socket.begin(); itSock != pThread->socket.end(); itSock++)
		//{
		//	nRet = FreeSocketObj(*itSock);
		//}// 结束 for(itSock = pThread->socket.begin(); itSock != pThread->socket.end(); itSock++)
		//pThread->socket.clear();
		//::LeaveCriticalSection(&pThread->cs);
		//RebuildArray(pThread);
		////发出释放线程通知，线程删除自己
		//::WSASetEvent(pThread->hEvents[0]);

		::EnterCriticalSection(&pPool->cs);
		nSize = pPool->m_Thread.size();
		::LeaveCriticalSection(&pPool->cs);
	}// 结束 while(nSize > 0)
	DeleteCriticalSection(&pPool->cs);
	return nRet;
}

/*!
\brief   处理 Socket IO 事件
\param   PTHREADINFO pThread：
\param   PSOCKETINFO pSocket：
\return  类型为 int 。
\version 1.0
\author  康  林
\date    2007-7-12 13:49:58
*/
int CManageSocket::HandleIO(PTHREADINFO pThread, PSOCKETINFO pSocket)
{
	// 获取具体发生的网络事件
	WSANETWORKEVENTS hEvent;
	SOCKET s;

	do
	{
		if(pSocket->IsLister)
		{
			s = pSocket->Sock.Listener->GetFd();
		}
		else
		{
			s = pSocket->Sock.Connect->GetFd();
		} // 结束 ()
		if(SOCKET_ERROR == ::WSAEnumNetworkEvents(s, pSocket->hEvent, &hEvent))
		{
			TRACE(_T("WSAEnumNetworkEvents error:%d\n"), WSAGetLastError());
			break;
		}// 结束 if(SOCKET_ERROR == ::WSAEnumNetworkEvents(s, pSocket->hEvent, &hEvent))

		TRACE(_T("HandleIO:%d\n"), hEvent.lNetworkEvents);

		if(hEvent.lNetworkEvents & FD_ACCEPT)//接受连接
		{
			if(hEvent.iErrorCode[FD_ACCEPT_BIT] == 0)
			{
				TRACE(_T("接受连接\n"));
				if(!pSocket->IsLister)
				{
					ASSERT(0);
					//出错
					break;
				}
				else
				{
					try
					{
						Network::CSocket * newSocket = pSocket->Sock.Listener->Accept();
						if(newSocket)
						{
							PLISTERINFO pLister = new LISTERINFO;
							pLister->Connect = newSocket;
							pLister->pSocket = pSocket;
							pLister->pThread = pThread;
							//把新 Socket 放入连接队列中，由连接处理线程进一步处理
							if(S_FALSE == AddLister(pLister))
							{
								break;
							}// 结束 if(S_FALSE == AddLister(pLister))
							//通知处理线程(ProcessListerThread)进行处理
							SetEvent(m_hLister);
						} // 结束 if(newSocket)
					}
					catch(CTException e)
					{
						TRACE(_T("异常：%s；异常值：%d\n"), e.what(), e.GetErr());
					}

				}
			}
			else
			{
				ASSERT(0);
				//break;
			}// 结束 if(hEvent.iErrorCode[FD_ACCEPT_BIT] == 0)

		}
		if(hEvent.lNetworkEvents & FD_READ)			// 套节字可读
		{
			TRACE(_T("套节字可读\n"));
			if(hEvent.iErrorCode[FD_READ_BIT] == 0)
			{
				if(!pSocket->IsLister)
				{
					if(pSocket->Service)
					{
						if(!pSocket->Service->ProcessReadEvent(pSocket->Sock.Connect))
						{
							TRACE(_T("Process read event error.\n"));
							break;
						} // 结束 if(!pSocket->Service->ProcessReadEvent(pSocket->Sock.Connect))
					}// 结束 if(pSocket->Service)
#ifdef _TEST
					char szText[256];
					int nRecv = pSocket->Sock.Connect->Receive(szText, strlen(szText), 0);
					if(nRecv > 0)
					{
						szText[nRecv] = '\0';
						LOG(_T("接收到数据：%S \n"), szText);
						if(szText[0] == 'e')
						{
							SetEvent(m_hOnRunExit);
						} // 结束 if(szText[0] == 'e')
					}
#endif
				} // 结束 if(!pSocket->IsLister)
			}
			else
			{
				ASSERT(0);
				break;
			}
			
		}
		if(hEvent.lNetworkEvents & FD_WRITE)	// 套节字可写
		{
			if(hEvent.iErrorCode[FD_WRITE_BIT] == 0)
			{
				TRACE(_T("套节字可写\n"));
				if(!pSocket->IsLister)
				{
					if(pSocket->Service)
					{
						if(!pSocket->Service->ProcessWriteEvent(pSocket->Sock.Connect))
						{
							TRACE(_T("Process write event error.\n"));
							break;
						} // 结束 if(!pSocket->Service->ProcessWriteEvent(pSocket->Sock.Connect))
					}// 结束 if(pSocket->Service)
				} // 结束 if(!pSocket->IsLister)
			}
			else
			{
				ASSERT(0);
				break;
			}
		}
		if(hEvent.lNetworkEvents & FD_CLOSE)	// 套节字关闭
		{
			TRACE(_T("关闭连接\n"));
			//RemoveSocketObj(pThread, pSocket);
			break;
		}
		
		return S_OK;

	} while(FALSE);

	// 套节字关闭，或者有错误发生，程序都会转到这里来执行
	RemoveSocketObj(pThread, pSocket);

	return S_FALSE;
}

/*!
\brief   处理线程
\param   LPVOID lpPara：
\return  类型为 DWORD 。
\version 1.0
\author  康  林
\date    2007-7-12 13:50:33
*/
DWORD CManageSocket::ProcessThread(LPVOID lpPara)
{
	BOOL bExit = FALSE;
	PPARAMETER pPara = (PPARAMETER)lpPara;
	PTHREADINFO pThread = pPara->pThread; // 取得本线程对象的指针
	pThread->pbExit = &bExit;
	CManageSocket * pManageSocket = pPara->pManageSocket;
	PTHREADPOLLINFO pPool = pPara->pPool;
	TRACE(_T("Create Thread (0x%X) Successed.\n"), GetCurrentThreadId());

	SetEvent(*(pPara->phEvent));

	while(TRUE)
	{
		int nHandleNum = pThread->socket.size() + 1;
		//	等待网络事件
		int nIndex = ::WSAWaitForMultipleEvents(
			nHandleNum, pThread->hEvents, FALSE, WSA_INFINITE, FALSE);
		if(WSA_WAIT_FAILED == nIndex || WSA_WAIT_TIMEOUT == nIndex || WAIT_IO_COMPLETION == 0)
		{
			if(bExit)
			{
				TRACE(_T("程序退出.\n"));
				return 1;
			} // 结束 if(bExit)
			TRACE(_T("WSAWaitForMultipleEvents 网络事件出错。%d\n"), WSAGetLastError());
			continue;
		}
		nIndex = nIndex - WSA_WAIT_EVENT_0;
		TRACE(_T("对象受信.%d\n"), nIndex);
		// 查看受信的事件对象
		for(int i = nIndex; i < nHandleNum; i++)
		{
			nIndex = ::WSAWaitForMultipleEvents(1, &pThread->hEvents[i], TRUE, 0, FALSE);
			if(nIndex == WSA_WAIT_FAILED || nIndex == WSA_WAIT_TIMEOUT)
			{
				continue;
			}

			if(0 == i)				// hEvents[0]受信，线程退出
			{
				pManageSocket->RebuildArray(pThread);
				// 如果没有客户I/O要处理了，则本线程退出
				if(pThread->socket.size() == 0)
				{
					pManageSocket->RemoveThread(pPool, pThread);
					TRACE(_T("Exit Process thread.\n"));
					return 2;
				}
				//::WSAResetEvent(pThread->hEvents[0]); //因为在 RebuildArray 中已经设置了
				//因为移动了事件句柄，所以这次后面如果有句柄受信，其序号就会发生错误，
				//所以退出，不查后面是否有受信对象
				break; 
			}

			// 查找对应的套节字对象指针，调用HandleIO处理网络事件
			if(i < nHandleNum)
			{
				PSOCKETINFO pSocket = NULL;
				try
				{
					::EnterCriticalSection(&pThread->cs);
					pSocket = (PSOCKETINFO)pThread->socket.at(i - 1);
					::LeaveCriticalSection(&pThread->cs);
				}
				catch(std::out_of_range e)
				{
					TRACE(_T("Get Socket Error.\n"));
					break;
				}
				if(pSocket != NULL)
				{
					if(S_FALSE == pManageSocket->HandleIO(pThread, pSocket))
					{
						TRACE(_T("HandleIO return False.\n"));
						//重建事件数组,在 RemoveSocketObj 已做了
						//WSASetEvent(pThread->hEvents[0]);

						//因为 Socket 的个数已发生改变，所以相应的事件句柄也发生了改变。
						//所以继续查原来后面的事件句柄对应的事件就会出错。
						break;
					}

				}
				else
					TRACE(_T(" Unable to find socket object \n "));
			}
			else
			{
				TRACE(_T("事件个数错误。\n"));
			} // 结束 if(i < nHandleNum)
			
		} // 结束 for(int i = nIndex; i < nHandleNum; i++)
	}// 结束 while(TRUE)
	TRACE(_T("Exit Process thread.\n"));
	return 0;
}

int CManageSocket::OnRun()
{
	while(TRUE)
	{
		DWORD dwRet = WaitForSingleObject(m_hOnRunExit, m_dwOnRunDelay);
		if(WAIT_FAILED == dwRet)
		{
			//无效句柄，则退出线程
			if(6 == ::GetLastError())
			{
				return S_OK;
			} // 结束 if(6 == ::GetLastError())
		} // 结束 if(WAIT_FAILED == dwRet)
		if(WAIT_OBJECT_0 == dwRet)
		{
			return S_OK;
		}// 结束 if(WAIT_OBJECT_0 == nRet)
		if(WAIT_TIMEOUT == dwRet)
		{
			LOG(_T("总监听数：%d\n"), m_TotalListerNumber);
			LOG(_T("当前监听数：%d\n"), m_CurrentListerNumber);
			
			LOG(_T("总连接数：%d\n"), m_TotalConnectNumber);
			LOG(_T("当前连接数：%d\n"), m_CurrentConnectNumber);

			LOG(_T("总前监听线程数：%d\n"), m_TotalListerThreadNumber);
			LOG(_T("当前监听线程数：%d\n"), m_CurrentListerThreadNumber);
			
			LOG(_T("总IO线程数：%d\n"), m_TotalIOThreadNumber);
			LOG(_T("当前IO线程数：%d\n"), m_CurrentIOThreadNumber);

			LOG(_T("\n"));
		} // 结束 if(WAIT_TIMEOUT == dwRet)
	}// 结束 while(TRUE)
	return S_OK;
}

/*!
\brief   把一个新的连接加入到连接队列中，等待连接队列处理线程进行处理
\param   CManageSocket::PLISTERINFO lpListerInfo：
\return  类型为 int 。
\version 1.0
\author  康  林
\date    2007-7-11 16:11:29
*/
int CManageSocket::AddLister(CManageSocket::PLISTERINFO lpListerInfo)
{
	int nRet = S_OK;
	ASSERT(lpListerInfo);
	::EnterCriticalSection(&m_csLister);
	try
	{
		m_lstLister.push_back(lpListerInfo);
	}
	catch(...)
	{
		nRet = S_FALSE;
	}
	::LeaveCriticalSection(&m_csLister);
	return nRet;
}

/*!
\brief   从连接队列中取出最前面的一个新连接进行处理，并把它从队列中称除。
\param   无
\return  类型为 CManageSocket::PLISTERINFO 。如果成功返回新的连接结构指针，如果队列中没有，则返回NULL
\version 1.0
\author  康  林
\date    2007-7-11 16:13:16
*/
CManageSocket::PLISTERINFO CManageSocket::GetLister()
{
	PLISTERINFO pInfo = NULL;
	try
	{
		::EnterCriticalSection(&m_csLister);
	}
	catch(...)
	{
		TRACE(_T("EnterCriticalSection(&m_csLister) exception.\n"));
	}
	
	if(!m_lstLister.empty())
	{
		if(m_lstLister.size() > 0)
		{
			pInfo = m_lstLister.front();
			m_lstLister.pop_front();
		}// 结束 if(m_lstLister.size() > 0)
	}// 结束 if(!m_lstLister.empty())
	try
	{
		::LeaveCriticalSection(&m_csLister);
	}
	catch (...)
	{
		TRACE(_T("LeaveCriticalSection(&m_csLister) exception.\n"));
		pInfo = NULL;
	}
	
	return pInfo;
}

/*!
\brief   处理新的连接队列的线程
\param   LPVOID lpPara：
\return  类型为 DWORD 。
\version 1.0
\author  康  林
\date    2007-7-11 16:15:06
*/
DWORD CManageSocket::ProcessListerThread(LPVOID lpPara)
{
	BOOL bExit = FALSE;
	CManageSocket * pThis = (CManageSocket * )lpPara;
	pThis->m_pbExitListerThread = &bExit;

	while(TRUE)
	{
		DWORD dwRet = WaitForSingleObject(pThis->m_hLister, 10000);
		if(WAIT_FAILED == dwRet)
		{
			//无效句柄，则退出线程
			if(6 == ::GetLastError())
			{
				TRACE(_T("Exit process lister thread.\n"));
				return 6;
			} // 结束 if(6 == ::GetLastError())
		}// 结束 if(WAIT_FAILED == dwRet)
		if(WAIT_TIMEOUT == dwRet || WAIT_OBJECT_0 == dwRet)
		{
			if(WAIT_TIMEOUT == dwRet)
			{
				//增加:超时进行的处理

			}// 结束 if(WAIT_TIMEOUT == dwRet)

			if(bExit)
			{
				TRACE(_T("Exit process lister thread.\n"));
				return 1;
			}// 结束 (bExit)

			PLISTERINFO pLister = pThis->GetLister();
			if(NULL == pLister)
			{
				continue;
			}// 结束 if(NULL == pLister)
			while(NULL != pLister)
			{
//#ifdef _DEBUG
//				//显示登录欢迎信息
//				_tstring szWelcome = _T("Welcome you.\n\rAuthor:KangLin\n\rEmail:kl222@126.com\n\r");
//				pLister->Connect->Send(szWelcome.c_str(), szWelcome.size()* sizeof(TCHAR));
//				
//#endif
				/*string szPeer;
				szPeer = pLister->Connect->GetPeerEndpoint();
				LOG(_T("主机（%S）连接。\n"), szPeer.c_str()); */

				if(bExit)
				{
					TRACE(_T("Exit process lister thread.\n"));
					return 1;
				} // 结束 (bExit)

				//if(pLister->pSocket->Service)
				//{
				//	pLister->pSocket->Service->AddClient(pLister->Connect);
				//} // 结束 (pLister->Connect)

				pThis->AddConncet(pLister->Connect, pLister->pSocket->Service);

				//释放内存
				delete pLister;

				pLister = pThis->GetLister();
			}// 结束 while(NULL != pLister)
		}// 结束 if(WAIT_TIMEOUT == dwRet || WAIT_OBJECT_0 == dwRet)
		
	} // 结束 while(TRUE)

}