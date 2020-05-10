#if !defined(AFX_VIDEOPPG_H__79F71532_52EC_4A60_A9C0_A69A5E2C6865__INCLUDED_)
#define AFX_VIDEOPPG_H__79F71532_52EC_4A60_A9C0_A69A5E2C6865__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// VideoPpg.h : Declaration of the CVideoPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CVideoPropPage : See VideoPpg.cpp.cpp for implementation.

class CVideoPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CVideoPropPage)
	DECLARE_OLECREATE_EX(CVideoPropPage)

// Constructor
public:
	CVideoPropPage();

// Dialog Data
	//{{AFX_DATA(CVideoPropPage)
	enum { IDD = IDD_PROPPAGE_VIDEO };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CVideoPropPage)
	afx_msg void OnButtonabout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOPPG_H__79F71532_52EC_4A60_A9C0_A69A5E2C6865__INCLUDED)
