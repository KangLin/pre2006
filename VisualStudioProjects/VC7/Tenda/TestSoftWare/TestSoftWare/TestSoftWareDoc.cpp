// TestSoftWareDoc.cpp :  CTestSoftWareDoc ���ʵ��
//

#include "stdafx.h"
#include "TestSoftWare.h"

#include "TestSoftWareDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestSoftWareDoc

IMPLEMENT_DYNCREATE(CTestSoftWareDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestSoftWareDoc, CDocument)
END_MESSAGE_MAP()


// CTestSoftWareDoc ����/����

CTestSoftWareDoc::CTestSoftWareDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CTestSoftWareDoc::~CTestSoftWareDoc()
{
}

BOOL CTestSoftWareDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CTestSoftWareDoc ���л�

void CTestSoftWareDoc::Serialize(CArchive& ar)
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


// CTestSoftWareDoc ���

#ifdef _DEBUG
void CTestSoftWareDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestSoftWareDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTestSoftWareDoc ����
