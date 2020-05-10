#include "stdafx.h"
#include ".\combinecheckport.h"
#include "..\NET\ICMP\ICMP.h"
#include "..\CommonFunction.h"

extern CString g_INIFile;

CCombineCheckPort::CCombineCheckPort(void)
{
	CString szPath = GetCurrentDir();
	szPath += _T("\\") + g_INIFile;
	TCHAR szRe [1024];

	if(::GetPrivateProfileString(_T("PING"), _T("RATE"), _T("100"), szRe, 1024, szPath) == 0)
	{
		TRACE(_T("��ȡPING�ĳ�ʱʱ��ʧ��"));
		return;
	} // ���� if(::GetPrivateProfileString(_T("PING"), _T("RATE"), _T("100"), szRe, 1024, szPath) == 0)
	m_nRate = _ttoi(szRe);

	m_nID = 1000;
	m_phEvent = NULL;
	m_hSendEvent = NULL;
	m_hSendEvent = ::CreateEvent(NULL, TRUE, FALSE, NULL);
	if(!m_hSendEvent)
	{
		TRACE(_T("�����¼�����ʧ�ܡ�"));
	} // ���� if(!m_hSendEvent)

	for(int i = 0; i < m_nIPNum; i++)
	{
		m_nRecive.push_back(0);
	} // ���� for(int i = 0; i < m_nIPNum; i++)
}

CCombineCheckPort::~CCombineCheckPort(void)
{
}

int CCombineCheckPort::SetRecive(int nPort, int nNum)
{
	if(nPort < 0 || nPort > m_nRecive.size())
	{
		ASSERT(0);
		return 0;
	} // ���� if(nPort < 0 || nPort > m_nRecive.size())
	
	m_nRecive [nPort] = nNum;
	return m_nRecive [nPort];
}

CString CCombineCheckPort::GetIP(int nPort)
{
	if(nPort < 0 || nPort > m_nRecive.size())
	{
		ASSERT(0);
		return CString();
	} // ���� if(nPort < 0 || nPort > m_nRecive.size())
	return m_szIP[nPort];
}

int CCombineCheckPort::GetRecive(int nPort)
{
	if(nPort < 0 || nPort > m_nRecive.size())
	{
		ASSERT(0);
		return 0;
	} // ���� if(nPort < 0 || nPort > m_nRecive.size())
	return m_nRecive [nPort];
}

int CCombineCheckPort::GetTimeOut()
{
	return m_TimeOut;
}

CTestSocket * CCombineCheckPort::GetSocket()
{
	return & m_Sock;
}

CLogon * CCombineCheckPort::GetLogon()
{
	return m_plog;
}

int CCombineCheckPort::GetPingNum()
{
	return m_nPingNum;
}

int CCombineCheckPort::GetRate()
{
	return m_nRate;
}
int CCombineCheckPort::GetPort()
{
	return m_nIPNum;
}

HANDLE CCombineCheckPort::GetEvent(int nPort)
{
	return * (m_phEvent + nPort);
}

UINT CCombineCheckPort::GetID()
{
	return m_nID;
}

