/*!
\warning Copyright (C) 2007 KangLin Studio;All rights reserved.
\file    Memory.h
\brief   This functions that is used to managent memory.
\version 1.0
\author  KangLin (kl222@126.com)
\date    2007-5-15 13:44:46
\par     Compiler:
         Microsoft Visual Studio 8.0 ¡ª¡ª C/C++ 8.0
*/

#ifndef __MEMORY_H_KL_2007_05_15__
#define __MEMORY_H_KL_2007_05_15__

#pragma once

#include ".\sfilter.h"

PVOID AllocateBuffer(int nSize);
void FreeBuffer(PVOID p);
void FreeUnicodeBuffer(PUNICODE_STRING pString);
void MoveBuffer(PVOID pDestination, PVOID pSource, ULONG nLen);

#endif //__MEMORY_H_KL_2007_05_15__