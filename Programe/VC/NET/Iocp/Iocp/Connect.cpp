#include "StdAfx.h"
#include "Connect.h"

CConnect::CConnect(CSocket * pSocket)
{
	ASSERT(pSocket);
	if(NULL == pSocket)
	{
		CTException e(_T("Socket 为空指针"));
		throw e;
	} // 结束 if(NULL == pSocket)

	m_pSocket = pSocket;
	m_pSendData = new CSendData();
	m_pRecvData = new CRecvData();

}

CConnect::~CConnect(void)
{
	if(m_pRecvData)
	{
		delete m_pRecvData;
	} // 结束 if(m_pRecvData)
	if(m_pSendData)
	{
		delete m_pSendData;
	} // 结束 if(m_pSendData)
	if(m_pSocket)
	{
		delete m_pSocket;
	} // 结束 if(m_pSocket)
}

/*!
\brief   OnHandleIOEvent
\param   void * pPara：
\return  类型为 int 。返回 1=读;2=写;3=关闭;负数=错误
\version 1.0
\author  康  林
\date    2007-9-28 10:09:16
*/
int CConnect::OnHandleIOEvent(void * pPara /* = NULL */)
{
	int nRet = S_OK;

	return nRet;
}

int CConnect::OnProcessRecvEvent()
{
	int nRet = S_OK;

	return nRet;
}

int CConnect::OnProcessWriteEvent()
{
	int nRet = S_OK;

	return nRet;
}

int CConnect::OnRecv(void * pBuf, int nLen)
{
	int nRet = S_OK;

	return nRet;
}

int CConnect::OnSend(void * pBuf, int nLen)
{
	int nRet = S_OK;

	return nRet;
}