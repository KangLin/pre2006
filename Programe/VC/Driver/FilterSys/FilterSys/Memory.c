/*!
\warning Copyright (C) 2007 KangLin Studio;All rights reserved.
\file    Memory.c
\brief   This functions that is used to managent memory.
		 The file is used to implement this functions.
\version 1.0
\author  KangLin (kl222@126.com)
\date    2007-5-15 13:46:15
\par     Compiler:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#include "Memory.h"
#include "ntddk.h"

/*!
\brief   Allocate Buffer,The buffer allocated with it. 
		 use FreeBuffer function to free. 
\param   int nSize：buffer size.
\return  类型为 PVOID 。If success, return pointer of buffer, otherwise is NULL.
\version 1.0
\author  KangLin
\date    2007-5-15 13:47:44
*/
PVOID AllocateBuffer(int nSize)
{
#ifndef _TEST
	PAGED_CODE();
	return ExAllocatePoolWithTag(NonPagedPool, nSize, 'KABU');
#else
	return new char[nSize];
#endif
}

/*!
\brief   Free Buffer
\param   PVOID p：
\return  类型为 void 。
\version 1.0
\author  KangLin
\date    2007-5-15 13:48:45
*/
void FreeBuffer(PVOID p)
{
	ASSERT(p);
	if(NULL != p)
	{
#ifndef _TEST
		PAGED_CODE();
		ExFreePoolWithTag(p, 'KABU');
#else
		free(p);
#endif
	} // 结束 if(NULL != p)
}

/*!
\brief   Move Buffer
\param   PVOID pDestination：Destination buffer
\param   PVOID pSource     ：Source buffer
\param   ULONG nLen        ：move length,in byte
\return  类型为 void 。
\version 1.0
\author  KangLin
\date    2007-5-15 13:48:53
*/
void MoveBuffer(PVOID pDestination, PVOID pSource, ULONG nLen)
{
	ASSERT(pDestination && pSource);

#ifndef _TEST
	PAGED_CODE();
	RtlMoveMemory(pDestination, pSource, nLen);
#else
	memmove(pDestination, pSource, nLen);
#endif
}

/*!
\brief   Free Unicode Buffer
\param   PUNICODE_STRING pString：
\return  类型为 void 。
\version 1.0
\author  KangLin
\date    2007-5-15 13:49:39
*/
void FreeUnicodeBuffer(PUNICODE_STRING pString)
{
	if(pString->Buffer)
	{
		FreeBuffer(pString->Buffer);
	} // 结束 if(pString->Buffer)
	
	FreeBuffer(pString);
}