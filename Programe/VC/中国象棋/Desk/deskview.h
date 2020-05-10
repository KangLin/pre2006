/*******************************************************************************************************
文件名：deskview.h
功  能：完成桌子视图
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-12-17
时  间：16:20:54

FileName：deskview.h
Function：Desk view
Compiler：Visual C++ 6.0
Author：  KangLin
          Copyright 2004 KangLin
Date：    2004-12-17
Time：    16:20:54
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

// 操作
private:
	CBitmap m_BlackBitmap;                //对话框背景图片
    enum{
		 DESKNUMBER_ENUM = g_DESKNUMBER,  //桌子数
		 DESKNUMBER_LINE_ENUM = 6,        //每行桌子数
	};
public:
    CDesk* m_pDesk[DESKNUMBER_ENUM];      //桌子指针
    BOOL SetChair(CCommand * pCmd);       //设置椅子信息
    void SetHand(CCommand& cmd);          //设置举手
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

#ifndef _DEBUG  // debug version in 中国象棋View.cpp
inline CChessDoc* CDeskView::GetDocument()
   { return (CChessDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEW_H__8AC2E728_DD92_4CEE_BC8F_F3AD5DB7508C__INCLUDED_)
