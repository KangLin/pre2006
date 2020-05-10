// GeneticsView.h : CGeneticsView ��Ľӿ�
//


#pragma once


class CGeneticsView : public CView
{
protected: // �������л�����
	CGeneticsView();
	DECLARE_DYNCREATE(CGeneticsView)

// ����
public:
	CGeneticsDoc* GetDocument() const;

// ����
public:

// ��д
	public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CGeneticsView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // GeneticsView.cpp �ĵ��԰汾
inline CGeneticsDoc* CGeneticsView::GetDocument() const
   { return reinterpret_cast<CGeneticsDoc*>(m_pDocument); }
#endif

