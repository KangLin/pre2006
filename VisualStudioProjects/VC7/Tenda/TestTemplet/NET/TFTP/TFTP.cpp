#include "stdafx.h"
#include ".\tftp.h"
#include "..\..\CommonFunction.h"

extern CString g_INIFile;

CTFTP::CTFTP(void)
{
	CString szPath = GetCurrentDir();
	szPath += _T("\\") + g_INIFile;
	TCHAR szRe [1024];
	if(::GetPrivateProfileString(_T("TFTP"), _T("FILE"), _T(""), szRe, 1024, szPath) < 0)
	{
		TRACE(_T("��ȡ�ļ���ʧ��"));
		return;
	} // ���� if(::GetPrivateProfileString(_T("TFTP"), _T("FILE"), _T(""), szRe, 1024, szPath) < 0)
	m_szFileName = szRe;
	if(m_szFileName != _T("") && -1 == m_szFileName.Find(_T('\\')))
	{
		m_szFileName = GetCurrentDir() + _T("\\") + m_szFileName;
	} // ���� if(m_szFileName != _T("") && -1 == m_szFileName.Find(_T('\\')))
	
	if(::GetPrivateProfileString(_T("TFTP"), _T("IP"), _T("192.168.0.1"), szRe, 1024, szPath) == 0)
	{
		TRACE(_T("��ȡдMAC��ַ��IPʧ��"));
		return;
	} // ���� if(::GetPrivateProfileString(_T("TFTP"), _T("IP"), _T("192.168.0.1"), szRe, 1024, szPath) == 0)
	m_szIP = szRe;

	if(::GetPrivateProfileString(_T("TFTP"), _T("TIMEOUT"), _T("5000"), szRe, 1024, szPath) < 0)
	{
		TRACE(_T("�������ļ��ж�ȡ��ʱʧ��"));
		return;
	} // ���� if(::GetPrivateProfileString(_T("TFTP"), _T("TIMEOUT"), _T("5000"), szRe, 1024, szPath) < 0)
	m_nTimeOut = _ttoi(szRe);
	
	m_nPort = TFTP_PORT;
	SetFileMode();
	m_Send = NULL;
	m_Recv = NULL;
	m_nMaxRepeat = 3;

	if(!m_Sock.Create(0, SOCK_DGRAM))
	{
		return;
	} // ���� if(!m_Sock.Create(0, SOCK_DGRAM))

}

CTFTP::~CTFTP(void)
{
	m_Sock.Close();
}

int CTFTP::SetFileName(LPCTSTR lpszFileName)
{
	ASSERT(lpszFileName != NULL);
	m_szFileName = lpszFileName;
	return 0;
}

int CTFTP::SetFileMode(LPCTSTR lpszFileMode)
{
	m_szFileMode = lpszFileMode;
	return 0;
}