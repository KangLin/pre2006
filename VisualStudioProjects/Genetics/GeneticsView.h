// GeneticsView.h : CGeneticsView 类的接口
//


#pragma once


class CGeneticsView : public CView
{
protected: // 仅从序列化创建
	CGeneticsView();
	DECLARE_DYNCREATE(CGeneticsView)

// 属性
public:
	CGeneticsDoc* GetDocument() const;

// 操作
public:

// 重写
	public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CGeneticsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // GeneticsView.cpp 的调试版本
inline CGeneticsDoc* CGeneticsView::GetDocument() const
   { return reinterpret_cast<CGeneticsDoc*>(m_pDocument); }
#endif

