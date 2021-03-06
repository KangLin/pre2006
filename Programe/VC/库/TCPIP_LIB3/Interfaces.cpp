// Interfaces.cpp: implementation of the CInterfaces class.
//
//////////////////////////////////////////////////////////////////////
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
#include "Interfaces.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define CInterfaces_Class "CInterfaces"
#define CHECK_POSITION(METHOD_NAME,RETURN_VALUE)	\
	if (m_iPosition>=m_iStructures)\
	{\
		ReportError(METHOD_NAME,"Passed over!");\
		return RETURN_VALUE;\
	}

CInterfaces::CInterfaces(int iMaxInterfaces) : CSpoofBase()
{
	try
	{
		//Set our name
		SetName(CInterfaces_Class);

		//Allocate the information
		m_iMaxInterfaces=iMaxInterfaces;

		//No structures retreived
		m_iStructures=0;

		//No position
		m_iPosition=0;

		//Allocate our info
		if (!iMaxInterfaces)
			m_pInfo=NULL;
		else
			m_pInfo=new INTERFACE_INFO[m_iMaxInterfaces];
	}
	ERROR_HANDLER("CInterfaces")
}

CInterfaces::~CInterfaces()
{
	try
	{
		delete m_pInfo;
	}
	ERROR_HANDLER("~CInterfaces")
}

BOOL CInterfaces::GetInterfaces()
{
	if (!m_iMaxInterfaces)
	{
		//structure not allocated
		ReportError("GetInterfaces","You constructed the class with 0 parameter!");
		return FALSE;
	}

	try
	{
		//Allocate a socket
		SOCKET sok;
		sok=socket(AF_INET,SOCK_DGRAM,0);

		//Check it's valid
		if (sok==INVALID_SOCKET)
		{
			SetLastError("GetInterfaces");
			return FALSE;
		}

		//Get the interface list
		unsigned long ulBytes;
		if (WSAIoctl(sok,SIO_GET_INTERFACE_LIST,NULL,NULL,m_pInfo,
					 sizeof(INTERFACE_INFO)*m_iMaxInterfaces,&ulBytes,NULL,NULL))
		{
			SetLastError("GetInterfaces");

			//Close the socket
			closesocket(sok);

			return FALSE;
		}

		//Check how many structures we have
		m_iStructures=ulBytes/sizeof(INTERFACE_INFO);

		//Set our position to zero
		m_iPosition=0;

		//Close the socket
		closesocket(sok);

		return TRUE;
	}
	ERROR_HANDLER_RETURN("GetInterfaces",FALSE)
}

long CInterfaces::GetAddress()
{
	CHECK_POSITION("GetAddress",0)
	
	try
	{
		return (m_pInfo+m_iPosition)->iiAddress.AddressIn.sin_addr.S_un.S_addr;
	}
	ERROR_HANDLER_RETURN("GetAddress",0);
}

BOOL CInterfaces::MoveNext()
{
	++m_iPosition;
	return m_iPosition<m_iStructures;
}

long CInterfaces::GetMask()
{
	CHECK_POSITION("GetMask",0)
	
	try
	{
		return (m_pInfo+m_iPosition)->iiNetmask.AddressIn.sin_addr.S_un.S_addr;
	}
	ERROR_HANDLER_RETURN("GetMask",0);
}

long CInterfaces::GetBroadcast()
{
	CHECK_POSITION("GetBroadcast",0)
	
	try
	{
		return (m_pInfo+m_iPosition)->iiBroadcastAddress.AddressIn.sin_addr.S_un.S_addr;
	}
	ERROR_HANDLER_RETURN("GetBroadcast",0);
}

BOOL CInterfaces::IsRunning()
{
	return GetFlags() & IFF_UP;
}

BOOL CInterfaces::IsBroadcast()
{
	return GetFlags() & IFF_BROADCAST;
}

BOOL CInterfaces::IsLoopback()
{
	return GetFlags() & IFF_LOOPBACK;
}

BOOL CInterfaces::IsPPP()
{
	return GetFlags() & IFF_POINTTOPOINT;
}

BOOL CInterfaces::IsMulticast()
{
	return GetFlags() & IFF_MULTICAST;
}

long CInterfaces::GetFlags()
{
	CHECK_POSITION("GetFlags",0)
	
	try
	{
		return (m_pInfo+m_iPosition)->iiFlags;
	}
	ERROR_HANDLER_RETURN("GetFlags",0);
}
