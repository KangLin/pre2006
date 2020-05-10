#include "StdAfx.h"
#include "Data.h"

CData::CData(void)
{
	m_pBuffer = new char[4096];
	m_nLength = 0;
	m_nMaxLen = 0;
}

CData::~CData(void)
{
	Clear();
}

int CData::Clear()
{
	if(m_pBuffer)
	{
		delete m_pBuffer;
	}// ½áÊø if(m_pBuffer)
	m_pBuffer = NULL;
	m_nLength = 0;
	m_nMaxLen = 0;
	return S_OK;
}