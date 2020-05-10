#include "StdAfx.h"
#include "TCPSock.h"

CTCPSocket::CTCPSocket(int fd) : CSocket(fd)
{
}

CTCPSocket::~CTCPSocket(void)
{
	if(INVALID_SOCKET != GetFd())
	{
		TRACE(_T("CTcpSocket::~CTcpSocket\n"));
		ShutDown();
		Close();
	} // 结束 if(INVALID_SOCKET != m_fd)
}

CTCPSocket::CTCPSocket(const TCHAR * thost, int port)
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

	m_nFd = sock;
}

_tstring CTCPSocket::GetMyAddress()
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

int CTCPSocket::GetMyPort()
{
	struct sockaddr_in info;
	INT info_size = sizeof(info);
	if(getsockname(GetFd(), (struct sockaddr * )&info, &info_size) < 0)
		return 0;
	return ntohs(info.sin_port);
}

_tstring CTCPSocket::GetMyEndpoint()
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

_tstring CTCPSocket::GetPeerAddress()
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

int CTCPSocket::GetPeerPort() {
	struct sockaddr_in  info;
	INT info_size = sizeof(info);

	getpeername(GetFd(), (struct sockaddr *)&info, &info_size);
	return ntohs(info.sin_port);
}

_tstring CTCPSocket::GetPeerEndpoint()
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

bool CTCPSocket::EnableNagles(int sock, bool enable) {
	int one = enable ? 0 : 1;
	if (setsockopt(sock, IPPROTO_TCP, TCP_NODELAY,
		(char *)&one, sizeof(one)) < 0) {
			int e = WSAGetLastError();
			TRACE(_T("unable to setsockopt TCP_NODELAY: %d"), e);
			return false;
	}
	return true;
}