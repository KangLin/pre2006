/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    WorkThread.h
\brief   �̳߳��еĹ����߳�,��Ҫ��������ɷ��ɵ�����(�߳�������Ĺ�ϵ��һ��һ)
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��9��4��  16:55:13
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
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
	//����߳��Ƿ�æ
	BOOL IsBusy();
	//���߳��������������߳����еı�������
	BOOL AssigTask(CTask * pTask);

	//���������߳�
	virtual int Stop();

	virtual int Run(void * pPara);

private:
	CTask * m_pTask;  //�������ָ��
	BOOL m_bBusy;     //���б�־
	CLock m_lockBusy;
	HANDLE m_hEvent;  //�߳�ִ���¼�	
	BOOL m_bExit;     //�߳��Ƿ��˳���־
};

#endif //__WORKTHREAD_H_KL_2007_09_04__
