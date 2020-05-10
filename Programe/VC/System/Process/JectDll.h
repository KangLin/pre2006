/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    JectDll.h
\brief   远程注入DLL库
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年6月2日  22:01:01
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#ifndef __JECTDLL_H_KL_2007_06_02__
#define __JECTDLL_H_KL_2007_06_02__

#pragma once

#ifdef UNICODE
#define InjectLib InjectLibW
#define EjectLib  EjectLibW
#else
#define InjectLib InjectLibA
#define EjectLib  EjectLibA
#endif   // !UNICODE

BOOL WINAPI InjectLibA(DWORD dwProcessId, PCSTR pszLibFile);
BOOL WINAPI InjectLibW(DWORD dwProcessId, PCWSTR pszLibFile);
BOOL WINAPI EjectLibA(DWORD dwProcessId, PCSTR pszLibFile);
BOOL WINAPI EjectLibW(DWORD dwProcessId, PCWSTR pszLibFile);

#endif