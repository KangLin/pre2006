/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    ManageSocket.cpp
\brief   Socket �����࣬���ڹ��� Socket
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��7��11��  17:26:20
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
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
	} // ���� if(NULL == m_hOnRunExit)


	//��ʼ������ Lister �߳���ر���
	m_pbExitListerThread = NULL;
	InitializeCriticalSection(&m_csLister);
	m_hLister = CreateEvent(NULL, FALSE, FALSE, NULL);
	if(NULL == m_hLister)
	{
		TRACE(_T("CreateEvent error\n"));
	}// ���� if(NULL == m_hLister)

}

CManageSocket::~CManageSocket(void)
{
	TRACE(_T("~CManageSocket.\n"));
	//�˳� OnRun
	SetEvent(m_hOnRunExit);


	//�˳� Lister ���д����߳�
	if(m_pbExitListerThread)
	{
		*m_pbExitListerThread = TRUE;
	}// ���� if(m_pbExitListerThread)
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
	}// ���� if(NULL == pSocket)
	memset(pSocket, 0, sizeof(SOCKETINFO));
	//�����¼�
	pSocket->hEvent = WSACreateEvent();
	ASSERT(pSocket->hEvent != WSA_INVALID_EVENT);
	if(WSA_INVALID_EVENT == pSocket->hEvent)
	{
		delete pSocket;
		return S_FALSE;
	} // ���� if(WSA_INVALID_EVENT == pSocket->hEvent)
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
	}// ���� if(server)

	//���뵽�̳߳���
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
				//ע�⣬λ�ò��ܱ䣬����ᷢ������
				::LeaveCriticalSection(&pThread->cs);
				nRet = RemoveSocketObj(*it, pSocket);
				::LeaveCriticalSection(&m_IOThreadPool.cs);
				return nRet;
			} // ���� if(pSocket->Sock.Connect == sock && !pSocket->IsLister)
		}// ���� for(itSock = pThread->socket.begin(); itSock != pThread->socket.end(); itSock++)
		::LeaveCriticalSection(&pThread->cs);
	}// ���� for(it = m_IOThreadPool.m_Thread.begin(); it != m_IOThreadPool.m_Thread.end(); it++)
	::LeaveCriticalSection(&m_IOThreadPool.cs);

	//����̳߳���û�д� Socket ����ɾ����
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
	}// ���� if(NULL == pSocket)

	if(!bCreateListerThread)
	{
		//�������Ӵ����߳�
		DWORD dwID;
		HANDLE hThreadLister = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ProcessListerThread, this, NULL, &dwID);
		if(NULL == hThreadLister)
		{
			TRACE(_T("CreateThread error\n")); 
		}
		else
		{
			CloseHandle(hThreadLister);
		}// ���� (NULL, NULL, (LPTHREAD_START_ROUTINE)ProcessListerThread, this, NULL, &dwID)
		bCreateListerThread = TRUE;
	} // ���� if(!bCreateListerThread)

	memset(pSocket, 0, sizeof(SOCKETINFO));
	//�����¼�
	pSocket->hEvent = WSACreateEvent();
	ASSERT(pSocket->hEvent != WSA_INVALID_EVENT);
	if(WSA_INVALID_EVENT == pSocket->hEvent)
	{
		delete pSocket;
		return S_FALSE;
	} // ���� if(WSA_INVALID_EVENT == pSocket->hEvent)
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

	//���뵽�̳߳���
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
				//ע�⣬λ�ò��ܱ䣬����ᷢ������
				::LeaveCriticalSection(&pThread->cs);
				nRet = RemoveSocketObj(*it, pSocket);
				::LeaveCriticalSection(&m_ListerThreadPool.cs);
				return nRet;
			} // ���� if(pSocket->Sock.Listener == sock && pSocket->IsLister)
		}// ���� for(itSock = pThread->socket.begin(); itSock != pThread->socket.end(); itSock++)
		::LeaveCriticalSection(&pThread->cs);
	}// ���� for(it = m_IOThreadPool.m_Thread.begin(); it != m_IOThreadPool.m_Thread.end(); it++)
	::LeaveCriticalSection(&m_ListerThreadPool.cs);

	//����̳߳���û�д� Socket ����ɾ����
	delete sock;
	return nRet;
}

