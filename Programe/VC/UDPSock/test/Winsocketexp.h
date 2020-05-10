// Winsocketexp.h : main header file for the WINSOCKETEXP application
//

#if !defined(AFX_WINSOCKETEXP_H__645FAFC2_2F4E_4A0E_8631_4EA564F7AB40__INCLUDED_)
#define AFX_WINSOCKETEXP_H__645FAFC2_2F4E_4A0E_8631_4EA564F7AB40__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWinsocketexpApp:
// See Winsocketexp.cpp for the implementation of this class
//

class CWinsocketexpApp : public CWinApp
{
public:
	CWinsocketexpApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinsocketexpApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWinsocketexpApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINSOCKETEXP_H__645FAFC2_2F4E_4A0E_8631_4EA564F7AB40__INCLUDED_)
