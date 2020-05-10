// TestManager.h: interface for the TestManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TESTMANAGER_H__FC38ABE2_870A_4790_8379_B86632CB4FE2__INCLUDED_)
#define AFX_TESTMANAGER_H__FC38ABE2_870A_4790_8379_B86632CB4FE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "TestItem.h"
#include "SisLogger.h"

using std::vector;

class GPIBDevice;

class TestManager  
{
public:
    typedef vector<TestItem *> ITEMVECTOR;

	TestManager();
	virtual ~TestManager();

    virtual bool Initialize(int argc, TCHAR* argv[]) = 0;
    virtual void CleanUp() = 0;
    virtual bool DoPrepare() { return true; }
    virtual bool DoEndWord(bool result) { return true; }

    void StartAll();
    virtual bool StartTestItem(int nIndex) = 0;
    bool AddTestItem(TestItem * pItem);

protected:
	GPIBDevice * m_pGPIB;
    bool m_bStopAtFail;
    ITEMVECTOR m_ItemSet;

};

#endif // !defined(AFX_TESTMANAGER_H__FC38ABE2_870A_4790_8379_B86632CB4FE2__INCLUDED_)
