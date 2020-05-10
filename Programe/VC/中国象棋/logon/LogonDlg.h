#if !defined(AFX_LOGONDLG_H__044A1B18_FDD5_4A43_B6CC_E783D656A446__INCLUDED_)
#define AFX_LOGONDLG_H__044A1B18_FDD5_4A43_B6CC_E783D656A446__INCLUDED_

#include "registdlg.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogonDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogonDlg dialog
class CMainFrame;

class CLogonDlg : public CDialog
{
// Construction
public:
    CMainFrame* m_pParent;   //父窗口指针

	void RegistReceive(CCommand* pCmd);
    void Receive(CCommand* pCmd);
   
    CLogonDlg(CWnd* pParent = NULL);   // standard constructor
    
// Dialog Data
    //{{AFX_DATA(CLogonDlg)
    enum { IDD = IDD_LOGONDLG_DIALOG };
    CEdit    m_ctrValidate;
    CString    m_szPassword;
    UINT    m_uPort;
    CString    m_szUserName;
    UINT    m_uValidate;
    UINT    m_uValidateCode;
    CString    m_szRemoteIP;
    //}}AFX_DATA


// Overrides
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CLogonDlg)
    protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
    //}}AFX_VIRTUAL

// Implementation
protected:

    // Generated message map functions
    //{{AFX_MSG(CLogonDlg)
    virtual BOOL OnInitDialog();
    afx_msg void OnRegist();
    virtual void OnOK();
    //}}AFX_MSG
    DECLARE_MESSAGE_MAP()
private:
    UINT Rand();
    CRegistDlg* m_pRegist; //注册对话框指针
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGONDLG_H__044A1B18_FDD5_4A43_B6CC_E783D656A446__INCLUDED_)
