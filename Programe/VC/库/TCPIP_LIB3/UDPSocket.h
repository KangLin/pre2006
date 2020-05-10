// UDPSocket.h: interface for the CUDPSocket class.
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

#if !defined(AFX_UDPSOCKET_H__B6FDDD18_19E2_4E61_A04E_CC6DD8583966__INCLUDED_)
#define AFX_UDPSOCKET_H__B6FDDD18_19E2_4E61_A04E_CC6DD8583966__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SpoofSocket.h"

typedef struct _UDPHeader
{
	unsigned short	SourcePort;
	unsigned short	DestinationPort;
	unsigned short	Length;
	unsigned short	Checksum;
} UDPHeader;

typedef UDPHeader FAR * LPUDPHeader;

#define UDPHeaderLength sizeof(UDPHeader)

class CUDPSocket :	public CSpoofSocket
{
public:
	//Create as aregular socket
	BOOL CreateRegular();

	//Allow UDP broadcast
	BOOL SetBroadcast(BOOL bBroadcast);

	//Send data
	BOOL Send(int iSourcePort, 
			  LPCSTR lpDestinationAddress, 
			  int iDestinationPort,
			  char* buf,
			  int BufLength);

	//Create the socket
	BOOL Create();

	//ctor and dtor
	CUDPSocket();
	virtual ~CUDPSocket();
};

#endif // !defined(AFX_UDPSOCKET_H__B6FDDD18_19E2_4E61_A04E_CC6DD8583966__INCLUDED_)
