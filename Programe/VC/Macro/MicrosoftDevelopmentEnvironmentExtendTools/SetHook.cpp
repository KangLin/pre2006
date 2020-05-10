#include "stdafx.h"

#include "SetHook.h"
#include "..\..\File\FileEx.h"
HHOOK g_hKeyHook = NULL; 
HHOOK g_hMsgHook = NULL; 
HINSTANCE g_hInstance = NULL; 

BOOL g_bAddBracket = FALSE;      //自动添加右边括号
BOOL g_bAutoFormatCCode = FALSE; //自动格式化 C 代码
CComPtr<IApplication> g_pApp;    //ADD_INS 对象实例
CString g_szInput=_T("");        //输入字符串
BOOL g_bErrorWarning = TRUE;     //错误提示
CString g_szINIFile = _T("MDEET.INI"); //配置文件
LONG g_nCurLine, g_nCurCol; //当前行、列

#define MAX_BUFFER 1024
void Init()
{
	CFileEx fe; 
	g_szINIFile = fe.GetFilePath() + _T("\\") + g_szINIFile; 
	TCHAR szPrompt[MAX_BUFFER];
    CString szTemp; 
	GetPrivateProfileString(_T("Settings"), _T("ErrorWarning"), _T("FALSE"), szPrompt, MAX_BUFFER, g_szINIFile);     
	szTemp = szPrompt; 
	szTemp.MakeLower(); 
	if(szTemp == _T("true"))
	{
		g_bErrorWarning = TRUE; 
	}
	else
	{
        g_bErrorWarning = FALSE; 
	} // 结束 if(szTemp == _T("true"))
	GetPrivateProfileString(_T("Settings"), _T("AutoFinishBracket"), _T("TRUE"), szPrompt, MAX_BUFFER, g_szINIFile); 
	szTemp = szPrompt; 
	szTemp.MakeLower(); 
	if(szTemp == _T("true"))
	{
		g_bAddBracket = TRUE; 
	}
	else
	{
        g_bAddBracket = FALSE; 
	} // 结束 if(szTemp == _T("false"))

}
extern "C" BOOL _stdcall SetKeyHook(IApplication* pApplication)
{
	Init();
	if(g_hKeyHook)
	{
		UnhookWindowsHookEx(g_hKeyHook);
	}
	if(g_hMsgHook)
    {
        UnhookWindowsHookEx(g_hMsgHook);
    } // 结束 if(g_hKeyHook || g_hMsgHook)
	
  	g_hInstance = ::AfxGetInstanceHandle(); 
	g_szInput = _T("");
	
	g_hKeyHook = ::SetWindowsHookEx(WH_KEYBOARD, (HOOKPROC)KeyboardProc, g_hInstance, ::GetCurrentThreadId());
    g_hMsgHook = ::SetWindowsHookEx(WH_GETMESSAGE, (HOOKPROC)GetMsgProc, g_hInstance, ::GetCurrentThreadId());
    if(g_hKeyHook && g_hMsgHook)
    {
		g_bAutoFormatCCode = TRUE; 
    }
    else
    {
        return FALSE;
    } //结束 if(g_hKeyHook && g_hMsgHook)

	if(g_pApp == NULL)
	{
		g_pApp = pApplication; 
		INITSEL(FALSE)
		g_nCurLine=GetLongProperty(pSel,_T("CurrentLine"));
		g_nCurCol=GetLongProperty(pSel,_T("CurrentColumn"));
		ENDSEL
	} // 结束 if(g_pApp == NULL)

	return TRUE;
}

