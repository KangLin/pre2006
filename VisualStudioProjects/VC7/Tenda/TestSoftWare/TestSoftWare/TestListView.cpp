// TestListView.cpp : ʵ���ļ�
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


// CTestListView ���

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


// CTestListView ��Ϣ�������
