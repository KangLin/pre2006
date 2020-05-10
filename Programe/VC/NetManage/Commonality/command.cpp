/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    command.cpp
\brief   命令类实现文件
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年8月14日  15:14:08
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#include "stdafx.h"
#include "command.h"
#include <stdio.h>
#include <stdexcept>

using namespace std;

CCommand::CCommand()
{
	m_nMaxLength = 0;
	m_nLength = 0;
	m_pBuffer = NULL;

	m_nNextPara = sizeof(DWORD);
}

CCommand::~CCommand()
{
	Clear();
}

/*!
\brief   得到命令
\param   无
\return  类型为 DWORD 。命令
\version 1.0
\author  康  林
\date    2007-8-14 15:15:47
*/
DWORD CCommand::GetCommand()
{
	DWORD * pCmd = NULL;
	DWORD dwCmd = 0;
	ASSERT(m_pBuffer);
	if(m_pBuffer)
	{
		pCmd = (DWORD * )m_pBuffer;
		dwCmd = *pCmd;
		return dwCmd;
	} // 结束 if(m_pBuffer)	
	CTException e(_T("异常：得到命令出错！命令没初始化。"));
	throw e;
}

int CCommand::GetPara(void ** pPara, DWORD* pdwLength)
{
	if(m_nNextPara >= m_nLength)
	{
		CTException e(_T("超出范围!"), S_OUT_OF_RANGE);
		return S_OUT_OF_RANGE;
		return S_FALSE;
	}// 结束 if(m_nNextPara >= m_nLength)
	*pPara = m_pBuffer + m_nNextPara + sizeof(DWORD);
	DWORD * pLen = (DWORD * )(m_pBuffer + m_nNextPara);
	*pdwLength = *pLen;
	m_nNextPara = m_nNextPara + sizeof(DWORD) + *pdwLength;
}

int CCommand::GetPara(_tstring * pPara)
{
	void * p = NULL;
	DWORD dwLen = 0;
	try
	{
		GetPara(&p, &dwLen);
		char * pp = new char[dwLen + sizeof(TCHAR)];
		memset(pp, 0, dwLen + sizeof(TCHAR));
		memcpy(pp, p, dwLen);
		*pPara = (LPCTSTR)pp;
		delete []pp;
		return S_OK;
	}
	catch(CTException e)
	{
		throw e;
		return S_FALSE;
	}
	return S_FALSE;
}

int CCommand::GetPara(DWORD * dwPara)
{
	if(m_nNextPara >= m_nLength)
	{
		CTException e(_T("超出范围!"), S_OUT_OF_RANGE);
		return S_OUT_OF_RANGE;
	}// 结束 if(m_nNextPara >= m_nLength)
	DWORD * pLen = (DWORD * )(m_pBuffer + m_nNextPara);
	if(*pLen != sizeof(DWORD))
	{
		CTException e(_T("类型不符!"), S_TYPE_ERROR);
		return S_FALSE;
	}// 结束 if(*pLen != sizeof(DWORD))
	pLen ++;
	*dwPara = *pLen;
	m_nNextPara = m_nNextPara + sizeof(DWORD) + sizeof(DWORD);
	return S_OK;
}

int CCommand::GetPara(LONG * lgPara)
{
	if(m_nNextPara >= m_nLength)
	{
		CTException e(_T("超出范围!"), S_OUT_OF_RANGE);
		return S_OUT_OF_RANGE;
	}// 结束 if(m_nNextPara >= m_nLength)
	DWORD * pLen = (DWORD * )(m_pBuffer + m_nNextPara);
	if(*pLen != sizeof(LONG))
	{
		CTException e(_T("类型不符!"), S_TYPE_ERROR);
		return S_FALSE;
	}// 结束 if(*pLen != sizeof(LONG))
	*lgPara = *(LONG * )(pLen + 1);
	m_nNextPara = m_nNextPara + sizeof(DWORD) + *pLen;
	return S_OK;
}

