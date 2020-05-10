#include "StdAfx.h"
#include "EventTCPListenSocket.h"

CEventTCPListenSocket::CEventTCPListenSocket(int port, bool localhostOnly, int sock): CTCPListenSocket(port, localhostOnly, sock)
{
	m_hEvent = WSACreateEvent();
	ASSERT(m_hEvent != WSA_INVALID_EVENT);
	if(WSA_INVALID_EVENT == m_hEvent)
	{
		return;
	}// 结束 if(WSA_INVALID_EVENT == m_hEvent)

	if(WSAEventSelect(GetFd(), m_hEvent, FD_ACCEPT | FD_CLOSE) == SOCKET_ERROR)
	{
		CTException e(_T("设置事件出错"), GetLastError());
		throw e;
	}
}

CEventTCPListenSocket::~CEventTCPListenSocket(void)
{
	if(m_hEvent)
	{
		CloseHandle(m_hEvent);
		m_hEvent = NULL;
	} // 结束 if(m_hEvent)
}

HANDLE CEventTCPListenSocket::GetEvent()
{
	return m_hEvent;
}