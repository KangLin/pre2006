#include "stdafx.h"
#include ".\set6608mac.h"
#include "..\TestTemplet\CommonFunction.h"

extern CString g_INIFile;

CSet6608MAC::CSet6608MAC(void)
{
	CString szPath = GetCurrentDir();
	szPath += _T("\\") + g_INIFile;
	TCHAR szRe [1024];
	if(::GetPrivateProfileString(_T("WRITEMAC"), _T("IP"), _T("192.168.0.1"), szRe, 1024, szPath) == 0)
	{
		m_plog->Message(_T("读取写MAC地址的IP失败"));
		return;
	} // 结束 if(::GetPrivateProfileString(_T("WRITEMAC"), _T("IP"), _T("192.168.0.1"), szRe, 1024, szPath) == 0)
	m_szIP = szRe; //_T("192.168.2.1");
	if(::GetPrivateProfileString(_T("WRITEMAC"), _T("PORT"), _T("1212"), szRe, 1024, szPath) == 0)
	{
		m_plog->Message(_T("读取写MAC地址的PORT失败"));
		return;
	} // 结束 if(::GetPrivateProfileString(_T("WRITEMAC"), _T("PORT"), _T("1212"), szRe, 1024, szPath) == 0)
	m_nPort = _ttoi(szRe); // 1212;
	if(::GetPrivateProfileString(_T("WRITEMAC"), _T("LOCATEPORT"), _T("0"), szRe, 1024, szPath) == 0)
	{
		m_plog->Message(_T("读取写MAC地址的LOACTEPORT失败"));
		return;
	} // 结束 if(::GetPrivateProfileString(_T("WRITEMAC"), _T("LOCATEPORT"), _T("0"), szRe, 1024, szPath) == 0)
	m_nLocatePort = _ttoi(szRe); // 1212;
	
	if(::GetPrivateProfileString(_T("WRITEMAC"), _T("TIMEOUT"), _T("5000"), szRe, 1024, szPath) == 0)
	{
		m_plog->Message(_T("读取写MAC地址的超时时间失败"));
		return;
	} // 结束 if(::GetPrivateProfileString(_T("WRITEMAC"), _T("TIMEOUT"), _T("5000"), szRe, 1024, szPath) == 0)
	m_TimeOut = _ttoi(szRe); // 5000;

	if(m_Sock.Create(m_nLocatePort, SOCK_DGRAM) == 0)
	{
		m_plog->Message(_T("Socket建立失败。"));
		return;
	} // 结束 if(m_Sock.Create(m_nLocatePort, SOCK_DGRAM) == 0)

}

CSet6608MAC::~CSet6608MAC(void)
{
	m_Sock.Close();
}

int CSet6608MAC::WriteMAC(void)
{
	TCHAR tmp[1024];
	TFTP * tmpTFTP;
	TFTP * SendTFTP;
	char szSend[100];
	char MAC[6];
	int iLen;
	CString rdc = _T("rdcloader");
	SendTFTP = (TFTP * )szSend;
	SendTFTP->op = htons(0xe2);
	memcpy(&szSend[2], rdc, rdc.GetLength() + 1);
	MACStrToHex((char * )(LPCTSTR)m_szMAC, MAC);
	memcpy(szSend + 2 + rdc.GetLength() + 1, MAC, 6);
	szSend[2 + rdc.GetLength() + 1 + 6] = 0;
		
	BOOL bSet = FALSE;
	//调用写入MAC地址函数
	for(int i = 0; i < m_Num; i++)
	{
		m_plog->Message(_T("第 "), FALSE);
		m_plog->Message(_itot(i + 1, tmp, 10), FALSE);
		m_plog->Message(_T(" 次写入MAC地址......"));

		if(SOCKET_ERROR == m_Sock.SendTo(SendTFTP, 2 + rdc.GetLength() + 1 + 6 + 1, m_nPort, m_szIP))
		{
			m_plog->Message(_T("写MAC时，发送数据出错。"));
			TRACE(_T("%d\n"), GetLastError());
			continue;
		} // 结束 if(SOCKET_ERROR == m_Sock.SendTo(SendTFTP, 2 + rdc.GetLength() + 1 + 6 + 1, m_nPort, m_szIP))

		if(!m_Sock.SetTimeOut(m_TimeOut))
		{
			TRACE(_T("设置MAC地址的Socket设置超时失败。"));
			continue;
		} // 结束 if(!m_Sock.SetTimeOut(m_TimeOut))
		iLen = m_Sock.Receive(tmp, 1024);//, m_szIP, m_nLocatePort);
		if(SOCKET_ERROR != iLen)
		{
			tmpTFTP = (TFTP * )tmp;
			if(tmpTFTP->op == htons(0xe0))
			{
				if(!memcmp(tmpTFTP->buf, MAC, 6))
				{
					bSet = TRUE;
					m_Sock.KillTimeOut();
					break;
				}
				m_plog->Message(_T("应答数据中MAC地址错误："), FALSE);
				m_plog->Message(tmpTFTP->buf);
			}
			else
			{
				m_plog->Message(_T("应答数据错误："), FALSE);
				m_plog->Message(tmp);
			} // 结束 if(tmpTFTP->op == htons(0xe0))
		}
		else
		{
			if(WSAEINTR == GetLastError())
			{
				m_plog->Message(_T("接收超时。")); 
			}
			else
			{
				m_plog->Message(_T("写MAC时，接收数据出错。数据为："), FALSE);
				tmp[iLen + 1] = _T('\0');
				m_plog->Message(tmp);
			} // 结束 if(WSAEINTR == GetLastError())
		} // 结束 if(SOCKET_ERROR != iLen)
		m_Sock.KillTimeOut();
	} // 结束 for(int i = 0; i < m_Num; i++)

	//验证是否写入成功
	if(bSet)
	{
		m_plog->Success(_T("MAC地址写入"));
		m_plog->Message(_T("请按复位键5秒，恢复出厂设置。"));
		return 0;
	}
	else
	{
		m_plog->Faile(_T("MAC地址写入"));
		return 1;
	} // 结束 if(bSet)
	return 0;
}