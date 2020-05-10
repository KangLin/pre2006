#include "StdAfx.h"
#include "DebugInfo.h"
#include <locale.h>

CDebugInfo::CDebugInfo(void)
{
}

CDebugInfo::CDebugInfo(LPCSTR lpszFile, INT nLine)
{
	ASSERT(lpszFile);
	m_szFileName = lpszFile;
	m_nLineNo = nLine;
}

CDebugInfo::~CDebugInfo(void)
{
}

void __cdecl CDebugInfo::operator()(const TCHAR * pszFmt, ...)
{
	va_list ptr; va_start(ptr, pszFmt);
	va_list arg_ptr;
	va_start(arg_ptr, pszFmt);
	WriteV(pszFmt, arg_ptr);
	va_end(ptr);
}

//mk:@MSITStore:C:\Program%20Files\Microsoft%20Visual%20Studio\MSDN98\98VS\2052\code0x07.chm::/devdoc/good/code/sdktools/image/drwatson/c5400_8to5.htm
INT CDebugInfo::WriteV(LPCTSTR pszFmt, va_list arg_ptr)
{
	TCHAR * buf = new TCHAR[1024];
	if(NULL == buf)
	{
		return FALSE;
	} // ½áÊø if(NULL == buf)
	_tstring szOutString;
#ifdef _UNICODE
	_stprintf_s(buf, 1024, _T("%S(%d):"), m_szFileName.c_str(), m_nLineNo);
#else
	_stprintf_s(buf, 1024, _T("%s(%d):"), m_szFileName.c_str(), m_nLineNo);
#endif // ½áÊø #ifdef _UNICODE
	
	
	szOutString = buf;
	
	_vsntprintf_s(buf, 1024, _TRUNCATE, pszFmt, arg_ptr);
	szOutString += buf;

#ifndef _DEBUG
	setlocale(LC_ALL, ".OCP"); //"chinese-simplified");
	_tprintf(_T("%s"), buf);
#endif

	delete []buf;

#ifdef _DEBUG
	OutputDebugString(szOutString.c_str());
#endif

	return S_OK;
}

void PRINTF(const TCHAR * pszFmt, ...)
{
	va_list ptr;
	va_start(ptr, pszFmt);
	va_list arg_ptr;
	va_start(arg_ptr, pszFmt);
	TCHAR * buf = new TCHAR[1024];
	if(NULL == buf)
	{
		return;
	}// ½áÊø if(NULL == buf)
	_vsntprintf_s(buf, 1024, _TRUNCATE, pszFmt, arg_ptr);
	setlocale(LC_ALL, ".OCP"); //"chinese-simplified");
	_tprintf(_T("%s"), buf);
	va_end(ptr);
	delete []buf;
}