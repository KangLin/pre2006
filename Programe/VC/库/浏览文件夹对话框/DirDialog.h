/*******************************************************************************************************
�ļ�����DirDialog.h
��  �ܣ���ʾ����ļ��жԻ���
��  ��: CDirDialog dd;
        dd.m_strInitDir = _T("��ʼ�ļ���");
		if(dd.DoBrowse(this)==IDOK)
	    {
		    //�õ�Ŀ¼
		    m_ctrPath.SetWindowText(dd.m_strPath);	
	    }
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-11-29
ʱ  �䣺10:48:34
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


