// IPAddressConvert.h : main header file for the IPADDRESSCONVERT application
//

#if !defined(AFX_IPADDRESSCONVERT_H__50C1A1AB_22F0_4A86_985B_3B382692B60B__INCLUDED_)
#define AFX_IPADDRESSCONVERT_H__50C1A1AB_22F0_4A86_985B_3B382692B60B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CIPAddressConvertApp:
// See IPAddressConvert.cpp for the implementation of this class
//

class CIPAddressConvertApp : public CWinApp
{
public:
	CIPAddressConvertApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPAddressConvertApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CIPAddressConvertApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPADDRESSCONVERT_H__50C1A1AB_22F0_4A86_985B_3B382692B60B__INCLUDED_)
