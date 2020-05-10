// Device.h: interface for the CDevice class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVICE_H__6D368151_2E4E_405C_B199_C9A52865C0BA__INCLUDED_)
#define AFX_DEVICE_H__6D368151_2E4E_405C_B199_C9A52865C0BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CDevice  
{
public:
	BOOL DisableDevice(BOOL bStatus);
	CDevice();
	virtual ~CDevice();

};

#endif // !defined(AFX_DEVICE_H__6D368151_2E4E_405C_B199_C9A52865C0BA__INCLUDED_)
