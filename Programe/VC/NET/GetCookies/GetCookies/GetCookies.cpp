// GetCookies.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "GetCookies.h"
#include <math.h>
#define _CRT_RAND_S
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include <Wininet.h>
#include <afxinet.h>
#pragma comment(lib, "Wininet.lib");

// The one and only application object

CWinApp theApp;

using namespace std;

int klRand(int nLowBount, int nUpBount)
{
	CTime tm = CTime::GetCurrentTime();
	srand((unsigned)tm.GetTime());

	return(((double)rand() / (double)RAND_MAX)* nUpBount + nLowBount);
}


int GetCookies()
{
	TCHAR szURL[256];          // buffer to hold the URL
	LPTSTR lpszData = NULL;    // buffer to hold the cookie data
	DWORD dwSize=0;           // variable to get the buffer size needed
	int nRet = 0;
	// Insert code to retrieve the URL.
	_tcscpy(szURL, _T("http://192.168.11.2/gensystem.asp"));

	if(InternetSetCookie(szURL, "oabusyusername", "kangl"))
	{
		if(InternetSetCookie(szURL, "oabusyname", "刘智"))
		
		TRACE("OK");
		return 0;
	} // 结束 if(InternetSetCookie(szURL, "oabusyusername", "zengg"))

retry:

	// The first call to InternetGetCookie will get the required 
	// buffer size needed to download the cookie data.
	if (!InternetGetCookie(szURL, NULL, lpszData, &dwSize))
	{
		// Check for an insufficient buffer error.
		if (GetLastError()== ERROR_INSUFFICIENT_BUFFER)
		{
			// Allocate the necessary buffer.
			lpszData = new TCHAR[dwSize];

			// Try the call again.
			goto retry;
		}
		else
		{
			// Insert error handling code.
			nRet = 1;
		}

	}
	else
	{
		// Insert code to display the cookie data.
		TRACE(_T("Cookiew:%s\n"), lpszData);
		// Release the memory allocated for the buffer.
		delete[]lpszData;
	}
	return nRet;

}

int RequestObject(CHttpConnection * pServer, LPCTSTR lpszContent, LPCTSTR lpszObject, LPCTSTR lpszReferer = NULL)
{
	int nRet = 0;
	CString sztmp, szContext, szUser, szPasswd;
	CHttpFile * pFile = NULL;
	CString strHeaders = _T("Content-Type: application/x-www-form-urlencoded");

	TRY
	{
		//详见:ms-help://MS.VSCC.v80/MS.MSDN.v80/MS.KB.v10.en/enu_kbie_dev/ie_dev/165298.htm
		LPCTSTR lptAccept = _T("image/gif, image/x-xbitmap, image/jpeg, image/pjpeg, application/x-shockwave-flash, application/msword, application/vnd.ms-excel, application/vnd.ms-powerpoint, */*");
		pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_POST, lpszObject, lpszReferer, 1, &lptAccept, NULL, INTERNET_FLAG_KEEP_CONNECTION /*INTERNET_FLAG_RELOAD*/);
		if(!pFile)
		{
			sztmp.Format(_T("找不到文件 %s 。\n"), lpszObject);
			TRACE(sztmp);
			return 3;
		} // 结束 (_T("找不到文件 %s 。\n"), szObject)

		if(!pFile->SendRequest(strHeaders, (LPVOID)lpszContent, _tcslen(lpszContent)))
		{
			TRACE(_T("发送请求出错。\n"));
			delete pFile;
			return 4;
		} // 结束 if(!pFile->SendRequest(strHeaders, (LPVOID)lpszContent, _tcslen(lpszContent)))

		//pFile->WriteString(lpszContent);
		//if(!pFile->EndRequest())
		//{
		//	TRACE(_T("发送请求出错.\n"));
		//	nRet = 4;
		//}// 结束 (!pFile->EndRequest())

		//读取HTML文件
		while(pFile->ReadString(sztmp))
		{
			szContext = szContext + sztmp;
		} // 结束 (pFile->ReadString(sztmp))

		cout << szContext << endl;
		TRACE(_T("%s\n"), szContext);

		CStdioFile file(_T("a.html"), CFile::modeCreate | CFile::modeReadWrite);
		file.Write(szContext, szContext.GetLength());
		file.Close();

		delete pFile;
		return nRet;
	}
	CATCH (CMemoryException, e)
	{
		if(pFile)
		{
			delete pFile;
			nRet = 1;
		}// 结束 if(pFile)
		return nRet;
	}
	END_CATCH

	return nRet;
}

