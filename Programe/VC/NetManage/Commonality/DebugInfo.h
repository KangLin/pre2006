#pragma once

class CDebugInfo
{
public:
	CDebugInfo(void);
	CDebugInfo(LPCSTR lpszFile, INT nLine);
	~CDebugInfo(void);

	INT WriteV(LPCTSTR pszFmt, va_list arg_ptr);

	void __cdecl operator()(const TCHAR * pszFmt, ...);

private:
	std::string m_szFileName;
	INT m_nLineNo;
};

void PRINTF(const TCHAR * pszFmt, ...);
