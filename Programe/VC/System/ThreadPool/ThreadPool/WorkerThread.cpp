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
		CTException e(_T("建立事件错误"), GetLastError());
		TRACE(_T("%s\n"), e.what());
		throw e;
	} // 结束 if(NULL == m_hEvent)
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
	} // 结束 if(!bRet)
	return S_OK;
}

/*!
\brief   判断线程是否忙，如果不忙，则把它置为忙。
\param   无
\return  类型为 BOOL 。
\version 1.0
\author  康  林
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
\param   BOOL bBusy：
\return  类型为 BOOL 。
\version 1.0
\author  康  林
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
\brief   分配任务给线程，对分配的任务进行处理
\param   CTask * pTask：任务指针
\return  类型为 int 。成功返回S_OK,如果设置事件失败，则返回S_FALSE。
\version 1.0
\author  康  林
\date    2007-9-4 16:51:39
*/
int CWorkerThread::AssigTask(CTask * pTask)
{
	//线程已退出，但又分配了任务
	ASSERT(!m_bExit);
	ASSERT(pTask);
	if(NULL == pTask || m_bExit)
	{
		return S_FALSE;
	} // 结束 if(NULL == pTask || m_bExit)
	m_pTask = pTask;
	SetBusy();
	BOOL bRet = SetEvent(m_hEvent);
	if(!bRet)
	{
		SetBusy(FALSE);
		m_pTask = NULL;
		return S_FALSE;
	}// 结束 if(!bRet)
	return S_OK;
}

/*!
\brief   线程主体
\param   void * pPara：主程序传给线程的参数
\return  类型为 int 。
\version 1.0
\author  康  林
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
		}// 结束 if(m_bExit)

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
				case CTask::INSERT_BACK:  //任务还有用,插入到任务队列最后
					{
						CThreadPool * pThreadPool = (CThreadPool * )pPara;
						pThreadPool->AddTask(m_pTask);
					}
					break;
				case CTask::EXIT:         //任务退出
					//TRACE(_T("任务正常退出\n"));
					break;
				case CTask::ERR:
					//TRACE(_T("任务出错退出\n"));
					break;
				default:
					break;
				}
			}// 结束 if(m_pTask)
		}// 结束 if(WAIT_OBJECT_0 == dwRet)

		m_pTask = NULL;
		SetBusy(FALSE);

	}
	while(!m_bExit);

	//TRACE(_T("workthread [0x%x] exit\n"), GetID());

	return S_OK;
}
