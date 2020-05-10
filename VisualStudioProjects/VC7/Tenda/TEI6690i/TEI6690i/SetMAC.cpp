/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：SetMAC.cpp
描  述：写入MAC地址
版  本：1.0
作  者：康  林
E_Mail：kl222@126.com
日  期：2005年11月8日
时  间：15:31:56
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10
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
	SetName(_T("写入MAC地址"));
	m_szMAC = _T("");

	CString szPath = GetCurrentDir();
	szPath += _T("\\") + g_6690iINIFile;
	TCHAR szRe [1024];
	if(::GetPrivateProfileString(_T("MACIP"), _T("IP"), _T("192.168.0.1"), szRe, 1024, szPath) == 0)
	{
		m_plog->Message(_T("读取写MAC地址的IP失败"));
		return;
	} // 结束 if(::GetPrivateProfileString(_T("MACIP"), _T("IP"), _T("192.168.0.1"), szRe, 1024, szPath) == 0)
	m_szIP = szRe; //_T("192.168.2.1");
	if(::GetPrivateProfileString(_T("MACIP"), _T("PORT"), _T("1212"), szRe, 1024, szPath) == 0)
	{
		m_plog->Message(_T("读取写MAC地址的PORT失败"));
		return;
	} // 结束 if(::GetPrivateProfileString(_T("MACIP"), _T("PORT"), _T("1212"), szRe, 1024, szPath) == 0)
	m_nPort = _ttoi(szRe); // 1212;
	if(::GetPrivateProfileString(_T("MACIP"), _T("TIMEOUT"), _T("5000"), szRe, 1024, szPath) == 0)
	{
		m_plog->Message(_T("读取写MAC地址的超时时间失败"));
		return;
	} // 结束 if(::GetPrivateProfileString(_T("MACIP"), _T("TIMEOUT"), _T("5000"), szRe, 1024, szPath) == 0)
	m_TimeOut = _ttoi(szRe); // 5000;
	if(::GetPrivateProfileString(_T("MACIP"), _T("PACKNUM"), _T("5"), szRe, 1024, szPath) == 0)
	{
		m_plog->Message(_T("读取写MAC地址的次数失败"));
		return;
	} // 结束 if(::GetPrivateProfileString(_T("MACIP"), _T("PACKNUM"), _T("5"), szRe, 1024, szPath) == 0)
	m_Num = _ttoi(szRe);
	if(::GetPrivateProfileString(_T("MACIP"), _T("MACADDRESSINCREATE"), _T("1"), szRe, 1024, szPath) == 0)
	{
		m_plog->Message(_T("读取MAC地址的增加量失败"));
		return;
	} // 结束 if(::GetPrivateProfileString(_T("MACIP"), _T("MACADDRESSINCREATE"), _T("1"), szRe, 1024, szPath) == 0)
	m_Increate = _ttoi(szRe);

	if(0 == m_Sock.Create(m_nPort, SOCK_DGRAM))
	{
		m_plog->Message(_T("WinSock 建立失败。"));
	} // 结束 if(0 == m_Sock.Create(m_nPort, SOCK_DGRAM))

}

CSetMAC::~CSetMAC(void)
{
	m_Sock.Close();
}

