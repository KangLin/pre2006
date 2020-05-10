#include "StdAfx.h"
#include ".\logon.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CLogon::CLogon(void)
{
	SetLogonFile();
	m_hControl = GetStdHandle(STD_OUTPUT_HANDLE);
}

CLogon::~CLogon(void)
{
	if(m_logFile.m_pStream != NULL)
	{
		m_logFile.Close();
	} // ���� if(m_logFile.m_pStream != NULL)

	CloseHandle(m_hControl);
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
int CLogon::Success(LPCTSTR lpszInfo, BOOL bSuccess)
{
	CString info(lpszInfo);
	if(bSuccess || lpszInfo == NULL)
	{
		info = _T("�� �� �� �ɹ� �� �� ��\n");
		ShowText(info, GREEN);
		m_logFile.WriteString(info);
	}
	else
	{
		_tprintf(info);
		m_logFile.WriteString(info);
		ShowText(_T("�ɹ��̡̡�\n"), GREEN);
		m_logFile.WriteString(_T("�ɹ��̡̡�\n"));
	} // ���� if(bSuccess || lpszInfo == NULL)
	
	return 0;
}

// ���ʧ����Ϣ
int CLogon::Faile(LPCTSTR lpszInfo, BOOL bFail)
{
	CString info(lpszInfo);
	if(bFail || lpszInfo == NULL)
	{
		info = _T("�� �� �� ʧ�� �� �� ��\n");
		ShowText(info);
		m_logFile.WriteString(info);
	}
	else
	{
		_tprintf(info);
		m_logFile.WriteString(info);
		ShowText(_T("ʧ�ܡ�����\n"));
		m_logFile.WriteString(_T("ʧ�ܡ�����\n"));
	} // ���� if(bFail || lpszInfo == NULL)
		
	return 0;
}

int CLogon::Error(LPCTSTR lpszInfo)
{
	_tprintf(lpszInfo);
	m_logFile.WriteString(lpszInfo);
	ShowText(_T("���������\n"));
	m_logFile.WriteString(_T("���������\n"));
	return 0;
}

// ���ͨ����Ϣ
int CLogon::Pass(LPCTSTR lpszInfo)
{
	if(!lpszInfo)
	{
		ShowText(_T("�� �� �� ͨ�� �� �� ��\n"), GREEN);
		m_logFile.WriteString(_T("�� �� �� ͨ�� �� �� ��\n"));
	}
	else
	{
		CString sztmp(lpszInfo);
		_tprintf(sztmp);
		m_logFile.WriteString(sztmp);
		sztmp = _T("ͨ���̡̡�\n");
		ShowText(sztmp, GREEN);
		m_logFile.WriteString(sztmp);
	} // ���� if(lpszInfo)
	return 0;
}

// �����Ϣ���Լ��л��з�
int CLogon::Message(LPCTSTR lpszMessage, BOOL bEntry, FONT_COLOR color)
{
	if(lpszMessage)
	{
		m_logFile.WriteString(lpszMessage);
		if(NOCOLOR == color)
		{
			_tprintf(lpszMessage);
		}
		else
		{
			ShowText(lpszMessage, color);
		} // ���� if(NOCOLOR == color)
	} // ���� if(lpszMessage)	
	if(bEntry)
	{
		_tprintf(_T("\n"));
		m_logFile.WriteString("\n");
	} // ���� if(bEntry)
		
	return 0;
}

int CLogon::ShowText(LPCTSTR lpszText, FONT_COLOR color)
{
	CONSOLE_SCREEN_BUFFER_INFO screeninfo;
	::GetConsoleScreenBufferInfo(m_hControl, &screeninfo);
	SetConsoleTextAttribute(m_hControl, color | FOREGROUND_INTENSITY);
	_tprintf(lpszText);
	SetConsoleTextAttribute(m_hControl, screeninfo.wAttributes);

	return 0;
}