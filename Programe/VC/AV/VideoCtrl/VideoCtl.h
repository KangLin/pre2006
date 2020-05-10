/*******************************************************************************************************
文件名：VideoCtl.h
功  能：捕获视频并显示
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-11-17
时  间：22:20:09
*******************************************************************************************************/
#if !defined(AFX_VIDEOCTL_H__F3B466EC_AC8D_489A_9D3F_7C2DBE174A3E__INCLUDED_)
#define AFX_VIDEOCTL_H__F3B466EC_AC8D_489A_9D3F_7C2DBE174A3E__INCLUDED_

#include "..\compress\compress.h"
#include "..\video2.0\VideoCapture.h"

#ifdef _PLAYVIDEOWND
#undef _PLAYVIDEOWND
#endif

#define  _PLAYVIDEOCTROL

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// VideoCtl.h : Declaration of the CVideoCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CVideoCtrl : See VideoCtl.cpp for implementation.

class CVideoCtrl : public COleControl
{
	DECLARE_DYNCREATE(CVideoCtrl)

// Constructor
public:
	CVideoCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CVideoCtrl();

	DECLARE_OLECREATE_EX(CVideoCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CVideoCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CVideoCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CVideoCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CVideoCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CVideoCtrl)
	afx_msg BOOL StartCapture();
	afx_msg BOOL StopCapture();
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CVideoCtrl)
	void FireDisplayVideo(BSTR FAR* lpData, long dwSize)
		{FireEvent(eventidDisplayVideo,EVENT_PARAM(VTS_PBSTR  VTS_I4), lpData, dwSize);}
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	void Display(LPVOID lpData, DWORD dwSize);
	enum {
	//{{AFX_DISP_ID(CVideoCtrl)
	dispidStartCapture = 1L,
	dispidStopCapture = 2L,
	eventidDisplayVideo = 1L,
	//}}AFX_DISP_ID
	};

private:
	int m_wndWidth;	    	//窗口客户区宽度
	int m_wndHeight;		//窗口客户区高度
	HDRAWDIB m_hdib;
	BITMAPINFO m_bmpInfo;
	HDC m_hdc;
	BOOL m_bCapturing;     //为TRUE:正在捕获视频

	CCompressor m_Compressor; //压缩器
	BYTE* m_pOut;           //压缩数据的缓存区
	DWORD m_dwOutSize;      //压缩数据的大小
	CVideoCapture* m_VideoCapture; //视频捕获类
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOCTL_H__F3B466EC_AC8D_489A_9D3F_7C2DBE174A3E__INCLUDED)
