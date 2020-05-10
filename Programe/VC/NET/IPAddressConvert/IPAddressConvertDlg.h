// IPAddressConvertDlg.h : header file
//

#if !defined(AFX_IPADDRESSCONVERTDLG_H__47B11BE1_E753_4146_A470_5CC3D4AA02FB__INCLUDED_)
#define AFX_IPADDRESSCONVERTDLG_H__47B11BE1_E753_4146_A470_5CC3D4AA02FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CIPAddressConvertDlg dialog

class CIPAddressConvertDlg : public CDialog
{
// Construction
public:
	CIPAddressConvertDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CIPAddressConvertDlg)
	enum { IDD = IDD_IPADDRESSCONVERT_DIALOG };
	CString	m_szIP;
	DWORD	m_dwIP;
	CString	m_szHexIP;
	int		m_nSelect;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIPAddressConvertDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CIPAddressConvertDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int IPFormString();
	int IPFromDWORD();
	int IPFormHex();
	int IPDWORDToString();
	DWORD HexStrToDWORD(char * str, int nSize);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IPADDRESSCONVERTDLG_H__47B11BE1_E753_4146_A470_5CC3D4AA02FB__INCLUDED_)
