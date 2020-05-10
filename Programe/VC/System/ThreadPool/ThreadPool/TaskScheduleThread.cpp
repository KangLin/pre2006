#include "StdAfx.h"
#include "TaskScheduleThread.h"
#include "ThreadPool.h"

CTaskScheduleThread::CTaskScheduleThread(void * pPara): CThread(pPara)
{
	m_bExit = FALSE;
	m_bBusy = FALSE;
}

CTaskScheduleThread::~CTaskScheduleThread(void)
{
	m_bBusy = TRUE;
	m_bExit = TRUE;
	while(m_bBusy)
	{
		Sleep(10);
	}
}

int CTaskScheduleThread::Run(void * pPara)
{
	//TRACE(_T("in CTaskScheduleThread::Run thread[0x%x]\n"), GetID());
	CThreadPool * pThreadPool = (CThreadPool * )pPara;
	m_bBusy = TRUE;
	while(!m_bExit)
	{
		TRACE(_T("�̳߳��е�ǰ���߳���:%d\n"), pThreadPool->GetNumThreads());
		CTask * pTask = pThreadPool->GetTask();
		if(NULL == pTask)
		{
			pThreadPool->OnIDLE();
			continue;
		}// ���� if(NULL == pTask)

		CWorkerThread * pWorkerThread = NULL;
		while(NULL == pWorkerThread)
		{
			pWorkerThread = pThreadPool->GetWorkerThread();
			if(NULL == pWorkerThread)
			{
				//�̲߳����������߳�
				if(S_OK != pThreadPool->AddWorkerThread())
				{
					Sleep(100);
				} // ���� if(!pThread->IsBusy())
			}// ���� (S_OK != AddThread())
		}

		pWorkerThread->AssigTask(pTask);
	}// ���� while(TRUE)

	m_bBusy = FALSE;

	return S_OK;
}
