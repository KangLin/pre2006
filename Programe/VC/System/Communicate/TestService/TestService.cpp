// TestService.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
	_tsetlocale(LC_ALL, _T(".OCP"));
	CManageSocket * pMag = new CManageSocket;
	Network::CTcpSocketLister * pLister = new Network::CTcpSocketLister(5000);
	pMag->AddLister(pLister, NULL);
	pMag->OnRun();
	
	delete pMag;

	return 0;
}

