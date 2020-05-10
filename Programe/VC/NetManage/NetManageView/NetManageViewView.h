// NetManageViewView.h : interface of the CNetManageViewView class
//


#pragma once


class CNetManageViewView : public CBCGPTabView
{
protected: // create from serialization only
	CNetManageViewView();
	DECLARE_DYNCREATE(CNetManageViewView)

// Attributes
public:
	CNetManageViewDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CNetManageViewView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);

};

#ifndef _DEBUG  // debug version in NetManageViewView.cpp
inline CNetManageViewDoc* CNetManageViewView::GetDocument() const
   { return reinterpret_cast<CNetManageViewDoc*>(m_pDocument); }
#endif