extern "C" BOOL _stdcall UnKeyHook()
{
	if(g_hKeyHook || g_hMsgHook)
	{
		if(g_pApp)
		{
			g_pApp.Release(); 
			TRACE(_T("%s(%d) : g_pApp.Release()\n"), __FILE__, __LINE__);
		} // 结束 if(g_pApp)
		
		if((UnhookWindowsHookEx(g_hKeyHook)
			&& UnhookWindowsHookEx(g_hMsgHook)))
		{
			g_hKeyHook = NULL; 
			g_hMsgHook = NULL; 
			g_bAutoFormatCCode = FALSE; 
			return TRUE; 
		} //结束 if((UnhookWindowsHookEx(g_hKeyHook) && UnhookWindowsHookEx(g_hMsgHook)))
	} // 结束 if(g_hKeyHook || g_hMsgHook)
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
LRESULT CALLBACK KeyboardProc(int nCode,     //指定是否需要处理该消息
							  WPARAM wParam, //虚拟键值
							  LPARAM lParam
							  )
{
	
	LRESULT lresult;
	
    lresult =  CallNextHookEx(g_hKeyHook, nCode, wParam, lParam);
		
    if(((DWORD)lParam & 0xC0000000) && (HC_ACTION == nCode))
    {
		INITSEL(lresult); 
		LONG nCurLine = GetLongProperty(pSel, _T("CurrentLine")); 
		LONG nCurCol = GetLongProperty(pSel, _T("CurrentColumn")); 
		ENDSEL
			
		if(nCurLine == g_nCurLine && nCurCol == g_nCurCol)
		{
			
			return lresult; 
		} // 结束 if(nCurLine == g_nCurLine && nCurCol == g_nCurCol)
        g_nCurLine = nCurLine; 
		g_nCurCol = nCurCol; 

		switch(wParam) //键盘按键标识
		{
		case VK_BACK:
		case VK_DELETE:
			g_szInput += wParam;
			break;
		case VK_ESCAPE:
			break;
#ifdef __VCNET__
		case VK_OEM_4:
			break;
#endif
		case VK_SPACE:
			break; 
		case VK_RETURN:
			EntryEvents(); 
			g_szInput.Empty(); 
			break;
		case VK_DOWN: //向下
			if(g_szInput.GetLength() > 0)
			{
				KeyDownEvents(); 
			}
			g_szInput.Empty(); 
			break;
		case VK_UP: //向上
			g_szInput.Empty(); 
			break; 
		case VK_LEFT:
			break; 
		case VK_RIGHT:
			break;
		case VK_PRIOR:
			g_szInput.Empty();
			break;
		case VK_NEXT:
			g_szInput.Empty();
			break;
		case VK_HOME:
			break;
		case VK_END:		   
			break;
		default:
			break;
		}
	}
    
    return lresult;
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
                case 0x1B:  // escape 
                    break;
				case _T('('):
				case _T('['):
				case _T('{'):
				case _T('\''):
				case _T('\"'):
					AddBracket((TCHAR)pMsg->wParam);
                case 0x08:  // backspace
                default:
                    g_szInput += (TCHAR)pMsg->wParam;
                    break;
                }
				
            } // 结束 if(PM_NOREMOVE == wParam)
        }
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
函数名：AddBracket
功  能：完成右边的括号
参  数：
TCHAR ch：
返回值：
作  者：康  林
版  本：4.0.0.0
日  期：2005-7-8
时  间：18:31:36
*******************************************************************************************************/
int AddBracket(TCHAR ch)
{
	if(!g_bAddBracket)
	{
		return 0;
	}
	TCHAR c[2];
	c[1] = 0;
	switch(ch)
	{
	case _T('('):
		c[0] = _T(')');
		break;
	case _T('['):
		c[0] = _T(']');
		break;
	case _T('{'):
		c[0] = _T('}');
		break; 
	case _T('\''):
		c[0] = _T('\''); 
		break; 
	case _T('\"'):
		c[0] = _T('\"'); 
		break; 
	}
	INITSEL(0)
		
	COleVariant var; 
	GetProperty(g_pApp, _T("Active"), var); 
	if(var == COleVariant((long)1, VT_BOOL))
	{
		PutDispatchProperty(pSel, _T("Text"), c);
		InvokeMethod(pSel, _T("CharLeft"));
	} // 结束 if(var == COleVariant((long)1, VT_BOOL))
	ENDSEL
}

