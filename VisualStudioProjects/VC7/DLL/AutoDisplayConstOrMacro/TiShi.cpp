// TiShi.cpp : 实现文件
//

#include "stdafx.h"
#include "TiShi.h"

// CTiShi

CTiShi::CTiShi()
{
    m_hInstance = NULL;  
}

CTiShi::CTiShi(HINSTANCE hInstance)
{
    m_hInstance = hInstance;
    Inital();
}

CTiShi::~CTiShi()
{
    DestroyWindow(m_hEditTip);
    DestroyWindow(m_hList);
    DestroyWindow(m_hEdit);
}

// 设置实例句柄
void CTiShi::SetInstance(HINSTANCE hInstance)
{
    ASSERT(hInstance != NULL);
    if(m_hInstance)
    {
        return;
    } //结束 if(hInstance)
    m_hInstance = hInstance;
    Inital();
}

// 初始化
BOOL CTiShi::Inital(void)
{
    m_hParent = NULL;
    m_iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
    m_iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);
    m_iTop = 0;
    m_iLeft = 0;
    m_iListWidth = 200;
    m_iListHeight = 200;
    m_iEditWidth = m_iListWidth;
    m_iEditHeight = 55;    
    m_szFont = _T("宋体");

    m_hFont = CreateFont(12, 0, 0, 0, 0,
                         FALSE, FALSE, FALSE,
                         DEFAULT_CHARSET, DEFAULT_QUALITY,
                         DEFAULT_QUALITY, DEFAULT_QUALITY,
                         FIXED_PITCH + FF_SWISS, m_szFont);

    m_hList = CreateWindowEx(WS_EX_TOPMOST, _T("ListBox"),
                             _T(""),
                             WS_POPUP | WS_BORDER | WS_VSCROLL | LBS_SORT,
                             m_iTop, m_iLeft, m_iListWidth, m_iListHeight,
                             NULL, NULL,
                             m_hInstance, NULL);
    SendMessage(m_hList, WM_SETFONT, (WPARAM)m_hFont, 0);
    lpWndProc = (WNDPROC)SetWindowLong(m_hList, GWL_WNDPROC, (LONG)WindowProc);

    m_hEditTip = CreateWindowEx(WS_EX_TOPMOST, _T("Edit"),
                            _T(""),
                            WS_POPUP | WS_BORDER 
                            | ES_READONLY | ES_MULTILINE | ES_CENTER
                            | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
                            0, 0, 0, 0,
                            m_hList, NULL,
                            m_hInstance, NULL);
    SendMessage(m_hEditTip, WM_SETFONT, (WPARAM)m_hFont, 0);

    m_hEdit = CreateWindowEx(WS_EX_TOPMOST, _T("Edit"),
                            _T(""),
                            WS_POPUP | WS_BORDER 
                            | ES_READONLY | ES_MULTILINE | ES_CENTER
                            | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
                            m_iTop + m_iListHeight, m_iLeft, m_iEditWidth, m_iEditHeight,
                            NULL, NULL,
                            m_hInstance, NULL);
    SendMessage(m_hEdit, WM_SETFONT, (WPARAM)m_hFont, 0);

    SetCopyRightInfo(_T("常量、宏自动提示器\r\n作者：康林\r\n时间：2005年06月13日\r\nE_Mail：kl222@126.com"));
    SetListText(_T("提示器"));

    return TRUE;
}

// 增加例表项
BOOL CTiShi::AddListItem(LPCTSTR lpszItem, BOOL bDirectness)
{
	ASSERT(lpszItem != NULL);
	//直接增加
    if(bDirectness)
    {
        int iIndex = SendMessage(m_hList, LB_ADDSTRING, 0, (LPARAM)lpszItem);
        if(iIndex == LB_ERR)
        {
            return FALSE;
        }
        else
        {        
            return TRUE;
        } //结束 if(iIndex == LB_ERR)
	} //结束 if(bDirectness)
	//查找是否有已存在,如果存在,则不加
    int iIndex = SendMessage(m_hList, LB_FINDSTRINGEXACT, 0, (LPARAM)lpszItem);
    if(iIndex == LB_ERR)
    {
        iIndex = SendMessage(m_hList, LB_ADDSTRING, 0, (LPARAM)lpszItem);
        if(iIndex == LB_ERR)
        {
            return FALSE;
        }
        else
        {        
            return TRUE;
        } //结束 if(iIndex == LB_ERR)
    } //结束 if(iIndex == LB_ERR)
    return FALSE;
}

