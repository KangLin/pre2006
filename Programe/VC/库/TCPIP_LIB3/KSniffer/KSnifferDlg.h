// KSnifferDlg.h : header file
//

#if !defined(AFX_KSNIFFERDLG_H__3A7823CD_9839_4564_8B17_EE78A2640F8D__INCLUDED_)
#define AFX_KSNIFFERDLG_H__3A7823CD_9839_4564_8B17_EE78A2640F8D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CKSnifferDlg dialog

class CClientSocket;

class CKSnifferDlg : public CDialog
{
// Construction
public:
	CKSnifferDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CKSnifferDlg)
	enum { IDD = IDD_KSNIFFER_DIALOG };
	CListBox	m_DataList;
	CListBox	m_InterfaceList;
	BOOL	m_Sniff;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CKSnifferDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CKSnifferDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	afx_msg void OnSniff();
	afx_msg void OnSniffcheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL BuildInterfaceList();
	CClientSocket* m_Socket;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_KSNIFFERDLG_H__3A7823CD_9839_4564_8B17_EE78A2640F8D__INCLUDED_)
