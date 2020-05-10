/*!
\warning Copyright (C) 2007 KangLin Studio;All rights reserved.
\file    Array.c
\brief   process array data struct
\version 1.0
\author  KangLin (kl222@126.com)
\date    2007-5-13 18:55:29
\par     Compiler:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*/

//#include "stdafx.h"

#include "Array.h"

/*!
\brief   Initial Array
\param   PARRAYHEAD pRoot��
\return  INT ��If success,return 0
\version 1.0
\author  KangLin
\date    2007-5-15 13:36:05
*/
INT InitialArray(PARRAYHEAD pRoot)
{
	ASSERT(pRoot);

#ifndef _TEST
	RtlZeroBytes(pRoot, sizeof(ARRAYHEAD));
#else
	memset(pRoot, 0, sizeof(ARRAYHEAD));
#endif

	return 0;
}

/*!
\brief   Clear Array
\param   PARRAYHEAD pRoot       ��
\param   CLEARDATA ClearCallBack��
\return  INT ��If success, return 0, otherwise, don't return zero.
\version 1.0
\author  KangLin
\date    2007-5-15 13:36:11
*/
INT ClearArray(PARRAYHEAD pRoot, CLEARDATA ClearCallBack)
{
	INT nRet = 0;
	INT i = 0;
	PDATASTRUCT pData = NULL;

	ASSERT(pRoot);

	if(ClearCallBack)
	{
		for(i = 0; i < pRoot->nElementNumber; i++)
		{
			pData = GetElementArray(pRoot, i);
			ClearCallBack(pData);
		} // ���� for(i = 0; i < pRoot->nElementNumber; i++)
	}// ���� if(ClearCallBack)

	if(pRoot->pArray)
	{
		FreeBuffer(pRoot->pArray);
		//pRoot->pArray = NULL;
	}// ���� if(pRoot->pArray)

	InitialArray(pRoot);

	return nRet;
}

/*!
\brief   Adjust Array size.If the buffer of array is too small.
		 reallocate bigest buffer.and move old array data to new buffer.
\param   PARRAYHEAD pRoot��
\param   INT nNum        ��
\return  ����Ϊ INT ��If success, return 0. otherwise don't return zero.
\version 1.0
\author  KangLin
\date    2007-5-15 13:38:17
*/
INT AdjustArray(PARRAYHEAD pRoot, INT nNum)
{
	INT nRet = 0;
	INT nOldLen = 0;
	PDATASTRUCT pBuf = NULL;

	ASSERT(pRoot);

	if(pRoot->nTotalSize >= nNum * sizeof(DATASTRUCT))
	{
		return nRet;
	}// ���� if(pRoot->nTotalSize >= nNum * sizeof(DATASTRUCT))


	nOldLen = pRoot->nTotalSize;


	// calculate allocate buffer size
	pRoot->nTotalSize = pRoot->nTotalSize + ALLOCATEBLOCKSZIE * sizeof(DATASTRUCT);
	if(pRoot->nTotalSize < nNum * sizeof(DATASTRUCT))
	{
		pRoot->nTotalSize = nNum * sizeof(DATASTRUCT);
	}// ���� if(pRoot->nTotalSize < nNum * sizeof(DATASTRUCT))

	// allocate buffer
	pBuf = (PDATASTRUCT)AllocateBuffer(pRoot->nTotalSize);
	if(NULL == pBuf)
	{
		return 1;
	} // ���� if(NULL == pBuf)

	// Zero Buffer
#ifndef _TEST
	RtlZeroBytes(pBuf, pRoot->nTotalSize);
#else
	memset(pBuf, 0, pRoot->nTotalSize);
#endif

	if(pRoot->nElementNumber > 0)
	{
		// move data
		MoveBuffer(pBuf, pRoot->pArray, nOldLen);

		// free old buffer
		FreeBuffer(pRoot->pArray);
	} // ���� if(pRoot->nElementNumber > 0)

	// set new buffer
	pRoot->pArray = pBuf;

	return nRet;
}

/*!
\brief   Append Element to Array
\param   PARRAYHEAD pRoot    ��
\param   PDATASTRUCT pElement��
\return  ����Ϊ INT ��If success, return 0. otherwise don't return zero.
\version 1.0
\author  KangLin
\date    2007-5-15 13:42:14
*/
INT AppendElementArray(PARRAYHEAD pRoot, PDATASTRUCT pElement)
{
	INT nRet = 0;
	PDATASTRUCT pDes = NULL;

	ASSERT(pRoot && pElement);

	nRet = AdjustArray(pRoot, pRoot->nElementNumber + 1);
	if(!nRet)
	{
		pDes = pRoot->pArray + pRoot->nElementNumber;
		MoveBuffer(pDes, pElement, sizeof(DATASTRUCT));
		pRoot->nElementNumber++;
	} // ���� if(!nRet)
	return nRet;
}

