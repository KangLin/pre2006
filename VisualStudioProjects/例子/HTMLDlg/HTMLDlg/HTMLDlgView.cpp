// HTMLDlgView.cpp : CHTMLDlgView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CHtmlView::OnFilePrint)
END_MESSAGE_MAP()

// CHTMLDlgView ����/����

CHTMLDlgView::CHTMLDlgView()
{
	// TODO: �ڴ˴���ӹ������

}

CHTMLDlgView::~CHTMLDlgView()
{
}

BOOL CHTMLDlgView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CHtmlView::PreCreateWindow(cs);
}

void CHTMLDlgView::OnInitialUpdate()
{
	CHtmlView::OnInitialUpdate();

	Navigate2(_T("http://www.msdn.microsoft.com/visualc/"),NULL,NULL);
}


// CHTMLDlgView ��ӡ



// CHTMLDlgView ���

#ifdef _DEBUG
void CHTMLDlgView::AssertValid() const
{
	CHtmlView::AssertValid();
}

void CHTMLDlgView::Dump(CDumpContext& dc) const
{
	CHtmlView::Dump(dc);
}

CHTMLDlgDoc* CHTMLDlgView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CHTMLDlgDoc)));
	return (CHTMLDlgDoc*)m_pDocument;
}
#endif //_DEBUG


// CHTMLDlgView ��Ϣ�������
