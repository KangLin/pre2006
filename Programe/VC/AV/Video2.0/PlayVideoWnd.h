/*******************************************************************************************************
�ļ�����PlayVideoWnd.h
��  �ܣ�
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����2.0.0.1
��  �ڣ�2004-11-17
ʱ  �䣺13:54:30

��  ����1.0.0.1
��  �ڣ�2004-11-3
ʱ  �䣺17:10:01
*******************************************************************************************************/
#if !defined(_PLAYVIDEOWND_H)
#define _PLAYVIDEOWND_H

#include "..\compress\compress.h"
#include "VideoCapture.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _PLAYVIDEOWND
#define _PLAYVIDEOWND
#endif

/*******************************************************************************************************
CDisplayWnd window
*******************************************************************************************************/

class CDisplayWnd : public CWnd
{
// Construction
public:
	CDisplayWnd();

// Attributes
public:

protected:
	int m_wndWidth;	    	//���ڿͻ������
	int m_wndHeight;		//���ڿͻ����߶�
	HDRAWDIB m_hdib;
	BITMAPINFO m_bmpInfo;
	HDC m_hdc;

	CCompressor m_Compressor; //ѹ����
	BYTE* m_pOut;           //ѹ�����ݵĻ�����
	DWORD m_dwOutSize;      //ѹ�����ݵĴ�С
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayWnd)
	public:
	virtual BOOL Create(const RECT& rect, CWnd* pParentWnd, DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_DLGFRAME, UINT nID = NULL, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual void Display(LPVOID pData, DWORD iSize);
	virtual ~CDisplayWnd();

	// Generated message map functions
	//{{AFX_MSG(CDisplayWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/*******************************************************************************************************
CPlayVideoWnd window
*******************************************************************************************************/

class CPlayVideoWnd : public CDisplayWnd 
{
// Construction
public:
	CPlayVideoWnd();
	virtual ~CPlayVideoWnd();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPlayVideoWnd)
	public:
	virtual BOOL Create(const RECT& rect, CWnd* pParentWnd, DWORD dwStyle = WS_CHILD | WS_VISIBLE | WS_DLGFRAME, UINT nID = NULL, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL StartCapture();
	BOOL StopCapture();
	
	void Display(LPVOID pData, DWORD iSize);	

//���ݳ�Ա
private:
	CVideoCapture* m_VideoCapture; //��Ƶ������

	// Generated message map functions
protected:
	//{{AFX_MSG(CPlayVideoWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//�ⲿ��������Ƶ����
//extern "C" DWORD WINAPI OnVideoData(LPVOID lpData, DWORD dwSize);
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_PLAYVIDEOWND_H)
