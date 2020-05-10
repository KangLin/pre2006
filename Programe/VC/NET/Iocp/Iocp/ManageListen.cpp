#include "StdAfx.h"
#include "ManageListen.h"
#include "EventTCPListenSocket.h"
#include "TCPSock.h"

CManageListen::CManageListen(CManageNet * pMngNet)
{
	if(NULL == pMngNet)
	{
		return;
	}// 结束 if(NULL == pMngNet)

	m_ManageNet = pMngNet;

	m_hThreadListen = NULL;
	::InitializeCriticalSection(&m_csListen);
	m_nLiseterNumber = 0;
	m_nTotalNumber = 0;
	m_hEvent[0] = CreateEvent(NULL, TRUE, FALSE, NULL);
	if(NULL == m_hEvent[0])
	{
		CTException e(_T("重置事件建立错误"), GetLastError());
		throw e;
	}// 结束 if(NULL == m_hEvent[0])	
}

CManageListen::~CManageListen(void)
{
	ClearListen();
	SetEvent(m_hEvent[0]);
	
	//结束线程
	if(m_pExit)
	{
		*m_pExit = TRUE;
		m_pExit = NULL;
	}// 结束 if(m_pExit)

	::DeleteCriticalSection(&m_csListen);

	//关闭重置事件句柄
	CloseHandle(m_hEvent[0]);
}

int CManageListen::Lock()
{
	::EnterCriticalSection(&m_csListen);
	return S_OK;
}

int CManageListen::UnLock()
{
	::LeaveCriticalSection(&m_csListen);
	return S_OK;
}

/*!
\brief   得到当前监听的SOCKET数
\param   无
\return  类型为 LONG 。监听SOCKET数
\version 1.0
\author  康  林
\date    2007-9-27 18:45:23
*/
LONG CManageListen::GetListenNumber()
{
	return m_nLiseterNumber;
}

/*!
\brief   得到总的SOCKET数
\param   无
\return  类型为 LONG 。
\version 1.0
\author  康  林
\date    2007-9-27 18:45:54
*/
LONG CManageListen::GetTotalListenNumber()
{
	return m_nTotalNumber;
}

int CManageListen::Initalize()
{
	int nRet = S_OK;

	return nRet;
}

/*!
\brief   增加一个新监听SOCKET
\param   int nPort：要监听的端口号
\return  类型为 int 。成功返回监听SOCKET的句柄,失败返回负值.(注意返回值是隐藏量)
\version 1.0
\author  康  林
\date    2007-9-27 14:33:59
*/
int CManageListen::AddListen(int nPort)
{
	static bool bCreateListenThread = FALSE;

	int nRet = INVALID_SOCKET;

	if(m_Listen.size() >= MAX_Listen_NUMBER - 1)
	{
		TRACE(_T("超过最大监听数[%d]\n"), MAX_Listen_NUMBER);
		return -2;
	} // 结束 if(m_Listen.size() >= MAX_Listen_NUMBER - 1)

	if(!bCreateListenThread)
	{
		//建立连接处理线程
		DWORD dwID;
		m_hThreadListen = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ListenWorkThread, this, NULL, &dwID);
		if(NULL == m_hThreadListen)
		{
			TRACE(_T("CreateThread error\n"));
			return -3;
		}// 结束 if(NULL == m_hThreadListen)
		bCreateListenThread = TRUE;
	} // 结束 if(!bCreateListenThread)

	vector<CListenSocket * >::iterator it;
	for(it = m_Listen.begin(); it != m_Listen.end(); it++)
	{
		CListenSocket * pListen = *it;
		if(pListen->GetMyPort() == nPort)
		{
			TRACE(_T("Listen已经存在\n"));
			return -4;
		} // 结束 if(pListen->GetMyPort() == nPort)
	}// 结束 for(it = m_Listen.begin(); it != m_Listen.end(); it++)

	Lock();
	try
	{
		CListenSocket * pListen = new CEventTCPListenSocket(nPort);
		try
		{
			m_Listen.push_back(pListen);
			nRet = pListen->GetFd();
			::InterlockedIncrement(&m_nLiseterNumber);
			InterlockedIncrement(&m_nTotalNumber);
			//设置事件数组
			SetEvent(m_hEvent[0]);
		}
		catch(...)
		{
			delete pListen;
			nRet = -5;
		}
	}
	catch(CTException e)
	{
		nRet = INVALID_SOCKET;
	}
	UnLock();

	return nRet;
}

/*!
\brief   RemoveListen
\param   int nFd：SOCKET句柄
\return  类型为 int 。
\version 1.0
\author  康  林
\date    2007-9-27 14:56:05
*/
int CManageListen::RemoveListen(int nFd)
{
	vector < CListenSocket * > ::iterator it;
	Lock();
	for(it = m_Listen.begin(); it != m_Listen.end(); it++)
	{
		CListenSocket * pListen = *it;
		if(pListen->GetFd() == nFd)
		{
			m_Listen.erase(it);
			//重置调事件数组
			SetEvent(m_hEvent[0]);
			delete pListen;
			InterlockedDecrement(&m_nLiseterNumber);
			return S_OK;
		} // 结束 if(pListen->GetFd() == nFd)
	}// 结束 for(it = m_Listen.begin(); it != m_Listen.end(); it++)
	UnLock();

	return S_OK;
}

