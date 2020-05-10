/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：CheckPort.cpp
描  述：用PING各个端口，检查各个端口是否能通。
版  本：1.0
作  者：康  林
E_Mail：kl222@126.com
日  期：2005年11月11日
时  间：14:57:56
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10
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
	SetName(_T("测试端口"));

	CString szPath = GetCurrentDir();
	szPath += _T("\\") + g_6690iINIFile;
	TCHAR szRe [1024];

	if(::GetPrivateProfileString(_T("PING"), _T("TIMEOUT"), _T("5000"), szRe, 1024, szPath) == 0)
	{
		m_plog->Message(_T("读取PING的超时时间失败"));
		return;
	} // 结束 if(::GetPrivateProfileString(_T("MACIP"), _T("TIMEOUT"), _T("5000"), szRe, 1024, szPath) == 0)
	m_TimeOut = _ttoi(szRe);

	if(::GetPrivateProfileString(_T("PING"), _T("PINGNUM"), _T("1"), szRe, 1024, szPath) == 0)
	{
		m_plog->Message(_T("读取PING的次数失败"));
		return;
	} // 结束 if(::GetPrivateProfileString(_T("PING"), _T("PINGNUM"), _T("1"), szRe, 1024, szPath) == 0)
	m_nPingNum = _ttoi(szRe);

	if(::GetPrivateProfileString(_T("PING"), _T("IPNUM"), _T("1"), szRe, 1024, szPath) == 0)
	{
		m_plog->Message(_T("读取PING的IP地址个数失败"));
		return;
	} // 结束 if(::GetPrivateProfileString(_T("PING"), _T("IPNUM"), _T("1"), szRe, 1024, szPath) == 0)
	m_nIPNum = _ttoi(szRe);

	for(int i = 0; i < m_nIPNum; i++)
	{
		CString sztmp;
		sztmp.Format(_T("%d"), i + 1);
		sztmp = _T("IP") + sztmp;
		if(::GetPrivateProfileString(_T("PING"), sztmp, _T("192.168.0.1"), szRe, 1024, szPath) == 0)
		{
			m_plog->Message(_T("读取IP地址失败"));
			return;
		} // 结束 if(::GetPrivateProfileString(_T("PING"), sztmp, _T("192.168.0.1"), szRe, 1024, szPath) == 0)
		sztmp = szRe;
		m_szIP.push_back(sztmp);
	} // 结束 for(int i = 0; i < m_nIPNum; i++)
	
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
		sztmp.Format(_T("正在检查端口 %d ，对应的IP地址为：%s  ......"), i + 1, m_szIP[i]);
		m_plog->Message(sztmp);
		for(int j = 0; j < m_nPingNum; j++)
		{
			if(!Ping(m_szIP[i], i))
			{
				bPing = TRUE;
				sztmp.Format(_T("第 %d 个端口，相应的IP地址为：%s，测试"), i + 1, m_szIP[i]);
				m_plog->Pass(sztmp);
				break;
			} // 结束 if(Ping(m_szIP[i], i))
		} // 结束 for(int j = 0; j < m_nPingNum; j++)
		if(!bPing)
		{
			//PING不通
			sztmp.Format(_T("第 %d 个端口，对应的IP地址为：%s，测试"), i + 1, m_szIP[i]);
			m_plog->Faile(sztmp);
			nPort = 1;
		} // 结束 if(!bPing)
	} // 结束 for(int i = 0; i < m_nIPNum; i++)
	if(nPort)
	{
		m_plog->Faile(_T("端口测试"));
	} // 结束 if(nPort)
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
	TRACE(_T("%d:%s:%s\n"), uSeq, _T("开始发送"), szIP);
	m_Sock.SendTo(&head, sizeof(head), uPort, szIP);

	int i = m_nPingNum;

	while(1)
	{
		if(!m_Sock.SetTimeOut(m_TimeOut))
		{
			m_plog->Message(_T("Socket设置超时失败。"));
			return 1;
		} // 结束 if(!m_Sock.SetTimeOut(m_TimeOut))
		
		TRACE(_T("%d:%s:%s\n"), i, _T("开始接收"), szIP);
		if(SOCKET_ERROR == m_Sock.ReceiveFrom(buf, sizeof(buf), szIP, uPort))
		{
			if(WSAEINTR == GetLastError())
			{
				m_plog->Message(_T("接收超时。"));
				TRACE(_T("接收超时。\n"));
				if(!m_Sock.KillTimeOut())
				{
					m_plog->Message(_T("结束超时出错。"));
				} // 结束 if(!m_Sock.KillTimeOut())
				return 2;
			}
			else
			{
				m_plog->Message(_T("接收出错。"));
				TRACE(_T("接收出错。\n"));
				if(!m_Sock.KillTimeOut())
				{
					m_plog->Message(_T("结束超时出错。"));
				} // 结束 if(!m_Sock.KillTimeOut())
				return 3;
			}
		} // 结束 if(SOCKET_ERROR == m_Sock.ReceiveFrom(buf, sizeof(buf), szIP, uPort))
		
		TRACE(_T("%d:%s\n"), i, _T("接收结束"));
		if(icmp.ProccessICMP(buf, &head) == ICMP_Echo_Reply)
		{
			if(head.sICMP.sUS.us2 == htons(uSeq))
			{
				if(!m_Sock.KillTimeOut())
				{
					m_plog->Message(_T("结束超时出错。"));
				} // 结束 if(!m_Sock.KillTimeOut())
				return 0; 
			}
			else
			{
				TRACE(_T("接收的 ICMP 数据不对:%d:%d\n"), uSeq, ntohs(head.sICMP.sUS.us2));
			}
		} // 结束 if(icmp.ProccessICMP(buf, &head) == ICMP_Echo_Reply)
		else
		{
			TRACE(_T("不是 ICMP 包。\n"));
		}
		
		if(!m_Sock.KillTimeOut())
		{
			m_plog->Message(_T("结束超时出错。"));
		} // 结束 if(!m_Sock.KillTimeOut())

		i--;

	} // 结束 while(1)

	if(!m_Sock.KillTimeOut())
	{
		m_plog->Message(_T("结束超时出错。"));
	} // 结束 if(!m_Sock.KillTimeOut())

	return 4;
}
