// TestSoftWareDoc.cpp :  CTestSoftWareDoc 类的实现
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


// CTestSoftWareDoc 构造/析构

CTestSoftWareDoc::CTestSoftWareDoc()
{
	// TODO: 在此添加一次性构造代码

}

CTestSoftWareDoc::~CTestSoftWareDoc()
{
}

BOOL CTestSoftWareDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CTestSoftWareDoc 序列化

void CTestSoftWareDoc::Serialize(CArchive& ar)
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


// CTestSoftWareDoc 诊断

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


// CTestSoftWareDoc 命令
