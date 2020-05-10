// NetManageView.h : main header file for the NetManageView application
//
#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols
#include "..\..\System\Communicate\ManageSocket.h"

// CNetManageViewApp:
// See NetManageView.cpp for the implementation of this class
//

class CNetManageViewApp : public CWinApp,
							public CBCGPWorkspace
{
public:
	CNetManageViewApp();
	virtual ~CNetManageViewApp();

	// Override from CBCGPWorkspace
	virtual void PreLoadState ();


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()

public:
	CManageSocket* m_pMagSocket;
};

extern CNetManageViewApp theApp;