// Input.h : main header file for the Input DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CInputApp
// See Input.cpp for the implementation of this class
//

class CInputApp : public CWinApp
{
public:
	CInputApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
