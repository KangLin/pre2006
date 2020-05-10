/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    Data.cpp
\brief   用于发送/接收数据，确保发送/接收的数据的正确性，按照定义的协议打包/解包。
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年8月14日  15:12:44
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#include "StdAfx.h"
#include "Data.h"
#include ".\command.h"

CData::CData()
{
	m_nLength = 0;
	m_nMaxLength = 0;
	m_pBuffer = NULL;
	m_pHead = NULL;
}

CData::~CData()
{
	Clear();
}

/*!
\brief   清除缓存区，释放内存
\param   无
\return  类型为 int 。成功返回S_OK，否则返回S_FALSE。
\version 1.0
\author  康  林
\date    2007-8-13 12:21:23
*/
int CData::Clear()
{
	if(m_pBuffer)
	{
		delete []m_pBuffer;
	}// 结束 if(m_pBuffer)
	m_nLength = 0;
	m_nMaxLength = 0;
	m_pBuffer = NULL;
	m_pHead = NULL;
	return S_OK;
}

CSendData::CSendData()
{
	m_nSended = 0;
}

CSendData::~CSendData()
{
	Clear();
}

/*!
\brief   初始化包，组包时必须先调用此函数。它分配包缓存并初始化包头和变量
\param   int nLength：包的长度
\return  类型为 int 。成功返回S_OK，否则返回S_FALSE。
\version 1.0
\author  康  林
\date    2007-8-13 12:17:20
*/
int CSendData::InitializePackage(int nLength)
{
	Clear();

	m_nLength = sizeof(PACKAGEHEAD);
	m_nMaxLength = nLength + m_nLength;
	m_pBuffer = new char[m_nMaxLength];
	if(NULL == m_pBuffer)
	{
		return S_FALSE;
	} // 结束 if(NULL == m_pBuffer)

	m_pHead = (PPACKAGEHEAD)m_pBuffer;
	memset(m_pHead, 0, m_nLength);
	m_pHead->nSign = PACKAGE_SIGN;
	m_pHead->dwVersion = 1;
	m_pHead->dwLength = 0;

	return S_OK;
}

/*!
\brief   向包缓存区中增加内容
\param   const void * pBuf：要增加的内容指针
\param   int nLength      ：内容的长度（单位：字节）
\return  类型为 int 。成功返回S_OK，否则返回S_FALSE。
\version 1.0
\author  康  林
\date    2007-8-13 12:18:51
*/
int CSendData::AddContent(const void * pBuf, int nLength)
{
	char * pBuffer = NULL;

	//ASSERT(pBuf && nLength > 0);
	if(NULL == pBuf || nLength < 0)
	{
		return S_FALSE;
	} // 结束 if(NULL == pBuf || nLength < 0)

	if(m_nLength + nLength > m_nMaxLength)
	{
		//重新分配内存
		m_nMaxLength = m_nMaxLength + nLength + nLength;
		pBuffer = new char[m_nMaxLength];
		if(NULL == pBuffer)
		{
			return S_FALSE;
		}// 结束 if(NULL == pBuffer)

		memcpy(pBuffer, m_pBuffer, m_nLength);

		delete []m_pBuffer;
		m_pBuffer = pBuffer;
		m_pHead = (PPACKAGEHEAD)m_pBuffer;
	}// 结束 if(m_nLength + nLength > m_nMaxLength)

	memcpy(m_pBuffer + m_nLength, pBuf, nLength);
	m_nLength += nLength;
	m_pHead->dwLength += nLength;
	return S_OK;
}

/*!
\brief   要发送数据的指针
\param   无
\return  类型为 char * 。要发送数据的指针
\version 1.0
\author  康  林
\date    2007-8-13 12:19:46
*/
char * CSendData::GetBuffer()
{
	return (m_pBuffer + m_nSended);
}