/*******************************************************************************************************
函数名：KeyDownEvents
功  能：键盘向下事件
参  数：无
返回值：
作  者：康  林
版  本：4.0.0.0
日  期：2005-7-9
时  间：7:08:26
*******************************************************************************************************/
int KeyDownEvents()
{
	if(!g_bAutoFormatCCode)
	{
		return 0; 
	} // 结束 if(!g_bAutoFormatCCode)
	INITSEL(0)
	
	LONG iLine, iCur, iCol, iCurCol; 
    iCol = GetLongProperty(pSel, _T("CurrentColumn")); 
    iLine = GetLongProperty(pSel, _T("CurrentLine")); 

	InvokeMethod(pSel, _T("LineUp"));
	InvokeMethod(pSel, _T("SelectLine"));	
	CString szText;
	szText = GetStringProperty(pSel, _T("Text"));
	TRACE(_T("%s(%d) : %s, szText = 长度=%d\n"), __FILE__, __LINE__, szText, szText.GetLength());
	LPTSTR lpszOut = new TCHAR[szText.GetLength() * 4 + sizeof(TCHAR)];
	::memset(lpszOut, 0, szText.GetLength() * 4 + sizeof(TCHAR));
	FormatVCCodeA(szText, lpszOut);
    PutDispatchProperty(pSel, _T("Text"), lpszOut);
	//InsertText(lpszOut);
    delete []lpszOut;
	iCur = GetLongProperty(pSel, _T("CurrentLine")); 
	iCurCol = GetLongProperty(pSel, _T("CurrentColumn")); 
	
	//修改结束块的注释
	ModifyEndBracketComment(szText, iLine - 1); 
	
	InvokeMethod2(pSel, _T("MoveTo"), COleVariant(iCur), COleVariant(iCurCol)); 
	long i = iCur;	//因为已包含了换行符
	while(iCur >= iLine && iCur != 1)
	{
		InvokeMethod1(pSel, _T("LineUp"), COleVariant((long)1));
		iCur = GetLongProperty(pSel, _T("CurrentLine"));
	}
	//格式化新加入的内容
	InvokeMethod1(g_pApp, _T("ExecuteCommand"), _T("SelectionFormat"));
	InvokeMethod2(pSel, _T("MoveTo"), COleVariant(i), COleVariant(iCol)); 

	ENDSEL
}

