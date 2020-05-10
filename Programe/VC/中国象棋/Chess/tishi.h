/*******************************************************************************************************
�ļ�����tishi.h
��  �ܣ�ʱ����ʾ
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2005-1-19
ʱ  �䣺15:21:07

FileName��tishi.h
Compiler��Visual C++ 6.0
Author��  KangLin
          Copyright 2005 KangLin
Date��    2005-1-19
Time��    15:21:07
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
    CStatic m_Total;        //�ܹ�����ʱ��
    CStatic m_Game;         //��ʱ
    CStatic m_Step;         //��ʱ
    CStaticEx m_bmp;        //���巽��ʾ
    CStatic m_Num;          //����

    CTime m_tmGame;         //��ʱ
    CTime m_tmTotal;        //����ʱ
    CTime m_tmStep;         //��ʱ

    UINT m_uWin;            //Ӯ������
    UINT m_uStandOff; //�͵�����
    UINT m_uTotal;           //������    

    CChessView* m_pParent;  //������ָ��

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
