/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    DataSupport.c
\brief   对具体数据的操作
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年6月7日  13:48:56
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#include "DataSupport.h"
#include "FilterSys.h"
#include "Memory.h"
#include "ntddk.h"

/*!
\brief   Compare between pDestination with pSource
\param   PDATASTRUCT pDestination：
\param   PDATASTRUCT pSource     ：
\return  类型为 INT 。\n
		 If pDestination = pSource, return 0;  \n
         If pDestination > pSource, return > 0;\n
		 If pDestination < pSource, return < 0;
\version 1.0
\author  KangLin
\date    2007-5-14 10:55:30
*/
INT CompareCallBack(PDATASTRUCT pDestination, PDATASTRUCT pSource)
{
	INT nRet = 0;

	//PAGED_CODE();

	nRet = RtlCompareUnicodeString(&pDestination->FileName, &pSource->FileName, TRUE);
	return nRet;
}

/*!
\brief   Free buffer of array 
\param   PDATASTRUCT pClear：data struct pointer
\return  INT 。return 0
\version 1.0
\author  KangLin
\date    2007-5-14 14:52:26
*/
INT ClearCallBack(PDATASTRUCT pClear)
{
	INT nRet = 0;
	//PAGED_CODE();
	FreeBuffer(pClear->FileName.Buffer);
	return nRet;
}

/*!
\brief   Insert the protected file into array
\param   PARRAYHEAD pRoot：array pointer
\param   PCHAR pString   ：the protected file
\param   INT nLen        ：file name length(in byte)
\return  INT 。If success,return 0. otherwise return no 0
\version 1.0
\author  KangLin
\date    2007-5-14 14:47:36
*/
INT InsertElement(PARRAYHEAD pRoot, PCHAR pString, INT nLen)
{
	INT nRet = 0;
	DATASTRUCT Des;
	PWSTR p = NULL;

	//PAGED_CODE();

	RtlZeroBytes(&Des, sizeof(DATASTRUCT));

	p = AllocateBuffer(nLen);
	if(NULL == p)
	{
		return 1;
	}// 结束 if(NULL == p)

	MoveBuffer(p, pString, nLen);
	RtlInitUnicodeString(&Des.FileName, p);
	nRet = InsertElementArray(pRoot, &Des, CompareCallBack);

	return nRet;
}

/*!
\brief   Remove the protected file from array
\param   PARRAYHEAD pRoot：array pointer
\param   PCHAR pString   ：removed element
\param   INT nLen        ：file name length(in byte)
\return  INT 。If success,return 0. otherwise return no 0
\version 1.0
\author  KangLin
\date    2007-5-16 16:18:20
*/
INT RemoveElement(PARRAYHEAD pRoot, PCHAR pString, INT nLen)
{
	INT nRet = 0;
	DATASTRUCT des;
	PWSTR p = NULL;

	//PAGED_CODE();

	RtlZeroBytes(&des, sizeof(DATASTRUCT));

	p = AllocateBuffer(nLen);
	if(NULL == p)
	{
		return 1;
	}// 结束 if(NULL == p)

	MoveBuffer(p, pString, nLen);
	RtlInitUnicodeString(&des.FileName, p);

	nRet = DeleteElementArray(pRoot, &des, CompareCallBack, ClearCallBack);

	FreeBuffer(p);

	return nRet;
}

/*!
\brief   Get Element and copy the content to user buffer.
\param   PARRAYHEAD pRoot：
\param   INT nPos        ：
\param   PCHAR pString   ：user buffer
\param   INT * pLen      ：the length of pString content 
\return  NTSTATUS 。If success,return STATUS_SUCCESS.
\version 1.0
\author  KangLin
\date    2007-5-18 17:11:08
*/
NTSTATUS GetElement(PARRAYHEAD pRoot, INT nPos, PCHAR pString, INT * pLen)
{
	NTSTATUS status = STATUS_SUCCESS;
	PDATASTRUCT pData = NULL;

	if(nPos < 0 || nPos > pRoot->nElementNumber - 1)
	{
		return STATUS_INVALID_PARAMETER;
	}// 结束 if(nPos < 0 || nPos > pRoot->nElementNumber - 1)

	pData = GetElementArray(pRoot, nPos);
	if(pData)
	{
		if(*pLen < pData->FileName.Length)
		{
			// user buffer is small than required.
			*pLen = pData->FileName.Length;
			return STATUS_BUFFER_OVERFLOW;
		}// 结束 if(*pLen < pData->FileName.Length)

		MoveBuffer(pString, pData->FileName.Buffer, pData->FileName.Length);
		*pLen = pData->FileName.Length;
	}
	else
	{
		status = STATUS_UNSUCCESSFUL;
	}// 结束 if(pData)

	return status;
}

/*!
\brief   判断文件是否是受保护
\param   PUNICODE_STRING pSourceFile ：要判断的文件。
\param   PARRAYHEAD pRoot            ：保护的数组。
\param   CHECKIFEQUAL compareCallBack：比较回调函数。
\return  类型为 BOOLEAN 。如果是禁止删除的文件,则返回TRUE,否则返回FLASE。
\version 1.0
\author  康  林
\date    2007-6-7 13:42:09
*/
BOOLEAN IsProtect(PUNICODE_STRING pSourceFile, PARRAYHEAD pRoot, CHECKIFEQUAL compareCallBack)
{
	BOOLEAN bRet = FALSE;
	UNICODE_STRING fileName;
	DATASTRUCT Element;
	INT nLen = 0;
	PWSTR pBuf = NULL;

	ASSERT(pSourceFile && pRoot && compareCallBack);
	if(NULL == pSourceFile)
	{
		return FALSE;
	} // 结束 if(NULL == pSourceFile)
	nLen = pSourceFile->Length + sizeof(WCHAR);
	pBuf = AllocateBuffer(nLen);
	if(NULL == pBuf)
	{
		return FALSE;
	}// 结束 if(NULL == pBuf)

	RtlInitEmptyUnicodeString(&Element.FileName, pBuf, nLen);
	RtlCopyUnicodeString(&Element.FileName, pSourceFile);

	if(-1 != SearchElementArray(pRoot, &Element, compareCallBack))
	{
		bRet = TRUE;
	}// 结束 if(-1 != SearchElementArray(pRoot, &Element, compareCallBack))

	FreeBuffer(pBuf);

	return bRet;
}