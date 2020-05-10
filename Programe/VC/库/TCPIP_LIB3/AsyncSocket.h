// AsyncSocket.h: interface for the CAsyncSocket class.
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

#if !defined(AFX_ASYNCSOCKET_H__980B05BD_A250_40D0_AD92_4F31AEC90E74__INCLUDED_)
#define AFX_ASYNCSOCKET_H__980B05BD_A250_40D0_AD92_4F31AEC90E74__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SpoofBase.h"

//Message handlers
#define WM_BASE				WM_USER
#define WM_SOCKET_GENERAL	WM_BASE+1
#define WM_SOCKET_ACCEPT	WM_BASE+2
#define WM_SOCKET_CONNECT	WM_BASE+3
#define WM_SOCKET_TIMEOUT	WM_BASE+4

//Definitions for no messaging
#define NO_OnSocketTimeout	virtual BOOL OnSocketTimeout() {return TRUE;}
#define NO_OnSocketConnect	virtual BOOL OnSocketConnect(int iErrorCode) {return TRUE;}
#define NO_OnSocketAccept	virtual BOOL OnSocketAccept(int iErrorCode) {return TRUE;}
#define NO_OnSocketClose	virtual BOOL OnSocketClose(int iErrorCode) {return TRUE;}
#define NO_OnSocketOOB		virtual BOOL OnSocketOOB(int iErrorCode) {return TRUE;}
#define NO_OnSocketWrite	virtual BOOL OnSocketWrite(int iErrorCode) {return TRUE;}
#define NO_OnSocketReceive	virtual BOOL OnSocketReceive(int iErrorCode) {return TRUE;}

class CBinaryTree;

class CAsyncSocket : protected CSpoofBase
	
{
	friend LRESULT CALLBACK SocketMessageHandler(HWND hwnd,      // handle to window
							  					 UINT uMsg,      // message identifier
												 WPARAM wParam,  // first message parameter
												 LPARAM lParam);

public:
	//Indicate a system shutdown
	void Shutdown();

	//Disable the time
	BOOL KillTimer();

	//Create a timeout
	BOOL SetTimeout(int iMs);

	//Set the instace of our app
	void SetInstance(HINSTANCE hInst);

	//ctor and dtor
	CAsyncSocket();
	virtual ~CAsyncSocket();
protected:
	//Messaging methods
	virtual BOOL OnSocketTimeout()=0;
	virtual BOOL OnSocketConnect(int iErrorCode)=0;
	virtual BOOL OnSocketAccept(int iErrorCode)=0;
	virtual BOOL OnSocketClose(int iErrorCode)=0;
	virtual BOOL OnSocketOOB(int iErrorCode)=0;
	virtual BOOL OnSocketWrite(int iErrorCode)=0;
	virtual BOOL OnSocketReceive(int iErrorCode)=0;

	//Get the ID of the socket
	int GetSocketID();

	//Get the handle of the window
	HWND getWindowHandle();

	//Get the socket handle
	virtual SOCKET GetAsyncHandle()=0;

	//Go to async regular mode
	virtual BOOL SetAsync()=0;

	//Remove the socket from the list
	void RemoveSocketFromList();

	//Add the socket to the list
	void AddSocketToList();
private:
	//Remove the handlers
	BOOL RemoveHandlers();

	//Get the instance of our APP
	HINSTANCE GetInstance();

	//Create our handlers
	BOOL SetHandlers();
	
	//Register our window
	BOOL RegisterWindow();

	//Find a socket
	static CAsyncSocket* GetSocketByID(int iSockID);
	
	//Our list of sockets
	static CBinaryTree* m_SocketTree;

	//Do we have a window handle
	static BOOL m_Window;

	//Our window's handle
	static HWND m_WindowHandle;

	//Instance of our window
	HINSTANCE m_Instance;

	//ID of our socket
	int m_SocketID;

	//Are we in the list
	BOOL m_List;
private:
	//Our shutdown class (all of this to avoid father to know his sons)
	class CAsyncShutdown : protected CSpoofBase
	{
	public:
		CAsyncShutdown();
		virtual ~CAsyncShutdown();
	protected:
		//Shutdown notifier
		virtual void NotifyShutdown();
	};
};

#endif // !defined(AFX_ASYNCSOCKET_H__980B05BD_A250_40D0_AD92_4F31AEC90E74__INCLUDED_)
