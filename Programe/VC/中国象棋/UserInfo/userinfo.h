//{{AFX_INCLUDES()
//}}AFX_INCLUDES
#if !defined(AFX_USERINFO_H__6292E463_0F32_4EBA_83AA_7DCF02CF7E61__INCLUDED_)
#define AFX_USERINFO_H__6292E463_0F32_4EBA_83AA_7DCF02CF7E61__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UserInfo.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CUserInfo dialog

class CUserInfo : public CDialog
{
	DECLARE_DYNCREATE(CUserInfo)
// Construction
public:
	CUserInfo(CWnd* pParent = NULL);   // standard constructor

	BOOL FindUser(LPCSTR lpszUserName);
    void AddUserInfo(CCommand* pCmd);
	BOOL SetListHead(CCommand* pCmd);
	void DeleteUserInfo(CCommand* pCmd);
	CString FindValue(LPCSTR lpszUserName, LPCSTR lpszField);

    CComboBox* m_pUserName;   //文本信息中的用户名列表,
                              //在CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)中设置
    CComboBox* m_pVideoUser;  //视频中的用户列表
// Dialog Data
	//{{AFX_DATA(CUserInfo)
	enum { IDD = IDD_USERINFO };
	//}}AFX_DATA

private:
	CListCtrl	m_UserInfo;
    int m_lstWidth;      //列表的初始宽度
    BOOL m_bSetListHead; //是否设置了表头

    INT HadUser(LPCSTR lpszUserName);
	BOOL DeleteUser(LPCSTR lpszUserName);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUserInfo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CUserInfo)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_USERINFO_H__6292E463_0F32_4EBA_83AA_7DCF02CF7E61__INCLUDED_)
