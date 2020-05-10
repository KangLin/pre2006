#include "StdAfx.h"
#include "ManageService.h"
#include "Service.h"

CManageService::CManageService(void)
{
}

CManageService::~CManageService(void)
{
}

int CManageService::AddConnect(CSocket * pSocket)
{
	int nRet = S_OK;
	ASSERT(pSocket);
	if(NULL == pSocket)
	{
		return S_FALSE;
	}// ���� if(NULL == pSocket)

	CService * pConnect = NULL;
	vector < CConnect * > ::iterator it;
	for(it = m_Connect.begin(); it != m_Connect.end(); it++)
	{
		pConnect = (CService * )*it;
		if(pConnect->m_pSocket == pSocket)
		{
			TRACE(_T("�������Ѿ�����\n"));
			return 1;
		} // ���� if(pConnect->m_pSock == pSocket)
	} // ���� for(it = m_Connect.begin(); it != m_Connect.end(); it++)

	try
	{
		pConnect = new CService(pSocket);
		if(pConnect)	 
		{
			m_Connect.push_back(pConnect);
		}// ���� if(pConnect)
	}
	catch(...)
	{
		nRet = S_FALSE;
	}

	return nRet;
}