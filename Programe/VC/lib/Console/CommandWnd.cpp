/*******************************************************************************************************
版权所有 (C) 2006 ；保留所有权利。
文件名：CommandWnd.cpp
描  述：完成命令控制台的操作
用  法：1、本类自己已完成了控制台操作。
        2、如果在程序中要调用本类执行命令。可以调用本类的成员函数 ExecCommand
版  本：2.0.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2006年11月10日
时  间：17:04:59
编译器：Microsoft Visual Studio 8.0 —— C/C++ 8.0
*******************************************************************************************************/
// console\CommandWnd.cpp : implementation file
//

#include "stdafx.h"
#include "CommandWnd.h"

#include <locale.h>

// CCommandWnd

//IMPLEMENT_DYNAMIC(CCommandWnd, CWnd)
IMPLEMENT_DYNCREATE(CCommandWnd, CWnd)

CCommandWnd::CCommandWnd()
{
	m_szPrompt = _T(">");
	m_pbExit = NULL;
	m_hPipeRead = NULL;
	m_hPipeWrite = NULL;
}

CCommandWnd::~CCommandWnd()
{
	if(m_pbExit)
	{
		*m_pbExit = TRUE;
	}// 结束 if(m_pbExit)
	if(m_hPipeRead)
	{
		CloseHandle(m_hPipeRead);
		m_hPipeRead = NULL;
	} // 结束 if(m_hPipeRead)
	if(m_hPipeWrite)
	{
		CloseHandle(m_hPipeWrite);
		m_hPipeWrite = NULL;
	} // 结束 if(m_hPipeWrite)
}

BEGIN_MESSAGE_MAP(CCommandWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_CHAR()
	ON_WM_MOUSEWHEEL()
	ON_WM_LBUTTONUP()
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_WM_CREATE()
	ON_WM_KEYUP()
	ON_WM_KEYDOWN()
	ON_WM_SIZE()
	ON_WM_VSCROLL()
END_MESSAGE_MAP()

// CCommandWnd message handlers
int CCommandWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return - 1;

	Clear();

	return 0;
}

void CCommandWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	SetFocus();
	CWnd::OnLButtonUp(nFlags, point);
}

BOOL CCommandWnd::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	SCROLLINFO si;
	GetScrollInfo(SB_VERT, &si);
	if(zDelta < 0)
	{
		si.nPos += si.nPage;
		if(si.nPos > si.nMax - si.nPage)
		{
			si.nPos = si.nMax - si.nPage;
		}// 结束 if(si.nPos > si.nMax - si.nPage)
	}
	else
	{
		si.nPos -= si.nPage;
		if(si.nPos < 0)
		{
			si.nPos = 0;
		} // 结束 if(si.nPos < 0)
	}// 结束 if(zDelta < 0)
	si.fMask = SIF_POS;
	SetScrollInfo(SB_VERT, &si);
	m_ptOrigin.y = si.nPos;
	Invalidate();

	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

void CCommandWnd::OnSetFocus(CWnd* pOldWnd)
{
	CWnd::OnSetFocus(pOldWnd);

	CClientDC dc(this);
	CSize size = dc.GetTextExtent(m_szPrompt);
	CreateSolidCaret(max(1, ::GetSystemMetrics(SM_CXBORDER)), size.cy);
	SetCaretPosition();
	ShowCaret();
}

void CCommandWnd::OnKillFocus(CWnd* pNewWnd)
{
	CWnd::OnKillFocus(pNewWnd);

	HideCaret();

	::DestroyCaret();
}

