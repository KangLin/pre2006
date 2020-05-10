// HTMLDlgDoc.cpp : CHTMLDlgDoc 类的实现
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


// CHTMLDlgDoc 构造/析构

CHTMLDlgDoc::CHTMLDlgDoc()
{
	// TODO: 在此添加一次性构造代码

}

CHTMLDlgDoc::~CHTMLDlgDoc()
{
}

BOOL CHTMLDlgDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CHTMLDlgDoc 序列化

void CHTMLDlgDoc::Serialize(CArchive& ar)
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


// CHTMLDlgDoc 诊断

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


// CHTMLDlgDoc 命令
