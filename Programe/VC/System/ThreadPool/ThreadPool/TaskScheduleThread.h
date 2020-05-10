#pragma once
#include "Thread.h"

class CTaskScheduleThread : public CThread
{
public:
	CTaskScheduleThread(void * pPara = NULL);
	virtual ~CTaskScheduleThread(void);

	virtual int Run(void * pPara);

private:
	BOOL m_bExit; //线程退出标志
	BOOL m_bBusy; //线程是否忙
};
