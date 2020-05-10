// SpoofBase.cpp: implementation of the CSpoofBase class.
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
#include "SpoofBase.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSpoofBase::CSpoofBase()
{
	try
	{
		//No name
		m_lpClassName=NULL;

		//Set it
		SetName("CSpoofBase");
	}
	ERROR_HANDLER("CSpoofBase")
}

CSpoofBase::~CSpoofBase()
{
	try
	{
		//Dispose of the name
		free(m_lpClassName);
	}
	ERROR_HANDLER("~CSpoofBase")
}

void CSpoofBase::SetLastError(LPSTR lpMethod)
{
	try
	{
		//First set the error
		m_LastError=WSAGetLastError();

		//Check if there is an error
		if (m_LastError)
			ReportError(m_lpClassName,m_LastError);
	}
	ERROR_HANDLER("SetLastError")
}

void CSpoofBase::SetLastError(LPSTR lpMethod,int iErrorCode)
{
	try
	{
		//First set the error
		m_LastError=iErrorCode;

		//Check if there is an error
		if (m_LastError)
			ReportError(m_lpClassName,m_LastError);
	}
	ERROR_HANDLER("SetLastError")
}

//----------------------- CSpoofBase start -----------------------
CSpoofBase::CSpoofLog* CSpoofBase::m_Log=NULL;

CSpoofBase::CSpoofLog::CSpoofLog()
{
}

CSpoofBase::CSpoofLog::~CSpoofLog()
{
}
//----------------------- CSpoofBase end -----------------------

void CSpoofBase::SetName(LPSTR lpName)
{
	try
	{
		//if exists dispose of it
		if (m_lpClassName)
			free(m_lpClassName);

		m_lpClassName=strdup(lpName);
	}
	ERROR_HANDLER("SetName")
}

void CSpoofBase::ReportError(LPSTR lpMethod,int iErrorCode)
{
	try
	{
		if (m_Log)
			//Report to the log
			m_Log->ReportSocketError(m_lpClassName,lpMethod,iErrorCode);
	}
	catch (...)
	{
		//Can't do anything to avoid circular catch
	}
}

void CSpoofBase::ReportError(LPSTR lpMethod, LPSTR lpMessage)
{
	try
	{
		if (m_Log)
			//Report to the log
			m_Log->ReportInitiatedError(m_lpClassName,lpMethod,lpMessage);
	}
	catch (...)
	{
		//Can't do anything to avoid circular catch
	}
}

int CSpoofBase::GetLastError()
{
	return m_LastError;
}

BOOL CSpoofBase::m_Initialized=FALSE;

BOOL CSpoofBase::InitializeSockets()
{
	//To avoid double initialize
	if (m_Initialized)
		return TRUE;

	try
	{
		//Initialize the sockets
		WORD wVersionRequested;
		WSADATA wsaData;
		int err;
 
		wVersionRequested = MAKEWORD( 2, 2 );
 
		err = WSAStartup( wVersionRequested, &wsaData );
		if (err!=0)
			/* Tell the user that we could not find a usable */
			/* WinSock DLL.                                  */
			return FALSE;
 
		/* Confirm that the WinSock DLL supports 2.2.*/
		/* Note that if the DLL supports versions greater    */
		/* than 2.2 in addition to 2.2, it will still return */
		/* 2.2 in wVersion since that is the version we      */
		/* requested.                                        */
 
		if (LOBYTE(wsaData.wVersion)!=2 || HIBYTE(wsaData.wVersion)!=2)
		{
			/* Tell the user that we could not find a usable */
			/* WinSock DLL.                                  */
			WSACleanup();
			return FALSE;
		}

		m_Initialized=TRUE;

		return TRUE;
	}
	ERROR_HANDLER_RETURN("InitializeSockets",FALSE)
}

BOOL CSpoofBase::ShutdownSockets()
{
	//Only if initialized
	if (!m_Initialized)
		return TRUE;

	try
	{
		//Notify shutdown class
		if (m_pShutdownClass)
		{
			m_pShutdownClass->NotifyShutdown();
			delete m_pShutdownClass;
		}

		if (WSACleanup()==SOCKET_ERROR)
		{
			SetLastError("ShutdownSockets");
			return FALSE;
		}
		
		m_Initialized=TRUE;
		return TRUE;
	}
	ERROR_HANDLER_RETURN("ShutdownSockets",FALSE)
}

void CSpoofBase::NotifyShutdown()
{
}

void CSpoofBase::RegisterShutdown(CSpoofBase* pBase)
{
	try
	{
		//Check if we already have a class
		if (m_pShutdownClass)
			delete m_pShutdownClass;

		m_pShutdownClass=pBase;
	}
	ERROR_HANDLER("RegisterShutdown")
}


CSpoofBase* CSpoofBase::m_pShutdownClass=NULL;

void CSpoofBase::SetLog(CSpoofLog *pLog)
{
	//Save the new log
	m_Log=pLog;
}

void CSpoofBase::ReportError(LPSTR lpMethod)
{
	try
	{
		//Unknown error
		LPVOID lpMsgBuf;

		FormatMessage( 
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM | 
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			GetLastError(),
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
			(LPTSTR) &lpMsgBuf,
			0,
			NULL);

		//Report the error
		ReportError(lpMethod,(LPSTR)lpMsgBuf);

		//Free the resources
		LocalFree(lpMsgBuf);
	}
	catch (...)
	{
	}
}

char FAR * CSpoofBase::LongToString(long lAddr)
{
	try
	{
		//First create the address
		in_addr addr;

		//Assign it
		addr.S_un.S_addr=lAddr;

		//Return the value
		return inet_ntoa(addr);
	}
	ERROR_HANDLER_RETURN("LongToString",NULL)
}

