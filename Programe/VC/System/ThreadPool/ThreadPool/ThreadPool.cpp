/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    ThreadPool.cpp
\brief   线程池类实现文件
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年9月6日  11:20:41
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#include "stdafx.h"

#include "ThreadPool.h"

CThreadPool::CThreadPool(int nNumThreads)
{
	m_nMaxThread = MAX_THREAD;
	m_nCurThread = 0;
	m_nMinThread = nNumThreads;
	m_pTashScheduleThread = NULL;

}

CThreadPool::~CThreadPool()
{
	TRACE(_T("start CThreadPool::~CThreadPool\n"));
	delete m_pTashScheduleThread;
	DeleteWorkerThread();
	TRACE(_T("CThreadPool::~CThreadPool end\n"));
}

int CThreadPool::Init()
{
	m_nMaxThread = MAX_THREAD;
	m_nCurThread = 0;

	int nRet = S_OK;

	int i = 0;
	for(i = 0; i < m_nMinThread; i++)
	{
		CWorkerThread * pThread = new CWorkerThread(this);
		if(!pThread)
		{
			TRACE(_T("建立新线程类错误"));
			return S_FALSE;
		}
		nRet = pThread->Start();
		if(S_OK != nRet)
		{
			TRACE(_T("建立线程失败"));
			return nRet;
		}// 结束 if(S_OK == nRet)
		nRet = AddThread(pThread);
		if(S_OK != nRet)
		{
			TRACE(_T("把新建立线程加入线程队列出错"));
			return nRet;
		} // 结束 if(S_OK != nRet)
	}// 结束 for(i = 0; i < m_nMinThread; i++)

	//建立调度线程
	m_pTashScheduleThread = new CTaskScheduleThread(this);
	if(NULL == m_pTashScheduleThread)
	{
		TRACE(_T("异常：生成任务调度线程出错"));
		return S_FALSE;
	}// 结束 if(NULL == m_pTashScheduleThread)
	nRet = m_pTashScheduleThread->Start();
	return nRet;
}

/*!
\brief   设置线程池能容纳的最大线程数
\param   int nMax：
\return  类型为 int 。
\version 1.0
\author  康  林
\date    2007-9-6 10:35:21
*/
int CThreadPool::SetMaxNumThreads(int nMax)
{
	m_nMaxThread = nMax;
	return S_OK;
}

/*!
\brief   得到线程池能容纳的最大线程数
\param   无
\return  类型为 int 。
\version 1.0
\author  康  林
\date    2007-9-6 10:35:47
*/
int CThreadPool::GetMaxNumThreads()
{
	return m_nMaxThread;
}

/*!
\brief   得到线程池中当前的线程数
\param   无
\return  类型为 int 。
\version 1.0
\author  康  林
\date    2007-9-6 10:35:03
*/
int CThreadPool::GetNumThreads()
{
	return m_nCurThread;
}

/*!
\brief   增加线程到线程队列中
\param   CWorkThread * pThread：线程
\return  类型为 int 。
\version 1.0
\author  康  林
\date    2007-9-5 16:00:38
*/
int CThreadPool::AddThread(CWorkerThread * pThread)
{
	int nRet = S_OK;
	m_LockWork.Lock();
	try
	{
		m_WorkerThreadQueue.push(pThread);
		m_nCurThread++;
	}
	catch(...)
	{
		nRet = S_FALSE;
		TRACE(_T("异常: CThreadPool::AddThread\n"));
	}
	m_LockWork.UnLock();
	return nRet;
}

