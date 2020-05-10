#ifndef __DLL_H_KL__
#define __DLL_H_KL__

#pragma once

#ifdef _WIN32
#include <windows.h>
#endif // 结束 #ifdef _WIN32

#ifdef __LINUX__
#include <dlfcn.h>
#include "tchar.h"
#endif // 结束 #ifdef __LINUX__


#ifdef _WIN32
typedef HMODULE dll_t;
#endif // 结束 #ifdef _WIN32

#ifdef __LINUX__
typedef void * dll_t;
#endif // 结束 #ifdef __LINUX__

/*******************************************************************************************************
函数名：load_library
描  述：加载指定的动态链接库
参  数：
        LPCTSTR lpFileName：动态库文件名
返回值：类型为 dll_t 。成功返回动态库句柄；失败返回NULL。
版  本：1.0
作  者：康  林
时  间：2006年10月23日 11:46:17
*******************************************************************************************************/
dll_t load_library(LPCTSTR lpFileName);

/*******************************************************************************************************
函数名：free_library
描  述：关闭动态链接库
参  数：
        dll_t hDll：动态库句柄
返回值：类型为 int 。成功返回0，否则返回非零。
版  本：1.0
作  者：康  林
时  间：2006年10月23日 11:49:50
*******************************************************************************************************/
int free_library(dll_t hDll);

//得到指定的函数指针
void* get_function(dll_t hDll, LPCSTR lpFunName);

#endif //__DLL_H_KL__
