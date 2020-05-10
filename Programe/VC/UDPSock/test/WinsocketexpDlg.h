// WinsocketexpDlg.h : header file
//

#if !defined(AFX_WINSOCKETEXPDLG_H__BBC01B15_1B71_43C6_96B3_C58A949E8995__INCLUDED_)
#define AFX_WINSOCKETEXPDLG_H__BBC01B15_1B71_43C6_96B3_C58A949E8995__INCLUDED_

#include "..\UDPSocket.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CWinsocketexpDlg dialog

class CWinsocketexpDlg : public CDialog
{
// Construction
public:
	CWinsocketexpDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CWinsocketexpDlg)
	enum { IDD = IDD_WINSOCKETEXP_DIALOG };
	CListBox	m_ctrListSend;
	CEdit	m_ctrSend;
	CListBox	m_ctrLstRecive;
	CString	m_szSend;
	CString	m_szLocatIP;
	CString	m_szRemoteIP;
	UINT	m_nRemotePort;
	UINT	m_nLocatePort;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWinsocketexpDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CWinsocketexpDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonsend();
	afx_msg void OnDestroy();
	afx_msg void OnButtonconnect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	CUDPSocket m_udpSocket;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WINSOCKETEXPDLG_H__BBC01B15_1B71_43C6_96B3_C58A949E8995__INCLUDED_)
