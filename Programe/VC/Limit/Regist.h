/*******************************************************************************************************
��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
�ļ�����Regist.h
��  ����ע��Ի���
��  ����2005.6.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2005��7��12��
ʱ  �䣺19:06:35
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10
*******************************************************************************************************/
#pragma once

#include "..\..\..\VisualStudioProjects\VC7\DLL\Syntax\resource.h"
#include "Limit.h"
#include "afxwin.h"

// CRegist �Ի���

class CRegist : public CDialog
{
	DECLARE_DYNAMIC(CRegist)

public:
	CRegist(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CRegist();

// �Ի�������
	enum { IDD = IDD_REGIST };

private:
    HICON m_hIcon;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
    virtual BOOL OnInitDialog();

    // ������
    DWORD m_dwMachinNo;
    // ע���
    DWORD m_dwRegist;
    CString m_szTitle;

	BOOL m_bShow;
	afx_msg void OnBnClickedShow();
	CEdit m_edThanks;
	CString m_edszThanks;

};
