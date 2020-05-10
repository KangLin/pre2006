/*******************************************************************************************************
版权所有 (C) 2006 ；保留所有权利。
文件名：Console.h
描  述：实现控制台的对话框，具体的功能实现在 CCommandWnd 中完成。此类中有其的一个实例。
版  本：2.0.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2006年11月22日
时  间：13:44:09
编译器：Microsoft Visual Studio 8.0 —— C/C++ 8.0
*******************************************************************************************************/

#pragma once

#include "CommandWnd.h"

// CConsoleDlg dialog

class CConsoleDlg : public CDialog
{
	//DECLARE_DYNAMIC(CConsoleDlg)
	DECLARE_DYNCREATE(CConsoleDlg)

public:
	CConsoleDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CConsoleDlg();

// Dialog Data
	enum { IDD = IDD_CONSOLE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CCommandWnd m_Cmd;

	virtual BOOL OnInitDialog();

	afx_msg void OnSize(UINT nType, int cx, int cy);
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void OnOK();
	virtual void OnCancel();
};
