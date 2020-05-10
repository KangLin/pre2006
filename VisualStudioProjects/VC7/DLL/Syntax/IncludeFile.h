#pragma once


// CIncludeFile 对话框

class CIncludeFile : public CDialog
{
	DECLARE_DYNAMIC(CIncludeFile)

public:
	CIncludeFile(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CIncludeFile();

// 对话框数据
	enum { IDD = IDD_INCLUDEFILE };

private:
    HICON m_hIcon;
	TCHAR m_szRelBuf[MAX_PATH];

protected:
	virtual void DoDataExchange(CDataExchange * pDX);     // DDX/DDV 支持

public:
    virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

public:
	CString m_szFile;
	CString m_szDocument; //文档名
	CString m_szRelative; //相对文件名
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonBrown();
};
