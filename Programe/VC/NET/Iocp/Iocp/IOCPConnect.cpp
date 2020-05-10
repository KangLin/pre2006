#include "StdAfx.h"
#include "IOCPConnect.h"

CIOCPConnect::CIOCPConnect(CSocket * pSocket, HANDLE hCompletion): CConnect(pSocket)
{
	//把SOCKET绑定到完成端口
	if(CreateIoCompletionPort((HANDLE)pSocket->GetFd(), hCompletion, (DWORD)this, 0) == NULL)
	{
		CTException e(_T("CreateIoCompletionPort failed with error %d\n"), GetLastError());
		throw e;
	}
	::InitializeCriticalSection(&m_csQueue);

	if(S_OK != PostIOCPRecvEvent())
	{
		CTException e(_T("投递接收端口失败"));
		throw e;
	} // 结束 if(S_OK != PostIOCPRecvEvent())
}

CIOCPConnect::~CIOCPConnect(void)
{
	::DeleteCriticalSection(&m_csQueue);
}

int CIOCPConnect::Lock()
{
	::EnterCriticalSection(&m_csQueue);
	return S_OK;
}

int CIOCPConnect::UnLock()
{
	::LeaveCriticalSection(&m_csQueue);
	return S_OK;
}

int CIOCPConnect::PostIOCPRecvEvent()
{
	int nRet = S_OK;

	DWORD dwRecvBytes = 0;
	DWORD dwFlag = 0;
	LPPER_IO_OPERATION_DATA pData = NULL;
	Lock();
	if(!m_qIODataBuf.empty())
	{
		pData = m_qIODataBuf.front();
		m_qIODataBuf.pop();
	} // 结束 if(!m_qIODataBuf.empty())
	UnLock();
	if(NULL == pData)
	{
		pData = new PER_IO_OPERATION_DATA;
		if(NULL == pData)
		{
			return S_FALSE;
		} // 结束 if(NULL == pData)
	}// 结束 if(NULL == pData)
	memset(pData, 0, sizeof(PER_IO_OPERATION_DATA));
	pData->DataBuf.buf = pData->Buffer;
	pData->DataBuf.len = DATA_BUFFER_SIZE;
	pData->nOption = IOCP_RECV;
	if(WSARecv(m_pSocket->GetFd(), &(pData->DataBuf), 1, &dwRecvBytes, &dwFlag,
		&(pData->Overlapped), NULL) == SOCKET_ERROR)
	{
		if (WSAGetLastError() != ERROR_IO_PENDING)
		{
			TRACE(_T("WSASend() failed with error %d\n"), WSAGetLastError());
			return S_FALSE;
		}
	}
	return S_OK;
}

/*!
\brief   处理重叠IO
\param   void * pPara：
\return  类型为 int 。返回 1=读;2=写;3=关闭;负数=错误
\version 1.0
\author  康  林
\date    2007-9-28 10:01:33
*/
int CIOCPConnect::OnHandleIOEvent(DWORD dwBytesTransferred, void * pPara /* = NULL */)
{
	int nRet = S_OK;
	if(0 == dwBytesTransferred)
	{
		TRACE(_T("关闭\n"));
		return 3;
	}// 结束 if(0 == nBCGPMenuGroupID)

	LPPER_IO_OPERATION_DATA pData = CONTAINING_RECORD(pPara, PER_IO_OPERATION_DATA, Overlapped);

	switch(pData->nOption)
	{
	case IOCP_RECV:
		OnRecv(pData->Buffer, dwBytesTransferred);
		Lock();
		try
		{
			m_qIODataBuf.push(pData);
		}
		catch(...)
		{
			
		}
		UnLock();
		PostIOCPRecvEvent();
		break;
	case IOCP_WRITE:
		pData->nTransferred += dwBytesTransferred;
		PostIOCPWriteEvent(pData);
		break;
	default:
		break;
	} // 结束 switch(pData->nOption)

	return nRet;
}

int CIOCPConnect::PostIOCPWriteEvent(LPPER_IO_OPERATION_DATA pData)
{
	DWORD dwSendBytes = 0;
	int nRet = S_OK;

	pData->DataBuf.len = pData->nLength - pData->nTransferred;
	pData->DataBuf.buf = pData->Buffer + pData->nTransferred;
	pData->nOption = IOCP_WRITE;
	memset(&pData->Overlapped, 0, sizeof(OVERLAPPED));
	if(pData->DataBuf.len > 0)
	{
		if(WSASend(m_pSocket->GetFd(), &(pData->DataBuf), 1, &dwSendBytes, 0,
			&(pData->Overlapped), NULL) == SOCKET_ERROR)
		{
			nRet = WSAGetLastError();
			if(nRet != ERROR_IO_PENDING)
			{
				TRACE(_T("WSASend() failed with error %d\n"), nRet);
				return nRet;
			}
		}
	}
	else
	{
		Lock();
		m_qIODataBuf.push(pData);
		UnLock();
	} // 结束 if(pData->DataBuf.len > 0)
	return nRet;
}

int CIOCPConnect::OnSend(void * pBuf, int nLen)
{
	int nRet = S_OK;
	
	LPPER_IO_OPERATION_DATA pData = NULL;
	Lock();
	if(!m_qIODataBuf.empty())
	{
		pData = m_qIODataBuf.front();
		m_qIODataBuf.pop();
	} // 结束 if(!m_qIODataBuf.empty())
	UnLock();
	if(NULL == pData)
	{
		pData = new PER_IO_OPERATION_DATA;
		if(NULL == pData)
		{
			return S_FALSE;
		} // 结束 if(NULL == pData)
	}// 结束 if(NULL == pData)
	memcpy(pData->Buffer, pBuf, nLen);
	pData->nLength = nLen;
	pData->nTransferred = 0;
	return PostIOCPWriteEvent(pData);
}

int CIOCPConnect::OnRecv(void * pBuf, int nLen)
{
	int nRet = S_OK;
	OnSend(pBuf, nLen);
	return nRet;
}