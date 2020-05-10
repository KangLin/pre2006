#include "StdAfx.h"
#include "WorkerThread.h"
#include "ThreadPool.h"

CWorkerThread::CWorkerThread(void * pPara) : CThread(pPara)
{
	m_bExit = FALSE;
	m_bBusy = FALSE;
	m_pTask = NULL;

	m_hEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
	if(NULL == m_hEvent)
	{
		CTException e(_T("�����¼�����"), GetLastError());
		TRACE(_T("%s\n"), e.what());
		throw e;
	} // ���� if(NULL == m_hEvent)
}

CWorkerThread::~CWorkerThread(void)
{
	//TRACE(_T("start CWorkerThread::~CWorkerThread, thread[0x%x]\n"), GetID());
	Stop();
	while(IsBusy())
	{
		Sleep(10);
		/*Stop();*/
	}
	//TRACE(_T("end CWorkerThread::~CWorkerThread, thread[0x%x]\n"), GetID());
}

int CWorkerThread::Stop()
{
	SetBusy();
	m_bExit = TRUE;
	bool bRet = SetEvent(m_hEvent);
	if(!bRet)
	{
		TRACE(_T("SetEvent error:%d\n"), GetLastError());
		return S_FALSE;
	} // ���� if(!bRet)
	return S_OK;
}

/*!
\brief   �ж��߳��Ƿ�æ�������æ���������Ϊæ��
\param   ��
\return  ����Ϊ BOOL ��
\version 1.0
\author  ��  ��
\date    2007-9-4 16:50:42
*/
BOOL CWorkerThread::IsBusy()
{
	BOOL bBusy;
	m_lockBusy.Lock();
	bBusy = m_bBusy;
	m_lockBusy.UnLock();
	return bBusy;
}

/*!
\brief   SetBusy
\param   BOOL bBusy��
\return  ����Ϊ BOOL ��
\version 1.0
\author  ��  ��
\date    2008-4-12 14:53:25
*/
BOOL CWorkerThread::SetBusy(BOOL bBusy /* = TRUE */)
{
	m_lockBusy.Lock();
	m_bBusy = bBusy;
	m_lockBusy.UnLock();
	return bBusy;
}

/*!
\brief   ����������̣߳��Է����������д���
\param   CTask * pTask������ָ��
\return  ����Ϊ int ���ɹ�����S_OK,��������¼�ʧ�ܣ��򷵻�S_FALSE��
\version 1.0
\author  ��  ��
\date    2007-9-4 16:51:39
*/
int CWorkerThread::AssigTask(CTask * pTask)
{
	//�߳����˳������ַ���������
	ASSERT(!m_bExit);
	ASSERT(pTask);
	if(NULL == pTask || m_bExit)
	{
		return S_FALSE;
	} // ���� if(NULL == pTask || m_bExit)
	m_pTask = pTask;
	SetBusy();
	BOOL bRet = SetEvent(m_hEvent);
	if(!bRet)
	{
		SetBusy(FALSE);
		m_pTask = NULL;
		return S_FALSE;
	}// ���� if(!bRet)
	return S_OK;
}

/*!
\brief   �߳�����
\param   void * pPara�������򴫸��̵߳Ĳ���
\return  ����Ϊ int ��
\version 1.0
\author  ��  ��
\date    2007-9-4 16:52:59
*/
int CWorkerThread::Run(void * pPara)
{
	do
	{
		DWORD dwRet = ::WaitForSingleObject(m_hEvent, INFINITE);
		if(m_bExit)
		{
			TRACE(_T("thread [0x%x]WaitForSingleObject get signaled and exit\n"), GetID());
			SetBusy(FALSE);
			break;
		}// ���� if(m_bExit)

		//TRACE(_T("thread [0x%x] run ....\n"), GetID());

		SetBusy(TRUE);

		if(WAIT_OBJECT_0 == dwRet)
		{
			ASSERT(m_pTask);
			if(m_pTask)
			{
				int nRet = m_pTask->Run();
				switch(nRet)
				{
				case CTask::INSERT_BACK:  //��������,���뵽����������
					{
						CThreadPool * pThreadPool = (CThreadPool * )pPara;
						pThreadPool->AddTask(m_pTask);
					}
					break;
				case CTask::EXIT:         //�����˳�
					//TRACE(_T("���������˳�\n"));
					break;
				case CTask::ERR:
					//TRACE(_T("��������˳�\n"));
					break;
				default:
					break;
				}
			}// ���� if(m_pTask)
		}// ���� if(WAIT_OBJECT_0 == dwRet)

		m_pTask = NULL;
		SetBusy(FALSE);

	}
	while(!m_bExit);

	//TRACE(_T("workthread [0x%x] exit\n"), GetID());

	return S_OK;
}
