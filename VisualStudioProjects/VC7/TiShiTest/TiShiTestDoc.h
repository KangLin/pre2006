// TiShiTestDoc.h :  CTiShiTestDoc ��Ľӿ�
//


#pragma once

class CTiShiTestDoc : public CDocument
{
protected: // �������л�����
	CTiShiTestDoc();
	DECLARE_DYNCREATE(CTiShiTestDoc)

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
	virtual ~CTiShiTestDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


