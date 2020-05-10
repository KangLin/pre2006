// GPIBDevice.cpp: implementation of the GPIBDevice class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sis163.h"
#include "GPIBDevice.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GPIBDevice::GPIBDevice()
{
    m_dAttPlus = 0;
}

GPIBDevice::~GPIBDevice()
{

}

bool GPIBDevice::Setup()
{
    // load from file
    int gpibAddr = 7;
    int gpibMode = 0x03;

    m_devSA = spaInit(gpibAddr, gpibMode);
    m_isOpen = m_devSA > 0;
    return m_isOpen;
}

double GPIBDevice::MeasChannelPower(int nChannel, char cMode)
{
    double center = CENTERFRE[nChannel-1];
    return spaMeasChannelPower(m_devSA,
                               center,
                               60e6, 0) + m_dAttPlus;
}

double GPIBDevice::MeasSpectralMask(int nChannel, char cMode)
{
    double value = 0;
    double center = CENTERFRE[nChannel-1];
    if (cMode == 'G')
        value = spaMeasSpectralMask(m_devSA,
                     center, 60e6, 0, 0, 0);
    //else
    //    value = spaMeasSpectralMask11b(m_devSA,
    //                 center, 60e6, 1, 0, 0);
    return value;
}