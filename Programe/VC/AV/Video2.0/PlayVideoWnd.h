/*******************************************************************************************************
文件名：PlayVideoWnd.h
功  能：
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：2.0.0.1
日  期：2004-11-17
时  间：13:54:30

版  本：1.0.0.1
日  期：2004-11-3
时  间：17:10:01
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
	int m_wndWidth;	    	//窗口客户区宽度
	int m_wndHeight;		//窗口客户区高度
	HDRAWDIB m_hdib;
	BITMAPINFO m_bmpInfo;
	HDC m_hdc;

	CCompressor m_Compressor; //压缩器
	BYTE* m_pOut;           //压缩数据的缓存区
	DWORD m_dwOutSize;      //压缩数据的大小
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

//数据成员
private:
	CVideoCapture* m_VideoCapture; //视频捕获类

	// Generated message map functions
protected:
	//{{AFX_MSG(CPlayVideoWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//外部程序处理视频数据
//extern "C" DWORD WINAPI OnVideoData(LPVOID lpData, DWORD dwSize);
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_PLAYVIDEOWND_H)
