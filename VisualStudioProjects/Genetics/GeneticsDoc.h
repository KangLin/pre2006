// GeneticsDoc.h :  CGeneticsDoc ��Ľӿ�
//


#pragma once

class CGeneticsDoc : public CDocument
{
protected: // �������л�����
	CGeneticsDoc();
	DECLARE_DYNCREATE(CGeneticsDoc)

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
	virtual ~CGeneticsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


