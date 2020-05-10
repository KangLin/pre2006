// SisCalibrate.cpp: implementation of the SisCalibrate class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sis163.h"
#include "SisCalibrate.h"
#include <iostream>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int MAX_TIME = 1;		      //please setting by you device power range
const int EE_POWER_SITE = 0x52;
const int MULTI_NO = 10000;       //for read power unit
const int RFPowerStep = 0x10;
const int POWER_RANGE_OK = 10000; //for 1 DBM

using std::cout;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SisCalibrate::SisCalibrate(DWORD dPower, DWORD dRate,
                int  nChannel, char cMode)
 : SisTestItem(dPower, dRate, nChannel, cMode)
{
     m_dRefPwrB = 0x7f;
     m_dRefPwrG = 0x5F;
}

SisCalibrate::~SisCalibrate()
{

}

void SisCalibrate::SetWishPower(double dWishG, double dWishB)
{
    m_dWishPwrG = dWishG;
    m_dWishPwrB = dWishB;
}

void SisCalibrate::SetRefPower(DWORD dRefG, DWORD dRefB)
{
    m_dRefPwrG = dRefG;
    m_dRefPwrB = dRefB;
}

bool SisCalibrate::CheckValid()
{
    DoTesting();
	return true;
	//return (m_dReflectG != 0 && m_dReflectB != 0);
}


//*************** calibrate testing funtion of G and B mode*****************//
void SisCalibrate::DoTesting()
{
    SisLogger::GetInstance()->LogMsg(
        "..Start to Calibrate with below parameters\n");
    char msg[100];
    sprintf(msg, "....Channel: %d, Mode: %C, Rate: %d, WishPwrB: %.2f, WishPwrG: %.2f\n",
            m_nChannel, m_cMode, m_dRate, m_dWishPwrB, m_dWishPwrG);
    SisLogger::GetInstance()->LogMsg(msg);
    m_cMode = 'G';
    AFun_SetTxRate(0x6c, AFun_pAdapter);
    AFun_SpecturmMask_A(TRUE, 0x6c, AFun_pAdapter);
    m_dReflectG = Calibrate('G', m_dWishPwrG, m_dRefPwrG);
    sprintf(msg, "....ResultPower of Mode G: %d\n", m_dReflectG);
    SisLogger::GetInstance()->LogMsg(msg);
    AFun_SpecturmMask_A(FALSE, 0x6c, AFun_pAdapter);
    m_cMode = 'B';
    AFun_SetTxRate(0x16, AFun_pAdapter);
    AFun_SpecturmMask_B(TRUE, 0x16, AFun_pAdapter);
    m_dReflectB = Calibrate('B', m_dWishPwrB, m_dRefPwrB);
    sprintf(msg, "....ResultPower of Mode B: %d", m_dReflectB);
    SisLogger::GetInstance()->LogMsg(msg);
    SisLogger::GetInstance()->LogEndl();
    AFun_SpecturmMask_B(FALSE, 0x16, AFun_pAdapter);
}

void SisCalibrate::DoEndWord(bool result)
{
    if(result && m_dReflectG > 0 && m_dReflectB > 0)
    {
		AFun_WriteEEPROM((EE_POWER_SITE/2 + m_nChannel - 1),
			(WORD)((m_dReflectG<<8) + m_dReflectB),
            AFun_pAdapter);
	}

    char msg[100];
    if (result)
        sprintf(msg, "Channel %d calibrate over...\n",
        m_nChannel);
    else
        sprintf(msg, "Channel %d calibrate fail...\n",
        m_nChannel);
    SisLogger::GetInstance()->LogMsg(msg);
    SisLogger::GetInstance()->LogEndl();

    m_dReflectB = m_dReflectG = 0;
    SisTestItem::DoEndWord(result);
}





double SisCalibrate::Calibrate(char cMode,
                               DWORD dWishPwr,
                               DWORD dRefPwr)
{
    DWORD resultPower = m_cMode == 'B' ? m_dRefPwrB : m_dRefPwrG;
	
	//******** start calibrate power
	for(int i=0;i<=MAX_TIME; i++)
	{
		AFun_SetTxPower(resultPower, AFun_pAdapter); //set transmite power
		//**** do not move
		if(i==0)
			Sleep(200);//must for power meter to stable do not move (100 may be fail)
		else if(i==1)
			Sleep(150);
		else if(i==2)
			Sleep(100);
		else
			Sleep(100);

		double readValue = m_pGPIB->MeasChannelPower(m_nChannel, m_cMode);
        readValue *= MULTI_NO;

		if( (dWishPwr * MULTI_NO) >= readValue)
        {
			if( ((dWishPwr*MULTI_NO) - readValue) <  POWER_RANGE_OK )
            {
				break;
			}
			else
            {
				resultPower += RFPowerStep;
			}
		}
		else
        {
			if( (readValue-(dWishPwr * MULTI_NO)) <  POWER_RANGE_OK )
            {
				break;
			}
			else
            {
				resultPower -= RFPowerStep;
			}
		}

		if(i>=MAX_TIME)
        {
			resultPower = 0;
		}
	}

    return resultPower;
}
//******** end calibration   power*************