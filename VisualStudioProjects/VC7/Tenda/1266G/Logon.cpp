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
	} // 结束 if(m_logFile.m_pStream != NULL)
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
int CLogon::Success(LPCTSTR szInfo, BOOL bSuccess)
{
	CString info(szInfo);
	if(bSuccess || szInfo == NULL)
	{
		info = _T("* * *  成功  * * *");
	}
	else
	{
		info += _T("成功！");
	} // 结束 if(bSuccess || szInfo == NULL)
	info += _T("\n");
	_tprintf(info);
	m_logFile.WriteString(info);
	return 0;
}

// 输出失败信息
int CLogon::Faile(LPCTSTR szInfo, BOOL bFail)
{
	CString info(szInfo);
	if(bFail || szInfo == NULL)
	{
		info = _T("！！！ 失败 ！！！");
	}
	else
	{
		info += _T("失败！！！");
	} // 结束 if(bFail || szInfo == NULL)
	info += _T("\n");
	_tprintf(info);	
	m_logFile.WriteString(info);
	
	return 0;
}

// 输出通过信息
int CLogon::Pass(LPCTSTR szInfo)
{
	if(!szInfo)
	{
		_tprintf(_T("* * * 通过 * * *\n"));
		m_logFile.WriteString(_T("* * * 通过 * * *\n"));
	}
	else
	{
		CString sztmp(szInfo);
		sztmp += _T("测试通过***\n");
		_tprintf(sztmp);
		m_logFile.WriteString(sztmp);
	} // 结束 if(szInfo)
	return 0;
}

// 输出信息：自己有换行符
int CLogon::Message(LPCTSTR lpszMessage, BOOL bEntry)
{
	if(lpszMessage)
	{
		m_logFile.WriteString(lpszMessage);
		_tprintf(lpszMessage);
	} // 结束 if(lpszMessage)	
	if(bEntry)
	{
		_tprintf(_T("\n"));
		m_logFile.WriteString("\n");
	} // 结束 if(bEntry)
		
	return 0;
}
