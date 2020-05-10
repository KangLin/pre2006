// SpeechPromptDlg.h : header file
//

#if !defined(AFX_SPEECHPROMPTDLG_H__07BF70D1_8DD4_432C_B83F_D0519A325723__INCLUDED_)
#define AFX_SPEECHPROMPTDLG_H__07BF70D1_8DD4_432C_B83F_D0519A325723__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CSpeechPromptDlg dialog

class CSpeechPromptDlg : public CDialog
{
// Construction
public:
	CSpeechPromptDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CSpeechPromptDlg)
	enum { IDD = IDD_SPEECHPROMPT_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpeechPromptDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CSpeechPromptDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtoninstallhook();
	afx_msg void OnButtonuninstallhook();
	afx_msg void OnDestroy();
	afx_msg void OnButton1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	HMODULE m_hDll;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPEECHPROMPTDLG_H__07BF70D1_8DD4_432C_B83F_D0519A325723__INCLUDED_)
