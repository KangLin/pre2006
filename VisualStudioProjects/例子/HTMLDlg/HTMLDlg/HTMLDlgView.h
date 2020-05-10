// HTMLDlgView.h : CHTMLDlgView 类的接口
//


#pragma once


class CHTMLDlgView : public CHtmlView
{
protected: // 仅从序列化创建
	CHTMLDlgView();
	DECLARE_DYNCREATE(CHTMLDlgView)

// 属性
public:
	CHTMLDlgDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CHTMLDlgView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // HTMLDlgView.cpp 中的调试版本
inline CHTMLDlgDoc* CHTMLDlgView::GetDocument() const
   { return reinterpret_cast<CHTMLDlgDoc*>(m_pDocument); }
#endif

