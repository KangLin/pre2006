// Test.h: interface for the CTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TEST_H__C38FC8E6_998F_44FC_8D0F_106F0B8BC4F3__INCLUDED_)
#define AFX_TEST_H__C38FC8E6_998F_44FC_8D0F_106F0B8BC4F3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <string>
#include <vector>
#include "Logon.h"
#include "TestItem.h"

using namespace std;

class CTest  
{
public:
	CTest();
	virtual ~CTest();

	virtual int SetVerInfo(LPCTSTR szInfo);
	virtual int ShowVerInfo();
	int DoPrepare(void);
	virtual int StartTest(void);
	virtual int EndTest(BOOL bSuccess = TRUE);

	virtual int AddItem(CTestItem* pTest);
	virtual int RemoveItem(int iIndex);
	virtual int ClearError(void);

protected:
	string m_szVerInfo; //∞Ê±æ–≈œ¢
	CLogon m_log;
	vector <CTestItem*> m_TestItem;
	vector <CString> m_ErrorItem;
	DWORD m_tmStart;
	
};

#endif // !defined(AFX_TEST_H__C38FC8E6_998F_44FC_8D0F_106F0B8BC4F3__INCLUDED_)