int CCombineCheckPort::DoTest()
{
	system(_T("arp -d"));

	int ret = 0;
	int i;
	_CombineCheckParam para;
	para.pInstance = this;

	if(m_nIPNum > MAXIMUM_WAIT_OBJECTS)
	{
		m_plog->Message(_T("ҪPING������Ŀ¼̫�࣬���������ú���ִ�С�"));
		return 1;
	} // ���� if(m_nIPNum > MAXIMUM_WAIT_OBJECTS)

	m_phEvent = new HANDLE[m_nIPNum];

	for(i = 0; i < m_nIPNum; i++)
	{
		
		m_nRecive [i] = 0;
		para.nPort = i;

		*(m_phEvent + i) = ::CreateEvent(NULL, TRUE, FALSE, NULL);

		::CreateThread(NULL, NULL, SendPing, &para, NULL, NULL);
		if(WAIT_OBJECT_0 == ::WaitForSingleObject(m_hSendEvent, INFINITE))
		{
		}
		else
		{
		} // ���� if(WAIT_OBJECT_0 == ::WaitForSingleObject(m_hSendEvent, INFINITE))

		::ResetEvent(m_hSendEvent);

	} // ���� for(int i = 0; i < m_IPNum; i++)
	
	if(WAIT_FAILED != ::WaitForMultipleObjects(m_nIPNum, m_phEvent, TRUE, INFINITE))
	{
	}
	else
	{
	} // ���� if(WAIT_FAILED != ::WaitForMultipleObjects(m_nIPNum, m_phEvent, TRUE, INFINITE))

	m_plog->Message(_T("\n"));
	for(i = 0; i < m_nIPNum; i++)
	{
		int nRate = 100 * ((float)m_nRecive [i] / (float)m_nPingNum);
		CString sztmp;
		sztmp.Format(_T("�� %d �˿ڣ���Ӧ��IP��ַΪ��%s��\n���� %d ���������յ� %d ������������ %d"), i + 1, m_szIP[i], m_nPingNum, m_nRecive [i], nRate);
		sztmp += _T("%%");
		m_plog->Message(sztmp, FALSE);
		
		if(nRate < m_nRate)
		{
			CString sztmp;
			sztmp.Format(_T("������"));
			m_plog->Faile(sztmp);
			ret = 1; 
		}
		else
		{
			m_plog->Pass(_T("������"));
		} // ���� if(nRate < m_nRate)

		::CloseHandle(*(m_phEvent + i));

	} // ���� for(int i = 0; i < m_nIPNum; i++)

	delete []m_phEvent;

	return ret;
}

#define CLASSSOCKET_COMBINECHECKPORT 0

