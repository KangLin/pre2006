/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：AutoDisplayConstOrMacro.cpp
描  述：常量、宏自动提示器实现文件
版  本：2005.6.0.0
作  者：康  林
E_Mail：kl222@126.com
日  期：2005-6-14
时  间：20:58:47
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10
*******************************************************************************************************/
// AutoDisplayConstOrMacro.cpp : 定义 DLL 的初始化例程。
//

#include "stdafx.h"
#include "AutoDisplayConstOrMacro.h"
#include "..\..\..\..\Programe\VC\File\FileEx.h"
#include "..\..\..\..\Programe\VC\Clipboard\Clipboard.h"
#include "..\..\..\..\Programe\VC\Limit\Limit.h"
#include "TiShi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define MAX_BUFFER 1024

HINSTANCE g_hInstance;   //DLL实例的句柄
HHOOK g_hKeyHook;        //键盘钩子句柄
HHOOK g_hMsgHook;        //消息钩子
HWND g_hWnd;             //程序中窗口的句柄(文档 TextSelect)
HWND g_hList;            //提示框的句柄
HWND g_hSysList;         //系统提示框的句柄
HWND g_hUserList;        //用户数据提示框的句柄
HWND g_hEditTip;         //Tip Edit 的句柄
HWND g_hEdit;            //版权信息框的句柄
HFONT g_hFont;           //字体句柄
WNDPROC lpWndProc;       //窗口处理函数
WNDPROC lpUserWndProc;
WNDPROC lpEditWndProc;   //编辑窗口处理函数
BOOL g_bShowTiShi;       //显示提示框

INT g_iScreenWidth;      //屏幕宽度
INT g_iScreenHeight;     //屏幕高度
INT g_iListTop;          //例表框的顶端
INT g_iListLeft;         //例表框的左边
INT g_iListWidth;        //例表框的宽度
INT g_iListHeight;       //例表框的高度
INT g_iEditWidth;        //版权框的宽度
INT g_iEditHeight;       //版权框的高度

BOOL g_bESCFunction;     //ESC值的作用。TRUE，清除前面的输入；FALSE，不清除前面的输入
CString g_szInput;       //输入字符串
CString g_szPrompt;      //要显示提示框的字符串
CString g_szUserPrompt;  //要显示用户数据提示框的字符串
CString g_szINIFile;     //配置文件
CString g_szListFile;    //例表文件
CString g_szTempFile;    //临时文件
CString g_szPath;        //当前DLL的路径
CString g_szCopyRight;   //版权

//
//	注意！
//
//		如果此 DLL 动态链接到 MFC
//		DLL，从此 DLL 导出并
//		调入 MFC 的任何函数在函数的最前面
//		都必须添加 AFX_MANAGE_STATE 宏。
//
//		例如:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// 此处为普通函数体
//		}
//
//		此宏先于任何 MFC 调用
//		出现在每个函数中十分重要。这意味着
//		它必须作为函数中的第一个语句
//		出现，甚至先于所有对象变量声明，
//		这是因为它们的构造函数可能生成 MFC
//		DLL 调用。
//
//		有关其他详细信息，
//		请参阅 MFC 技术说明 33 和 58。
//

// CAutoDisplayConstOrMacroApp

BEGIN_MESSAGE_MAP(CAutoDisplayConstOrMacroApp, CWinApp)
END_MESSAGE_MAP()


// CAutoDisplayConstOrMacroApp 构造

CAutoDisplayConstOrMacroApp::CAutoDisplayConstOrMacroApp()
{
	// TODO: 在此处添加构造代码，
    // 将所有重要的初始化放置在 InitInstance 中
    g_hList = NULL;
    g_hEdit = NULL;
    g_hKeyHook = NULL;
    g_hMsgHook = NULL;
}


// 唯一的一个 CAutoDisplayConstOrMacroApp 对象

CAutoDisplayConstOrMacroApp theApp;


// CAutoDisplayConstOrMacroApp 初始化

