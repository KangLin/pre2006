/*******************************************************************************************************
文件名：playVideoWnd.h
功  能：显示视频窗口头文件
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-11-3
时  间：17:10:01
*******************************************************************************************************/
#if !defined(_PLAYVIDEOWND_H)
#define _PLAYVIDEOWND_H

#include "VideoCapture.h"
#include "..\compress\compress.h"
#include <afxmt.h>

#ifdef _CCHESS
#include "d:\Programe\VC\中国象棋\DSocket.h"        //数据报
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

//数据成员
private:
	BOOL m_bOnlyPlay;         //只显示视频数据，不捕获视频
	CVideoCapture* m_VideoCapture;
	int m_wndWidth;	    	//窗口客户区宽度
	int m_wndHeight;		//窗口客户区高度
	HDRAWDIB m_hdib;
	BITMAPINFO m_bmpInfo;
	HDC m_hdc;

	CCompressor m_Compressor; //压缩器
	BYTE* m_pOut;           //压缩数据的缓存区
	DWORD m_dwOutSize;      //压缩数据的大小


    //------------------------------------------------------------------------
	//以下是完成 ===中国象棋中的定义=== 功能的语句块
	//

#ifdef _CCHESS
public:
	CDSocket m_DSocket;     //数据报
	BOOL bConnect;          //已连接
	UINT m_uLocatPort;       //本地端口
	UINT m_uRemotePort;      //远程主机端口
	CString m_szRemoteName;  //远程主机名

public:
	BOOL CreateDSocket(CString szRemoteName, UINT uPort = 7791, UINT uRemotePort = 7791);

#endif

	//
	//以上是完成 ===中国象棋中的定义=== 功能的语句块
	//------------------------------------------------------------------------

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

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_PLAYVIDEOWND_H)
