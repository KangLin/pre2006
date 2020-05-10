// SisPowerTest.cpp: implementation of the SisPowerTest class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sis163.h"
#include "SisPowerTest.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SisPowerTest::SisPowerTest(DWORD dPower, DWORD dRate,
                int  nChannel, char cMode)
 : SisTestItem(dPower, dRate, nChannel, cMode)
{
    
}

SisPowerTest::~SisPowerTest()
{

}

void SisPowerTest::SetLimit(double maxLimit, double minLimit)
{
	m_maxLimit = maxLimit;
	m_minLimit = minLimit;
}

bool SisPowerTest::CheckValid()
{
    DoTesting();
	bool bRet = false;
    if (m_pGPIB->IsOpen())
    {
        bRet = (m_maxLimit >= m_actPower
		     && m_minLimit <= m_actPower);
    }
    return bRet;
}

void SisPowerTest::DoTesting()
{
    SisLogger::GetInstance()->LogMsg(
        "..Start to test Transmit power with below parameters\n");
    char msg[100];
    sprintf(msg, "....Channel: %d, Mode: %C, Rate: %d, MaxLimit: %.2f, MinLimit: %.2f\n",
            m_nChannel, m_cMode, m_dRate, m_maxLimit, m_minLimit);
    SisLogger::GetInstance()->LogMsg(msg);
    AFun_SpecturmMask_A(TRUE, m_dRate, AFun_pAdapter);
    AFun_ContinueTxMode(TRUE, AFun_pAdapter);
    Sleep(200);
    m_actPower = m_pGPIB->MeasChannelPower(m_nChannel, m_cMode);
    sprintf(msg, "....Actual power read from GPIB: %.2f",m_actPower);
    SisLogger::GetInstance()->LogMsg(msg);
    SisLogger::GetInstance()->LogEndl();
}

void SisPowerTest::DoEndWord(bool result)
{
    if (result)
        SisLogger::GetInstance()->LogMsg("Transmit power testing Pass....\n");
    else
        SisLogger::GetInstance()->LogMsg("Transmit power testing Fail!!!!\n");
    SisLogger::GetInstance()->LogEndl();
    AFun_ContinueTxMode(FALSE, AFun_pAdapter);
    AFun_SpecturmMask_A(FALSE, m_dRate, AFun_pAdapter);
    SisTestItem::DoEndWord(result);
}
