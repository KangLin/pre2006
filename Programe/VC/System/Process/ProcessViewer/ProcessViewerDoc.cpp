// ProcessViewerDoc.cpp : CProcessViewerDoc ���ʵ��
//

#include "stdafx.h"
#include "ProcessViewer.h"

#include "ProcessViewerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CProcessViewerDoc

IMPLEMENT_DYNCREATE(CProcessViewerDoc, CDocument)

BEGIN_MESSAGE_MAP(CProcessViewerDoc, CDocument)
END_MESSAGE_MAP()


// CProcessViewerDoc ����/����

CProcessViewerDoc::CProcessViewerDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CProcessViewerDoc::~CProcessViewerDoc()
{
}

BOOL CProcessViewerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CProcessViewerDoc ���л�

void CProcessViewerDoc::Serialize(CArchive& ar)
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


// CProcessViewerDoc ���

#ifdef _DEBUG
void CProcessViewerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CProcessViewerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CProcessViewerDoc ����
