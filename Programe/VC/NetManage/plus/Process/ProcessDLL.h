/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    ProcessDLL.h
\brief   进程DLL的导出函数头文件
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年8月14日  17:16:25
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#ifndef __PROCESSDLL_H_KL_2008_08_14__
#define __PROCESSDLL_H_KL_2008_08_14__

#pragma once

extern "C" _stdcall INT DoInitalize();
extern "C" _stdcall INT DoCommand(DWORD dwCmd, CCommand * pCmd);
extern "C" _stdcall INT DoEnd();

extern "C" _stdcall INT SetContext(void* pContext);

#endif //__PROCESSDLL_H_KL_2008_08_14__
