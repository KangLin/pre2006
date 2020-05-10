// Test.cpp : Defines the entry point for the console application.
//
#ifdef _WIN32
#include "stdafx.h"
#endif
#include <stdio.h>

#ifdef _WIN32
#include "..\..\dll.h"
#include "..\..\thread.h"
#endif
#ifdef __LINUX__
#include <unistd.h>
#include "dll.h"
#include "thread.h"
#endif // 结束 #ifdef __LINUX__

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

	hDll = load_library(_T("dll"));
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
	free_library(hDll);
}

DWORD new_thread(void * )
{
	_tprintf(_T("start thread...."));
	Sleep(2000);
	_tprintf(_T("end thread..."));
	
	return 600;
}

void test_thread()
{
	thread_t hThread;
	hThread = thread_create(new_thread, NULL);
	return;
}

#ifdef _WIN32
int _tmain(int argc, _TCHAR * argv[])
#endif
#ifdef __LINUX__
int main(int argc, char * argv[])
#endif // 结束 #ifdef __LINUX__
{
	test_dll();
	test_thread();
	Sleep(6000);
	return 0;
}
