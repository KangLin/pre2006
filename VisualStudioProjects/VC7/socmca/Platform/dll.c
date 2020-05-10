#include "dll.h"

#ifdef _WIN32
dll_t load_library(LPCTSTR lpFileName)
{
	return LoadLibrary(lpFileName);
}

int free_library(dll_t hDll)
{
	return !FreeLibrary(hDll);
}

void * get_function(dll_t hDll, LPCTSTR lpFunName)
{
	return GetProcAddress(hDll, (LPCSTR)lpFunName);
}

#endif // ½áÊø #ifdef _WIN32

#ifdef __LINUX__
dll_t load_library(LPCTSTR lpFileName)
{
	return dlopen(lpFileName, RTLD_NOW);
}

int free_libary(dll_t hDll)
{
	return dlclose(hDll);
}

void* get_function(dll_t hDll, LPCTSTR lpFunName)
{
	void * f;
	f = dlsym(hDll, lpFunName);
	if(dlerror())
	{
		return NULL;
	}// ½áÊø if(dlerror())
	return f;
}
#endif // ½áÊø #ifdef __LINUX__
