// ProcessViewerDoc.h : CProcessViewerDoc ��Ľӿ�
//


#pragma once


class CProcessViewerDoc : public CDocument
{
protected: // �������л�����
	CProcessViewerDoc();
	DECLARE_DYNCREATE(CProcessViewerDoc)

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
	virtual ~CProcessViewerDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


