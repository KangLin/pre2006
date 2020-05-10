#pragma once
#include "sock.h"

class CTCPSocket : public CSocket
{
public:
	CTCPSocket(int fd);
	//连接给定的地址
	CTCPSocket(const TCHAR *host, int port);
	virtual ~CTCPSocket(void);

	// information about this end of the socket
	virtual _tstring GetMyAddress();     // a string e.g. "192.168.0.1"
	virtual int GetMyPort();
	virtual _tstring GetMyEndpoint();    // <address>::<port>

	// information about the remote end of the socket
	virtual _tstring GetPeerAddress();   // a string e.g. "192.168.0.1"
	virtual int GetPeerPort();
	virtual _tstring GetPeerEndpoint();  // <address>::<port>

	static bool EnableNagles(int sock, bool enable);

};
