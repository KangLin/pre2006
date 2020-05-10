#include "StdAfx.h"
#include "TCPListenSocket.h"
#include "TCPSock.h"

CTCPListenSocket::CTCPListenSocket(int port, bool localhostOnly /* = false */, int sock /* = INVALID_SOCKET */) : CListenSocket (sock)
{
	if(sock != INVALID_SOCKET)
	{
		m_nFd = sock;
		return;
	}

	if((m_nFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		throw CTException(_T("unable to create listening socket"), WSAGetLastError());

#ifndef WIN32
	// - By default, close the socket on exec()
	fcntl(sock, F_SETFD, FD_CLOEXEC);

	int one = 1;
	if(setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR,
		(const char *)&one, sizeof(one)) < 0) {
			int e = errorNumber;
			closesocket(m_fd);
			throw CSocketException("unable to create listening socket", e);
	}
#endif

	// - Bind it to the desired port
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	if (localhostOnly)
		addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	else
		addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(m_nFd, (struct sockaddr * )&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		int e = WSAGetLastError();
		closesocket(m_nFd);
		throw CTException(_T("unable to bind listening socket"), e);
	}

	// - Set it to be a listening socket
	if(listen(m_nFd, SOMAXCONN) == SOCKET_ERROR)
	{
		int e = WSAGetLastError();
		closesocket(m_nFd);
		throw CTException(_T("unable to set socket to listening mode"), e);
	}
}

CTCPListenSocket::~CTCPListenSocket(void)
{
	if(INVALID_SOCKET != m_nFd)
	{
		TRACE(_T("CTcpSocketListen::~CTcpSocketListen\n"));
		ShutDown();
		Close();
	} // ½áÊø if(INVALID_SOCKET != m_fd)
}

CSocket * CTCPListenSocket::Accept()
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
	CSocket * s = new CTCPSocket(new_sock);
	/*if (filter && !filter->verifyConnection(s)) {
	delete s;
	return 0;
	}*/
	return s;
}

_tstring CTCPListenSocket::GetMyAddress()
{
	USES_CONVERSION;

	struct sockaddr_in  info;
	struct in_addr    addr;
	INT info_size = sizeof(info);

	getsockname(GetFd(), (struct sockaddr *)&info, &info_size);
	memcpy(&addr, &info.sin_addr, sizeof(addr));

	char * name = inet_ntoa(addr);
	_tstring szReturn = A2T(name);
	return szReturn;

}

int CTCPListenSocket::GetMyPort()
{
	struct sockaddr_in info;
	INT info_size = sizeof(info);
	if(getsockname(GetFd(), (struct sockaddr * )&info, &info_size) < 0)
		return 0;
	return ntohs(info.sin_port);
}

_tstring CTCPListenSocket::GetMyEndpoint()
{
	USES_CONVERSION;
	_tstring szAdd = GetMyAddress();
	int port = GetMyPort();

	int buflen = szAdd.length() * sizeof(TCHAR) + 32;
	TCHAR * buffer = new TCHAR[buflen];
	_stprintf(buffer, _T("%s::%d"), szAdd.c_str(), port);
	_tstring szRet(buffer);
	delete []buffer;
	return szRet;
}

_tstring CTCPListenSocket::GetPeerAddress()
{
	USES_CONVERSION;
	struct sockaddr_in  info;
	struct in_addr    addr;
	INT info_size = sizeof(info);

	getpeername(GetFd(), (struct sockaddr *)&info, &info_size);
	memcpy(&addr, &info.sin_addr, sizeof(addr));

	char* name = inet_ntoa(addr);
	_tstring szRet = A2T(name);
	return szRet;
}

int CTCPListenSocket::GetPeerPort() {
	struct sockaddr_in  info;
	INT info_size = sizeof(info);

	getpeername(GetFd(), (struct sockaddr *)&info, &info_size);
	return ntohs(info.sin_port);
}

_tstring CTCPListenSocket::GetPeerEndpoint()
{
	_tstring szAdd;
	szAdd = GetPeerAddress();
	int port = GetPeerPort();

	int buflen = szAdd.length()*sizeof(TCHAR) + 32;
	TCHAR* buffer = new TCHAR[buflen];
	_stprintf(buffer, _T("%s::%d"), szAdd.c_str(), port);
	_tstring szRet(buffer);
	delete []buffer;
	return szRet;
}