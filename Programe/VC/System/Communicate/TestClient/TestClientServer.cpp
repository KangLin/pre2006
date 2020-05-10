#include "StdAfx.h"
#include "TestClientServer.h"
#include "..\..\..\NetManage\Commonality\DefineCommand.h"
#include "..\..\..\NetManage\Commonality\command.h"
#include <atltime.h>

CTestClientServer::CTestClientServer(void)
{
	m_pSocket = NULL;
}

CTestClientServer::~CTestClientServer(void)
{
}

int CTestClientServer::AddClient(Network::CSocket * pSock)
{
	CManageServer::AddClient(pSock);

	m_pSocket = pSock;
	
	return S_OK;
}

int CTestClientServer::ProcessCommand(CCommand & cmd, CManageServer::PCONNECT pConnect)
{
	int nRet = S_OK;
	switch(cmd.GetCommand())
	{
	case CMD_ANSWER_ECHO:
		{
			DWORD dwErr = S_OK;
			cmd.GetPara(&dwErr);
			CTime time = CTime::GetCurrentTime();
			_tstring szTmp;
			cmd.GetPara(&szTmp);
			TRACE(_T("Time:%d:%d:%d; ²âÊÔ»ØÏÔÓ¦´ð(%d)£º%s\n"), time.GetHour(), time.GetMinute(), time.GetSecond(), pConnect->pSocket->GetFd(), szTmp.c_str());
		}
		break;
	default:
		break;
	}

	

	return nRet;
}

bool CTestClientServer::ProcessWriteEvent(Network::CSocket * pSock)
{
	CCommand cmd;
	int len = 9000;

	cmd.SetCommand(CMD_TEST_ECHO);
	TCHAR * buf = new TCHAR[100];
	try
	{
		CTime time = CTime::GetCurrentTime();

		_tstring szTemp;
		_stprintf(buf, _T("Time:%d:%d:%d; Test echo Socket:%d"), time.GetHour(), time.GetMinute(), time.GetSecond(), pSock->GetFd());
		szTemp = buf;
		cmd.AddPara(szTemp.c_str());
		Send(m_pSocket, &cmd);
	}
	catch(...)
	{
		TRACE(_T(" CTestClientServer::ProcessWriteEvent exception\n"));
	}


	return TRUE;
}