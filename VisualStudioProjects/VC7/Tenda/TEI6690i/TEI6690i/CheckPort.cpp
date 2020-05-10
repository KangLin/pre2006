/*******************************************************************************************************
��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
�ļ�����CheckPort.cpp
��  ������PING�����˿ڣ��������˿��Ƿ���ͨ��
��  ����1.0
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2005��11��11��
ʱ  �䣺14:57:56
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10
*******************************************************************************************************/

#include "StdAfx.h"
#include ".\checkport.h"
#include "ICMP.h"
#include "CommonFunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CString g_6690iINIFile;

CCheckPort::CCheckPort(void)
{
	SetName(_T("���Զ˿�"));

	CString szPath = GetCurrentDir();
	szPath += _T("\\") + g_6690iINIFile;
	TCHAR szRe [1024];

	if(::GetPrivateProfileString(_T("PING"), _T("TIMEOUT"), _T("5000"), szRe, 1024, szPath) == 0)
	{
		m_plog->Message(_T("��ȡPING�ĳ�ʱʱ��ʧ��"));
		return;
	} // ���� if(::GetPrivateProfileString(_T("MACIP"), _T("TIMEOUT"), _T("5000"), szRe, 1024, szPath) == 0)
	m_TimeOut = _ttoi(szRe);

	if(::GetPrivateProfileString(_T("PING"), _T("PINGNUM"), _T("1"), szRe, 1024, szPath) == 0)
	{
		m_plog->Message(_T("��ȡPING�Ĵ���ʧ��"));
		return;
	} // ���� if(::GetPrivateProfileString(_T("PING"), _T("PINGNUM"), _T("1"), szRe, 1024, szPath) == 0)
	m_nPingNum = _ttoi(szRe);

	if(::GetPrivateProfileString(_T("PING"), _T("IPNUM"), _T("1"), szRe, 1024, szPath) == 0)
	{
		m_plog->Message(_T("��ȡPING��IP��ַ����ʧ��"));
		return;
	} // ���� if(::GetPrivateProfileString(_T("PING"), _T("IPNUM"), _T("1"), szRe, 1024, szPath) == 0)
	m_nIPNum = _ttoi(szRe);

	for(int i = 0; i < m_nIPNum; i++)
	{
		CString sztmp;
		sztmp.Format(_T("%d"), i + 1);
		sztmp = _T("IP") + sztmp;
		if(::GetPrivateProfileString(_T("PING"), sztmp, _T("192.168.0.1"), szRe, 1024, szPath) == 0)
		{
			m_plog->Message(_T("��ȡIP��ַʧ��"));
			return;
		} // ���� if(::GetPrivateProfileString(_T("PING"), sztmp, _T("192.168.0.1"), szRe, 1024, szPath) == 0)
		sztmp = szRe;
		m_szIP.push_back(sztmp);
	} // ���� for(int i = 0; i < m_nIPNum; i++)
	
	m_Sock.Socket(SOCK_RAW, FD_READ | FD_WRITE | FD_OOB | FD_ACCEPT | FD_CONNECT | FD_CLOSE, IPPROTO_ICMP);
}

CCheckPort::~CCheckPort(void)
{
	m_Sock.Close();
}

int CCheckPort::DoTest(void)
{
	CString sztmp;
	int nPort = 0;

	for(int i = 0; i < m_nIPNum; i++)
	{
		BOOL bPing = FALSE;
		sztmp.Format(_T("���ڼ��˿� %d ����Ӧ��IP��ַΪ��%s  ......"), i + 1, m_szIP[i]);
		m_plog->Message(sztmp);
		for(int j = 0; j < m_nPingNum; j++)
		{
			if(!Ping(m_szIP[i], i))
			{
				bPing = TRUE;
				sztmp.Format(_T("�� %d ���˿ڣ���Ӧ��IP��ַΪ��%s������"), i + 1, m_szIP[i]);
				m_plog->Pass(sztmp);
				break;
			} // ���� if(Ping(m_szIP[i], i))
		} // ���� for(int j = 0; j < m_nPingNum; j++)
		if(!bPing)
		{
			//PING��ͨ
			sztmp.Format(_T("�� %d ���˿ڣ���Ӧ��IP��ַΪ��%s������"), i + 1, m_szIP[i]);
			m_plog->Faile(sztmp);
			nPort = 1;
		} // ���� if(!bPing)
	} // ���� for(int i = 0; i < m_nIPNum; i++)
	if(nPort)
	{
		m_plog->Faile(_T("�˿ڲ���"));
	} // ���� if(nPort)
	return nPort;
}

int CCheckPort::Ping(CString szIP, UINT uSeq)
{

	TIMEVAL tm = {0, 0};
	

	CICMP icmp;
	char buf[1024];
	UINT uPort = 0;
	
	ICMPHeader head;
	icmp.ECHO(&head, 10, uSeq, 255);
	TRACE(_T("%d:%s:%s\n"), uSeq, _T("��ʼ����"), szIP);
	m_Sock.SendTo(&head, sizeof(head), uPort, szIP);

	int i = m_nPingNum;

	while(1)
	{
		if(!m_Sock.SetTimeOut(m_TimeOut))
		{
			m_plog->Message(_T("Socket���ó�ʱʧ�ܡ�"));
			return 1;
		} // ���� if(!m_Sock.SetTimeOut(m_TimeOut))
		
		TRACE(_T("%d:%s:%s\n"), i, _T("��ʼ����"), szIP);
		if(SOCKET_ERROR == m_Sock.ReceiveFrom(buf, sizeof(buf), szIP, uPort))
		{
			if(WSAEINTR == GetLastError())
			{
				m_plog->Message(_T("���ճ�ʱ��"));
				TRACE(_T("���ճ�ʱ��\n"));
				if(!m_Sock.KillTimeOut())
				{
					m_plog->Message(_T("������ʱ����"));
				} // ���� if(!m_Sock.KillTimeOut())
				return 2;
			}
			else
			{
				m_plog->Message(_T("���ճ���"));
				TRACE(_T("���ճ���\n"));
				if(!m_Sock.KillTimeOut())
				{
					m_plog->Message(_T("������ʱ����"));
				} // ���� if(!m_Sock.KillTimeOut())
				return 3;
			}
		} // ���� if(SOCKET_ERROR == m_Sock.ReceiveFrom(buf, sizeof(buf), szIP, uPort))
		
		TRACE(_T("%d:%s\n"), i, _T("���ս���"));
		if(icmp.ProccessICMP(buf, &head) == ICMP_Echo_Reply)
		{
			if(head.sICMP.sUS.us2 == htons(uSeq))
			{
				if(!m_Sock.KillTimeOut())
				{
					m_plog->Message(_T("������ʱ����"));
				} // ���� if(!m_Sock.KillTimeOut())
				return 0; 
			}
			else
			{
				TRACE(_T("���յ� ICMP ���ݲ���:%d:%d\n"), uSeq, ntohs(head.sICMP.sUS.us2));
			}
		} // ���� if(icmp.ProccessICMP(buf, &head) == ICMP_Echo_Reply)
		else
		{
			TRACE(_T("���� ICMP ����\n"));
		}
		
		if(!m_Sock.KillTimeOut())
		{
			m_plog->Message(_T("������ʱ����"));
		} // ���� if(!m_Sock.KillTimeOut())

		i--;

	} // ���� while(1)

	if(!m_Sock.KillTimeOut())
	{
		m_plog->Message(_T("������ʱ����"));
	} // ���� if(!m_Sock.KillTimeOut())

	return 4;
}
