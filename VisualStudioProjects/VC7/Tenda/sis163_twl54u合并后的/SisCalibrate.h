// SisCalibrate.h: interface for the SisCalibrate class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SISCALIBRATE_H__06A3EEF1_0EA8_4484_A858_7CC660707437__INCLUDED_)
#define AFX_SISCALIBRATE_H__06A3EEF1_0EA8_4484_A858_7CC660707437__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SisTestItem.h"

class SisCalibrate : public SisTestItem  
{
public:
	SisCalibrate(DWORD dPower, DWORD dRate,
                 int  nChannel, char cMode);
	virtual ~SisCalibrate();

    void     SetWishPower(double dWishG, double dWishB);
    void     SetRefPower(DWORD dRefG, DWORD dRefB);

protected:
    bool     CheckValid();
    void     DoTesting();
    void     DoEndWord(bool result);

protected:
    DWORD    m_dReflectG;
    DWORD    m_dReflectB;
    double   m_dWishPwrG;
    double   m_dWishPwrB;
    DWORD    m_dRefPwrG;
    DWORD    m_dRefPwrB;
    
private:
	double Calibrate(char cMode, DWORD dWishPwr, DWORD dRefPwr);
};

#endif // !defined(AFX_SISCALIBRATE_H__06A3EEF1_0EA8_4484_A858_7CC660707437__INCLUDED_)
