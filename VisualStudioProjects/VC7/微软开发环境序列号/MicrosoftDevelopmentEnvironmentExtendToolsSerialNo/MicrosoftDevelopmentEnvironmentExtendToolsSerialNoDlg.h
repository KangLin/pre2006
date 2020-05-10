// MicrosoftDevelopmentEnvironmentExtendToolsSerialNoDlg.h : 头文件
//

#pragma once


// CMicrosoftDevelopmentEnvironmentExtendToolsSerialNoDlg 对话框
class CMicrosoftDevelopmentEnvironmentExtendToolsSerialNoDlg : public CDialog
{
// 构造
public:
	CMicrosoftDevelopmentEnvironmentExtendToolsSerialNoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MICROSOFTDEVELOPMENTENVIRONMENTEXTENDTOOLSSERIALNO_DIALOG };

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
public:
    DWORD m_dwRegist;
    DWORD m_dwMachine;
    afx_msg void OnBnClickedButton1();
};
