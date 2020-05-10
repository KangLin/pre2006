#include "StdAfx.h"
#include "ManageNet.h"

CManageNet::CManageNet(void)
{
	//��ʼ�� Socket ��
	if(S_OK != InitalizeSocket())
	{
		CTException e(_T("��ʼ��SOCKET��ʧ��"));
		throw e;
	}// ���� if(S_OK != InitalizeSocket())

	m_pConnect = NULL;
	m_pListen = NULL;
}

CManageNet::~CManageNet(void)
{
	if(m_pListen)
	{
		delete m_pListen;
	}// ���� if(m_pListen)
	if(m_pConnect)
	{
		delete m_pConnect;
	} // ���� if(m_pConnect)
}

/*!
\brief   ��ʼ��CManageListen��CManageConnect����
\param   CManageListen * pMngListen  �������������
\param   CManageConnect * pMngConnect�����ӹ������
\return  ����Ϊ int ���ɹ�����S_OK,ʧ�ܷ���S_FALSE.
\version 1.0
\author  ��  ��
\date    2007-9-28 8:51:45
*/
int CManageNet::Initalize(CManageConnect * pMngConnect, CManageListen * pMngListen)
{
	int nRet = S_OK;
	if(NULL == pMngListen)
	{
		m_pListen = new CManageListen(this);
		if(NULL == m_pListen)
		{
			return S_FALSE;
		} // ���� if(NULL == pMngListen)
	}
	else
	{
		m_pListen = pMngListen;
	}// ���� if(NULL == pMngListen)
	if(pMngConnect)
	{
		m_pConnect = pMngConnect;
	}
	else
	{
		m_pConnect = new CManageConnect;
		if(NULL == m_pConnect)
		{
			return S_FALSE;
		} // ���� if(NULL == m_pConnect)
	} // ���� if(pMngConnect)
	return nRet;
}

/*!
\brief   AddListen
\param   int nPort�������˿�
\return  ����Ϊ int ���ɹ����ؼ���SOCKET�ľ��,ʧ�ܷ��ظ�ֵ.(ע�ⷵ��ֵ��������)
\version 1.0
\author  ��  ��
\date    2007-9-28 8:56:04
*/
int CManageNet::AddListen(int nPort)
{
	int nRet = S_OK;

	nRet = m_pListen->AddListen(nPort);

	return nRet;
}

/*!
\brief   ɾ������
\param   int nFd��
\return  ����Ϊ int ��
\version 1.0
\author  ��  ��
\date    2007-9-28 19:10:00
*/
int CManageNet::RemoveListen(int nFd)
{
	int nRet = S_OK;
	nRet = m_pListen->RemoveListen(nFd);
	return nRet;
}

/*!
\brief   AddConncet
\param   CSocket * pSocket��
\return  ����Ϊ int ���ɹ�����S_OK,ʧ�ܷ���S_FALSE
\version 1.0
\author  ��  ��
\date    2007-9-28 8:57:51
*/
int CManageNet::AddConncet(CSocket * pSocket)
{
	return m_pConnect->AddConnect(pSocket);
}

/*!
\brief   RemoveConnect
\param   CSocket * pSock��
\return  ����Ϊ int ���ɹ�����S_OK,ʧ�ܷ���S_FALSE
\version 1.0
\author  ��  ��
\date    2007-9-28 8:59:55
*/
int CManageNet::RemoveConnect(CSocket * pSock)
{
	return m_pConnect->RemoveConnect(pSock);
}