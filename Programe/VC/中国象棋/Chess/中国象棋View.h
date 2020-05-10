/*******************************************************************************************************
文件名：中国象棋View.h
功  能：
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2005-1-3
时  间：16:00:45

FileName：中国象棋View.h
Compiler：Visual C++ 6.0
Author：  KangLin
          Copyright 2005 KangLin
Date：    2005-1-3
Time：    16:00:45
*******************************************************************************************************/
// 中国象棋View.h : interface of the CChessView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_VIEW_H__9A73A0F5_9162_4BCF_943F_63952FF47B8F__INCLUDED_)
#define AFX_VIEW_H__9A73A0F5_9162_4BCF_943F_63952FF47B8F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include < mmsystem.h > 

#pragma comment(lib, "winmm")

//{{AFX_INCLUDES()
#include "tishi.h"
#include "..\XQ\xq.h"
//}}AFX_INCLUDES

class CMainFrame;

class CChessView : public CFormView
{
protected: // create from serialization only
	CChessView();
	DECLARE_DYNCREATE(CChessView)

public:
	//{{AFX_DATA(CChessView)
	enum { IDD = IDD_CHESS_FORM };
	CStatic	m_ctrBlackUserName;
	CStatic	m_ctrRedUserName;
	CXQ		m_ctrXQ;
	//}}AFX_DATA

// Attributes
private:
    BOOL PromptSound(LPCTSTR ID);
	void SetLocateUserName();
    void SetRemoteUserName(LPCSTR szUser);
    void ShowTiShi();
    void SendHand();
    void ReStart();

    //用于工具栏是否可用
    BOOL m_bStandOff;
    BOOL m_bRepent;

	CBitmap m_bmpBK;             //背景图片
    CUDPSocket m_sckChess;       //象棋Sock

    CString m_szRemoteUserName;  //对方用户名
	UINT m_uRemotePort;          //对方象棋Port，在SetRemoteAddress中设置
	CString m_szRemoteIP;        //对方象棋IP
    UINT m_uServerPort;          //服务器Port，在OnCreate中设置
    CString m_szServerIP;        //服务器IP，在OnCreate中设置

    typedef enum{
            NO = 0,
            SETDOWN = 1,         //刚入坐
            SET = 2,             //设置了参数
            START = 4,           //同意开始下棋
            PLAYCHESS = 32       //正在下棋
    } ENUM_STATE;
    ENUM_STATE m_CurState;       //当前状态
    ENUM_STATE m_RemoteState;    //对方状态

    CTiShi m_TiShiRemote;        //对方提示框
    CTiShi m_TiShi;              //本方提示框

public:
    struct Sets
    {
        BOOL bSet;               //设置了参数
        LONG dwStep;             //每步时间，单位：分钟
        UINT uAdd;               //加分值
        UINT uInc;               //减分值
    }m_Sets, m_tmpSets;
    CMainFrame* m_pMainWnd;      //主框架窗口指针,在OnCreate中设置
    CChessApp* m_pChessApp;      //象棋应用程序指针,在OnCreate中设置
    long m_lChairNo;             //当前用户的椅子号

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChessView)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual void OnDraw(CDC* pDC);
	//}}AFX_VIRTUAL

// Implementation
public:
    //处理握手
    void Hand(CCommand& cmd);
    //确定接收设置参数
    void ReceivedPara(CCommand& cmd);
    //悔棋
    void RepentChess();
    //接受悔棋
    void ReceiveRepent(CCommand& cmd);
    //请求和棋
    void StandOff();
    //接受求和
    void ReceivedStandOff(CCommand * pcmd = NULL, BOOL bTiShi = FALSE);
    //认输
    void Giveup();
    void ReceiveGiveup(CCommand& cmd);
    // 走棋
    void WalkChess(CCommand& cmd);
	void Start(CCommand &cmd);
	void OtherExit(CCommand& cmd);
	void OtherSetDown(CCommand& cmd);
    void SetDown(CCommand& cmd);
    void PlayChess(CCommand& cmd);
    //设置对方地址
	BOOL SetRemoteAddress(CString szIP, UINT uPort);
    //向对方发送数据
	BOOL SendData(LPVOID lpData, INT iLen);
	BOOL SendData(CCommand& cmd);
	//向服务器发送数据
	BOOL SendDataToServer(LPVOID lpData, INT iLen);
    BOOL SendDataToServer(CCommand & cmd);
    //超时
    void OverTime(LONG span);
	void Close();
    void Exit();                                               //退出
    void LeaveChair(CCommand & cmd);                           //离开椅子
    static	DWORD _stdcall ReceiveThread(LPVOID lpParameter);  //接收函数
    CChessDoc* GetDocument();
	virtual ~CChessView();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CChessView)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnChessClose();
	afx_msg void OnChessGiveup();
	afx_msg void OnChessRepent();
	afx_msg void OnChessSet();
	afx_msg void OnChessStandoff();
	afx_msg void OnChessStart();
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnUpdateChessGiveup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateChessRepent(CCmdUI* pCmdUI);
	afx_msg void OnUpdateChessSet(CCmdUI* pCmdUI);
	afx_msg void OnUpdateChessStandoff(CCmdUI* pCmdUI);
	afx_msg void OnUpdateChessStart(CCmdUI* pCmdUI);
	afx_msg void OnUpdateChessClose(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
    DECLARE_EVENTSINK_MAP()
    void MoveChessXq(short x, short y, long chess);
};

#ifndef _DEBUG  // debug version in 中国象棋View.cpp
inline CChessDoc* CChessView::GetDocument()
   { return (CChessDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEW_H__9A73A0F5_9162_4BCF_943F_63952FF47B8F__INCLUDED_)
