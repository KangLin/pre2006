// PasswordManageDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"
#include ".\PasswordManager\PasswordManager.h"
#include "passwordManager\EncrypterManager.h"


// CPasswordManageDlg �Ի���
class CPasswordManageDlg : public CDialog
{
// ����
public:
	CPasswordManageDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_PASSWORDMANAGE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOk();
public:
	CListCtrl m_list;
	CPasswordManager m_PasswordManager;
	CEncrypterManager m_EncrypterManager;
};
