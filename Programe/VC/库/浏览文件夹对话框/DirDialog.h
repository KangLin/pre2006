/*******************************************************************************************************
文件名：DirDialog.h
功  能：显示浏览文件夹对话框
用  法: CDirDialog dd;
        dd.m_strInitDir = _T("初始文件夹");
		if(dd.DoBrowse(this)==IDOK)
	    {
		    //得到目录
		    m_ctrPath.SetWindowText(dd.m_strPath);	
	    }
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-11-29
时  间：10:48:34
*******************************************************************************************************/
////////////////////////////////////////////////////////////////////////
// DirDialog.h: interface for the CDirDialog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DIRDIALOG_H__62FFAC92_1DEE_11D1_B87A_0060979CDF6D__INCLUDED_)
#define AFX_DIRDIALOG_H__62FFAC92_1DEE_11D1_B87A_0060979CDF6D__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

class CDirDialog
{
  public:
    CDirDialog();
    virtual ~CDirDialog();
    int DoBrowse(CWnd *pwndParent);

    CString m_strPath;
    CString m_strInitDir;
    CString m_strSelDir;
    CString m_strWindowTitle;
    int  m_iImageIndex;
};

#endif // !defined(AFX_DIRDIALOG_H__62FFAC92_1DEE_11D1_B87A_0060979CDF6D__INCLUDED_)


