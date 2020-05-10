#include "StdAfx.h"
#include ".\command.h"
#include "ManageServer.h"

CManageServer::CManageServer(void)
{
}

CManageServer::~CManageServer(void)
{
	TRACE(_T("CManageServer::~CManageServer\n"));
	//ע��ֻ�ͷ� pCmd ���ڴ棬Socket ���ڴ��� CManageSocket �ͷ�
	list<PCONNECT> ::iterator it;
	for(it = m_Connect.begin(); it != m_Connect.end(); it++)
	{
		PCONNECT p =*it;
		if(p->pReceive)
		{
			delete p->pReceive;
		}// ���� if(p->pReceive)
		if(p->pSend)
		{
			delete p->pSend;
		} // ���� if(p->pSend)
		delete p;
	}// ���� for(it = m_Connect.begin(); it != m_Connect.end(); it++)
	m_Connect.clear();
}

/*!
\brief   ���ӿͻ��ˣ���ʵ��������һ������
\param   Network::CSocket * pSock��
\return  ����Ϊ int ��
\version 1.0
\author  ��  ��
\date    2007-8-14 15:20:25
*/
int CManageServer::AddClient(Network::CSocket * pSock)
{
	int nRet = S_OK;
	ASSERT(pSock);
	PCONNECT pConnect = new CONNECT;
	if(NULL == pConnect)
	{
		return S_FALSE;
	}// ���� if(NULL == pConnect)
	memset(pConnect, 0, sizeof(CONNECT));


	pConnect->pSocket = pSock;
	CReceiveData * pReceive = new CReceiveData(pSock);
	if(NULL == pReceive)
	{
		return S_FALSE;
	}// ���� if(NULL == pReceive)
	pConnect->pReceive = pReceive;

	CSend * pSend = new CSend(pSock);
	if(NULL == pSend)
	{
		delete pReceive;
		return S_FALSE;
	} // ���� if(NULL == pSend)
	pConnect->pSend = pSend;


	try
	{
		m_Connect.push_back(pConnect);
	}
	catch(...)
	{
		nRet = S_FALSE;
	}

	return nRet;
}

int CManageServer::RemoveClient(Network::CSocket * pSock)
{
	
	list<PCONNECT>::iterator it;
	for(it = m_Connect.begin(); it != m_Connect.end(); it++)
	{
		PCONNECT p = *it;
		if(p->pSocket == pSock)
		{
			TRACE(_T("RemoveClient socket:%d\n"), pSock->GetFd());
			//ע��ֻ�ͷ� pReceive ���ڴ棬Socket ���ڴ��� CManageSocket �ͷ�
			if(p->pReceive)
			{
				delete p->pReceive;
			}// ���� if(p->pReceive)
			if(p->pSend)
			{
				delete p->pSend;
			} // ���� if(p->pSend)
			delete p;

			//���б���ɾ���ڵ�
			m_Connect.erase(it);

			return S_OK;
		} // ���� if(p->pSocket == pSock)
	}// ���� for(it = m_Connect.begin(); it != m_Connect.end(); it++)
	return S_FALSE;
}

/*!
\brief   �������ݽ����¼�
\param   Network::CSocket * pSock��
\return  ����Ϊ bool ��
\version 1.0
\author  ��  ��
\date    2007-7-28 17:00:35
*/
bool CManageServer::ProcessReadEvent(Network::CSocket * pSock)
{
	bool bRet = TRUE;
	BOOL bExist = FALSE;
	ASSERT(pSock);
	PCONNECT pConnect = NULL;

	list<PCONNECT>::iterator it;
	for(it = m_Connect.begin(); it != m_Connect.end(); it++)
	{
		if((*it)->pSocket == pSock)
		{
			pConnect = *it;
			break;
		} // ���� if((*it)->pSocket == pSock)
	} // ���� for(it = m_Connect.begin(); it != m_Connect.end(); it++)

	if(NULL == pConnect)
	{
		TRACE(_T("Error:Socket ������.\n"));
		return FALSE;
	}// ���� if(NULL == pConnect)

	int nRet = 0;

	do
	{
		//��ȡ����
		CCommand cmd;
		nRet = pConnect->pReceive->Receive(&cmd);
		switch(nRet)
		{
		case CReceiveData::ISNULL:
			bRet = TRUE;
			continue;
		case CReceiveData::ISOK:
		case CReceiveData::ISNEXT:
		case CReceiveData::ISOKHEADCONTINE:   //�Ѷ������ݲ���,����һ����ͷû�ж���
			break;
		case CReceiveData::ISCONTINUE:        //ֻ������������
		case CReceiveData::ISHEADCONTINE:     //ֻ�������ְ�ͷ����
			continue;
		case CReceiveData::ISERROR:           //�����д�,����FLASE,��CManageSocket �е� HandleIO �ͷŵ��� Socket.
		case CReceiveData::NOALLOCATEBUFFER:  //�����ڴ����
		default:                              //�д�,����FLASE,��CManageSocket �е� HandleIO �ͷŵ��� Socket.
			bRet = FALSE;
			continue;
		}// ���� switch(nRet)

		ProcessCommand(cmd, pConnect);

	} while(CReceiveData::ISNEXT == nRet);

	return bRet;
}

/*!
\brief   �������������
\param   CCommand & cmd   ������
\param   PCONNECT pConnect��������ָ��
\return  ����Ϊ int ���ɹ�����S_OK�����򷵻�FALSE��
\version 1.0
\author  ��  ��
\date    2007-8-21 17:49:37
*/
int CManageServer::ProcessCommand(CCommand & cmd, PCONNECT pConnect)
{
	int nRet = S_OK;
	return nRet;
}

/*!
\brief   �������¼�����Socket��дʱ���͵��ô˺����������ݷ���
\param   Network::CSocket * pSock��
\return  ����Ϊ bool ���ɹ�����TRUE��ʧ�ܷ���FALSE����Socket�رա�
\version 1.0
\author  ��  ��
\date    2007-8-14 15:21:01
*/
bool CManageServer::ProcessWriteEvent(Network::CSocket * pSock)
{
	bool bRet = TRUE;
	ASSERT(pSock);
	PCONNECT pConnect = NULL;

	list<PCONNECT>::iterator it;
	for(it = m_Connect.begin(); it != m_Connect.end(); it++)
	{
		if((*it)->pSocket == pSock)
		{
			pConnect = *it;
			break;
		} // ���� if((*it)->pSocket == pSock)
	} // ���� for(it = m_Connect.begin(); it != m_Connect.end(); it++)

	if(NULL == pConnect)
	{
		TRACE(_T("Error:Socket ������.\n"));
		return FALSE;
	}// ���� if(NULL == pConnect)

	//�޸�:����
	pConnect->pSend->ProcessSend();

	return bRet;
}

int CManageServer::Send(Network::CSocket * pSock, CCommand * pCmd)
{
	int nRet = S_OK;
	ASSERT(pSock);
	PCONNECT pConnect = NULL;

	list<PCONNECT>::iterator it;
	for(it = m_Connect.begin(); it != m_Connect.end(); it++)
	{
		if((*it)->pSocket == pSock)
		{
			pConnect = *it;
			break;
		} // ���� if((*it)->pSocket == pSock)
	} // ���� for(it = m_Connect.begin(); it != m_Connect.end(); it++)

	if(NULL == pConnect)
	{
		TRACE(_T("Error:Socket ������.\n"));
		return S_FALSE;
	}// ���� if(NULL == pConnect)

	pConnect->pSend->Send(pCmd);

	return nRet;
}

int CManageServer::CheckTimeouts()
{
	return 0;
}