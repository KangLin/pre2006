#include "StdAfx.h"
#include "ManageNet.h"

CManageNet::CManageNet(void)
{
	//初始化 Socket 库
	if(S_OK != InitalizeSocket())
	{
		CTException e(_T("初始化SOCKET库失败"));
		throw e;
	}// 结束 if(S_OK != InitalizeSocket())

	m_pConnect = NULL;
	m_pListen = NULL;
}

CManageNet::~CManageNet(void)
{
	if(m_pListen)
	{
		delete m_pListen;
	}// 结束 if(m_pListen)
	if(m_pConnect)
	{
		delete m_pConnect;
	} // 结束 if(m_pConnect)
}

/*!
\brief   初始化CManageListen和CManageConnect对象
\param   CManageListen * pMngListen  ：监听管理对象
\param   CManageConnect * pMngConnect：连接管理对象
\return  类型为 int 。成功返回S_OK,失败返回S_FALSE.
\version 1.0
\author  康  林
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
		} // 结束 if(NULL == pMngListen)
	}
	else
	{
		m_pListen = pMngListen;
	}// 结束 if(NULL == pMngListen)
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
		} // 结束 if(NULL == m_pConnect)
	} // 结束 if(pMngConnect)
	return nRet;
}

/*!
\brief   AddListen
\param   int nPort：临听端口
\return  类型为 int 。成功返回监听SOCKET的句柄,失败返回负值.(注意返回值是隐藏量)
\version 1.0
\author  康  林
\date    2007-9-28 8:56:04
*/
int CManageNet::AddListen(int nPort)
{
	int nRet = S_OK;

	nRet = m_pListen->AddListen(nPort);

	return nRet;
}

/*!
\brief   删除连接
\param   int nFd：
\return  类型为 int 。
\version 1.0
\author  康  林
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
\param   CSocket * pSocket：
\return  类型为 int 。成功返回S_OK,失败返回S_FALSE
\version 1.0
\author  康  林
\date    2007-9-28 8:57:51
*/
int CManageNet::AddConncet(CSocket * pSocket)
{
	return m_pConnect->AddConnect(pSocket);
}

/*!
\brief   RemoveConnect
\param   CSocket * pSock：
\return  类型为 int 。成功返回S_OK,失败返回S_FALSE
\version 1.0
\author  康  林
\date    2007-9-28 8:59:55
*/
int CManageNet::RemoveConnect(CSocket * pSock)
{
	return m_pConnect->RemoveConnect(pSock);
}