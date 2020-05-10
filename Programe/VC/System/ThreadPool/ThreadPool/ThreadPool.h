/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    ThreadPool.h
\brief   �̳߳���ͷ�ļ�
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��9��6��  11:16:44
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/

#ifndef __THREADPOOL_H_KL_2008_09_04__
#define __THREADPOOL_H_KL_2008_09_04__

#pragma once

#include ".\WorkerThread.h"
#include "TaskScheduleThread.h"
#include <queue>
using namespace std;

#define MAX_THREAD 250

class CThreadPool
{
public:
	CThreadPool(int nNumThreads = 16);
	virtual ~CThreadPool();

	int Init();
	//�����̳߳������ɵ�����߳���
	int SetMaxNumThreads(int nMax);
	//�õ��̳߳������ɵ�����߳���
	int GetMaxNumThreads();
	//�õ��̳߳��е�ǰ���߳���
	int GetNumThreads();

	//�����̵߳��̶߳�����
	int AddWorkerThread();
	//�ӹ����̶߳�����ȡ�����е��߳�
	CWorkerThread * GetWorkerThread();
	//ɾ�����й����߳�
	int DeleteWorkerThread();

	//�����������������
	int AddTask(CTask * pTask);
	//�õ���������еĵ�һ�������ָ��
	CTask * GetTask();

	virtual int OnIDLE();

private:
	unsigned int m_nCurThread;      //��ǰ�̸߳���
	unsigned int m_nMinThread;      //��ʼ�߳���
	unsigned int m_nMaxThread;      //����߳���
	queue < CWorkerThread * > m_WorkerThreadQueue;
	CLock m_LockWork;

	queue < CTask * > m_TaskQueue;  //�������
	CLock m_LockTask;

	//�����̵߳��̶߳�����
	int AddThread(CWorkerThread * pThread);
	//�����߳�
	CTaskScheduleThread * m_pTashScheduleThread;
};

#endif //__THREADPOOL_H_KL_2008_09_04__
