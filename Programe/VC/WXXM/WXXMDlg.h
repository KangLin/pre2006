// WXXMDlg.h : header file
//

#if !defined(AFX_WXXMDLG_H__2467C856_593B_4D9B_A53B_5B64BBBF9E4F__INCLUDED_)
#define AFX_WXXMDLG_H__2467C856_593B_4D9B_A53B_5B64BBBF9E4F__INCLUDED_

#include "..\¿â\TRAYICON\TrayIcon.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWXXMDlg dialog

class CWXXMDlg : public CDialog
{
	DECLARE_DYNAMIC(CWXXMDlg)
// Construction
public:
	CWXXMDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWXXMDlg)
	enum { IDD = IDD_WXXM_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWXXMDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWXXMDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnAbout();
	afx_msg void OnExit();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnOpen();
	afx_msg void OnKeyprompt();
	afx_msg void OnUpdateKeyprompt(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL StopKeyPrompt();
	BOOL StartKeyPrompt();
	HMODULE m_hKeyPromptDll;
	BOOL m_bRun;
	virtual LRESULT OnTrayNotifiy(WPARAM wID, LPARAM lEvent);
	CTrayIcon* m_pTrayIcon;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WXXMDLG_H__2467C856_593B_4D9B_A53B_5B64BBBF9E4F__INCLUDED_)
