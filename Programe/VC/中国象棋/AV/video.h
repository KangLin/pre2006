/*******************************************************************************************************
�ļ�����video.h
��  �ܣ������Ƶ����Ƶ�ķ��͡����ա�
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-12-18
ʱ  �䣺19:39:48

FileName��video.h
Function��
Compiler��Visual C++ 6.0
Author��  KangLin
          Copyright 2004 KangLin
Date��    2004-12-18
Time��    19:39:48
*******************************************************************************************************/
//{{AFX_INCLUDES()
#include "displayvideo.h"
#include "ctrvideo.h"
#include "..\..\��\Control\buttonst\winxpbuttonst.h"
//}}AFX_INCLUDES
#if !defined(AFX_VIDEO_H__FBC3CF8F_3722_4D12_9A35_4ED3D216C8CF__INCLUDED_)
#define AFX_VIDEO_H__FBC3CF8F_3722_4D12_9A35_4ED3D216C8CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// video.h : header file
//
#include "..\..\��\Control\SizeBarControl\scbarg.h"
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

	BOOL VideoConnect(CCommand& cmd);  //������Ƶ����
    BOOL AudioConnect(CCommand& cmd);  //������Ƶ����
	BOOL StartVideo(CCommand& cmd);    //ͬ����Ƶ����
    BOOL StartAudio(CCommand& cmd);    //ͬ����Ƶ����
    BOOL NoVideo(CCommand& cmd);       //��ͬ����Ƶ����
    BOOL NoAudio(CCommand& cmd);       //��ͬ����Ƶ����
	void End();
	
	static DWORD _stdcall VideoReceiveThread(LPVOID lpParameter); //��Ƶ�����߳�
	static DWORD _stdcall AudioReceiveThread(LPVOID lpParameter); //��Ƶ�����߳�

private:
	BOOL Initializtion(BOOL bAgree = FALSE);
    BOOL VideoSendData(LPVOID lpData, UINT iLen); //������Ƶ����
    BOOL VideoSendData(CCommand& cmd);
    BOOL AudioSendData(LPVOID lpData, UINT iLen); //������Ƶ����
    BOOL AudioSendData(CCommand& cmd);
    BOOL SendDataToServer(LPVOID lpData, UINT iLen); //���������������    
    BOOL SendDataToServer(CCommand& cmd);
    
	CUDPSocket m_sckVideo;    //��Ƶ
	CUDPSocket m_sckAudio;    //��Ƶ
	UINT m_uRemoteVideoPort;  //��Ƶ�˿�
	UINT m_uRemoteAudioPort;  //��Ƶ�˿�
	CString m_szRemoteIP;     //Զ��IP
    UINT m_uServerPort;       //�������˿�
    CString m_szServerIP;     //������IP

	BOOL m_StartVideo;        //��Ƶ��ʼ
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