/*!
\brief   要发送数据的长度
\param   无
\return  类型为 int 。要发送数据的长度
\version 1.0
\author  康  林
\date    2007-8-13 12:20:24
*/
int CSendData::GetLength()
{
	return (m_nLength - m_nSended);
}

/*!
\brief   设置已经发送数据的长度
\param   int nLength：已经发送数据的长度
\return  类型为 int 。成功返回S_OK，否则返回S_FALSE。
\version 1.0
\author  康  林
\date    2007-8-13 12:20:54
*/
int CSendData::SetSended(int nLength)
{
	m_nSended += nLength;
	return S_OK;
}

/*!
\brief   清除缓存区，释放内存
\param   无
\return  类型为 int 。成功返回S_OK，否则返回S_FALSE。
\version 1.0
\author  康  林
\date    2007-8-13 12:21:23
*/
int CSendData::Clear()
{
	if(m_pBuffer)
	{
		delete []m_pBuffer;
	}// 结束 if(m_pBuffer)
	m_nLength = 0;
	m_nMaxLength = 0;
	m_nSended = 0;
	m_pBuffer = NULL;
	m_pHead = NULL;
	return S_OK;
}

CReceiveData::CReceiveData(Network::CSocket * pSocket)
{
	ASSERT(pSocket);
	m_pSocket = pSocket;

	m_nState = ISNULL;

	m_pBuffer = NULL;
	m_nLength = 0;
	m_nReceive = 0;
	m_nReceivePackHead = 0;
}

CReceiveData::~CReceiveData(void)
{
	if(m_pBuffer)
	{
		delete []m_pBuffer;
	}// 结束 if(m_pBuffer)
	m_pBuffer = NULL;
	m_nLength = 0;
	m_nReceive = 0;
	m_nReceivePackHead = 0;
}

