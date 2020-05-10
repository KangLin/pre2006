#include "thread.h"

#ifdef _WIN32

thread_t create_thread(void * (*thread_function)(void * ), void * para)
{
	return CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)thread_function, para, NULL, NULL);
}

#endif // ���� #ifdef _WIN32

#ifdef __LINUX__
thread_t create_thread(void * (*thread_function)(void * ), void * para)
{
	thread_t hThread;
	int nRet;
	nRet = pthread_create(&hThread, NULL, thread_function, para);
	if(nRet)
	{
		return(pthread_t)NULL;
	}
	else
	{
		return hThread;
	} // ���� if(nRet)
}
#endif // ���� #ifdef __LINUX__