DWORD _stdcall CCombineCheckPort::SendPing(void * para)
{
	_CombineCheckParam * p = (_CombineCheckParam * )para;
	CCombineCheckPort * pthis = (CCombineCheckPort * )p->pInstance;
	UINT nPort = p->nPort;
	CString szIP;
	szIP = pthis->GetIP(nPort);
	int nPingNum = pthis->GetPingNum();

	::SetEvent(pthis->m_hSendEvent);

	int nReiveNum = 0;
	char buf[1024];
	CString sztmpIP;
	bool ret = false;
	UINT id = pthis->GetID() + nPort;
	
	TRACE(_T("�����߳� %d\n"), nPort);

#if CLASSSOCKET_COMBINECHECKPORT

	CTestSocket * pSock = new CTestSocket;
	pSock->Socket(SOCK_RAW, FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE, IPPROTO_ICMP);

#else
	
	SOCKET s;
	s = ::socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	SOCKADDR_IN addr, tmpaddr;
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.S_un.S_addr = inet_addr(szIP);
	fd_set fdread;
	TIMEVAL tm;
	tm.tv_sec = 0;
	tm.tv_usec = 1000 * pthis->GetTimeOut();

#endif

	ICMPHeader head;
	CICMP icmp;

	//���� PING ��
	for(int i = 0; i < nPingNum; i++)
	{
		pthis->GetLogon()->Message(_T("."), FALSE);
		icmp.ECHO(&head, id, i, 255);

#if CLASSSOCKET_COMBINECHECKPORT
		if(SOCKET_ERROR == pSock->SendTo(&head, sizeof(head), 0, szIP))
#else
		if(SOCKET_ERROR == sendto(s, (char * )&head, sizeof(head), 0, (const sockaddr * )&addr, sizeof(addr)))	
#endif
		{
			pthis->GetLogon()->Message(_T("�������ݳ���"));
			continue;
		} // ���� if(SOCKET_ERROR == pSock->SendTo(&head, sizeof(head), 0, szIP))

		//���� PING ������ͳ�ƻذ���
		while(1)
		{
#if CLASSSOCKET_COMBINECHECKPORT
			if(!pSock->SetTimeOut(pthis->GetTimeOut()))
			{
				pthis->GetLogon()->Message(_T("Socket���ó�ʱʧ�ܡ�"));
				break;
			} // ���� ()
#else
			FD_ZERO(&fdread);
			FD_SET(s, &fdread);
			int ret;
			ret = select(0, &fdread, NULL, NULL, &tm);
			if(SOCKET_ERROR == ret)
			{
				TRACE(_T("select����\n"));
				continue;
			} // ���� if(SOCKET_ERROR == ret)
			if(ret == 0)
			{
				TRACE(_T("select��ʱ������:%d,�˿�:%d,��ʱʱ��:%d:%d\n"), i, nPort, tm.tv_sec, tm.tv_usec);
				break;
			} // ���� if(ret == 0)
			if(ret > 0)
			{
				if(!FD_ISSET(s, &fdread))
				{
					TRACE(_T("select�������ݳ���\n"));
					continue;
				} // ���� if(!FD_ISSET(s, &fdread))
			} // ���� if(ret > 0)
#endif

#if CLASSSOCKET_COMBINECHECKPORT
			//if(SOCKET_ERROR == pSock->ReceiveFrom(buf, sizeof(buf), sztmpIP, nPort))
			if(SOCKET_ERROR == pSock->Receive(buf, sizeof(buf)))
#else
			int addrlen;
			//if(SOCKET_ERROR == recvfrom(s, buf, sizeof(buf), 0, (sockaddr*)&tmpaddr, &addrlen))
			if(SOCKET_ERROR == recv(s, buf, sizeof(buf), 0)) //, (sockaddr * )&tmpaddr, &addrlen))
#endif
			{

#if !CLASSSOCKET_COMBINECHECKPORT
				//if(WSAEINTR == GetLastError())
				if(WSAETIMEDOUT == GetLastError())
				{
					TRACE(_T("���ճ�ʱ��\n"));
					break;
				}
				else
				{
					TRACE(_T("�������ݳ���\n"));
					continue;
				} // ���� if(WSAETIMEDOUT == GetLastError())
#endif

#if CLASSSOCKET_COMBINECHECKPORT
				if(WSAEINTR == GetLastError())
				{
					TRACE(_T("���ճ�ʱ��\n"));
				}
				else
				{
					TRACE(_T("�������ݳ���\n"));
				}
				if(!pSock->KillTimeOut())
				{
					pthis->GetLogon()->Message(_T("������ʱ����"));
				} // ���� ()
				break;
#endif

			} // ���� if(SOCKET_ERROR == recv(s, buf, sizeof(buf), 0))

			if(icmp.ProccessICMP(buf, &head) == ICMP_Echo_Reply)
			{
				if(ntohs(head.sICMP.sUS.us1) == nPort + pthis->GetID())
				{
					pthis->SetRecive(nPort, pthis->GetRecive(nPort) + 1);
					if(pthis->GetRecive(nPort) == nPingNum)
					{
						break;
					} // ���� if(pthis->GetRecive(nPort) == nPingNum)
				}
				else
				{
					TRACE(_T("���յ� ICMP ���ݲ���.��ǰIP��%s,�õ���IP��%s,�˿�:%d������:%d:%d\n"), szIP, sztmpIP, nPort, ntohs(head.sICMP.sUS.us1), ntohs(head.sICMP.sUS.us2));
				} // ���� if(ntohs(head.sICMP.sUS.us1) == nPort + pthis->GetID())
			}
			else
			{
				TRACE(_T("���� ICMP �����̣߳�%d\n"), nPort);
			} // ���� if(icmp.ProccessICMP(buf, &head) == ICMP_Echo_Reply)

#if CLASSSOCKET_COMBINECHECKPORT
			if(!pSock->KillTimeOut())
			{
				pthis->GetLogon()->Message(_T("������ʱ����"));
			} // ���� if(!pSock->KillTimeOut())
#endif

		} // ���� while(1)

	} // ���� for(int i = 0; i < nPingNum; i++)

#if CLASSSOCKET_COMBINECHECKPORT
	delete pSock;
#else
	closesocket(s);
#endif

	SetEvent(pthis->GetEvent(nPort));

	return 0;
}