#include "StdAfx.h"
#include "Sock.h"

#pragma comment(lib, "Ws2_32.lib")

BOOL g_bInitialized = FALSE;

int InitalizeSocket()
{
	if(!g_bInitialized)
	{
		static CInitSock s;
		g_bInitialized = TRUE;
		return S_OK;
	}// Ω· ¯ if(!m_bInitialized)
	return S_FALSE;
}

CInitSock::CInitSock(BYTE minorVer, BYTE majorVer)
{
	// ≥ı ºªØWS2_32.dll
	WSADATA wsaData;
	WORD sockVersion = MAKEWORD(minorVer, majorVer);
	if(::WSAStartup(sockVersion, &wsaData) != 0)
	{
		throw CTException(_T("unable to initialise Winsock2"), WSAGetLastError());
	}
	TRACE(_T("Initialized Socket\n"));
}

CInitSock::~CInitSock()
{	
	::WSACleanup();
	TRACE(_T("Cleanup Socket\n"));
}

CSocket::CSocket(int nFd)
{
	m_nFd = nFd;
}

CSocket::~CSocket(void)
{
}

int CSocket::GetFd()
{
	ASSERT(m_nFd != SOCKET_ERROR);
	return m_nFd;
}

int CSocket::Send(void * pBuf, int nLen, int nFlags /* = 0*/)
{
	return send(GetFd(), (char*)pBuf, nLen, nFlags);
}

int CSocket::Recv(void * pBuf, int nLen, int nFlags)
{
	return recv(GetFd(), (char * )pBuf, nLen, nFlags);
}

int CSocket::ShutDown(int nHow)
{
	return shutdown(GetFd(), nHow);
}

int CSocket::Close()
{
	return closesocket(GetFd());
}