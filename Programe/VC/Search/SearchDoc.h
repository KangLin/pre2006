// SearchDoc.h : interface of the CSearchDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_SEARCHDOC_H__21067BAA_9C1B_4C63_9051_1012A5DBC42E__INCLUDED_)
#define AFX_SEARCHDOC_H__21067BAA_9C1B_4C63_9051_1012A5DBC42E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CSearchDoc : public CDocument
{
protected: // create from serialization only
	CSearchDoc();
	DECLARE_DYNCREATE(CSearchDoc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSearchDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSearchDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CSearchDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SEARCHDOC_H__21067BAA_9C1B_4C63_9051_1012A5DBC42E__INCLUDED_)