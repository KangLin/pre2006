#if !defined(AFX_DDD_H__0F3FE361_06B5_4D1F_9B3E_218A8091159D__INCLUDED_)
#define AFX_DDD_H__0F3FE361_06B5_4D1F_9B3E_218A8091159D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DDD.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDDD dialog

class CDDD : public CDialog
{
// Construction
public:
	CDDD(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDDD)
	enum { IDD = IDD_DDD_DIALOG };
	CButton	m_ok;
	CButton	m_cancel;
	CButton	m_button;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDDD)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDDD)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DDD_H__0F3FE361_06B5_4D1F_9B3E_218A8091159D__INCLUDED_)
