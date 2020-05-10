#include "StdAfx.h"
#include ".\logon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CLogon::CLogon(void)
{
	SetLogonFile();
}

CLogon::~CLogon(void)
{
	if(m_logFile.m_pStream != NULL)
	{
		m_logFile.Close();
	} // ���� if(m_logFile.m_pStream != NULL)
}

int CLogon::SetLogonFile(LPCTSTR lpszFile)
{
	TCHAR szPath[MAX_PATH];
	::GetModuleFileName(NULL, szPath, MAX_PATH);
	CString path(szPath), file;
	int i = path.ReverseFind(_T('\\'));
	file = path.Right(path.GetLength() - i);
	path = path.Left(i);
	m_szFile = path;
	m_szFile += _T("\\");

	
	if(NULL == lpszFile)
	{
		m_szFile += file + _T(".log");
	}
	else
	{
		m_szFile += lpszFile;
	} // ���� if(NULL == lpszFile)

	if(m_logFile.m_pStream != NULL)
	{
		m_logFile.Close();
	} // ���� if(NULL == lpszFile)

	m_logFile.Open(m_szFile, CFile::modeCreate | CFile::modeReadWrite);
	
	return 0;
}

CString CLogon::GetLogonFile(void)
{
	return CString(m_szFile);	
}

// ����ɹ���Ϣ
int CLogon::Success(LPCTSTR szInfo, BOOL bSuccess)
{
	CString info(szInfo);
	if(bSuccess || szInfo == NULL)
	{
		info = _T("* * *  �ɹ�  * * *");
	}
	else
	{
		info += _T("�ɹ���");
	} // ���� if(bSuccess || szInfo == NULL)
	info += _T("\n");
	_tprintf(info);
	m_logFile.WriteString(info);
	return 0;
}

// ���ʧ����Ϣ
int CLogon::Faile(LPCTSTR szInfo, BOOL bFail)
{
	CString info(szInfo);
	if(bFail || szInfo == NULL)
	{
		info = _T("������ ʧ�� ������");
	}
	else
	{
		info += _T("ʧ�ܣ�����");
	} // ���� if(bFail || szInfo == NULL)
	info += _T("\n");
	_tprintf(info);	
	m_logFile.WriteString(info);
	
	return 0;
}

// ���ͨ����Ϣ
int CLogon::Pass(LPCTSTR szInfo)
{
	if(!szInfo)
	{
		_tprintf(_T("* * * ͨ�� * * *\n"));
		m_logFile.WriteString(_T("* * * ͨ�� * * *\n"));
	}
	else
	{
		CString sztmp(szInfo);
		sztmp += _T("����ͨ��***\n");
		_tprintf(sztmp);
		m_logFile.WriteString(sztmp);
	} // ���� if(szInfo)
	return 0;
}

// �����Ϣ���Լ��л��з�
int CLogon::Message(LPCTSTR lpszMessage, BOOL bEntry)
{
	if(lpszMessage)
	{
		m_logFile.WriteString(lpszMessage);
		_tprintf(lpszMessage);
	} // ���� if(lpszMessage)	
	if(bEntry)
	{
		_tprintf(_T("\n"));
		m_logFile.WriteString("\n");
	} // ���� if(bEntry)
		
	return 0;
}