/*!
\brief   ����һ�� PSOCKETINFO ����ָ�����̳߳�
\param   PTHREADPOLLINFO pPool��
\param   PSOCKETINFO pSocket  ��
\return  ����Ϊ int ��
\version 1.0
\author  ��  ��
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
		} // ���� if(S_OK == nRet)
	}// ���� for(it = pPool->m_Thread.begin(); it != pPool->m_Thread.end(); it++)
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
		} // ���� if(NULL == pThread)
	} // ���� if(S_FALSE == nRet)

	return nRet;
}

/*!
\brief   ����һ�� PSOCKETINFO ����ָ�����߳�
\param   PTHREADINFO pThread��
\param   PSOCKETINFO pSocket��
\return  ����Ϊ int ��
\version 1.0
\author  ��  ��
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
		}// ���� if(pSocket->IsLister)
		TRACE(_T("Socket Number��%d\n"), pThread->socket.size());
#endif

		try
		{
			pThread->socket.push_back(pSocket);
			int nPos = pThread->socket.size();
			pThread->hEvents[nPos] = pSocket->hEvent;

			//Ϊʲôֻ�����¼�֪ͨ������Ϊʲô����������һ��ֱ�����ã�����ʱ�����ò����¼�֪ͨ��
			//������Ϊ�߳����ڵȴ�ǰ��ָ���������¼���������ռӵ��¼������������ȴ���������ڣ���Ȼ���Ѽӵ��������У���
			//���̵߳ȴ��ĸ���û�з����仯������Ҫ������ĵ����¼�֪ͨ�̼߳������µ��¼���
			//�����ͷ��߳��� Socket �����෴�Ĵ��������// <a href = ".\ManageSocket.cpp#���߳���ɾ��"></a>
			//֪ͨ�����¼��������
			WSASetEvent(pThread->hEvents[0]);// <a name = "���߳��в���Socket"></a>
		}
		catch(...)
		{
			nRet = S_FALSE;
		};
	}
	else
	{
		nRet = S_FALSE;
	} // ���� if(pThread->socket.size() < WSA_MAXIMUM_WAIT_EVENTS - 1)
	::LeaveCriticalSection(&pThread->cs);
	return nRet;
}

/*!
\brief   �ͷ� PSOCKETINFO ����
\param   PSOCKETINFO pSocket��
\return  ����Ϊ int ��
\version 1.0
\author  ��  ��
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
				//�Ƴ������еĿͻ���
				pSocket->Service->RemoveClient(pSocket->Sock.Connect);
			} // ���� if(pSocket->Service)
			
			delete pSocket->Sock.Connect;
		}// ���� if(pSocket->IsLister)
		CloseHandle(pSocket->hEvent);
		// �Ƿ�ɾ�����񣿲���ɾ�����񣬷�����Ӧ�ó���ɾ��

		delete pSocket;
	}
	catch(...)
	{
		TRACE(_T("FreeSocketObj Error.\n"));
	}
	
	return nRet;
}

/*!
\brief   ��ָ���߳��е� Socket ��������ȥָ���� PSOCKETINFO
\param   CManageSocket::PTHREADINFO pThread��
\param   CManageSocket::PSOCKETINFO pSocket ��
\return  ����Ϊ int ��
\version 1.0
\author  ��  ��
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
		} // ���� if((*it) == pSocket)
	}// ���� for(it = pThread->socket.begin(); it != pThread->socket.end(); it++)
	::LeaveCriticalSection(&pThread->cs);

	//��������¼��������飬��::WSASetEvent(pThread->hEvents[0])����ͬһ�߳��ڲ�����Ч����Ĵ���
	//������¼�֪ͨ����������������Ч�ľ����������� Socket ���뵽�߳��ڲ����෴�Ĵ���:)
	//�����// <a href = ".\ManageSocket.cpp#���߳��в���Socket"></a>
	RebuildArray(pThread);// <a name = "���߳���ɾ��"></a>

	//֪ͨ�����¼��������
	::WSASetEvent(pThread->hEvents[0]);

	// ˵��һ�������ж�
	if(pSocket->IsLister)
	{
		::InterlockedDecrement(&m_CurrentListerNumber);
	}
	else
	{
		::InterlockedDecrement(&m_CurrentConnectNumber);
	}// ���� if(pSocket->IsLister)

	nRet = FreeSocketObj(pSocket);

	return nRet;
}

/*!
\brief   ���½����̶߳���� hEvents ���飬��Ϊ��������߳��ڵ�һ�� Socket ��ɾ���ˣ�����Ҫ�ƶ����� hEvents
\param   PTHREADINFO pThread��������߳̽ṹ����
\return  ����Ϊ int ��
\version 1.0
\author  ��  ��
\date    2007-7-5 16:54:16
*/
int CManageSocket::RebuildArray(PTHREADINFO pThread)
{
	int i = 0;

	ASSERT(pThread);

	::EnterCriticalSection(&pThread->cs);
	// �ӵ�1����ʼд����0������ָʾ��Ҫ�ؽ���
	for(i = 0; i < pThread->socket.size(); i++)
	{
		pThread->hEvents[i + 1] = pThread->socket[i]->hEvent;
	}// ���� for(i = 0; i < pThread->socket.size(); i++)
	::LeaveCriticalSection(&pThread->cs);

	//�����ؽ������¼�����
	if(::WSAResetEvent(pThread->hEvents[0]))
	{
		return S_OK;
	} // ���� if(::WSAResetEvent(pThread->hEvents[0]))
	return S_FALSE;
}

