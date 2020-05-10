#include "StdAfx.h"
#include "ManageConnect.h"

CManageConnect::CManageConnect(void)
{
	::InitializeCriticalSection(&m_csConnect);
	m_ConnectNumber = 0;
	m_TotalConnectNumber = 0;
}

CManageConnect::~CManageConnect(void)
{
	ClearConnect();
	::DeleteCriticalSection(&m_csConnect);
}

int CManageConnect::Lock()
{
	::EnterCriticalSection(&m_csConnect);
	return S_OK;
}

int CManageConnect::UnLock()
{
	::LeaveCriticalSection(&m_csConnect);
	return S_OK;
}

int CManageConnect::Initalize()
{
	int nRet = S_OK;

	return nRet;
}

/*!
\brief   �õ���ǰ������
\param   ��
\return  ����Ϊ LONG ��
\version 1.0
\author  ��  ��
\date    2007-9-28 19:08:28
*/
LONG CManageConnect::GetConnectNumber()
{
	return m_ConnectNumber;
}

/*!
\brief   �õ��ܵ�������
\param   ��
\return  ����Ϊ LONG ��
\version 1.0
\author  ��  ��
\date    2007-9-28 19:08:39
*/
LONG CManageConnect::GetTotalConnectNumber()
{
	return m_TotalConnectNumber;
}

/*!
\brief   ��������
\param   CSocket * pSocket��SOCKET
\return  ����Ϊ int ���ɹ�����S_OK,ʧ�ܷ���S_FALSE
\version 1.0
\author  ��  ��
\date    2007-9-28 18:43:42
*/
int CManageConnect::AddConnect(CSocket * pSocket)
{
	int nRet = S_OK;
	ASSERT(pSocket);
	if(NULL == pSocket)
	{
		return S_FALSE;
	}// ���� if(NULL == pSocket)

	CConnect * pConnect = NULL;
	vector < CConnect * > ::iterator it;
	for(it = m_Connect.begin(); it != m_Connect.end(); it++)
	{
		pConnect =* it;
		if(pConnect->m_pSocket == pSocket)
		{
			TRACE(_T("�������Ѿ�����\n"));
			return 1;
		} // ���� if(pConnect->m_pSock == pSocket)
	} // ���� for(it = m_Connect.begin(); it != m_Connect.end(); it++)

	Lock();
	try
	{
		pConnect = new CConnect(pSocket);
		if(pConnect)
		{
			m_Connect.push_back(pConnect);
			InterlockedIncrement(&m_ConnectNumber);
			InterlockedIncrement(&m_TotalConnectNumber);
		}// ���� if(pConnect)
	}
	catch(...)
	{
		nRet = S_FALSE;
	}
	UnLock();

	return nRet;
}

/*!
\brief   ɾ������
\param   CSocket * pSocket��SOCKET
\return  ����Ϊ int ���ɹ�����S_OK,ʧ�ܷ���S_FALSE
\version 1.0
\author  ��  ��
\date    2007-9-28 18:44:08
*/
int CManageConnect::RemoveConnect(CSocket * pSocket)
{
	int nRet = S_FALSE;
	vector < CConnect * > ::iterator it;
	CConnect * pConnect = NULL;

	Lock();

	for(it = m_Connect.begin(); it != m_Connect.end(); it++)
	{
		pConnect = *it;
		if(pConnect->m_pSocket == pSocket)
		{
			m_Connect.erase(it);
			delete pConnect;
			nRet = S_OK;
			InterlockedDecrement(&m_ConnectNumber);
			break;
		} // ���� if(pConnect->m_pSock == pSocket)
	}// ���� for(it = m_Connect.begin(); it != m_Connect.end(); it++)

	UnLock();

	return nRet;
}

/*!
\brief   ɾ����������
\param   ��
\return  ����Ϊ int ���ɹ�����S_OK,ʧ�ܷ���S_FALSE
\version 1.0
\author  ��  ��
\date    2007-9-28 18:44:25
*/
int CManageConnect::ClearConnect()
{
	int nRet = S_OK;

	Lock();

	try
	{
		vector < CConnect * > ::iterator it;
		for(it = m_Connect.begin(); it != m_Connect.end(); it++)
		{
			delete(*it);
		}// ���� (*it)
		m_Connect.clear();
	}
	catch(...)
	{
		nRet = S_FALSE;
	}

	UnLock();

	return nRet;
}