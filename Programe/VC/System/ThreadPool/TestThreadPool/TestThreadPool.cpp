// TestThreadPool.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\ThreadPool\ThreadPool.h"
#include "SockTask.h"
#define NUM 200000

int _tmain(int argc, _TCHAR* argv[])
{
	CSockTask task[NUM];
	CThreadPool threadPool;
	threadPool.Init();

	for(int i = 0; i < NUM; i++)
	{
		threadPool.AddTask(&task[i]);
	} // ½áÊø for(int i = 0; i < 20; i++)
	
	Sleep(100);
	return 0;
}

