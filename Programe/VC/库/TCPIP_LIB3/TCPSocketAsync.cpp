// TCPSocketAsync.cpp: implementation of the CTCPSocketAsync class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TCPSocketAsync.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTCPSocketAsync::CTCPSocketAsync() : CTCPSocket(), CAsyncSocket()
{

}

CTCPSocketAsync::~CTCPSocketAsync()
{

}

BOOL CTCPSocketAsync::Connect(int iSourcePort,LPCSTR lpDestinationAddress,int iDestinationPort)
{
	try
	{
		//Set the async notification
		int iResult;
		iResult=WSAAsyncSelect(getHandle(),getWindowHandle(),WM_SOCKET_CONNECT,FD_CONNECT);

		if (iResult)
		{
			CTCPSocket::SetLastError("Connect");
			return FALSE;
		}

		//Call the original connect
		BOOL bResult;
		bResult=CTCPSocket::Connect(iSourcePort,lpDestinationAddress,iDestinationPort);

		if (bResult)
			AddSocketToList();
		else
			CTCPSocket::ReportError("Connect","Failed to connect!");

		return bResult;
	}
	ERROR_HANDLER_AMBIG_RETURN(CSpoofSocket,"Connect",FALSE)
}

BOOL CTCPSocketAsync::Listen(int iBackLog)
{
	try
	{
		int iResult;
		
		iResult=WSAAsyncSelect(getHandle(),getWindowHandle(),WM_SOCKET_ACCEPT,FD_ACCEPT);
		if (iResult)
		{
			CTCPSocket::SetLastError("Listen");
			return FALSE;
		}

		return CTCPSocket::Listen(iBackLog);
	}
	ERROR_HANDLER_AMBIG_RETURN(CSpoofSocket,"Listen",FALSE)
}

BOOL CTCPSocketAsync::SetAsync()
{
	try
	{
		//Set event to read / write / close / oob
		int iResult;

		iResult=WSAAsyncSelect(getHandle(),getWindowHandle(),WM_SOCKET_GENERAL,FD_WRITE | FD_READ | FD_CLOSE | FD_OOB);
		if (iResult)
		{
			CTCPSocket::SetLastError("SetAsync");
			return FALSE;
		}
		
		return TRUE;
	}
	ERROR_HANDLER_AMBIG_RETURN(CSpoofSocket,"SetAsync",FALSE)
}

BOOL CTCPSocketAsync::OnSocketConnect(int iErrorCode)
{
	//First set async again
	return SetAsync();
}

void CTCPSocketAsync::Accepted()
{
	try
	{
		AddSocketToList();

		//Go to async mode
		SetAsync();
	}
	ERROR_HANDLER_AMBIG(CSpoofSocket,"CTCPSocketAsync")
}

SOCKET CTCPSocketAsync::GetAsyncHandle()
{
	return getHandle();
}

BOOL CTCPSocketAsync::CreateRegular()
{
	try
	{
		if (!CTCPSocket::CreateRegular())
			return FALSE;
		else
		{
			AddSocketToList();
			return TRUE;
		}
	}
	ERROR_HANDLER_AMBIG_RETURN(CSpoofSocket,"CreateRegular",FALSE)
}

BOOL CTCPSocketAsync::Create()
{
	try
	{
		if (!CTCPSocket::Create())
			return FALSE;
		else
		{
			AddSocketToList();
			return TRUE;
		}
	}
	ERROR_HANDLER_AMBIG_RETURN(CSpoofSocket,"Create",FALSE)
}