int CSetMAC::DoPrepare(void)
{
	//m_plog->Message(_T("开始写入MAC地址......"));

	//从配置文件中读入要写的MAC地址
	CString szPath = GetCurrentDir();
	szPath += _T("\\") + g_INIFile; // _T("Setup.Ini");
	int nLen = 7;

	TCHAR szReturnedString[7];
	if(::GetPrivateProfileString(_T("MACADDR"), _T("MAC_OUI"), _T("00037F"), szReturnedString, nLen, szPath) != 6)
	{
		m_plog->Message(_T("从配置文件中读出MAC地址错误。"));
		return 1;
	} // 结束 if(::GetPrivateProfileString(_T("MACADDR"), _T("MAC_OUI"), _T("00037F"), szReturnedString, nLen, szPath) != 6)
	szReturnedString[6] = _T('\0');
	m_szMAC = _T("set mac=");
	m_szMAC += szReturnedString;
	if(::GetPrivateProfileString(_T("MACADDR"), _T("MAC_CURR_ADDR"), _T("-1"), szReturnedString, nLen, szPath) != 6)
	{
		m_plog->Message(_T("从配置文件中读出MAC地址错误。"));
		return 1;
	} // 结束 if(::GetPrivateProfileString(_T("MACADDR"), _T("MAC_CURR_ADDR"), _T("-1"), szReturnedString, nLen, szPath) != 6)
	m_szMAC += szReturnedString;
	m_szMAC.MakeLower();
	m_plog->Message(_T("写入的MAC地址为："), FALSE);
	m_plog->Message(m_szMAC);

	if(WriteMAC())
	{
		//写入MAC地址失败
		return 2;
	} // 结束 if(WriteMAC())

	//向配置文件中写入下次的MAC地址
	DWORD nextAddr = HexStrToDWORD(szReturnedString, 6);
	nextAddr += m_Increate;
	_stprintf(szReturnedString, "%06X", nextAddr);
	if(!::WritePrivateProfileString(_T("MACADDR"), _T("MAC_CURR_ADDR"), szReturnedString, szPath))
	{
		m_plog->Message(_T("MAC地址写入配置文件失败！！！"));
		return 2;
	} // 结束 if(!::WritePrivateProfileString(_T("MACADDR"), _T("MAC_CURR_ADDR"), szReturnedString, szPath))
	//_tprintf(_T("下次写入的MAC地址为：%s\n"), szReturnedString);
	
	return 0;
}


/*******************************************************************************************************
函数名：WriteMAC
描  述：写入MAC地址
参  数：void：无
返回值：类型为 int 。成功返回零，失败返回非零。
版  本：1.0
作  者：康  林
时  间：2005年11月8日 15:30:59
*******************************************************************************************************/
int CSetMAC::WriteMAC(void)
{
	TCHAR tmp[1024];
	CString reOK;
	int iLen;

	reOK = _T("ok "); //对方应答数据
	reOK += m_szMAC;
	m_bSet = FALSE;
	//调用写入MAC地址函数
	for(int i = 0; i < m_Num; i++)
	{
		m_plog->Message(_T("第 "), FALSE);
		m_plog->Message(_itot(i + 1, tmp, 10), FALSE);
		m_plog->Message(_T(" 次写入MAC地址......"));

		if(SOCKET_ERROR == m_Sock.SendTo(m_szMAC, m_szMAC.GetLength(), m_nPort, m_szIP))
		{
			m_plog->Message(_T("写MAC时，发送数据出错。"));
			TRACE(_T("%d\n"), GetLastError());
			continue;
		} // 结束 if(SOCKET_ERROR == m_Sock.SendTo(m_szMAC, m_szMAC.GetLength(), m_nPort, m_szIP))

		if(!m_Sock.SetTimeOut(m_TimeOut))
		{
			TRACE(_T("设置MAC地址的Socket设置超时失败。"));
			continue;
		} // 结束 if(!m_Sock.SetTimeOut(m_TimeOut))
		iLen = m_Sock.ReceiveFrom(tmp, 1024, m_szIP, m_nPort);
		if(SOCKET_ERROR != iLen)
		{
			tmp[iLen] = _T('\0');
			if(reOK == tmp)
			{
				//m_plog->Message(_T("收到数据："), FALSE);
				//m_plog->Message(tmp);
				m_bSet = TRUE;
				m_Sock.KillTimeOut();
				break;
			}
			else
			{
				m_plog->Message(_T("应答数据错误："), FALSE);
				m_plog->Message(tmp);
			} // 结束 (reOK == tmp)
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
	if(m_bSet)
	{
		m_plog->Success(_T("MAC地址写入"));
		return 0;
	}
	else
	{
		m_plog->Faile(_T("MAC地址写入"));
		return 1;
	} // 结束 if(m_bSet)
	return 0;
}

/*******************************************************************************************************
函数名：HexStrToDWORD
描  述：从用字符串表示的十六进制转换为DWORD
参  数：
        char * str：十六进制的数字字符串
		int nSize ：要转换的长度
返回值：类型为 DWORD 。
版  本：1.0
作  者：康  林
时  间：2005年11月4日 21:28:34
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
				} // 结束 if(str[i] >= _T('A') && str[i] <= _T('F'))
			} // 结束 if(str[i] >= _T('a') && str[i] <= _T('f'))
        }
    }

    return value;
}
