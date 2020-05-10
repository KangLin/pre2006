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
	} // 结束 if(m_logFile.m_pStream != NULL)

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
	} // 结束 if(NULL == lpszFile)

	if(m_logFile.m_pStream != NULL)
	{
		m_logFile.Close();
	} // 结束 if(NULL == lpszFile)

	m_logFile.Open(m_szFile, CFile::modeCreate | CFile::modeReadWrite);
	
	return 0;
}

CString CLogon::GetLogonFile(void)
{
	return CString(m_szFile);	
}

// 输出成功信息
int CLogon::Success(LPCTSTR lpszInfo, BOOL bSuccess)
{
	CString info(lpszInfo);
	if(bSuccess || lpszInfo == NULL)
	{
		info = _T("√ √ √ 成功 √ √ √\n");
		ShowText(info, GREEN);
		m_logFile.WriteString(info);
	}
	else
	{
		_tprintf(info);
		m_logFile.WriteString(info);
		ShowText(_T("成功√√√\n"), GREEN);
		m_logFile.WriteString(_T("成功√√√\n"));
	} // 结束 if(bSuccess || lpszInfo == NULL)
	
	return 0;
}

// 输出失败信息
int CLogon::Faile(LPCTSTR lpszInfo, BOOL bFail)
{
	CString info(lpszInfo);
	if(bFail || lpszInfo == NULL)
	{
		info = _T("× × × 失败 × × ×\n");
		ShowText(info);
		m_logFile.WriteString(info);
	}
	else
	{
		_tprintf(info);
		m_logFile.WriteString(info);
		ShowText(_T("失败×××\n"));
		m_logFile.WriteString(_T("失败×××\n"));
	} // 结束 if(bFail || lpszInfo == NULL)
		
	return 0;
}

int CLogon::Error(LPCTSTR lpszInfo)
{
	_tprintf(lpszInfo);
	m_logFile.WriteString(lpszInfo);
	ShowText(_T("出错×××\n"));
	m_logFile.WriteString(_T("出错×××\n"));
	return 0;
}

// 输出通过信息
int CLogon::Pass(LPCTSTR lpszInfo)
{
	if(!lpszInfo)
	{
		ShowText(_T("√ √ √ 通过 √ √ √\n"), GREEN);
		m_logFile.WriteString(_T("√ √ √ 通过 √ √ √\n"));
	}
	else
	{
		CString sztmp(lpszInfo);
		_tprintf(sztmp);
		m_logFile.WriteString(sztmp);
		sztmp = _T("通过√√√\n");
		ShowText(sztmp, GREEN);
		m_logFile.WriteString(sztmp);
	} // 结束 if(lpszInfo)
	return 0;
}

// 输出信息：自己有换行符
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
		} // 结束 if(NOCOLOR == color)
	} // 结束 if(lpszMessage)	
	if(bEntry)
	{
		_tprintf(_T("\n"));
		m_logFile.WriteString("\n");
	} // 结束 if(bEntry)
		
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