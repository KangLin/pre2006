#if !defined(AFX_DISPLAYVIDEO_H__E6489EF8_1D9A_4B0D_9EF7_E131B43863CB__INCLUDED_)
#define AFX_DISPLAYVIDEO_H__E6489EF8_1D9A_4B0D_9EF7_E131B43863CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// DisplayVideo.h : main header file for DISPLAYVIDEO.DLL

#if !defined( __AFXCTL_H__ )
	#error include 'afxctl.h' before including this file
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CDisplayVideoApp : See DisplayVideo.cpp for implementation.

class CDisplayVideoApp : public COleControlModule
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

#endif // !defined(AFX_DISPLAYVIDEO_H__E6489EF8_1D9A_4B0D_9EF7_E131B43863CB__INCLUDED)
