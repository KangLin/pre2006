/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：Test.cpp
描  述：测试程序主类
用  法：
        1、用SetVerInfo设置程序标题、SetVerNum设置版本号、SetTime设置时间。
		2、在 OnPrepare 中初始化。
		3、用 AddItem 加入测试项的实例。
版  本：1.0
作  者：康  林
E_Mail：kl222@126.com
日  期：2005年11月9日
时  间：17:04:45
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10
*******************************************************************************************************/

// Test.cpp: implementation of the CTest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "iostream"
#include "Test.h"
#include "Logon.h"
#include <conio.h>
#include "CommonFunction.h"

//增加:加入测试项目的头文件


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern CString g_INIFile;

CTest::CTest()
{
	m_szVerInfo = _T("              产测程序");
	SetVerNum();
	m_Time = CTime::GetCurrentTime();
}

CTest::~CTest()
{
	if(!m_TestItem.empty())
	{
		for(int i = 0; i < m_TestItem.size(); i++)
		{
			delete m_TestItem[i];
		} // 结束 for(int i = 0; i < m_TestItem.size(); i++)
		m_TestItem.clear();
	} // 结束 if(!m_TestItem.empty())
	ClearError();
}

int CTest::SetVerInfo(LPCTSTR szInfo)
{
	m_szVerInfo = szInfo;
	return 0;
}

int CTest::ShowVerInfo()
{
	CString sztmp;
	string szCom(_T("==================================================================\n"));
	m_log.Message(szCom.c_str());
	m_log.Message(m_szVerInfo.c_str());
	m_log.Message(_T("\n"));
	sztmp = _T("                       版本号：");
	sztmp = sztmp + m_szMajor + _T(".") + m_szMinor;
	m_log.Message(sztmp);
	m_log.Message(_T("\n"));
	sztmp = _T("                   日期：");
	sztmp += m_Time.Format(_T("%Y年%m月%d日"));
	m_log.Message(sztmp);
	m_log.Message(_T("\n"));
	m_log.Message(_T("                 深圳吉祥腾达科技有限公司\n"));
	m_log.Message(szCom.c_str());

	return 0;
}

int CTest::SetVerNum(LPCTSTR lpszMajor, LPCTSTR lpszMinor)
{
	if(NULL == lpszMajor || NULL == lpszMinor)
	{
		return 1;
	} // 结束 if(NULL == lpszMajor || NULL == lpszMinor)
	m_szMajor = lpszMajor;
	m_szMinor = lpszMinor;
	return 0;
}

int CTest::SetTime(CTime tm)
{
	m_Time = tm;
	return 0;
}

int CTest::DoPrepare(void)
{
	return 0;
}

