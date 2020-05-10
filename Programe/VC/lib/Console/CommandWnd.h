/*******************************************************************************************************
��Ȩ���� (C) 2006 ����������Ȩ����
�ļ�����CommandWnd.h
��  ��������������̨�Ĳ���
��  ����2.0.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2006��11��10��
ʱ  �䣺17:05:38
��������Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*******************************************************************************************************/
#pragma once

#include "Doc.h"

// CCommandWnd

class CCommandWnd : public CWnd
{
	//DECLARE_DYNAMIC(CCommandWnd)
	DECLARE_DYNCREATE(CCommandWnd)

public:
	CCommandWnd();
	virtual ~CCommandWnd();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	virtual int OnDraw(CDC * pDC);
	virtual int OnPrepareDC(CDC * pDC);

private:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd * pOldWnd);
	afx_msg void OnKillFocus(CWnd * pNewWnd);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar * pScrollBar);

public:
	int SetPrompt(LPCTSTR lpctPrompt);
	int ExecCommand(LPCTSTR lpctCommand = NULL);
	int Clear();
	int InitInput();
	int Add(LPCTSTR lpszStr);

	struct PARA
	{
		LPCTSTR pszCmd;        // Ҫִ�е�����
		CCommandWnd * pWnd;
		HANDLE hEvent;         //�¼�
		HANDLE * phPipeRead;   //���ܵ�
		HANDLE * phPipeWrite;  //д�ܵ�
		BOOL ** ppExit;        //�����Ƿ��˳�
	};
	enum
	{
		PREVIEWCOMMANDNOOVER = 0x100, //��һ������û��ִ����
	};

private:
	int m_nCurRow;        //��굱ǰ��
	int m_nCurCol;        //��굱ǰ��
	CPoint m_ptCaretPos;  //������λ��
	CPoint m_ptOrigin;    //��굱ǰ��ԭ��
	CSize m_LogicSize;    //�߼��ߴ�
	CFont m_Font, *m_pOldFont;

	CString m_szPrompt;   //��ʾ��
	CString m_szInput;    //��ǰ�����ַ���

	CDoc m_Doc;

	HANDLE m_hPipeRead, m_hPipeWrite;
	BOOL * m_pbExit;

	int DrawTextOut();
	int DrawTextOut(LPCTSTR lpszInput);
	int DrawTextOut(CDC * pDC, CRect * pInvalidation = NULL);	

	int SetVScrollBottom(LPCTSTR lpszStr = NULL);
	int SetCaretPosition();

	int SetOrigin(int x = 0, int y = 0);
	int SetLogicSize(int x,int y);
	
};

DWORD ExeCmdThread(void * Para);
