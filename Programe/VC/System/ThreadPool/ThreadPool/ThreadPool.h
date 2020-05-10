/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    ThreadPool.h
\brief   线程池类头文件
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年9月6日  11:16:44
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
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
	//设置线程池能容纳的最大线程数
	int SetMaxNumThreads(int nMax);
	//得到线程池能容纳的最大线程数
	int GetMaxNumThreads();
	//得到线程池中当前的线程数
	int GetNumThreads();

	//增加线程到线程队列中
	int AddWorkerThread();
	//从工作线程队列中取出空闲的线程
	CWorkerThread * GetWorkerThread();
	//删除所有工作线程
	int DeleteWorkerThread();

	//增加任务到任务队列中
	int AddTask(CTask * pTask);
	//得到任务队列中的第一个任务的指针
	CTask * GetTask();

	virtual int OnIDLE();

private:
	unsigned int m_nCurThread;      //当前线程个数
	unsigned int m_nMinThread;      //起始线程数
	unsigned int m_nMaxThread;      //最大线程数
	queue < CWorkerThread * > m_WorkerThreadQueue;
	CLock m_LockWork;

	queue < CTask * > m_TaskQueue;  //任务队列
	CLock m_LockTask;

	//增加线程到线程队列中
	int AddThread(CWorkerThread * pThread);
	//调度线程
	CTaskScheduleThread * m_pTashScheduleThread;
};

#endif //__THREADPOOL_H_KL_2008_09_04__
