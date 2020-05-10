#include "StdAfx.h"
#include "TCPIOCmpListenSocket.h"
#include "TCPIOCmpSocket.h"

CTCPIOCmpListenSocket::CTCPIOCmpListenSocket(int port, bool localhostOnly, int sock) : CTCPListenSocket(port, localhostOnly, sock)
{
}

CTCPIOCmpListenSocket::~CTCPIOCmpListenSocket(void)
{
}

CSocket * CTCPIOCmpListenSocket::Accept()
{
	int new_sock = INVALID_SOCKET;

	// Accept an incoming connection
	if((new_sock = ::accept(GetFd(), 0, 0)) < 0)
		throw CTException(_T("unable to accept new connection"), WSAGetLastError());

#ifndef WIN32
	// - By default, close the socket on exec()
	fcntl(new_sock, F_SETFD, FD_CLOEXEC);
#endif

	// Disable Nagle's algorithm
	int one = 1;
	if (setsockopt(new_sock, IPPROTO_TCP, TCP_NODELAY,
		(char *)&one, sizeof(one)) < 0) {
			int e = WSAGetLastError();
			closesocket(new_sock);
			throw CTException(_T("unable to setsockopt TCP_NODELAY"), e);
	}

	// Create the socket object & check connection is allowed
	CSocket * s = new CTCPIOCmpSocket(new_sock);
	/*if (filter && !filter->verifyConnection(s)) {
	delete s;
	return 0;
	}*/
	return s;
}