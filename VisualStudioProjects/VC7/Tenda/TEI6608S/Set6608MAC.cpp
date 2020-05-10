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
		m_plog->Message(_T("��ȡдMAC��ַ��IPʧ��"));
		return;
	} // ���� if(::GetPrivateProfileString(_T("WRITEMAC"), _T("IP"), _T("192.168.0.1"), szRe, 1024, szPath) == 0)
	m_szIP = szRe; //_T("192.168.2.1");
	if(::GetPrivateProfileString(_T("WRITEMAC"), _T("PORT"), _T("1212"), szRe, 1024, szPath) == 0)
	{
		m_plog->Message(_T("��ȡдMAC��ַ��PORTʧ��"));
		return;
	} // ���� if(::GetPrivateProfileString(_T("WRITEMAC"), _T("PORT"), _T("1212"), szRe, 1024, szPath) == 0)
	m_nPort = _ttoi(szRe); // 1212;
	if(::GetPrivateProfileString(_T("WRITEMAC"), _T("LOCATEPORT"), _T("0"), szRe, 1024, szPath) == 0)
	{
		m_plog->Message(_T("��ȡдMAC��ַ��LOACTEPORTʧ��"));
		return;
	} // ���� if(::GetPrivateProfileString(_T("WRITEMAC"), _T("LOCATEPORT"), _T("0"), szRe, 1024, szPath) == 0)
	m_nLocatePort = _ttoi(szRe); // 1212;
	
	if(::GetPrivateProfileString(_T("WRITEMAC"), _T("TIMEOUT"), _T("5000"), szRe, 1024, szPath) == 0)
	{
		m_plog->Message(_T("��ȡдMAC��ַ�ĳ�ʱʱ��ʧ��"));
		return;
	} // ���� if(::GetPrivateProfileString(_T("WRITEMAC"), _T("TIMEOUT"), _T("5000"), szRe, 1024, szPath) == 0)
	m_TimeOut = _ttoi(szRe); // 5000;

	if(m_Sock.Create(m_nLocatePort, SOCK_DGRAM) == 0)
	{
		m_plog->Message(_T("Socket����ʧ�ܡ�"));
		return;
	} // ���� if(m_Sock.Create(m_nLocatePort, SOCK_DGRAM) == 0)

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
	//����д��MAC��ַ����
	for(int i = 0; i < m_Num; i++)
	{
		m_plog->Message(_T("�� "), FALSE);
		m_plog->Message(_itot(i + 1, tmp, 10), FALSE);
		m_plog->Message(_T(" ��д��MAC��ַ......"));

		if(SOCKET_ERROR == m_Sock.SendTo(SendTFTP, 2 + rdc.GetLength() + 1 + 6 + 1, m_nPort, m_szIP))
		{
			m_plog->Message(_T("дMACʱ���������ݳ���"));
			TRACE(_T("%d\n"), GetLastError());
			continue;
		} // ���� if(SOCKET_ERROR == m_Sock.SendTo(SendTFTP, 2 + rdc.GetLength() + 1 + 6 + 1, m_nPort, m_szIP))

		if(!m_Sock.SetTimeOut(m_TimeOut))
		{
			TRACE(_T("����MAC��ַ��Socket���ó�ʱʧ�ܡ�"));
			continue;
		} // ���� if(!m_Sock.SetTimeOut(m_TimeOut))
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
				m_plog->Message(_T("Ӧ��������MAC��ַ����"), FALSE);
				m_plog->Message(tmpTFTP->buf);
			}
			else
			{
				m_plog->Message(_T("Ӧ�����ݴ���"), FALSE);
				m_plog->Message(tmp);
			} // ���� if(tmpTFTP->op == htons(0xe0))
		}
		else
		{
			if(WSAEINTR == GetLastError())
			{
				m_plog->Message(_T("���ճ�ʱ��")); 
			}
			else
			{
				m_plog->Message(_T("дMACʱ���������ݳ�������Ϊ��"), FALSE);
				tmp[iLen + 1] = _T('\0');
				m_plog->Message(tmp);
			} // ���� if(WSAEINTR == GetLastError())
		} // ���� if(SOCKET_ERROR != iLen)
		m_Sock.KillTimeOut();
	} // ���� for(int i = 0; i < m_Num; i++)

	//��֤�Ƿ�д��ɹ�
	if(bSet)
	{
		m_plog->Success(_T("MAC��ַд��"));
		m_plog->Message(_T("�밴��λ��5�룬�ָ��������á�"));
		return 0;
	}
	else
	{
		m_plog->Faile(_T("MAC��ַд��"));
		return 1;
	} // ���� if(bSet)
	return 0;
}