void CCommandWnd::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	DWORD dwRecive;
	
	switch(nChar)
	{
	case _T('\r'):
		if(m_hPipeWrite)
		{
			TRACE(_T("Input:%s\n"), m_szInput);
			m_szInput += _T("\n\r");
			//Add(m_szInput);
			WriteFile(m_hPipeWrite, m_szInput, m_szInput.GetLength(), &dwRecive, NULL);
			m_szInput = _T("");
			m_ptCaretPos.x = 0;
		}
		else
		{
			m_ptCaretPos.x = 0;
			ExecCommand(NULL);
		} // 结束 if(m_hPipeWrite)
		break;
	case VK_UP:
		DrawTextOut(m_Doc.GetPrevKey());
		break;
	case VK_DOWN:
		DrawTextOut(m_Doc.GetNextKey());
		break;
	default:
		break;
	} // 结束 switch(nChar)

	CWnd::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CCommandWnd::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch(nChar)
	{
	case _T('\b'):
		if(m_szInput != m_szPrompt)
		{
			CString szTmp = m_szInput;
			szTmp.Delete(m_szInput.GetLength() - 1);
			DrawTextOut(szTmp);
		} // 结束 if(m_szInput != m_szPrompt)
		break;
	default:
		m_szInput.AppendChar(nChar);
		DrawTextOut();
		break;
	}// 结束 switch(nChar)

	CWnd::OnChar(nChar, nRepCnt, nFlags);
}

void CCommandWnd::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CWnd::OnKeyUp(nChar, nRepCnt, nFlags);
}

void CCommandWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	SCROLLINFO si;
	CClientDC dc(this);
	if(cy < m_LogicSize.cy)
	{
		GetScrollInfo(SB_VERT, &si);

		si.fMask = SIF_PAGE;
		si.nPage = cy;

		if(si.nPos > si.nMax - cy)
		{
			SetVScrollBottom();
			si.fMask = 0;
		}// 结束 if(si.nPos > si.nMax - cy)
		
	}
	else //隐藏滚动条
	{
		si.fMask = SIF_ALL;
		si.nPage = 0;
		si.nMax = 0;
		si.nMin = 0;
		si.nPos = 0;

		SetOrigin();
	}// 结束 if(cy < m_LogicSize.cy)
	
	SetScrollInfo(SB_VERT, &si);

}

void CCommandWnd::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	SCROLLINFO si;
	GetScrollInfo(SB_VERT, &si);

	int nDelta = 0;
	CSize size;
	CClientDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	dc.DPtoLP(&rect);
	size = dc.GetTextExtent(m_szInput);

	switch(nSBCode)
	{
	case SB_LINEDOWN:
		nDelta = size.cy;
		break;
	case SB_LINEUP:
		nDelta = -size.cy;
		break;
	case SB_PAGEDOWN:
		nDelta = rect.Height() - size.cy;
		break;
	case SB_PAGEUP:
		nDelta = -(rect.Height() - size.cy);
		break;
	case SB_THUMBPOSITION:
		si.nPos = (int)nPos;
		break;
	case SB_THUMBTRACK:
		si.nPos = (int)nPos;
		break;
	default:
		return;
	} // 结束 switch(nSBCode)
	si.nPos += nDelta;
	if(si.nPos < si.nMin)
	{
		si.nPos = si.nMin; 
	}
	else if(si.nPos > si.nMax - si.nPage)
	{
		si.nPos = si.nMax - si.nPage;
	} // 结束 if(si.nPos < si.nMin)

	si.fMask = SIF_POS;
	SetScrollInfo(SB_VERT, &si);
	m_ptOrigin.y = si.nPos;
	Invalidate();

	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void CCommandWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// Do not call CWnd::OnPaint() for painting messages
	OnPrepareDC(&dc);
	OnDraw(&dc);
}

/*******************************************************************************************************
函数名：OnPrepareDC
描  述：调整DC的座标系
参  数：
        CDC * pDC：
返回值：类型为 int 。成功返回0
版  本：2.0.0.1
作  者：康  林
时  间：2006年11月22日 15:17:45
*******************************************************************************************************/
int CCommandWnd::OnPrepareDC(CDC * pDC)
{
	pDC->SetWindowOrg(m_ptOrigin.x, m_ptOrigin.y);
	return 0;
}

