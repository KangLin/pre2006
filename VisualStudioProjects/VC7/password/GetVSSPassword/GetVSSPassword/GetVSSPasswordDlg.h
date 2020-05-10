// GetVSSPasswordDlg.h : 头文件
//

#pragma once


// CGetVSSPasswordDlg 对话框
class CGetVSSPasswordDlg : public CDialog
{
// 构造
public:
	CGetVSSPasswordDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GETVSSPASSWORD_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
