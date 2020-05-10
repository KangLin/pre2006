// CrackPassword.h : main header file for the CRACKPASSWORD application
//

#if !defined(AFX_CRACKPASSWORD_H__938F06CD_6260_4D66_A317_03F081F039FF__INCLUDED_)
#define AFX_CRACKPASSWORD_H__938F06CD_6260_4D66_A317_03F081F039FF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCrackPasswordApp:
// See CrackPassword.cpp for the implementation of this class
//

class CCrackPasswordApp : public CWinApp
{
public:
	CCrackPasswordApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCrackPasswordApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CCrackPasswordApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRACKPASSWORD_H__938F06CD_6260_4D66_A317_03F081F039FF__INCLUDED_)
