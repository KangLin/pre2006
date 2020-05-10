/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：RelativePath.cpp
描  述：得到相对路径
版  本：1.0.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2005-5-16
时  间：17:33:33
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10

Copyright (C) 2005 KangLin Studio;All rights reserved.
FileName   ：RelativePath.cpp
Description：Get relative path
Version    ：1.0.0.1
Author     ：KangLin
E_Mail     ：kl222@126.com
Date       ：2005-5-16
Time       ：17:33:34
Compiler   ：Microsoft Development Environment 7.10 —— C/C++ 7.10
*******************************************************************************************************/
// RelativePath.cpp : 实现文件
//

#include "stdafx.h"
#include "Syntax.h"
#include "RelativePath.h"
#include ".\relativepath.h"


// CRelativePath 对话框

IMPLEMENT_DYNAMIC(CRelativePath, CDialog)
CRelativePath::CRelativePath(CWnd* pParent /*=NULL*/)
	: CDialog(CRelativePath::IDD, pParent)
{
    m_bClipboard = TRUE;
    m_szSource = _T("");
    m_szDestination = _T("");
    m_szRelative = _T("");
    m_hIcon = AfxGetApp()->LoadIcon(IDI_KL);
}

CRelativePath::~CRelativePath()
{
}

void CRelativePath::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_EDIT_SOURCE, m_szSource);
    DDX_Text(pDX, IDC_EDIT_DESTINATION, m_szDestination);
    DDX_Text(pDX, IDC_EDIT_RELATIVE, m_szRelative);
}


BEGIN_MESSAGE_MAP(CRelativePath, CDialog)
    ON_EN_CHANGE(IDC_EDIT_SOURCE, OnEnChangeEditSource)
    ON_EN_CHANGE(IDC_EDIT_DESTINATION, OnEnChangeEditDestination)
    ON_BN_CLICKED(IDC_BUTTON_SOURCE, OnBnClickedButtonSource)
    ON_BN_CLICKED(IDC_BUTTON_DESTINATION, OnBnClickedButtonDestination)
END_MESSAGE_MAP()


// CRelativePath 消息处理程序

void CRelativePath::OnEnChangeEditSource()
{
    GetRelativePath();
}

void CRelativePath::OnEnChangeEditDestination()
{
   GetRelativePath();
}

BOOL CRelativePath::OnInitDialog()
{
    CDialog::OnInitDialog();

    //设置对话框图标
    SetIcon(m_hIcon, TRUE);
    SetIcon(m_hIcon, FALSE);

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void CRelativePath::OnBnClickedButtonSource()
{
    CString szFile;
    
    CFileDialog fd(TRUE, NULL, m_szSource);
    if(fd.DoModal() == IDOK)
    {
        szFile = fd.GetPathName();
        if(!szFile.IsEmpty())
        {
            m_szSource = szFile;
            UpdateData(FALSE);
            GetRelativePath();
        }
    }
}

void CRelativePath::OnBnClickedButtonDestination()
{
    CString szFile;
    CFileDialog fd(TRUE, NULL, m_szSource);
    if(fd.DoModal() == IDOK)
    {
        szFile = fd.GetPathName();
        if(!szFile.IsEmpty())
        {
            m_szDestination = szFile;
            UpdateData(FALSE);
            GetRelativePath();
        }
    }
}

/*******************************************************************************************************
函数名：GetRelativePath
描  述：得到相对路径，并复制到剪切板。
参  数：
         void：无
返回值：
版  本：1.0.0.1
作  者：康  林
时  间：2005-5-16 17:32:14
*******************************************************************************************************/
bool CRelativePath::GetRelativePath(void)
{
    TCHAR szFile[MAX_PATH];
    UpdateData(TRUE);
    if(PathRelativePathTo(szFile, m_szSource, FILE_ATTRIBUTE_NORMAL, m_szDestination, FILE_ATTRIBUTE_NORMAL))
    {
        m_szRelative = szFile;
    }
    else
    {
        m_szRelative = m_szDestination;
    }
    if(m_bClipboard)
    {
        if ( !OpenClipboard() )
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
        hglbCopy = ::GlobalAlloc(GMEM_MOVEABLE, m_szRelative.GetLength() + sizeof(TCHAR));
        if(hglbCopy == NULL)
        {
            ::CloseClipboard();
            TRACE(_T("%s(%d) : 全局堆分配失败。\n"), __FILE__, __LINE__);
            return FALSE;
        }
        lpData = (LPTSTR) ::GlobalLock(hglbCopy);
        memcpy(lpData, m_szRelative, m_szRelative.GetLength() + sizeof(TCHAR));
        
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
        
    }
    this->UpdateData(FALSE);
    return TRUE;
}
