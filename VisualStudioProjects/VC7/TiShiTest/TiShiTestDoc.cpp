// TiShiTestDoc.cpp :  CTiShiTestDoc 类的实现
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


// CTiShiTestDoc 构造/析构

CTiShiTestDoc::CTiShiTestDoc()
{
	// TODO: 在此添加一次性构造代码

}

CTiShiTestDoc::~CTiShiTestDoc()
{
}

BOOL CTiShiTestDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	reinterpret_cast<CEditView*>(m_viewList.GetHead())->SetWindowText(NULL);

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CTiShiTestDoc 序列化

void CTiShiTestDoc::Serialize(CArchive& ar)
{
	// CEditView 包含一个处理所有序列化的编辑控件
	reinterpret_cast<CEditView*>(m_viewList.GetHead())->SerializeRaw(ar);
}


// CTiShiTestDoc 诊断

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


// CTiShiTestDoc 命令
