// TestSoftWareDoc.h :  CTestSoftWareDoc ��Ľӿ�
//


#pragma once

class CTestSoftWareDoc : public CDocument
{
protected: // �������л�����
	CTestSoftWareDoc();
	DECLARE_DYNCREATE(CTestSoftWareDoc)

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
	virtual ~CTestSoftWareDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


