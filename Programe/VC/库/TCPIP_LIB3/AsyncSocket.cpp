// AsyncSocket.cpp: implementation of the CAsyncSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "AsyncSocket.h"
#include "BinaryTree.h"

//Window class name
#define CAsyncSocket_Class "CAsyncSocketClass"
#define CAsyncShutdown_Class "CAsyncShutdown"

//Message handler
LRESULT CALLBACK SocketMessageHandler(HWND hwnd,      // handle to window
							  		  UINT uMsg,      // message identifier
									  WPARAM wParam,  // first message parameter
									  LPARAM lParam)   // second message parameter
													
{
	//first get the socket
	CAsyncSocket* cSock;

	cSock=CAsyncSocket::GetSocketByID((int)wParam);

	if (cSock)
		//Socket exists
		switch (uMsg)
		{
		case WM_SOCKET_GENERAL:
			if (WSAGETSELECTEVENT(lParam) == FD_READ)
				return cSock->OnSocketReceive(WSAGETSELECTERROR(lParam));
			else if (WSAGETSELECTEVENT(lParam) == FD_WRITE)
				return cSock->OnSocketWrite(WSAGETSELECTERROR(lParam));
			else if (WSAGETSELECTEVENT(lParam) == FD_OOB)
				return cSock->OnSocketOOB(WSAGETSELECTERROR(lParam));
			else if (WSAGETSELECTEVENT(lParam) == FD_CLOSE)
				return cSock->OnSocketClose(WSAGETSELECTERROR(lParam));
			break;
		case WM_SOCKET_CONNECT:
			if (WSAGETSELECTEVENT(lParam) == FD_CONNECT)
				return cSock->OnSocketConnect(WSAGETSELECTERROR(lParam));
			break;
		case WM_SOCKET_ACCEPT:
			if (WSAGETSELECTEVENT(lParam) == FD_ACCEPT)
				return cSock->OnSocketAccept(WSAGETSELECTERROR(lParam));
			break;
		case WM_TIMER:
			//Inform the socket
			return cSock->OnSocketTimeout();
		default:                       /* Passes it on if unproccessed    */
			return (int)(DefWindowProc(hwnd, uMsg, wParam, lParam));
		}
	else
		return (int)(DefWindowProc(hwnd, uMsg, wParam, lParam));

	return TRUE;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAsyncSocket::CAsyncSocket() : CSpoofBase()
{
	try
	{
		m_Instance=0;
		m_List=FALSE;

		//Initialize all data
		if (!m_SocketTree)
		{
			//Intialize the tree
			m_SocketTree=new CBinaryTree;

			//Create handlers
			if (!SetHandlers())
				ReportError("CAsyncSocket","Failed to init handlers!");

			//Create a new socket to do the shutdown
			CAsyncShutdown* pShutdown;
			pShutdown=new CAsyncShutdown;

			//The class registers itself
		}
	}
	ERROR_HANDLER("CAsyncSocket")
}

CAsyncSocket::~CAsyncSocket()
{
	try
	{
		RemoveSocketFromList();
	}
	ERROR_HANDLER("~CAsyncSocket")
}

//Static members
CBinaryTree* CAsyncSocket::m_SocketTree=NULL;
BOOL CAsyncSocket::m_Window=FALSE;
HWND CAsyncSocket::m_WindowHandle=0;

BOOL CAsyncSocket::SetHandlers()
{
	try
	{
		//First create the window class
		if (!m_Window)
			if (!RegisterWindow())
			{
				//Error
				ReportError("SetHandlers","Error registering the window, please check API error!");
				return FALSE;
			}
			else
			{
				m_WindowHandle=CreateWindowEx(0,CAsyncSocket_Class,"Socket notification sink",
											  WS_OVERLAPPED,0,0,0,0,0,NULL,GetInstance(),NULL);
				//Check the value of the window
				if (!m_WindowHandle)
				{
					//Error
					ReportError("SetHandlers","Error creating the window, please check API error!");
					return FALSE;
				}
				else
					//We have a window
					m_Window=TRUE;
			}

		//Created !!
		//Success
		return TRUE;
	}
	ERROR_HANDLER_RETURN("CAsyncSocket",FALSE)
}

HINSTANCE CAsyncSocket::GetInstance()
{
	//Returns the instance of the application, must be overided
	return m_Instance;
}

void CAsyncSocket::AddSocketToList()
{
	try
	{
		//Add socket to list
		m_SocketID=GetAsyncHandle();
		m_SocketTree->newNode(GetSocketID())->setData(this);
		m_List=TRUE;
	}
	ERROR_HANDLER("AddSocketToList")
}

int CAsyncSocket::GetSocketID()
{
	return m_SocketID;
}

CAsyncSocket* CAsyncSocket::GetSocketByID(int iSockID)
{
	try
	{
		//Get the socket
		CBinaryTree* retVal;

		retVal=m_SocketTree->getNode(iSockID);

		//Check if valid
		if (retVal)
			//Got socket
			return retVal->getData();
		else
			//Nothing
			return NULL;
	}
	catch (...)
	{
		//Can't report since this is a static method
		return NULL;
	}
}

BOOL CAsyncSocket::RegisterWindow()
{
	try
	{
		WNDCLASS wc;

		/* Fill in window class structure with parameters that describe the       */
		/* main window.                                                           */

		wc.style = 0;										  /* Class style(s).                    */
		wc.lpfnWndProc = (WNDPROC)SocketMessageHandler;       /* Function to retrieve messages for  */
											/* windows of this class.             */
		wc.cbClsExtra = 0;                  /* No per-class extra data.           */
		wc.cbWndExtra = 0;                  /* No per-window extra data.          */
		wc.hIcon = NULL;				    /* Icon name from .RC        */
		wc.hInstance = GetInstance();          /* Application that owns the class.   */
		wc.hCursor = NULL;
		wc.hbrBackground = NULL;
		wc.lpszMenuName =  NULL;   /* Name of menu resource in .RC file. */
		wc.lpszClassName = CAsyncSocket_Class ; /* Name used in call to CreateWindow. */

		/* Register the window class and return success/failure code. */

		return (RegisterClass(&wc));
	}
	ERROR_HANDLER_RETURN("RegisterWindow",FALSE)
}

void CAsyncSocket::SetInstance(HINSTANCE hInst)
{
	m_Instance=hInst;
}

BOOL CAsyncSocket::RemoveHandlers()
{
	try
	{
		//First shut down the windows
		if (m_Window)
		{
			if (!DestroyWindow(m_WindowHandle))
				return FALSE;

			if (!UnregisterClass(CAsyncSocket_Class,GetInstance()))
				return FALSE;
		}

		m_Window=FALSE;
		m_WindowHandle=NULL;

		return TRUE;
	}
	ERROR_HANDLER_RETURN("RemoveHandlers",FALSE)
}

HWND CAsyncSocket::getWindowHandle()
{
	return m_WindowHandle;
}

void CAsyncSocket::RemoveSocketFromList()
{
	try
	{
		if (m_List)
			m_SocketTree->deleteNode(m_SocketID);
	}
	ERROR_HANDLER("RemoveSocketFromList")
}

BOOL CAsyncSocket::SetTimeout(int iMs)
{
	try
	{
		if (!m_Window)
			return FALSE;

		//Set the timer
		return SetTimer(getWindowHandle(),GetAsyncHandle(),iMs,NULL);
	}
	ERROR_HANDLER_RETURN("SetTimeout",FALSE)
}

BOOL CAsyncSocket::KillTimer()
{
	try
	{
		if (!m_Window)
			return FALSE;

		return ::KillTimer(getWindowHandle(),GetAsyncHandle());
	}
	ERROR_HANDLER_RETURN("KillTimer",FALSE)
}

void CAsyncSocket::Shutdown()
{
	try
	{
		//Remove the handlers
		RemoveHandlers();
	
		//Delete the tree
		delete m_SocketTree;
	}
	ERROR_HANDLER("Shutdown")
}

CAsyncSocket::CAsyncShutdown::CAsyncShutdown() : CSpoofBase()
{
	try
	{
		//Register myself
		SetName(CAsyncShutdown_Class);

		//Register for shutdown
		RegisterShutdown(this);
	}
	ERROR_HANDLER("CAsyncShutdown")
}

CAsyncSocket::CAsyncShutdown::~CAsyncShutdown()
{
}

void CAsyncSocket::CAsyncShutdown::NotifyShutdown()
{
	try
	{
		//Socket shutdown!
		CAsyncSocket* pSocket;
		pSocket->Shutdown();
	}
	ERROR_HANDLER("NotifyShutdown")
}