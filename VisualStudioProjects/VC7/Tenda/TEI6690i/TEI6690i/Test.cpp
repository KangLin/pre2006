/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：Test.cpp
描  述：测试程序主类
用  法：
        1、用SetVerInfo设置程序标题。
		2、在 OnPrepare 中加入测试项的实例。
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
#include "Test.h"
#include "Logon.h"
#include ".\test.h"
#include "SetMac.h"
#include "iostream"
#include "CheckPort.h"
#include <conio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTest::CTest()
{
	m_szVerInfo = _T("             TEI6690i/I+ TEI6618i/I+ 产测程序");
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
	string szCom(_T("==================================================================\n"));
	m_log.Message(szCom.c_str());
	m_log.Message(m_szVerInfo.c_str());
	m_log.Message(_T("\n"));
	m_log.Message(_T("                 深圳吉祥腾达科技有限公司\n"));
	m_log.Message(szCom.c_str());
	m_log.Message();
	m_log.Message(_T("测试目的："));
	for(int i = 0; i < m_TestItem.size(); i++)
	{
		CString sztmp;
		sztmp.Format(_T("... %d、%s"), i + 1, m_TestItem[i]->GetName());
		m_log.Message(sztmp);
	} // 结束 for(int i = 0; i < m_TestItem.size(); i++)
	return 0;
}

/*******************************************************************************************************
函数名：DoPrepare
描  述：
参  数：void：无
返回值：类型为 int 。
版  本：1.0
作  者：康  林
时  间：2005年11月11日 19:00:18
*******************************************************************************************************/
int CTest::DoPrepare(void)
{
	CCheckPort * pCheckPort = new CCheckPort;
	if(pCheckPort)
	{
		AddItem(pCheckPort); 
	}
	else
	{
		m_log.Message(_T("CCheckPort 构造失败"));
	} // 结束 if(pCheckPort)

	CSetMAC * pSetMac = new CSetMAC;
	if(pSetMac)
	{
		AddItem(pSetMac);
	}
	else
	{
		m_log.Message(_T("CSetMAC 构造失败"));
	} // 结束 if(!pSetMac)

	return 0;
}

int CTest::StartTest(void)
{
	int reval;
	
	DoPrepare();
	ShowVerInfo();

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
			if(bonce && (i != m_TestItem.size()))
			{
				if(i != m_TestItem.size() - 1)
				{
					CString sztmp;
					sztmp.Format(_T("\n有错误，是否继续进行 %s 测试？否，请按 N 键。是，请按其它任一键 (ENTER)。"), m_TestItem[i + 1]->GetName());
					m_log.Message(sztmp);
					beep();

					TCHAR c;
					//cin >> c;
#if _MSC_VER >= 1300
					c = _gettch();
#else
					c = _getch();
#endif
					if(_T('n') == c || _T('N') == c)
					{
						break;
					} // 结束 if(_T('n') == c || _T('N') == c)
				}
				else
				{
					beep();
				} // 结束 if(i != m_TestItem.size() - 1)		
			} // 结束 if(bonce && (i != m_TestItem.size()))

		} // 结束 for(int i = 0; i < m_TestItem.size(); i++)

	}while(EndTest(!reval));
    
	return 0;
}

int CTest::EndTest(BOOL bSuccess)
{
	m_log.Message();
	DWORD ts = GetTickCount() - m_tmStart;
	
	CString sztmp;
	sztmp.Format(_T("用时：%d毫秒"), ts);
	m_log.Message(sztmp);
	m_log.Message();
	if(bSuccess)
	{
		m_log.Pass();
	}
	else
	{
		m_log.Faile();
		//beep();
		for(int i = 0; i < m_ErrorItem.size(); i++)
		{
			CString sztmp(_T(".... "));
			CString sz;
			sz.Format(_T("%d. "), i + 1);
			sztmp += sz;
			m_log.Faile(sztmp + m_ErrorItem[i]);
		} // 结束 for(int i = 0; i < m_ErrorItem.size(); i++)
		ClearError();
	} // 结束 while(EndTest(!reval))

	m_log.Message(_T("\n\n是否继续下一次测试？否，请按 N 键。是，请按其它任一键 (ENTER)。"));
	TCHAR c;
	//cin >> c;
#if _MSC_VER >= 1300
				c = _gettch();
#else
				c = _getch();
#endif

	if(_T('n') == c || _T('N') == c || _T('\e') == c)
	{
		return 0;
	} // 结束 if(_T('n') == c || _T('N') == c || _T('\e') == c)
	return 1;
}

int CTest::AddItem(CTestItem* pTest)
{
	pTest->SetLog(&m_log);
	m_TestItem.push_back(pTest);
	return 0;
}

int CTest::RemoveItem(int iIndex)
{
	return 0;
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