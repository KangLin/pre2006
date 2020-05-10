/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    ThreadPool.cpp
\brief   �̳߳���ʵ���ļ�
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��9��6��  11:20:41
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
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
			TRACE(_T("�������߳������"));
			return S_FALSE;
		}
		nRet = pThread->Start();
		if(S_OK != nRet)
		{
			TRACE(_T("�����߳�ʧ��"));
			return nRet;
		}// ���� if(S_OK == nRet)
		nRet = AddThread(pThread);
		if(S_OK != nRet)
		{
			TRACE(_T("���½����̼߳����̶߳��г���"));
			return nRet;
		} // ���� if(S_OK != nRet)
	}// ���� for(i = 0; i < m_nMinThread; i++)

	//���������߳�
	m_pTashScheduleThread = new CTaskScheduleThread(this);
	if(NULL == m_pTashScheduleThread)
	{
		TRACE(_T("�쳣��������������̳߳���"));
		return S_FALSE;
	}// ���� if(NULL == m_pTashScheduleThread)
	nRet = m_pTashScheduleThread->Start();
	return nRet;
}

/*!
\brief   �����̳߳������ɵ�����߳���
\param   int nMax��
\return  ����Ϊ int ��
\version 1.0
\author  ��  ��
\date    2007-9-6 10:35:21
*/
int CThreadPool::SetMaxNumThreads(int nMax)
{
	m_nMaxThread = nMax;
	return S_OK;
}

/*!
\brief   �õ��̳߳������ɵ�����߳���
\param   ��
\return  ����Ϊ int ��
\version 1.0
\author  ��  ��
\date    2007-9-6 10:35:47
*/
int CThreadPool::GetMaxNumThreads()
{
	return m_nMaxThread;
}

/*!
\brief   �õ��̳߳��е�ǰ���߳���
\param   ��
\return  ����Ϊ int ��
\version 1.0
\author  ��  ��
\date    2007-9-6 10:35:03
*/
int CThreadPool::GetNumThreads()
{
	return m_nCurThread;
}

/*!
\brief   �����̵߳��̶߳�����
\param   CWorkThread * pThread���߳�
\return  ����Ϊ int ��
\version 1.0
\author  ��  ��
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
		TRACE(_T("�쳣: CThreadPool::AddThread\n"));
	}
	m_LockWork.UnLock();
	return nRet;
}

/*!
\brief   �ӹ����̶߳�����ȡ�����е��߳�
\param   ��
\return  ����Ϊ CWorkThread * ���ɹ������߳�ָ�룬���򷵻�NULL��
\version 1.0
\author  ��  ��
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
	}// ���� if(nSize <= 0)

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
				}// ���� if(!pThread->IsBusy())			
			}// ���� if(pThread)
			
		}
		catch(...)
		{
			TRACE(_T("�쳣: CThreadPool::GetWorkThread\n"));
		}

		pThread = NULL;
	} // ���� while(nSize--)

	m_LockWork.UnLock();

	return pThread;
}

/*!
\brief   ���ӹ����̣߳�ÿ��������Ϊ��ʼ����ֵ�������ܳ����̳߳����������ֵ��
\param   ��
\return  ����Ϊ int ��
\version 1.0
\author  ��  ��
\date    2007-9-6 10:21:55
*/
int CThreadPool::AddWorkerThread()
{
	int nRet = S_FALSE;
	int nNum = m_nMinThread;
	if(nNum + m_nCurThread > m_nMaxThread)
	{
		nNum = m_nMaxThread - m_nCurThread;
	}// ���� if(nNum + m_nCurThread > m_nMaxThread)

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
				TRACE(_T("�����߳�ʧ��"));
				break;
			}// ���� if(S_OK == nRet)
			nRet = AddThread(pWorkerThread);
			if(nRet != S_OK)
			{
				break;
			} // ���� if(nRet != S_OK)
		}
		else
		{
			nRet = S_FALSE;
			break;
		} // ���� if(pWorkerThread)
	}// ���� for(i = 0; i < nNum; i++)

	return nRet;
}

/*!
\brief   ɾ�����й����߳�
\param   ��
\return  ����Ϊ int ��
\version 1.0
\author  ��  ��
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
	}// ���� for(int i = 0; i < nSize; i++)
	m_LockWork.UnLock();

	return nRet;
}

/*!
\brief   �����������������
\param   CTask * pTask��
\return  ����Ϊ int ��
\version 1.0
\author  ��  ��
\date    2007-9-6 11:09:03
*/
int CThreadPool::AddTask(CTask * pTask)
{
	int nRet = S_OK;
	ASSERT(pTask);
	if(NULL == pTask)
	{
		return S_FALSE;
	}// ���� if(NULL == pTask)

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
\brief   �õ���������еĵ�һ�������ָ�룬����������Ϊ�գ��򷵻�NULL��
\param   ��
\return  ����Ϊ CTask * ��������е�ָ�롣
\version 1.0
\author  ��  ��
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
	} // ���� if(m_TaskQueue.size() > 0)
	m_LockTask.UnLock();
	return pTask;
}

int CThreadPool::OnIDLE()
{
	Sleep(10);
	return S_OK;
}
