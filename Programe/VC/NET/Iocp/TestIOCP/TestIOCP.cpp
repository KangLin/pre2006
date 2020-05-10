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
		//��ʼ�� Socket ��
		if(S_OK != InitalizeSocket())
		{
			CTException e(_T("��ʼ��SOCKET��ʧ��"));
			throw e;
		}// ���� (_T("��ʼ��SOCKET��ʧ��"))

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
		TRACE(_T("�쳣:%s\n"), e.what());
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
		TRACE(_T("�ܹ���������:%d\n"), MngConnect.GetTotalConnectNumber());
		TRACE(_T("��ǰ������:%d\n"), MngConnect.GetConnectNumber());
		TRACE(_T("�ܹ��ļ�����:%d\n"), MngListen.GetTotalListenNumber());
		TRACE(_T("��ǰ������:%d\n\n"), MngListen.GetListenNumber());
	} // ���� while(TRUE)
}

int _tmain(int argc, _TCHAR* argv[])
{

	_tsetlocale(LC_ALL, _T(".OCP"));

	//TextTCPSocket();
	TestLister();

	return 0;
}

