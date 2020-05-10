// ProcessViewerView.cpp : CProcessViewerView 类的实现
//

#include "stdafx.h"
#include "ProcessViewer.h"

#include "ProcessViewerDoc.h"
#include "ProcessViewerView.h"
#include "ProcessModuleDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProcessViewerView

IMPLEMENT_DYNCREATE(CProcessViewerView, CFormView)

BEGIN_MESSAGE_MAP(CProcessViewerView, CFormView)
	ON_BN_CLICKED(IDC_BUTTON1, &CProcessViewerView::OnBnClickedButton1)
END_MESSAGE_MAP()

// CProcessViewerView 构造/析构

CProcessViewerView::CProcessViewerView()
	: CFormView(CProcessViewerView::IDD)
{
	// TODO: 在此处添加构造代码

}

CProcessViewerView::~CProcessViewerView()
{
}

void CProcessViewerView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BOOL CProcessViewerView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CFormView::PreCreateWindow(cs);
}

void CProcessViewerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CProcessViewerView 诊断

#ifdef _DEBUG
void CProcessViewerView::AssertValid() const
{
	CFormView::AssertValid();
}

void CProcessViewerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CProcessViewerDoc* CProcessViewerView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProcessViewerDoc)));
	return (CProcessViewerDoc*)m_pDocument;
}
#endif //_DEBUG


// CProcessViewerView 消息处理程序

void CProcessViewerView::OnBnClickedButton1()
{
	CProcessModuleDlg dlg;
	dlg.DoModal();
}
