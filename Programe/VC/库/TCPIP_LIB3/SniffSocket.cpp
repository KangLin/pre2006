// SniffSocket.cpp: implementation of the CSniffSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SniffSocket.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSniffSocket::CSniffSocket() : CSpoofSocket(), CAsyncSocket()
{
}

CSniffSocket::~CSniffSocket()
{
	RemoveSocketFromList();
}

BOOL CSniffSocket::Sniff(BOOL bSniff)
{
	try
	{
		if (CSpoofSocket::Sniff(bSniff))
			return !WSAAsyncSelect(getHandle(),getWindowHandle(),WM_SOCKET_GENERAL,FD_READ);
		else
			return FALSE;
	}
	ERROR_HANDLER_AMBIG_RETURN(CSpoofSocket,"Sniff",FALSE)
}
	

BOOL CSniffSocket::Create()
{
	try
	{
		SetProtocol(IPPROTO_IP);
		if (CSpoofSocket::Create(IPPROTO_IP))
		{
			AddSocketToList();
			return TRUE;
		}
		else
			return FALSE;
	}
	ERROR_HANDLER_AMBIG_RETURN(CSpoofSocket,"Create",FALSE)
}

SOCKET CSniffSocket::GetAsyncHandle()
{
	return getHandle();
}

BOOL CSniffSocket::SetAsync()
{
	//Do nothing
	return TRUE;
}
