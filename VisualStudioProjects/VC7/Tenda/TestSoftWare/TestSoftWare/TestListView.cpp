// TestListView.cpp : 实现文件
//

#include "stdafx.h"
#include "TestSoftWare.h"
#include "TestListView.h"


// CTestListView

IMPLEMENT_DYNCREATE(CTestListView, CListView)

CTestListView::CTestListView()
{
}

CTestListView::~CTestListView()
{
}

BEGIN_MESSAGE_MAP(CTestListView, CListView)
END_MESSAGE_MAP()


// CTestListView 诊断

#ifdef _DEBUG
void CTestListView::AssertValid() const
{
	CListView::AssertValid();
}

void CTestListView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}
#endif //_DEBUG


// CTestListView 消息处理程序