/*!
\brief   接收命令数据
\param   CCommand * pCmd：接收数据成功后的命令实例
\return  类型为 int 。返回当前的接收状态。
\version 1.0
\author  康  林
\date    2007-7-15 10:28:14
*/
int CReceiveData::Receive(CCommand * pCmd)
{
	int nLen = 0;
	char * pBuf = NULL;

	ASSERT(pCmd);

	switch(m_nState)
	{
	case ISCONTINUE:
		nLen = m_pSocket->Receive(m_pBuffer + m_nReceive, m_nLength - m_nReceive);
		if(SOCKET_ERROR == nLen || 0 == nLen)
		{
			return ISERROR;
		}// 结束 if(SOCKET_ERROR == nLen || 0 == nLen)
		if(m_nLength - m_nReceive == nLen)
		{
			m_nState = ISOK;
		}
		else
		{	
			m_nState = ISCONTINUE;
		} // 结束 if(m_nLength - m_nReceive == nLen)
		m_nReceive += nLen;
		break;
	case ISHEADCONTINE:
	case ISOKHEADCONTINE:
		nLen = m_pSocket->Receive(((char * )&m_PackHead) + m_nReceivePackHead, sizeof(PACKAGEHEAD) - m_nReceivePackHead);
		if(SOCKET_ERROR == nLen || 0 == nLen)
		{
			m_nState = ISERROR;
			break;
		}// 结束 if(SOCKET_ERROR == nLen || 0 == nLen)
		if(nLen < sizeof(PACKAGEHEAD) - m_nReceivePackHead)
		{
			m_nState = ISHEADCONTINE;
			break;
		}// 结束 if(nLen < sizeof(PACKAGEHEAD) - m_nReceivePackHead)
		if(nLen == sizeof(PACKAGEHEAD) - m_nReceivePackHead)
		{
			if(CheckPackageHead(&m_PackHead) != S_OK)
			{
				TRACE(_T("包头标志不对! \n"));
				m_nState = ISERROR;
				break;
			}// 结束 (_T("包头标志不对! n"))

			//报文长度
			m_nLength = m_PackHead.dwLength;
			//接收报文
			m_nState = ReceiveMessage();
		} // 结束 if(nLen == sizeof(PACKAGEHEAD) - m_nReceivePackHead)
		break;
	case ISNEXT:
		//接收报文
		m_nState = ReceiveMessage();
		break;
	default:
		//得到报文的头
		nLen = m_pSocket->Receive(&m_PackHead, sizeof(PACKAGEHEAD));
		if(SOCKET_ERROR == nLen || 0 == nLen)
		{
			return ISERROR;
		}// 结束 if(SOCKET_ERROR == nLen || 0 == nLen)
		if(nLen < sizeof(PACKAGEHEAD))
		{
			TRACE(_T("包头大小不对!"));
			m_nState = ISHEADCONTINE;
			break;
		} // 结束 if(nLen < sizeof(PACKAGEHEAD))
		if(CheckPackageHead(&m_PackHead) != S_OK)
		{
			TRACE(_T("包头标志不对! \n"));
			m_nState = ISERROR;
			break;
		}// 结束 if(CheckPackageHead(&m_nReceivePackHead) != S_OK)

		//报文长度
		m_nLength = m_PackHead.dwLength;
		//接收报文
		m_nState = ReceiveMessage();

		break;
	} // 结束 switch(m_nState)

	//初始化命令实例
	if(ISOK == m_nState)
	{
		if(pCmd->SetCommand(m_pBuffer, m_nLength) == S_OK)
		{
			//m_nState = ISOK;

			//检查是否还有下一组报文
			nLen = m_pSocket->Receive(&m_PackHead, sizeof(PACKAGEHEAD));
			if(SOCKET_ERROR != nLen)
			{
				if(nLen < sizeof(PACKAGEHEAD))
				{
					TRACE(_T("包头大小不对!"));
					m_nState = ISOKHEADCONTINE;
				} // 结束 if(nLen < sizeof(PACKAGEHEAD))
				if(CheckPackageHead(&m_PackHead) == S_OK)
				{
					m_nLength = m_PackHead.dwLength;
					m_nState = ISNEXT;
				}
				else
				{
					TRACE(_T("包头标志不对! \n"));
					m_nState = ISERROR;
				} // 结束 if(CheckPackageHead(&packHead) == S_OK)
			}// 结束 if(SOCKET_ERROR != nLen)
		}
		else
		{
			m_nState = ISERROR;
		}// 结束 if(pCmd->SetCommand(m_pBuffer, m_nLength) == S_OK)
	} // 结束 if(ISOK == m_nState)
	return m_nState;
}

/*!
\brief   接收报文
\prarm   无
\return  类型为 int 。
\version 1.0
\author  康  林
\date    2007-8-14 11:37:41
*/
int CReceiveData::ReceiveMessage()
{
	int nLen = 0;

	//申请报文缓冲区
	if(m_pBuffer)
	{
		delete m_pBuffer;
		m_pBuffer = NULL;
	}// 结束 (m_pBuffer)
	m_pBuffer = new char[m_nLength];
	if(NULL == m_pBuffer)
	{
		return NOALLOCATEBUFFER;
	} // 结束 if(NULL == m_pBuffer)

	//接收报文数据
	nLen = m_pSocket->Receive(m_pBuffer, m_nLength);
	if(nLen == m_nLength)
	{
		m_nState = ISOK;
		m_nReceive = nLen;
	}
	else
	{
		//还有数据没有全部到达
		m_nState = ISCONTINUE;
		if(SOCKET_ERROR == nLen)
		{
			//况说明接收的数据暂时还未到达
			m_nReceive = 0;			
		}
		else if(0 == nLen)      //Socket 已关闭
		{
			m_nReceive = 0;
			m_nState = ISERROR; 
		}
		else
		{
			m_nReceive = nLen;
		} // 结束 if(0 == nLen)
	} // 结束 if(nLen == m_nLength)

	return m_nState;
}

