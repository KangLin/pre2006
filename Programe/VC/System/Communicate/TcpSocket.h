#pragma once

#include "socket.h"

using namespace std;

namespace Network
{

	class CTcpSocket : public CSocket
	{
	public:
		CTcpSocket(int fd);
		//连接给定的地址
		CTcpSocket(const TCHAR *host, int port);
		virtual ~CTcpSocket(void);

		//属性
		virtual string GetMyAddress();
		virtual int GetMyPort();
		virtual string GetMyEndpoint();

		virtual string GetPeerAddress();
		virtual int GetPeerPort();
		virtual string GetPeerEndpoint();

		//操作
		virtual int Send(const void * lpBuf, int nBufLen, int nFlags = 0);
		virtual int Receive(void * lpBuf, int nBufLen, int nFlags = 0);
		virtual int Shutdown();
		virtual int Close();

		virtual bool SameMachine();

		static bool EnableNagles(int sock, bool enable);
		static bool IsSocket(int sock);
		static bool IsConnected(int sock);
		static int GetSockPort(int sock);

	};

	class CTcpSocketLister : public CSocketListener
	{
	public:
		CTcpSocketLister(int port, bool localhostOnly = false, int sock = INVALID_SOCKET);
		virtual ~CTcpSocketLister();

		virtual int Shutdown();
		virtual int Close();
		virtual CSocket * Accept();

		int GetMyAddresses(std::list < char * > * addrs);
		int GetMyPort();

	};


};