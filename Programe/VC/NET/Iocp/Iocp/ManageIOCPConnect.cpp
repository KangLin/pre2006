#include "StdAfx.h"
#include "ManageIOCPConnect.h"
#include "IOCPConnect.h"

CManageIOCPConnect::CManageIOCPConnect(void)
{
	m_hCompletion = NULL;
	SetThreadNumber(1);
	Initalize();
}

CManageIOCPConnect::~CManageIOCPConnect(void)
{
	//����:���������߳�
}

int CManageIOCPConnect::Initalize()
{
	bool bInital = FALSE;
	int nThreadNumber = 0;
	if(bInital)
	{
		TRACE(_T("��ɶ˿��Ѿ���ʼ����\n"));
		return S_FALSE;
	}// ���� if(bInital)

	int nRet = S_OK;
	int i = 0;
	DWORD dwThreadID = 0;
	SYSTEM_INFO SystemInfo;

	// ������ɶ˿ڶ���
	m_hCompletion = ::CreateIoCompletionPort(INVALID_HANDLE_VALUE, 0, 0, 0);

	// Determine how many processors are on the system.

	GetSystemInfo(&SystemInfo);
	nThreadNumber = SystemInfo.dwNumberOfProcessors * m_nThread;


	// Create worker threads based on the number of processors available on the
	// system. Create two worker threads for each processor.

	for(i = 0; i < nThreadNumber; i++)
	{
		HANDLE ThreadHandle;

		// Create a server worker thread and pass the completion port to the thread.

		if((ThreadHandle = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)CompleteIOWorkThread, this,
			0, &dwThreadID)) == NULL)
		{
			nRet = GetLastError();
			TRACE(_T("CreateThread() failed with error %d\n"), nRet);
			return nRet;
		}
		m_hThread.push_back(ThreadHandle);
	}

	bInital = TRUE;

	return nRet;
}

int CManageIOCPConnect::SetThreadNumber(int nNum /* = 1 */)
{
	m_nThread = nNum;
	return m_nThread;
}

int CManageIOCPConnect::GetThreadNumber() 
{
	return m_nThread;
}

/*!
\brief   Ϊһ����ɶ˿���������
\param   CSocket * pSocket��
\return  ����Ϊ int ��
\version 1.0
\author  ��  ��
\date    2007-9-28 19:10:36
*/
int CManageIOCPConnect::AddConnect(CSocket * pSocket)
{
	int nRet = S_OK;

	ASSERT(pSocket);
	if(NULL == pSocket)
	{
		return S_FALSE;
	}// ���� if(NULL == pSocket)

	CConnect * pConnect = NULL;
	vector < CConnect * > ::iterator it;
	for(it = m_Connect.begin(); it != m_Connect.end(); it++)
	{
		pConnect = *it;
		if(pConnect->m_pSocket == pSocket)
		{
			TRACE(_T("�������Ѿ�����\n"));
			return 1;
		} // ���� if(pConnect->m_pSock == pSocket)
	} // ���� for(it = m_Connect.begin(); it != m_Connect.end(); it++)

	Lock();
	try
	{
		pConnect = new CIOCPConnect(pSocket, m_hCompletion);
		if(pConnect)
		{
			try
			{
				m_Connect.push_back(pConnect);
				InterlockedIncrement(&m_ConnectNumber);
				InterlockedIncrement(&m_TotalConnectNumber);
			}
			catch(...)
			{
				nRet = S_FALSE;
			}
		}// ���� if(pConnect)
	}
	catch(CTException e)
	{
		TRACE(_T("�쳣:(%d)%s\n"), e.GetErr(), e.what());
		nRet = S_FALSE;
	}
	UnLock();

	return nRet;
}

DWORD CManageIOCPConnect::CompleteIOWorkThread(void * pPara)
{
	CManageIOCPConnect * pThis = (CManageIOCPConnect * )pPara;
	DWORD dwBytesTransferred = 0;
	CIOCPConnect * pConnect;
	LPOVERLAPPED pIoData = NULL;
	BOOL bExit = FALSE;
	pThis->m_pExit = &bExit;

	int nRet = 0;
	while(TRUE)
	{
		if(bExit)
		{
			return 1;
		} // ���� if(bExit)
		if(GetQueuedCompletionStatus(pThis->m_hCompletion, &dwBytesTransferred,
			(LPDWORD)&pConnect, (LPOVERLAPPED * )&pIoData, INFINITE) == 0)
		{
			DWORD dwRet = GetLastError();
			TRACE(_T("GetQueuedCompletionStatus failed with error %d\n"), dwRet);
			pThis->m_pExit = NULL;
			return dwRet;
		}
		if(bExit)
		{
			return 1;
		} // ���� if(bExit)
		nRet = pConnect->OnHandleIOEvent(dwBytesTransferred, pIoData);
		switch(nRet)
		{
		case 1:
		case 2:
			break;
		case 3:
			pThis->RemoveConnect(pConnect->m_pSocket);
			break;
		default:
			break;
		}
	}// ���� while(TRUE)

	pThis->m_pExit = NULL;

	return 0;
}