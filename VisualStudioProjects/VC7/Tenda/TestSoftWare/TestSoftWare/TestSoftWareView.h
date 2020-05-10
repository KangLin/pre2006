// TestSoftWareView.h : CTestSoftWareView ��Ľӿ�
//


#pragma once

#include "TestSoftWareDoc.h"

class CTestSoftWareView : public CTreeView
{
protected: // �������л�����
	CTestSoftWareView();
	DECLARE_DYNCREATE(CTestSoftWareView)

// ����
public:
	CTestSoftWareDoc* GetDocument() const;

// ����
public:

// ��д
	public:
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CTestSoftWareView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
private:
	CImageList m_image;

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // TestSoftWareView.cpp �ĵ��԰汾
inline CTestSoftWareDoc* CTestSoftWareView::GetDocument() const
   { return reinterpret_cast<CTestSoftWareDoc*>(m_pDocument); }
#endif