BOOL CAutoDisplayConstOrMacroApp::InitInstance()
{
	TRACE(_T("%s(%d) : CAutoDisplayConstOrMarcoApp::InitInstance()\n"), __FILE__, __LINE__); 
	CWinApp::InitInstance();

    g_hInstance = ::AfxGetInstanceHandle();
    g_szInput = _T("");
    g_bShowTiShi = FALSE;

    TCHAR szFile [MAX_PATH];
    ::GetModuleFileName(g_hInstance, szFile, MAX_PATH);

    CFileEx fe;
    CString szTemp;
    fe.GetFilePath(szTemp);
    g_szPath = szTemp;
    g_szINIFile = szTemp + _T("\\");
    fe.GetFileTitle(szTemp);
    g_szINIFile += szTemp + _T(".INI");

    TCHAR szPrompt[MAX_BUFFER];
    GetPrivateProfileString(_T("Settings"), _T("PromptString"), _T(".."), szPrompt, MAX_BUFFER, g_szINIFile);
    g_szPrompt = szPrompt;
    GetPrivateProfileString(_T("Settings"), _T("UserPromptString"), _T(".>"), szPrompt, MAX_BUFFER, g_szINIFile);
    g_szUserPrompt = szPrompt;
    GetPrivateProfileString(_T("Settings"), _T("ListFile"), _T("List.txt"), szPrompt, MAX_BUFFER, g_szINIFile);
    g_szListFile = szPrompt;
    GetPrivateProfileString(_T("Settings"), _T("TempFile"), _T("TempList.txt"), szPrompt, MAX_BUFFER, g_szINIFile);
    g_szTempFile = szPrompt;
    GetPrivateProfileString(_T("Settings"), _T("ESCFunction"), _T("TRUE"), szPrompt, MAX_BUFFER, g_szINIFile);
    if(!_tcsicmp(szPrompt, _T("true")))
    {
        g_bESCFunction = TRUE;
    }
    else
    {
        g_bESCFunction = FALSE;
    } //结束 if(_tcscmp(szPrompt, _T("TRUE")))

    g_iScreenWidth = GetSystemMetrics(SM_CXFULLSCREEN);
    g_iScreenHeight = GetSystemMetrics(SM_CYFULLSCREEN);

    g_iListWidth = 200;
    g_iListHeight = 200;
    g_iEditWidth = g_iListWidth;
    g_iEditHeight = 55;

    g_hFont = CreateFont(12, 0, 0, 0, 0,
                         FALSE, FALSE, FALSE,
                         DEFAULT_CHARSET, DEFAULT_QUALITY,
                         DEFAULT_QUALITY, DEFAULT_QUALITY,
                         FIXED_PITCH + FF_SWISS, _T("宋体"));
    g_hSysList = CreateWindowEx(WS_EX_TOPMOST, _T("ListBox"),
                             _T("常量、宏自动提示器"),
                             WS_POPUP | WS_BORDER | WS_VSCROLL | LBS_SORT,
                             0, 0, g_iListWidth, g_iListHeight,
                             NULL, NULL,
                             g_hInstance, NULL);
    SendMessage(g_hSysList, WM_SETFONT, (WPARAM)g_hFont, 0);
    lpWndProc = (WNDPROC)SetWindowLong(g_hSysList, GWL_WNDPROC, (LONG)WindowProc);

    if(g_szUserPrompt != g_szPrompt)
    {
        g_hUserList = CreateWindowEx(WS_EX_TOPMOST, _T("ListBox"),
                                         _T("常量、宏自动提示器 - 用户数据"),
                     WS_POPUP | WS_BORDER | WS_VSCROLL | LBS_SORT,
                     0, 0, g_iListWidth, g_iListHeight,
                     NULL, NULL,
                     g_hInstance, NULL);
        SendMessage(g_hUserList, WM_SETFONT, (WPARAM)g_hFont, 0);
        //lpUserWndProc = (WNDPROC)SetWindowLong(g_hUserList, GWL_WNDPROC, (LONG)UserWindowProc);
        lpWndProc = (WNDPROC)SetWindowLong(g_hUserList, GWL_WNDPROC, (LONG)WindowProc);
    }
    else
    {
        g_hUserList = NULL;
    }//结束 if(m_szUserPrompt != m_szPrompt)

    g_hEditTip = CreateWindowEx(WS_EX_TOPMOST, _T("Edit"),
                            _T("显示隐藏字符串"),
                            WS_POPUP | WS_BORDER 
                            | ES_READONLY | ES_MULTILINE | ES_CENTER
                            | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
                            0, 200, g_iEditWidth, g_iEditHeight,
                            NULL, NULL,
                            g_hInstance, NULL);
    SendMessage(g_hEditTip, WM_SETFONT, (WPARAM)g_hFont, 0);

    g_szCopyRight = _T("常量、宏自动提示器 Ver:2005.6\r\n作者：康林\r\n时间：2005年06月13日\r\nE_Mail：kl222@126.com");
    g_hEdit = CreateWindowEx(WS_EX_TOPMOST, _T("Edit"),
                            g_szCopyRight,
                            WS_POPUP | WS_BORDER 
                            | ES_READONLY | ES_MULTILINE | ES_CENTER
                            | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
                            0, 200, g_iEditWidth, g_iEditHeight,
                            NULL, NULL,
                            g_hInstance, NULL);
    SendMessage(g_hEdit, WM_SETFONT, (WPARAM)g_hFont, 0);
    //lpEditWndProc = (WNDPROC)SetWindowLong(g_hEdit, GWL_WNDPROC, (LONG)EditWndProc);

    TRY
    {
        CStdioFile sf(g_szPath + _T("\\") + g_szListFile, CFile::modeRead);
        while(sf.ReadString(szTemp))
        {
            SendMessage(g_hSysList, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)szTemp);
        }
        sf.Close();
    }
    CATCH(CFileException, e)
    {
        
        MessageBox(NULL, _T("在目录： ") + g_szPath + _T(" 下找不到文件：") + g_szListFile + _T(" 。把此文件复制到此位置。"), _T("文件错误"), NULL);
    }
    END_CATCH

    return TRUE;
}

