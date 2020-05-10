#include "stdafx.h"
#include "CommonFunction.h"

CString g_INIFile = _T("Config.INI");

CString GetCurrentDir()
{
	TCHAR szPath[MAX_PATH];
	::GetModuleFileName(NULL, szPath, MAX_PATH);
	CString path(szPath);
	int i = path.ReverseFind(_T('\\'));
	path = path.Left(i);
	return path;
}

CString GetFileName(LPCTSTR lpszFile)
{
	CString szPath(lpszFile);
	int i = szPath.ReverseFind(_T('\\'));
	CString szFile;
	szFile = szPath.Right(szPath.GetLength() - i - 1);
	return szFile;
}

CString GetFileTitle(LPCTSTR lpszFile)
{
	CString szFile = GetFileName(lpszFile);
	int i = szFile.ReverseFind(_T('.') - 1);
	szFile = szFile.Left(i);
	return szFile;
}