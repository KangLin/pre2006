#include "synchronization.h"

#ifdef _WIN32

int mutex_init(mutex_t * m)
{
	*m = CreateMutex(NULL, FALSE, NULL);
	if(*m)
	{
		return 0; 
	}
	else
	{
		return 1; 
	} // ½áÊø if(*m)
}

int mutex_lock(mutex_t m)
{
	switch(WaitForSingleObject(m, INFINITE))
	{
	case WAIT_OBJECT_0:
		return 0;
	default:
		return 1;
	} // ½áÊø switch(WaitForSingleObject(m, INFINITE))
}

int mutex_unlock(mutex_t m)
{
	return !ReleaseMutex(m);
}

#endif

#ifdef __LINUX__

int mutex_init(mutex_t * m)
{
	return pthread_mutex_init(m, NULL);
}

int mutex_lock(mutex_t m)
{
	return pthread_mutex_lock(&m);
}

int mutex_unlock(mutex_t m)
{
	return pthread_mutex_lock(&m);
}


#endif // ½áÊø #ifdef __LINUX__
