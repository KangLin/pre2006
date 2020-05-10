/*******************************************************************************************************
��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
�ļ�����SetMAC.cpp
��  ����д��MAC��ַ
��  ����1.0
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2005��11��8��
ʱ  �䣺15:31:56
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10
*******************************************************************************************************/

#include "StdAfx.h"
#include ".\setmac.h"
#include "CommonFunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern CString g_INIFile;
extern CString g_6690iINIFile;

CSetMAC::CSetMAC(void)
{
	SetName(_T("д��MAC��ַ"));
	m_szMAC = _T("");

	CString szPath = GetCurrentDir();
	szPath += _T("\\") + g_6690iINIFile;
	TCHAR szRe [1024];
	if(::GetPrivateProfileString(_T("MACIP"), _T("IP"), _T("192.168.0.1"), szRe, 1024, szPath) == 0)
	{
		m_plog->Message(_T("��ȡдMAC��ַ��IPʧ��"));
		return;
	} // ���� if(::GetPrivateProfileString(_T("MACIP"), _T("IP"), _T("192.168.0.1"), szRe, 1024, szPath) == 0)
	m_szIP = szRe; //_T("192.168.2.1");
	if(::GetPrivateProfileString(_T("MACIP"), _T("PORT"), _T("1212"), szRe, 1024, szPath) == 0)
	{
		m_plog->Message(_T("��ȡдMAC��ַ��PORTʧ��"));
		return;
	} // ���� if(::GetPrivateProfileString(_T("MACIP"), _T("PORT"), _T("1212"), szRe, 1024, szPath) == 0)
	m_nPort = _ttoi(szRe); // 1212;
	if(::GetPrivateProfileString(_T("MACIP"), _T("TIMEOUT"), _T("5000"), szRe, 1024, szPath) == 0)
	{
		m_plog->Message(_T("��ȡдMAC��ַ�ĳ�ʱʱ��ʧ��"));
		return;
	} // ���� if(::GetPrivateProfileString(_T("MACIP"), _T("TIMEOUT"), _T("5000"), szRe, 1024, szPath) == 0)
	m_TimeOut = _ttoi(szRe); // 5000;
	if(::GetPrivateProfileString(_T("MACIP"), _T("PACKNUM"), _T("5"), szRe, 1024, szPath) == 0)
	{
		m_plog->Message(_T("��ȡдMAC��ַ�Ĵ���ʧ��"));
		return;
	} // ���� if(::GetPrivateProfileString(_T("MACIP"), _T("PACKNUM"), _T("5"), szRe, 1024, szPath) == 0)
	m_Num = _ttoi(szRe);
	if(::GetPrivateProfileString(_T("MACIP"), _T("MACADDRESSINCREATE"), _T("1"), szRe, 1024, szPath) == 0)
	{
		m_plog->Message(_T("��ȡMAC��ַ��������ʧ��"));
		return;
	} // ���� if(::GetPrivateProfileString(_T("MACIP"), _T("MACADDRESSINCREATE"), _T("1"), szRe, 1024, szPath) == 0)
	m_Increate = _ttoi(szRe);

	if(0 == m_Sock.Create(m_nPort, SOCK_DGRAM))
	{
		m_plog->Message(_T("WinSock ����ʧ�ܡ�"));
	} // ���� if(0 == m_Sock.Create(m_nPort, SOCK_DGRAM))

}

CSetMAC::~CSetMAC(void)
{
	m_Sock.Close();
}

int CSetMAC::DoPrepare(void)
{
	//m_plog->Message(_T("��ʼд��MAC��ַ......"));

	//�������ļ��ж���Ҫд��MAC��ַ
	CString szPath = GetCurrentDir();
	szPath += _T("\\") + g_INIFile; // _T("Setup.Ini");
	int nLen = 7;

	TCHAR szReturnedString[7];
	if(::GetPrivateProfileString(_T("MACADDR"), _T("MAC_OUI"), _T("00037F"), szReturnedString, nLen, szPath) != 6)
	{
		m_plog->Message(_T("�������ļ��ж���MAC��ַ����"));
		return 1;
	} // ���� if(::GetPrivateProfileString(_T("MACADDR"), _T("MAC_OUI"), _T("00037F"), szReturnedString, nLen, szPath) != 6)
	szReturnedString[6] = _T('\0');
	m_szMAC = _T("set mac=");
	m_szMAC += szReturnedString;
	if(::GetPrivateProfileString(_T("MACADDR"), _T("MAC_CURR_ADDR"), _T("-1"), szReturnedString, nLen, szPath) != 6)
	{
		m_plog->Message(_T("�������ļ��ж���MAC��ַ����"));
		return 1;
	} // ���� if(::GetPrivateProfileString(_T("MACADDR"), _T("MAC_CURR_ADDR"), _T("-1"), szReturnedString, nLen, szPath) != 6)
	m_szMAC += szReturnedString;
	m_szMAC.MakeLower();
	m_plog->Message(_T("д���MAC��ַΪ��"), FALSE);
	m_plog->Message(m_szMAC);

	if(WriteMAC())
	{
		//д��MAC��ַʧ��
		return 2;
	} // ���� if(WriteMAC())

	//�������ļ���д���´ε�MAC��ַ
	DWORD nextAddr = HexStrToDWORD(szReturnedString, 6);
	nextAddr += m_Increate;
	_stprintf(szReturnedString, "%06X", nextAddr);
	if(!::WritePrivateProfileString(_T("MACADDR"), _T("MAC_CURR_ADDR"), szReturnedString, szPath))
	{
		m_plog->Message(_T("MAC��ַд�������ļ�ʧ�ܣ�����"));
		return 2;
	} // ���� if(!::WritePrivateProfileString(_T("MACADDR"), _T("MAC_CURR_ADDR"), szReturnedString, szPath))
	//_tprintf(_T("�´�д���MAC��ַΪ��%s\n"), szReturnedString);
	
	return 0;
}


