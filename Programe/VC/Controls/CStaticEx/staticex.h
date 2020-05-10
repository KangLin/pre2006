/*******************************************************************************************************
文件名：staticex.h
功  能：显示缩放位图
        ToolTip功能
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-12-31
时  间：19:57:05

FileName：staticex.h
Function：
Compiler：Visual C++ 6.0
Author：  KangLin
          Copyright 2004 KangLin
Date：    2004-12-31
Time：    19:57:05
*******************************************************************************************************/
#if !defined(AFX_STATICEX_H__9E4FF47F_CA9B_43EE_A210_19A85512CFAC__INCLUDED_)
#define AFX_STATICEX_H__9E4FF47F_CA9B_43EE_A210_19A85512CFAC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// staticex.h : header file
//

#include <afxctl.h>

/////////////////////////////////////////////////////////////////////////////
// CStaticEx window

class CStaticEx : public CWnd
{
	DECLARE_DYNCREATE(CStaticEx)
// Construction
public:
	CStaticEx();

// Attributes
public:
	CIPicture m_BKPicture;           //背景图片对象
private:
	bool GetCBitmapFromPictureHolder(CIPicture *ph, CBitmap *pb);
	
	COLORREF m_TransparenceColor;    //透明色
	BOOL m_bTransparence;            //背景是否透明


	//------------------------------------------------------------------------
	//以下是完成 === ToolTip === 功能的语句块
	//

	CToolTipCtrl m_ToolTip;
	void InitToolTip();
public:
	BOOL SetToolTipText(int nText, BOOL bActivate = TRUE);
	BOOL SetToolTipText(LPCSTR lpszText, BOOL bActivate = TRUE);

	//
	//以上是完成 === ToolTip === 功能的语句块
	//------------------------------------------------------------------------


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CStaticEx)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void OnDraw(CDC *pDC);
	//}}AFX_VIRTUAL

// Implementation
public:

	BOOL SetTransparence(COLORREF nColor = RGB(255, 255, 255), BOOL bTransparence = TRUE);

	BOOL SetBitmap(UINT nID);
	BOOL SetBitmap(HBITMAP hBitmap);
	BOOL SetBitmap(CBitmap* Bitmap);
	virtual ~CStaticEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CStaticEx)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STATICEX_H__9E4FF47F_CA9B_43EE_A210_19A85512CFAC__INCLUDED_)
