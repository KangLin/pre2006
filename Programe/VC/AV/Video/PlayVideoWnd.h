/*******************************************************************************************************
�ļ�����playVideoWnd.h
��  �ܣ���ʾ��Ƶ����ͷ�ļ�
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-11-3
ʱ  �䣺17:10:01
*******************************************************************************************************/
#if !defined(_PLAYVIDEOWND_H)
#define _PLAYVIDEOWND_H

#include "VideoCapture.h"
#include "..\compress\compress.h"
#include <afxmt.h>

#ifdef _CCHESS
#include "d:\Programe\VC\�й�����\DSocket.h"        //���ݱ�
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef _PLAYVIDEOWND
#define _PLAYVIDEOWND
#endif
/////////////////////////////////////////////////////////////////////////////
// CPlayVideoWnd window
class CPlayVideoWnd : public CWnd
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
	BOOL SetOnlyPlay(BOOL bOnlyPlay = TRUE);
	BOOL StartCapture();
	BOOL StopCapture();
	
	void Display(BYTE *pData, DWORD iSize);	

//���ݳ�Ա
private:
	BOOL m_bOnlyPlay;         //ֻ��ʾ��Ƶ���ݣ���������Ƶ
	CVideoCapture* m_VideoCapture;
	int m_wndWidth;	    	//���ڿͻ������
	int m_wndHeight;		//���ڿͻ����߶�
	HDRAWDIB m_hdib;
	BITMAPINFO m_bmpInfo;
	HDC m_hdc;

	CCompressor m_Compressor; //ѹ����
	BYTE* m_pOut;           //ѹ�����ݵĻ�����
	DWORD m_dwOutSize;      //ѹ�����ݵĴ�С


    //------------------------------------------------------------------------
	//��������� ===�й������еĶ���=== ���ܵ�����
	//

#ifdef _CCHESS
public:
	CDSocket m_DSocket;     //���ݱ�
	BOOL bConnect;          //������
	UINT m_uLocatPort;       //���ض˿�
	UINT m_uRemotePort;      //Զ�������˿�
	CString m_szRemoteName;  //Զ��������

public:
	BOOL CreateDSocket(CString szRemoteName, UINT uPort = 7791, UINT uRemotePort = 7791);

#endif

	//
	//��������� ===�й������еĶ���=== ���ܵ�����
	//------------------------------------------------------------------------

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

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_PLAYVIDEOWND_H)
