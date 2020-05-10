// TiShiTestView.h : CTiShiTestView ��Ľӿ�
//


#pragma once
#include "T.h"

class CTiShiTestView : public CEditView
{
protected: // �������л�����
	CTiShiTestView();
	DECLARE_DYNCREATE(CTiShiTestView)

// ����
public:
	CTiShiTestDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT & cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CTiShiTestView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEditUndo();
	CT ts;
	afx_msg void On32771();
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
};

#ifndef _DEBUG  // TiShiTestView.cpp �ĵ��԰汾
inline CTiShiTestDoc* CTiShiTestView::GetDocument() const
   { return reinterpret_cast<CTiShiTestDoc*>(m_pDocument); }
#endif

