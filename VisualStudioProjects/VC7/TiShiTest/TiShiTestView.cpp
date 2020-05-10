// TiShiTestView.cpp : CTiShiTestView ���ʵ��
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CEditView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CEditView::OnFilePrintPreview)
	ON_COMMAND(ID_EDIT_UNDO, OnEditUndo)
	ON_COMMAND(ID_32771, On32771)
	ON_WM_CHAR()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CTiShiTestView ����/����

CTiShiTestView::CTiShiTestView()
{
	// TODO: �ڴ˴���ӹ������

}

CTiShiTestView::~CTiShiTestView()
{
}

BOOL CTiShiTestView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸� CREATESTRUCT cs ���޸Ĵ������
	// ��ʽ

	BOOL bPreCreated = CEditView::PreCreateWindow(cs);
	cs.style &= ~(ES_AUTOHSCROLL|WS_HSCROLL);	// ���û���

	return bPreCreated;
}


// CTiShiTestView ��ӡ

BOOL CTiShiTestView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ׼��
	return CEditView::OnPreparePrinting(pInfo);
}

void CTiShiTestView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ��ʼ��ӡ
	CEditView::OnBeginPrinting(pDC, pInfo);
}

void CTiShiTestView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
	// Ĭ�� CEditView ������ӡ
	CEditView::OnEndPrinting(pDC, pInfo);
}


// CTiShiTestView ���

#ifdef _DEBUG
void CTiShiTestView::AssertValid() const
{
	CEditView::AssertValid();
}

void CTiShiTestView::Dump(CDumpContext& dc) const
{
	CEditView::Dump(dc);
}

CTiShiTestDoc* CTiShiTestView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTiShiTestDoc)));
	return (CTiShiTestDoc*)m_pDocument;
}
#endif //_DEBUG


// CTiShiTestView ��Ϣ�������

void CTiShiTestView::OnEditUndo()
{
	
}

void CTiShiTestView::On32771()
{
	//ts.CreateEx(this->GetSafeHwnd());

}

void CTiShiTestView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ts.Show(this->GetSafeHwnd(), TRUE);
	
	ts.Move(nChar);
	//this->SetFocus();
	CEditView::OnChar(nChar, nRepCnt, nFlags);
}

int CTiShiTestView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CEditView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	ts.CreateEx(this->GetSafeHwnd());
	CFileEx fe;

	ts.LoadString(fe.GetFilePath() + "\\LIST.TXT");
	return 0;
}
