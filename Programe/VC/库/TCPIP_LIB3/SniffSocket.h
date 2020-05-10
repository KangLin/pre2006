// SniffSocket.h: interface for the CSniffSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SNIFFSOCKET_H__B694EA57_2BC0_483C_897E_80256AC3D059__INCLUDED_)
#define AFX_SNIFFSOCKET_H__B694EA57_2BC0_483C_897E_80256AC3D059__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SpoofSocket.h"
#include "AsyncSocket.h"

class CSniffSocket : 
	public CSpoofSocket,
	public CAsyncSocket
{
public:
	//Create the socket
	BOOL Create();

	//ctor and dtor
	CSniffSocket();
	virtual ~CSniffSocket();

	//Turn to be a sniffer socket
	virtual BOOL Sniff(BOOL bSniff);
protected:
	//Get the socket handle
	virtual SOCKET GetAsyncHandle();

	//Go to async mode
	virtual BOOL SetAsync();

	NO_OnSocketTimeout
	NO_OnSocketConnect
	NO_OnSocketAccept
	NO_OnSocketClose
	NO_OnSocketOOB	
	NO_OnSocketWrite
};

#endif // !defined(AFX_SNIFFSOCKET_H__B694EA57_2BC0_483C_897E_80256AC3D059__INCLUDED_)
