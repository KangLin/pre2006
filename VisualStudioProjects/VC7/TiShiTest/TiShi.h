#ifndef __TISHI_H__
#define __TISHI_H__

#pragma once

typedef int(*EnterFun)(LPCTSTR lpcszText);
typedef void(*KeyPressFun)(UINT nChar, UINT nRepCnt, UINT nFlags);
/*******************************************************************************************************
函数名：ShowTipFun
描  述：回调函数，此回调函数由 ShowTip 调用。
参  数：
        UINT nIndex：选择条目的索引号。
		LPCTSTR lpcszText：选择条目的内容。
		LPTSTR* lpszInText：此回调函数完成后返回给程序的字符串（也就是要在帮助提示框中提示的文本）。
		                    回调函数只要分配内存，ShowTip 会负责释放内存的。
返回值：类型为 int 。成功返回 0，错误返回非零。
*******************************************************************************************************/
typedef int(*ShowTipFun)(UINT nIndex, LPCTSTR lpcszText, LPTSTR* lpszInText);

// CTiShi

class CTiShi : public CListBox
{
	DECLARE_DYNAMIC(CTiShi)

public:
	CTiShi();
	virtual ~CTiShi();

protected:
	DECLARE_MESSAGE_MAP()

private:
	CEdit m_Edit;               //版权信息提示框
	CEdit m_edTip;              //对选定项的注释框

	CFont m_Font;               //字体

	int m_iScreenWidth;         //屏幕宽度
    int m_iScreenHeight;        //屏幕高度
    int m_iTop;                 //提示框的上边位置
    int m_iLeft;                //提示框的左边位置
	int m_iListWidth;           //条目提示框的宽度
	int m_iListHeight;          //条目提示框的高度
    int m_iEditWidth;           //版权信息框的宽度
    int m_iEditHeight;          //版权信息框的高度

	BOOL m_bShow;               //提示框是否显示
	BOOL m_bVerTiShi;           //是否显示版权信息提示框
	HWND m_hParent;             //父窗口的句柄

	EnterFun m_EnterFun;        //当条目提示框选择按确定键选择时的回调函数
	KeyPressFun m_KeyPressFun;  //处理键盘消息回调函数
	ShowTipFun m_ShowTipFun;    //显示条目提示框帮助提示框前的回调函数

protected:
	CString m_szInput;    //输入字符串

public:
	// 设置字体
	int SetFont(LPCTSTR lpszFacename = _T("宋体"),
		        int nHeight = 12,
				int nWidth = 0,
				int nEscapement = 0,
				int nOrientation = 0,
				int nWeight = 0,
				BYTE bItalic = FALSE,
				BYTE bUnderline = FALSE,
				BYTE cStrikeOut = FALSE,
				BYTE nCharSet = DEFAULT_CHARSET,
				BYTE nOutPrecision = DEFAULT_QUALITY,
				BYTE nClipPrecision = DEFAULT_QUALITY,
				BYTE nQuality = DEFAULT_QUALITY,
				BYTE nPitchAndFamily = FIXED_PITCH + FF_SWISS
				);
	int SetFont(CFont * pFont);
	// 移动提示框
	BOOL Move(LPCTSTR lpszText);
	BOOL Move(TCHAR ch);
	BOOL Move(UINT nCh);
	BOOL Move(void);
	// 显示提示框
	BOOL Show(HWND hParent, BOOL bShow = TRUE, LPCTSTR lpcszInput = NULL);
	// 显示选择项的注释框 Tip
	int ShowTip(LPCTSTR lpszText);

	// 设置版权信息,此信息显示在版权信息提示框中
	int SetCopyRight(LPCTSTR lpszCopyRight);
	int ShowCopyRight(BOOL bShow);

	// 得到条目提示框中选项择的文本
	virtual CString GetString(void);

	BOOL RegisterEnterFun(EnterFun fun);
	BOOL RegisterKeyPress(KeyPressFun fun);
	BOOL RegisterShowTip(ShowTipFun fun);
	
	virtual BOOL CreateEx(HWND hParent = NULL);

	//事件
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);

protected:
	// 鼠标左击事件
	virtual void OnLeftButtonEvents(LPCTSTR lpszText);	
	// 键盘事件
	virtual void OnKeyEvents(UINT nChar, LPCTSTR lpszText);
	// Enter 键事件
	virtual void OnEnter(LPCTSTR lpszText);

	// 查找字符串
	virtual int FindText();
	virtual int FindText(LPCTSTR lpcszText);

public:
	// 从文件中加载数据
	virtual int LoadString(LPCTSTR lpszFileName);
	
	//------------------------------------------------------------------------
	//以下是完成 === ToolTip === 功能的语句块
	//
private:
	CToolTipCtrl m_ToolTip;
	void InitToolTip();
public:
	BOOL SetToolTipText(int nText, BOOL bActivate = TRUE);
	BOOL SetToolTipText(LPCSTR lpszText, BOOL bActivate = TRUE);
	virtual BOOL PreTranslateMessage(MSG * pMsg);
	//
	//以上是完成 === ToolTip === 功能的语句块
	//------------------------------------------------------------------------

protected:
	// 得到指定字体的大小
	int GetFontSize(HWND hWnd, LPCTSTR lpszText, LPSIZE lpSize);
};

#endif // 结束 #ifdef __TISHI_H__