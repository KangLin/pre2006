#pragma once
#include "tcpsock.h"

class CTCPCmpRouteSocket :	public CTCPSocket
{
public:
	CTCPCmpRouteSocket(int nFD);
	virtual ~CTCPCmpRouteSocket(void);

};
