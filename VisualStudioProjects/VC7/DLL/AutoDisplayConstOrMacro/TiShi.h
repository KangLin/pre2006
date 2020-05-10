/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：TiShi.h
描  述：消息处理没完成
版  本：2005.6.0.0
作  者：康  林
E_Mail：kl222@126.com
日  期：2005-6-16
时  间：15:13:18
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10
*******************************************************************************************************/
#pragma once

#define MAX_BUFFER 1024

// CTiShi

class CTiShi 
{
public:
	CTiShi();
	virtual ~CTiShi();
    CTiShi(HINSTANCE hInstance);

private:
    int m_iScreenWidth;     //屏幕宽度
    int m_iScreenHeight;    //屏幕高度
    int m_iTop;             //提示框的上边位置
    int m_iLeft;            //提示框的左边位置
    int m_iListWidth;       //例表宽度
    int m_iListHeight;      //例表高度
    int m_iEditWidth;       //版权信息框的宽度
    int m_iEditHeight;      //版权信息框的高度

    BOOL m_bShow;           //显示提示框

    WNDPROC lpWndProc;      //窗口处理函数

    // 初始化
    BOOL Inital(void);
    // 移动提示框
    BOOL MoveTiShi(void);
    // 显示Tip
    void ShowTip();
    
public:
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
    BOOL SetListPos(POSTION_ENUM pos);
    HINSTANCE m_hInstance;  //实例句柄
    HWND m_hParent;         //父窗口句柄
    HWND m_hList;           //例表句柄
    HWND m_hEditTip;        //显示Tip句柄
    HWND m_hEdit;           //版权信息句柄
    HFONT m_hFont;          //字体句柄

    CString m_szEditText;   //版权信息
    CString m_szListText;   //
    CString m_szFont;       //字体名
    
    // 设置实例句柄
    void SetInstance(HINSTANCE hInstance);
    // 增加例表项
    BOOL AddListItem(LPCTSTR lpszItem, BOOL bDirectness = FALSE);
    // 删除例表项
    BOOL DeleteListItem(LPCTSTR lpszItem);
    // 查找指定的字符串（不完全匹配）
    BOOL FindString(LPCTSTR lpszItem);
    // 复制字符串到 IDE
	virtual BOOL CopyString(TCHAR ch);
    // 设置版权信息
    BOOL SetCopyRightInfo(LPCTSTR lpszCopyRight);
    // 设置例表标题栏
    BOOL SetListText(LPCTSTR lpszText);
    // 显示/隐藏提示框
	BOOL ShowTiShi(bool bShow, HWND hParent = NULL);
	// 得到提示框是否显示
	BOOL Showed();

	static LRESULT CALLBACK WindowProc(HWND hWnd,
                                       UINT uMsg,
                                       WPARAM wParam,
                                       LPARAM lParam
                                       );
};


