// SetMacSock.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SetTestSock.h"

// CTestSocket

CTestSocket::CTestSocket()
{

}

CTestSocket::~CTestSocket()
{
}


// CTestSocket ��Ա����

BOOL CTestSocket::SetTimeOut(UINT uTimeOut)
{
	m_nTimerID = SetTimer(NULL, 0, uTimeOut, NULL);
	return m_nTimerID;
}

BOOL CTestSocket::KillTimeOut(void)
{
	return KillTimer(NULL, m_nTimerID);
}

BOOL CTestSocket::OnMessagePending()
{
	MSG msg;

	if(::PeekMessage(&msg, NULL, WM_TIMER, WM_TIMER, PM_NOREMOVE))
	{
		if (msg.wParam == (UINT) m_nTimerID)
		{
			// Remove the message and call CancelBlockingCall.
			::PeekMessage(&msg, NULL, WM_TIMER, WM_TIMER, PM_REMOVE);
			CancelBlockingCall();
			return FALSE;  // No need for idle time processing.
		};
	};

	return CSocket::OnMessagePending();
}
