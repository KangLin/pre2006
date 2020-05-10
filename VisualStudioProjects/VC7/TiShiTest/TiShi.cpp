/*******************************************************************************************************
版权所有 (C) 2006 康林工作室；保留所有权利。
文件名：TiShi.cpp
描  述：完成提示框的显示、字符查找、ToolTip等所有功能。
使  用：
        1、定义一个对象。
		2、初始化
		   a、从文件中加载条目，调用LoadString
		   b、用AddString一条条的加
		   c、可以重载LoadString来自定义加载数据。
		3、如果需要，注册回调函数。
		4、要调整提示框位置时，调用Show函数
		   也可以选调用Show，再调用相应的Move
	    5、可以重载OnEnter或设置EnterFun，来处理确定键按下后的事件。
版  本：1.0.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2006年1月2日
时  间：10:48:34
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10
*******************************************************************************************************/

#include "stdafx.h"
#include "TiShiTest.h"
#include "TiShi.h"
#include ".\tishi.h"


// CTiShi

IMPLEMENT_DYNAMIC(CTiShi, CListBox)
CTiShi::CTiShi()
{
	m_iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
    m_iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);
    m_iTop = 0;
    m_iLeft = 0;
	m_iListWidth = 200;
	m_iListHeight = 200;
    m_iEditWidth = m_iListWidth;
	m_iEditHeight = 55;
	m_bShow = FALSE;
	m_szInput = _T("");

	m_bVerTiShi = TRUE;
	m_hParent = NULL;

	m_EnterFun = NULL;
	m_KeyPressFun = NULL;
	m_ShowTipFun = NULL;

}

CTiShi::~CTiShi()
{
}


BEGIN_MESSAGE_MAP(CTiShi, CListBox)
	ON_WM_CREATE()
	ON_WM_LBUTTONUP()
    ON_WM_KEYUP()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


// CTiShi 消息处理程序
void CTiShi::OnLButtonUp(UINT nFlags, CPoint point)
{
	OnLeftButtonEvents(GetString());

	CListBox::OnLButtonUp(nFlags, point);
	GetString();
}

void CTiShi::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	if(m_EnterFun)
	{
		m_EnterFun(GetString());
	}// 结束 if(m_EnterFun)
	OnEnter(GetString());

	CListBox::OnLButtonDblClk(nFlags, point);
}

/*******************************************************************************************************
函数名：OnLeftButton
描  述：用于处理鼠标左击事件。它是一个虚拟函数。用户可以在派生类中自定义自己的事件。
参  数：
		LPCTSTR lpszText：列表选择的文本
返回值：类型为 void 。
版  本：1.0.0.1
作  者：康  林
时  间：2005年8月29日 8:07:45
*******************************************************************************************************/
void CTiShi::OnLeftButtonEvents(LPCTSTR lpszText)
{
	TRACE(_T("CTiShi::OnLeftButton"));
	return;
}

//修改:键盘输入还没有完成
void CTiShi::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	int nIndex = GetCurSel();
	if(nIndex != -1)
	{
		switch(nChar)
		{
		case VK_UP:
			TRACE("UP\n");
		case VK_DOWN:
			TRACE("Down\n");
		case VK_PRIOR:
			TRACE("PageUP\n");
		case VK_NEXT:
			TRACE("PageDown\n");
			break;
		case VK_RETURN:
			TRACE("RETURN\n");
			if(m_EnterFun)
			{
				m_EnterFun(GetString());
			}// 结束 if(m_EnterFun)
			OnEnter(GetString());
			break;
		default:
			TRACE("Other\n");
			::SetFocus(m_hParent); //设置焦点为父窗口
		}// 结束 switch(nChar)

		OnKeyEvents(nChar, GetString());
		m_KeyPressFun(nChar, nRepCnt, nFlags);
	}	

error_exit:
	CListBox::OnKeyUp(nChar, nRepCnt, nFlags);
	GetString();
}

