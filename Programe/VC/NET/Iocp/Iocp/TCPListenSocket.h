#pragma once
#include "Listensock.h"

class CTCPListenSocket : public CListenSocket
{
public:
	CTCPListenSocket(int port, bool localhostOnly = FALSE, int sock = INVALID_SOCKET);
	virtual ~CTCPListenSocket(void);

	// accept() returns a new Socket object if there is a connection
	// attempt in progress AND if the connection passes the filter
	// if one is installed.  Otherwise, returns 0.
	virtual CSocket * Accept();

	// information about this end of the socket
	virtual _tstring GetMyAddress();     // a string e.g. "192.168.0.1"
	virtual int GetMyPort();
	virtual _tstring GetMyEndpoint();    // <address>::<port>

	// information about the remote end of the socket
	virtual _tstring GetPeerAddress();   // a string e.g. "192.168.0.1"
	virtual int GetPeerPort();
	virtual _tstring GetPeerEndpoint();  // <address>::<port>

};
