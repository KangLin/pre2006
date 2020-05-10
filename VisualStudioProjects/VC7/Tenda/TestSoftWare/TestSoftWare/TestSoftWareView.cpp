// TestSoftWareView.cpp : CTestSoftWareView 类的实现
//

#include "stdafx.h"
#include "TestSoftWare.h"

#include "TestSoftWareDoc.h"
#include "TestSoftWareView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestSoftWareView

IMPLEMENT_DYNCREATE(CTestSoftWareView, CTreeView)

BEGIN_MESSAGE_MAP(CTestSoftWareView, CTreeView)
END_MESSAGE_MAP()

// CTestSoftWareView 构造/析构

CTestSoftWareView::CTestSoftWareView()
{
	// TODO: 在此处添加构造代码

}

CTestSoftWareView::~CTestSoftWareView()
{
}

BOOL CTestSoftWareView::PreCreateWindow(CREATESTRUCT& cs)
{
	cs.style |= TVS_HASLINES | TVS_LINESATROOT | TVS_HASBUTTONS | TVS_SHOWSELALWAYS;

	return CTreeView::PreCreateWindow(cs);
}

void CTestSoftWareView::OnInitialUpdate()
{
	CTreeView::OnInitialUpdate();

	m_image.Create(IDB_IMAGE, 16, 4, RGB(0, 0, 0));
	GetTreeCtrl().SetImageList(&m_image, TVSIL_NORMAL);
	GetTreeCtrl().InsertItem(_T("产品"), 1, 1);
}


// CTestSoftWareView 诊断

#ifdef _DEBUG
void CTestSoftWareView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CTestSoftWareView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CTestSoftWareDoc* CTestSoftWareView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestSoftWareDoc)));
	return (CTestSoftWareDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestSoftWareView 消息处理程序
