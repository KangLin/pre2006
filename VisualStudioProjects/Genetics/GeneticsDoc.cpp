// GeneticsDoc.cpp :  CGeneticsDoc 类的实现
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


// CGeneticsDoc 构造/析构

CGeneticsDoc::CGeneticsDoc()
{
	// TODO: 在此添加一次性构造代码

}

CGeneticsDoc::~CGeneticsDoc()
{
}

BOOL CGeneticsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CGeneticsDoc 序列化

void CGeneticsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CGeneticsDoc 诊断

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


// CGeneticsDoc 命令
