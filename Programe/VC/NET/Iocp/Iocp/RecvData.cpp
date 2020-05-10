#include "StdAfx.h"
#include "RecvData.h"

CRecvData::CRecvData(void)
{
	m_nRecvLength = 0;
}

CRecvData::~CRecvData(void)
{
}

int CRecvData::Clear()
{
	m_nRecvLength = 0;
	return CData::Clear();
}