/*!
\brief   得到指定位置的参数
\param   int nPos          ：参数的位置
\param   const void ** pBuf：参数的指针
\param   DWORD* dwLength   ：参数的长度
\return  类型为 int 。成功返回S_OK，否则返回错码。
\version 1.0
\author  康  林
\date    2007-8-17 14:24:57
*/
int CCommand::GetPara(int nPos, const void ** pBuf, DWORD* dwLength)
{
	int nTotalLen = sizeof(DWORD);
	DWORD nLen = 0;                                    //参数长度
	char * pPara = NULL;

	while(nPos--)
	{
		DWORD * pLen = (DWORD * )(m_pBuffer + nTotalLen);
		nLen = *pLen;                                  //本参数的长度
		pPara =(char*) pLen + 1;                       //本参数指针

		nTotalLen = nTotalLen + sizeof(DWORD) + nLen;  //下一参数位置
		if(nTotalLen > m_nLength)
		{
			CTException e(_T("超出范围!"), S_OUT_OF_RANGE);
			return S_OUT_OF_RANGE;
		} // 结束 if(nTotalLen > m_nLength)
	} // 结束 while(nPos--)

	*dwLength = nLen;
	*pBuf = pPara;

	return S_OK;
}

/*!
\brief   设置命令
\param   DWORD dwCmd：命令
\return  类型为 int 。成功返回 S_OK，失败返回 S_FALSE 。
\version 1.0
\author  康  林
\date    2007-8-14 15:16:04
*/
int CCommand::SetCommand(DWORD dwCmd)
{
	int nRet = S_OK;
	Clear();
	m_nMaxLength = 1024;
	m_nLength = sizeof(DWORD);
	m_pBuffer = new char[m_nMaxLength];
	if(NULL == m_pBuffer)
	{
		nRet = S_FALSE;
		CTException e(_T("内存分配出错!"));
		throw e;
		return nRet;
	}
	else
	{
		memcpy(m_pBuffer, &dwCmd, m_nLength);
	}// 结束 if(NULL == m_pBuffer)
	return nRet;
}

/*!
\brief   设置命令
\param   DWORD dwCmd       ：命令
\param   const void * pPara：命令参数指针
\param   DWORD dwLength    ：命令参数长度
\return  类型为 int 。成功返回 S_OK，失败返回 S_FALSE 。
\version 1.0
\author  康  林
\date    2007-8-14 15:16:16
*/
int CCommand::SetCommand(DWORD dwCmd, const void * pPara, DWORD dwLength)
{
	int nRet = S_OK;
	Clear();
	m_nMaxLength = sizeof(DWORD) + dwLength;
	m_nLength = m_nMaxLength;
	m_pBuffer = new char[m_nMaxLength];
	if(NULL == m_pBuffer)
	{
		nRet = S_FALSE;
		CTException e(_T("内存分配出错!"));
		throw e;
		return nRet;
	}
	else
	{
		memcpy(m_pBuffer, &dwCmd, m_nLength);
		memcpy(m_pBuffer + sizeof(DWORD), pPara, dwLength);
	}// 结束 if(NULL == m_pBuffer)
	return nRet;
}

/*!
\brief   SetCommand
\param   const void * pBuf：命令指针
\param   DWORD dwLength   ：命令长度（包括了命令的参数）
\return  类型为 int 。成功返回 S_OK，失败返回 S_FALSE 。
\version 1.0
\author  康  林
\date    2007-8-14 15:16:44
*/
int CCommand::SetCommand(const void * pBuf, DWORD dwLength)
{
	int nRet = S_OK;
	Clear();
	m_nMaxLength = dwLength;
	m_nLength = dwLength;
	m_pBuffer = new char[m_nMaxLength];
	if(NULL == m_pBuffer)
	{
		nRet = S_FALSE;
		CTException e(_T("内存分配出错!"));
		throw e;
		return nRet;
	}
	else
	{
		memcpy(m_pBuffer, pBuf, m_nMaxLength);
	} // 结束 if(NULL == m_pBuffer)
	return nRet;
}

