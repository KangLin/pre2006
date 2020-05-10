/*******************************************************************************************************
文件名：中国象棋.h
功  能：
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-12-31
时  间：20:18:23

FileName：中国象棋.h
Compiler：Visual C++ 6.0
Author：  KangLin
          Copyright 2004 KangLin
Date：    2004-12-31
Time：    20:18:23
*******************************************************************************************************/
// 中国象棋.h : main header file for the 中国象棋 application
//

#if !defined(AFX__H__A2F59016_48AA_467E_B554_FA5742AF8123__INCLUDED_)
#define AFX__H__A2F59016_48AA_467E_B554_FA5742AF8123__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CChessApp:
// See 中国象棋.cpp for the implementation of this class
//

class CChessApp : public CWinApp
{
public:
	CChessApp();

	CMultiDocTemplate* m_ChessDocTemp;
	CMultiDocTemplate* m_DeskDocTemp;

	CString m_gszImageDir; //头像文件的目录,在CChessApp::CChessApp()中设置
    CString m_gszUserName; //用户名,在CLogonDlg::Receive(CCommand* pCmd)中设置

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChessApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CChessApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX__H__A2F59016_48AA_467E_B554_FA5742AF8123__INCLUDED_)
