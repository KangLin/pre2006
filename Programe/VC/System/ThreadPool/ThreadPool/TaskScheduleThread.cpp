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
		TRACE(_T("线程池中当前的线程数:%d\n"), pThreadPool->GetNumThreads());
		CTask * pTask = pThreadPool->GetTask();
		if(NULL == pTask)
		{
			pThreadPool->OnIDLE();
			continue;
		}// 结束 if(NULL == pTask)

		CWorkerThread * pWorkerThread = NULL;
		while(NULL == pWorkerThread)
		{
			pWorkerThread = pThreadPool->GetWorkerThread();
			if(NULL == pWorkerThread)
			{
				//线程不够，增加线程
				if(S_OK != pThreadPool->AddWorkerThread())
				{
					Sleep(100);
				} // 结束 if(!pThread->IsBusy())
			}// 结束 (S_OK != AddThread())
		}

		pWorkerThread->AssigTask(pTask);
	}// 结束 while(TRUE)

	m_bBusy = FALSE;

	return S_OK;
}
