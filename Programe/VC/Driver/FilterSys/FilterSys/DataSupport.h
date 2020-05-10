/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    DataSupport.h
\brief   对具体数据的操作
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年6月7日  13:48:32
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#ifndef __DATASUPPORT_H_KL_2007_06_06__
#define __DATASUPPORT_H_KL_2007_06_06__

#pragma once

#include "Array.h"

INT CompareCallBack(PDATASTRUCT pDestination, PDATASTRUCT pSource);

INT ClearCallBack(PDATASTRUCT pClear);

INT InsertElement(PARRAYHEAD pRoot, PCHAR pString, INT nLen);

INT RemoveElement(PARRAYHEAD pRoot, PCHAR pString, INT nLen);

NTSTATUS GetElement(PARRAYHEAD pRoot, INT nPos, PCHAR pString, INT * pLen);

BOOLEAN IsProtect(PUNICODE_STRING pSourceFile, PARRAYHEAD pRoot, CHECKIFEQUAL compareCallBack);

#endif // __DATASUPPORT_H_KL_2007_06_06__