int CTest::StartTest(void)
{
	//CTime t(2006, 2, 20, 0, 0, 0), cur;
	//cur = CTime::GetCurrentTime();

	//CString szPath = GetCurrentDir();
	//szPath += _T("\\") + g_INIFile;
	//TCHAR szRe [1024];
	//szRe [0] = _T('0');
	//szRe [1] = 0;

	//if(::GetPrivateProfileString(_T("MACADDR"), _T("LIMIT"), _T("0"), szRe, 1024, szPath) == 0)
	//{		
	//	return 1;
	//} // 结束 if(::GetPrivateProfileString(_T("MACADDR"), _T("LIMIT"), _T("0"), szRe, 1024, szPath) == 0)
	//
	//if(t < cur && !_tcscmp(szRe, _T("0")))
	//{
	//	return 1;
	//} // 结束 if(t < cur && !_tcscmp(szRe, _T("0")))

	int reval;
    	
	ShowVerInfo();

	if(DoPrepare())
	{
		return 1;
	} // 结束 if(DoPrepare())

	m_log.Message();
	m_log.Message(_T("测试目的："));
	for(int i = 0; i < m_TestItem.size(); i++)
	{
		CString sztmp;
		sztmp.Format(_T("... %d、%s"), i + 1, m_TestItem[i]->GetName());
		m_log.Message(sztmp);
	} // 结束 for(int i = 0; i < m_TestItem.size(); i++)

	m_log.Message(_T("\n退出，请按 N 键或 ESC 键。\n开始，请按其它任一键（例如：ENTER）。"));
	TCHAR c;
	//cin >> c;
#if _MSC_VER >= 1300
	c = _gettch();
#else
	c = _getch();
#endif
	if(_T('n') == c || _T('N') == c || 0x1b /*ESC*/ == c)
	{
		return 1;
	} // 结束 if(_T('n') == c || _T('N') == c || 0x1b == c)

	do
	{
		reval = 0;
		m_tmStart = GetTickCount();

		//开始测试
		for(int i = 0; i < m_TestItem.size(); i++)
		{
			BOOL bonce = FALSE;

			m_log.Message();
			m_log.Message(_T("开始"), FALSE);
			m_log.Message(m_TestItem[i]->GetName(), FALSE);
			m_log.Message(_T("......"));

			if(m_TestItem[i]->DoPrepare())
			{
				reval++;
				bonce = TRUE;
				m_ErrorItem.push_back(m_TestItem[i]->GetName()); 
			}
			else
			{
				if(m_TestItem[i]->DoTest())
				{
					reval++;
					bonce = TRUE;
					m_ErrorItem.push_back(m_TestItem[i]->GetName());
				}
				else
				{
					if(m_TestItem[i]->DoEnd())
					{
						reval++;
						bonce = TRUE;
						m_ErrorItem.push_back(m_TestItem[i]->GetName());
					} // 结束 if(m_TestItem[i]->DoEnd())
				} // 结束 if(m_TestItem[i]->DoTest())
			} // 结束 if(m_TestItem[i]->DoPrepare())

			m_log.Message(m_TestItem[i]->GetName(), FALSE);
			m_log.Message(_T("结束。"));
			if(bonce && (i + 1 != m_TestItem.size()))
			{
				CString sztmp;
				sztmp.Format(_T("\n有错误，是否继续进行 %s 测试？\n... 如果否，请按 N 键或 ESC 键。\n... 如果是，请按其它任一键（例如 ENTER 键）。"), m_TestItem[i + 1]->GetName());
				m_log.Message(sztmp);
				beep();

				TCHAR c;
				//cin >> c;
#if _MSC_VER >= 1300
				c = _gettch();
#else
				c = _getch();
#endif
				if(_T('n') == c || _T('N') == c || 0x1b /*ESC*/ == c)
				{
					m_log.Message(_T("N"));
					break;
				} // 结束 if(_T('n') == c || _T('N') == c || 0x1b == c)

				m_log.Message(_T("Y"));

			} // 结束 if(bonce && (i + 1 != m_TestItem.size()))

		} // 结束 for(int i = 0; i < m_TestItem.size(); i++)

	}while(EndTest(!reval));
    
	return 0;
}

int CTest::EndTest(BOOL bSuccess)
{
	m_log.Message();
	DWORD ts = GetTickCount() - m_tmStart;
	CString sztmp;
	sztmp.Format(_T("用时：%d毫秒(%.3f秒)"), ts, (float)ts / (float)1000);
	m_log.Message(sztmp);

	m_log.Message();
	if(bSuccess)
	{
		m_log.Pass();
	}
	else
	{
		m_log.Faile();
		beep();
		for(int i = 0; i < m_ErrorItem.size(); i++)
		{
			CString sztmp(_T("... "));
			CString sz;
			sz.Format(_T("%d. "), i + 1);
			sztmp += sz;
			m_log.Faile(sztmp + m_ErrorItem[i]);
		} // 结束 for(int i = 0; i < m_ErrorItem.size(); i++)
		ClearError();
	} // 结束 while(EndTest(!reval))

	m_log.Message(_T("\n\n是否继续下一次测试？\n... 如果否，请按 N 键或 ESC 键。\n... 如果是，请按其它任一键（例如 ENTER 键）。"));
	TCHAR c;
	
#if _MSC_VER >= 1300
	c = _gettch();
#else
    c = _getch();
#endif

	if(_T('n') == c || _T('N') == c || 0x1b /*ESC*/ == c)
	{
		return 0;
	} // 结束 if(_T('n') == c || _T('N') == c || 0x1b == c)

	m_log.Message(_T("Y"));

	return 1;
}

int CTest::AddItem(CTestItem* pTest)
{
	int nRet = 0;
	nRet = pTest->SetLog(&m_log);
	if(!nRet)
	{
		m_TestItem.push_back(pTest);
	} // 结束 if(!nRet)
	return nRet;
}

int CTest::RemoveItem(int iIndex)
{
	int nRet = 0;
	TRACE(_T("%s(%d) : CTest::RemoveItem 没有实现。\n"), __FILE__, __LINE__);
	return nRet;
}

int CTest::ClearError(void)
{
	if(!m_ErrorItem.empty())
	{
		m_ErrorItem.clear();
	} // 结束 if(!m_ErrorItem.empty())
	return 0;
}

void CTest::beep()
{
	Beep(2000, 1000);
}