int CAutoDisplayConstOrMacroApp::ExitInstance()
{
    // TODO: 在此添加专用代码和/或调用基类
	TRACE(_T("%s(%d) : CAutoDisplayConstOrMacroApp::ExitInstance()\n"), __FILE__, __LINE__); 
    TRY
    {
        DestroyWindow(g_hEditTip);
        DestroyWindow(g_hSysList);
        if(g_hUserList)
        {
            DestroyWindow(g_hUserList);
        }
        DestroyWindow(g_hEdit);
		UnHook();
    }
    CATCH(CException, e)
    {
        TRACE(_T("%s(%d) : 关闭句柄出错\n"), __FILE__, __LINE__);  
    }
    END_CATCH 
    return CWinApp::ExitInstance();
}

/*******************************************************************************************************
函数名：ClearInput
描  述：清除前面的输入
参  数：
        int iCount：要清除的个数。为0时，全部清除。默认为0。
返回值：无
版  本：2005.6.0.0
作  者：康  林
时  间：2005-6-13 18:21:02
*******************************************************************************************************/
void ClearInput(int iCount)
{
    int iEnd;

    if(iCount == 0)
    {
        iEnd = g_szInput.GetLength() + g_szPrompt.GetLength();
    }
    else
    {
        iEnd = iCount;
    } //结束 if(iCount == 0)
    
    for(int i = 0; i < iEnd; i++)
    {
        keybd_event(VK_BACK, 0xFF, KEYEVENTF_EXTENDEDKEY, 0);
        keybd_event(VK_BACK, 0xFF, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);
    } //结束 for(int i = 0; i < iEnd; i++)
}

/*******************************************************************************************************
函数名：ShowTiShi
描  述：显示/隐藏提示框
参  数：
         BOOL bShow ：显示/隐藏提示框。默认为 TRUE。
                      TRUE：显示。
                      FALSE：隐藏。
         BOOL bClear：是否清除前面的输入。默认为 FALSE。
                      TRUE：清除。
                      FALSE：不清除。
返回值：无
版  本：2005.6.0.0
作  者：康  林
时  间：2005-6-13 16:58:45
*******************************************************************************************************/
void ShowTiShi(BOOL bShow, BOOL bClear)
{
    if(bShow)
    {
        if(!g_bShowTiShi)
        {
            //设置例表句柄
            if(g_szInput == g_szUserPrompt)
            {
                g_hList = g_hUserList;
            }
            if(g_szInput == g_szPrompt)
            {
                g_hList = g_hSysList;
            }
            int iIndex;
            iIndex = SendMessage(g_hList, LB_GETCURSEL, NULL, NULL);
            if(iIndex == LB_ERR)
            {
                SendMessage(g_hList, LB_SETCURSEL, 0, NULL);
            }
            g_bShowTiShi = TRUE;
            g_szInput = _T("");
            g_hWnd = GetFocus();
            //注意：下面的位置不能变
            MoveTiShi();
            ShowWindow(g_hList, SW_SHOW);
            ShowWindow(g_hEdit, SW_SHOW);
            SetFocus(g_hWnd);                    
        } //结束 if(!g_bShowTiShi)
    }
    else
    {
       if(g_bShowTiShi)
       {
           ShowWindow(g_hList, SW_HIDE);
           ShowWindow(g_hEditTip, SW_HIDE);
           ShowWindow(g_hEdit, SW_HIDE);
           SetFocus(g_hWnd);
           if(bClear)
           {
               ClearInput();
           } //结束 if(bClear)        
           g_bShowTiShi = FALSE;
       } //结束 if(g_bShowTiShi)
    } //结束 if(bShow)
}

