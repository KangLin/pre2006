// dll.h : main header file for the dll DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CdllApp
// See dll.cpp for the implementation of this class
//

class CdllApp : public CWinApp
{
public:
	CdllApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};

void WINAPI show();
