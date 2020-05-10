// PingSocket.h: interface for the CPingSocket class.
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

#if !defined(AFX_PINGSOCKET_H__469EE2E5_24E2_4DAA_A2BD_4A7DE284F4D4__INCLUDED_)
#define AFX_PINGSOCKET_H__469EE2E5_24E2_4DAA_A2BD_4A7DE284F4D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "StdAfx.h"	// Added by ClassView
#include "..\ICMPSocketAsync.h"

class CPingSocket : public CICMPSocketAsync
{
public:
	//is the trace done
	BOOL TraceDone();

	//Do the ping
	void Ping(LPCSTR lpDestinationAddress);

	//Is the ping done ?
	BOOL PingDone();

	//ctor and dtor
	CPingSocket();
	virtual ~CPingSocket();
protected:
	NO_OnSocketAccept
	NO_OnSocketConnect
	NO_OnSocketClose
	NO_OnSocketOOB
	NO_OnSocketWrite

	virtual BOOL OnSocketTimeout();
	virtual BOOL OnSocketReceive(int iErrorCode);
private:
	//Is the trace done ?
	BOOL m_TraceDone;

	//The trace time to live
	unsigned char m_TTL;

	//Last tick the icmp was sent
	DWORD m_LastTick;
	
	//Is the ping done ?
	BOOL m_PingDone;
	
};

#endif // !defined(AFX_PINGSOCKET_H__469EE2E5_24E2_4DAA_A2BD_4A7DE284F4D4__INCLUDED_)