/*******************************************************************************************************
��������WriteMAC
��  ����д��MAC��ַ
��  ����void����
����ֵ������Ϊ int ���ɹ������㣬ʧ�ܷ��ط��㡣
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��11��8�� 15:30:59
*******************************************************************************************************/
int CSetMAC::WriteMAC(void)
{
	TCHAR tmp[1024];
	CString reOK;
	int iLen;

	reOK = _T("ok "); //�Է�Ӧ������
	reOK += m_szMAC;
	m_bSet = FALSE;
	//����д��MAC��ַ����
	for(int i = 0; i < m_Num; i++)
	{
		m_plog->Message(_T("�� "), FALSE);
		m_plog->Message(_itot(i + 1, tmp, 10), FALSE);
		m_plog->Message(_T(" ��д��MAC��ַ......"));

		if(SOCKET_ERROR == m_Sock.SendTo(m_szMAC, m_szMAC.GetLength(), m_nPort, m_szIP))
		{
			m_plog->Message(_T("дMACʱ���������ݳ���"));
			TRACE(_T("%d\n"), GetLastError());
			continue;
		} // ���� if(SOCKET_ERROR == m_Sock.SendTo(m_szMAC, m_szMAC.GetLength(), m_nPort, m_szIP))

		if(!m_Sock.SetTimeOut(m_TimeOut))
		{
			TRACE(_T("����MAC��ַ��Socket���ó�ʱʧ�ܡ�"));
			continue;
		} // ���� if(!m_Sock.SetTimeOut(m_TimeOut))
		iLen = m_Sock.ReceiveFrom(tmp, 1024, m_szIP, m_nPort);
		if(SOCKET_ERROR != iLen)
		{
			tmp[iLen] = _T('\0');
			if(reOK == tmp)
			{
				//m_plog->Message(_T("�յ����ݣ�"), FALSE);
				//m_plog->Message(tmp);
				m_bSet = TRUE;
				m_Sock.KillTimeOut();
				break;
			}
			else
			{
				m_plog->Message(_T("Ӧ�����ݴ���"), FALSE);
				m_plog->Message(tmp);
			} // ���� (reOK == tmp)
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
	if(m_bSet)
	{
		m_plog->Success(_T("MAC��ַд��"));
		return 0;
	}
	else
	{
		m_plog->Faile(_T("MAC��ַд��"));
		return 1;
	} // ���� if(m_bSet)
	return 0;
}

/*******************************************************************************************************
��������HexStrToDWORD
��  ���������ַ�����ʾ��ʮ������ת��ΪDWORD
��  ����
        char * str��ʮ�����Ƶ������ַ���
		int nSize ��Ҫת���ĳ���
����ֵ������Ϊ DWORD ��
��  ����1.0
��  �ߣ���  ��
ʱ  �䣺2005��11��4�� 21:28:34
*******************************************************************************************************/
DWORD CSetMAC::HexStrToDWORD(char * str, int nSize)
{
    DWORD value=0;

	for(int i = 0; i < nSize; ++i)
    {
		if(str[i] >= '0' && str[i] <= '9')
        {
    	    value <<= 4;
    	    value += (str[i] - '0');
        }
        else
        {
			value <<= 4;
			if(str[i] >= _T('a') && str[i] <= _T('f'))
			{
				value += (str[i] - _T('a') + 10);
			}				
			else
			{
				if(str[i] >= _T('A') && str[i] <= _T('F'))
				{
					value += (str[i] - _T('A') + 10);
				} // ���� if(str[i] >= _T('A') && str[i] <= _T('F'))
			} // ���� if(str[i] >= _T('a') && str[i] <= _T('f'))
        }
    }

    return value;
}
