// UDPSocketAsync.cpp: implementation of the CUDPSocketAsync class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "UDPSocketAsync.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUDPSocketAsync::CUDPSocketAsync() : CUDPSocket(), CAsyncSocket()
{

}

CUDPSocketAsync::~CUDPSocketAsync()
{

}

BOOL CUDPSocketAsync::Listen()
{
	try
	{
		int iResult;
		
		iResult=WSAAsyncSelect(getHandle(),getWindowHandle(),WM_SOCKET_GENERAL,FD_READ);
		if (iResult)
		{
			CUDPSocket::SetLastError("Listen");
			return FALSE;
		}

		return TRUE;
	}
	ERROR_HANDLER_AMBIG_RETURN(CSpoofSocket,"Listen",FALSE)
}

BOOL CUDPSocketAsync::SetAsync()
{
	try
	{
		//Set event to read / write 
		int iResult;

		iResult=WSAAsyncSelect(getHandle(),getWindowHandle(),WM_SOCKET_GENERAL,FD_WRITE | FD_READ);
		if (iResult)
		{
			CUDPSocket::SetLastError("SetAsync");
			return FALSE;
		}
		
		return TRUE;
	}
	ERROR_HANDLER_AMBIG_RETURN(CSpoofSocket,"SetAsync",FALSE)
}

BOOL CUDPSocketAsync::OnSocketConnect(int iErrorCode)
{
	//First set async again
	return SetAsync();
}

void CUDPSocketAsync::Accepted()
{
	try
	{
		AddSocketToList();

		//Go to async mode
		SetAsync();
	}
	ERROR_HANDLER_AMBIG(CSpoofSocket,"CTCPSocketAsync")
}

SOCKET CUDPSocketAsync::GetAsyncHandle()
{
	return getHandle();
}

BOOL CUDPSocketAsync::CreateRegular()
{
	try
	{
		if (!CUDPSocket::CreateRegular())
			return FALSE;
		else
		{
			AddSocketToList();
			return TRUE;
		}
	}
	ERROR_HANDLER_AMBIG_RETURN(CSpoofSocket,"CreateRegular",FALSE)
}

BOOL CUDPSocketAsync::Create()
{
	try
	{
		if (!CUDPSocket::Create())
			return FALSE;
		else
		{
			AddSocketToList();
			return TRUE;
		}
	}
	ERROR_HANDLER_AMBIG_RETURN(CSpoofSocket,"Create",FALSE)
}