/*!
\brief   从工作线程队列中取出空闲的线程
\param   无
\return  类型为 CWorkThread * 。成功返回线程指针，否则返回NULL。
\version 1.0
\author  康  林
\date    2007-9-4 18:07:43
*/
CWorkerThread * CThreadPool::GetWorkerThread()
{
	CWorkerThread * pThread = NULL;
	int nSize = 0;

	m_LockWork.Lock();
	nSize = m_WorkerThreadQueue.size();
	if(nSize <= 0)
	{
		m_LockWork.UnLock();
		return pThread;
	}// 结束 if(nSize <= 0)

	while(nSize--)
	{
		try
		{
			pThread = m_WorkerThreadQueue.front();
			m_WorkerThreadQueue.pop();
			m_WorkerThreadQueue.push(pThread);		
			if(pThread)
			{
				if(!pThread->IsBusy())
				{
					pThread->SetBusy();
					break;
				}// 结束 if(!pThread->IsBusy())			
			}// 结束 if(pThread)
			
		}
		catch(...)
		{
			TRACE(_T("异常: CThreadPool::GetWorkThread\n"));
		}

		pThread = NULL;
	} // 结束 while(nSize--)

	m_LockWork.UnLock();

	return pThread;
}

/*!
\brief   增加工作线程，每次增加数为初始化的值，但不能超过线程池容量的最大值。
\param   无
\return  类型为 int 。
\version 1.0
\author  康  林
\date    2007-9-6 10:21:55
*/
int CThreadPool::AddWorkerThread()
{
	int nRet = S_FALSE;
	int nNum = m_nMinThread;
	if(nNum + m_nCurThread > m_nMaxThread)
	{
		nNum = m_nMaxThread - m_nCurThread;
	}// 结束 if(nNum + m_nCurThread > m_nMaxThread)

	int i = 0;
	for(i = 0; i < nNum; i++)
	{
		CWorkerThread * pWorkerThread = new CWorkerThread(this);
		if(pWorkerThread)
		{
			nRet = pWorkerThread->Start();
			if(S_OK != nRet)
			{
				ASSERT(0);
				TRACE(_T("启动线程失败"));
				break;
			}// 结束 if(S_OK == nRet)
			nRet = AddThread(pWorkerThread);
			if(nRet != S_OK)
			{
				break;
			} // 结束 if(nRet != S_OK)
		}
		else
		{
			nRet = S_FALSE;
			break;
		} // 结束 if(pWorkerThread)
	}// 结束 for(i = 0; i < nNum; i++)

	return nRet;
}

/*!
\brief   删除所有工作线程
\param   无
\return  类型为 int 。
\version 1.0
\author  康  林
\date    2007-9-6 11:19:47
*/
int CThreadPool::DeleteWorkerThread()
{
	int nRet = S_OK;
	m_LockWork.Lock();
	int nSize = m_WorkerThreadQueue.size();
	for(int i = 0; i < nSize; i++)
	{
		CWorkerThread * p = m_WorkerThreadQueue.front();
		delete p;
		m_WorkerThreadQueue.pop();
	}// 结束 for(int i = 0; i < nSize; i++)
	m_LockWork.UnLock();

	return nRet;
}

/*!
\brief   增加任务到任务队列中
\param   CTask * pTask：
\return  类型为 int 。
\version 1.0
\author  康  林
\date    2007-9-6 11:09:03
*/
int CThreadPool::AddTask(CTask * pTask)
{
	int nRet = S_OK;
	ASSERT(pTask);
	if(NULL == pTask)
	{
		return S_FALSE;
	}// 结束 if(NULL == pTask)

	m_LockTask.Lock();
	try
	{
		m_TaskQueue.push(pTask);
	}
	catch(...)
	{
		nRet = FALSE;
	}
	m_LockTask.UnLock();

	return nRet;
}

/*!
\brief   得到任务队列中的第一个任务的指针，如果任务队列为空，则返回NULL。
\param   无
\return  类型为 CTask * 。任务队列的指针。
\version 1.0
\author  康  林
\date    2007-9-6 10:01:26
*/
CTask * CThreadPool::GetTask()
{
	CTask * pTask = NULL;
	m_LockTask.Lock();
	if(m_TaskQueue.size() > 0)
	{
		try
		{
			pTask = m_TaskQueue.front();
			m_TaskQueue.pop();
		}
		catch(...)
		{
			pTask = NULL;
		}
	} // 结束 if(m_TaskQueue.size() > 0)
	m_LockTask.UnLock();
	return pTask;
}

int CThreadPool::OnIDLE()
{
	Sleep(10);
	return S_OK;
}
