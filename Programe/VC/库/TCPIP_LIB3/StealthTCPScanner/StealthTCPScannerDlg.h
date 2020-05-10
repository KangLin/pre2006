// StealthTCPScannerDlg.h : header file
//

#if !defined(AFX_STEALTHTCPSCANNERDLG_H__9B2D0C57_D681_4D6D_A1DE_67C3B14295F7__INCLUDED_)
#define AFX_STEALTHTCPSCANNERDLG_H__9B2D0C57_D681_4D6D_A1DE_67C3B14295F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ClientSocket.h"

/////////////////////////////////////////////////////////////////////////////
// CStealthTCPScannerDlg dialog

class CStealthTCPScannerDlg : public CDialog
{
// Construction
public:
	CStealthTCPScannerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CStealthTCPScannerDlg)
	enum { IDD = IDD_STEALTHTCPSCANNER_DIALOG };
	CListBox	m_TCPList;
	CIPAddressCtrl	m_DestinationIP;
	CListBox	m_InterfaceList;
	CString	m_URL;
	long	m_ScanDelay;
	long	m_EndPort;
	long	m_Loop;
	BOOL	m_AutoScroll;
	long	m_StartPort;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStealthTCPScannerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CStealthTCPScannerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnScan();
	afx_msg void OnQuit();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL CreateSocket();
	//Convert from the control to a string
	LPSTR IPCtrlToSTR(CIPAddressCtrl* ctrl);

	//Convert address (DNS)
	BOOL ConvertAddress();

	//Stealth scan
	BOOL Scan();

	//Build the interface list
	BOOL BuildInterfaceList();

	//Our socket to scan with
	CClientSocket* m_Socket;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STEALTHTCPSCANNERDLG_H__9B2D0C57_D681_4D6D_A1DE_67C3B14295F7__INCLUDED_)
