/*******************************************************************************************************
版权所有 (C) 2006 ；保留所有权利。
文件名：CommandWnd.h
描  述：完成命令控制台的操作
版  本：2.0.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2006年11月10日
时  间：17:05:38
编译器：Microsoft Visual Studio 8.0 —— C/C++ 8.0
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
		LPCTSTR pszCmd;        // 要执行的命令
		CCommandWnd * pWnd;
		HANDLE hEvent;         //事件
		HANDLE * phPipeRead;   //读管道
		HANDLE * phPipeWrite;  //写管道
		BOOL ** ppExit;        //程序是否退出
	};
	enum
	{
		PREVIEWCOMMANDNOOVER = 0x100, //上一个命令没有执行完
	};

private:
	int m_nCurRow;        //光标当前行
	int m_nCurCol;        //光标当前列
	CPoint m_ptCaretPos;  //插入点的位置
	CPoint m_ptOrigin;    //光标当前行原点
	CSize m_LogicSize;    //逻辑尺寸
	CFont m_Font, *m_pOldFont;

	CString m_szPrompt;   //提示符
	CString m_szInput;    //当前输入字符串

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
