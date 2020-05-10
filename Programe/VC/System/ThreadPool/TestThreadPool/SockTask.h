#pragma once

#include "..\ThreadPool\Task.h"

class CSockTask : public CTask
{
public:
	CSockTask(void);
	virtual ~CSockTask(void);

	virtual int Run();
};
