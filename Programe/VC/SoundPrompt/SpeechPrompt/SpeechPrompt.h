// SpeechPrompt.h : main header file for the SPEECHPROMPT application
//

#if !defined(AFX_SPEECHPROMPT_H__3DB7CF17_5DB9_4E46_9F81_7A61869A550D__INCLUDED_)
#define AFX_SPEECHPROMPT_H__3DB7CF17_5DB9_4E46_9F81_7A61869A550D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CSpeechPromptApp:
// See SpeechPrompt.cpp for the implementation of this class
//

class CSpeechPromptApp : public CWinApp
{
public:
	CSpeechPromptApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpeechPromptApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CSpeechPromptApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPEECHPROMPT_H__3DB7CF17_5DB9_4E46_9F81_7A61869A550D__INCLUDED_)
