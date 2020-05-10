// GPIBDevice.h: interface for the GPIBDevice class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GPIBDEVICE_H__A13CCAF0_1DBB_44BA_B15F_46E4DB279586__INCLUDED_)
#define AFX_GPIBDEVICE_H__A13CCAF0_1DBB_44BA_B15F_46E4DB279586__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "devlib\\manlibInst.h"

const double CENTERFRE[14] = {
                2412e6,     // channel 1
                2417e6,     // channel 2
                2422e6,     // channel 3
                2427e6,     // channel 4
                2432e6,     // channel 5
                2437e6,     // channel 6
                2442e6,     // channel 7
                2447e6,     // channel 8
                2452e6,     // channel 9
                2457e6,     // channel 10
                2462e6,     // channel 11
                2467e6,     // channel 12
                2472e6,     // channel 13
                2484e6      // channel 14
            };  // Hz

class GPIBDevice  
{
public:
	GPIBDevice();
	virtual ~GPIBDevice();

     bool Setup();
     bool IsOpen() { return m_isOpen; }
     double MeasChannelPower(int nChannel, char cMode);
     double MeasSpectralMask(int nChannel, char cMode);
     void SetAttPlus(double attPlus) {m_dAttPlus = attPlus;}

protected:
    long   m_devSA;
    bool   m_isOpen;
    double m_dAttPlus;
};

#endif // !defined(AFX_GPIBDEVICE_H__A13CCAF0_1DBB_44BA_B15F_46E4DB279586__INCLUDED_)