/*******************************************************************************************************
函数名：MoveTiShi
描  述：移动提示框
参  数：无
返回值：无
版  本：2005.6.0.0
作  者：康  林
时  间：2005-6-13 16:58:03
*******************************************************************************************************/
void MoveTiShi()
{
    CPoint caret;
    CSize chSize;
    int top, left;

    //if(!IsWindowVisible(g_hList))
    //{
    //    return;
    //} //结束 if(!IsWindowVisible(g_hList))

    if(!g_bShowTiShi)
    {
        return;
    } //结束 if(g_bShowTiShi)
    //SetFocus(g_hWnd);
    GetCaretPos(&caret);
    ::ClientToScreen(g_hWnd, &caret);
    TRACE(_T("%s(%d) : %d,%d\n"), __FILE__, __LINE__, caret.x,caret.y);
    GetTextExtentPoint32(GetDC(g_hWnd), _T("a"), 1, &chSize);
    caret.Offset(chSize);
    if(caret.x + g_iListWidth > g_iScreenWidth)
    {
        left = caret.x - g_iListWidth;
    }
    else
    {
        left = caret.x;
    } //结束 if(caret.x + g_iListWidth > g_iScreenWidth)
    if(caret.y + g_iListHeight + g_iEditHeight > g_iScreenHeight)
    {
        top = caret.y - g_iListHeight - g_iEditHeight - chSize.cy;
    }
    else
    {
        top = caret.y;
    } //结束 if(caret.y + g_iListHeight + g_iEditHeight > g_iScreenHeight)

    g_iListLeft = left;
    g_iListTop = top;

    MoveWindow(g_hList, left, top, g_iListWidth, g_iListHeight, TRUE);
    MoveWindow(g_hEdit, left, top + g_iListHeight, g_iEditWidth, g_iEditHeight, TRUE);
    FindString();

}

