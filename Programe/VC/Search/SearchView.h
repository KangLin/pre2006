// SearchView.h : interface of the CSearchView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEARCHVIEW_H__B1E28AD1_B5DA_40BC_AC01_811949DA5000__INCLUDED_)
#define AFX_SEARCHVIEW_H__B1E28AD1_B5DA_40BC_AC01_811949DA5000__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CSearchView : public CFormView
{
protected: // create from serialization only
	CSearchView();
	DECLARE_DYNCREATE(CSearchView)

public:
	//{{AFX_DATA(CSearchView)
	enum { IDD = IDD_SEARCH_FORM };
	CEdit	m_ctrPath;
	CEdit	m_ctrFileName;
	CButton	m_ctrBtSearch;
	CButton	m_ctrBtBrowe;
	CListBox m_lstFile;
	CString	m_szFileName;
	CString	m_szPath;
	//}}AFX_DATA

// Attributes
public:
	CSearchDoc* GetDocument();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSearchView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSearchView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSearch();
	afx_msg void OnBrowe();
	afx_msg void OnDblclkFile();
	afx_msg void OnToolFindfile();
	afx_msg void OnToolWord();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
};

CString ShowBrowseFolderDialog(HWND hWnd);
#ifndef _DEBUG  // debug version in SearchView.cpp
inline CSearchDoc* CSearchView::GetDocument()
   { return (CSearchDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHVIEW_H__B1E28AD1_B5DA_40BC_AC01_811949DA5000__INCLUDED_)