/*!
\brief   �ͷ� PTHREADINFO
\param   PTHREADINFO pThread��
\return  ����Ϊ int ��
\version 1.0
\author  ��  ��
\date    2007-7-6 11:01:38
*/
int CManageSocket::FreeThreadObj(PTHREADINFO pThread)
{
	ASSERT(pThread);

	TRACE(_T("Free Thread:%p\n"), pThread);

	//�ͷ� PSOCKETINFO
	vector<PSOCKETINFO>::iterator it;
	::EnterCriticalSection(&pThread->cs);
	for(it = pThread->socket.begin(); it != pThread->socket.end(); it++)
	{
		FreeSocketObj(*it);
	}// ���� for(it = pThread->socket.begin(); it != pThread->socket.end(); it++)
	pThread->socket.clear();
	::LeaveCriticalSection(&pThread->cs);

	//�ͷŷ��� Socket ���еĹؼ�����α���
	::DeleteCriticalSection(&pThread->cs);
	//�ͷ�hEvent[0]�¼�����
	::CloseHandle(pThread->hEvents[0]);
	if(pThread->pbExit)
	{
		*(pThread->pbExit) = TRUE;
	} // ���� if(pThread->pbExit)
	
	delete pThread;
	return S_OK;
}

/*!
\brief   ��һ���̳߳�������һ���µ��߳�
\param   CManageSocket::PTHREADPOLLINFO pPool��ָ�����̳߳�
\return  ����Ϊ CManageSocket::PTHREADINFO �������ӵ��̶߳���ָ�룬������ɹ����� NULL
\version 1.0
\author  ��  ��
\date    2007-7-9 11:05:19
*/
CManageSocket::PTHREADINFO CManageSocket::AddThread(CManageSocket::PTHREADPOLLINFO pPool)
{
	int nRet = S_OK;
	//�½��߳̽ṹ
	PTHREADINFO pThread = new THREADINFO;
	if(NULL == pThread)
	{
		return NULL;
	}// ���� if(NULL == pThread)

	memset(pThread, 0, sizeof(THREADINFO));
	//��ʼ���ٽ��
	InitializeCriticalSection(&pThread->cs);
	//��ʼ hEvent[0] �¼�����
	pThread->hEvents[0] = WSACreateEvent(); // CreateEvent(NULL, TRUE, FALSE, NULL);

	//�������߳�
	PARAMETER Para;
	DWORD dwID;
	HANDLE hEvent;
	hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if(NULL == hEvent)
	{
		delete pThread;
		return NULL;
	}// ���� if(NULL == hEvent)
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
			//�����̶߳�����뵽�̳߳�
			::EnterCriticalSection(&pPool->cs);
			try
			{
				pPool->m_Thread.push_back(pThread);
				::LeaveCriticalSection(&pPool->cs);
				//����
				if(pPool->bIsLister)
				{
					::InterlockedIncrement(&m_TotalListerThreadNumber);
					::InterlockedIncrement(&m_CurrentListerThreadNumber);
				}
				else
				{
					::InterlockedIncrement(&m_TotalIOThreadNumber);
					::InterlockedIncrement(&m_CurrentIOThreadNumber);
				} // ���� if(pPool->bIsLister)

				return pThread;
			}
			catch(...)
			{
				::LeaveCriticalSection(&pPool->cs);
			}
		} // ���� if(WAIT_OBJECT_0 == ::WaitForSingleObject(hEvent, INFINITE))
	} // ���� if(hThread)

	//������
	//�ͷ���Դ
	CloseHandle(hEvent);
	if(NULL != hThread)
	{
		CloseHandle(hThread);
	} // ���� if(NULL != hThread)
	delete pThread;
	return NULL;
}

