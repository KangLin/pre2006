// AttackerDlg.h : header file
//

#if !defined(AFX_ATTACKERDLG_H__8456DC89_947E_41AF_9892_DA13C972DBF4__INCLUDED_)
#define AFX_ATTACKERDLG_H__8456DC89_947E_41AF_9892_DA13C972DBF4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CAttackerDlg dialog

#define ATTACK_SYN 0
#define ATTACK_ECHO 1
#define ATTACK_UDP 2

#define ERROR_INVALID_SOURCE "Invalid source IP address"
#define ERROR_INVALID_DESTINATION "Invalid destination IP address"

class CSpoofSocket;

class CAttackerDlg : public CDialog
{
// Construction
public:
	CAttackerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CAttackerDlg)
	enum { IDD = IDD_ATTACKER_DIALOG };
	CIPAddressCtrl	m_SourceIP;
	CIPAddressCtrl	m_DestinationIP;
	int		m_Packets;
	short	m_SourcePort;
	short	m_DestinationPort;
	int		m_AttackType;
	BOOL	m_TcpOptions;
	BOOL	m_IPOptions;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAttackerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void DisplaySocketError(CSpoofSocket* sock);
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CAttackerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSend();
	afx_msg void OnQuit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetIPOptions(CSpoofSocket* sok);
	void EchoAttack();
	void UDPFlood();
	LPSTR IPCtrlToSTR(CIPAddressCtrl* ctrl);
	void SynFlood();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ATTACKERDLG_H__8456DC89_947E_41AF_9892_DA13C972DBF4__INCLUDED_)