/*******************************************************************************************************
函数名：DrawTextOut
描  述：输出当前字符串文本
参  数：无
返回值：类型为 int 。
版  本：2.0.0.1
作  者：康  林
时  间：2006年11月24日 9:56:47
*******************************************************************************************************/
int CCommandWnd::DrawTextOut()
{
	CClientDC dc(this);
	CSize size;
	CRect rcText(0, 0, 0, 0);
	size = dc.GetTextExtent(m_szInput);
	rcText.top = m_ptCaretPos.y;
	rcText.left = 0;
	rcText.bottom = rcText.top + size.cy;
	rcText.right = rcText.left + size.cx;
	return DrawTextOut(&dc, &rcText);
}

/*******************************************************************************************************
函数名：DrawTextOut
描  述：输出当前字符串文本
参  数：
        CDC * pDC            ：设备上下文。
		CRect * pInvalidation：要清除的区域。
返回值：类型为 int 。成功返回0
版  本：2.0.0.1
作  者：康  林
时  间：2006年11月23日 16:32:46
*******************************************************************************************************/
int CCommandWnd::DrawTextOut(CDC * pDC, CRect * pInvalidation)
{
	int nRet = 0;
	HideCaret();

	CFont * pOldFont = pDC->SelectObject(this->GetParent()->GetFont());

	OnPrepareDC(pDC);

	CSize size;
	nRet = pDC->ExtTextOut(0, m_ptCaretPos.y, ETO_OPAQUE, pInvalidation, m_szInput, NULL);
	if(nRet)
	{
		size = pDC->GetTextExtent(m_szInput);
		m_ptCaretPos.x = size.cx;
		if(!SetVScrollBottom())
		{
			Invalidate();
		} // 结束 if(!SetVScrollBottom())
		SetCaretPosition();
		nRet = 0; 
	}
	else
	{
		nRet = 1;
	}// 结束 if(nRet)

	pDC->SelectObject(pOldFont);

	ShowCaret();
	return nRet;
}

/*******************************************************************************************************
函数名：DrawTextOut
描  述：输出当前字符串文本，并删除原来输入行。
参  数：
        LPCTSTR lpszInput：
返回值：类型为 int 。
版  本：2.0.0.1
作  者：康  林
时  间：2006年11月29日 11:57:36
*******************************************************************************************************/
int CCommandWnd::DrawTextOut(LPCTSTR lpszInput)
{
	CClientDC dc(this);
	CSize size;

	//要删除的区域大小
	CRect rcText(0, 0, 0, 0);
	size = dc.GetTextExtent(m_szInput);
	rcText.top = m_ptCaretPos.y;
	rcText.left = 0;
	rcText.bottom = rcText.top + size.cy;
	rcText.right = rcText.left + size.cx;

	m_szInput = lpszInput;

	return DrawTextOut(&dc, &rcText);
}

/*******************************************************************************************************
函数名：OnDraw
描  述：重画
参  数：
        CDC * pDC：
返回值：类型为 int 。成功返回0
版  本：2.0.0.1
作  者：康  林
时  间：2006年11月22日 15:17:53
*******************************************************************************************************/
int CCommandWnd::OnDraw(CDC * pDC)
{
	CRect rect;
	GetClientRect(&rect);
	rect.InflateRect(1, 1);

	pDC->DPtoLP(&rect);
	CBrush brush(RGB(255, 255, 255));
	CBrush * pOldBrush;
	CPen pen(PS_NULL, 0, RGB(255, 255, 255)), *pOldPen;
	pOldBrush = (CBrush * )pDC->SelectObject(&brush);
	pOldPen = (CPen * )pDC->SelectObject(&pen);
	pDC->Rectangle(rect);
	pDC->SelectObject(pOldBrush);
	pDC->SelectObject(pOldPen);
	CFont * pOldeFont = pDC->SelectObject(this->GetParent()->GetFont());

	int i, nRow = 0;
	CPoint point(0, nRow);
	for(i = 1; i <= m_Doc.GetRowCount(); i++)
	{
		LPCTSTR lpStr = m_Doc.GetRow(i);
		if(lpStr)
		{
			pDC->TextOut(point.x, point.y, lpStr);
			CSize size = pDC->GetTextExtent(lpStr);
			nRow += size.cy;
			point.x = 0;
			point.y = nRow;
		} // 结束 if(lpStr)
	}// 结束 for(i = 1; i <= m_Doc.GetRowCount(); i++)

	pDC->TextOut(point.x, point.y, m_szInput);

	SetCaretPosition();

	pDC->SelectObject(pOldeFont);

	return 0;
}

