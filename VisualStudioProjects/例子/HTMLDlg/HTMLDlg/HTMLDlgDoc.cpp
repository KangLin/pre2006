// HTMLDlgDoc.cpp : CHTMLDlgDoc ���ʵ��
//

#include "stdafx.h"
#include "HTMLDlg.h"

#include "HTMLDlgDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CHTMLDlgDoc

IMPLEMENT_DYNCREATE(CHTMLDlgDoc, CDocument)

BEGIN_MESSAGE_MAP(CHTMLDlgDoc, CDocument)
END_MESSAGE_MAP()


// CHTMLDlgDoc ����/����

CHTMLDlgDoc::CHTMLDlgDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CHTMLDlgDoc::~CHTMLDlgDoc()
{
}

BOOL CHTMLDlgDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CHTMLDlgDoc ���л�

void CHTMLDlgDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CHTMLDlgDoc ���

#ifdef _DEBUG
void CHTMLDlgDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CHTMLDlgDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CHTMLDlgDoc ����
