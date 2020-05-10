// ICMPSocketAsync.cpp: implementation of the CICMPSocketAsync class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ICMPSocketAsync.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CICMPSocketAsync::CICMPSocketAsync()
{

}

CICMPSocketAsync::~CICMPSocketAsync()
{

}

BOOL CICMPSocketAsync::SetAsync()
{
	try
	{
		//Set event to read / write / close / oob
		int iResult;

		iResult=WSAAsyncSelect(getHandle(),getWindowHandle(),WM_SOCKET_GENERAL,FD_WRITE | FD_READ);
		if (iResult)
		{
			CICMPSocket::SetLastError("SetAsync");
			return FALSE;
		}
		
		return TRUE;
	}
	ERROR_HANDLER_AMBIG_RETURN(CSpoofSocket,"SetAsync",FALSE)
}

BOOL CICMPSocketAsync::OnSocketReceive(int iErrorCode)
{
	try
	{
		//Here we receive the data
		if (!iErrorCode)
		{
			//Buffer
			char* buf;
			buf=new char[ICMP_BUF];

			//Read the data
			int iRead;
			iRead=Receive(buf,ICMP_BUF);

			BOOL bResult=FALSE;

			//Only if not an error
			if (iRead!=SOCKET_ERROR)
				bResult=ProccessICMP(buf);
			
			//Clean up
			delete [] buf;
			return bResult;
		}
		else
			return FALSE;
	}
	ERROR_HANDLER_AMBIG_RETURN(CSpoofSocket,"OnSocketReceive",FALSE)
}

BOOL CICMPSocketAsync::Create()
{
	try
	{
		if (!CICMPSocket::Create())
		{
			CICMPSocket::ReportError("Create","Failed to create ICMP socket!");
			return FALSE;
		}

		AddSocketToList();

		return SetAsync();
	}
	ERROR_HANDLER_AMBIG_RETURN(CSpoofSocket,"Create",FALSE)
}

SOCKET CICMPSocketAsync::GetAsyncHandle()
{
	return getHandle();
}