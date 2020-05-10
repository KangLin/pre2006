// GeneticsView.cpp : CGeneticsView 类的实现
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CGeneticsView 构造/析构

CGeneticsView::CGeneticsView()
{
	// TODO: 在此处添加构造代码

}

CGeneticsView::~CGeneticsView()
{
}

BOOL CGeneticsView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式

	return CView::PreCreateWindow(cs);
}

// CGeneticsView 绘制

void CGeneticsView::OnDraw(CDC * pDC)
{
	CGeneticsDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	RECT rect;
	GetClientRect(&rect);

	pDC->MoveTo(20, 20);
	pDC->LineTo(10, 10);
	
}


// CGeneticsView 打印

BOOL CGeneticsView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGeneticsView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印前添加额外的初始化
}

void CGeneticsView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 打印后添加清除过程
}


// CGeneticsView 诊断

#ifdef _DEBUG
void CGeneticsView::AssertValid() const
{
	CView::AssertValid();
}

void CGeneticsView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGeneticsDoc* CGeneticsView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGeneticsDoc)));
	return (CGeneticsDoc*)m_pDocument;
}
#endif //_DEBUG


// CGeneticsView 消息处理程序