int GetObject(CHttpConnection * pServer, LPCTSTR lpszObject, LPCTSTR lpszReferer = NULL)
{
	CString sztmp, szContext;
	CHttpFile * pFile = NULL;

	TRY
	{
		pFile = pServer->OpenRequest(CHttpConnection::HTTP_VERB_GET, lpszObject, lpszReferer, 1, NULL, NULL, INTERNET_FLAG_KEEP_CONNECTION  /* INTERNET_FLAG_RELOAD*/);
		if(!pFile)
		{
			sztmp.Format(_T("找不到文件 %s 。\n"), lpszObject);
			TRACE(sztmp);
			return 3;
		} // 结束 (_T("找不到文件 %s 。\n"), szObject)

		if(!pFile->SendRequest())
		{
			TRACE(_T("发送请求出错。\n"));
			delete pFile;
			return 4;
		} // 结束 if(!pFile->SendRequest())

		DWORD dwRet, dwLen;
		if(!pFile->QueryInfoStatusCode(dwRet))
		{
			TRACE(_T("查询发送请求出错。\n"));
			delete pFile;
			return 4;
		} // 结束 if(!pFile->QueryInfoStatusCode(dwRet))

		if(dwRet == HTTP_STATUS_DENIED)
		{
			//DWORD dwPrompt;
			//dwPrompt = pFile->ErrorDlg(NULL, ERROR_INTERNET_INCORRECT_PASSWORD,
			//	FLAGS_ERROR_UI_FLAGS_GENERATE_DATA | FLAGS_ERROR_UI_FLAGS_CHANGE_OPTIONS, NULL);

			//// if the user cancelled the dialog, bail out

			//if (dwPrompt != ERROR_INTERNET_FORCE_RETRY)
			//{
			//	cerr << _T("Access denied: Invalid password\n");
			//	ThrowTearException(1);
			//}

			TRACE(_T("%s(%d) : %s\n"), __FILE__, __LINE__, _T("密码错误。"));

			pFile->SendRequest();
			pFile->QueryInfoStatusCode(dwRet);
		}


		//读取HTML文件
		//while(pFile->ReadString(sztmp))
		//{
		//	szContext = szContext + sztmp;
		//} // 结束 while(pFile->ReadString(sztmp))

		//cout << szContext << endl;

		return 0;
	}
	CATCH(CInternetException, e)
	{
		if(pFile)
		{
			delete pFile;
		} // 结束 if(pFile)
		return 1;
	}
	END_CATCH
}

