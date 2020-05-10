#pragma once
#include "Thread.h"

class CTaskScheduleThread : public CThread
{
public:
	CTaskScheduleThread(void * pPara = NULL);
	virtual ~CTaskScheduleThread(void);

	virtual int Run(void * pPara);

private:
	BOOL m_bExit; //�߳��˳���־
	BOOL m_bBusy; //�߳��Ƿ�æ
};