/*******************************************************************************************************
函数名：OnKeyEvents
描  述：用于处理键盘事件。它是一个虚拟函数。用户可以在派生类中自定义自己的事件。
参  数：
        UINT nChar      ：输入键
		LPCTSTR lpszText：列表选择的文本
返回值：类型为 void 。
版  本：1.0.0.1
作  者：康  林
时  间：2006年1月2日 11:03:39
*******************************************************************************************************/
void CTiShi::OnKeyEvents(UINT nChar, LPCTSTR lpszText)
{
	TRACE(_T("GetText:%s\n"), lpszText);
	TRACE(_T("CTiShi::OnKeyEvents\n"));
	return;
}

/*******************************************************************************************************
函数名：OnEnter
描  述：Enter 键事件。它是一个虚拟函数，用户可以在派生类中自定义自己的事件。
参  数：
        LPCTSTR lpszText：当前选择的条目内容。
返回值：类型为 void 。
版  本：1.0.0.1
作  者：康  林
时  间：2006年9月4日 13:56:32
*******************************************************************************************************/
void CTiShi::OnEnter(LPCTSTR lpszText)
{
	::SetFocus(m_hParent);
	Show(m_hParent, FALSE);
	return;
}

/*******************************************************************************************************
函数名：RegisterKeyPress
描  述：注册处理键盘消息的回调函数
参  数：
        KeyPressFun fun：键盘消息处理回调函数。
返回值：类型为 BOOL 。
*******************************************************************************************************/
BOOL CTiShi::RegisterKeyPress(KeyPressFun fun)
{
	if(fun == NULL)
	{
		return FALSE;
	}// 结束 if(fun == NULL)
	m_KeyPressFun = fun;
	return TRUE;
}

/*******************************************************************************************************
函数名：RegisterEnterFun
描  述：设置确定键的回调函数
参  数：
        EnterFun fun：回调函数指针
返回值：类型为 BOOL 。成功返回TURE，否则返回FALSE。
*******************************************************************************************************/
BOOL CTiShi::RegisterEnterFun(EnterFun fun)
{
	if(fun == NULL)
	{
		return FALSE;
	} // 结束 if(fun == NULL)
	m_EnterFun = fun;
	return TRUE;
}

/*******************************************************************************************************
函数名：RegisterShowTip
描  述：注册条目帮助提示框的回调函数。
参  数：
        ShowTipFun fun：条目帮助提示框的回调函数。它的定义：
		typedef int(*ShowTipFun)(UINT nIndex, LPCTSTR lpcszText)
		参数：
		     UINT nIndex：被选择条目的索引
			 LPCTSTR lpcszText：被选择条目的内容
返回值：类型为 BOOL 。
*******************************************************************************************************/
BOOL CTiShi::RegisterShowTip(ShowTipFun fun)
{
	if(fun == NULL)
	{
		return FALSE;
	}// 结束 if(fun == NULL)
	m_ShowTipFun = fun;
	return TRUE;
}

// 设置版权信息
int CTiShi::SetCopyRight(LPCTSTR lpszCopyRight)
{
	CString szTemp, szLeave, m_szEditText;
    int iPos;
	CSize tmpsize, Size(m_iEditWidth, 0);
    
    m_szEditText = lpszCopyRight;
	GetFontSize(GetSafeHwnd(), m_szEditText, &Size);

    m_iListWidth = Size.cx;
    m_iEditWidth = m_iListWidth;
    m_iEditHeight = Size.cy;
    
	m_Edit.SetWindowText(m_szEditText);
    Move();
    
	return 1;
}

int CTiShi::ShowCopyRight(BOOL bShow)
{
	return m_bVerTiShi = bShow;
}