/*******************************************************************************************************
函数名：ModifyEndBracketComment
功  能：修改结束块后的注释
参  数：
         LPCTSTR lpszCode：代码
         LONG iLine：当前行
返回值：
作  者：康  林
版  本：4.0.0.0
日  期：2005-7-10
时  间：8:51:19
*******************************************************************************************************/
int ModifyEndBracketComment(LPCTSTR lpszCode, LONG iLine)
{
	INITSEL(0)
	LONG iCur = GetLongProperty(pSel, _T("CurrentLine"));

    CString szText = _T("");
	LPTSTR lpTemp = new TCHAR[_tcslen(lpszCode) + sizeof(TCHAR)];
	ValidCCodeA(lpszCode, lpTemp, FALSE);
	
	if(_tcsstr(lpTemp, _T("if(")))
	{
		szText = _T("if(");
	} // 结束 if(_tcsstr(lpTemp, _T("if(")))
	if(_tcsstr(lpTemp, _T("for(")))
	{
		szText = _T("for("); 
	} // 结束 for(_tcsstr(lpTemp, _T("for(")))
	if(_tcsstr(lpTemp, _T("while(")))
	{
		szText = _T("while("); 
	} // 结束 while(_tcsstr(lpTemp, _T("while(")))
	if(_tcsstr(lpTemp, _T("switch(")))
	{
		szText = _T("switch("); 
	} // 结束 switch(_tcsstr(lpTemp, _T("switch(")))
	if(szText != _T(""))
	{
		InvokeMethod1(pSel, _T("GotoLine"), COleVariant(iLine)); 
		InvokeMethod(pSel, _T("SelectLine")); 
		CString szTemp = GetStringProperty(pSel, _T("Text"));
		delete []lpTemp;
		lpTemp = new TCHAR[szTemp.GetLength() + sizeof(TCHAR)];
		ValidCCodeA(szTemp, lpTemp, FALSE);
		LONG iPos = 0;
ModifyEndBracketComment_Loop:
		while(!(MatchSplitSymbol(lpTemp, _T("{"), _T("}")) > 0))
		{
			iPos++; 			
			InvokeMethod1(pSel, _T("GotoLine"), COleVariant(iLine + iPos));
			if(iPos + iLine > GetLongProperty(pSel, _T("CurrentLine")))
			{
				//测试:到文档结束时还没找到, 是否自动结束
				break;
			} // 结束 if(iPos > GetLongProperty(pSel, _T("BottomLine")))
			InvokeMethod(pSel, _T("SelectLine"));			
			szTemp += GetStringProperty(pSel, _T("Text"));
			delete []lpTemp;
			lpTemp = new TCHAR[szTemp.GetLength() + sizeof(TCHAR)]; 
			ValidCCodeA(szTemp, lpTemp, FALSE); 
		} // 结束 while(!(MatchSplitSymbol(lpTemp, _T("{"), _T("}")) > 0))
		
		szTemp = GetStringProperty(pSel, _T("Text"));
		if(szTemp.Find(_T("结束")) != -1)
		{
			LONG iCur = GetLongProperty(pSel, _T("CurrentLine"));

			InvokeMethod1(pSel, _T("GotoLine"), COleVariant(iLine));
			InvokeMethod(pSel, _T("SelectLine"));
			szTemp = GetStringProperty(pSel, _T("Text"));
			ValidCCodeA(szTemp, lpTemp); 
			LONG iPos = 0;
			while(!(MatchSplitSymbolC(lpTemp, _T("("), _T(")"), NULL, NULL, TRUE) > 0))
			{
				iPos++;
				InvokeMethod1(pSel, _T("GotoLine"), COleVariant(iLine + iPos));
				if(iLine + iPos > GetLongProperty(pSel, _T("CurrentLine")))
				{
					break;
				} // 结束 if(iLine + iPos > GetLongProperty(pSel, _T("BottomLine")))
				
				InvokeMethod(pSel, _T("SelectLine"));
				CString szSur = GetStringProperty(pSel, _T("Text")); 
				szTemp += szSur; 
				delete []lpTemp;
				lpTemp = new TCHAR[szTemp.GetLength() + sizeof(TCHAR)]; 
				ValidCCodeA(szTemp, lpTemp); 
			} // 结束 while(!(MatchSplitSymbolC(lpTemp, _T("("), _T(")"), NULL, NULL, TRUE) > 0))

			InvokeMethod1(pSel, _T("GotoLine"), COleVariant(iCur));
			InvokeMethod(pSel, _T("StartOfLine")); 
			COleVariant bEnd; 
			InvokeMethod1(pSel, _T("FindText"), _T("结束"), bEnd); 
			if(bEnd == COleVariant((short)1, VT_BOOL))
			{
				InvokeMethod1(pSel, _T("EndOfLine"), COleVariant((long)1));
				szText = _T("结束 ") + szText + lpTemp;
				szText += _T(")");
				PutDispatchProperty(pSel, _T("Text"), szText);	
			} // 结束 if(pSel, _T( ), COleVariant((long)1))
		}
		else
		{
			iPos++;
			InvokeMethod1(pSel, _T("GotoLine"), COleVariant(iLine + iPos));
			InvokeMethod(pSel, _T("SelectLine"));
			CString szStr = GetStringProperty(pSel, _T("Text"));
			if(szStr.Find(_T("else")) != -1 
				&& (iLine + iPos <= GetLongProperty(pSel, _T("BottomLine"))))
			{
				szTemp = GetStringProperty(pSel, _T("Text"));
				delete []lpTemp;
				lpTemp = new TCHAR[szTemp.GetLength() + sizeof(TCHAR)];
				ValidCCodeA(szTemp, lpTemp, FALSE); 
				goto ModifyEndBracketComment_Loop;
			}			
		} // 结束 if(szTemp.Find(_T("结束")) != -1)
	} // 结束 if(szText != _T(""))
	delete []lpTemp;
	ENDSEL
}