/*******************************************************************************************************
函数名：FindString
描  述：在提示框中查找指定的字符串，并选择它。
参  数：无
返回值：无
版  本：2005.6.0.0
作  者：康  林
时  间：2005-6-14 10:34:50
*******************************************************************************************************/
void FindString()
{
    /*g_szInput =*/ g_szInput.MakeUpper();
    int iIndex = SendMessage(g_hList, LB_FINDSTRING, 0, (LPARAM)(LPCTSTR)g_szInput);
    if(iIndex != LB_ERR)
    {
        SendMessage(g_hList, LB_SELECTSTRING, 0, (LPARAM)(LPCTSTR)g_szInput);
    } //结束 if(iIndex != LB_ERR)
    ShowTip();
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
void ShowTip()
{
    TCHAR szReceive[MAX_BUFFER];
    int iIndex, iCur;
    iCur = SendMessage(g_hList, LB_GETCURSEL, NULL, NULL);
    if(iCur != LB_ERR)
    {
        iIndex = SendMessage(g_hList, LB_GETTEXT, iCur, (LPARAM)szReceive);
        if(iIndex != LB_ERR)
        {
            CSize size;
            CString sztemp(szReceive);
            //sztemp.TrimRight();
            GetTextExtentPoint32(GetDC(g_hList), sztemp, sztemp.GetLength(), &size);
            if(size.cx > g_iListWidth)
            {
                CRect rect;
                iIndex = SendMessage(g_hList, LB_GETITEMRECT, iCur, (LPARAM)&rect);
                if(iIndex != LB_ERR)
                {
                    int x, y;
                    CPoint topleft, caret;
                    topleft = rect.TopLeft();
                    ::ClientToScreen(g_hList, &topleft);

                    y = topleft.y;

                    CSize chSize;
                    GetCaretPos(&caret);
                    ::ClientToScreen(g_hWnd, &caret);
                    GetTextExtentPoint32(GetDC(g_hWnd), _T("a"), 1, &chSize);
                    caret.Offset(chSize);

                    if(caret.x <= g_iListLeft)
                    {
                        if(g_iListLeft + g_iListWidth + size.cx <= g_iScreenWidth)
                        {
                            x = g_iListLeft + g_iListWidth;
                        }
                        else
                        {
                            x = g_iListLeft - size.cx;
                        }//结束 if(g_iListLeft + g_iListWidth + size.cx <= g_iScreenWidth)
                    }
                    else
                    {
                        if(g_iListLeft - size.cx >= 0)
                        {
                            x = g_iListLeft - size.cx;
                        }
                        else
                        {
                            x = g_iListLeft + g_iListWidth;
                        } //结束 if(g_iListLeft - size.cx >= 0)
                    }

                    SetWindowText(g_hEditTip, sztemp);
                    MoveWindow(g_hEditTip, x, y, size.cx, size.cy + 1, TRUE);
                    ShowWindow(g_hEditTip, SW_SHOW);
                    SetFocus(g_hWnd);
                    return;
                }
            }
        } //结束 if(iIndex != LB_ERR)
    } //结束 if(iCur != LB_ERR)

    ShowWindow(g_hEditTip, SW_HIDE);
}

/*******************************************************************************************************
函数名：CopyString
描  述：把提示框中的字符复制到 IDE 中
参  数：
         TCHAR ch：输入的字符。默认为 NULL。不加。
返回值：
版  本：2005.6.0.0
作  者：康  林
时  间：2005-6-14 10:34:04
*******************************************************************************************************/
BOOL CopyString(TCHAR ch)
{
    TCHAR szReceive[MAX_BUFFER];
    int iIndex;
    iIndex = SendMessage(g_hList, LB_GETCURSEL, NULL, NULL);
    if(iIndex != LB_ERR)
    {
        iIndex = SendMessage(g_hList, LB_GETTEXT, iIndex, (LPARAM)szReceive);
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
    } //结束 if(SendMessage(g_hList, LB_GETCURSEL, NULL, NULL) != LB_ERR)

    return TRUE;
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
BOOL SetListPos(POSTION_ENUM pos)
{
    int iCur, iNum, iCount;
    iNum = 8;

    //------------------------------------------------------------------------
    //以下是完成 === 见 BUG-4 位置不能调换 === 功能的语句块
    //

    if(!(0x80 && GetAsyncKeyState(VK_MENU)))
    {
        //ShowTiShi(FALSE, FALSE);
        g_szInput = _T(""); //见 BUG-4
        return FALSE;
    } //结束 if(!(0x80 && GetAsyncKeyState(VK_MENU)))
    
    if(!g_bShowTiShi)
    {
        return FALSE;
    } //结束 if(!g_bShowTiShi)

    //
    //以上是完成 === 见 BUG-4 位置不能调换 === 功能的语句块
    //------------------------------------------------------------------------
           
    iCur = SendMessage(g_hList, LB_GETCURSEL, NULL, NULL);
    if(iCur == LB_ERR)
    {
        iCur = 0;
    } //结束 if(iIndex == LB_ERR)
    iCount = SendMessage(g_hList, LB_GETCOUNT, NULL, NULL);
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
    if(SendMessage(g_hList, LB_SETCURSEL, iCur, NULL) != LB_ERR)
    {
        ShowTip();
        return TRUE;
    }
    else
    {
        return FALSE;
    }//结束 if(SendMessage(g_hList, LB_SETCURSEL, iCur, NULL) != LB_ERR)
}

/*******************************************************************************************************
函数名：AddTempList
描  述：增加列表中的临时项
参  数：
        LPCTSTR lpszItem：要增加的项
返回值：类型为 BOOL 。成功返回TRUE，否则返回FALSE。
版  本：2005.6.0.1
作  者：康  林
时  间：2006年1月1日 12:36:16
*******************************************************************************************************/
extern "C" BOOL WINAPI AddTempList(LPCTSTR lpszItem)
{
    if(AddListItem(lpszItem))
    {
        TRY
        {
            CStdioFile sf(g_szPath + _T("\\") + g_szTempFile, CFile::modeCreate | CFile::modeReadWrite | CFile::modeNoTruncate);
            sf.SeekToEnd();
            sf.WriteString(lpszItem);
            sf.WriteString("\r\n");
            sf.Close();    
        }
        CATCH(CFileException, e)
        {
            TRACE(_T("%s(%d) : 文件错误\n"), __FILE__, __LINE__);
        }
        END_CATCH
        return TRUE;
    }

    return FALSE;
}

/*******************************************************************************************************
函数名：AddListItem
描  述：向例表中增加一项
参  数：
         LPCTSTR lpszItem：要增加的项
返回值：成功返回 TRUE,否则返回 FALSE
版  本：2005.6.0.0
作  者：康  林
时  间：2005-6-15 21:01:31
*******************************************************************************************************/
extern "C" BOOL WINAPI AddListItem(LPCTSTR lpszItem)
{
    ASSERT(lpszItem != NULL);
    SetListHand();
    int iIndex = SendMessage(g_hList, LB_FINDSTRINGEXACT, 0, (LPARAM)lpszItem);
    if(iIndex == LB_ERR)
    {
        iIndex = SendMessage(g_hList, LB_ADDSTRING, 0, (LPARAM)lpszItem);
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

/*******************************************************************************************************
函数名：DeleteTempList
描  述：删除例表中的临时项
参  数：无
返回值：
版  本：2005.6.0.0
作  者：康  林
时  间：2005-6-18 14:50:34
*******************************************************************************************************/
extern "C" BOOL WINAPI DeleteTempList()
{
    CString szTemp;
    TRY
    {
        CStdioFile sf(g_szPath + _T("\\") + g_szTempFile, CFile::modeRead);
        while(sf.ReadString(szTemp))
        {
            DeleteListItem(szTemp);
        } //结束 while(sf.ReadString(szTemp))
        sf.Close();
        sf.Remove(g_szPath + _T("\\") + g_szTempFile);
    }
    CATCH(CFileException, e)
    {
        TRACE(_T("%s(%d) : 文件错误\n"), __FILE__, __LINE__);
    }
    END_CATCH
    
    return FALSE;
}

/*******************************************************************************************************
函数名：DeleteListItem
描  述：删除例表中指定的字符串
参  数：
         LPCTSTR lpszItem：要删除的字符串
返回值：成功返回 TRUE,否则返回 FALSE
版  本：2005.6.0.0
作  者：康  林
时  间：2005-6-15 21:02:18
*******************************************************************************************************/
extern "C" BOOL WINAPI DeleteListItem(LPCTSTR lpszItem)
{
    ASSERT(lpszItem != NULL);
    SetListHand();    
    int iIndex = SendMessage(g_hList, LB_FINDSTRINGEXACT, 0, (LPARAM)lpszItem);
    if(iIndex == LB_ERR)
    {
        return FALSE;
    } //结束 if(iIndex == LB_ERR)
    if(SendMessage(g_hList, LB_DELETESTRING, iIndex, NULL) == LB_ERR)
    {
        return FALSE;
    } //结束 if(iIndex == LB_ERR)

    return TRUE;
}

/*******************************************************************************************************
函数名：SetListHand
描  述：设置例表的句柄
参  数：无
返回值：
版  本：2005.6.0.0
作  者：康  林
时  间：2005-6-16 22:47:07
*******************************************************************************************************/
BOOL SetListHand()
{
    if(NULL == g_hUserList)
    {
        g_hList = g_hSysList;
    }
    else
    {
        g_hList = g_hUserList;
    }
    return TRUE;
}

extern "C" BOOL WINAPI SetVCHook()
{
	return SetHook();
}

/*******************************************************************************************************
函数名：SetHook
描  述：设置键盘钩子
参  数：无
返回值：成功返回 TRUE,否则返回 FALSE
版  本：2005.6.0.0
作  者：康  林
时  间：2005-6-13 13:10:20
*******************************************************************************************************/
extern "C" BOOL WINAPI SetHook()
{
#ifdef __LIMIT__
#pragma message ("定义 __LIMIT__")
    
     AFX_MANAGE_STATE(AfxGetStaticModuleState());
     if(!Regist(FALSE, _T("微软开发环境工具集")))
     {
         return FALSE;
     } // 结束 if(!Regist(FALSE, _T("微软开发环境工具集")))
#endif // 结束 #ifdef __LIMIT__
	
	if(g_hKeyHook || g_hMsgHook)
    {
        return FALSE;
    } // 结束 if(g_hKeyHook || g_hMsgHook)
    g_hKeyHook = ::SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)KeyboardProc, g_hInstance, ::GetCurrentThreadId());
    g_hMsgHook = ::SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC)GetMsgProc, g_hInstance, ::GetCurrentThreadId());
    if(g_hKeyHook && g_hMsgHook)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    } //结束 if(g_hKeyHook)
}