/*!
\brief   ���̳߳����Ƴ�ָ�����̶߳���(PTHREADINFO)
\param   PTHREADPOLLINFO pPool���̳߳�
\param   PTHREADINFO pThread ���̶߳���
\return  ����Ϊ int ��
\version 1.0
\author  ��  ��
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
			//�ͷ��̶߳���
			FreeThreadObj(pThread);
			//���б���ɾ����
			pPool->m_Thread.erase(it);
			//����
			if(pPool->bIsLister)
			{
				::InterlockedDecrement(&m_CurrentListerThreadNumber);
			}
			else
			{
				::InterlockedDecrement(&m_CurrentIOThreadNumber);
			} // ���� if(pPool->bIsLister)
			//�뿪�ٽ���
			::LeaveCriticalSection(&pPool->cs);
			return S_OK;
		} // ���� if(*it == pThread)
	}// ���� for(it = pPool->m_Thread.begin(); it != pPool->m_Thread.end(); it++)
	::LeaveCriticalSection(&pPool->cs);

	//�ͷ��̶߳���
	FreeThreadObj(pThread);
	
	return nRet;
}

/*!
\brief   �ͷ��̳߳�
\param   PTHREADPOLLINFO pPool��
\return  ����Ϊ int ��
\version 1.0
\author  ��  ��
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
		//}// ���� for(itSock = pThread->socket.begin(); itSock != pThread->socket.end(); itSock++)
		//pThread->socket.clear();
		//::LeaveCriticalSection(&pThread->cs);
		//RebuildArray(pThread);
		////�����ͷ��߳�֪ͨ���߳�ɾ���Լ�
		//::WSASetEvent(pThread->hEvents[0]);

		::EnterCriticalSection(&pPool->cs);
		nSize = pPool->m_Thread.size();
		::LeaveCriticalSection(&pPool->cs);
	}// ���� while(nSize > 0)
	DeleteCriticalSection(&pPool->cs);
	return nRet;
}

/*!
\brief   ���� Socket IO �¼�
\param   PTHREADINFO pThread��
\param   PSOCKETINFO pSocket��
\return  ����Ϊ int ��
\version 1.0
\author  ��  ��
\date    2007-7-12 13:49:58
*/
int CManageSocket::HandleIO(PTHREADINFO pThread, PSOCKETINFO pSocket)
{
	// ��ȡ���巢���������¼�
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
		} // ���� ()
		if(SOCKET_ERROR == ::WSAEnumNetworkEvents(s, pSocket->hEvent, &hEvent))
		{
			TRACE(_T("WSAEnumNetworkEvents error:%d\n"), WSAGetLastError());
			break;
		}// ���� if(SOCKET_ERROR == ::WSAEnumNetworkEvents(s, pSocket->hEvent, &hEvent))

		TRACE(_T("HandleIO:%d\n"), hEvent.lNetworkEvents);

		if(hEvent.lNetworkEvents & FD_ACCEPT)//��������
		{
			if(hEvent.iErrorCode[FD_ACCEPT_BIT] == 0)
			{
				TRACE(_T("��������\n"));
				if(!pSocket->IsLister)
				{
					ASSERT(0);
					//����
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
							//���� Socket �������Ӷ����У������Ӵ����߳̽�һ������
							if(S_FALSE == AddLister(pLister))
							{
								break;
							}// ���� if(S_FALSE == AddLister(pLister))
							//֪ͨ�����߳�(ProcessListerThread)���д���
							SetEvent(m_hLister);
						} // ���� if(newSocket)
					}
					catch(CTException e)
					{
						TRACE(_T("�쳣��%s���쳣ֵ��%d\n"), e.what(), e.GetErr());
					}

				}
			}
			else
			{
				ASSERT(0);
				//break;
			}// ���� if(hEvent.iErrorCode[FD_ACCEPT_BIT] == 0)

		}
		if(hEvent.lNetworkEvents & FD_READ)			// �׽��ֿɶ�
		{
			TRACE(_T("�׽��ֿɶ�\n"));
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
						} // ���� if(!pSocket->Service->ProcessReadEvent(pSocket->Sock.Connect))
					}// ���� if(pSocket->Service)