/*******************************************************************************************************
函数名：EntryEvents
功  能：回车事件
参  数：无
返回值：
作  者：康  林
版  本：4.0.0.0
日  期：2005-7-9
时  间：7:02:49
*******************************************************************************************************/
int EntryEvents()
{
	if(!g_bAutoFormatCCode)
	{
		return 0; 
	} // 结束 if(!g_bAutoFormatCCode)
	
    INITSEL(0)
	LONG iLine, iCur, iCol;
	
    iLine = GetLongProperty(pSel, _T("CurrentLine"));
	iCol = GetLongProperty(pSel, _T("CurrentColumn"));
	InvokeMethod(pSel, _T("LineUp"));
	InvokeMethod(pSel, _T("SelectLine"));
	CString szText;
	szText = GetStringProperty(pSel, _T("Text"));
	LPTSTR lpszOut = new TCHAR[szText.GetLength() * 4 + sizeof(TCHAR)];
	ValidCCodeA(szText, lpszOut);
	szText.Delete(szText.GetLength(), 2);
	TRACE(_T("szText = %s(%d) : %s长度=%d\n"), __FILE__, __LINE__, szText, szText.GetLength());
	delete []lpszOut;
    lpszOut = new TCHAR[szText.GetLength() * 4 + sizeof(TCHAR)];
	::memset(lpszOut, 0, szText.GetLength() * 4 + sizeof(TCHAR));
	FormatVCCodeA(szText, lpszOut);
	CString szTemp = lpszOut;
    PutDispatchProperty(pSel, _T("Text"), lpszOut);
	//InsertText(lpszOut);
    delete []lpszOut;
	iCur = GetLongProperty(pSel, _T("CurrentLine"));
	//自动增加括号
	if(AutoAddBracket(szText))
	{
		PutDispatchProperty(pSel, _T("Text"), _T("{\r\n"));
	}
	else
	{
		if(szTemp.Right(4) == _T("\r\n\r\n"))
		{
			InvokeMethod(pSel, _T("SelectLine"));
			InvokeMethod1(pSel, _T("LineUp"), COleVariant((long)1));
			PutDispatchProperty(pSel, _T("Text"), _T(""));
		}
	}
	iCur = GetLongProperty(pSel, _T("CurrentLine"));
	//增加右大括号
	LONG iEndLine = AddRightBracket();

	InvokeMethod1(pSel, _T("GoToLine"), COleVariant((long)(iEndLine + 10)));
	InvokeMethod1(pSel, _T("GoToLine"), COleVariant(iEndLine));
	InvokeMethod(pSel, _T("EndOfLine"));
	int i = GetLongProperty(pSel, _T("CurrentLine"));
	while( i >= iLine && i != 1)
	{
		InvokeMethod1(pSel, _T("LineUp"), COleVariant((long)1));
		i = GetLongProperty(pSel, _T("CurrentLine"));
	}
	//格式化新加入的内容
	InvokeMethod1(g_pApp, _T("ExecuteCommand"), _T("SelectionFormat"));
	InvokeMethod1(pSel, _T("GoToLine"), COleVariant(iCur));
	InvokeMethod(pSel, _T("SelectLine"));
	szText = GetStringProperty(pSel, _T("Text"));
	if(szText == _T("\r\n"))
	{
		InvokeMethod1(pSel, _T("CharLeft"), COleVariant((long)1));
		InvokeMethod(pSel, _T("NewLine"));
	}
	else
	{
		InvokeMethod2(pSel, _T("MoveTo"), COleVariant(iCur), COleVariant(iCol));
	}

	ENDSEL
		return 1;
}

