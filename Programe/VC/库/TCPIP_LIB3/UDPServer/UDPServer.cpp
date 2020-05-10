// UDPServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ClientSocket.h"
#include <windows.h>

void GeneralErrorMessage(CClientSocket* icmp,char* cError)
{
	printf("%s\n",cError);

	icmp->Close();
	((CSpoofSocket*)icmp)->ShutdownSockets();

	delete icmp;
}

class CLog : public CSpoofBase::CSpoofLog
{
	public:
		//ctor and dtor
		CLog(){;}
		virtual ~CLog(){;}
	protected:
		//Report an error must overide
		virtual void ReportCatchError(LPSTR lpClass,LPSTR lpMethod,LPSTR lpMessage) 
		{
			printf("Caught error in class: %s, method: %s, message: %s",lpClass,lpMethod,lpMessage);
		}

		virtual void ReportInitiatedError(LPSTR lpClass,LPSTR lpMethod,LPSTR lpMessage)
		{
			printf("Initiated message in class: %s, method: %s, message: %s",lpClass,lpMethod,lpMessage);
		}

		virtual void ReportSocketError(LPSTR lpClass,LPSTR lpMethod,int iErrorCode)
		{
			printf("Socket error in class: %s, method: %s, error code: %d",lpClass,lpMethod,iErrorCode);
		}
};

int main(int argc, char* argv[])
{
	//Our socket
	CClientSocket* clt;
	clt=new CClientSocket;

	CLog* pLog;
	pLog=new CLog;

	((CSpoofSocket*)clt)->SetLog(pLog);

	//Initalize data
	if (!((CSpoofSocket*)clt)->InitializeSockets())
	{
		GeneralErrorMessage(clt,"Sockets couldn't be initialized");
		return 1;
	}

	clt->SetInstance(NULL);

	//Create and bind
	if (!clt->CreateRegular())
	{
		GeneralErrorMessage(clt,"Socket couldn't be created");
		return 1;
	}
	
	clt->Bind("127.0.0.1",1000);
	clt->Listen();

	printf("UDPServer listens on 127.0.0.1 port 1000\n");

	//If there is no message map, then receive won't work
	MSG msg;

	//Set the message map to zeros
	memset(&msg,0,sizeof(msg));

	while (GetMessage(&msg, NULL, 0, 0))
	{
		//Dispatch the message
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	//Shutdown
	clt->Close();
	((CSpoofSocket*)clt)->ShutdownSockets();

	delete pLog;

	//Self deleting
	//delete clt;

	return 0;
}
