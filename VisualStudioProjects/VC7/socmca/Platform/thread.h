#ifndef __THREAD_H_KL__
#define __THREAD_H_KL__

#pragma once

#ifdef _WIN32
#include <windows.h>
#endif // 结束 #ifdef _WIN32

#ifdef __LINUX__
#include <pthread.h>
#include "tchar.h"
#endif // 结束 #ifdef __LINUX__


#ifdef _WIN32
typedef HANDLE thread_t;
#endif // 结束 #ifdef _WIN32

#ifdef __LINUX__
typedef pthread_t thread_t;
#endif // 结束 #ifdef __LINUX__

/*******************************************************************************************************
函数名：thread_create
描  述：建立线程
参  数：
		thread_t * hThread            ：线程句柄。
        DWORD thread_function(void * )：线程函数。
		void * para                   ：传给线程函数的参数。
返回值：类型为 thread_t 。成功返回线程句柄。失败返回NULL。
版  本：1.0
作  者：康  林
时  间：2006年10月23日 17:33:22
*******************************************************************************************************/
int thread_create(thread_t * hThread, DWORD thread_function(void * ), void * para);

/*******************************************************************************************************
函数名：thread_exit
描  述：线程退出
参  数：
        void * retval：退出代码
返回值：类型为 void 。
版  本：1.0
作  者：康  林
时  间：2006年10月25日 9:58:46
*******************************************************************************************************/
void thread_exit(DWORD dwExit);

int thread_terminate(thread_t hTread);

#endif //__THREAD_H_KL__