// 得到指定字体的大小
int CTiShi::GetFontSize(HWND hWnd, LPCTSTR lpszText, LPSIZE lpSize)
{
	CString szTemp = lpszText;
	CString szLeave;
	int iPos = szTemp.Find("\r\n");
	CSize Size(0, 0), tmpsize;
	while(1)
	{
		if(iPos != -1)
		{
			// Right 执行后没有改变原来的存储区
			szLeave = szTemp.Right(szTemp.GetLength() - iPos - 2);
			szTemp = szTemp.Left(iPos);
		}
		//不能测试出包含换行符字符串的大小
		if(GetTextExtentPoint32(::GetDC(hWnd), szTemp, szTemp.GetLength(), &tmpsize))
		{
			if(tmpsize.cx > Size.cx)
			{
				Size.cx = tmpsize.cx;
			} // 结束 if(tmpsize.cx > Size.cx)
			Size.cy += tmpsize.cy; 
		}
		else
		{
			return FALSE;
		} // 结束 if(GetTextExtentPoint32(::GetDC(hWnd), szTemp, szTemp.GetLength(), &tmpsize))

		if(iPos == -1)
		{
			break;
		} // 结束 if(iPos == -1)
		szTemp = szLeave;
		iPos = szTemp.Find("\r\n");
	} // 结束 (1)
	lpSize->cx = Size.cx;
	lpSize->cy = Size.cy;
	return TRUE;
}

// 设置字体
int CTiShi::SetFont(LPCTSTR lpszFacename,
					int nHeight,
					int nWidth,
					int nEscapement,
					int nOrientation,
					int nWeight,
					BYTE bItalic,
					BYTE bUnderline,
					BYTE cStrikeOut,
					BYTE nCharSet,
					BYTE nOutPrecision,
					BYTE nClipPrecision,
					BYTE nQuality,
					BYTE nPitchAndFamily
					)
{
	CString szFont = lpszFacename;

	m_Font.Detach();
	m_Font.CreateFont(nHeight, nWidth, nEscapement, nOrientation, nWeight, bItalic, bUnderline, cStrikeOut, nCharSet, nOutPrecision,
		nClipPrecision, nQuality, nPitchAndFamily, lpszFacename);
	return SetFont(&m_Font);
}

int CTiShi::SetFont(CFont * pFont)
{
	CListBox::SetFont(pFont);
	m_Edit.SetFont(pFont);
	m_edTip.SetFont(pFont);
	return 1;
}

/*******************************************************************************************************
函数名：CreateEx
描  述：建立提示框
参  数：
        HWND hParent：父窗口句柄。
返回值：类型为 BOOL 。
版  本：1.0.0.1
作  者：康  林
时  间：2005年8月29日 10:33:42
*******************************************************************************************************/
BOOL CTiShi::CreateEx(HWND hParent)
{
	if(m_hParent)
	{
		return FALSE;
	} // 结束 if(m_hParent)

	m_hParent = hParent;
	
	return CListBox::CreateEx(WS_EX_TOPMOST,
		_T("ListBox"), NULL, WS_POPUP | WS_BORDER | WS_VSCROLL | LBS_SORT,
		m_iLeft, m_iTop, m_iListWidth, m_iListHeight,
		NULL, NULL, NULL);
}

int CTiShi::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CListBox::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_Edit.CreateEx(WS_EX_TOPMOST, _T("Edit"), NULL,
					WS_POPUP | WS_BORDER
					| ES_READONLY | ES_MULTILINE | ES_CENTER
					| ES_AUTOVSCROLL | ES_AUTOHSCROLL,
					m_iLeft, m_iTop + m_iListHeight, m_iEditWidth, m_iEditHeight,
					this->GetSafeHwnd(), NULL);
	SetCopyRight(_T("作者：康林\r\n时间：2005年06月13日\r\nE_Mail：kl222@126.com"));
	m_edTip.CreateEx(WS_EX_TOPMOST, _T("Edit"), NULL,
					WS_POPUP | WS_BORDER | ES_READONLY | ES_MULTILINE //| ES_CENTER 
					| ES_AUTOVSCROLL | ES_AUTOHSCROLL,
					0, 0, 0, 0,
					this->GetSafeHwnd(), NULL);
	SetFont();
	InitToolTip();
	return 0;
}

