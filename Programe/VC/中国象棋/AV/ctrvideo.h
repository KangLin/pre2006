#if !defined(AFX_CTRVIDEO_H__8656D95D_1CD3_4C77_AE35_7CD6D0CECD04__INCLUDED_)
#define AFX_CTRVIDEO_H__8656D95D_1CD3_4C77_AE35_7CD6D0CECD04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.

/////////////////////////////////////////////////////////////////////////////
// CVideoCtr wrapper class

class CVideoCtr : public CWnd
{
protected:
	DECLARE_DYNCREATE(CVideoCtr)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0x135c6036, 0x4af4, 0x4c68, { 0xba, 0x2b, 0x3b, 0xb0, 0xc3, 0x1f, 0x33, 0xaa } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName,
		LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect,
		CWnd* pParentWnd, UINT nID,
		CCreateContext* pContext = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID); }

    BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle,
		const RECT& rect, CWnd* pParentWnd, UINT nID,
		CFile* pPersist = NULL, BOOL bStorage = FALSE,
		BSTR bstrLicKey = NULL)
	{ return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey); }

// Attributes
public:

// Operations
public:
	BOOL StartCapture();
	BOOL StopCapture();
	void AboutBox();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CTRVIDEO_H__8656D95D_1CD3_4C77_AE35_7CD6D0CECD04__INCLUDED_)
