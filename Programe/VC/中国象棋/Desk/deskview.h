/*******************************************************************************************************
�ļ�����deskview.h
��  �ܣ����������ͼ
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-12-17
ʱ  �䣺16:20:54

FileName��deskview.h
Function��Desk view
Compiler��Visual C++ 6.0
Author��  KangLin
          Copyright 2004 KangLin
Date��    2004-12-17
Time��    16:20:54
*******************************************************************************************************/

#if !defined(AFX_VIEW_H__8AC2E728_DD92_4CEE_BC8F_F3AD5DB7508C__INCLUDED_)
#define AFX_VIEW_H__8AC2E728_DD92_4CEE_BC8F_F3AD5DB7508C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "desk.h"

class CDeskView : public CScrollView
{
protected: // create from serialization only
	CDeskView();
	DECLARE_DYNCREATE(CDeskView)

// Attributes
public:
	CChessDoc* GetDocument();

// ����
private:
	CBitmap m_BlackBitmap;                //�Ի��򱳾�ͼƬ
    enum{
		 DESKNUMBER_ENUM = g_DESKNUMBER,  //������
		 DESKNUMBER_LINE_ENUM = 6,        //ÿ��������
	};
public:
    CDesk* m_pDesk[DESKNUMBER_ENUM];      //����ָ��
    BOOL SetChair(CCommand * pCmd);       //����������Ϣ
    void SetHand(CCommand& cmd);          //���þ���
    void StopHand(CCommand& cmd);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDeskView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDeskView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CDeskView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in �й�����View.cpp
inline CChessDoc* CDeskView::GetDocument()
   { return (CChessDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEW_H__8AC2E728_DD92_4CEE_BC8F_F3AD5DB7508C__INCLUDED_)
