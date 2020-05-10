// kping.cpp : Defines the entry point for the console application.
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
#include "PingSocket.h"
#include <windows.h>

void UsageErrorMessage(char* cProgramName)
{
	printf("Usage:\n");
	printf("%s <host>\n",cProgramName);
}

void HostErrorMessage(char* cHost)
{
	printf("Host:%s is invalid\n",cHost);
}

void GeneralErrorMessage(CPingSocket* icmp,char* cError)
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
	//First check parameters
	if (argc<2)
	{
		UsageErrorMessage(argv[0]);
		return 1;
	}

	//Our IP address
	char IP[16]="";

	//Our socket
	CPingSocket* icmp;
	icmp=new CPingSocket;

	//Set our log
	CLog* pLog;
	pLog=new CLog;

	((CSpoofSocket*)icmp)->SetLog(pLog);

	//Initalize data
	if (!((CSpoofSocket*)icmp)->InitializeSockets())
	{
		GeneralErrorMessage(icmp,"Sockets couldn't be initialized");
		return 1;
	}

	//Check if it's an address
	if ((*argv[1]>='a' && *argv[1]<='z') || 
		(*argv[1]>='A' && *argv[1]<='Z'))
	{
		//Try to resolve the DNS
		long addr;
		addr=icmp->ResolveDNS(argv[1]);

		if (addr)
			//OK
			memcpy(IP,((CSpoofSocket*)icmp)->LongToString(addr),16);
		else
		{
			HostErrorMessage(argv[1]);

			delete icmp;
			return 1;
		}
	}
	else
	{
		//Check address validity


		if (strlen(argv[1])>15)
		{
			HostErrorMessage(argv[1]);
			delete icmp;
			return 1;
		}

		memcpy(IP,argv[1],strlen(argv[1]));
	
		//Check validity
		if (!icmp->ValidAddress(IP))
		{
			HostErrorMessage(IP);
			delete icmp;
			return 1;
		}
	}

	icmp->SetInstance(NULL);

	//Create and bind
	if (!icmp->Create())
	{
		GeneralErrorMessage(icmp,"Socket couldn't be created");
		return 1;
	}
	
	printf("Pinging:%s\n\n",IP);

	int iMaxCount=5;

	int iCount=iMaxCount;

	//If there is no message map, then receive won't work
	MSG msg;

	//Set the message map to zeros
	memset(&msg,0,sizeof(msg));

	while ((icmp->PingDone() || GetMessage(&msg, NULL, 0, 0)) && iCount) 
	{
		if (icmp->PingDone())
		{
			--iCount;

			//Ping
			icmp->Ping(IP);
		}
		
		//Only we had a message
		if (msg.hwnd)
		{
			//Dispatch the message
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			//Again rezero
			memset(&msg,0,sizeof(msg));
		}
	}

	//Shutdown
	icmp->Close();
	((CSpoofSocket*)icmp)->ShutdownSockets();

	//No log 
	delete pLog;

	//No need to delete, shutdown deletes all async sockets
	//Dispose
	//delete icmp;

	return 0;
}