/*!
\brief   Remove Element from Array
\param   PARRAYHEAD pRoot       ��
\param   INT nPos               ��
\param   CLEARDATA ClearCallBack��call back function that is used compare two element.
\return  ����Ϊ INT ��If success, return 0. otherwise don't return zero.
\version 1.0
\author  KangLin
\date    2007-5-15 13:42:36
*/
INT RemoveElementArray(PARRAYHEAD pRoot, INT nPos, CLEARDATA ClearCallBack)
{
	INT nRet = 0;
	PDATASTRUCT pDes = NULL;
	PDATASTRUCT pSource = NULL;
	INT nLen = 0;
	INT i = 0;

	ASSERT(nPos >= 0 && nPos < pRoot->nElementNumber && pRoot->nElementNumber > 0);
	if(!(nPos >= 0 && nPos < pRoot->nElementNumber && pRoot->nElementNumber > 0))
	{
		return 1;
	}// ���� if(!(nPos >= 0 && nPos < pRoot->nElementNumber && pRoot->nElementNumber > 0))

	//clear data
	if(ClearCallBack)
	{
		nRet = ClearCallBack(pRoot->pArray + nPos);
	}// ���� if(ClearCallBack)

	nLen = sizeof(DATASTRUCT);
	for(i = nPos + 1; i < pRoot->nElementNumber; i++)
	{
		pSource = pRoot->pArray + i;
		pDes = pRoot->pArray + (i - 1);
		MoveBuffer(pDes, pSource, nLen);
#ifdef _TEST
		memset(pSource, 0, nLen);
#else
		RtlZeroBytes(pSource, nLen);
#endif
	} // ���� for(i = nPos + 1; i < pRoot->nElementNumber; i++)
	pRoot->nElementNumber--;

	return nRet;
}

/*!
\brief   Get Element in Array
\param   PARRAYHEAD pRoot��
\param   INT nPos        ��
\return ����Ϊ PDATASTRUCT ��return the element's pointer.
\version 1.0
\author  KangLin
\date    2007-5-15 13:43:43
*/
PDATASTRUCT GetElementArray(PARRAYHEAD pRoot, INT nPos)
{
	PDATASTRUCT pRet = NULL;

	ASSERT(nPos >= 0 && nPos < pRoot->nElementNumber);
	if(!(nPos >= 0 && nPos < pRoot->nElementNumber))
	{
		return pRet;
	}// ���� if(!(nPos >= 0 && nPos < pRoot->nElementNumber))

	pRet = pRoot->pArray + nPos;

	return pRet;
}

/*******************************************************************************************************
��������InsertElementArray
��  ����
��  ����
        PARRAYHEAD pRoot     ��
		PDATASTRUCT pElement ��
		CHECKIFEQUAL CallBack��
����ֵ������Ϊ INT ��
��  ����1.0
��  �ߣ�KangLin
ʱ  �䣺2007��5��11�� 8:51:18
*******************************************************************************************************/
INT InsertElementArray(PARRAYHEAD pRoot, PDATASTRUCT pElement, CHECKIFEQUAL CallBack)
{
	INT nRet = 0;
	INT nLow = 0, nHight = 0, nMid = 0;
	INT nReture = 0;
	PDATASTRUCT pData = NULL;
	PDATASTRUCT pDes = NULL;
	PDATASTRUCT pSource = NULL;
	INT nLen = 0, nPos = 0;
	INT i = 0;

	ASSERT(pRoot && pElement && CallBack);

	nRet = AdjustArray(pRoot, pRoot->nElementNumber + 1);
	if(nRet)
	{
		return nRet;
	}// ���� if(nRet)
	nHight = pRoot->nElementNumber - 1;
	while(nLow <= nHight)
	{
		nMid = (nLow + nHight) / 2;
		pData = GetElementArray(pRoot, nMid);
		nReture = CallBack(pData, pElement);
		if(0 == nReture)
		{
			// replace data
			MoveBuffer(pData, pElement, sizeof(DATASTRUCT));
			return nRet;
		}
		else if(nReture > 0)
		{
			nHight = nMid - 1;
			nPos = nMid;
		}
		else
		{
			nLow = nMid + 1;
			nPos = nMid + 1;
		} // ���� if(0 == nReture)
	}// ���� while(nLow <= nHight)

	// Move data and insert element
	// - Move data
	nLen = sizeof(DATASTRUCT);
	for(i = pRoot->nElementNumber - 1; i >= nPos; i--)
	{
		pSource = pRoot->pArray + i;
		pDes = pRoot->pArray + (i + 1);
		MoveBuffer(pDes, pSource, nLen);
	} // ���� for(i = pRoot->nElementNumber - 1; i >= nPos; i--)
	pSource = pRoot->pArray + nPos;
	// - Insert element
	MoveBuffer(pSource, pElement, sizeof(DATASTRUCT));
	// - Element number increase one
	pRoot->nElementNumber++;

	return nRet;
}