/*******************************************************************************************************
函数名：SetPrompt
描  述：设置提示符
参  数：
        LPCTSTR lpctPrompt：提示符
返回值：类型为 int 。成功返回0
版  本：2.0.0.1
作  者：康  林
时  间：2006年11月22日 15:07:42
*******************************************************************************************************/
int CCommandWnd::SetPrompt(LPCTSTR lpctPrompt)
{
	m_szPrompt = lpctPrompt;
	return 0;
}

/*******************************************************************************************************
函数名：InitInput
描  述：初始化输入
参  数：无
返回值：类型为 int 。
版  本：2.0.0.1
作  者：康  林
时  间：2006年11月22日 15:32:03
*******************************************************************************************************/
int CCommandWnd::InitInput()
{
	m_szInput = m_szPrompt;
	DrawTextOut();
	return 0;
}

/*******************************************************************************************************
函数名：SetOrigin
描  述：重设置原点。
参  数：
		int x：
		int y：
返回值：类型为 int 。
版  本：2.0.0.1
作  者：康  林
时  间：2006年11月27日 13:53:46
*******************************************************************************************************/
int CCommandWnd::SetOrigin(int x, int y)
{
	m_ptOrigin.x = x;
	m_ptOrigin.y = y;
	return 0;
}

/*******************************************************************************************************
函数名：SetLogicSize
描  述：设置逻辑尺寸大小
参  数：
		int x：宽
		int y：高
返回值：类型为 int 。
版  本：2.0.0.1
作  者：康  林
时  间：2006年11月27日 13:57:44
*******************************************************************************************************/
int CCommandWnd::SetLogicSize(int x, int y)
{
	m_LogicSize.cx = x;
	m_LogicSize.cy = y;
	return 0; 
}

/*******************************************************************************************************
函数名：Add
描  述：把字符串加到文档的内容中，并调整插入点的位置。
参  数：
        LPCTSTR lpszStr：要加入的字符串
返回值：类型为 int 。成功返回 0，否则返回非零。
版  本：2.0.0.1
作  者：康  林
时  间：2006年11月24日 10:10:28
*******************************************************************************************************/
int CCommandWnd::Add(LPCTSTR lpszStr)
{
	ASSERT(lpszStr);
	int nRet = 0;

	CClientDC dc(this);
	CFont * pOldFont = dc.SelectObject(this->GetParent()->GetFont());

	CSize size = dc.GetTextExtent(lpszStr);

	m_ptCaretPos.y += size.cy;
	m_LogicSize.cy += size.cy;

	SetVScrollBottom(lpszStr);

	SetCaretPosition();

	nRet = m_Doc.Add(lpszStr);
	dc.SelectObject(pOldFont);
	Invalidate();
	return nRet;
}

/*******************************************************************************************************
函数名：SetVScrollBottom
描  述：把滚动条滚动到底
参  数：
        LPCTSTR lpszStr：输入的字符串,如果没有,用当前输入行的字符串
返回值：类型为 int 。成功返回0,不需要滚动，返回1
版  本：2.0.0.1
作  者：康  林
时  间：2006年11月27日 11:05:12
*******************************************************************************************************/
int CCommandWnd::SetVScrollBottom(LPCTSTR lpszStr)
{
	CString szCmd;
	if(lpszStr)
	{
		szCmd = lpszStr;
	}
	else
	{
		szCmd = m_szInput;
	}// 结束 if(lpszStr)

	CClientDC dc(this);
	CSize size = dc.GetTextExtent(szCmd);

	CRect rect;
	GetClientRect(&rect);
	dc.DPtoLP(&rect);

	SCROLLINFO si;
	GetScrollInfo(SB_VERT, &si);

	si.fMask = SIF_ALL;
	si.nMin = 0;
	si.nMax = m_ptCaretPos.y + size.cy - 1;
	si.nPage = rect.Height();
	if(si.nPos == si.nMax - si.nPage)
	{
		return 1;
	}// 结束 if(si.nPos == si.nMax - si.nPage)
	si.nPos = si.nMax - si.nPage;
	if(si.nMax > rect.Height())
	{
		SetScrollInfo(SB_VERT, &si);
		m_ptOrigin.y = si.nMax - si.nPage;
		return 0; 
	}
	else
	{
		return 1;
	}// 结束 if(si.nMax > rect.Height())
}

