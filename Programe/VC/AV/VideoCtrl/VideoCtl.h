/*******************************************************************************************************
�ļ�����VideoCtl.h
��  �ܣ�������Ƶ����ʾ
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-11-17
ʱ  �䣺22:20:09
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
	int m_wndWidth;	    	//���ڿͻ������
	int m_wndHeight;		//���ڿͻ����߶�
	HDRAWDIB m_hdib;
	BITMAPINFO m_bmpInfo;
	HDC m_hdc;
	BOOL m_bCapturing;     //ΪTRUE:���ڲ�����Ƶ

	CCompressor m_Compressor; //ѹ����
	BYTE* m_pOut;           //ѹ�����ݵĻ�����
	DWORD m_dwOutSize;      //ѹ�����ݵĴ�С
	CVideoCapture* m_VideoCapture; //��Ƶ������
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOCTL_H__F3B466EC_AC8D_489A_9D3F_7C2DBE174A3E__INCLUDED)
