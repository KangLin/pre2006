/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：Regist.h
描  述：注册对话框
版  本：2005.6.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2005年7月12日
时  间：19:06:35
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10
*******************************************************************************************************/
#pragma once

#include "..\..\..\VisualStudioProjects\VC7\DLL\Syntax\resource.h"
#include "Limit.h"
#include "afxwin.h"

// CRegist 对话框

class CRegist : public CDialog
{
	DECLARE_DYNAMIC(CRegist)

public:
	CRegist(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRegist();

// 对话框数据
	enum { IDD = IDD_REGIST };

private:
    HICON m_hIcon;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();

    // 机器码
    DWORD m_dwMachinNo;
    // 注册号
    DWORD m_dwRegist;
    CString m_szTitle;

	BOOL m_bShow;
	afx_msg void OnBnClickedShow();
	CEdit m_edThanks;
	CString m_edszThanks;

};
