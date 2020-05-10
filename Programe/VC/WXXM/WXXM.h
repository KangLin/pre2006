// WXXM.h : main header file for the WXXM application
//

#if !defined(AFX_WXXM_H__E7F10646_CBDC_4D61_9F92_1AB90B6CB1E7__INCLUDED_)
#define AFX_WXXM_H__E7F10646_CBDC_4D61_9F92_1AB90B6CB1E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWXXMApp:
// See WXXM.cpp for the implementation of this class
//

class CWXXMApp : public CWinApp
{
	DECLARE_DYNAMIC(CWXXMApp)
public:
	CWXXMApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWXXMApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CWXXMApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WXXM_H__E7F10646_CBDC_4D61_9F92_1AB90B6CB1E7__INCLUDED_)
