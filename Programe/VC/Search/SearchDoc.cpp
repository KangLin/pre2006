// SearchDoc.cpp : implementation of the CSearchDoc class
//

#include "stdafx.h"
#include "Search.h"

#include "SearchDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchDoc

IMPLEMENT_DYNCREATE(CSearchDoc, CDocument)

BEGIN_MESSAGE_MAP(CSearchDoc, CDocument)
	//{{AFX_MSG_MAP(CSearchDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchDoc construction/destruction

CSearchDoc::CSearchDoc()
{
	// TODO: add one-time construction code here

}

CSearchDoc::~CSearchDoc()
{
}

BOOL CSearchDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CSearchDoc serialization

void CSearchDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}	
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CSearchDoc diagnostics

#ifdef _DEBUG
void CSearchDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CSearchDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSearchDoc commands
