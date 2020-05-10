#if !defined(AFX_TEST_H__C38FC8E6_998F_44FC_8D0F_106F0B8BC4F3__INCLUDEE_)
#define AFX_TEST_H__C38FC8E6_998F_44FC_8D0F_106F0B8BC4F3__INCLUDEDE_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLogon
{
public:
	enum FONT_COLOR
	{
		NOCOLOR = 0,
		RED = FOREGROUND_RED,
		GREEN = FOREGROUND_GREEN,
		BULE = FOREGROUND_BLUE,
		YELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
	};

	CLogon(void);
	~CLogon(void);
	int SetLogonFile(LPCTSTR lpszFile = NULL);
	CString GetLogonFile(void);
	// 输出成功信息
	virtual int Success(LPCTSTR lpszInfo = NULL, BOOL bSuccess = FALSE);
	// 输出通过信息
	int Pass(LPCTSTR lpszInfo = NULL);
	// 输出失败信息
	virtual int Faile(LPCTSTR lpszInfo = NULL, BOOL bFail = FALSE);
	int Error(LPCTSTR lpszInfo = NULL);
	// 输出信息
	int Message(LPCTSTR lpszMessage = NULL, BOOL bEntry = TRUE, FONT_COLOR color = NOCOLOR);

private:
	CString m_szFile;
	CStdioFile m_logFile;
	HANDLE m_hControl;

	
	int ShowText(LPCTSTR lpszText, FONT_COLOR color = RED);
};

#endif //!define AFX_TEST_H__C38FC8E6_998F_44FC_8D0F_106F0B8BC4F3__INCLUDEDE_