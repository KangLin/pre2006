#pragma once
#include "tcpsock.h"

class CTCPIOCmpSocket :	public CTCPSocket
{
public:
	CTCPIOCmpSocket(int nFd);
	virtual ~CTCPIOCmpSocket(void);


};