/*!
\brief   检查包头是否正确
\param   PPACKAGEHEAD pPackageHead：包头指针
\return  类型为 int 。如果正确返回S_OK，否则返回S_FALSE。
\version 1.0
\author  康  林
\date    2007-8-13 13:11:42
*/
int CReceiveData::CheckPackageHead(PPACKAGEHEAD pPackageHead)
{
	if((WORD)PACKAGE_SIGN == pPackageHead->nSign)
	{
		return S_OK;
	}// 结束 if((WORD)PACKAGE_SIGN == pPackageHead->nSign)
	return S_FALSE;
}

CSend::CSend(Network::CSocket * pSocket)
{
	m_pSocket = pSocket;
	::InitializeCriticalSection(&m_CriticalSection);
}

CSend::~CSend()
{
	::EnterCriticalSection(&m_CriticalSection);
	list < CSendData * > ::iterator it;
	for(it = m_SendData.begin(); it != m_SendData.end(); it++)
	{
		delete * it;
	}// 结束 for(it = m_SendData.begin(); it != m_SendData.end(); it++)
	m_SendData.clear();
	::LeaveCriticalSection(&m_CriticalSection);
	::DeleteCriticalSection(&m_CriticalSection);
}

/*!
\brief   发送数据，实际是先加入到发送队列，然后调用 ProcessSend 进行发送。
\param   CCommand * pCmd：命令对象
\return  类型为 int 。成功返回S_OK，失败返回 S_FALSE。
\version 1.0
\author  康  林
\date    2007-8-14 11:50:11
*/
int CSend::Send(CCommand * pCmd)
{
	int nRet = S_OK;
	CSendData * pSendData = new CSendData();
	if(NULL == pSendData)
	{
		return S_FALSE;
	}// 结束 if(NULL == pSendData)

	do 
	{
		nRet = pSendData->InitializePackage(pCmd->GetLength());
		if(S_FALSE == nRet)
		{
			break;
		}// 结束 if(S_FALSE == nRet)

		nRet = pSendData->AddContent(pCmd->GetBuffer(), pCmd->GetLength());
		if(nRet == S_FALSE)
		{
			break;
		}// 结束 if(nRet == S_FALSE)

		try
		{
			::EnterCriticalSection(&m_CriticalSection);
			m_SendData.push_back(pSendData);
			::LeaveCriticalSection(&m_CriticalSection);
		}
		catch (...)
		{
			TRACE(_T("发送数据加入到发送队列出错!"));
			::LeaveCriticalSection(&m_CriticalSection);
			nRet = S_FALSE;
			break;
		}

	} while(FALSE);

	if(S_FALSE == nRet)
	{
		delete pSendData; 
	}
	else
	{
		//发送
		nRet = ProcessSend();
	} // 结束 if(S_FALSE == nRet)
	
	return nRet;
}

/*!
\brief   发送数据
\param   无
\return  类型为 int 。成功返回S_OK，失败返回 S_FALSE。
\version 1.0
\author  康  林
\date    2007-8-14 11:51:18
*/
int CSend::ProcessSend()
{
	int nRet = S_OK;
	if(m_SendData.size() == 0)
	{
		return nRet;
	}// 结束 if(m_SendData.size() == 0)

	CSendData * pSendData = NULL;
	pSendData = *m_SendData.begin();
	//发送
	int nLen = m_pSocket->Send(pSendData->GetBuffer(), pSendData->GetLength());
	if(SOCKET_ERROR == nLen)
	{
		nRet = S_FALSE;
	}
	else if(pSendData->GetLength() == nLen)
	{
		nRet = S_OK;
		try
		{
			::EnterCriticalSection(&m_CriticalSection);
			m_SendData.pop_front();
			::LeaveCriticalSection(&m_CriticalSection);
		}
		catch (...)
		{
			::LeaveCriticalSection(&m_CriticalSection);
			nRet = S_FALSE;
		}
		delete pSendData;
	}
	else
	{
		nRet = pSendData->SetSended(nLen);
	}// 结束 if(SOCKET_ERROR == nLen)

	return nRet;
}