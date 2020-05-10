#include "stdafx.h"
#include "Global.h"
#include "..\..\System\Communicate\TcpSocket.h"
#include ".\NetManageServer.h"

CGlobal::CGlobal()
{
	m_pServer = NULL;
	m_pMagSocket = NULL;
	m_nPort = 5000;
}

CGlobal::~CGlobal()
{
	if(m_pServer)
	{
		delete m_pServer;
	} // 结束 if(m_Server)
	if(m_pMagSocket)
	{
		delete m_pMagSocket;
	} // 结束 if(m_pMagSocket)
}

INT CGlobal::GetDllConfig(_tstring & szName)
{
	CFileEx fe;
	_tstring szPath = fe.GetFilePath();
	_tstring szConfig = szPath + _T("\\Dll.INI");
	szName = szConfig;
	return S_OK;
}

INT CGlobal::OnDo()
{
	INT nRet = S_FALSE;
	//加载动态连接库
	nRet = LoadDLL();
	if(S_OK == nRet)
	{
		//网络通迅
		nRet = Communicate();
	}// 结束 if(S_OK == nRet)
	return nRet;
}

INT CGlobal::LoadDLL()
{
	INT nRet = S_OK;

	nRet = m_Dll.Load();
	if(S_FALSE == nRet)
	{
		TRACE(_T("%S(%d):加载动态链接库出错\n"), __FILE__, __LINE__);
	}// 结束 if(S_FALSE == nRet)

	return nRet;
}

INT CGlobal::Communicate()
{
	INT nRet = S_OK;
	m_pMagSocket = new CManageSocket;
	try
	{
		//此对象在 CManageSocket 中释放
		Network::CTcpSocketLister * pLister = new Network::CTcpSocketLister(m_nPort);
		if(NULL == pLister)
		{
			return S_FALSE;
		}// 结束 if(NULL == pLister)
		m_pServer = new CNetManageServer;
		if(NULL == m_pServer)
		{
			return S_FALSE;
		}// 结束 if(NULL == m_pServer)
		m_pServer->SetDLL(&m_Dll);
		m_pMagSocket->AddLister(pLister, m_pServer);
		m_pMagSocket->OnRun();
	}
	catch(CTException e)
	{
		TRACE(_T("异常：%s\n"), e.what());
		nRet = S_FALSE;
	}

	return nRet;
}