// TestClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\socket.h"
#include "..\..\..\NetManage\Commonality\command.h"
#include "..\..\..\NetManage\Commonality\Data.h"
#include "..\..\..\NetManage\Commonality\DefineCommand.h"
#include "..\..\..\NetManage\Commonality\type.h"
#include "testclientserver.h"
#include <atltime.h>

_tstring szIP;
UINT nPort = 0;

void Thread(void * para)
{
	int i = 0;
	//for(i = 0; i < 1000; i++)
	{
		try
		{
			try
			{
				_tsetlocale(LC_ALL, _T(".OCP"));
				CManageSocket * pMag = new CManageSocket;
				CTestClientServer * server = new CTestClientServer;
				Network::CTcpSocket * p = new Network::CTcpSocket(szIP.c_str(), nPort);
				TRACE(_T("连接Sockeet:%d\n"), p->GetFd());

				pMag->AddConncet(p, server);			

				while(1)
				{
					CCommand cmd;
					cmd.SetCommand(CMD_TEST_ECHO);
					TCHAR * buf = new TCHAR[100];
					try
					{
						CTime time = CTime::GetCurrentTime();

						_tstring szTemp;
						_stprintf(buf, _T("Time:%d:%d:%d; Test echo Socket:%d"), time.GetHour(), time.GetMinute(), time.GetSecond(), p->GetFd());
						szTemp = buf;
						cmd.AddPara(szTemp.c_str());
						server->Send(p, &cmd);
					}
					catch(...)
					{
						TRACE(_T(" CTestClientServer::ProcessWriteEvent exception\n"));
					}
					Sleep(10);
				} // 结束 while(1)


				//pMag->OnRun();


				delete pMag;
			}
			catch(CTException e)
			{
				TRACE(_T("connect error:%s;%d\n"), e.what(), e.GetErr());
			};
		}
		catch (...)
		{
			TRACE(_T("连接异常,内存不足!\n"));

		}
	} // 结束 for(i = 0; i < 1000; i++)	
}

int _tmain(int argc, _TCHAR* argv[])
{
	_tsetlocale(LC_ALL, _T(".OCP"));
	if(argc != 3)
	{
		_tprintf(_T("TestClient IP Port\n"));
		return 1;
	}// 结束 if(argc != 3)

	szIP = argv[1];
	nPort = _ttoi(argv[2]);

	Network::InitalizeSocket();
	
	for(int i = 0; i < 100; i++)
	{
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)Thread, NULL, NULL, NULL);
	} // 结束 for(int i = 0; i < 10; i++)
	
	while(1)
	{
		Sleep(1000);
	};


	/*Network::CTcpSocket * p = NULL;
	try
	{
		p = new Network::CTcpSocket(argv[1], _ttoi(argv[2]));
		CCommand cmd;
		int len = 9000;
		
		cmd.SetCommand(CMD_TEST_ECHO);
		cmd.AddPara(_T("aaaaaaa"));
		CSend Send(p);
		Send.Send(&cmd);
	}
	catch(Network::CSocketException e)
	{
		TRACE(_T("connect error:%S;%d\n"),e.m_Text.c_str(), e.m_Err);
	};

	delete p;
	*/

	return 0;
}