/*******************************************************************************************************
函数名：AutoAddBracket
功  能：自动增加左括号
参  数：无
返回值：
作  者：康  林
版  本：4.0.0.0
日  期：2005-7-8
时  间：18:33:18
*******************************************************************************************************/
LONG AutoAddBracket(LPCTSTR lpszText)
{
	LONG iReturn = 0;
	INITSEL(0)

	CString szText(lpszText);
	LPTSTR lpTemp;
	lpTemp = new TCHAR[szText.GetLength() + sizeof(TCHAR)];
	ValidCCodeA(szText, lpTemp, FALSE);
	szText = lpTemp;
	delete []lpTemp;
	if(szText.Right(1) == _T(")"))
	{
		InvokeMethod1(pSel, _T("StartOfDocument"), COleVariant((LONG)1));
		szText = GetStringProperty(pSel, _T("Text"));
		InvokeMethod(pSel, _T("CharRight"));
		lpTemp = new TCHAR[szText.GetLength() + sizeof(TCHAR)];
		ValidCCodeA(szText, lpTemp, FALSE);
		LPTSTR lpBefor = new TCHAR[szText.GetLength() + sizeof(TCHAR)];
		if(ReversionMatchSplitSymbol(lpTemp, _T("("), _T(")"), lpBefor) > 0)
		{
			_tcsrev(lpBefor);
			szText = lpBefor;
			_tcscpy(lpBefor, szText.Left(szText.Find(_T(" "))));
			_tcsrev(lpBefor);
			if(!_tcscmp(lpBefor, _T("if"))
				|| !_tcscmp(lpBefor, _T("while"))
				|| !_tcscmp(lpBefor, _T("for"))
				|| !_tcscmp(lpBefor, _T("switch"))
				)
			{
				
				iReturn = 1;
			}
		}
		delete []lpTemp;
		delete []lpBefor;
	}
	
	ENDSEL

	return iReturn;
}

/*******************************************************************************************************
函数名：AddRightBracket
功  能：增加右边大括号
参  数：无
返回值：增加后的插入点的位置
作  者：康  林
版  本：4.0.0.0
日  期：2005-7-8
时  间：18:30:50
*******************************************************************************************************/
LONG AddRightBracket()
{
	INITSEL(0)
	LONG iCur = GetLongProperty(pSel, _T("CurrentLine"));
	//是否添加右大括号
	InvokeMethod(pSel, _T("SelectAll"));
	CString szText = GetStringProperty(pSel, _T("Text")); 
	TCHAR * lpszTemp = new TCHAR[szText.GetLength() + sizeof(TCHAR)]; 
	TCHAR * lpszBack = new TCHAR[szText.GetLength() + sizeof(TCHAR)]; 
	ValidCCodeA(szText, lpszTemp, FALSE);
	int i;
	while(1)
	{
		while((i = MatchSplitSymbol(lpszTemp, _T("{"), _T("}"), NULL, lpszBack)) > 0)
		{
			_tcscpy(lpszTemp, lpszBack);
		}
		if(i < 0)
		{
			//不匹配
			CString szCrLf; 
			if(i == -2)
			{
				szCrLf += _T("\r\n}");
			}
			else
			{
				TRACE(_T("%s(%d) : 却少左大括号\n"), __FILE__, __LINE__);
#ifndef _DEBUG
#pragma message("已编译：文件中却少左大括号，已自动添加一个，请检查是否正确。")
				if(g_bErrorWarning)
				{
					MessageBox(NULL, _T("文件中却少左大括号，已自动添加一个，请检查是否正确。"),
						_T("警告"), MB_OK | MB_ICONWARNING);
				}
#endif
				szCrLf += _T("{\r\n");
			}
			InvokeMethod1(pSel, _T("GoToLine"), COleVariant(iCur));
			InvokeMethod(pSel, _T("EndOfLine"));
			PutDispatchProperty(pSel, _T("Text"), szCrLf);
			iCur = GetLongProperty(pSel, _T("CurrentLine"));
			
			//增加结束块的注释
			AddEndBracketComment();
			
			InvokeMethod(pSel, _T("SelectAll"));
			szText = GetStringProperty(pSel, _T("Text"));
			delete []lpszTemp;
			delete []lpszBack;
			lpszTemp = new TCHAR[szText.GetLength() + sizeof(TCHAR)];
			lpszBack = new TCHAR[szText.GetLength() + sizeof(TCHAR)];
			ValidCCodeA(szText, lpszTemp, FALSE);			
		}
		else
		{			
			break;
		}
	}
	
	delete []lpszBack;
	delete []lpszTemp;
	ENDSEL
		return iCur;
}

