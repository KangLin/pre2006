// ProcessViewerView.h : CProcessViewerView ��Ľӿ�
//


#pragma once


class CProcessViewerView : public CFormView
{
protected: // �������л�����
	CProcessViewerView();
	DECLARE_DYNCREATE(CProcessViewerView)

public:
	enum{ IDD = IDD_PROCESSVIEWER_FORM };

// ����
public:
	CProcessViewerDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual void OnInitialUpdate(); // ������һ�ε���

// ʵ��
public:
	virtual ~CProcessViewerView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};

#ifndef _DEBUG  // ProcessViewerView.cpp �еĵ��԰汾
inline CProcessViewerDoc* CProcessViewerView::GetDocument() const
   { return reinterpret_cast<CProcessViewerDoc*>(m_pDocument); }
#endif