/*******************************************************************************************************
函数名：Move
描  述：移动提示框
参  数：无
返回值：类型为 BOOL 。
版  本：1.0.0.1
作  者：康  林
时  间：2006年1月2日 11:16:37
*******************************************************************************************************/
BOOL CTiShi::Move()
{
	if(!(m_hParent && m_bShow))
    {
        return FALSE;
    } // 结束 if(!(m_hParent && m_bShow))

    CPoint caret;
	if(!::GetCaretPos(&caret))
    {
        return FALSE;
    }
	::ClientToScreen(m_hParent, &caret);

    CSize size;
	if(!GetTextExtentPoint32(::GetDC(m_hParent), _T("a"), 1, &size))
    {
        return FALSE;
    }
    //修改:在本程序中要在插入符后一个字符才提示,所以这样.
    //     其它情况直接在插入后提示,只要纵坐标减少就行,横坐标不要变
    caret.Offset(size);
	if(caret.x + m_iListWidth <= m_iScreenWidth)
    {
		m_iLeft = caret.x;
    }
    else
    {
		m_iLeft = caret.x - m_iListWidth;
    }
	if(caret.y + m_iListHeight + m_iEditHeight <= m_iScreenHeight)
    {
		m_iTop = caret.y;
    }
    else
    {
		m_iTop = caret.y - m_iListHeight - m_iEditHeight - size.cy;
    }

	MoveWindow(m_iLeft, m_iTop, m_iListWidth, m_iListHeight, TRUE);
	m_Edit.MoveWindow(m_iLeft, m_iTop + m_iListHeight, m_iEditWidth, m_iEditHeight, TRUE);

	FindText();

	//增加:移动条目帮助提示框的位置

	::SetFocus(m_hParent);

	return TRUE;
}

/*******************************************************************************************************
函数名：Move
描  述：
参  数：
        UINT nCh：输入的字符
返回值：类型为 BOOL 。
版  本：1.0.0.1
作  者：康  林
时  间：2006年1月2日 11:15:58
*******************************************************************************************************/
BOOL CTiShi::Move(UINT nCh)
{
	switch(nCh)
	{
	case VK_BACK:
		m_szInput.Delete(m_szInput.GetLength() - 1);
		break;
	default:
		m_szInput += (TCHAR)nCh;
	} // 结束 (m_szInput.GetLength() - 1)
	return Move();
}

/*******************************************************************************************************
函数名：Move
描  述：
参  数：
        TCHAR ch：输入的字符
返回值：类型为 BOOL 。
版  本：1.0.0.1
作  者：康  林
时  间：2006年1月2日 11:16:13
*******************************************************************************************************/
BOOL CTiShi::Move(TCHAR ch)
{
	return Move((UINT)ch);
}

/*******************************************************************************************************
函数名：Move
描  述：
参  数：
        LPCTSTR lpszText：输入的字符串
返回值：类型为 BOOL 。
版  本：1.0.0.1
作  者：康  林
时  间：2006年1月2日 11:16:23
*******************************************************************************************************/
BOOL CTiShi::Move(LPCTSTR lpszText)
{
	m_szInput = lpszText;
	return Move();
}

/*******************************************************************************************************
函数名：Show
描  述：显示提示框
参  数：
        HWND hParent：父窗口句柄。因为显示了提示窗口以后，要把焦点重设置到容器窗口。
		BOOL bShow  ：TRUE，显示；FALSE，隐藏。
返回值：类型为 BOOL 。
版  本：1.0.0.1
作  者：康  林
时  间：2005年8月29日 10:41:08
*******************************************************************************************************/
BOOL CTiShi::Show(HWND hParent, BOOL bShow, LPCTSTR lpcszInput)
{
	ASSERT(hParent != NULL);
	m_hParent = hParent;
	BOOL bOld = m_bShow;
	m_bShow = bShow;
	if(m_bShow)
	{
		/*LONG lnStyle = ::GetWindowLong(this->GetSafeHwnd(), GWL_STYLE);
		lnStyle = lnStyle & ~WS_POPUP | WS_CHILD;
		::SetWindowLong(this->GetSafeHwnd(), GWL_STYLE, lnStyle);
		::SetParent(this->GetSafeHwnd(), m_hParent);*/
		Move();
		//::SetWindowPos(this->GetSafeHwnd(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		if(lpcszInput)
		{
			m_szInput = lpcszInput;
		} // 结束 if(lpcszInput)
		ShowWindow(SW_SHOW);
		if(m_bVerTiShi)
		{
			m_Edit.ShowWindow(SW_SHOW);
		}
		else
		{
			m_Edit.ShowWindow(SW_HIDE);
		} // 结束 if(m_bVerTiShi)
		::SetFocus(m_hParent); //设置焦点为容器窗口
	}
	else
	{
		m_edTip.ShowWindow(SW_HIDE);
		m_Edit.ShowWindow(SW_HIDE);
		ShowWindow(SW_HIDE);
		m_szInput = _T("");
	} // 结束 if(m_bShow)
	return bOld;
}