#ifdef _TEST
					char szText[256];
					int nRecv = pSocket->Sock.Connect->Receive(szText, strlen(szText), 0);
					if(nRecv > 0)
					{
						szText[nRecv] = '\0';
						LOG(_T("���յ����ݣ�%S \n"), szText);
						if(szText[0] == 'e')
						{
							SetEvent(m_hOnRunExit);
						} // ���� if(szText[0] == 'e')
					}
#endif
				} // ���� if(!pSocket->IsLister)
			}
			else
			{
				ASSERT(0);
				break;
			}
			
		}
		if(hEvent.lNetworkEvents & FD_WRITE)	// �׽��ֿ�д
		{
			if(hEvent.iErrorCode[FD_WRITE_BIT] == 0)
			{
				TRACE(_T("�׽��ֿ�д\n"));
				if(!pSocket->IsLister)
				{
					if(pSocket->Service)
					{
						if(!pSocket->Service->ProcessWriteEvent(pSocket->Sock.Connect))
						{
							TRACE(_T("Process write event error.\n"));
							break;
						} // ���� if(!pSocket->Service->ProcessWriteEvent(pSocket->Sock.Connect))
					}// ���� if(pSocket->Service)
				} // ���� if(!pSocket->IsLister)
			}
			else
			{
				ASSERT(0);
				break;
			}
		}
		if(hEvent.lNetworkEvents & FD_CLOSE)	// �׽��ֹر�
		{
			TRACE(_T("�ر�����\n"));
			//RemoveSocketObj(pThread, pSocket);
			break;
		}
		
		return S_OK;

	} while(FALSE);

	// �׽��ֹرգ������д����������򶼻�ת��������ִ��
	RemoveSocketObj(pThread, pSocket);

	return S_FALSE;
}

