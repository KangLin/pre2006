#pragma once

#include "..\resource.h"

// CShowResult 对话框

class CShowResult : public CDialog
{
	DECLARE_DYNAMIC(CShowResult)

public:
	CShowResult(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CShowResult();

// 对话框数据
	enum { IDD = IDD_SHOWRESULT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

    DECLARE_MESSAGE_MAP()

private:
    HICON m_hIcon;

public:
    virtual BOOL OnInitDialog();
    // 赢方用户名
    CString m_szWin;
    // 输方用户名
    CString m_szLoss;
    // 赢方积分
    int m_iWin;
    // 输方积分
    int m_iLoss;
    // 赢棋加分值
    int m_iAdd;
    // 输棋减分值
    int m_iInc;
};
