#pragma once


// CIncludeFile �Ի���

class CIncludeFile : public CDialog
{
	DECLARE_DYNAMIC(CIncludeFile)

public:
	CIncludeFile(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CIncludeFile();

// �Ի�������
	enum { IDD = IDD_INCLUDEFILE };

private:
    HICON m_hIcon;
	TCHAR m_szRelBuf[MAX_PATH];

protected:
	virtual void DoDataExchange(CDataExchange * pDX);     // DDX/DDV ֧��

public:
    virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	CString m_szFile;
	CString m_szDocument; //�ĵ���
	CString m_szRelative; //����ļ���
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonBrown();
};
