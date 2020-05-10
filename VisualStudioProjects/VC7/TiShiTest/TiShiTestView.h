// TiShiTestView.h : CTiShiTestView 类的接口
//


#pragma once
#include "T.h"

class CTiShiTestView : public CEditView
{
protected: // 仅从序列化创建
	CTiShiTestView();
	DECLARE_DYNCREATE(CTiShiTestView)

// 属性
public:
	CTiShiTestDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT & cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CTiShiTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEditUndo();
	CT ts;
	afx_msg void On32771();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // TiShiTestView.cpp 的调试版本
inline CTiShiTestDoc* CTiShiTestView::GetDocument() const
   { return reinterpret_cast<CTiShiTestDoc*>(m_pDocument); }
#endif

