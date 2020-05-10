// 中国象棋服务器Doc.h : interface of the CChessDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DOC_H__0C6145E8_EB21_4844_95E5_3453656F8D7D__INCLUDED_)
#define AFX_DOC_H__0C6145E8_EB21_4844_95E5_3453656F8D7D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\..\库\database\ado\ado.h"
#include "process\process.h"

class CChessDoc : public CDocument
{
protected: // create from serialization only
	CChessDoc();
	DECLARE_DYNCREATE(CChessDoc)

// Attributes
public:
	CAdoConnection m_AdoConn;
	CAdoRecordSet m_AdoRecSet;

    CUDPSocket m_sckCommand;     //命令

// Operations
public:
    static DWORD _stdcall ReceiveThread(LPVOID lpParameter);
    static DWORD _stdcall OverTimeThread(LPVOID lpParameter);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChessDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	virtual void OnCloseDocument();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChessDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CChessDoc)
	afx_msg void OnUserinfo();
	afx_msg void OnInfo();
	afx_msg void OnChair();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DOC_H__0C6145E8_EB21_4844_95E5_3453656F8D7D__INCLUDED_)