/*******************************************************************************************************
函数名：UnHook
描  述：释放键盘钩子
参  数：无
返回值：成功返回 TRUE,否则返回 FALSE
版  本：2005.6.0.0
作  者：康  林
时  间：2005-6-13 13:10:58
*******************************************************************************************************/
extern"C" BOOL WINAPI UnHook()
{
#ifdef __LIMIT__
     AFX_MANAGE_STATE(AfxGetStaticModuleState());
     if(!Regist(FALSE, _T("微软开发环境工具集")))
     {
         return FALSE;
     } // 结束 if(!Regist(FALSE, _T("微软开发环境工具集")))
#endif // 结束 #ifdef __LIMIT__

    if(!(g_hMsgHook || g_hKeyHook))
    {
        return FALSE;
    } // 结束 if(!(g_hMsgHook || g_hKeyHook))
    BOOL ir;
    ir = UnhookWindowsHookEx(g_hMsgHook);
    if(UnhookWindowsHookEx(g_hKeyHook)&& ir)
    {
		g_hMsgHook = NULL;
		g_hKeyHook = NULL;
        return TRUE;
    } //结束 if(UnhookWindowsHookEx(g_hKeyHook))

    return FALSE;
}

/*******************************************************************************************************
函数名：KeyboardProc
描  述：键盘钩子处理函数
参  数：
         int nCode：指定是否需要处理该消息
         WPARAM wParam：虚拟键值
         LPARAM lParam：
返回值：
版  本：2005.6.0.0
作  者：康  林
时  间：2005-6-13 13:11:26
*******************************************************************************************************/
LRESULT CALLBACK KeyboardProc(int nCode,   //指定是否需要处理该消息
    WPARAM wParam,                         //虚拟键值
    LPARAM lParam
    )
{

    if(((DWORD)lParam & 0xC0000000) && (HC_ACTION == nCode))
    {
       switch(wParam) //键盘按键标识
       {
       case VK_BACK:
           if(g_szInput.GetLength() == 0 && g_bShowTiShi)
           {
               ShowTiShi(FALSE, FALSE);    
           }
           else
           {
               g_szInput.Delete(g_szInput.GetLength() - 1);
               MoveTiShi();
           }
           TRACE(_T("%s(%d) : BACK:g_szInput=%s\n"), __FILE__, __LINE__, g_szInput);
           break;
       case VK_ESCAPE:
           if(g_bESCFunction)
           {
               ShowTiShi(FALSE);
           }
           else
           {
               ShowTiShi(FALSE, FALSE);
               g_szInput = _T("");
           }//结束 if(g_bESCFunction)           
           break;
#ifdef __VCNET__
       case VK_OEM_4:
           //keybd_event(VK_OEM_6, 0xff, KEYEVENTF_EXTENDEDKEY, 0);
           //keybd_event(VK_OEM_6, 0xff, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);

           //if(!(0x80 && GetAsyncKeyState(VK_SHIFT)))
           //{
           //    keybd_event(VK_SHIFT, 0xff, KEYEVENTF_EXTENDEDKEY, 0);
           //   keybd_event(VK_SHIFT, 0xff, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);    
           //} //结束 if(!(0x80 && GetAsyncKeyState(VK_MENU)))       
           //keybd_event(VK_LEFT, 0xff, KEYEVENTF_EXTENDEDKEY, 0);
           //keybd_event(VK_LEFT, 0xff, KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP, 0);    
           break;
#endif
       case VK_SPACE:
           //ShowTiShi(FALSE);
           break;
       case VK_DOWN: //向下
           SetListPos(DOWN);
           break;
       case VK_UP: //向上
           SetListPos(UP);
           break;
       case VK_PRIOR:
           SetListPos(PAGEUP);
           break;
       case VK_NEXT:
           SetListPos(PAGEDOWN);
           break;
       case VK_HOME:
           SetListPos(HOME);
           break;
       case VK_END:
           SetListPos(END);
           break;
       default:
           break;
       }
       //TRACE(_T("%s(%d) : g_szInput=%s\n"), __FILE__, __LINE__, g_szInput);

     }
    
    return CallNextHookEx(g_hKeyHook, nCode, wParam, lParam);
}

