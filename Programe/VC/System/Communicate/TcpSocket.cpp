#include "StdAfx.h"
#include "TcpSocket.h"
#include <AtlBase.h>


namespace Network
{

CTcpSocket::CTcpSocket(int fd): CSocket(fd)
{
}

CTcpSocket::CTcpSocket(const TCHAR * thost, int port)
{
	int sock;
	char * host = NULL;
	USES_CONVERSION;

	host = T2A(thost);

	// - Create a socket
	if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		TRACE(_T("不能建立 Socket\n"));
		throw CTException(_T("不能建立 Socket"), WSAGetLastError());
	} // 结束 if((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)

#ifndef WIN32
	// - By default, close the socket on exec()
	fcntl(sock, F_SETFD, FD_CLOEXEC);
#endif

	// - Connect it to something

	// Try processing the host as an IP address
	struct sockaddr_in addr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = inet_addr(host);
	addr.sin_port = htons(port);
	if ((int)addr.sin_addr.s_addr == -1) {
		// Host was not an IP address - try resolving as DNS name
		struct hostent *hostinfo;
		hostinfo = gethostbyname(host);
		if (hostinfo && hostinfo->h_addr) {
			addr.sin_addr.s_addr = ((struct in_addr *)hostinfo->h_addr)->s_addr;
		} else {
			int e = WSAGetLastError();
			closesocket(sock);
			TRACE(_T("不能解析主机名。\n"));
			throw CTException(_T("不能解析主机名。"), e);
		}
	}

