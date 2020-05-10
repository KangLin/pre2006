// TestItem.h: interface for the TestItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTITEM_H__8F07F5E2_C80E_4F5A_BA77_690ED598B685__INCLUDED_)
#define AFX_TESTITEM_H__8F07F5E2_C80E_4F5A_BA77_690ED598B685__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GPIBDevice.h"

class TestItem  
{
public:
	TestItem();
	virtual ~TestItem();

    virtual void DoPrepare();
    virtual void DoEndWord(bool result);
    virtual bool StartTest()=0;

	void SetAdapter(PVOID pAdapter) { AFun_pAdapter = pAdapter; }
	void SetGPIBDevice(GPIBDevice * pGPIB);
protected:
	GPIBDevice * m_pGPIB;
	PVOID        AFun_pAdapter;

};

#endif // !defined(AFX_TESTITEM_H__8F07F5E2_C80E_4F5A_BA77_690ED598B685__INCLUDED_)