/*!
\brief   Replace the Element of pointed position in Array
\param   PARRAYHEAD pRoot    ��
\param   PDATASTRUCT pElement��replacing element
\param   INT nPos            ��replaced position
\return  INT ��if success, return 0;
\version 1.0
\author  KangLin
\date    2007-5-17 9:57:08
*/
INT ReplaceElementArray(PARRAYHEAD pRoot, PDATASTRUCT pElement, INT nPos)
{
	INT nRet = 0;
	PDATASTRUCT pDes = NULL;

	ASSERT(pRoot && pElement);
	if(nPos < 0 || nPos > pRoot->nElementNumber - 1)
	{
		return 1;
	}// ���� if(nPos < 0 || nPos > pRoot->nElementNumber - 1)

	pDes = pRoot->pArray + nPos;
	MoveBuffer(pDes, pElement, sizeof(DATASTRUCT));
	return nRet;
}

/*******************************************************************************************************
��������SearchElementArray
��  ����Search the Element in Array, use bisearch
��  ����
        PARRAYHEAD pRoot     ��point to array root
		PDATASTRUCT pElement ��seach element
		CHECKIFEQUAL CallBack��call back function
����ֵ������Ϊ INT ��if failed, return -1.if successed, return the element position.
��  ����1.0
��  �ߣ�KangLin
ʱ  �䣺2007��5��10�� 17:14:56
*******************************************************************************************************/
INT SearchElementArray(PARRAYHEAD pRoot, PDATASTRUCT pElement, CHECKIFEQUAL CallBack)
{
	INT nRet = -1;
	INT nLow = 0, nHight = 0, nMid = 0;
	INT nReture = 0;
	PDATASTRUCT pData = NULL;

	ASSERT(-1 != pRoot->nElementNumber);
	ASSERT(pRoot && pElement && CallBack);

	nHight = pRoot->nElementNumber - 1;
	while(nLow <= nHight)
	{
		nMid = (nLow + nHight) / 2;
		pData = GetElementArray(pRoot, nMid);
		nReture = CallBack(pData, pElement);
		if(0 == nReture)
		{
			return nMid;
		}
		else if(nReture > 0)
		{
			nHight = nMid - 1;
		}
		else
		{
			nLow = nMid + 1;
		}// ���� if(0 == nReture)
	}// ���� while(nLow <= nHight)
	return nRet;
}

/*!
\brief   ��������ɾ��ָ����Ԫ��
\param   PARRAYHEAD pRoot       ������ָ��
\param   PDATASTRUCT pElement   ��Ҫɾ��Ԫ�ص�ָ��
\param   CHECKIFEQUAL CallBack  ���Ƚ������е�Ԫ����Ҫɾ��Ԫ�صĻص�����
\param   CLEARDATA ClearCallBack��ɾ��Ԫ��ʱ������ص������������ͷ������б�ɾ��Ԫ�ص��ڴ�ռ�
\return  ����Ϊ INT ���ɹ�����0��ʧ�ܷ��ط��㡣
\version 1.0
\author  ��  ��
\date    2007-5-13 18:48:00
*/
INT DeleteElementArray(PARRAYHEAD pRoot, PDATASTRUCT pElement, CHECKIFEQUAL CallBack, CLEARDATA ClearCallBack)
{
	INT nRet = 1;
	INT nPos = 0;

	ASSERT(pRoot && pElement && CallBack);

	nPos = SearchElementArray(pRoot, pElement, CallBack);
	if(nPos != -1)
	{
		return RemoveElementArray(pRoot, nPos, ClearCallBack);
	}// ���� if(nPos != -1)
	return nRet;
}