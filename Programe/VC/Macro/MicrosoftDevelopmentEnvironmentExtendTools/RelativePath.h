#if !defined(AFX_RELATIVEPATH_H__DE4793EE_51BF_448A_83FC_04821341D2FC__INCLUDED_)
#define AFX_RELATIVEPATH_H__DE4793EE_51BF_448A_83FC_04821341D2FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RelativePath.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRelativePath dialog

class CRelativePath : public CDialog
{
// Construction
public:
	CRelativePath(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CRelativePath)
	enum { IDD = IDD_DIALOG_GETRELATIVEPATH };
	// 源文件
    CString m_szSource;
	// 目的文件
    CString m_szDestination;
    // 相对路径
    CString m_szRelative;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRelativePath)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
    
    //是否复制到剪切板中
    BOOL m_bClipboard;

	bool GetRelativePath(void);

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CRelativePath)
	afx_msg void OnButtonBrower();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonBrower2();
	afx_msg void OnChangeEditDestionation();
	afx_msg void OnChangeEditDirfile();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RELATIVEPATH_H__DE4793EE_51BF_448A_83FC_04821341D2FC__INCLUDED_)
