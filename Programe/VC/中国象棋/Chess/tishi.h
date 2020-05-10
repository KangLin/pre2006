/*******************************************************************************************************
文件名：tishi.h
功  能：时间提示
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2005-1-19
时  间：15:21:07

FileName：tishi.h
Compiler：Visual C++ 6.0
Author：  KangLin
          Copyright 2005 KangLin
Date：    2005-1-19
Time：    15:21:07
*******************************************************************************************************/
#if !defined(AFX_TISHI_H__6D419604_AA72_4114_BC7C_D39F960CFD59__INCLUDED_)
#define AFX_TISHI_H__6D419604_AA72_4114_BC7C_D39F960CFD59__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// tishi.h : header file
//

#include "..\..\Controls\CStaticEx\StaticEx.h"

class CChessView;

/////////////////////////////////////////////////////////////////////////////
// CTiShi window

class CTiShi : public CStatic
{
// Construction
public:
	CTiShi();

// Attributes
public:

private:
    CStatic m_Total;        //总共下棋时间
    CStatic m_Game;         //局时
    CStatic m_Step;         //步时
    CStaticEx m_bmp;        //下棋方提示
    CStatic m_Num;          //盘数

    CTime m_tmGame;         //局时
    CTime m_tmTotal;        //共用时
    CTime m_tmStep;         //步时

    UINT m_uWin;            //赢的盘数
    UINT m_uStandOff; //和的盘数
    UINT m_uTotal;           //总盘数    

    CChessView* m_pParent;  //父窗口指针

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTiShi)
	public:
	virtual BOOL Create(CWnd* pParentWnd);
	//}}AFX_VIRTUAL

// Implementation
public:
    void AddWin();
    void AddStandOff();
    void AddTotal();
	void SetStepTime();
	void SetGameTime();
	void SetTotalTime();
	void SetBitmap(UINT uID);
	virtual ~CTiShi();

private:
    void SetNums();

	// Generated message map functions
protected:
	//{{AFX_MSG(CTiShi)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TISHI_H__6D419604_AA72_4114_BC7C_D39F960CFD59__INCLUDED_)
