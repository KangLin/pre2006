// TiShiTestDoc.cpp :  CTiShiTestDoc ���ʵ��
//

#include "stdafx.h"
#include "TiShiTest.h"

#include "TiShiTestDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTiShiTestDoc

IMPLEMENT_DYNCREATE(CTiShiTestDoc, CDocument)

BEGIN_MESSAGE_MAP(CTiShiTestDoc, CDocument)
END_MESSAGE_MAP()


// CTiShiTestDoc ����/����

CTiShiTestDoc::CTiShiTestDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CTiShiTestDoc::~CTiShiTestDoc()
{
}

BOOL CTiShiTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	reinterpret_cast<CEditView*>(m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CTiShiTestDoc ���л�

void CTiShiTestDoc::Serialize(CArchive& ar)
{
	// CEditView ����һ�������������л��ı༭�ؼ�
	reinterpret_cast<CEditView*>(m_viewList.GetHead())->SerializeRaw(ar);
}


// CTiShiTestDoc ���

#ifdef _DEBUG
void CTiShiTestDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CTiShiTestDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CTiShiTestDoc ����
