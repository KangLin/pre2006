// Cracker.h: interface for the CCracker class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CRACKER_H__BB9890C6_F7B8_48EE_8FB5_5AA25D05E6E1__INCLUDED_)
#define AFX_CRACKER_H__BB9890C6_F7B8_48EE_8FB5_5AA25D05E6E1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GetPassword.h"

class CCracker  
{
public:
	CCracker();
	virtual ~CCracker();

	//返回0表示得到密码,其它表示没有得到密码
	typedef DWORD (*CRACKERFUN)(LPCTSTR pszPassword);
	enum STATUS{STOP, START, PAUSE, GETPASSWORD};

	//得到密码
	CString GetPassword();
	int SetPassword(LPCTSTR pszPassword);
	
	//设置得到破解密码对象的指针
	int SetGetPassword(CGetPassword* pGetPassword);
	//设置线程个数
	int SetThreadNumber(int nNum);

	//开始破解
	int StartCrack();
	int StopCrack();
	int PauseCrack();
	
	//得到状态
	int GetStatus();
	int SetStatus(int nStatus);	
	
	//设置破解函数指针
	int SetCrackFun(CRACKERFUN pFun);
	CRACKERFUN GetCrackFun();
	
private:
	int m_nStatus; //运行状态
	int m_nThread; //破解线程个数
	CGetPassword* m_pPassword;//得到密码类指针
	CRACKERFUN m_pCracker;//破解函数指针
	CString m_szPassword; //得到的密码
	
	HANDLE m_hMutex_Password;

	//破解线程
	static DWORD pCrackerThread(void* pPara);

};

#endif // !defined(AFX_CRACKER_H__BB9890C6_F7B8_48EE_8FB5_5AA25D05E6E1__INCLUDED_)
