// TestManager.cpp: implementation of the TestManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TestManager.h"
#include "GPIBDevice.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TestManager::TestManager()
{
    m_pGPIB = NULL;
    m_bStopAtFail = false;
}

TestManager::~TestManager()
{
    for (int i=0; i<m_ItemSet.size(); ++i)
    {
        delete m_ItemSet[i];
    }
    delete m_pGPIB;
}

void TestManager::StartAll()
{
    DoPrepare();
    int fail = 0;
    for (int i=0; i<m_ItemSet.size(); ++i)
    {
        if (!StartTestItem(i))
        {
            ++fail;
            if (m_bStopAtFail) break;
        }
    }
    if (fail > 0)   // some test item fail
    {
        DoEndWord(false);
        SisLogger::GetInstance()->LogFail();
    }
    else            // all item pass
    {
        DoEndWord(true);
        SisLogger::GetInstance()->LogSucc();
    }
}

bool TestManager::AddTestItem(TestItem * pItem)
{
    bool bRet = false;
    ITEMVECTOR::iterator it = m_ItemSet.end();
    ITEMVECTOR::size_type size = m_ItemSet.size();
    m_ItemSet.insert(it, pItem);
    if (size != m_ItemSet.size())
        bRet = true;

    return bRet;
}

