// SisPowerTest.h: interface for the SisPowerTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SISPOWERTEST_H__ED7A9AF4_B5D1_43B6_A8A2_171714A36840__INCLUDED_)
#define AFX_SISPOWERTEST_H__ED7A9AF4_B5D1_43B6_A8A2_171714A36840__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SisTestItem.h"

class SisPowerTest : public SisTestItem  
{
public:
	SisPowerTest(DWORD dPower, DWORD dRate,
                 int  nChannel, char cMode);
	virtual ~SisPowerTest();

	void SetLimit(double maxLimit, double minLimit);
	bool CheckValid();

protected:
    void     DoEndWord(bool result);
    void     DoTesting();

protected:
	double   m_maxLimit;
	double   m_minLimit;
	double   m_refPower;
	double   m_actPower;
};

#endif // !defined(AFX_SISPOWERTEST_H__ED7A9AF4_B5D1_43B6_A8A2_171714A36840__INCLUDED_)
