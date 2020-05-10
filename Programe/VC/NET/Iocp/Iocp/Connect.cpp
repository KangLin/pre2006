#include "StdAfx.h"
#include "Connect.h"

CConnect::CConnect(CSocket * pSocket)
{
	ASSERT(pSocket);
	if(NULL == pSocket)
	{
		CTException e(_T("Socket Ϊ��ָ��"));
		throw e;
	} // ���� if(NULL == pSocket)

	m_pSocket = pSocket;
	m_pSendData = new CSendData();
	m_pRecvData = new CRecvData();

}

CConnect::~CConnect(void)
{
	if(m_pRecvData)
	{
		delete m_pRecvData;
	} // ���� if(m_pRecvData)
	if(m_pSendData)
	{
		delete m_pSendData;
	} // ���� if(m_pSendData)
	if(m_pSocket)
	{
		delete m_pSocket;
	} // ���� if(m_pSocket)
}

/*!
\brief   OnHandleIOEvent
\param   void * pPara��
\return  ����Ϊ int ������ 1=��;2=д;3=�ر�;����=����
\version 1.0
\author  ��  ��
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