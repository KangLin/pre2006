// SpoofBase.h: interface for the CSpoofBase class.
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

#if !defined(AFX_SPOOFBASE_H__3760FA30_2B52_4F62_9EB6_46640C36E4F1__INCLUDED_)
#define AFX_SPOOFBASE_H__3760FA30_2B52_4F62_9EB6_46640C36E4F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//windows sockets2
#include <winsock2.h>
#include <ws2tcpip.h>

#define ERROR_HANDLER(METHOD_NAME)	\
	catch (...)\
	{\
		/*Get the last error*/\
		ReportError(METHOD_NAME);\
	}

#define ERROR_HANDLER_RETURN(METHOD_NAME,RETURN_VALUE)	\
	catch (...)\
	{\
		/*Get the last error*/\
		ReportError(METHOD_NAME);\
		return RETURN_VALUE;\
	}

#define ERROR_HANDLER_AMBIG(BASE_CLASS,METHOD_NAME)	\
	catch (...)\
	{\
		/*Get the last error*/\
		BASE_CLASS::ReportError(METHOD_NAME);\
	}

#define ERROR_HANDLER_AMBIG_RETURN(BASE_CLASS,METHOD_NAME,RETURN_VALUE)	\
	catch (...)\
	{\
		/*Get the last error*/\
		BASE_CLASS::ReportError(METHOD_NAME);\
		return RETURN_VALUE;\
	}

//Handles basic errors
class CSpoofBase  
{
public:
	//The external log
	class CSpoofLog
	{
		friend class CSpoofBase;
	public:
		//ctor and dtor
		CSpoofLog();
		virtual ~CSpoofLog();
	protected:
		//Report an error must overide
		virtual void ReportCatchError(LPSTR lpClass,LPSTR lpMethod,LPSTR lpMessage)=0;
		virtual void ReportInitiatedError(LPSTR lpClass,LPSTR lpMethod,LPSTR lpMessage)=0;
		virtual void ReportSocketError(LPSTR lpClass,LPSTR lpMethod,int iErrorCode)=0;
	};
public:
	//Convert long to string
	char FAR * LongToString(long lAddr);

	//Save a new log
	void SetLog(CSpoofLog* pLog);

	//Initialize the sockets
	BOOL InitializeSockets();

	//Shutdown the sockets
	BOOL ShutdownSockets();

	//Get the last error
	int GetLastError();
	
	//ctor and dtor
	CSpoofBase();
	virtual ~CSpoofBase();
protected:
	//Report an unknown error (use GetLastError)
	void ReportError(LPSTR lpMethod);

	//Shutdown notifier
	virtual void NotifyShutdown();

	//Register shutdown class
	void RegisterShutdown(CSpoofBase* pBase);

	//Report an error
	void ReportError(LPSTR lpMethod,LPSTR lpMessage);

	//Report and error
	virtual void ReportError(LPSTR lpMethod,int iErrorCode);

	//Set the name of the current class
	void SetName(LPSTR lpName);

	//Set the socket last error
	void SetLastError(LPSTR lpMethod);
	void SetLastError(LPSTR lpMethod,int iErrorCode);
private:
	//Last error we had
	int m_LastError;

	//Our log
	static CSpoofLog* m_Log;

	//Are we initialized
	static BOOL m_Initialized;

	//Our class name
	LPSTR m_lpClassName;

	//Class to notify
	static CSpoofBase* m_pShutdownClass;
};

#endif // !defined(AFX_SPOOFBASE_H__3760FA30_2B52_4F62_9EB6_46640C36E4F1__INCLUDED_)