// 删除例表项
BOOL CTiShi::DeleteListItem(LPCTSTR lpszItem)
{
    ASSERT(lpszItem != NULL);
    int iIndex = SendMessage(m_hList, LB_FINDSTRINGEXACT, 0, (LPARAM)lpszItem);
    if(iIndex == LB_ERR)
    {
        return FALSE;
    } //结束 if(iIndex == LB_ERR)
    if(SendMessage(m_hList, LB_DELETESTRING, iIndex, NULL) == LB_ERR)
    {
        return FALSE;
    } //结束 if(iIndex == LB_ERR)

    return TRUE;
}

/*******************************************************************************************************
函数名：CopyString
描  述：把提示框中的字符复制到IDE中
参  数：
         TCHAR ch：输入的字符。默认为 NULL。不加。
返回值：无
版  本：2005.6.0.0
作  者：康  林
时  间：2005-6-14 10:34:04
*******************************************************************************************************/
BOOL CTiShi::CopyString(TCHAR ch)
{
    TCHAR szReceive[MAX_BUFFER];
    int iIndex;
    iIndex = SendMessage(m_hList, LB_GETCURSEL, NULL, NULL);
    if(iIndex != LB_ERR)
    {
        iIndex = SendMessage(m_hList, LB_GETTEXT, iIndex, (LPARAM)szReceive);
        if(iIndex != LB_ERR)
        {
            CString sztemp(szReceive, iIndex);
            if(ch != NULL)
            {
                sztemp += ch;
            } //结束 if(ch != NULL)

            if ( !OpenClipboard(NULL) )
            {
                TRACE(_T("%s(%d) : 不能打开剪切板\n"), __FILE__, __LINE__);
                return FALSE;
            }
            // 清空当前剪切板
            if( !EmptyClipboard() )
            {
                TRACE(_T("%s(%d) : 剪切板清空失败。\n"), __FILE__, __LINE__);
                return FALSE;
            }

            LPTSTR lpData;
            HGLOBAL hglbCopy;
            hglbCopy = ::GlobalAlloc(GMEM_MOVEABLE, sztemp.GetLength() + sizeof(TCHAR));
            if(hglbCopy == NULL)
            {
                ::CloseClipboard();
                TRACE(_T("%s(%d) : 全局堆分配失败。\n"), __FILE__, __LINE__);
                return FALSE;
            }
            lpData = (LPTSTR) ::GlobalLock(hglbCopy);
            memcpy(lpData, sztemp, sztemp.GetLength() + sizeof(TCHAR));

            // 设置剪切板数据.
            if ( ::SetClipboardData( CF_TEXT, hglbCopy) == NULL )
            {
                TRACE(_T("%s(%d) : 不能设置剪切板数据。\n"), __FILE__, __LINE__);

                CloseClipboard();
                ::GlobalUnlock(hglbCopy);
                GlobalFree(hglbCopy);

                return FALSE;
            }
            // 关闭剪切板
            CloseClipboard();
            ::GlobalUnlock(hglbCopy);
            GlobalFree(hglbCopy);

            /* CClipboard cb;
            if(cb.SetData((LPCTSTR)sztemp))
            {*/
            
            keybd_event(VK_SHIFT, 0xff, KEYEVENTF_EXTENDEDKEY, 0);
            keybd_event(VK_INSERT, 0xff, KEYEVENTF_EXTENDEDKEY, 0);
            keybd_event(VK_INSERT, 0xff, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
            keybd_event(VK_SHIFT, 0xff, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
            /*//因为CONTROL与SHIFT有冲突,所以不用下面的方法
            keybd_event(VK_CONTROL, 0xff, KEYEVENTF_EXTENDEDKEY, 0);
            keybd_event('V', 0xff, KEYEVENTF_EXTENDEDKEY, 0);
            keybd_event('V', 0xff, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
            keybd_event(VK_CONTROL, 0xff, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);//*/
            //} //结束 if(cb.SetData((LPCTSTR)sztemp))
        } //结束 if(iIndx != LB_ERR)
    } //结束 if(SendMessage(m_hList, LB_GETCURSEL, NULL, NULL) != LB_ERR)
}

// 查找指定的字符串（不完全匹配）
BOOL CTiShi::FindString(LPCTSTR lpszItem)
{
    ASSERT(lpszItem != NULL);
    if(!MoveTiShi())
    {
        return FALSE;
    }

    CString sztemp(lpszItem);
    int iIndex = SendMessage(m_hList, LB_FINDSTRING, -1, (LPARAM)(LPCTSTR)sztemp.MakeUpper());
    if(iIndex != LB_ERR)
    {
        if(SendMessage(m_hList, LB_SELECTSTRING, -1, (LPARAM)(LPCTSTR)sztemp) != LB_ERR)
        {
            ShowTip();
            return TRUE;
        }
    } //结束 if(iIndex != LB_ERR)
    
    ShowTip();
    return FALSE;
}

/*******************************************************************************************************
函数名：ShowTip
描  述：当例表选择项不能完全显示时,显示一个 Edit 来显示此项。
参  数：无
返回值：无
版  本：2005.6.0.0
作  者：康  林
时  间：2005-6-15 13:25:44
*******************************************************************************************************/
void CTiShi::ShowTip()
{
    TCHAR szReceive[MAX_BUFFER];
    int iIndex, iCur;
    iCur = SendMessage(m_hList, LB_GETCURSEL, NULL, NULL);
    if(iCur != LB_ERR)
    {
        iIndex = SendMessage(m_hList, LB_GETTEXT, iCur, (LPARAM)szReceive);
        if(iIndex != LB_ERR)
        {
            CSize size;
            CString sztemp(szReceive);
            //sztemp.TrimRight();
            GetTextExtentPoint32(GetDC(m_hList), sztemp, sztemp.GetLength(), &size);
            if(size.cx > m_iListWidth)
            {
                CRect rect;
                iIndex = SendMessage(m_hList, LB_GETITEMRECT, iCur, (LPARAM)&rect);
                if(iIndex != LB_ERR)
                {
                    int x, y;
                    CPoint topleft, caret;
                    topleft = rect.TopLeft();
                    ::ClientToScreen(m_hList, &topleft);

                    y = topleft.y;

                    CSize chSize;
                    GetCaretPos(&caret);
                    ::ClientToScreen(m_hParent, &caret);
                    GetTextExtentPoint32(GetDC(m_hParent), _T("a"), 1, &chSize);
                    caret.Offset(chSize);

                    if(caret.x <= m_iLeft)
                    {
                        if(m_iLeft + m_iListWidth + size.cx <= m_iScreenWidth)
                        {
                            x = m_iLeft + m_iListWidth;
                        }
                        else
                        {
                            x = m_iLeft - size.cx;
                        }//结束 if(m_iLeft + m_iListWidth + size.cx <= m_iScreenWidth)
                    }
                    else
                    {
                        if(m_iLeft - size.cx >= 0)
                        {
                            x = m_iLeft - size.cx;
                        }
                        else
                        {
                            x = m_iLeft + m_iListWidth;
                        } //结束 if(m_iLeft - size.cx >= 0)
                    }

                    SetWindowText(m_hEditTip, sztemp);
                    MoveWindow(m_hEditTip, x, y, size.cx, size.cy + 1, TRUE);
                    ShowWindow(m_hEditTip, SW_SHOW);
                    SetFocus(m_hParent);
                    return;
                }
            }
        } //结束 if(iIndex != LB_ERR)
    } //结束 if(iCur != LB_ERR)

    ShowWindow(m_hEditTip, SW_HIDE);
}

// 设置版权信息
BOOL CTiShi::SetCopyRightInfo(LPCTSTR lpszCopyRight)
{
    CString szTemp, szLeave;
    int iPos;
    CSize tmpsize, Size(150, 0);
    
    m_szEditText = lpszCopyRight;
    szTemp = m_szEditText;
    iPos = szTemp.Find("\r\n");
    do
    {
        if(iPos != -1)
        {
           //调试: Right 执行后是否改变原来的存储区
            szLeave = szTemp.Right(szTemp.GetLength() - iPos + 1);
            szTemp = szTemp.Left(iPos - 1);
        }
        //调试: 是否能测试出包含换行符字符串的大小
        if(GetTextExtentPoint32(GetDC(m_hEdit), szTemp, szTemp.GetLength(), &tmpsize))
        {
            if(tmpsize.cx > Size.cx)
            {
                Size.cx = tmpsize.cx;
            } // 结束 if(tmpsize.cx > Size.cx)
            Size.cy += tmpsize.cy;
        } // 结束 if(GetTextExtentPoint32(GetDC(m_hEdit), szTemp, szTemp.GetLength(), &tmpsize))
        iPos = szTemp.Find("\r\n");
    }  while(iPos != -1);

    m_iListWidth = Size.cx;
    m_iEditWidth = m_iListWidth;
    m_iEditHeight = Size.cy;
    
    SetWindowText(m_hEdit, m_szEditText);
    MoveTiShi();
    return 0;
}

// 设置例表标题栏
BOOL CTiShi::SetListText(LPCTSTR lpszText)
{
    SetWindowText(m_hList, lpszText);
    return 0;
}

// 显示/隐藏提示框
BOOL CTiShi::ShowTiShi(bool bShow,  HWND hParent)
{
    if(bShow)
    {
        m_bShow = TRUE;
        if(hParent)
        {
            m_hParent = hParent;
        }
        else
        {
            m_hParent = GetFocus();
        } //结束 if(hParent)
        int iIndex;
        iIndex = SendMessage(m_hList, LB_GETCURSEL, NULL, NULL);
        if(iIndex == LB_ERR)
        {
            SendMessage(m_hList, LB_SETCURSEL, 0, NULL);
        }
        MoveTiShi();        
        ShowWindow(m_hList, SW_SHOW);
        ShowWindow(m_hEdit, SW_SHOW);
        SetFocus(m_hParent);
    }
    else
    {
        m_bShow = FALSE;
        ShowWindow(m_hList, SW_HIDE);
        ShowWindow(m_hEdit, SW_HIDE);
    }
    return 0;
}

/*******************************************************************************************************
函数名：Showed
描  述：得到提示框的显示状态。
参  数：无
返回值：类型为 BOOL 。显示返回TRUE，否则返回FALSE。
版  本：1.0
作  者：康  林
时  间：2005年8月28日 9:36:56
*******************************************************************************************************/
BOOL CTiShi::Showed()
{
	retrun m_bShow;
}

// 移动提示框
BOOL CTiShi::MoveTiShi(void)
{
    if(!m_bShow)
    {
        return FALSE;
    }

    CPoint caret;
    if(!GetCaretPos(&caret))
    {
        return FALSE;
    }
    ClientToScreen(m_hParent, &caret);

    CSize size;
    if(!GetTextExtentPoint32(GetDC(m_hParent), _T("a"), 1, &size))
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
    if(size.cy + m_iListHeight + m_iEditHeight <= m_iScreenHeight)
    {
		m_iTop = caret.y;
    }
    else
    {
		m_iTop = caret.y - m_iListHeight - m_iEditHeight;
    }

    MoveWindow(m_hList, m_iLeft, m_iTop, m_iListWidth, m_iListHeight, TRUE);
    MoveWindow(m_hEdit, m_iLeft, m_iTop + m_iListHeight, m_iEditWidth, m_iEditHeight, TRUE);

    return 0;
}

/*******************************************************************************************************
函数名：SetListPos
描  述：移动例表框中的选择项目
参  数：
         POSTION_ENUM pos：移动方式
返回值：成功，TRUE；失败，FALSE。
版  本：2005.6.0.0
作  者：康  林
时  间：2005-6-14 21:11:41
*******************************************************************************************************/
BOOL CTiShi::SetListPos(POSTION_ENUM pos)
{
    int iCur, iNum, iCount;
    iNum = 8;

    //------------------------------------------------------------------------
    //以下是完成 === 见 BUG-4 位置不能调换 === 功能的语句块
    //

    if(!(0x80 && GetAsyncKeyState(VK_MENU)))
    {
        //ShowTiShi(FALSE, FALSE);
        //m_szInput = _T(""); //见 BUG-4
        return FALSE;
    } //结束 if(!(0x80 && GetAsyncKeyState(VK_MENU)))
    
    if(!m_bShow)
    {
        return FALSE;
    } //结束 if(!m_bShowTiShi)

    //
    //以上是完成 === 见 BUG-4 位置不能调换 === 功能的语句块
    //------------------------------------------------------------------------
           
    iCur = SendMessage(m_hList, LB_GETCURSEL, NULL, NULL);
    if(iCur == LB_ERR)
    {
        iCur = 0;
    } //结束 if(iIndex == LB_ERR)
    iCount = SendMessage(m_hList, LB_GETCOUNT, NULL, NULL);
    if(iCount == LB_ERR)
    {
        return FALSE;
    } //结束 if(iCount == LB_ERR)
    switch(pos)
    {
    case UP:
        iCur--;
        break;
    case DOWN:
        iCur++;
        break;
    case PAGEUP:
        iCur -= iNum;
        break;
    case PAGEDOWN:
        iCur += iNum;
        break;
    case HOME:
        iCur = 0;
        break;
    case END:
        iCur = iCount - 1;
        break;
    } //结束 switch(pos)
    if(iCur < 0)
    {
        iCur = 0;
    } //结束 if(iCur < 0)
    if(iCur >= iCount)
    {
        iCur = iCount - 1;
    } //结束 if(iCur >= iCount)
    if(SendMessage(m_hList, LB_SETCURSEL, iCur, NULL) != LB_ERR)
    {
        ShowTip();
        return TRUE;
    }
    else
    {
        return FALSE;
    }//结束 if(SendMessage(m_hList, LB_SETCURSEL, iCur, NULL) != LB_ERR)
}

/*******************************************************************************************************
函数名：WindowProc
描  述：例表框架的消息处理过程
参  数：
         HWND hWnd：例表框句柄
         UINT uMsg：消息
         WPARAM wParam：参数
         LPARAM lParam：参数
返回值：
版  本：2005.6.0.0
作  者：康  林
时  间：2005-6-14 15:21:08
*******************************************************************************************************/
LRESULT CALLBACK CTiShi::WindowProc(HWND hWnd,
                                    UINT uMsg,
                                    WPARAM wParam,
                                    LPARAM lParam
                                    )
{
    //switch(uMsg)
    //{
    //case WM_LBUTTONDBLCLK:
    //    if(m_bShow)
    //    {
    //        ShowTiShi(FALSE);

    //        CopyString();
    //        break;
    //    } //结束 if(m_bShowTiShi) 
    //case WM_LBUTTONUP:
    //    if(m_bShow)
    //    {
    //        ShowTip();
    //    }
    //    break;
    //} //结束 switch(uMsg)
    //return CallWindowProc(lpWndProc, hWnd, uMsg, wParam, lParam);
    return 0;
}
