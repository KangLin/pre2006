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
	} // ���� if(m_Server)
	if(m_pMagSocket)
	{
		delete m_pMagSocket;
	} // ���� if(m_pMagSocket)
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
	//���ض�̬���ӿ�
	nRet = LoadDLL();
	if(S_OK == nRet)
	{
		//����ͨѸ
		nRet = Communicate();
	}// ���� if(S_OK == nRet)
	return nRet;
}

INT CGlobal::LoadDLL()
{
	INT nRet = S_OK;

	nRet = m_Dll.Load();
	if(S_FALSE == nRet)
	{
		TRACE(_T("%S(%d):���ض�̬���ӿ����\n"), __FILE__, __LINE__);
	}// ���� if(S_FALSE == nRet)

	return nRet;
}

INT CGlobal::Communicate()
{
	INT nRet = S_OK;
	m_pMagSocket = new CManageSocket;
	try
	{
		//�˶����� CManageSocket ���ͷ�
		Network::CTcpSocketLister * pLister = new Network::CTcpSocketLister(m_nPort);
		if(NULL == pLister)
		{
			return S_FALSE;
		}// ���� if(NULL == pLister)
		m_pServer = new CNetManageServer;
		if(NULL == m_pServer)
		{
			return S_FALSE;
		}// ���� if(NULL == m_pServer)
		m_pServer->SetDLL(&m_Dll);
		m_pMagSocket->AddLister(pLister, m_pServer);
		m_pMagSocket->OnRun();
	}
	catch(CTException e)
	{
		TRACE(_T("�쳣��%s\n"), e.what());
		nRet = S_FALSE;
	}

	return nRet;
}