#if !defined(AFX_REGISTDLG_H__8B312637_1486_4329_B4E7_76A86F72BDE3__INCLUDED_)
#define AFX_REGISTDLG_H__8B312637_1486_4329_B4E7_76A86F72BDE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RegistDlg.h : header file
//
#include "..\..\Controls\CStaticEx\StaticEx.h"

/////////////////////////////////////////////////////////////////////////////
// CRegistDlg dialog
class CLogonDlg;

class CRegistDlg : public CDialog
{
// Construction
public:
	CRegistDlg(CWnd* pParent = NULL);   // standard constructor

private:
	BOOL DisplayImage(LPCSTR szImageName);

public:
	void Receive(CCommand*pCmd);
// Dialog Data
	//{{AFX_DATA(CRegistDlg)
	enum { IDD = IDD_REGISTDLG_DIALOG };
	CComboBox	m_ctrlImage;
	long	m_uAge;
	CString	m_szPassword;
	CString	m_szPassword2;
	CString	m_szUserName;
	int		m_iImage;
	int		m_iSex;
	//}}AFX_DATA
    CStaticEx m_staticexImage;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRegistDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRegistDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboimage();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGISTDLG_H__8B312637_1486_4329_B4E7_76A86F72BDE3__INCLUDED_)
