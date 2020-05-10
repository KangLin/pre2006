// AddInsInput.h : main header file for the AddInsInput DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols

// CAddInsInputApp
// See AddInsInput.cpp for the implementation of this class
//

class CAddInsInputApp : public CWinApp
{
public:
	CAddInsInputApp();
	
// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
public:
	virtual int ExitInstance();
};

#ifdef __cplusplus
extern "C"
{
#endif // ½áÊø #ifdef __cplusplus

void __stdcall Show();
BOOL __stdcall Init(EnvDTE::_DTE * pDTE);
void __stdcall Free();
BOOL __stdcall SetDTE(EnvDTE::_DTE * pDTE);

#ifdef __cplusplus
}
#endif // ½áÊø #ifdef __cplusplus

