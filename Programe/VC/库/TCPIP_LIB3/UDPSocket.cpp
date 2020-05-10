// UDPSocket.cpp: implementation of the CUDPSocket class.
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
#include "UDPSocket.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUDPSocket::CUDPSocket() : CSpoofSocket()
{
}

CUDPSocket::~CUDPSocket()
{
}

BOOL CUDPSocket::Create()
{
	try
	{
		SetProtocol(IPPROTO_UDP);
		return CSpoofSocket::Create(IPPROTO_UDP);
	}
	ERROR_HANDLER_RETURN("Create",FALSE)
}

BOOL CUDPSocket::Send(int iSourcePort, 
					  LPCSTR lpDestinationAddress, 
					  int iDestinationPort,
					  char* buf,
					  int BufLength)
{
	try
	{
		//We can construct the UDP here
		LPUDPHeader lpUDP;
		lpUDP=new UDPHeader;

		//Set the ports
		lpUDP->SourcePort=htons(iSourcePort);
		lpUDP->DestinationPort=htons(iDestinationPort);

		//Set the length
		lpUDP->Length=htons(UDPHeaderLength);

		//Check sum
		lpUDP->Checksum=0;

		BOOL bResult;

		if (BufLength)
		{
			//Create the buffer
			int iTotalLength;
			iTotalLength=UDPHeaderLength+BufLength;

			char* tmpBuf;
			tmpBuf=new char[iTotalLength];

			//Set the length
			lpUDP->Length=htons(iTotalLength);

			memcpy(tmpBuf,lpUDP,UDPHeaderLength);
			memcpy(tmpBuf+UDPHeaderLength,buf,BufLength);
			
			//Update it
			lpUDP->Checksum=CalculatePseudoChecksum(tmpBuf,iTotalLength,lpDestinationAddress,iTotalLength);

			//Recopy it
			memcpy(tmpBuf,lpUDP,UDPHeaderLength);

			//Send it
			bResult=CSpoofSocket::Send(lpDestinationAddress,tmpBuf,iTotalLength,iDestinationPort);

			//Delete
			delete tmpBuf;
		}
		else
		{
			//Update it
			lpUDP->Checksum=CalculatePseudoChecksum((char*)lpUDP,UDPHeaderLength,lpDestinationAddress,UDPHeaderLength);

			//Send it
			bResult=CSpoofSocket::Send(lpDestinationAddress,(char*)lpUDP,UDPHeaderLength,iDestinationPort);
		}

		//Clean up
		delete lpUDP;

		return bResult;
	}
	ERROR_HANDLER_RETURN("Send",FALSE)
}

BOOL CUDPSocket::SetBroadcast(BOOL bBroadcast)
{
	try
	{
		//Set broadcast option
		
		if(setsockopt(getHandle(),SOL_SOCKET,SO_BROADCAST,(char*)&bBroadcast,sizeof(bBroadcast))==SOCKET_ERROR)
		{
			//Check for options error
			SetLastError("SetBroadcast");
			return FALSE;
		}	

		return TRUE;
	}
	ERROR_HANDLER_RETURN("SetBroadcast",FALSE)
}

BOOL CUDPSocket::CreateRegular()
{
	try
	{
		SetProtocol(IPPROTO_UDP);
		return CSpoofSocket::Create(IPPROTO_UDP);
	}
	ERROR_HANDLER_RETURN("CreateRegular",FALSE)
}
