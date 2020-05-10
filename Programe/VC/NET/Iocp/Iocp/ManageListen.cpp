#include "StdAfx.h"
#include "ManageListen.h"
#include "EventTCPListenSocket.h"
#include "TCPSock.h"

CManageListen::CManageListen(CManageNet * pMngNet)
{
	if(NULL == pMngNet)
	{
		return;
	}// ���� if(NULL == pMngNet)

	m_ManageNet = pMngNet;

	m_hThreadListen = NULL;
	::InitializeCriticalSection(&m_csListen);
	m_nLiseterNumber = 0;
	m_nTotalNumber = 0;
	m_hEvent[0] = CreateEvent(NULL, TRUE, FALSE, NULL);
	if(NULL == m_hEvent[0])
	{
		CTException e(_T("�����¼���������"), GetLastError());
		throw e;
	}// ���� if(NULL == m_hEvent[0])	
}

CManageListen::~CManageListen(void)
{
	ClearListen();
	SetEvent(m_hEvent[0]);
	
	//�����߳�
	if(m_pExit)
	{
		*m_pExit = TRUE;
		m_pExit = NULL;
	}// ���� if(m_pExit)

	::DeleteCriticalSection(&m_csListen);

	//�ر������¼����
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
\brief   �õ���ǰ������SOCKET��
\param   ��
\return  ����Ϊ LONG ������SOCKET��
\version 1.0
\author  ��  ��
\date    2007-9-27 18:45:23
*/
LONG CManageListen::GetListenNumber()
{
	return m_nLiseterNumber;
}

/*!
\brief   �õ��ܵ�SOCKET��
\param   ��
\return  ����Ϊ LONG ��
\version 1.0
\author  ��  ��
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
\brief   ����һ���¼���SOCKET
\param   int nPort��Ҫ�����Ķ˿ں�
\return  ����Ϊ int ���ɹ����ؼ���SOCKET�ľ��,ʧ�ܷ��ظ�ֵ.(ע�ⷵ��ֵ��������)
\version 1.0
\author  ��  ��
\date    2007-9-27 14:33:59
*/
int CManageListen::AddListen(int nPort)
{
	static bool bCreateListenThread = FALSE;

	int nRet = INVALID_SOCKET;

	if(m_Listen.size() >= MAX_Listen_NUMBER - 1)
	{
		TRACE(_T("������������[%d]\n"), MAX_Listen_NUMBER);
		return -2;
	} // ���� if(m_Listen.size() >= MAX_Listen_NUMBER - 1)

	if(!bCreateListenThread)
	{
		//�������Ӵ����߳�
		DWORD dwID;
		m_hThreadListen = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ListenWorkThread, this, NULL, &dwID);
		if(NULL == m_hThreadListen)
		{
			TRACE(_T("CreateThread error\n"));
			return -3;
		}// ���� if(NULL == m_hThreadListen)
		bCreateListenThread = TRUE;
	} // ���� if(!bCreateListenThread)

	vector<CListenSocket * >::iterator it;
	for(it = m_Listen.begin(); it != m_Listen.end(); it++)
	{
		CListenSocket * pListen = *it;
		if(pListen->GetMyPort() == nPort)
		{
			TRACE(_T("Listen�Ѿ�����\n"));
			return -4;
		} // ���� if(pListen->GetMyPort() == nPort)
	}// ���� for(it = m_Listen.begin(); it != m_Listen.end(); it++)

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
			//�����¼�����
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
\param   int nFd��SOCKET���
\return  ����Ϊ int ��
\version 1.0
\author  ��  ��
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
			//���õ��¼�����
			SetEvent(m_hEvent[0]);
			delete pListen;
			InterlockedDecrement(&m_nLiseterNumber);
			return S_OK;
		} // ���� if(pListen->GetFd() == nFd)
	}// ���� for(it = m_Listen.begin(); it != m_Listen.end(); it++)
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
		}// ���� for(it = m_Listen.begin(); it != m_Listen.end(); it++)
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
	} // ���� for(i = 0; i < m_Listen.size(); i++)
	UnLock();
	ResetEvent(m_hEvent[0]);
	return S_OK;
}

int CManageListen::HandleIO(int nPos)
{
	int nRet = S_OK;
	// ��ȡ���巢���������¼�
	WSANETWORKEVENTS hEvent;
	CEventTCPListenSocket * pListen = (CEventTCPListenSocket * )m_Listen[nPos];
	do
	{
		if(SOCKET_ERROR == ::WSAEnumNetworkEvents(pListen->GetFd(), pListen->GetEvent(), &hEvent))
		{
			TRACE(_T("WSAEnumNetworkEvents error:%d\n"), WSAGetLastError());
			break;
		}// ���� if(SOCKET_ERROR == ::WSAEnumNetworkEvents(pListen->GetFd(), pListen->GetEvent(), &hEvent))

		TRACE(_T("HandleIO:%d\n"), hEvent.lNetworkEvents);

		if(hEvent.lNetworkEvents & FD_ACCEPT)//��������
		{
			if(hEvent.iErrorCode[FD_ACCEPT_BIT] == 0)
			{

				CTCPSocket * pSock = (CTCPSocket * )pListen->Accept();
				TRACE(_T("��������:%s\n"), pSock->GetPeerEndpoint().c_str());

				m_ManageNet->AddConncet(pSock);
			}
			else
			{
				ASSERT(0);
				//break;
			}// ���� if(hEvent.iErrorCode[FD_ACCEPT_BIT] == 0)

		}
		
		if(hEvent.lNetworkEvents & FD_CLOSE)	// �׽��ֹر�
		{
			TRACE(_T("�ر�����\n"));
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
		//	�ȴ������¼�
		int nIndex = ::WSAWaitForMultipleEvents(
			nHandleNum, pThis->m_hEvent, FALSE, WSA_INFINITE, FALSE);
		if(WSA_WAIT_FAILED == nIndex || WSA_WAIT_TIMEOUT == nIndex || WAIT_IO_COMPLETION == 0)
		{
			if(bExit)
			{
				TRACE(_T("�����˳�,�߳̽���.\n"));
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
			if(bExit)
			{
				TRACE(_T("�����˳�,�߳̽���.\n"));
				return 1;
			} // ���� if(bExit)
			nIndex = ::WSAWaitForMultipleEvents(1, &pThis->m_hEvent[i], TRUE, 0, FALSE);
			if(nIndex == WSA_WAIT_FAILED || nIndex == WSA_WAIT_TIMEOUT)
			{
				continue;
			}

			if(0 == i)				// hEvents[0]���ţ��߳��˳�
			{
				if(bExit)
				{
					TRACE(_T("�����˳�,�߳̽���.\n"));
					return 1;
				} // ���� if(bExit)
				pThis->RebuildArray();
				// ���û�пͻ�I/OҪ�����ˣ����߳��˳�
				if(0 == pThis->GetListenNumber())
				{
					TRACE(_T("Exit Process thread.\n"));
					pThis->m_pExit = NULL;
					return 2;
				}
				//��Ϊ�ƶ����¼������������κ�������о�����ţ�����žͻᷢ������
				//�����˳�����������Ƿ������Ŷ���
				break; 
			}

			// ���Ҷ�Ӧ���׽��ֶ���ָ�룬����HandleIO���������¼�
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
				TRACE(_T("�¼���������\n"));
			} // ���� if(i < nHandleNum)

		} // ���� for(int i = nIndex; i < nHandleNum; i++)
	}// ���� while(TRUE)

	pThis->m_pExit = NULL;

	return nRet;
}