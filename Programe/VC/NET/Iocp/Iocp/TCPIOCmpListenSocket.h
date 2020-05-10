#pragma once
#include "tcpListensocket.h"

class CTCPIOCmpListenSocket : public CTCPListenSocket
{
public:
	CTCPIOCmpListenSocket(int port, bool localhostOnly, int sock = INVALID_SOCKET);
	virtual ~CTCPIOCmpListenSocket(void);

	// accept() returns a new Socket object if there is a connection
	// attempt in progress AND if the connection passes the filter
	// if one is installed.  Otherwise, returns 0.
	virtual CSocket * Accept();
};
