/*!
\warning Copyright (C) 2007 KangLin Studio;All rights reserved.
\file    Support.c
\brief   Support function
\version 1.0
\author  KangLin (kl222@126.com)
\date    2007-5-14 10:52:59
\par     Compiler:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#include "sfilter.h"
#include "Support.h"

ARRAYHEAD gFileNameArrayHead;

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

	PAGED_CODE();

	nRet = RtlCompareUnicodeString(&pDestination->FileName, &pSource->FileName, TRUE);
	return nRet;
}

/*!
\brief   Compare the Directory included whether in file name.
\param   PDATASTRUCT pDestination：file name
\param   PDATASTRUCT pSource     ：directory
\return  INT 。
		 If success, return 0;  \n
         If pDestination > pSource, return > 0;\n
		 If pDestination < pSource, return < 0;
\version 1.0
\author  KangLin
\date    2007-5-16 14:20:18
*/
INT CompareDirCallBack(PDATASTRUCT pDestination, PDATASTRUCT pSource)
{
	NTSTATUS status = STATUS_SUCCESS;
	INT nRet = 0;
	INT nMin = 0;
	UNICODE_STRING UnDes;
	UNICODE_STRING UnSou;
	PWSTR pDes = NULL;
	PWSTR pSou = NULL;

	PAGED_CODE();

	status = RtlUpcaseUnicodeString(&UnDes, &pDestination->FileName, TRUE);
	if(NT_SUCCESS(status))
	{
		pDes = UnDes.Buffer;
	}
	else
	{
		pDes = pDestination->FileName.Buffer;
	}// 结束 if(NT_SUCCESS(status))

	status = RtlUpcaseUnicodeString(&UnSou, &pSource->FileName, TRUE);
	if(NT_SUCCESS(status))
	{
		pSou = UnSou.Buffer;
	}
	else
	{
		pSou = pSource->FileName.Buffer;
	}// 结束 if(NT_SUCCESS(status))
	
	nMin = min(pDestination->FileName.Length, pSource->FileName.Length);

	nRet = RtlCompareMemory(pDes, pSou, nMin);
	if(nRet == nMin)
	{
		nRet = 0; 
	}
	else
	{
		nRet = RtlCompareUnicodeString(&pDestination->FileName, &pSource->FileName, TRUE);
	}// 结束 if(nRet == nMin)

	// Free buffer
	RtlFreeUnicodeString(&UnDes);
	RtlFreeUnicodeString(&UnSou);

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
	PAGED_CODE();
	FreeBuffer(pClear->FileName.Buffer);
	return nRet;
}

/*!
\brief   得到完全的路径名，把设备符号名与文件对象名连接成完全路径名。
\param   IN PDEVICE_OBJECT DeviceObject：设备对象
\param   IN PIRP Irp                   ：
\param   PUNICODE_STRING* pFullPath    ：返回路径名,
\note                                    由调用者释放内存。
\return  类型为 NTSTATUS 。成功返回 STATUS_SUCCESS,否则返回错误代码。
\version 1.0
\author  康  林
\date    2007-5-16 13:04:33
*/
NTSTATUS GetFullPath(IN PDEVICE_OBJECT DeviceObject,
					 IN PIRP Irp,
					 /*out*/PUNICODE_STRING* pFullPath
					 )
{
	PSFILTER_DEVICE_EXTENSION pExt;
	PWSTR pFileBuffer = NULL;
	PUNICODE_STRING pFileName = NULL;
	NTSTATUS status = STATUS_SUCCESS;
	int nLen = 0;
	PIO_STACK_LOCATION pIrpSp = IoGetCurrentIrpStackLocation(Irp);

	PAGED_CODE();

	pFileName = AllocateBuffer(sizeof(UNICODE_STRING));
	if(NULL == pFileName)
	{
		status = STATUS_INSUFFICIENT_RESOURCES;
	}
	else
	{
		RtlZeroBytes(pFileName, sizeof(UNICODE_STRING));
		pExt = (PSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension;
		nLen = pExt->DeviceLinkSymbolName.Length + pIrpSp->FileObject->FileName.Length + sizeof(WCHAR);
		if(0 == nLen)
		{
			return STATUS_SUCCESS;
		} // 结束 if(0 == nLen)
		pFileBuffer = AllocateBuffer(nLen);
		if(NULL == pFileBuffer)
		{
			status = STATUS_INSUFFICIENT_RESOURCES;
			FreeBuffer(pFileName);
			pFileName = NULL;
		}
		else
		{
			RtlInitEmptyUnicodeString(pFileName, pFileBuffer, nLen);
			status = RtlAppendUnicodeStringToString(pFileName, &pExt->DeviceLinkSymbolName);
			if(NT_SUCCESS(status))
			{
				status = RtlAppendUnicodeStringToString(pFileName, &pIrpSp->FileObject->FileName);
			}// 结束 if(NT_SUCCESS(status))
		}// 结束 (pExt->DeviceLinkSymbolName.Length + pIrpSp->FileObject->FileName.Length)
		if(NT_SUCCESS(status))
		{
			*pFullPath = pFileName;
		}
		else
		{
			if(pFileName)
			{
				FreeBuffer(pFileName);
			}// 结束 if(pFileName)
			if(pFileBuffer)
			{
				FreeBuffer(pFileBuffer);
			} // 结束 if(pFileBuffer)
		}// 结束 if(NT_SUCCESS(status))
	}
	return status;
}

/*!
\brief   判断文件是否是禁止删除的文件
\param   PUNICODE_STRING pSourceFile：要判断的文件。
\param   CHECKIFEQUAL compareCallBack ：比较回调函数。
\return  类型为 BOOLEAN 。如果是禁止删除的文件,则返回TRUE,否则返回FLASE。
\version 1.0
\author  康  林
\date    2007-5-16 14:12:18
*/
BOOLEAN SfIsDisableDeleteFile(PUNICODE_STRING pSourceFile, CHECKIFEQUAL compareCallBack)
{
	BOOLEAN bRet = FALSE;
	UNICODE_STRING fileName;
	DATASTRUCT Element;
	INT nLen = 0;
	PWSTR pBuf = NULL;

	PAGED_CODE();

	if(gWriteProtectData)
	{
		return FALSE;
	}// 结束 if(gWriteProtectData)

	//RtlInitUnicodeString(&fileName, L"\\aa.txt");
	//if(!RtlCompareUnicodeString(&fileName, pSourceFile, TRUE))
	//{
	//	bRet = TRUE;
	//} // 结束 if(!RtlCompareUnicodeString(&fileName, pSouceFile, TRUE))
	//return bRet;
	ASSERT(pSourceFile);
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

	if(-1 != SearchElementArray(&gFileNameArrayHead, &Element, compareCallBack))
	{
		bRet = TRUE;
	}// 结束 if(-1 != SearchElementArray(&gFileNameArrayHead, &Element, compareCallBack))

	FreeBuffer(pBuf);

	return bRet;
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

	PAGED_CODE();

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

	PAGED_CODE();

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