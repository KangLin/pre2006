#pragma once



// CLicense 对话框

class CLicense : public CDialog
{
	DECLARE_DYNAMIC(CLicense)

public:
	CLicense(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CLicense();

// 对话框数据
	enum { IDD = IDD_DLG_LICENSE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
