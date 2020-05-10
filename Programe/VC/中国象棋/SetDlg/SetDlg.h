#pragma once
#include "..\resource.h"       // main symbols
#include "atlcomtime.h"

// CSetDlg 对话框

class CSetDlg : public CDialog
{
	DECLARE_DYNAMIC(CSetDlg)

public:
	CSetDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CSetDlg();

// 对话框数据
	enum { IDD = IDD_SETDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()

private:
    HICON m_hIcon;
public:
    virtual BOOL OnInitDialog();
    // 每步间隔时间
    LONG m_dwStep;
    // 赢棋加分值
    UINT m_uAddPoint;
    // 输棋减分值
    UINT m_uIncPoint;
    //本对话框的用途
    enum
    {
        Setting,
        ReceiveSet
    };
    int m_iFunction;
};
