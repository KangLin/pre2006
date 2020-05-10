#pragma once
#include "afxwin.h"


// CProcessModuleDlg dialog

class CProcessModuleDlg : public CDialog
{
	DECLARE_DYNAMIC(CProcessModuleDlg)

public:
	CProcessModuleDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CProcessModuleDlg();

// Dialog Data
	enum { IDD = IDD_PROCESSMODULEDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOk();

private:
	CListBox m_lstProcess;
	CListBox m_lstModule;
	afx_msg void OnLbnDblclkListProcess();
	virtual BOOL OnInitDialog();
};
