// TestIOCP.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "..\IOCP\TCPSock.h"
#include "..\iocp\TCPListenSocket.h"
#include <locale.h>
#include "..\Iocp\ManageNet.h"
#include "..\Iocp\ManageIOCPConnect.h"

void TextTCPSocket()
{
	try
	{
		//初始化 Socket 库
		if(S_OK != InitalizeSocket())
		{
			CTException e(_T("初始化SOCKET库失败"));
			throw e;
		}// 结束 (_T("初始化SOCKET库失败"))

		CTCPSocket * pSocket = new CTCPSocket(_T("192.168.101.180"), 5150);
		TRACE(_T("%s:%d;%s\n"), pSocket->GetMyAddress().c_str(),pSocket->GetMyPort(),pSocket->GetMyEndpoint().c_str());
		TRACE(_T("%s:%d;%s\n"), pSocket->GetPeerAddress().c_str(),pSocket->GetPeerPort(),pSocket->GetPeerEndpoint().c_str());
		_tstring sztmp=_T("okokok");
		pSocket->Send((void*)sztmp.c_str(),sizeof(TCHAR)*sztmp.size());
		char buf[100];
		int len = 0;
		memset(buf,0,100);
		pSocket->Recv(buf,len);
		TRACE(_T("%d:%s\n"),len,buf);
		delete pSocket;
	}
	catch(CTException e)
	{
		TRACE(_T("异常:%s\n"), e.what());
	}
}

void TestLister()
{
	CManageNet net;
	CManageIOCPConnect MngConnect;
	CManageListen MngListen(&net);
	net.Initalize(&MngConnect, &MngListen);
	net.AddListen(5000);
	while(TRUE)
	{
		Sleep(1000);
		TRACE(_T("总共的连接数:%d\n"), MngConnect.GetTotalConnectNumber());
		TRACE(_T("当前连接数:%d\n"), MngConnect.GetConnectNumber());
		TRACE(_T("总共的监听数:%d\n"), MngListen.GetTotalListenNumber());
		TRACE(_T("当前监听数:%d\n\n"), MngListen.GetListenNumber());
	} // 结束 while(TRUE)
}

int _tmain(int argc, _TCHAR* argv[])
{

	_tsetlocale(LC_ALL, _T(".OCP"));

	//TextTCPSocket();
	TestLister();

	return 0;
}

