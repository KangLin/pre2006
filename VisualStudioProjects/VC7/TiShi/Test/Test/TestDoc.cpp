// TestDoc.cpp : CTestDoc ���ʵ��
//

#include "stdafx.h"
#include "Test.h"

#include "TestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestDoc

IMPLEMENT_DYNCREATE(CTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CTestDoc, CDocument)
END_MESSAGE_MAP()


// CTestDoc ����/����

CTestDoc::CTestDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CTestDoc::~CTestDoc()
{
}

BOOL CTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CTestDoc ���л�

void CTestDoc::Serialize(CArchive& ar)
{
	// CEditView ����һ�������������л��ı༭�ؼ�
	reinterpret_cast<CEditView*>(m_viewList.GetHead())->SerializeRaw(ar);
}


// CTestDoc ���

#ifdef _DEBUG
void CTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTestDoc ����
