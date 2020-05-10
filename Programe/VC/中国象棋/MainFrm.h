/*******************************************************************************************************
文件名：MainFrm.h
功  能：
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-12-18
时  间：19:40:30

FileName：MainFrm.h
Compiler：Visual C++ 6.0
Author：  KangLin
          Copyright 2004 KangLin
Date：    2004-12-18
Time：    19:40:30
*******************************************************************************************************/

#if !defined(AFX_MAINFRM_H__63CB1839_3D1B_4E1D_B381_31BCE5257E45__INCLUDED_)
#define AFX_MAINFRM_H__63CB1839_3D1B_4E1D_B381_31BCE5257E45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "中国象棋Doc.h"
#include "chess\中国象棋view.h"
#include "desk\deskview.h"

#include "..\库\Control\ToolBar\ToolBarEx\toolbarex.h"
#include "..\库\Control\CoolTabContrl\CoolTabCtrl.h"
#include "TextMessage\textmessage.h"
#include "av\video.h"
#include "userinfo\userinfo.h"
#include "LOGON\logonDLG.h"

class CMainFrame : public CMDIFrameWnd
{
	DECLARE_DYNAMIC(CMainFrame)
public:
	CMainFrame();

// Attributes
private:	
	CLogonDlg* m_pLogon;        //登录对话框指针

	CString m_szServerIP;       //服务器IP
	UINT m_uServerPort;         //服务器port
	CUDPSocket m_sckCommand;    //命令

    CView* GetView(CRuntimeClass* pViewClass); //得到指定视图的指针
	BOOL Exit();                //退出

public:
	enum {DESK_ENUM, CHESS_ENUM};
	
	int m_iView;                //当前显示的视图
    CChessView* m_pChessView;   //象棋视图,在CChessView::OnCreate中设置
    CDeskView* m_pDeskView;     //桌子视图,在CDeskView::OnCreate中设置

	CCoolBar m_ControlBar;
	CCoolTabCtrl m_TabCtrl;
	CUserInfo m_UserInfo;       //用户信息
	CVideo m_Video;             //视频、音频
    CTextMessage m_TextMessage; //文本

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL ActiveOrCreateChess();
	BOOL GetServerAddress(CString* szServerIP, UINT* uServerPort);
	BOOL SendData(CCommand* pcmd);
	BOOL CreateOrActive(CDocTemplate* pTemplate,
		                CRuntimeClass* pViewClass);
	
	static DWORD _stdcall ReceiveThread(LPVOID lpParameter);     //接收线程
	BOOL SendData(LPVOID lpData, UINT iLen);
	void SetServerAddress(CString szServerIP, UINT uServerPort);
	
	virtual ~CMainFrame();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
    CToolBarEx m_ToolBar;

	/*------------------------------------------------------------------------
	//以下是由 ---康  林--- 删除于 2004-12-16 : 13:50:29
	//

	CToolBar    m_wndToolBar;

	//
	//以上是由 ---康  林--- 删除于 2004-12-16 : 13:50:29
	//------------------------------------------------------------------------*/

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnChess();
	afx_msg void OnDesk();
	afx_msg void OnUpdateChess(CCmdUI* pCmdUI);
	afx_msg void OnTextmessage();
	afx_msg void OnUpdateTextmessage(CCmdUI* pCmdUI);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnUpdateDesk(CCmdUI* pCmdUI);
	afx_msg void OnFileLogon();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__63CB1839_3D1B_4E1D_B381_31BCE5257E45__INCLUDED_)
