#pragma once


// CTestListView ��ͼ

class CTestListView : public CListView
{
	DECLARE_DYNCREATE(CTestListView)

protected:
	CTestListView();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CTestListView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


