// GeneticsView.cpp : CGeneticsView ���ʵ��
//

#include "stdafx.h"
#include "Genetics.h"

#include "GeneticsDoc.h"
#include "GeneticsView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGeneticsView

IMPLEMENT_DYNCREATE(CGeneticsView, CView)

BEGIN_MESSAGE_MAP(CGeneticsView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CGeneticsView ����/����

CGeneticsView::CGeneticsView()
{
	// TODO: �ڴ˴���ӹ������

}

CGeneticsView::~CGeneticsView()
{
}

BOOL CGeneticsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ������
	// ��ʽ

	return CView::PreCreateWindow(cs);
}

// CGeneticsView ����

void CGeneticsView::OnDraw(CDC * pDC)
{
	CGeneticsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���

	RECT rect;
	GetClientRect(&rect);

	pDC->MoveTo(20, 20);
	pDC->LineTo(10, 10);
	
}


// CGeneticsView ��ӡ

BOOL CGeneticsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CGeneticsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡǰ��Ӷ���ĳ�ʼ��
}

void CGeneticsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��ӡ������������
}


// CGeneticsView ���

#ifdef _DEBUG
void CGeneticsView::AssertValid() const
{
	CView::AssertValid();
}

void CGeneticsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGeneticsDoc* CGeneticsView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGeneticsDoc)));
	return (CGeneticsDoc*)m_pDocument;
}
#endif //_DEBUG


// CGeneticsView ��Ϣ�������
