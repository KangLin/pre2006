/*******************************************************************************************************
�ļ�����desk.h
��  �ܣ�ʵ�����ӡ�����
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2005-1-2
ʱ  �䣺11:16:31

FileName��desk.h
Function��
Compiler��Visual C++ 6.0
Author��  KangLin
          Copyright 2005 KangLin
Date��    2005-1-2
Time��    11:16:31
*******************************************************************************************************/
#if !defined(AFX_DESK_H__CA5E8786_B91F_4E15_9C06_792B3FC2C732__INCLUDED_)
#define AFX_DESK_H__CA5E8786_B91F_4E15_9C06_792B3FC2C732__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// desk.h : header file
//

#include "..\..\��\Control\buttonst\winxpbuttonst.h"
#include "..\..\Controls\CStaticEx\StaticEx.h"

/////////////////////////////////////////////////////////////////////////////
// ������

class CChair : public CStaticEx
{
	DECLARE_DYNCREATE(CChair)
// Construction
public:
	CChair();

// Attributes
private:
    int m_iChairNo;       //���Ӻ�
    CString m_szUserName; //�û���

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChair)
	//}}AFX_VIRTUAL

// Implementation
public:
    BOOL SetChairNo(int No);
	BOOL SetChairInfo(LPCSTR lpszUserName, UINT uResID);
	BOOL SetChairInfo(LPCSTR lpszUserName, HICON hIcon);
	BOOL SetChairInfo(LPCSTR lpszUserName, LPCSTR lpszImageFile);

	virtual ~CChair();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChair)
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnChairUserinfo();
    afx_msg void OnChairSendmessage();
};


/////////////////////////////////////////////////////////////////////////////
// ������

class CDesk : public CWnd
{
	DECLARE_DYNCREATE(CDesk)
// Construction
public:
	CDesk();

// Attributes
public:
    enum{
		DESK_WIDTH_ENUM = 168, //���ӿ��
		DESK_HEIGHT_ENUM = 84, //���Ӹ߶�
	};
private:
    //����
    CChair m_LeftChair;
	CChair m_RightChair;
    CStaticEx m_Desk;       //����
    CStaticEx m_LeftHand;   //��߾���
    CStaticEx m_RightHand;  //�ұ߾���
	int m_DeskNo;           //���Ӻ�

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDesk)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetDeskNumber(int iDeskNum);
	BOOL SetDeskText(LPCSTR lpszText = NULL);
	BOOL SetRightUser(LPCSTR lpszUserName = NULL, HICON hIcon = NULL);
	BOOL SetLeftUser(LPCSTR lpszUserName = NULL, HICON hIcon = NULL);
	BOOL SetLeftUser(LPCSTR lpszUserName, CString szFile = "");
    BOOL SetRightUser(LPCSTR lpszUserName, CString szFile = "");
    //����
    BOOL SetLeftHand(HICON hIcon = NULL);
    BOOL SetRightHand(HICON hIcon = NULL);

	virtual int Create(int x, int y, CWnd* pParentWnd, int nID = NULL);
	virtual ~CDesk();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDesk)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DESK_H__CA5E8786_B91F_4E15_9C06_792B3FC2C732__INCLUDED_)