/*******************************************************************************************************
函数名：ShowTip
描  述：显示选择项的帮助提示框 Tip。
        1、如果条目提示框没显示，则帮助提示框也不用显示。
		2、调用回调函数，得到帮助内容。
		3、再调整帮助提示框的位置。
参  数：
        LPCTSTR lpszText：选择项的内容。
返回值：类型为 int 。
*******************************************************************************************************/
int CTiShi::ShowTip(LPCTSTR lpszText)
{
	CString szInText(lpszText);
	LPTSTR pStr;
	BOOL bShowTip = FALSE;
	if(!m_bShow)
	{
		m_edTip.ShowWindow(SW_HIDE);
		return FALSE;
	} // 结束 if(!m_bShow)

	if(m_ShowTipFun)
	{
		if(!m_ShowTipFun(GetCurSel(), lpszText, &pStr))
		{
			if(pStr)
			{
				szInText = pStr;
				bShowTip = TRUE;
			}// 结束 if(pStr)
		}// 结束 if(!m_ShowTipFun(GetCurSel(), lpszText, &pStr))
		if(pStr)
		{
			delete []pStr;
		} // 结束 if(pStr)
	}// 结束 if(m_ShowTipFun)
	
	//调整条目项帮助提示框的位置
	int nCur;
	nCur = GetCurSel();
	if(nCur != LB_ERR)
    {
		CRect rect;
		CSize size;
		int nTop, nLeft;
		if(LB_ERR != GetItemRect(nCur, &rect))
		{
			ClientToScreen(&rect);
			
			if(FALSE == bShowTip)
			{
				//默认处理时，当可以显示所有内容时，不显示帮助提示框
				GetFontSize(GetSafeHwnd(), szInText, &size);
				if(size.cx < rect.Width())
				{
					m_edTip.ShowWindow(SW_HIDE);
					return FALSE;
				}
				else
				{
					bShowTip = TRUE;
				}// 结束 if(size.cx < rect.Width())
			}
			else
			{
				GetFontSize(m_edTip.GetSafeHwnd(), szInText, &size);
			} // 结束 if(FALSE == bShowTip)

			//调整位置
			if(size.cx < m_iScreenWidth - rect.left - rect.Width())
			{
				nLeft = rect.left + m_iListWidth;
				nTop = rect.top;
			}
			else if(size.cx < rect.left)
			{
				nLeft = rect.left - size.cx;
				nTop = rect.top;
			}
			else 
			{
				nLeft = (m_iScreenWidth - size.cx) / 2;
				nTop = rect.top + rect.Height();
			} // 结束 if(size.cx < m_iScreenWidth - rect.left - rect.Width())
			m_edTip.MoveWindow(nLeft, nTop, size.cx, size.cy);
		} // 结束 if(LB_ERR != GetItemRect(iCur, &rect))
	}// 结束 if(nCur != LB_ERR)

	if(bShowTip)
	{
		m_edTip.SetWindowText(szInText);
		m_edTip.ShowWindow(SW_SHOWNOACTIVATE);//SW_SHOW);
	} // 结束 if(bShowTip)

}

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
//以下是完成 ===ToolTip=== 功能的函数块
//

/*******************************************************************************************************
函数名：InitToolTip
功  能：初始化 ToolTip
参  数：无
返回值：无
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-17
时  间：19:54:35
*******************************************************************************************************/
void CTiShi::InitToolTip()
{
	if (m_ToolTip.m_hWnd == NULL)
	{
		// Create ToolTip control
		m_ToolTip.Create(this);
		// Create inactive
		m_ToolTip.Activate(FALSE);
		// Enable multiline
		m_ToolTip.SendMessage(TTM_SETMAXTIPWIDTH, 0, 100 /*最大窗口宽度*/);
	} // if
}