/*!
\brief   �����߳�
\param   LPVOID lpPara��
\return  ����Ϊ DWORD ��
\version 1.0
\author  ��  ��
\date    2007-7-12 13:50:33
*/
DWORD CManageSocket::ProcessThread(LPVOID lpPara)
{
	BOOL bExit = FALSE;
	PPARAMETER pPara = (PPARAMETER)lpPara;
	PTHREADINFO pThread = pPara->pThread; // ȡ�ñ��̶߳����ָ��
	pThread->pbExit = &bExit;
	CManageSocket * pManageSocket = pPara->pManageSocket;
	PTHREADPOLLINFO pPool = pPara->pPool;
	TRACE(_T("Create Thread (0x%X) Successed.\n"), GetCurrentThreadId());

	SetEvent(*(pPara->phEvent));

	while(TRUE)
	{
		int nHandleNum = pThread->socket.size() + 1;
		//	�ȴ������¼�
		int nIndex = ::WSAWaitForMultipleEvents(
			nHandleNum, pThread->hEvents, FALSE, WSA_INFINITE, FALSE);
		if(WSA_WAIT_FAILED == nIndex || WSA_WAIT_TIMEOUT == nIndex || WAIT_IO_COMPLETION == 0)
		{
			if(bExit)
			{
				TRACE(_T("�����˳�.\n"));
				return 1;
			} // ���� if(bExit)
			TRACE(_T("WSAWaitForMultipleEvents �����¼�����%d\n"), WSAGetLastError());
			continue;
		}
		nIndex = nIndex - WSA_WAIT_EVENT_0;
		TRACE(_T("��������.%d\n"), nIndex);
		// �鿴���ŵ��¼�����
		for(int i = nIndex; i < nHandleNum; i++)
		{
			nIndex = ::WSAWaitForMultipleEvents(1, &pThread->hEvents[i], TRUE, 0, FALSE);
			if(nIndex == WSA_WAIT_FAILED || nIndex == WSA_WAIT_TIMEOUT)
			{
				continue;
			}

			if(0 == i)				// hEvents[0]���ţ��߳��˳�
			{
				pManageSocket->RebuildArray(pThread);
				// ���û�пͻ�I/OҪ�����ˣ����߳��˳�
				if(pThread->socket.size() == 0)
				{
					pManageSocket->RemoveThread(pPool, pThread);
					TRACE(_T("Exit Process thread.\n"));
					return 2;
				}
				//::WSAResetEvent(pThread->hEvents[0]); //��Ϊ�� RebuildArray ���Ѿ�������
				//��Ϊ�ƶ����¼������������κ�������о�����ţ�����žͻᷢ������
				//�����˳�����������Ƿ������Ŷ���
				break; 
			}

			// ���Ҷ�Ӧ���׽��ֶ���ָ�룬����HandleIO���������¼�
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
						//�ؽ��¼�����,�� RemoveSocketObj ������
						//WSASetEvent(pThread->hEvents[0]);

						//��Ϊ Socket �ĸ����ѷ����ı䣬������Ӧ���¼����Ҳ�����˸ı䡣
						//���Լ�����ԭ��������¼������Ӧ���¼��ͻ����
						break;
					}

				}
				else
					TRACE(_T(" Unable to find socket object \n "));
			}
			else
			{
				TRACE(_T("�¼���������\n"));
			} // ���� if(i < nHandleNum)
			
		} // ���� for(int i = nIndex; i < nHandleNum; i++)
	}// ���� while(TRUE)
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
			//��Ч��������˳��߳�
			if(6 == ::GetLastError())
			{
				return S_OK;
			} // ���� if(6 == ::GetLastError())
		} // ���� if(WAIT_FAILED == dwRet)
		if(WAIT_OBJECT_0 == dwRet)
		{
			return S_OK;
		}// ���� if(WAIT_OBJECT_0 == nRet)
		if(WAIT_TIMEOUT == dwRet)
		{
			LOG(_T("�ܼ�������%d\n"), m_TotalListerNumber);
			LOG(_T("��ǰ��������%d\n"), m_CurrentListerNumber);
			
			LOG(_T("����������%d\n"), m_TotalConnectNumber);
			LOG(_T("��ǰ��������%d\n"), m_CurrentConnectNumber);

			LOG(_T("��ǰ�����߳�����%d\n"), m_TotalListerThreadNumber);
			LOG(_T("��ǰ�����߳�����%d\n"), m_CurrentListerThreadNumber);
			
			LOG(_T("��IO�߳�����%d\n"), m_TotalIOThreadNumber);
			LOG(_T("��ǰIO�߳�����%d\n"), m_CurrentIOThreadNumber);

			LOG(_T("\n"));
		} // ���� if(WAIT_TIMEOUT == dwRet)
	}// ���� while(TRUE)
	return S_OK;
}