	// Attempt to connect to the remote host
	if (connect(sock, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
		int e = WSAGetLastError();
		closesocket(sock);
		TRACE(_T("不能连接到主机。\n"));
		throw CTException(_T("不能连接到主机。"), e);
	}

	// Disable Nagle's algorithm, to reduce latency
	EnableNagles(sock, false);

	SetFd(sock);
}

CTcpSocket::~CTcpSocket(void)
{
	if(INVALID_SOCKET != GetFd())
	{
		TRACE(_T("CTcpSocket::~CTcpSocket\n"));
		Shutdown();
		Close();
	} // 结束 if(INVALID_SOCKET != m_fd)
}

string CTcpSocket::GetMyAddress()
{
	struct sockaddr_in  info;
	struct in_addr    addr;
	INT info_size = sizeof(info);

	getsockname(GetFd(), (struct sockaddr *)&info, &info_size);
	memcpy(&addr, &info.sin_addr, sizeof(addr));

	char* name = inet_ntoa(addr);
	if (name) {
		return name;
	} else {
		return "";
	}
}

int CTcpSocket::GetMyPort()
{
	return GetSockPort(GetFd());
}

string CTcpSocket::GetMyEndpoint() {
	string szAdd = GetMyAddress();
	int port = GetMyPort();

	int buflen = szAdd.length() + 32;
	char* buffer = new char[buflen];
	sprintf(buffer, "%s::%d", szAdd.c_str(), port);
	string szRet(buffer);
	delete []buffer;
	return szRet;
}

string CTcpSocket::GetPeerAddress()
{
	struct sockaddr_in  info;
	struct in_addr    addr;
	INT info_size = sizeof(info);

	getpeername(GetFd(), (struct sockaddr *)&info, &info_size);
	memcpy(&addr, &info.sin_addr, sizeof(addr));

	char* name = inet_ntoa(addr);
	if (name) {
		return name;
	} else {
		return "";
	}
}

int CTcpSocket::GetPeerPort() {
	struct sockaddr_in  info;
	INT info_size = sizeof(info);

	getpeername(GetFd(), (struct sockaddr *)&info, &info_size);
	return ntohs(info.sin_port);
}

string CTcpSocket::GetPeerEndpoint()
{
	string szAdd;
	szAdd = GetPeerAddress();
	int port = GetPeerPort();

	int buflen = szAdd.length() + 32;
	char* buffer = new char[buflen];
	sprintf(buffer, "%s::%d", szAdd.c_str(), port);
	string szRet(buffer);
	delete []buffer;
	return szRet;
}

int CTcpSocket::Send(const void * lpBuf, int nBufLen, int nFlags /* = 0 */)
{
	int nRet = SOCKET_ERROR;
	nRet = ::send(GetFd(), (const char * )lpBuf, nBufLen, nFlags);
	return nRet;
}

int CTcpSocket::Receive(void * lpBuf, int nBufLen, int nFlags /* = 0 */)
{
	int nRet = SOCKET_ERROR;
	nRet = ::recv(GetFd(), (char * )lpBuf, nBufLen, nFlags);
	return nRet;
}

int CTcpSocket::Shutdown()
{
	int nRet = ::shutdown(GetFd(), SD_BOTH);
	TRACE(_T("shutdown Socket:%d;状态:%d\n"), GetFd(), nRet);
	return nRet;
}

int CTcpSocket::Close()
{
	int nRet;
	nRet = ::closesocket(GetFd());
	TRACE(_T("关闭 Socket:%d;状态:%d\n"), GetFd(), nRet);
	return nRet;
}

bool CTcpSocket::SameMachine() {
	struct sockaddr_in peeraddr, myaddr;
	INT addrlen = sizeof(struct sockaddr_in);

	getpeername(GetFd(), (struct sockaddr * )&peeraddr, &addrlen);
	getsockname(GetFd(), (struct sockaddr *)&myaddr, &addrlen);

	return (peeraddr.sin_addr.s_addr == myaddr.sin_addr.s_addr);
}

bool CTcpSocket::EnableNagles(int sock, bool enable) {
	int one = enable ? 0 : 1;
	if (setsockopt(sock, IPPROTO_TCP, TCP_NODELAY,
		(char *)&one, sizeof(one)) < 0) {
			int e = WSAGetLastError();
			TRACE(_T("unable to setsockopt TCP_NODELAY: %d"), e);
			return false;
	}
	return true;
}

bool CTcpSocket::IsSocket(int sock)
{
	struct sockaddr_in info;
	INT info_size = sizeof(info);
	return getsockname(sock, (struct sockaddr *)&info, &info_size) >= 0;
}

bool CTcpSocket::IsConnected(int sock)
{
	struct sockaddr_in info;
	INT info_size = sizeof(info);
	return getpeername(sock, (struct sockaddr *)&info, &info_size) >= 0;
}


int CTcpSocket::GetSockPort(int sock)
{
	struct sockaddr_in info;
	INT info_size = sizeof(info);
	if (getsockname(sock, (struct sockaddr *)&info, &info_size) < 0)
		return 0;
	return ntohs(info.sin_port);
}

CTcpSocketLister::CTcpSocketLister(int port, bool localhostOnly, int sock)
{
	if(sock != INVALID_SOCKET)
	{
		m_fd = sock;
		return;
	}

	if((m_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
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
	if(bind(m_fd, (struct sockaddr * )&addr, sizeof(addr)) == SOCKET_ERROR)
	{
		int e = WSAGetLastError();
		closesocket(m_fd);
		throw CTException(_T("unable to bind listening socket"), e);
	}

	// - Set it to be a listening socket
	if(listen(m_fd, SOMAXCONN) == SOCKET_ERROR)
	{
		int e = WSAGetLastError();
		closesocket(m_fd);
		throw CTException(_T("unable to set socket to listening mode"), e);
	}
}

CTcpSocketLister::~CTcpSocketLister()
{
	if(INVALID_SOCKET != m_fd)
	{
		TRACE(_T("CTcpSocketLister::~CTcpSocketLister\n"));
		Shutdown();
		Close();
	} // 结束 if(INVALID_SOCKET != m_fd)
}

int CTcpSocketLister::Shutdown()
{
	int nRet = ::shutdown(GetFd(), SD_BOTH);
	TRACE(_T("shutdown Socket:%d;状态:%d\n"), GetFd(), nRet);
	return nRet;
}

int CTcpSocketLister::Close()
{
	int nRet;
	nRet = ::closesocket(GetFd());
	TRACE(_T("关闭 Socket:%d;状态:%d\n"), GetFd(), nRet);
	return nRet;
}

CSocket * CTcpSocketLister::Accept()
{
	int new_sock = INVALID_SOCKET;

	// Accept an incoming connection
	if ((new_sock = ::accept(m_fd, 0, 0)) < 0)
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
	CSocket * s = new CTcpSocket(new_sock);
	/*if (filter && !filter->verifyConnection(s)) {
		delete s;
		return 0;
	}*/
	return s;
}

int CTcpSocketLister::GetMyAddresses(std::list < char * > *result)
{
	const hostent* addrs = gethostbyname(0);
	if (addrs == 0)
		throw CTException(_T("gethostbyname"), WSAGetLastError());
	if (addrs->h_addrtype != AF_INET)
		throw CTException(_T("getMyAddresses: bad family"));
	for (int i=0; addrs->h_addr_list[i] != 0; i++) {
		const char* addrC = inet_ntoa(*((struct in_addr*)addrs->h_addr_list[i]));
		char* addr = new char[strlen(addrC)+1];
		strcpy(addr, addrC);
		result->push_back(addr);
	}
	return S_OK;
}

int CTcpSocketLister::GetMyPort()
{
	return CTcpSocket::GetSockPort(GetFd());
}



};