/*******************************************************************************************************
函数名：SetCaretPosition
描  述：设置插入点位置
参  数：无
返回值：类型为 int 。
版  本：2.0.0.1
作  者：康  林
时  间：2006年11月27日 13:28:38
*******************************************************************************************************/
int CCommandWnd::SetCaretPosition()
{
	CPoint point(m_ptCaretPos);
	CClientDC dc(this);
	OnPrepareDC(&dc);
	dc.LPtoDP(&point);
	SetCaretPos(point);
	return 0;
}

/*******************************************************************************************************
函数名：Clear
描  述：清除窗口的内容，就象在命令行中运行 cls 命令。
参  数：无
返回值：类型为 int 。成功返回0
版  本：2.0.0.1
作  者：康  林
时  间：2006年11月23日 14:01:10
*******************************************************************************************************/
int CCommandWnd::Clear()
{
	m_Doc.FreeBuffer();
	m_nCurRow = m_nCurCol = 1;
	m_ptCaretPos.x = m_ptCaretPos.y = 0;
	SetLogicSize(0, 0);
	SetOrigin(0, 0);
	m_hPipeRead = m_hPipeWrite = NULL;

	InitInput();

	CClientDC dc(this);
	CSize size = dc.GetTextExtent(m_szPrompt);
	m_ptCaretPos.x = size.cx;

	SCROLLINFO si;
	si.fMask = SIF_PAGE | SIF_RANGE | SIF_POS;
	si.nPage = 0;
	si.nMin = 0;
	si.nMax = 0;
	si.nPos = 0;
	SetScrollInfo(SB_VERT, &si);
	SetScrollInfo(SB_HORZ, &si);

	Invalidate();
	return 0;
}

