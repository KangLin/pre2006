/*******************************************************************************************************
��Ȩ���� (C) 2006 ����������Ȩ����
�ļ�����Console.h
��  ����ʵ�ֿ���̨�ĶԻ��򣬾���Ĺ���ʵ���� CCommandWnd ����ɡ������������һ��ʵ����
��  ����2.0.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2006��11��22��
ʱ  �䣺13:44:09
��������Microsoft Visual Studio 8.0 ���� C/C++ 8.0
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
