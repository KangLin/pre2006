// SisMaskTest.h: interface for the SisMaskTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SISMASKTEST_H__B8E517BB_C9A2_4F73_BC22_0EB0E5829806__INCLUDED_)
#define AFX_SISMASKTEST_H__B8E517BB_C9A2_4F73_BC22_0EB0E5829806__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SisTestItem.h"

class SisMaskTest : public SisTestItem  
{
public:
	SisMaskTest(DWORD dPower, DWORD dRate,
                int  nChannel, char cMode);
	virtual ~SisMaskTest();

	void SetCmpValue(int value);
	bool CheckValid();

protected:
    void     DoEndWord(bool result);
    void     DoTesting();

protected:
	int  m_cmpValue;
	int  m_actValue;

};

#endif // !defined(AFX_SISMASKTEST_H__B8E517BB_C9A2_4F73_BC22_0EB0E5829806__INCLUDED_)
