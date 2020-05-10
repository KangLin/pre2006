// GetVSSPasswordDlg.h : ͷ�ļ�
//

#pragma once


// CGetVSSPasswordDlg �Ի���
class CGetVSSPasswordDlg : public CDialog
{
// ����
public:
	CGetVSSPasswordDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GETVSSPASSWORD_DIALOG };

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

private:
	CString m_szPassword;
	CString m_szEnPassword;

	int GetPassword(LPCTSTR lpcszEncryptPassword, LPTSTR lpszPassword);
	int HexToInt(char c);

public:
	afx_msg void OnBnClickedOk();
};
