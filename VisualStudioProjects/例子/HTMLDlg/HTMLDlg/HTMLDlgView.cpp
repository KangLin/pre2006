// HTMLDlgView.cpp : CHTMLDlgView 类的实现
//

#include "stdafx.h"
#include "HTMLDlg.h"

#include "HTMLDlgDoc.h"
#include "HTMLDlgView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHTMLDlgView

IMPLEMENT_DYNCREATE(CHTMLDlgView, CHtmlView)

BEGIN_MESSAGE_MAP(CHTMLDlgView, CHtmlView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CHtmlView::OnFilePrint)
END_MESSAGE_MAP()

// CHTMLDlgView 构造/析构

CHTMLDlgView::CHTMLDlgView()
{
	// TODO: 在此处添加构造代码

}

CHTMLDlgView::~CHTMLDlgView()
{
}

BOOL CHTMLDlgView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CHtmlView::PreCreateWindow(cs);
}

void CHTMLDlgView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	Navigate2(_T("http://www.msdn.microsoft.com/visualc/"),NULL,NULL);
}


// CHTMLDlgView 打印



// CHTMLDlgView 诊断

#ifdef _DEBUG
void CHTMLDlgView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CHTMLDlgView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CHTMLDlgDoc* CHTMLDlgView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHTMLDlgDoc)));
	return (CHTMLDlgDoc*)m_pDocument;
}
#endif //_DEBUG


// CHTMLDlgView 消息处理程序