int SendHtml(LPCTSTR pszUser, LPCTSTR pszPasswd)
{
	int nRet = 0;
	CInternetSession Session;
	CHttpConnection * pServer = NULL;
	CString m_szURL = _T("http://192.168.11.2/default.asp");
	CString szReferer = m_szURL;
	CString szUserName(_T("")), szPassword(_T(""));
	CString szUser(pszUser), szPasswd(pszPasswd);

	TRY
	{
		CString szIP;
		INTERNET_PORT nPort;
		CString szObject;
		DWORD dwServiceType;
		CString sztmp;

		if(!AfxParseURL(m_szURL, dwServiceType, szIP, szObject, nPort) || dwServiceType != INTERNET_SERVICE_HTTP)
		{
			sztmp.Format(_T("地址 %s 有错。\n"), m_szURL);
			TRACE(sztmp);
			return 1;
		} // 结束 if(!AfxParseURL(m_szURL, dwServiceType, szIP, szObject, nPort) || dwServiceType != INTERNET_SERVICE_HTTP)

		pServer = Session.GetHttpConnection(szIP, INTERNET_FLAG_KEEP_CONNECTION, nPort, szUserName, szPassword);
		if(!pServer)
		{
			sztmp.Format(_T("不能打开地址 %s 。\n"), m_szURL);
			TRACE(sztmp);
			Session.Close();
			return 2;
		} // 结束 if(!pServer)

		//nRet = GetObject(pServer, szObject, szReferer);
		//if(nRet)
		//{
		//	goto _Exit_;
		//}// 结束 (nRet)

		CString strContent;
		CString strUser(_T("kangl"));
		CString strTime( /*_T("pmgo")*/ _T("amcome"));
		CTime tm = CTime::GetCurrentTime();
		CTime tmNoon(tm.GetYear(), tm.GetMonth(), tm.GetDay(), 9, 0, 0);
		CTime Afternoon(tm.GetYear(), tm.GetMonth(), tm.GetDay(), 18, 0, 0);
		if(tm.GetTime() < tmNoon.GetTime())
		{
			strTime = _T("amcome");
			//Sleep(klRand(2, 5)*1000 * 60);
		} // 结束 if(tm.GetTime() < tmNoon.GetTime())
		else if(tm.GetTime() > Afternoon.GetTime())
		{
			strTime = _T("pmgo");			
			//Sleep(klRand(10, 30)*1000 * 60);
		}
		else
		{
			return 1;
			strTime = _T("");
		}

		CString strButton(_T("%C8%B7%B6%A8"));
		strContent.Format(_T("username=%s&kqtimephase=%s&yy=&okbutton=%s"), szUser, strTime, strButton);

		sztmp.Format(_T("username=%s&password=%s&image2.x=0&image2.y=0"), szUser, szPasswd);
		nRet = RequestObject(pServer, sztmp, szObject, szReferer);
		if(nRet)
		{
			goto _Exit_;
		}// 结束 (nRet)

		szObject = _T("/kq/handkq.asp");
		szReferer = _T("http://192.168.11.2/kq/handkq.asp");
		nRet = RequestObject(pServer, strContent, szObject, szReferer);
		if(nRet)
		{
			goto _Exit_;
		}// 结束 (nRet)
		

_Exit_:
		pServer->Close();
		delete pServer;
		Session.Close();

		return nRet;

	}
	CATCH(CInternetException, e)
	{
		TRACE(_T("连接失败\n"));
		if(pServer)
		{
			delete pServer;
		} // 结束 if(pServer)
		Session.Close();
		e->ReportError();
		return 1;
	}
	END_CATCH
}

