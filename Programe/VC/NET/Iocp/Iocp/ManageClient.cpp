#include "StdAfx.h"
#include "ManageClient.h"
#include "Client.h"

CManageClient::CManageClient(void)
{
}

CManageClient::~CManageClient(void)
{
}

int CManageClient::AddConnect(CSocket * pSocket)
{
	int nRet = S_OK;
	ASSERT(pSocket);
	if(NULL == pSocket)
	{
		return S_FALSE;
	}// 结束 if(NULL == pSocket)

	CClient * pConnect = NULL;
	vector < CConnect * > ::iterator it;
	for(it = m_Connect.begin(); it != m_Connect.end(); it++)
	{
		pConnect = (CClient*)*it;
		if(pConnect->m_pSocket == pSocket)
		{
			TRACE(_T("此连接已经存在\n"));
			return 1;
		} // 结束 if(pConnect->m_pSock == pSocket)
	} // 结束 for(it = m_Connect.begin(); it != m_Connect.end(); it++)

	try
	{
		pConnect = new CClient(pSocket);
		if(pConnect)
		{
			m_Connect.push_back(pConnect);
		}// 结束 if(pConnect)
	}
	catch(...)
	{
		nRet = S_FALSE;
	}

	return nRet;
}