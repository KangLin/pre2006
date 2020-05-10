/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：RelativePath.h
描  述：得到相对路径。
版  本：1.0.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2005-5-16
时  间：17:34:11
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10

Copyright (C) 2005 KangLin Studio;All rights reserved.
FileName   ：RelativePath.h
Description：Get relative path
Version    ：1.0.0.1
Author     ：KangLin
E_Mail     ：kl222@126.com
Date       ：2005-5-16
Time       ：17:34:12
Compiler   ：Microsoft Development Environment 7.10 —— C/C++ 7.10
*******************************************************************************************************/
#pragma once


// CRelativePath 对话框

class CRelativePath : public CDialog
{
	DECLARE_DYNAMIC(CRelativePath)

public:
	CRelativePath(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CRelativePath();

// 对话框数据
	enum { IDD = IDD_RELATIVEPATH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnEnChangeEditSource();
    afx_msg void OnEnChangeEditDestination();
    virtual BOOL OnInitDialog();

    // 源文件
    CString m_szSource;
    // 目的文件
    CString m_szDestination;
    // 相对路径
    CString m_szRelative;
    //是否复制到剪切板中
    BOOL m_bClipboard;

private:
    HICON m_hIcon;

public:
    afx_msg void OnBnClickedButtonSource();
    afx_msg void OnBnClickedButtonDestination();
    bool GetRelativePath(void);
};
