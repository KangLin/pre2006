#if !defined(AFX_VIDEOCTRL_H__42F9EBDB_B855_4121_8CB7_A62AFA8FD220__INCLUDED_)
#define AFX_VIDEOCTRL_H__42F9EBDB_B855_4121_8CB7_A62AFA8FD220__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// VideoCtrl.h : main header file for VIDEOCTRL.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CVideoCtrlApp : See VideoCtrl.cpp for implementation.

class CVideoCtrlApp : public COleControlModule
{
public:
	BOOL InitInstance();
	int ExitInstance();
};

extern const GUID CDECL _tlid;
extern const WORD _wVerMajor;
extern const WORD _wVerMinor;

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOCTRL_H__42F9EBDB_B855_4121_8CB7_A62AFA8FD220__INCLUDED)
