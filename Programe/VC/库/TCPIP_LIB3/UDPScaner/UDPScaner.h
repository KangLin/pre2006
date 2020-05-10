// UDPScaner.h : main header file for the UDPSCANER application
//

#if !defined(AFX_UDPSCANER_H__911FCA64_896C_4A27_ACB1_74C909419CD6__INCLUDED_)
#define AFX_UDPSCANER_H__911FCA64_896C_4A27_ACB1_74C909419CD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUDPScanerApp:
// See UDPScaner.cpp for the implementation of this class
//

class CUDPScanerApp : public CWinApp
{
public:
	CUDPScanerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUDPScanerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUDPScanerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDPSCANER_H__911FCA64_896C_4A27_ACB1_74C909419CD6__INCLUDED_)