/*!
\brief   ��һ���µ����Ӽ��뵽���Ӷ����У��ȴ����Ӷ��д����߳̽��д���
\param   CManageSocket::PLISTERINFO lpListerInfo��
\return  ����Ϊ int ��
\version 1.0
\author  ��  ��
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
\brief   �����Ӷ�����ȡ����ǰ���һ�������ӽ��д����������Ӷ����гƳ���
\param   ��
\return  ����Ϊ CManageSocket::PLISTERINFO ������ɹ������µ����ӽṹָ�룬���������û�У��򷵻�NULL
\version 1.0
\author  ��  ��
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
		}// ���� if(m_lstLister.size() > 0)
	}// ���� if(!m_lstLister.empty())
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
\brief   �����µ����Ӷ��е��߳�
\param   LPVOID lpPara��
\return  ����Ϊ DWORD ��
\version 1.0
\author  ��  ��
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
			//��Ч��������˳��߳�
			if(6 == ::GetLastError())
			{
				TRACE(_T("Exit process lister thread.\n"));
				return 6;
			} // ���� if(6 == ::GetLastError())
		}// ���� if(WAIT_FAILED == dwRet)
		if(WAIT_TIMEOUT == dwRet || WAIT_OBJECT_0 == dwRet)
		{
			if(WAIT_TIMEOUT == dwRet)
			{
				//����:��ʱ���еĴ���

			}// ���� if(WAIT_TIMEOUT == dwRet)

			if(bExit)
			{
				TRACE(_T("Exit process lister thread.\n"));
				return 1;
			}// ���� (bExit)

			PLISTERINFO pLister = pThis->GetLister();
			if(NULL == pLister)
			{
				continue;
			}// ���� if(NULL == pLister)
			while(NULL != pLister)
			{
//#ifdef _DEBUG
//				//��ʾ��¼��ӭ��Ϣ
//				_tstring szWelcome = _T("Welcome you.\n\rAuthor:KangLin\n\rEmail:kl222@126.com\n\r");
//				pLister->Connect->Send(szWelcome.c_str(), szWelcome.size()* sizeof(TCHAR));
//				
//#endif
				/*string szPeer;
				szPeer = pLister->Connect->GetPeerEndpoint();
				LOG(_T("������%S�����ӡ�\n"), szPeer.c_str()); */

				if(bExit)
				{
					TRACE(_T("Exit process lister thread.\n"));
					return 1;
				} // ���� (bExit)

				//if(pLister->pSocket->Service)
				//{
				//	pLister->pSocket->Service->AddClient(pLister->Connect);
				//} // ���� (pLister->Connect)

				pThis->AddConncet(pLister->Connect, pLister->pSocket->Service);

				//�ͷ��ڴ�
				delete pLister;

				pLister = pThis->GetLister();
			}// ���� while(NULL != pLister)
		}// ���� if(WAIT_TIMEOUT == dwRet || WAIT_OBJECT_0 == dwRet)
		
	} // ���� while(TRUE)

}