/*******************************************************************************************************
函数名：ExecCommand
描  述：执行命令
参  数：
        LPCTSTR lpctCommand：要执行的命令。如果为NULL，则执行命令行输入的命令，否则执行此输入命令。
返回值：类型为 int 。成功返回0，否则返回非零。
版  本：2.0.0.1
作  者：康  林
时  间：2006年11月22日 15:35:13
*******************************************************************************************************/
int CCommandWnd::ExecCommand(LPCTSTR lpctCommand)
{
	if(NULL != m_pbExit)
	{
		TRACE(_T("上个命令没有执行完\n"));
		return PREVIEWCOMMANDNOOVER;
	}// 结束 if(NULL != m_pbExit)

	CString szCmd;
	if(lpctCommand)  //直接给出的命令
	{
		szCmd = lpctCommand;
		InitInput();
		m_szInput += lpctCommand;
	}
	else             //从控制台执行命令
	{
		szCmd = m_szInput.Right(m_szInput.GetLength() - m_szPrompt.GetLength());
	} // 结束 if(lpctCommand)

	if(!_tcsicmp(szCmd.Trim(), _T("cls")))
	{
		Clear();
		return 0;
	}// 结束 if(_tcsicmp(szCmd.Trim(), _T("cls")))

	//把执行的命令存到内容链表中
	Add(m_szInput);
	m_Doc.AddKey(m_szInput); //增加到键盘缓存

	m_szInput = _T("");
	SendMessage(WM_KILLFOCUS, NULL, NULL);

	int nRet = 0;
	HANDLE hEvent = NULL;
	SECURITY_ATTRIBUTES sa;
	memset(&sa, 0, sizeof(SECURITY_ATTRIBUTES));
	sa.nLength              = sizeof(sa);
	sa.bInheritHandle       = TRUE;
	sa.lpSecurityDescriptor = NULL;
	if(CreatePipe(&m_hPipeRead, &m_hPipeWrite, &sa, 0))
	{
		hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
		if(hEvent)
		{
			PARA para;
			para.hEvent       = hEvent;
			para.pWnd         = this;
			para.pszCmd       = szCmd;
			para.phPipeRead   = &m_hPipeRead;
			para.phPipeWrite  = &m_hPipeWrite;
			para.ppExit       = &m_pbExit;

			HANDLE hThread = NULL;
			hThread = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ExeCmdThread, &para, NULL, NULL);
			if(hThread)
			{
				if(WaitForSingleObject(hEvent, INFINITE) == WAIT_OBJECT_0)
				{

				} // 结束 if(WaitForSingleObject(hEvent, INFINITE) == WAIT_OBJECT_0)
				if(hEvent)
				{
					CloseHandle(hEvent);
				}// 结束 if(hEvent)
				CloseHandle(hThread);
				return nRet;
			}
			else
			{
				nRet = 3;
				TRACE(_T("线程建立失败。\n"));
			}// 结束 if(hThread)
		}
		else
		{
			nRet = 4;
			TRACE(_T("建立事件失败。\n"));
		}// 结束 if(hEvent)
	}
	else
	{
		nRet = 5;
		TRACE(_T("建立管道失败。\n"));
	}// 结束 if(CreatePipe(&m_hPipeRead, &m_hPipeWrite, &sa, 0))

	InitInput();

	return nRet;
}

