#include "StdAfx.h"
#include "Lock.h"

CLock::CLock(void)
{
	InitializeCriticalSection(&m_CriticalSection);
}

CLock::~CLock(void)
{
	::DeleteCriticalSection(&m_CriticalSection);
}

int CLock::Lock()
{
	::EnterCriticalSection(&m_CriticalSection);
	return S_OK;
}

int CLock::UnLock()
{
	::LeaveCriticalSection(&m_CriticalSection);
	return S_OK;
}