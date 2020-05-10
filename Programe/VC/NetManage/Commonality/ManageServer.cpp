#include "StdAfx.h"
#include ".\command.h"
#include "ManageServer.h"

CManageServer::CManageServer(void)
{
}

CManageServer::~CManageServer(void)
{
	TRACE(_T("CManageServer::~CManageServer\n"));
	//注意只释放 pCmd 的内存，Socket 的内存由 CManageSocket 释放
	list<PCONNECT> ::iterator it;
	for(it = m_Connect.begin(); it != m_Connect.end(); it++)
	{
		PCONNECT p =*it;
		if(p->pReceive)
		{
			delete p->pReceive;
		}// 结束 if(p->pReceive)
		if(p->pSend)
		{
			delete p->pSend;
		} // 结束 if(p->pSend)
		delete p;
	}// 结束 for(it = m_Connect.begin(); it != m_Connect.end(); it++)
	m_Connect.clear();
}

/*!
\brief   增加客户端，其实就是增加一个连接
\param   Network::CSocket * pSock：
\return  类型为 int 。
\version 1.0
\author  康  林
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
	}// 结束 if(NULL == pConnect)
	memset(pConnect, 0, sizeof(CONNECT));


	pConnect->pSocket = pSock;
	CReceiveData * pReceive = new CReceiveData(pSock);
	if(NULL == pReceive)
	{
		return S_FALSE;
	}// 结束 if(NULL == pReceive)
	pConnect->pReceive = pReceive;

	CSend * pSend = new CSend(pSock);
	if(NULL == pSend)
	{
		delete pReceive;
		return S_FALSE;
	} // 结束 if(NULL == pSend)
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
			//注意只释放 pReceive 的内存，Socket 的内存由 CManageSocket 释放
			if(p->pReceive)
			{
				delete p->pReceive;
			}// 结束 if(p->pReceive)
			if(p->pSend)
			{
				delete p->pSend;
			} // 结束 if(p->pSend)
			delete p;

			//从列表中删除节点
			m_Connect.erase(it);

			return S_OK;
		} // 结束 if(p->pSocket == pSock)
	}// 结束 for(it = m_Connect.begin(); it != m_Connect.end(); it++)
	return S_FALSE;
}

/*!
\brief   处理数据接收事件
\param   Network::CSocket * pSock：
\return  类型为 bool 。
\version 1.0
\author  康  林
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
		} // 结束 if((*it)->pSocket == pSock)
	} // 结束 for(it = m_Connect.begin(); it != m_Connect.end(); it++)

	if(NULL == pConnect)
	{
		TRACE(_T("Error:Socket 不存在.\n"));
		return FALSE;
	}// 结束 if(NULL == pConnect)

	int nRet = 0;

	do
	{
		//读取命令
		CCommand cmd;
		nRet = pConnect->pReceive->Receive(&cmd);
		switch(nRet)
		{
		case CReceiveData::ISNULL:
			bRet = TRUE;
			continue;
		case CReceiveData::ISOK:
		case CReceiveData::ISNEXT:
		case CReceiveData::ISOKHEADCONTINE:   //已读出内容部分,但下一个包头没有读完
			break;
		case CReceiveData::ISCONTINUE:        //只读出部分数据
		case CReceiveData::ISHEADCONTINE:     //只读出部分包头数据
			continue;
		case CReceiveData::ISERROR:           //数据有错,返回FLASE,由CManageSocket 中的 HandleIO 释放掉此 Socket.
		case CReceiveData::NOALLOCATEBUFFER:  //分配内存出错
		default:                              //有错,返回FLASE,由CManageSocket 中的 HandleIO 释放掉此 Socket.
			bRet = FALSE;
			continue;
		}// 结束 switch(nRet)

		ProcessCommand(cmd, pConnect);

	} while(CReceiveData::ISNEXT == nRet);

	return bRet;
}

/*!
\brief   处理解包后的命令
\param   CCommand & cmd   ：命令
\param   PCONNECT pConnect：上下文指针
\return  类型为 int 。成功返回S_OK，否则返回FALSE。
\version 1.0
\author  康  林
\date    2007-8-21 17:49:37
*/
int CManageServer::ProcessCommand(CCommand & cmd, PCONNECT pConnect)
{
	int nRet = S_OK;
	return nRet;
}

/*!
\brief   处理发送事件。当Socket可写时，就调用此函数进行数据发送
\param   Network::CSocket * pSock：
\return  类型为 bool 。成功返回TRUE；失败返回FALSE，则Socket关闭。
\version 1.0
\author  康  林
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
		} // 结束 if((*it)->pSocket == pSock)
	} // 结束 for(it = m_Connect.begin(); it != m_Connect.end(); it++)

	if(NULL == pConnect)
	{
		TRACE(_T("Error:Socket 不存在.\n"));
		return FALSE;
	}// 结束 if(NULL == pConnect)

	//修改:发送
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
		} // 结束 if((*it)->pSocket == pSock)
	} // 结束 for(it = m_Connect.begin(); it != m_Connect.end(); it++)

	if(NULL == pConnect)
	{
		TRACE(_T("Error:Socket 不存在.\n"));
		return S_FALSE;
	}// 结束 if(NULL == pConnect)

	pConnect->pSend->Send(pCmd);

	return nRet;
}

int CManageServer::CheckTimeouts()
{
	return 0;
}