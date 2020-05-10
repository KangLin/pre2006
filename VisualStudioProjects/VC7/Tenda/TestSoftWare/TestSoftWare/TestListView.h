#pragma once


// CTestListView 视图

class CTestListView : public CListView
{
	DECLARE_DYNCREATE(CTestListView)

protected:
	CTestListView();           // 动态创建所使用的受保护的构造函数
	virtual ~CTestListView();

public:
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	DECLARE_MESSAGE_MAP()
};


