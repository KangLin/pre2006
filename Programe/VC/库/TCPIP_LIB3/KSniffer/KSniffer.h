// KSniffer.h : main header file for the KSNIFFER application
//

#if !defined(AFX_KSNIFFER_H__713525CD_8877_412E_90E1_506B822FC970__INCLUDED_)
#define AFX_KSNIFFER_H__713525CD_8877_412E_90E1_506B822FC970__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CKSnifferApp:
// See KSniffer.cpp for the implementation of this class
//

class CKSnifferApp : public CWinApp
{
public:
	CKSnifferApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKSnifferApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CKSnifferApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KSNIFFER_H__713525CD_8877_412E_90E1_506B822FC970__INCLUDED_)
