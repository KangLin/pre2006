// PingSocket.cpp: implementation of the CPingSocket class.
//
//////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPingSocket::CPingSocket() : CICMPSocketAsync()
{
	m_PingDone=TRUE;
}

CPingSocket::~CPingSocket()
{

}

BOOL CPingSocket::OnSocketReceive(int iErrorCode)
{
	//Reset the timer
	KillTimer();

	if (CICMPSocketAsync::OnSocketReceive(iErrorCode))
	{
		//Check if it is our ping
		if (GetLastICMPHeader()->sICMP.sUS.us1==GetCurrentProcessId())
		{
			//Can print data
			printf("Reply from %s: bytes=%i time=%ims TTL=%i\n",
				CSpoofSocket::LongToString(GetLastIPHeader()->sourceIPAddress),
		     	   GetLastDataSize(),
				   GetTickCount()-m_LastTick,
				   GetLastIPHeader()->TTL);

			//Set ping done
			m_PingDone=TRUE;
		}
	}

	return TRUE;
}

BOOL CPingSocket::PingDone()
{
	return m_PingDone;
}

void CPingSocket::Ping(LPCSTR lpDestinationAddress)
{
	//Set the timeout
	SetTimeout(1000);

	//Set ping timer
	m_LastTick=GetTickCount();

	//Set ping done
	m_PingDone=FALSE;

	SendEcho(lpDestinationAddress,FALSE,GetCurrentProcessId(),0,0);
}

BOOL CPingSocket::OnSocketTimeout()
{
	//Kill the timer
	KillTimer();

	printf("Request timed out.\n");

	//Set available new ping
	m_PingDone=TRUE;

	return FALSE;
}
