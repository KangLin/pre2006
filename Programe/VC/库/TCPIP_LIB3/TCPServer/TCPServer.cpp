// TCPServer.cpp : Defines the entry point for the console application.
//
/*
 *
 *
 *  Copyright (c) 2000 Barak Weichselbaum <barak@komodia.com>
 *  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 *
 * Contact info:
 * Site: http://www.komodia.com
 * Email: barak@komodia.com
 */

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
	clt->Listen(5);

	printf("Telnet to 127.0.0.1 port 1000\n");

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
