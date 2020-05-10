// ProcessViewerDoc.cpp : CProcessViewerDoc 类的实现
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


// CProcessViewerDoc 构造/析构

CProcessViewerDoc::CProcessViewerDoc()
{
	// TODO: 在此添加一次性构造代码

}

CProcessViewerDoc::~CProcessViewerDoc()
{
}

BOOL CProcessViewerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CProcessViewerDoc 序列化

void CProcessViewerDoc::Serialize(CArchive& ar)
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


// CProcessViewerDoc 诊断

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


// CProcessViewerDoc 命令
