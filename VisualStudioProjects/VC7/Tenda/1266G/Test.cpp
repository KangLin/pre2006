/*******************************************************************************************************
��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
�ļ�����Test.cpp
��  �������Գ�������
��  ����
        1����SetVerInfo���ó�����⡣
		2���� OnPrepare �м���������ʵ����
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

//����:���������Ŀ��ͷ�ļ�


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTest::CTest()
{
	m_szVerInfo = _T("             TEI6690i/I+ TEI6618i/I+ �������");
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
	string szCom(_T("==================================================================\n"));
	m_log.Message(szCom.c_str());
	m_log.Message(m_szVerInfo.c_str());
	m_log.Message(_T("\n"));
	m_log.Message(_T("                 ���ڼ����ڴ�Ƽ����޹�˾\n"));
	m_log.Message(szCom.c_str());
	m_log.Message();
	m_log.Message(_T("����Ŀ�ģ�"));
	for(int i = 0; i < m_TestItem.size(); i++)
	{
		CString sztmp;
		sztmp.Format(_T("... %d��%s"), i + 1, m_TestItem[i]->GetName());
		m_log.Message(sztmp);
	} // ���� for(int i = 0; i < m_TestItem.size(); i++)
	return 0;
}

int CTest::DoPrepare(void)
{
	//����:���������Ŀ

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

		//��ʼ����
		for(int i = 0; i < m_TestItem.size(); i++)
		{
			if(reval)
			{
				m_log.Message(_T("\n�д����Ƿ�������ԣ��ǣ��밴 Y �������밴 N ����"));
				TCHAR c;
				cin >> c;
				if(_T('n') == c || _T('N') == c)
				{
					break;
				} // ���� if(_T('n') == c || _T('N') == c)
			} // ���� if(reval)

			m_log.Message();
			m_log.Message(_T("��ʼ"), FALSE);
			m_log.Message(m_TestItem[i]->GetName(), FALSE);
			m_log.Message(_T("......"));

			if(m_TestItem[i]->DoPrepare())
			{
				reval++;				
				m_ErrorItem.push_back(m_TestItem[i]->GetName());
				continue;
			} // ���� if(m_TestItem[i]->DoPrepare())
			if(m_TestItem[i]->DoTest())
			{
				reval++;				
				m_ErrorItem.push_back(m_TestItem[i]->GetName());
				continue;
			} // ���� if(m_TestItem[i]->DoTest())
			if(m_TestItem[i]->DoEnd())
			{
				reval++;				
				m_ErrorItem.push_back(m_TestItem[i]->GetName());
			} // ���� if(m_TestItem[i]->DoEnd())
		} // ���� for(int i = 0; i < m_TestItem.size(); i++)

	}while(EndTest(!reval));
    
	return 0;
}

int CTest::EndTest(BOOL bSuccess)
{
	m_log.Message();
	DWORD ts = GetTickCount() - m_tmStart;
	CString sztmp;
	sztmp.Format(_T("��ʱ��%d����"), ts);
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
		} // ���� for(int i = 0; i < m_ErrorItem.size(); i++)
		ClearError();
	} // ���� while(EndTest(!reval))

	m_log.Message(_T("\n\n�Ƿ������һ�β��ԣ�����ǣ��밴Y�������밴N����"));
	TCHAR c;
	cin >> c;
	if(_T('n') == c || _T('N') == c)
	{
		return 0;
	} // ���� if(_T('n') == c || _T('N') == c)
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
	} // ���� if(!m_ErrorItem.empty())
	return 0;
}
