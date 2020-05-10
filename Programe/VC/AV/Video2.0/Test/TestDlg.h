// TestDlg.h : header file
//

#if !defined(AFX_TESTDLG_H__2526EED0_0853_4C70_9AF0_E3ACF0743361__INCLUDED_)
#define AFX_TESTDLG_H__2526EED0_0853_4C70_9AF0_E3ACF0743361__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\playvideownd.h"
/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog

class CTestDlg : public CDialog
{
// Construction
public:
	CTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDlg)
	enum { IDD = IDD_TEST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnStartcapture();
	afx_msg void OnStopcapture();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	CPlayVideoWnd* m_PlayVideoWnd;
	CDisplayWnd* m_DisplayWnd;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLG_H__2526EED0_0853_4C70_9AF0_E3ACF0743361__INCLUDED_)
