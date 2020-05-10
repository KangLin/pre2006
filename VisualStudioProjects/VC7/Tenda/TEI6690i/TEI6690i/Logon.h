#if !defined(AFX_TEST_H__C38FC8E6_998F_44FC_8D0F_106F0B8BC4F3__INCLUDEE_)
#define AFX_TEST_H__C38FC8E6_998F_44FC_8D0F_106F0B8BC4F3__INCLUDEDE_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CLogon
{
public:
	CLogon(void);
	~CLogon(void);
	int SetLogonFile(LPCTSTR lpszFile = NULL);
	CString GetLogonFile(void);
	// 输出成功信息
	virtual int Success(LPCTSTR szInfo = NULL, BOOL bSuccess = FALSE);
	// 输出失败信息
	virtual int Faile(LPCTSTR szInfo = NULL, BOOL bFail = FALSE);
	// 输出通过信息
	int Pass(LPCTSTR szInfo = NULL);
	// 输出信息
	int Message(LPCTSTR lpszMessage = NULL, BOOL bEntry = TRUE);

private:
	CString m_szFile;
	CStdioFile m_logFile;
	
};

#endif //!define AFX_TEST_H__C38FC8E6_998F_44FC_8D0F_106F0B8BC4F3__INCLUDEDE_