int SendHtmlWage(LPCTSTR pszUser, LPCTSTR pszPasswd, LPCTSTR pszName, LPCTSTR pszYear, LPCTSTR pszMonth)
{
	int nRet = 0;
	CInternetSession Session;
	CHttpConnection * pServer = NULL;
	CString m_szURL = _T("http://192.168.11.2/default.asp");
	CString szReferer = m_szURL;
	CString szUserName(_T("")), szPassword(_T(""));
	CString szUser(pszUser), szPasswd(pszPasswd);

	TRY
	{
		CString szIP;
		INTERNET_PORT nPort;
		CString szObject;
		DWORD dwServiceType;
		CString sztmp;

		if(!AfxParseURL(m_szURL, dwServiceType, szIP, szObject, nPort) || dwServiceType != INTERNET_SERVICE_HTTP)
		{
			sztmp.Format(_T("地址 %s 有错。\n"), m_szURL);
			TRACE(sztmp);
			return 1;
		} // 结束 if(!AfxParseURL(m_szURL, dwServiceType, szIP, szObject, nPort) || dwServiceType != INTERNET_SERVICE_HTTP)

		pServer = Session.GetHttpConnection(szIP, INTERNET_FLAG_KEEP_CONNECTION, nPort, szUserName, szPassword);
		if(!pServer)
		{
			sztmp.Format(_T("不能打开地址 %s 。\n"), m_szURL);
			TRACE(sztmp);
			Session.Close();
			return 2;
		} // 结束 if(!pServer)

		//修改查询日期
		CString strContent;
		strContent.Format(_T("tyear=%s&tmonth=%s&submit=%s"), pszYear, pszMonth, "%B2%E9%D1%AF");

		sztmp.Format(_T("username=%s&password=%s&image2.x=0&image2.y=0"), szUser, szPasswd);
		nRet = RequestObject(pServer, sztmp, szObject, szReferer);
		if(nRet)
		{
			goto _Exit_;
		}// 结束 (nRet)

		//设置Cookie
		//GetCookies();
		InternetSetCookie(_T("http://192.168.11.2/wageinf.asp"), _T("oabusyname"), pszName);

		szObject = _T("/wageinf.asp");
		szReferer = _T("http://192.168.11.2/wageinf.asp");
		nRet = RequestObject(pServer, strContent, szObject, szReferer);
		if(nRet)
		{
			goto _Exit_;
		}// 结束 if(nRet)

		ShellExecute(NULL, _T("open"), _T("a.html"), NULL, NULL, SW_NORMAL);

		//DeleteFile(_T("a.html"));

_Exit_:
		pServer->Close();
		delete pServer;
		Session.Close();

		return nRet;

	}
	CATCH(CInternetException, e)
	{
		TRACE(_T("连接失败\n"));
		if(pServer)
		{
			delete pServer;
		} // 结束 if(pServer)
		Session.Close();
		e->ReportError();
		return 1;
	}
	END_CATCH
}

