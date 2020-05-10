// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define TRACE _tprintf
#include <string>

using namespace std;

#ifdef _UNICODE
#define _tstring wstring
#else
#define _tstring string
#endif // ½áÊø #ifdef

// TODO: reference additional headers your program requires here
