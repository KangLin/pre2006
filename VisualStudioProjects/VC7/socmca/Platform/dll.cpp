#include "dll.h"

#ifdef _WIN32
dll_t load_library(LPCTSTR lpFileName)
{
	return LoadLibrary(lpFileName);
}

int free_library(dll_t hDll)
{
	if(FreeLibrary(hDll))
	{
		return 0;
	}
	else
	{
		return 1;
	} // 结束 if(FreeLibrary(hDll))
}

void * get_function(dll_t hDll, LPCSTR lpFunName)
{
	return GetProcAddress(hDll, (LPCSTR)lpFunName);
}

#endif // 结束 #ifdef _WIN32

#ifdef __LINUX__
dll_t load_library(LPCTSTR lpFileName)
{
	return dlopen(lpFileName, RTLD_NOW);
}

int free_library(dll_t hDll)
{
	return dlclose(hDll);
}

void* get_function(dll_t hDll, LPCSTR lpFunName)
{
	void * f;
	f = dlsym(hDll, lpFunName);
	if(dlerror())
	{
		return NULL;
	}// 结束 if(dlerror())
	return f;
}
#endif // 结束 #ifdef __LINUX__