int SendHtmlGetPassword(LPCTSTR pszUser, LPCTSTR pszPasswd, LPCTSTR pszName)
{
	int nRet = 0;
	CInternetSession Session;
	CHttpConnection * pServer = NULL;
	CString m_szURL = _T("http://192.168.11.2/default.asp");
	CString szReferer = m_szURL;
	CString szUserName(_T("")), szPassword(_T(""));
	CString szUser(pszUser), szPasswd(pszPasswd);

	TRY
	{
		CString szIP;
		INTERNET_PORT nPort;
		CString szObject;
		DWORD dwServiceType;
		CString sztmp;

		if(!AfxParseURL(m_szURL, dwServiceType, szIP, szObject, nPort) || dwServiceType != INTERNET_SERVICE_HTTP)
		{
			sztmp.Format(_T("地址 %s 有错。\n"), m_szURL);
			TRACE(sztmp);
			return 1;
		} // 结束 if(!AfxParseURL(m_szURL, dwServiceType, szIP, szObject, nPort) || dwServiceType != INTERNET_SERVICE_HTTP)

		pServer = Session.GetHttpConnection(szIP, INTERNET_FLAG_KEEP_CONNECTION, nPort, szUserName, szPassword);
		if(!pServer)
		{
			sztmp.Format(_T("不能打开地址 %s 。\n"), m_szURL);
			TRACE(sztmp);
			Session.Close();
			return 2;
		} // 结束 if(!pServer)

		//修改查询日期
		CString strContent;
		//strContent.Format(_T("tyear=%s&tmonth=%s&submit=%s"), pszYear, pszMonth, "%B2%E9%D1%AF");

		sztmp.Format(_T("username=%s&password=%s&image2.x=0&image2.y=0"), szUser, szPasswd);
		nRet = RequestObject(pServer, sztmp, szObject, szReferer);
		if(nRet)
		{
			goto _Exit_;
		}// 结束 (nRet)

		//设置Cookie
		//GetCookies();
		InternetSetCookie(_T("http://192.168.11.2/userinf.asp"), _T("oabusyusername"), pszName);

		szObject = _T("/userinf.asp");
		szReferer = _T("http://192.168.11.2/userinf.asp");
		nRet = RequestObject(pServer, strContent, szObject, szReferer);
		if(nRet)
		{
			goto _Exit_;
		}// 结束 if(nRet)

		ShellExecute(NULL, _T("open"), _T("a.html"), NULL, NULL, SW_NORMAL);

		//DeleteFile(_T("a.html"));

_Exit_:
		pServer->Close();
		delete pServer;
		Session.Close();

		return nRet;

	}
	CATCH(CInternetException, e)
	{
		TRACE(_T("连接失败\n"));
		if(pServer)
		{
			delete pServer;
		} // 结束 if(pServer)
		Session.Close();
		e->ReportError();
		return 1;
	}
	END_CATCH
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		_tprintf(_T("Fatal Error: MFC initialization failed\n"));
		nRetCode = 1;
	}
	else
	{
		//考勤
		if(argc == 3)
		{
			SendHtml(argv[1], argv[2]);
			cout << _T("考勤完成。") << endl;
			return 1;
		}// 结束 ("Command Parameter Format:username password")

		//考勤
		if(argc == 4)
		{
			if(_tcsicmp(argv[1], _T("/k")) == 0)
			{
				SendHtml(argv[2], argv[3]);
				cout << _T("考勤完成。") << endl;
				return 1;
			} // 结束 if(_tcsicmp(argv[1], _T("/k")) == 0)
			if(_tcsicmp(argv[1], _T("/w")) == 0)
			{
				TCHAR szUser[30], szYear[30], szMonth[30];
				cout << _T("要查询的用户名 年 月：");
				scanf(_T("%s %s %s"), szUser, szYear, szMonth);
				//得到工资
				SendHtmlWage(argv[2], argv[3], szUser, szYear, szMonth);
				return 1;
			}// 结束 if(_tcsicmp(argv[1], _T("/w")) == 0)
			if(_tcsicmp(argv[1], _T("/p")) == 0)
			{
				TCHAR szUser[30], szYear[30], szMonth[30];
				cout << _T("要查询的用户名");
				scanf(_T("%s"), szUser);
				//得到工资
				SendHtmlGetPassword(argv[2], argv[3], szUser);
				return 1;
			}// 结束 if(_tcsicmp(argv[1], _T("/p")) == 0)
			
			return 1;

		}// 结束 if(argc == 4)

		//考勤
		if(argc == 5)
		{
			if(_tcsicmp(argv[1], _T("/w")) == 0)
			{
				TCHAR szYear[30], szMonth[30];
				cout << _T("要查询的年 月：");
				scanf(_T("%s %s"), szYear, szMonth);
				//得到工资
				SendHtmlWage(argv[2], argv[3], argv[4], szYear, szMonth);
				return 1;
			} // 结束 if(_tcsicmp(argv[1], _T("/w")) == 0)
		}// 结束 if(argc == 5)

		if(argc == 6)
		{
			//得到工资
			SendHtmlWage(argv[1], argv[2], argv[3], argv[4], argv[5]);
			return 1;
		} // 结束 if(argc == 6)

		cout << _T("1、考勤格式:") << endl;
		cout << _T("		命令 登录用户名 登录密码") << endl;

		cout << _T("2、考勤命令格式:") << endl;
		cout << _T("		命令 /k 登录用户名 登录密码") << endl;

		cout << _T("3、得到某人密码命令格式:") << endl;
		cout << _T("		命令 /p 登录用户名 登录密码") << endl;

		cout << _T("4、得到某人工资命令格式:") << endl;
		cout << _T("		命令 /w 登录用户名 登录密码") << endl;

		cout << _T("5、得到某人工资命令格式:") << endl;
		cout << _T("		命令 登录用户名 登录密码 查询用户名 年 月") << endl;

		
	}

	return nRetCode;
}