/*******************************************************************************************************
函数名：AddEndBracketComment
功  能：增加结束块的注释
参  数：无
返回值：
作  者：康  林
版  本：4.0.0.0
日  期：2005-7-9
时  间：6:40:16
*******************************************************************************************************/
int AddEndBracketComment()
{
	INITSEL(0)
	LONG iCur = GetLongProperty(pSel, _T("CurrentLine"));

	InvokeMethod1(pSel, _T("StartOfDocument"), COleVariant((LONG)1));
	
	CString szText = GetStringProperty(pSel, _T("Text"));
	InvokeMethod(pSel, _T("CharRight"));
	LPTSTR lpTemp = new TCHAR[szText.GetLength() + sizeof(TCHAR)];
	ValidCCodeA(szText, lpTemp);
	LPTSTR lpBefor = new TCHAR[szText.GetLength() + sizeof(TCHAR)];
	if(ReversionMatchSplitSymbol(lpTemp, _T("{"), _T("}"), lpBefor, NULL, TRUE) > 0)
	{
		CString szT = lpBefor;
		szT.TrimRight();
		if(szT.Right(1) == _T(")"))
		{			
			ValidCCodeA(lpBefor, lpTemp);
			if(ReversionMatchSplitSymbol(lpTemp, _T("("), _T(")"), lpBefor, NULL, TRUE) > 0)
			{
				CString szTemp(_T("("));
				szTemp += lpTemp;
				szTemp += _T(")");
				_tcsrev(lpBefor);
				szText = lpBefor;
				_tcscpy(lpBefor, szText.Left(szText.Find(_T(" "))));
				_tcsrev(lpBefor);
				if(!_tcscmp(lpBefor, _T("if"))
					|| !_tcscmp(lpBefor, _T("while"))
					|| !_tcscmp(lpBefor, _T("for"))
					|| !_tcscmp(lpBefor, _T("switch"))
					)
				{
					szTemp = lpBefor + szTemp;
					//InvokeMethod1(pSel, _T("GoToLine"), COleVariant(iCur));
					//InvokeMethod(pSel, _T("EndOfLine"));
					PutDispatchProperty(pSel, _T("Text"), _T(" // 结束 ") + szTemp);
				}
			}
		}
	}
	delete []lpTemp;
	delete []lpBefor;
	
	ENDSEL
	return 0;
}

int InsertText(LPCTSTR lpszText)
{
	INITSEL(0)
		CString szCrLf(CR);
	szCrLf += LF;
	TCHAR *lpPos, *lpSur;
	TCHAR *lpTemp = new TCHAR[ _tcslen(lpszText) + sizeof(TCHAR) ];
	lpSur = (LPTSTR)lpszText;
	lpPos = _tcsstr(lpSur, szCrLf);
	while(lpPos)
	{
		memcpy(lpTemp, lpSur, lpPos - lpSur);
		(TCHAR)*(lpTemp + (lpPos - lpSur)) = 0;
		CString sz(lpTemp);
		sz.TrimLeft();
		PutDispatchProperty(pSel, _T("Text"), lpTemp);
		lpSur = lpPos + 2;
		if(NULL != lpSur)
		{
			InvokeMethod(pSel, _T("NewLine"));
		}
		lpPos = _tcsstr(lpSur, szCrLf);
	}
	if(NULL != *lpSur && szCrLf != *lpSur)
	{
		PutDispatchProperty(pSel, _T("Text"), lpSur);
	}
	delete []lpTemp;
	ENDSEL
}

