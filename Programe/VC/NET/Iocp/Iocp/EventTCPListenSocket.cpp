#include "StdAfx.h"
#include "EventTCPListenSocket.h"

CEventTCPListenSocket::CEventTCPListenSocket(int port, bool localhostOnly, int sock): CTCPListenSocket(port, localhostOnly, sock)
{
	m_hEvent = WSACreateEvent();
	ASSERT(m_hEvent != WSA_INVALID_EVENT);
	if(WSA_INVALID_EVENT == m_hEvent)
	{
		return;
	}// ���� if(WSA_INVALID_EVENT == m_hEvent)

	if(WSAEventSelect(GetFd(), m_hEvent, FD_ACCEPT | FD_CLOSE) == SOCKET_ERROR)
	{
		CTException e(_T("�����¼�����"), GetLastError());
		throw e;
	}
}

CEventTCPListenSocket::~CEventTCPListenSocket(void)
{
	if(m_hEvent)
	{
		CloseHandle(m_hEvent);
		m_hEvent = NULL;
	} // ���� if(m_hEvent)
}

HANDLE CEventTCPListenSocket::GetEvent()
{
	return m_hEvent;
}