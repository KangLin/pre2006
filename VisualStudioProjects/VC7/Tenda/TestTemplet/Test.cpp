/*******************************************************************************************************
��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
�ļ�����Test.cpp
��  �������Գ�������
��  ����
        1����SetVerInfo���ó�����⡢SetVerNum���ð汾�š�SetTime����ʱ�䡣
		2���� OnPrepare �г�ʼ����
		3���� AddItem ����������ʵ����
��  ����1.0
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2005��11��9��
ʱ  �䣺17:04:45
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10
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

//����:���������Ŀ��ͷ�ļ�


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

extern CString g_INIFile;

CTest::CTest()
{
	m_szVerInfo = _T("              �������");
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
		} // ���� for(int i = 0; i < m_TestItem.size(); i++)
		m_TestItem.clear();
	} // ���� if(!m_TestItem.empty())
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
	sztmp = _T("                       �汾�ţ�");
	sztmp = sztmp + m_szMajor + _T(".") + m_szMinor;
	m_log.Message(sztmp);
	m_log.Message(_T("\n"));
	sztmp = _T("                   ���ڣ�");
	sztmp += m_Time.Format(_T("%Y��%m��%d��"));
	m_log.Message(sztmp);
	m_log.Message(_T("\n"));
	m_log.Message(_T("                 ���ڼ����ڴ�Ƽ����޹�˾\n"));
	m_log.Message(szCom.c_str());

	return 0;
}

int CTest::SetVerNum(LPCTSTR lpszMajor, LPCTSTR lpszMinor)
{
	if(NULL == lpszMajor || NULL == lpszMinor)
	{
		return 1;
	} // ���� if(NULL == lpszMajor || NULL == lpszMinor)
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
	//} // ���� if(::GetPrivateProfileString(_T("MACADDR"), _T("LIMIT"), _T("0"), szRe, 1024, szPath) == 0)
	//
	//if(t < cur && !_tcscmp(szRe, _T("0")))
	//{
	//	return 1;
	//} // ���� if(t < cur && !_tcscmp(szRe, _T("0")))

	int reval;
    	
	ShowVerInfo();

	if(DoPrepare())
	{
		return 1;
	} // ���� if(DoPrepare())

	m_log.Message();
	m_log.Message(_T("����Ŀ�ģ�"));
	for(int i = 0; i < m_TestItem.size(); i++)
	{
		CString sztmp;
		sztmp.Format(_T("... %d��%s"), i + 1, m_TestItem[i]->GetName());
		m_log.Message(sztmp);
	} // ���� for(int i = 0; i < m_TestItem.size(); i++)

	m_log.Message(_T("\n�˳����밴 N ���� ESC ����\n��ʼ���밴������һ�������磺ENTER����"));
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
	} // ���� if(_T('n') == c || _T('N') == c || 0x1b == c)

	do
	{
		reval = 0;
		m_tmStart = GetTickCount();

		//��ʼ����
		for(int i = 0; i < m_TestItem.size(); i++)
		{
			BOOL bonce = FALSE;

			m_log.Message();
			m_log.Message(_T("��ʼ"), FALSE);
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
					} // ���� if(m_TestItem[i]->DoEnd())
				} // ���� if(m_TestItem[i]->DoTest())
			} // ���� if(m_TestItem[i]->DoPrepare())

			m_log.Message(m_TestItem[i]->GetName(), FALSE);
			m_log.Message(_T("������"));
			if(bonce && (i + 1 != m_TestItem.size()))
			{
				CString sztmp;
				sztmp.Format(_T("\n�д����Ƿ�������� %s ���ԣ�\n... ������밴 N ���� ESC ����\n... ����ǣ��밴������һ�������� ENTER ������"), m_TestItem[i + 1]->GetName());
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
				} // ���� if(_T('n') == c || _T('N') == c || 0x1b == c)

				m_log.Message(_T("Y"));

			} // ���� if(bonce && (i + 1 != m_TestItem.size()))

		} // ���� for(int i = 0; i < m_TestItem.size(); i++)

	}while(EndTest(!reval));
    
	return 0;
}

int CTest::EndTest(BOOL bSuccess)
{
	m_log.Message();
	DWORD ts = GetTickCount() - m_tmStart;
	CString sztmp;
	sztmp.Format(_T("��ʱ��%d����(%.3f��)"), ts, (float)ts / (float)1000);
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
		} // ���� for(int i = 0; i < m_ErrorItem.size(); i++)
		ClearError();
	} // ���� while(EndTest(!reval))

	m_log.Message(_T("\n\n�Ƿ������һ�β��ԣ�\n... ������밴 N ���� ESC ����\n... ����ǣ��밴������һ�������� ENTER ������"));
	TCHAR c;
	
#if _MSC_VER >= 1300
	c = _gettch();
#else
    c = _getch();
#endif

	if(_T('n') == c || _T('N') == c || 0x1b /*ESC*/ == c)
	{
		return 0;
	} // ���� if(_T('n') == c || _T('N') == c || 0x1b == c)

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
	} // ���� if(!nRet)
	return nRet;
}

int CTest::RemoveItem(int iIndex)
{
	int nRet = 0;
	TRACE(_T("%s(%d) : CTest::RemoveItem û��ʵ�֡�\n"), __FILE__, __LINE__);
	return nRet;
}

int CTest::ClearError(void)
{
	if(!m_ErrorItem.empty())
	{
		m_ErrorItem.clear();
	} // ���� if(!m_ErrorItem.empty())
	return 0;
}

void CTest::beep()
{
	Beep(2000, 1000);
}