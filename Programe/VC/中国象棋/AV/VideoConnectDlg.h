#if !defined(AFX_VIDEOCONNECTDLG_H__C87F89FD_CF4F_491D_AD6A_54D0BE690378__INCLUDED_)
#define AFX_VIDEOCONNECTDLG_H__C87F89FD_CF4F_491D_AD6A_54D0BE690378__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VideoConnectDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVideoConnectDlg dialog

class CVideoConnectDlg : public CDialog
{
// Construction
public:
	CVideoConnectDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVideoConnectDlg)
	enum { IDD = IDD_VIDEOCONNECTDLG_DIALOG };
	CEdit	m_ctrUserName;
	CString	m_szUserName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoConnectDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVideoConnectDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOCONNECTDLG_H__C87F89FD_CF4F_491D_AD6A_54D0BE690378__INCLUDED_)
