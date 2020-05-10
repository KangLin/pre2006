/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    WorkThread.h
\brief   线程池中的工作线程,主要功能是完成分派的任务(线程与任务的关系是一对一)
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年9月4日  16:55:13
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#ifndef __WORKTHREAD_H_KL_2007_09_04__
#define __WORKTHREAD_H_KL_2007_09_04__

#pragma once
#include "thread.h"
#include "task.h"
#include "Lock.h"

class CWorkerThread : public CThread
{
public:
	CWorkerThread(void * pPara = NULL);
	virtual ~CWorkerThread(void);

	BOOL SetBusy(BOOL bBusy = TRUE);
	//检查线程是否忙
	BOOL IsBusy();
	//给线程设置任务，这是线程运行的必须条件
	BOOL AssigTask(CTask * pTask);

	//结束工作线程
	virtual int Stop();

	virtual int Run(void * pPara);

private:
	CTask * m_pTask;  //任务对象指针
	BOOL m_bBusy;     //空闲标志
	CLock m_lockBusy;
	HANDLE m_hEvent;  //线程执行事件	
	BOOL m_bExit;     //线程是否退出标志
};

#endif //__WORKTHREAD_H_KL_2007_09_04__
