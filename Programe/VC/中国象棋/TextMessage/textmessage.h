/*******************************************************************************************************
�ļ�����textmessage.h
��  �ܣ�ʵ���ı���Ϣ�Ľ��պͷ���
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-12-30
ʱ  �䣺15:31:45

FileName��textmessage.h
Function��
Compiler��Visual C++ 6.0
Author��  KangLin
          Copyright 2004 KangLin
Date��    2004-12-30
Time��    15:31:45
*******************************************************************************************************/
#if !defined(AFX_TEXTMESSAGE_H__1CFE5EE9_AF88_4322_A541_C976032BF222__INCLUDED_)
#define AFX_TEXTMESSAGE_H__1CFE5EE9_AF88_4322_A541_C976032BF222__INCLUDED_

//{{AFX_INCLUDES()
#include "..\richtext\richtext.h"
#include "..\..\��\Control\buttonst\winxpbuttonst.h"
#include "..\..\��\Control\ToolBar\ToolBarEx\toolbarex.h"
//}}AFX_INCLUDES

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CTextMessage dialog

class CTextMessage : public CDialog
{
	DECLARE_DYNCREATE(CTextMessage)
// Construction
public:
	BOOL SetReceiveText(LPCSTR lpszText);
	CTextMessage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTextMessage)
	enum { IDD = IDD_TEXTMESSAGE };
	CComboBox	m_ctrUserName;
	CRichText	m_reReceive;
	CRichText	m_reSend;
	CString	m_szUserName;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTextMessage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTextMessage)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSendClick();
	afx_msg void OnKeyUpRichtextsend(short FAR* KeyCode, short Shift);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CWinXPButtonST m_btSend;

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTMESSAGE_H__1CFE5EE9_AF88_4322_A541_C976032BF222__INCLUDED_)
