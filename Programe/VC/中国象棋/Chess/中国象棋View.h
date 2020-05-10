/*******************************************************************************************************
�ļ������й�����View.h
��  �ܣ�
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2005-1-3
ʱ  �䣺16:00:45

FileName���й�����View.h
Compiler��Visual C++ 6.0
Author��  KangLin
          Copyright 2005 KangLin
Date��    2005-1-3
Time��    16:00:45
*******************************************************************************************************/
// �й�����View.h : interface of the CChessView class
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

    //���ڹ������Ƿ����
    BOOL m_bStandOff;
    BOOL m_bRepent;

	CBitmap m_bmpBK;             //����ͼƬ
    CUDPSocket m_sckChess;       //����Sock

    CString m_szRemoteUserName;  //�Է��û���
	UINT m_uRemotePort;          //�Է�����Port����SetRemoteAddress������
	CString m_szRemoteIP;        //�Է�����IP
    UINT m_uServerPort;          //������Port����OnCreate������
    CString m_szServerIP;        //������IP����OnCreate������

    typedef enum{
            NO = 0,
            SETDOWN = 1,         //������
            SET = 2,             //�����˲���
            START = 4,           //ͬ�⿪ʼ����
            PLAYCHESS = 32       //��������
    } ENUM_STATE;
    ENUM_STATE m_CurState;       //��ǰ״̬
    ENUM_STATE m_RemoteState;    //�Է�״̬

    CTiShi m_TiShiRemote;        //�Է���ʾ��
    CTiShi m_TiShi;              //������ʾ��

public:
    struct Sets
    {
        BOOL bSet;               //�����˲���
        LONG dwStep;             //ÿ��ʱ�䣬��λ������
        UINT uAdd;               //�ӷ�ֵ
        UINT uInc;               //����ֵ
    }m_Sets, m_tmpSets;
    CMainFrame* m_pMainWnd;      //����ܴ���ָ��,��OnCreate������
    CChessApp* m_pChessApp;      //����Ӧ�ó���ָ��,��OnCreate������
    long m_lChairNo;             //��ǰ�û������Ӻ�

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
    //��������
    void Hand(CCommand& cmd);
    //ȷ���������ò���
    void ReceivedPara(CCommand& cmd);
    //����
    void RepentChess();
    //���ܻ���
    void ReceiveRepent(CCommand& cmd);
    //�������
    void StandOff();
    //�������
    void ReceivedStandOff(CCommand * pcmd = NULL, BOOL bTiShi = FALSE);
    //����
    void Giveup();
    void ReceiveGiveup(CCommand& cmd);
    // ����
    void WalkChess(CCommand& cmd);
	void Start(CCommand &cmd);
	void OtherExit(CCommand& cmd);
	void OtherSetDown(CCommand& cmd);
    void SetDown(CCommand& cmd);
    void PlayChess(CCommand& cmd);
    //���öԷ���ַ
	BOOL SetRemoteAddress(CString szIP, UINT uPort);
    //��Է���������
	BOOL SendData(LPVOID lpData, INT iLen);
	BOOL SendData(CCommand& cmd);
	//���������������
	BOOL SendDataToServer(LPVOID lpData, INT iLen);
    BOOL SendDataToServer(CCommand & cmd);
    //��ʱ
    void OverTime(LONG span);
	void Close();
    void Exit();                                               //�˳�
    void LeaveChair(CCommand & cmd);                           //�뿪����
    static	DWORD _stdcall ReceiveThread(LPVOID lpParameter);  //���պ���
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

#ifndef _DEBUG  // debug version in �й�����View.cpp
inline CChessDoc* CChessView::GetDocument()
   { return (CChessDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEW_H__9A73A0F5_9162_4BCF_943F_63952FF47B8F__INCLUDED_)
