/*******************************************************************************************************
��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
�ļ�����RelativePath.h
��  �����õ����·����
��  ����1.0.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2005-5-16
ʱ  �䣺17:34:11
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10

Copyright (C) 2005 KangLin Studio;All rights reserved.
FileName   ��RelativePath.h
Description��Get relative path
Version    ��1.0.0.1
Author     ��KangLin
E_Mail     ��kl222@126.com
Date       ��2005-5-16
Time       ��17:34:12
Compiler   ��Microsoft Development Environment 7.10 ���� C/C++ 7.10
*******************************************************************************************************/
#pragma once


// CRelativePath �Ի���

class CRelativePath : public CDialog
{
	DECLARE_DYNAMIC(CRelativePath)

public:
	CRelativePath(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRelativePath();

// �Ի�������
	enum { IDD = IDD_RELATIVEPATH };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    afx_msg void OnEnChangeEditSource();
    afx_msg void OnEnChangeEditDestination();
    virtual BOOL OnInitDialog();

    // Դ�ļ�
    CString m_szSource;
    // Ŀ���ļ�
    CString m_szDestination;
    // ���·��
    CString m_szRelative;
    //�Ƿ��Ƶ����а���
    BOOL m_bClipboard;

private:
    HICON m_hIcon;

public:
    afx_msg void OnBnClickedButtonSource();
    afx_msg void OnBnClickedButtonDestination();
    bool GetRelativePath(void);
};
