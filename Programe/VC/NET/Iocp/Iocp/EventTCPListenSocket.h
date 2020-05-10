#pragma once
#include "tcpListensocket.h"

class CEventTCPListenSocket : public CTCPListenSocket
{
public:
	CEventTCPListenSocket(int port, bool localhostOnly = FALSE, int sock = INVALID_SOCKET);
	virtual ~CEventTCPListenSocket(void);

	HANDLE GetEvent();

private:
	HANDLE m_hEvent;
};
