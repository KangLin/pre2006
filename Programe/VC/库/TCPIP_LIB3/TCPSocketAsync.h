// TCPSocketAsync.h: interface for the CTCPSocketAsync class.
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

#if !defined(AFX_TCPSOCKETASYNC_H__1D78325D_C154_4B21_97E5_320394FD47EF__INCLUDED_)
#define AFX_TCPSOCKETASYNC_H__1D78325D_C154_4B21_97E5_320394FD47EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TCPSocket.h"
#include "AsyncSocket.h"

class CTCPSocketAsync : 
	public CTCPSocket, 
	public CAsyncSocket
{
public:
	//Our async connection
	virtual BOOL Connect(int iSourcePort,LPCSTR lpDestinationAddress,int iDestinationPort);

	//Listen to incoming connections
	virtual BOOL Listen(int iBackLog);

	//Create this socket as a regular socket
	virtual BOOL CreateRegular();
	
	//Create as a raw socket
	virtual BOOL Create();

	//ctor and dtor
	CTCPSocketAsync();
	virtual ~CTCPSocketAsync();
protected:
	//Go to async mode
	virtual BOOL SetAsync();

	//Set the socket to async mode
	virtual BOOL OnSocketConnect(int iErrorCode);

	//When the socket is accepted, what to do
	virtual void Accepted();

	//Get the socket handle
	virtual SOCKET GetAsyncHandle();
};

#endif // !defined(AFX_TCPSOCKETASYNC_H__1D78325D_C154_4B21_97E5_320394FD47EF__INCLUDED_)
