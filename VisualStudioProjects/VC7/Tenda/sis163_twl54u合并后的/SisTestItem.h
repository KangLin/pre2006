// SisTestItem.h: interface for the SisTestItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SISTESTITEM_H__B5146CA0_20CC_4ADE_96D9_52A873CF231C__INCLUDED_)
#define AFX_SISTESTITEM_H__B5146CA0_20CC_4ADE_96D9_52A873CF231C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TestItem.h"
#include "AdapterFun.h"

class SisTestItem : public TestItem  
{
public:
	SisTestItem(DWORD dPower, DWORD dRate,
                int  nChannel, char cMode);
	virtual ~SisTestItem();

    bool StartTest();
	virtual bool CheckValid()=0;

protected:
    virtual void DoPrepare();
    virtual void DoEndWord(bool result);
	virtual void DoTesting()=0;
    DWORD   m_dPower;
    DWORD   m_dRate;
    int     m_nChannel;
    char    m_cMode;
};

#endif // !defined(AFX_SISTESTITEM_H__B5146CA0_20CC_4ADE_96D9_52A873CF231C__INCLUDED_)
