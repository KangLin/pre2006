// TestSoftWareView.h : CTestSoftWareView 类的接口
//


#pragma once

#include "TestSoftWareDoc.h"

class CTestSoftWareView : public CTreeView
{
protected: // 仅从序列化创建
	CTestSoftWareView();
	DECLARE_DYNCREATE(CTestSoftWareView)

// 属性
public:
	CTestSoftWareDoc* GetDocument() const;

// 操作
public:

// 重写
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 构造后第一次调用

// 实现
public:
	virtual ~CTestSoftWareView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
private:
	CImageList m_image;

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // TestSoftWareView.cpp 的调试版本
inline CTestSoftWareDoc* CTestSoftWareView::GetDocument() const
   { return reinterpret_cast<CTestSoftWareDoc*>(m_pDocument); }
#endif

