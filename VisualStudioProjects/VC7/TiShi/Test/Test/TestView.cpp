// TestView.cpp : CTestView ���ʵ��
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"
#include "TestView.h"
#include "..\..\..\..\..\Programe\VC\File\FileEx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestView

IMPLEMENT_DYNCREATE(CTestView, CEditView)

BEGIN_MESSAGE_MAP(CTestView, CEditView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CEditView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_KEYUP()
END_MESSAGE_MAP()

// CTestView ����/����

CTestView::CTestView()
{
	// TODO: �ڴ˴���ӹ������

}

CTestView::~CTestView()
{
}

BOOL CTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// ���û���

	return bPreCreated;
}


// CTestView ��ӡ

BOOL CTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ׼��
	return CEditView::OnPreparePrinting(pInfo);
}

void CTestView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ��ʼ��ӡ
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CTestView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ������ӡ
	CEditView::OnEndPrinting(pDC, pInfo);
}


// CTestView ���

#ifdef _DEBUG
void CTestView::AssertValid() const
{
	CEditView::AssertValid();
}

void CTestView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CTestDoc* CTestView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTestDoc)));
	return (CTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CTestView ��Ϣ�������

int CTestView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	m_TiShi.CreateEx(this->GetSafeHwnd());
	CFileEx fe;

	m_TiShi.LoadString(fe.GetFilePath() + _T("\\list.txt"));
	m_TiShi.SetSize(200, 200);
	return 0;
}

void CTestView::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	m_TiShi.Show(this->GetSafeHwnd());

	CEditView::OnKeyUp(nChar, nRepCnt, nFlags);
}
