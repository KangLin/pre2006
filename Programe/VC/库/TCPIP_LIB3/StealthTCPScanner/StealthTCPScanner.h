// StealthTCPScanner.h : main header file for the STEALTHTCPSCANNER application
//

#if !defined(AFX_STEALTHTCPSCANNER_H__83B7C7ED_1CFA_4419_A383_CD3C4CB017AB__INCLUDED_)
#define AFX_STEALTHTCPSCANNER_H__83B7C7ED_1CFA_4419_A383_CD3C4CB017AB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CStealthTCPScannerApp:
// See StealthTCPScanner.cpp for the implementation of this class
//

class CStealthTCPScannerApp : public CWinApp
{
public:
	CStealthTCPScannerApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStealthTCPScannerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CStealthTCPScannerApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STEALTHTCPSCANNER_H__83B7C7ED_1CFA_4419_A383_CD3C4CB017AB__INCLUDED_)
