#ifndef __TYPE_H_KL_2007_7_2__
#define __TYPE_H_KL_2007_7_2__

#pragma once

#include <string>
#include "Exception.h"

#ifndef _tstring
#ifdef _UNICODE
#define _tstring std::wstring
#else
#define _tstring std::string
#endif
#endif

#undef S_OK
#define S_OK 0
#undef S_FALSE
#define S_FALSE -1

#include <windows.h>
#ifndef ASSERT
#ifdef _DEBUG
#define ASSERT _ASSERT
#else
#define ASSERT(x)((void)0)
#endif
#endif

#ifndef TRACE
#ifdef _DEBUG
#define TRACE _tprintf //CDebugInfo(__FILE__, __LINE__)
#else
#define TRACE(x) 
#endif // ½áÊø #ifdef _DEBUG
#endif

#undef LOG
#ifdef _DEBUG
#define LOG PRINTF //CDebugInfo(__FILE__, __LINE__)
#else
#define LOG(x)
#endif // ½áÊø #ifdef _DEBUG
#define MAX_BUFFER 1024


#endif //__TYPE_H_KL_2007_7_2__