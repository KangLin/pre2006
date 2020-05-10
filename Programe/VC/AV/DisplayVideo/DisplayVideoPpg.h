#if !defined(AFX_DISPLAYVIDEOPPG_H__6077F3CB_F8C4_4383_BBC0_FB76D2006BFE__INCLUDED_)
#define AFX_DISPLAYVIDEOPPG_H__6077F3CB_F8C4_4383_BBC0_FB76D2006BFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// DisplayVideoPpg.h : Declaration of the CDisplayVideoPropPage property page class.

////////////////////////////////////////////////////////////////////////////
// CDisplayVideoPropPage : See DisplayVideoPpg.cpp.cpp for implementation.

class CDisplayVideoPropPage : public COlePropertyPage
{
	DECLARE_DYNCREATE(CDisplayVideoPropPage)
	DECLARE_OLECREATE_EX(CDisplayVideoPropPage)

// Constructor
public:
	CDisplayVideoPropPage();

// Dialog Data
	//{{AFX_DATA(CDisplayVideoPropPage)
	enum { IDD = IDD_PROPPAGE_DISPLAYVIDEO };
		// NOTE - ClassWizard will add data members here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DATA

// Implementation
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Message maps
protected:
	//{{AFX_MSG(CDisplayVideoPropPage)
	afx_msg void OnButtonabout();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISPLAYVIDEOPPG_H__6077F3CB_F8C4_4383_BBC0_FB76D2006BFE__INCLUDED)
