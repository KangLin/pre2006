/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：AutoDisplayConstOrMacro.h
描  述：常量、宏自动提示器头文件
版  本：1.0.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2005-6-14
时  间：14:43:10
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10
*******************************************************************************************************/
// AutoDisplayConstOrMacro.h : AutoDisplayConstOrMacro DLL 的主头文件
//
#if !defined(__KL_AUTODISPLAYMACROORCONST_H__521BE306_5FBC_4693_B266_92166DA83CD1__INCLUDED__1976121__)
#define __KL_AUTODISPLAYMACROORCONST_H__521BE306_5FBC_4693_B266_92166DA83CD1__INCLUDED__1976121__

#pragma once

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// 主符号
#include "Export.h"

// CAutoDisplayConstOrMacroApp
// 有关此类实现的信息，请参阅 AutoDisplayConstOrMacro.cpp
//

class CAutoDisplayConstOrMacroApp : public CWinApp
{
public:
	CAutoDisplayConstOrMacroApp();

// 重写
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
    virtual int ExitInstance();
};

//设置显示框的句柄
BOOL SetListHand();
//显示\隐藏窗口
void ShowTiShi(BOOL bShow = TRUE, BOOL bClear = TRUE);
//移动提示窗口
void MoveTiShi();
//清除前面的输入
void ClearInput(int iCount = 0);
//在例表框中查找指定的字符串
void FindString();
//显示Tip
void ShowTip();
//把例表框中的字符串复制到IDE中
BOOL CopyString(TCHAR ch = NULL);
//键盘控制常量
enum POSTION_ENUM
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    PAGEUP,
    PAGEDOWN,
    HOME,
    END
};
//移动例表框中的选择项
BOOL SetListPos(POSTION_ENUM pos);

//键盘钩子处理函数
LRESULT CALLBACK KeyboardProc(int nCode, /*指定是否需要处理该消息*/
    WPARAM wParam,
    LPARAM lParam
    );
//消息钩子处理函数
LRESULT CALLBACK GetMsgProc(
  int nCode,      // hook code
  WPARAM wParam,  // removal flag
  LPARAM lParam   // address of structure with message
);

//例表框消息处理函数
LRESULT CALLBACK WindowProc(HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
    );
//用户数据例表框消息处理函数
LRESULT CALLBACK UserWindowProc(HWND hwnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
);
//版权Edit消息处理函数
LRESULT CALLBACK EditWndProc(HWND hWnd,
    UINT uMsg,
    WPARAM wParam,
    LPARAM lParam
    );

#endif // 结束 #if !defined(__KL_AUTODISPLAYMACROORCONST_H__521BE306_5FBC_4693_B266_92166DA83CD1__INCLUDED__1976121__)