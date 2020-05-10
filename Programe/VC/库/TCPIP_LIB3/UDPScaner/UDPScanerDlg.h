// UDPScanerDlg.h : header file
//

#if !defined(AFX_UDPSCANERDLG_H__E6A75D2B_6365_4C5A_B89C_E769D758A468__INCLUDED_)
#define AFX_UDPSCANERDLG_H__E6A75D2B_6365_4C5A_B89C_E769D758A468__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CUDPScanerDlg dialog

class CScanSocket;
class CUDPSocket;

#define ICMP_EVENT 100

class CUDPScanerDlg : public CDialog
{
// Construction
public:
	void Report();
	virtual  ~CUDPScanerDlg();
	CUDPScanerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CUDPScanerDlg)
	enum { IDD = IDD_UDPSCANER_DIALOG };
	CListBox	m_UDPList;
	CIPAddressCtrl	m_DestinationIP;
	int		m_EndPort;
	int		m_StartPort;
	int		m_ScanDelay;
	BOOL	m_AutoScroll;
	int		m_Loop;
	CString	m_URL;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUDPScanerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUDPScanerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnQuit();
	afx_msg void OnScan();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL ConvertAddress();
	char m_cDestinationIP[16];
	int m_LoopCount;
	BOOL ICMPScan();
	LPSTR IPCtrlToSTR(CIPAddressCtrl* ctrl);
	CUDPSocket* m_UDP;
	CScanSocket* m_ICMP;
	BOOL Scan();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDPSCANERDLG_H__E6A75D2B_6365_4C5A_B89C_E769D758A468__INCLUDED_)
