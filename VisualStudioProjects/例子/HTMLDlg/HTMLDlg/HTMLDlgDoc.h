// HTMLDlgDoc.h : CHTMLDlgDoc ��Ľӿ�
//


#pragma once


class CHTMLDlgDoc : public CDocument
{
protected: // �������л�����
	CHTMLDlgDoc();
	DECLARE_DYNCREATE(CHTMLDlgDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CHTMLDlgDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


