// MicrosoftDevelopmentEnvironmentExtendToolsSerialNoDlg.h : ͷ�ļ�
//

#pragma once


// CMicrosoftDevelopmentEnvironmentExtendToolsSerialNoDlg �Ի���
class CMicrosoftDevelopmentEnvironmentExtendToolsSerialNoDlg : public CDialog
{
// ����
public:
	CMicrosoftDevelopmentEnvironmentExtendToolsSerialNoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MICROSOFTDEVELOPMENTENVIRONMENTEXTENDTOOLSSERIALNO_DIALOG };

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
    DWORD m_dwRegist;
    DWORD m_dwMachine;
    afx_msg void OnBnClickedButton1();
};
