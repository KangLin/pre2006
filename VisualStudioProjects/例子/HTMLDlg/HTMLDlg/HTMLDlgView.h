// HTMLDlgView.h : CHTMLDlgView ��Ľӿ�
//


#pragma once


class CHTMLDlgView : public CHtmlView
{
protected: // �������л�����
	CHTMLDlgView();
	DECLARE_DYNCREATE(CHTMLDlgView)

// ����
public:
	CHTMLDlgDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CHTMLDlgView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // HTMLDlgView.cpp �еĵ��԰汾
inline CHTMLDlgDoc* CHTMLDlgView::GetDocument() const
   { return reinterpret_cast<CHTMLDlgDoc*>(m_pDocument); }
#endif

