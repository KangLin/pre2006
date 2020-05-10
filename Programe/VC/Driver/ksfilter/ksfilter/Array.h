/*!
\warning Copyright (C) 2007 KangLin Studio;All rights reserved.
\file    Array.h
\brief   process array data struct
\version 1.0
\author  KangLin (kl222@126.com)
\date    2007-5-14 9:35:31
\par     Compiler:
		 Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/


#ifndef __ARRAY_HEAD_H_KL_2007_05_09__
#define __ARRAY_HEAD_H_KL_2007_05_09__

#pragma once


#ifndef _TEST

#include ".\sfilter.h"
#include "Memory.h"

enum _ATTRIBUTES
{
	DISABLEDELTE = 0x00000001,
	DISABLEDISAPLAY = 0x00000002,
	DIECTORY = 0x80000000
};

typedef struct _KF_FILENAME
{
	UNICODE_STRING FileName;  //file name
	ULONG Attributes;         //attributes of file
}KFFILENAME, *PKFFILENAME;

#define PDATASTRUCT PKFFILENAME
#define DATASTRUCT KFFILENAME

#else

#include <tchar.h>
typedef unsigned long ULONG;

#define PDATASTRUCT TCHAR** 
#define DATASTRUCT TCHAR*

#endif

#ifndef INT
#define INT int
#endif

#define ALLOCATEBLOCKSZIE 20

/////////////////////////////////////////////////////////////////////////////
//
//                         Array head struct
//
/////////////////////////////////////////////////////////////////////////////

typedef struct _ARRAYHEAD
{
	ULONG nTotalSize;    //Array total size,don't include the array head, start from pVoid
	//ULONG nElementSize;  //size of each element in array
	INT nElementNumber;  //number of element in array, based 1.
	PDATASTRUCT pArray;  //point to start address of array
}ARRAYHEAD, *PARRAYHEAD;

/*******************************************************************************************************
函数名：CHECKIFEQUAL
描  述：Compare between pDestination and pSource.
		Used by InsertElementArray and SearchElementArray.
		Implemented by user.
参  数：
        PDATASTRUCT pDestination：
		PDATASTRUCT pSource     ：
返回值：类型为 INT 。
		If equal, return = 0;
		If pDestination > pSource, return > 0;
		If pDestination < pSource, return < 0;
版  本：1.0
作  者：KangLin
时  间：2007年5月11日 14:42:47
*******************************************************************************************************/
typedef INT (*CHECKIFEQUAL)(PDATASTRUCT pDestination, PDATASTRUCT pSource);
/*******************************************************************************************************
函数名：CLEARDATA
描  述：use to clear data.
		Used by RemoveElementArray and DeleteElementArray.
		Implemented by user.
参  数：
        PDATASTRUCT pClear：
返回值：类型为 typedef INT 。
版  本：1.0
作  者：KangLin
时  间：2007年5月11日 14:45:38
*******************************************************************************************************/
typedef INT (*CLEARDATA)(PDATASTRUCT pClear);

INT InitialArray(PARRAYHEAD pRoot);
INT ClearArray(PARRAYHEAD pRoot, CLEARDATA ClearCallBack);
INT AdjustArray(PARRAYHEAD pRoot, INT nNum);

INT InsertElementArray(PARRAYHEAD pRoot, PDATASTRUCT pElement, CHECKIFEQUAL CallBack);
INT ReplaceElementArray(PARRAYHEAD pRoot, PDATASTRUCT pElement, INT nPos);
INT DeleteElementArray(PARRAYHEAD pRoot, PDATASTRUCT pElement, CHECKIFEQUAL CallBack, CLEARDATA ClearCallBack);
INT SearchElementArray(PARRAYHEAD pRoot, PDATASTRUCT pElement, CHECKIFEQUAL CallBack);
INT AppendElementArray(PARRAYHEAD pRoot, PDATASTRUCT pElement);
INT RemoveElementArray(PARRAYHEAD pRoot, INT nPos, CLEARDATA ClearCallBack);
PDATASTRUCT GetElementArray(PARRAYHEAD pRoot, INT nPos);

#endif //__ARRAY_HEAD_H_KL_2007_05_09__