/*******************************************************************************************************
函数名：ExeCmdThread
描  述：执行命令线程
参  数：
        void * Para：传给线程的参数
返回值：类型为 DWORD 。
版  本：2.0.0.1
作  者：康  林
时  间：2006年11月28日 17:03:50
*******************************************************************************************************/
DWORD ExeCmdThread(void * Para)
{
	BOOL bMainExit = FALSE;

	CCommandWnd * pWnd;
	CString szCmd;
	HANDLE hEvent;
	HANDLE * phRead, *phWrite;
	BOOL ** ppExit;
	CCommandWnd::PARA * para = (CCommandWnd::PARA * )Para;
	pWnd = para->pWnd;
	szCmd = para->pszCmd;
	phRead = para->phPipeRead;
	phWrite = para->phPipeWrite;
	hEvent = para->hEvent;
	ppExit = para->ppExit;
	
	*ppExit = &bMainExit;

	SetEvent(hEvent);

	DWORD nRet = 0;
	HANDLE hRead = NULL, hWrite = NULL;
	SECURITY_ATTRIBUTES sa;
	STARTUPINFO StartupInfo;
	PROCESS_INFORMATION ProcessInfo;
	memset(&sa, 0, sizeof(SECURITY_ATTRIBUTES));
	memset(&StartupInfo, 0, sizeof(STARTUPINFO));
	memset(&ProcessInfo, 0, sizeof(ProcessInfo));

	sa.nLength              = sizeof(sa);
	sa.bInheritHandle       = TRUE;
	sa.lpSecurityDescriptor = NULL;
	if(CreatePipe(&hRead, &hWrite, &sa, 0))
	{
		::GetStartupInfo(&StartupInfo);
		StartupInfo.cb           = sizeof(StartupInfo);
		StartupInfo.dwFlags      = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
		StartupInfo.hStdInput    = *phRead;
		StartupInfo.hStdOutput   = hWrite;
		StartupInfo.hStdError    = hWrite;
		StartupInfo.wShowWindow = SW_HIDE;
		//执行命令
		BOOL bRet;
		bRet = ::CreateProcess(NULL, (LPTSTR)(LPCTSTR)szCmd, &sa, &sa, TRUE, NULL, NULL, NULL, &StartupInfo, &ProcessInfo);
		//成功
		if(bRet)
		{
			CloseHandle(hWrite);
			hWrite = NULL;
			CloseHandle(*phRead);
			*phRead = NULL;

			DWORD dwRead   = 0;
			DWORD dwTotal  = 0;
			BOOL bExit     = FALSE;

			//执行结果输出，并存到内容链表中
			while(PeekNamedPipe(hRead, NULL, 0, &dwRead, &dwTotal, NULL) || !bExit)
			{
				if(bMainExit)
				{
					TRACE(_T("%s(%d):程序退出\n"), __FILE__, __LINE__);
					nRet = 0xFFFFFFFF;
					break;
				} // 结束 if(bMainExit)
				if(dwTotal > 0)
				{
					TCHAR * pBuf = NULL;
					dwRead = dwTotal + sizeof(TCHAR);
					pBuf = new TCHAR[dwRead];
					if(NULL == pBuf)
					{
						break;
					} // 结束 if(NULL == pBuf)
					if(ReadFile(hRead, pBuf, dwTotal, &dwRead, NULL))
					{
						pBuf[dwRead] = _T('\0');
						TCHAR * p = _tcstok(pBuf, _T("\n\r"));
						while(p)
						{

							_tsetlocale(LC_ALL, _T(".OCP"));

							TRACE(_T("%s\n"), p);
							pWnd->Add(p);
							p = _tcstok(NULL, _T("\n\r"));
						}// 结束 while(p)
					} // 结束 if(ReadFile(hRead, pBuf, dwTotal, &dwRead, NULL))
					delete []pBuf;
					pWnd->SendMessage(WM_SETFOCUS, NULL, NULL);
					pWnd->SendMessage(WM_ACTIVATE, WA_ACTIVE, NULL);
				} // 结束 if(dwTotal > 0)
				if(WAIT_OBJECT_0 == WaitForSingleObject(ProcessInfo.hProcess, 0))
				{
					TRACE(_T("%s(%d):程序退出\n"), __FILE__, __LINE__);
					bExit = TRUE;
				} // 结束 if(WAIT_OBJECT_0 == WaitForSingleObject(ProcessInfo.hProcess, 0))
			}// 结束 while(PeekNamedPipe(hRead, NULL, 0, &dwRead, &dwTotal, NULL) || !bExit)
		}
		else //失败
		{
			TRACE(_T("进程建立失败。\n"));
			pWnd->Add(_T("命令错误。"));
			nRet = 2;
		}// 结束 if(bRet)
	}
	else
	{
		TRACE(_T("管道建立失败。\n"));
		nRet = 1;
	}// 结束 if(CreatePipe(&hRead, &hWrite, &sa, 0))

	if(hRead)
	{
		CloseHandle(hRead);
		hRead = NULL;
	} // 结束 if(hRead)
	if(hWrite)
	{
		CloseHandle(hWrite);
		hWrite = NULL;
	}// 结束 if(hWrite)

	if(ProcessInfo.hProcess)
	{
		CloseHandle(ProcessInfo.hProcess);
		ProcessInfo.hProcess = NULL;
	} // 结束 if(ProcessInfo.hProcess)

	if(nRet != 0xFFFFFFFF)
	{
		if(*phRead)
		{
			CloseHandle(*phRead);
			*phRead = NULL;
		}// 结束 (*phRead)
		if(*phWrite)
		{
			CloseHandle(*phWrite);
			*phWrite = NULL;
		} // 结束 if(*phWrite)

		//下一个命令行
		pWnd->InitInput();

		pWnd->SendMessage(WM_SETFOCUS, NULL, NULL);
		pWnd->SendMessage(WM_ACTIVATE, WA_ACTIVE, NULL);
		*ppExit = NULL;
	} // 结束 if(nRet != 0xFFFFFFFF)
	TRACE(_T("%s(%d):程序退出\n"), __FILE__, __LINE__);
	return nRet;
}