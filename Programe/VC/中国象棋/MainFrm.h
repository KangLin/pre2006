/*******************************************************************************************************
�ļ�����MainFrm.h
��  �ܣ�
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-12-18
ʱ  �䣺19:40:30

FileName��MainFrm.h
Compiler��Visual C++ 6.0
Author��  KangLin
          Copyright 2004 KangLin
Date��    2004-12-18
Time��    19:40:30
*******************************************************************************************************/

#if !defined(AFX_MAINFRM_H__63CB1839_3D1B_4E1D_B381_31BCE5257E45__INCLUDED_)
#define AFX_MAINFRM_H__63CB1839_3D1B_4E1D_B381_31BCE5257E45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "�й�����Doc.h"
#include "chess\�й�����view.h"
#include "desk\deskview.h"

#include "..\��\Control\ToolBar\ToolBarEx\toolbarex.h"
#include "..\��\Control\CoolTabContrl\CoolTabCtrl.h"
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
	CLogonDlg* m_pLogon;        //��¼�Ի���ָ��

	CString m_szServerIP;       //������IP
	UINT m_uServerPort;         //������port
	CUDPSocket m_sckCommand;    //����

    CView* GetView(CRuntimeClass* pViewClass); //�õ�ָ����ͼ��ָ��
	BOOL Exit();                //�˳�

public:
	enum {DESK_ENUM, CHESS_ENUM};
	
	int m_iView;                //��ǰ��ʾ����ͼ
    CChessView* m_pChessView;   //������ͼ,��CChessView::OnCreate������
    CDeskView* m_pDeskView;     //������ͼ,��CDeskView::OnCreate������

	CCoolBar m_ControlBar;
	CCoolTabCtrl m_TabCtrl;
	CUserInfo m_UserInfo;       //�û���Ϣ
	CVideo m_Video;             //��Ƶ����Ƶ
    CTextMessage m_TextMessage; //�ı�

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
	
	static DWORD _stdcall ReceiveThread(LPVOID lpParameter);     //�����߳�
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
	//�������� ---��  ��--- ɾ���� 2004-12-16 : 13:50:29
	//

	CToolBar    m_wndToolBar;

	//
	//�������� ---��  ��--- ɾ���� 2004-12-16 : 13:50:29
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
