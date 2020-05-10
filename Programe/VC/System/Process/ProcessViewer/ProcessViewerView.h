// ProcessViewerView.h : CProcessViewerView 类的接口
//


#pragma once


class CProcessViewerView : public CFormView
{
protected: // 仅从序列化创建
	CProcessViewerView();
	DECLARE_DYNCREATE(CProcessViewerView)

public:
	enum{ IDD = IDD_PROCESSVIEWER_FORM };

// 属性
public:
	CProcessViewerDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CProcessViewerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};

#ifndef _DEBUG  // ProcessViewerView.cpp 中的调试版本
inline CProcessViewerDoc* CProcessViewerView::GetDocument() const
   { return reinterpret_cast<CProcessViewerDoc*>(m_pDocument); }
#endif

