// SisTestItem.cpp: implementation of the SisTestItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sis163.h"
#include "SisTestItem.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SisTestItem::SisTestItem(DWORD dPower, DWORD dRate,
                int  nChannel, char cMode)
{
    m_dPower = dPower;
    m_dRate = dRate;
    m_nChannel = nChannel;
    m_cMode = cMode;
}

SisTestItem::~SisTestItem()
{
    
}

// starting a test item
bool SisTestItem::StartTest()
{
    DoPrepare();
    bool bRet = CheckValid();
    DoEndWord(bRet);
    return bRet;
}

// enter test mode, set channel and set txRate
void SisTestItem::DoPrepare()
{
    //set channel
    AFun_SetChannel(m_nChannel, AFun_pAdapter);
    // set rate
    AFun_SetTxRate(m_dRate, AFun_pAdapter);
    Sleep(10);
}

// default do nothing except delay 20ms
void SisTestItem::DoEndWord(bool result)
{
	Sleep(20);
}
