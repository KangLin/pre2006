#pragma once
#include "afxwin.h"


// CInputData 对话框

class CInputData : public CDialog
{
	DECLARE_DYNAMIC(CInputData)

public:
	CInputData(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInputData();

// 对话框数据
	enum { IDD = IDD_INPUTDATA };

public:
    virtual BOOL OnInitDialog();
    afx_msg void OnSize(UINT nType, int cx, int cy);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

private:
    HICON m_hIcon;
    CStatic m_Group;

	DECLARE_MESSAGE_MAP()
    
public:
    afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
    CComboBox m_cbDoctor;
};
