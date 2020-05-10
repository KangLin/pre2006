//{{AFX_INCLUDES()
#include "richtext.h"
//}}AFX_INCLUDES
#if !defined(AFX_LICENSE_H__1085EC76_51BB_4C47_997D_CF6744391A47__INCLUDED_)
#define AFX_LICENSE_H__1085EC76_51BB_4C47_997D_CF6744391A47__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// License.h : header file
//
#include "resource.h"

/////////////////////////////////////////////////////////////////////////////
// CLicense dialog

class CLicense : public CDialog
{
// Construction
public:
	CLicense(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLicense)
	enum { IDD = IDD_DLG_LICENSE };
	CRichText m_RichText; 
	int		m_bAgree;
	BOOL	m_m_bShow;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLicense)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLicense)
	virtual BOOL OnInitDialog();
	afx_msg void OnRadio1();
	afx_msg void OnRadio2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
		
private:
	HICON m_hIcon;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LICENSE_H__1085EC76_51BB_4C47_997D_CF6744391A47__INCLUDED_)
