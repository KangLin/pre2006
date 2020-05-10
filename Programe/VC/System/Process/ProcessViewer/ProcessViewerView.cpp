// ProcessViewerView.cpp : CProcessViewerView ���ʵ��
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

// CProcessViewerView ����/����

CProcessViewerView::CProcessViewerView()
	: CFormView(CProcessViewerView::IDD)
{
	// TODO: �ڴ˴���ӹ������

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
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CFormView::PreCreateWindow(cs);
}

void CProcessViewerView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CProcessViewerView ���

#ifdef _DEBUG
void CProcessViewerView::AssertValid() const
{
	CFormView::AssertValid();
}

void CProcessViewerView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CProcessViewerDoc* CProcessViewerView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProcessViewerDoc)));
	return (CProcessViewerDoc*)m_pDocument;
}
#endif //_DEBUG


// CProcessViewerView ��Ϣ�������

void CProcessViewerView::OnBnClickedButton1()
{
	CProcessModuleDlg dlg;
	dlg.DoModal();
}