/*******************************************************************************************************
函数名：SetToolTipText
功  能：设置ToolTip文本
参  数：
         LPCSTR lpszText：要显示的文本
         BOOL bActivate：是否激活
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-17
时  间：20:23:36
*******************************************************************************************************/
BOOL CTiShi::SetToolTipText(LPCSTR lpszText, BOOL bActivate)
{
	// We cannot accept NULL pointer
	if (lpszText == NULL) return FALSE;

	// Initialize ToolTip
	InitToolTip();

	// If there is no tooltip defined then add it
	if (m_ToolTip.GetToolCount() == 0)
	{
		CRect rect; 
		GetClientRect(rect);
		m_ToolTip.AddTool(this, lpszText, rect, 1);
	} // 结束 if(m_ToolTip.GetToolCount() == 0)

	// Set text for tooltip
	m_ToolTip.UpdateTipText(lpszText, this, 1);
	m_ToolTip.Activate(bActivate);
	return TRUE;
}

/*******************************************************************************************************
函数名：SetToolTipText
功  能：设置ToolTip文本
参  数：
         int nText：要显示的文本的资源号
         BOOL bActivate：是否激活
返回值：
作  者：康  林
版  本：1.0.0.1
日  期：2004-12-17
时  间：20:24:10
*******************************************************************************************************/
BOOL CTiShi::SetToolTipText(int nText, BOOL bActivate)
{
	CString sText;

	// Load string resource
	sText.LoadString(nText);
	// If string resource is not empty
	if (sText.IsEmpty() == FALSE) 
	{
		SetToolTipText((LPCTSTR)sText, bActivate);
	}
	return TRUE;
}

BOOL CTiShi::PreTranslateMessage(MSG* pMsg)
{
	m_ToolTip.RelayEvent(pMsg);
	return CListBox::PreTranslateMessage(pMsg);
}

//
//以上是完成 ===ToolTip=== 功能的函数块
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>


// 从文件中加载数据
int CTiShi::LoadString(LPCTSTR lpszFileName)
{
	TRY
	{
		CStdioFile stdf(lpszFileName, CFile::modeRead);
		CString szText;
		while(stdf.ReadString(szText))
		{
			AddString(szText);
		} // 结束 (stdf.ReadString(szText))
	}
	CATCH(CFileException, e)
	{
		e->ReportError();
		return 0;
	}
	END_CATCH
	return 1;
}

/*******************************************************************************************************
函数名：FindText
描  述：在条目提示框中查找字符串，输入的字符串存在成员变量 m_szInput 中。
参  数：无
返回值：类型为 int 。
版  本：1.0.0.1
作  者：康  林
时  间：2005年8月29日 11:43:50
*******************************************************************************************************/
int CTiShi::FindText()
{
	return FindText(m_szInput);
}

int CTiShi::FindText(LPCTSTR lpcszText)
{
	int nRet = 0;
	int nIndex = FindString(-1, lpcszText);
	TRACE(_T("%s(%d) : %s:%d\n"), __FILE__, __LINE__,  m_szInput, nIndex);
	if(LB_ERR != nIndex)
	{
		SetCurSel(nIndex);
		nRet = 1;
	}// 结束 if(LB_ERR != nIndex)
	GetString();	
	
	return nRet;
}

/*******************************************************************************************************
函数名：GetString
描  述：默认得到条目提示框中选择的文本。
        此函数为重载函数，用户可以重载，得到自己需要的数据。
		可重载此函数，显示对此项的注释框 Tip
参  数：void：无
返回值：类型为 CString 。
版  本：1.0.0.1
作  者：康  林
时  间：2005年8月29日 11:44:51
*******************************************************************************************************/
CString CTiShi::GetString(void)
{
	CString szText;
	int nIndex = GetCurSel();
	if(LB_ERR != nIndex)
	{
		GetText(nIndex, szText);
		
		// 是否显示注释框 Tip
		ShowTip(szText);
	} // 结束 if(LB_ERR != nIndex)
	return szText;
}