/*!
\brief   增加参数
\param   const void * pBuf：参数指针
\param   DWORD dwLength   ：参数长度
\return  类型为 int 。成功返回 S_OK，失败返回 S_FALSE 。
\version 1.0
\author  康  林
\date    2007-8-14 15:17:15
*/
int CCommand::AddPara(const void * pBuf, DWORD dwLength)
{
	int nRet = S_OK;
	char * pBuffer = NULL;
	if(m_nLength + dwLength + sizeof(DWORD) > m_nMaxLength)
	{
		//内存不够，重新分配内存
		m_nMaxLength = m_nMaxLength + dwLength + sizeof(DWORD) + dwLength + sizeof(DWORD);
		pBuffer = new char[m_nMaxLength];
		if(NULL == pBuffer)
		{
			CTException e(_T("内存分配出错!"));
			throw e;
			return S_FALSE;
		}// 结束 if(NULL == pBuffer)
		memcpy(pBuffer, m_pBuffer, m_nLength);
		delete []m_pBuffer;
		m_pBuffer = pBuffer;
	}// 结束 if(m_nLength + dwLength + sizeof(DWORD) > m_nMaxLength)

	//参数长度
	memcpy(m_pBuffer + m_nLength, &dwLength, sizeof(DWORD));
	m_nLength += sizeof(DWORD);
	//参数
	memcpy(m_pBuffer + m_nLength, pBuf, dwLength);
	m_nLength += dwLength;

	return nRet;
}

/*!
\brief   AddPara
\param   DWORD dwPara：参数
\return  类型为 int 。成功返回 S_OK，失败返回 S_FALSE 。
\version 1.0
\author  康  林
\date    2007-8-14 15:18:32
*/
int CCommand::AddPara(DWORD dwPara)
{
	return AddPara(&dwPara, sizeof(DWORD));
}

int CCommand::AddPara(LONG lgPara)
{
	return AddPara(&lgPara, sizeof(LONG));
}

int CCommand::AddPara(LPCTSTR lpszPara)
{
	ASSERT(lpszPara);
	DWORD dwLength = (_tcslen(lpszPara) + 1) * sizeof(TCHAR);
	return AddPara(lpszPara, dwLength);
}

int CCommand::AddPara(UINT32 dwPara)
{
	return AddPara(&dwPara,sizeof(UINT32));
}

int CCommand::AddPara(BOOL bPara)
{
	return AddPara(&bPara, sizeof(BOOL));
}

/*!
\brief   修改指定位置的参数，如果指定位置不存在返回FALSE
\param   int nPos         ：要修改的位置(从1开始)
\param   const void * pBuf：参数指针
\param   DWORD dwLength   ：参数长度
\return  类型为 int 。成功返回S_OK，失败返回S_FALSE。
\version 1.0
\author  康  林
\date    2007-8-17 12:37:06
*/
int CCommand::ModifyPara(int nPos, const void * pBuf, DWORD dwLength)
{
	int nTotalLen = sizeof(DWORD);
	DWORD nLen = 0;                                    //参数长度
	char * pPara = NULL;

	while(nPos--)
	{
		DWORD * pLen = (DWORD * )(m_pBuffer + nTotalLen);
		nLen = *pLen;                                  //本参数的长度
		pPara =(char*) pLen + 1;                       //本参数指针
		
		nTotalLen = nTotalLen + sizeof(DWORD) + nLen;  //下一参数位置
		if(nTotalLen > m_nLength)
		{
			return S_OUT_OF_RANGE;
		} // 结束 if(nTotalLen > m_nLength)
	} // 结束 while(nPos--)

	if(nLen == dwLength)
	{
		memcpy(pPara, pBuf, nLen);
		return S_OK;
	}// 结束 if(nLen == dwLength)

	return S_TYPE_ERROR;
}

/*!
\brief   得到命令缓存区指针
\param   无
\return  类型为 void * 。命令缓存区指针
\version 1.0
\author  康  林
\date    2007-8-14 15:18:43
*/
void * CCommand::GetBuffer()
{
	return m_pBuffer;
}

/*!
\brief   得到命令长度
\param   无
\return  类型为 int 。缓存长度
\version 1.0
\author  康  林
\date    2007-8-14 15:19:05
*/
int CCommand::GetLength()
{
	return m_nLength;
}

/*!
\brief   清除缓存
\param   无
\return  类型为 int 。成功返回 S_OK，失败返回 S_FALSE 。
\version 1.0
\author  康  林
\date    2007-8-14 15:19:18
*/
int CCommand::Clear()
{
	if(m_pBuffer)
	{
		delete []m_pBuffer;
	}// 结束 if(m_pBuffer)
	m_nMaxLength = 0;
	m_nLength = 0;
	return S_OK;
}