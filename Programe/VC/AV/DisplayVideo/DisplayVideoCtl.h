/*******************************************************************************************************
文件名：DisplayVideoCtl.h
功  能：显示压缩的视频数据
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-11-17
时  间：22:29:54
*******************************************************************************************************/
#if !defined(AFX_DISPLAYVIDEOCTL_H__9C5BC4D5_BACD_41FD_B790_FA28FFB49C18__INCLUDED_)
#define AFX_DISPLAYVIDEOCTL_H__9C5BC4D5_BACD_41FD_B790_FA28FFB49C18__INCLUDED_

#include "..\compress\compress.h"
#include "..\video2.0\VideoCapture.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// DisplayVideoCtl.h : Declaration of the CDisplayVideoCtrl ActiveX Control class.

/////////////////////////////////////////////////////////////////////////////
// CDisplayVideoCtrl : See DisplayVideoCtl.cpp for implementation.

class CDisplayVideoCtrl : public COleControl
{
	DECLARE_DYNCREATE(CDisplayVideoCtrl)

// Constructor
public:
	CDisplayVideoCtrl();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDisplayVideoCtrl)
	public:
	virtual void OnDraw(CDC* pdc, const CRect& rcBounds, const CRect& rcInvalid);
	virtual void DoPropExchange(CPropExchange* pPX);
	virtual void OnResetState();
	//}}AFX_VIRTUAL

// Implementation
protected:
	~CDisplayVideoCtrl();

	DECLARE_OLECREATE_EX(CDisplayVideoCtrl)    // Class factory and guid
	DECLARE_OLETYPELIB(CDisplayVideoCtrl)      // GetTypeInfo
	DECLARE_PROPPAGEIDS(CDisplayVideoCtrl)     // Property page IDs
	DECLARE_OLECTLTYPE(CDisplayVideoCtrl)		// Type name and misc status

// Message maps
	//{{AFX_MSG(CDisplayVideoCtrl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

// Dispatch maps
	//{{AFX_DISPATCH(CDisplayVideoCtrl)
	afx_msg void Display(BSTR FAR* lpData, long dwSize);
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()

	afx_msg void AboutBox();

// Event maps
	//{{AFX_EVENT(CDisplayVideoCtrl)
	//}}AFX_EVENT
	DECLARE_EVENT_MAP()

// Dispatch and event IDs
public:
	enum {
	//{{AFX_DISP_ID(CDisplayVideoCtrl)
	dispidDisplay = 1L,
	//}}AFX_DISP_ID
	};
	
private:
	int m_wndWidth;	    	//窗口客户区宽度
	int m_wndHeight;		//窗口客户区高度
	HDRAWDIB m_hdib;
	BITMAPINFO m_bmpInfo;
	HDC m_hdc;
	BOOL m_bDraw;

	CCompressor m_Compressor; //压缩器
	BYTE* m_pOut;           //压缩数据的缓存区
	DWORD m_dwOutSize;      //压缩数据的大小
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISPLAYVIDEOCTL_H__9C5BC4D5_BACD_41FD_B790_FA28FFB49C18__INCLUDED)
