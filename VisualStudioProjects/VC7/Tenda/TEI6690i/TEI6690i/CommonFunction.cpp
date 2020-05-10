#include "stdafx.h"
#include "CommonFunction.h"

CString g_INIFile = _T("Setup.INI");
CString g_6690iINIFile = _T("6690i.INI");

CString GetCurrentDir()
{
	TCHAR szPath[MAX_PATH];
	::GetModuleFileName(NULL, szPath, MAX_PATH);
	CString path(szPath);
	int i = path.ReverseFind(_T('\\'));
	path = path.Left(i);
	return path;
}