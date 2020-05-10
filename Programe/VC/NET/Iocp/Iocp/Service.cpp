#include "StdAfx.h"
#include "Service.h"

CService::CService(CSocket * pSocket): CConnect(pSocket)
{
}

CService::~CService(void)
{
}
