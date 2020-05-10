#pragma once
#include "sock.h"

class CListenSocket : public CSocket
{
public:
	CListenSocket(int fd);
	virtual ~CListenSocket(void);

	// accept() returns a new Socket object if there is a connection
	// attempt in progress AND if the connection passes the filter
	// if one is installed.  Otherwise, returns 0.
	virtual CSocket * Accept() = 0;
};
