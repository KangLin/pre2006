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
#include "iostream"
#include "Test.h"
#include "Logon.h"

//增加:加入测试项目的头文件


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

int CTest::DoPrepare(void)
{
	//增加:加入测试项目

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
			if(reval)
			{
				m_log.Message(_T("\n有错误，是否继续测试？是，请按 Y 键，否请按 N 键。"));
				TCHAR c;
				cin >> c;
				if(_T('n') == c || _T('N') == c)
				{
					break;
				} // 结束 if(_T('n') == c || _T('N') == c)
			} // 结束 if(reval)

			m_log.Message();
			m_log.Message(_T("开始"), FALSE);
			m_log.Message(m_TestItem[i]->GetName(), FALSE);
			m_log.Message(_T("......"));

			if(m_TestItem[i]->DoPrepare())
			{
				reval++;				
				m_ErrorItem.push_back(m_TestItem[i]->GetName());
				continue;
			} // 结束 if(m_TestItem[i]->DoPrepare())
			if(m_TestItem[i]->DoTest())
			{
				reval++;				
				m_ErrorItem.push_back(m_TestItem[i]->GetName());
				continue;
			} // 结束 if(m_TestItem[i]->DoTest())
			if(m_TestItem[i]->DoEnd())
			{
				reval++;				
				m_ErrorItem.push_back(m_TestItem[i]->GetName());
			} // 结束 if(m_TestItem[i]->DoEnd())
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

	m_log.Message(_T("\n\n是否继续下一次测试？如果是，请按Y键；否，请按N键。"));
	TCHAR c;
	cin >> c;
	if(_T('n') == c || _T('N') == c)
	{
		return 0;
	} // 结束 if(_T('n') == c || _T('N') == c)
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
