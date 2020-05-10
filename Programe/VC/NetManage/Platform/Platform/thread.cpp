#include "thread.h"

#ifdef _WIN32

int thread_create(thread_t * hThread, DWORD thread_function(void * ), void * para)
{
	*hThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)thread_function, para, NULL, NULL);
	if(*hThread)
	{
		return 0; 
	}
	else
	{
		return 1;
	} // ½áÊø if(*hThread)
}

void thread_exit(DWORD dwExit)
{
	return ::ExitThread(dwExit);
}

int thread_terminate(thread_t hTread)
{
	return !TerminateThread(hTread, 0);
}

#endif // ½áÊø #ifdef _WIN32



#ifdef __LINUX__

int thread_create(thread_t * hThread, DWORD thread_function(void * ), void * para)
{
	return pthread_create(hThread, NULL, (void * (*)(void * ))thread_function, para);
}

void thread_exit(DWORD dwExit)
{
	return pthread_exit(&dwExit);
}

int thread_terminate(thread_t hTread)
{
	return pthread_cancel(hTread);
}

#endif // ½áÊø #ifdef __LINUX__
