// TestSoftWareView.cpp : CTestSoftWareView ���ʵ��
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

// CTestSoftWareView ����/����

CTestSoftWareView::CTestSoftWareView()
{
	// TODO: �ڴ˴���ӹ������

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
	GetTreeCtrl().InsertItem(_T("��Ʒ"), 1, 1);
}


// CTestSoftWareView ���

#ifdef _DEBUG
void CTestSoftWareView::AssertValid() const
{
	CTreeView::AssertValid();
}

void CTestSoftWareView::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}

CTestSoftWareDoc* CTestSoftWareView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestSoftWareDoc)));
	return (CTestSoftWareDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestSoftWareView ��Ϣ�������
