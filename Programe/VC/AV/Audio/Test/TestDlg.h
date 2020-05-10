// TestDlg.h : header file
//

#if !defined(AFX_TESTDLG_H__06EAF9B3_D47C_46C0_8509_A5BE23C744C0__INCLUDED_)
#define AFX_TESTDLG_H__06EAF9B3_D47C_46C0_8509_A5BE23C744C0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <afxmt.h>

/////////////////////////////////////////////////////////////////////////////
// CTestDlg dialog
#include "..\wave.h"
#include "..\Mixer.h"

class CTestDlg : public CDialog
{
// Construction
public:
	CTestDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CTestDlg)
	enum { IDD = IDD_TEST_DIALOG };
	CEdit	m_Destination;
	CListBox	m_ListControl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTestDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	CWaveIn m_WaveIn;
	CWaveOut m_WaveOut;

public:
	~CTestDlg();
	char* m_pData;
	long m_lDataLen;
	CMutex m_Mutex;
	// Generated message map functions
	//{{AFX_MSG(CTestDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnStartrecor();
	afx_msg void OnStoprecord();
	afx_msg void OnStartplay();
	afx_msg void OnPause();
	afx_msg void OnClosedev();
	afx_msg void OnCloserecorddev();
	afx_msg void OnButton1();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTDLG_H__06EAF9B3_D47C_46C0_8509_A5BE23C744C0__INCLUDED_)