int CManageListen::ClearListen()
{
	int nRet = S_OK;

	Lock();
	try
	{
		vector < CListenSocket * > ::iterator it;
		for(it = m_Listen.begin(); it != m_Listen.end(); it++)
		{
			delete(*it);
		}// 结束 for(it = m_Listen.begin(); it != m_Listen.end(); it++)
		m_Listen.clear();
	}
	catch(...)
	{
		nRet = S_FALSE;
	}
	UnLock();

	return nRet;
}

int CManageListen::RebuildArray()
{
	Lock();
	int i = 0;
	for(i = 0; i < m_Listen.size(); i++)
	{
		CEventTCPListenSocket * pListen = (CEventTCPListenSocket * )m_Listen[i];
		m_hEvent[i + 1] = pListen->GetEvent();
	} // 结束 for(i = 0; i < m_Listen.size(); i++)
	UnLock();
	ResetEvent(m_hEvent[0]);
	return S_OK;
}

int CManageListen::HandleIO(int nPos)
{
	int nRet = S_OK;
	// 获取具体发生的网络事件
	WSANETWORKEVENTS hEvent;
	CEventTCPListenSocket * pListen = (CEventTCPListenSocket * )m_Listen[nPos];
	do
	{
		if(SOCKET_ERROR == ::WSAEnumNetworkEvents(pListen->GetFd(), pListen->GetEvent(), &hEvent))
		{
			TRACE(_T("WSAEnumNetworkEvents error:%d\n"), WSAGetLastError());
			break;
		}// 结束 if(SOCKET_ERROR == ::WSAEnumNetworkEvents(pListen->GetFd(), pListen->GetEvent(), &hEvent))

		TRACE(_T("HandleIO:%d\n"), hEvent.lNetworkEvents);

		if(hEvent.lNetworkEvents & FD_ACCEPT)//接受连接
		{
			if(hEvent.iErrorCode[FD_ACCEPT_BIT] == 0)
			{

				CTCPSocket * pSock = (CTCPSocket * )pListen->Accept();
				TRACE(_T("接受连接:%s\n"), pSock->GetPeerEndpoint().c_str());

				m_ManageNet->AddConncet(pSock);
			}
			else
			{
				ASSERT(0);
				//break;
			}// 结束 if(hEvent.iErrorCode[FD_ACCEPT_BIT] == 0)

		}
		
		if(hEvent.lNetworkEvents & FD_CLOSE)	// 套节字关闭
		{
			TRACE(_T("关闭连接\n"));
			RemoveListen(pListen->GetFd());
			break;
		}

		return S_OK;

	} while(FALSE);

	return S_FALSE;
}

DWORD CManageListen::ListenWorkThread(void * pPara)
{
	BOOL bExit = FALSE;
	int nRet = S_OK;
	CManageListen * pThis = (CManageListen * )pPara;
	pThis->m_pExit = &bExit;

	while(TRUE)
	{
		int nHandleNum = pThis->GetListenNumber() + 1;
		//	等待网络事件
		int nIndex = ::WSAWaitForMultipleEvents(
			nHandleNum, pThis->m_hEvent, FALSE, WSA_INFINITE, FALSE);
		if(WSA_WAIT_FAILED == nIndex || WSA_WAIT_TIMEOUT == nIndex || WAIT_IO_COMPLETION == 0)
		{
			if(bExit)
			{
				TRACE(_T("程序退出,线程结束.\n"));
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
			if(bExit)
			{
				TRACE(_T("程序退出,线程结束.\n"));
				return 1;
			} // 结束 if(bExit)
			nIndex = ::WSAWaitForMultipleEvents(1, &pThis->m_hEvent[i], TRUE, 0, FALSE);
			if(nIndex == WSA_WAIT_FAILED || nIndex == WSA_WAIT_TIMEOUT)
			{
				continue;
			}

			if(0 == i)				// hEvents[0]受信，线程退出
			{
				if(bExit)
				{
					TRACE(_T("程序退出,线程结束.\n"));
					return 1;
				} // 结束 if(bExit)
				pThis->RebuildArray();
				// 如果没有客户I/O要处理了，则本线程退出
				if(0 == pThis->GetListenNumber())
				{
					TRACE(_T("Exit Process thread.\n"));
					pThis->m_pExit = NULL;
					return 2;
				}
				//因为移动了事件句柄，所以这次后面如果有句柄受信，其序号就会发生错误，
				//所以退出，不查后面是否有受信对象
				break; 
			}

			// 查找对应的套节字对象指针，调用HandleIO处理网络事件
			if(i < nHandleNum)
			{

				if(S_FALSE == pThis->HandleIO(i - 1))
				{
					TRACE(_T("HandleIO return False.\n"));
					break;
				}
			}
			else
			{
				TRACE(_T("事件个数错误。\n"));
			} // 结束 if(i < nHandleNum)

		} // 结束 for(int i = nIndex; i < nHandleNum; i++)
	}// 结束 while(TRUE)

	pThis->m_pExit = NULL;

	return nRet;
}