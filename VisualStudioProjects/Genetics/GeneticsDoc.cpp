// GeneticsDoc.cpp :  CGeneticsDoc ���ʵ��
//

#include "stdafx.h"
#include "Genetics.h"

#include "GeneticsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGeneticsDoc

IMPLEMENT_DYNCREATE(CGeneticsDoc, CDocument)

BEGIN_MESSAGE_MAP(CGeneticsDoc, CDocument)
END_MESSAGE_MAP()


// CGeneticsDoc ����/����

CGeneticsDoc::CGeneticsDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CGeneticsDoc::~CGeneticsDoc()
{
}

BOOL CGeneticsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CGeneticsDoc ���л�

void CGeneticsDoc::Serialize(CArchive& ar)
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


// CGeneticsDoc ���

#ifdef _DEBUG
void CGeneticsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGeneticsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGeneticsDoc ����
