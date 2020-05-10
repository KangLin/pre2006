/*******************************************************************************************************
文件名：video.h
功  能：完成视频、音频的发送、接收。
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-12-18
时  间：19:39:48

FileName：video.h
Function：
Compiler：Visual C++ 6.0
Author：  KangLin
          Copyright 2004 KangLin
Date：    2004-12-18
Time：    19:39:48
*******************************************************************************************************/
//{{AFX_INCLUDES()
#include "displayvideo.h"
#include "ctrvideo.h"
#include "..\..\库\Control\buttonst\winxpbuttonst.h"
//}}AFX_INCLUDES
#if !defined(AFX_VIDEO_H__FBC3CF8F_3722_4D12_9A35_4ED3D216C8CF__INCLUDED_)
#define AFX_VIDEO_H__FBC3CF8F_3722_4D12_9A35_4ED3D216C8CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// video.h : header file
//
#include "..\..\库\Control\SizeBarControl\scbarg.h"
#include "..\command\command.h"
#include "afxwin.h"

/////////////////////////////////////////////////////////////////////////////
// CVideo dialog

class CVideo : public CDialog
{
	DECLARE_DYNCREATE(CVideo)
// Construction
public:	
	~CVideo();
	BOOL GetHostName();

	CVideo(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CVideo)
	enum { IDD = IDD_VIDEO };
	CDisplayVideo	m_ctrlDisplayVideo;
	//}}AFX_DATA

	BOOL VideoConnect(CCommand& cmd);  //请求视频连接
    BOOL AudioConnect(CCommand& cmd);  //请求音频连接
	BOOL StartVideo(CCommand& cmd);    //同意视频连接
    BOOL StartAudio(CCommand& cmd);    //同意音频连接
    BOOL NoVideo(CCommand& cmd);       //不同意视频连接
    BOOL NoAudio(CCommand& cmd);       //不同意音频连接
	void End();
	
	static DWORD _stdcall VideoReceiveThread(LPVOID lpParameter); //视频接收线程
	static DWORD _stdcall AudioReceiveThread(LPVOID lpParameter); //音频接收线程

private:
	BOOL Initializtion(BOOL bAgree = FALSE);
    BOOL VideoSendData(LPVOID lpData, UINT iLen); //发送视频数据
    BOOL VideoSendData(CCommand& cmd);
    BOOL AudioSendData(LPVOID lpData, UINT iLen); //发送音频数据
    BOOL AudioSendData(CCommand& cmd);
    BOOL SendDataToServer(LPVOID lpData, UINT iLen); //向服务器发送数据    
    BOOL SendDataToServer(CCommand& cmd);
    
	CUDPSocket m_sckVideo;    //视频
	CUDPSocket m_sckAudio;    //音频
	UINT m_uRemoteVideoPort;  //视频端口
	UINT m_uRemoteAudioPort;  //音频端口
	CString m_szRemoteIP;     //远端IP
    UINT m_uServerPort;       //服务器端口
    CString m_szServerIP;     //服务器IP

	BOOL m_StartVideo;        //视频开始
    CVideoCtr m_ctrlVideo;

	CWinXPButtonST m_butVideo;
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideo)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CVideo)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnVideoClick();
	afx_msg void OnDisplayVideo(BSTR FAR* lpData, long dwSize);
	DECLARE_EVENTSINK_MAP()
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
    CComboBox m_cmbUser;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEO_H__FBC3CF8F_3722_4D12_9A35_4ED3D216C8CF__INCLUDED_)
