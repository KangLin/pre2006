// CrackPasswordDlg.h : header file
//

#if !defined(AFX_CRACKPASSWORDDLG_H__4437B742_EB78_462E_8607_A354877C550A__INCLUDED_)
#define AFX_CRACKPASSWORDDLG_H__4437B742_EB78_462E_8607_A354877C550A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GetPassword\Cracker.h"
#include "CrackPassword.h"

/////////////////////////////////////////////////////////////////////////////
// CCrackPasswordDlg dialog
class CCrackPasswordDlg : public CDialog
{
// Construction
public:
	CCrackPasswordDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CCrackPasswordDlg)
	enum { IDD = IDD_CRACKPASSWORD_DIALOG };
	CString	m_szPassword;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCrackPasswordDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CCrackPasswordDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonStart();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CGetPassword m_Password;
	CCracker m_Cracker;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CRACKPASSWORDDLG_H__4437B742_EB78_462E_8607_A354877C550A__INCLUDED_)