/*******************************************************************************************************
函数名：GetMsgProc
功  能：处理消息钩子函数
参  数：
		int code：钩子代码
		WPARAM wParam： 移除标志
		LPARAM lParam：消息的地址
返回值：
作  者：康  林
版  本：2005.6.0.0
日  期：2004-12-5
时  间：14:46:42
*******************************************************************************************************/
LRESULT CALLBACK GetMsgProc(int nCode,        // hook code
							WPARAM wParam,  // 移除标志
							LPARAM lParam   // 消息的地址
							)
{
    MSG* pMsg = (MSG*) lParam;
    switch(pMsg->message)
    {		
    case WM_CHAR:
        {			
            if(PM_REMOVE == wParam)
            {
                switch(pMsg->wParam)
                {
                case 0x08:  // backspace 
                    break;
                case 0x1B:  // escape 
                    break;
                case '+':
                case '!':
                case '-':
                case '*':
                case '/':
                case '\\':
                case ';':
                case ':':
                case '(':                    
                case ')':                    
                case '[':
                case ']':
                case '{':
                case '}':
                case '&':
                case '%':
                case '>':
                case '<':
                case '=':
                case '.':
                case ',':
                case '?':
                case '~':
                case '|':
                case '^':
                case '\'':
                case '"':
                case 0x20:  // 空格
                    if(g_bShowTiShi)
                    {
                        ShowTiShi(FALSE);
                        ClearInput(1);
                        CopyString((TCHAR)pMsg->wParam);
                        break;
                    } //结束 if(g_bShowTiShi)
                default:
                    g_szInput += (TCHAR)pMsg->wParam;
                    MoveTiShi();
                    break;
                }

            }//if(PM_NOREMOVE == wParam)
        }

        if(g_szInput == g_szPrompt || g_szInput == g_szUserPrompt)
        {
            ShowTiShi();
        }
        else
        {
            if(g_szInput.GetLength() > g_szPrompt.GetLength() && !g_bShowTiShi)
            {
                g_szInput = g_szInput.Right(g_szInput.GetLength() - 1);
            } //结束 if(g_szInput.GetLength() > g_szPrompt.GetLength())
            if(g_szInput == g_szPrompt || g_szInput == g_szUserPrompt)
            {   
                ShowTiShi();
            } //结束 if(g_szInput == g_szPrompt)
        } //结束 if(g_szInput == g_szPrompt)

        //TRACE(_T("%s(%d) : WS_CHAR:g_szInput=%s\n"), __FILE__, __LINE__, g_szInput);
        break;
    default:
        break;		
    }

    LRESULT lresult;

    lresult= ::CallNextHookEx(g_hMsgHook, nCode, wParam, lParam);

    return lresult;
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
LRESULT CALLBACK WindowProc(HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
    )
{
    switch(uMsg)
    {
    case WM_LBUTTONDBLCLK:
        if(g_bShowTiShi)
        {
            SetFocus(g_hWnd);
            ShowTiShi(FALSE);
            CopyString();            
            break;
        } //结束 if(g_bShowTiShi) 
    case WM_LBUTTONUP:
        if(g_bShowTiShi)
        {
            ShowTip();
        }
        break;
    } //结束 switch(uMsg)
    return CallWindowProc(lpWndProc, hWnd, uMsg, wParam, lParam);
}

/*******************************************************************************************************
函数名：UserWindowProc
描  述：用户数据例表框架的消息处理过程
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
LRESULT CALLBACK UserWindowProc(HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
    )
{
    switch(uMsg)
    {
    case WM_LBUTTONDBLCLK:
        if(g_bShowTiShi)
        {
            ShowTiShi(FALSE);

            CopyString();
            break;
        } //结束 if(g_bShowTiShi) 
    case WM_LBUTTONUP:
        if(g_bShowTiShi)
        {
            ShowTip();
        }
        break;
    } //结束 switch(uMsg)
    return CallWindowProc(lpWndProc, hWnd, uMsg, wParam, lParam);
}

/*******************************************************************************************************
函数名：EditWndProc
描  述：版权Edit消息处理函数
参  数：
         HWND hWnd：
         UINT uMsg：
         WPARAM wParam：
         LPARAM lParam：
返回值：
版  本：2005.6.0.0
作  者：康  林
时  间：2005-6-14 21:13:50
*******************************************************************************************************/
LRESULT CALLBACK EditWndProc(HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
    )
{
    switch(uMsg)
    {
    case WM_PAINT:
        PAINTSTRUCT ps; 
        HDC hdc, hComDC;
        HBITMAP bmp;
        BITMAP bitmap;
  
        hdc = BeginPaint(hWnd, &ps);
        bmp = ::LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_KL));
        GetObject(bmp, sizeof(BITMAP), &bitmap);
        hComDC = ::CreateCompatibleDC(hdc);
        ::SelectObject(hComDC, bmp);

        BitBlt(hdc, 0, 0, bitmap.bmWidth, bitmap.bmHeight, hComDC, 0, 0,SRCCOPY);
        TextOut(hdc, 0, 0, g_szCopyRight, g_szCopyRight.GetLength());
        EndPaint(hWnd, &ps);        

        return 0L; 

        break;
    default:
        break;
    } //结束 switch(uMsg)
    return CallWindowProc(lpEditWndProc, hWnd, uMsg, wParam, lParam);
}
