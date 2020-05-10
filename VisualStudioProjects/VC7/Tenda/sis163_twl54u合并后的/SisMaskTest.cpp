// SisMaskTest.cpp: implementation of the SisMaskTest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sis163.h"
#include "SisMaskTest.h"
#include "GPIBDevice.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SisMaskTest::SisMaskTest(DWORD dPower, DWORD dRate,
                int  nChannel, char cMode)
 : SisTestItem(dPower, dRate, nChannel, cMode)
{

}

SisMaskTest::~SisMaskTest()
{

}

void SisMaskTest::SetCmpValue(int value)
{
	m_cmpValue = value;
}

bool SisMaskTest::CheckValid()
{
    DoTesting();

    return (m_actValue <= m_cmpValue);
}

void SisMaskTest::DoTesting()
{
    AFun_SpecturmMask_A(TRUE, m_dRate, AFun_pAdapter);
    AFun_ContinueTxMode(TRUE, AFun_pAdapter);
    SisLogger::GetInstance()->LogMsg(
        "..Start to test Mask with below parameters\n");
    char msg[100];
    sprintf(msg, "....Channel: %d, Mode: %C, Rate: %d\n",
            m_nChannel, m_cMode, m_dRate);
    SisLogger::GetInstance()->LogMsg(msg);
	Sleep(200);
    try 
    {
	    m_actValue = m_pGPIB->MeasSpectralMask(m_nChannel, m_cMode);
    }
    catch (...)
    {
        m_actValue = -99999;
    }
}

void SisMaskTest::DoEndWord(bool result)
{
	char msg[50];
    if (result)
        sprintf(msg, "Mask testing Pass....%d\n", m_actValue);
    else
        sprintf(msg, "Mask testing Fail!!!!%d\n", m_actValue);
	SisLogger::GetInstance()->LogMsg(msg);
    SisLogger::GetInstance()->LogEndl();
    AFun_ContinueTxMode(FALSE, AFun_pAdapter);
    AFun_SpecturmMask_A(FALSE, m_dRate, AFun_pAdapter);
    SisTestItem::DoEndWord(result);
}
