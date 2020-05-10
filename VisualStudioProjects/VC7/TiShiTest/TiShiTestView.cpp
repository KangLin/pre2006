// TiShiTestView.cpp : CTiShiTestView 类的实现
//

#include "stdafx.h"
#include "TiShiTest.h"
#include "..\..\..\Programe\VC\File\FileEx.h"
#include "TiShiTestDoc.h"
#include "TiShiTestView.h"
#include ".\tishitestview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTiShiTestView

IMPLEMENT_DYNCREATE(CTiShiTestView, CEditView)

BEGIN_MESSAGE_MAP(CTiShiTestView, CEditView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_COMMAND(ID_32771, On32771)
	ON_WM_CHAR()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CTiShiTestView 构造/析构

CTiShiTestView::CTiShiTestView()
{
	// TODO: 在此处添加构造代码

}

CTiShiTestView::~CTiShiTestView()
{
}

BOOL CTiShiTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改 CREATESTRUCT cs 来修改窗口类或
	// 样式

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// 启用换行

	return bPreCreated;
}


// CTiShiTestView 打印

BOOL CTiShiTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认 CEditView 准备
	return CEditView::OnPreparePrinting(pInfo);
}

void CTiShiTestView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// 默认 CEditView 开始打印
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CTiShiTestView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// 默认 CEditView 结束打印
	CEditView::OnEndPrinting(pDC, pInfo);
}


// CTiShiTestView 诊断

#ifdef _DEBUG
void CTiShiTestView::AssertValid() const
{
	CEditView::AssertValid();
}

void CTiShiTestView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CTiShiTestDoc* CTiShiTestView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTiShiTestDoc)));
	return (CTiShiTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CTiShiTestView 消息处理程序

void CTiShiTestView::OnEditUndo()
{
	
}

void CTiShiTestView::On32771()
{
	//ts.CreateEx(this->GetSafeHwnd());

}

void CTiShiTestView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	ts.Show(this->GetSafeHwnd(), TRUE);
	
	ts.Move(nChar);
	//this->SetFocus();
	CEditView::OnChar(nChar, nRepCnt, nFlags);
}

int CTiShiTestView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  在此添加您专用的创建代码
	ts.CreateEx(this->GetSafeHwnd());
	CFileEx fe;

	ts.LoadString(fe.GetFilePath() + "\\LIST.TXT");
	return 0;
}
