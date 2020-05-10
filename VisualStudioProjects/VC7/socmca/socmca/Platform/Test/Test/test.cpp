// Test.cpp : Defines the entry point for the console application.
//
#ifdef _WIN32
#include "stdafx.h"
#endif

#include <stdio.h>

#ifdef _WIN32
#include "..\..\dll.h"
#include "..\..\thread.h"
#include "..\..\synchronization.h"
#endif
#ifdef __LINUX__
#include <unistd.h>
#include "dll.h"
#include "thread.h"
#include "synchronization.h"
#endif // 结束 #ifdef __LINUX__

#ifdef _WIN32
#define sleep(x) Sleep(x * 1000)
#endif // 结束 #ifdef _WIN32

void test_dll()
{
	dll_t hDll;
	void * (*fun)();

#ifdef _WIN32
	TCHAR szDll[] = _T("dll");
#endif
#ifdef __LINUX__
	char szDll[] = _T("/home/yd104/Platform/lib/.libs/libshow.so");
#endif // 结束 #ifdef __LINUX__

	hDll = load_library(szDll);
	if(!hDll)
	{
		_tprintf(_T("load library fail.\n"));
		return;
	} // 结束 if(!hDll)
	fun = (void * (*)())get_function(hDll, "show");
	if(!fun)
	{
		_tprintf(_T("get function fail.\n"));
		return;
	} // 结束 if(!fun)
	fun();
	if(0 != free_library(hDll))
	{
		_tprintf(_T("free library fail.\n"));
	} // 结束 if(0 != free_library(hDll))
}

DWORD new_thread(void * )
{
	_tprintf(_T("start thread....\n"));
	sleep(1);
	_tprintf(_T("end thread...\n"));
	
	return 600;
}

DWORD exit_thread(void * )
{
	_tprintf(_T("start exit_thread....\n"));
	sleep(1);
	thread_exit(100);
	_tprintf(_T("end exit_thread...\n"));

	return 200;	
}

DWORD terminate_thread(void * )
{
	_tprintf(_T("start terminate_thread....\n"));
	while(1)
	{
		;
	}// 结束 while(1)
	_tprintf(_T("end terminate_thread....\n"));
}

void test_thread()
{
	thread_t hThread;
	thread_create(&hThread, new_thread, NULL);
	if(hThread == NULL)
	{
		_tprintf(_T("create thread fail\n"));
		return;
	}// 结束 if(hThread == NULL)
	thread_create(&hThread, exit_thread, NULL);
	if(hThread == NULL)
	{
		_tprintf(_T("create exit thread fail\n"));
		return;
	}// 结束 if(hThread == NULL)
	thread_create(&hThread, terminate_thread, NULL);
	if(hThread == NULL)
	{
		_tprintf(_T("create terminate thread fail\n"));
		return;
	}// 结束 if(hThread == NULL)
	thread_terminate(hThread);
	
}

struct MUTEX_NUM
{
	int num;
	mutex_t m;
};

DWORD mutex_thread(void * pnum)
{
	MUTEX_NUM * num = (MUTEX_NUM * )pnum;
	while(1)
	{
		mutex_lock(num->m);
		num->num++;
		_tprintf(_T("mutex_thread:%d\n"), num->num);
		mutex_unlock(num->m);
		
	}// 结束 while(1)
	return 0;
}

void test_mutex()
{
	MUTEX_NUM num;
	num.num = 0;
	mutex_init(&num.m);
	thread_t hThread;
	thread_create(&hThread, mutex_thread, &num);
	int i;
	for(i = 0; i < 100; i++)
	{
		mutex_lock(num.m);
		num.num ++;
		_tprintf(_T("test_mutex:%d\n"), num.num);
		mutex_unlock(num.m);
	}// 结束 for(i = 0; i < 10000; i++)
	thread_terminate(hThread);
}

#ifdef _WIN32
int _tmain(int argc, _TCHAR * argv[])
#endif
#ifdef __LINUX__
int main(int argc, char * argv[])
#endif // 结束 #ifdef __LINUX__
{
	_tprintf(_T("start mutex test\n"));
	test_mutex();
	_tprintf(_T("start dll test\n"));
	test_dll();
	_tprintf(_T("start thread test\n"));
	test_thread();
	sleep(8);

	_tprintf(_T("end test\n"));
	return 0;
}
