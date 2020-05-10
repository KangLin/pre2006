// 中国象棋服务器View.cpp : implementation of the CChessView class
//

#include "stdafx.h"
#include "中国象棋服务器.h"
#include "中国象棋服务器doc.h"
#include "中国象棋服务器view.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CChessView

IMPLEMENT_DYNCREATE(CChessView, CFormView)

BEGIN_MESSAGE_MAP(CChessView, CFormView)
	//{{AFX_MSG_MAP(CChessView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChessView construction/destruction

CChessView::CChessView()
	: CFormView(CChessView::IDD)
{
	//{{AFX_DATA_INIT(CChessView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CChessView::~CChessView()
{
}

void CChessView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CChessView)
	DDX_Control(pDX, IDC_DATAGRID1, m_dgInfo);
	//}}AFX_DATA_MAP
}

BOOL CChessView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CChessView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();
}

/////////////////////////////////////////////////////////////////////////////
// CChessView printing

BOOL CChessView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CChessView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CChessView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CChessView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CChessView diagnostics

#ifdef _DEBUG
void CChessView::AssertValid() const
{
	CFormView::AssertValid();
}

void CChessView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CChessDoc* CChessView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChessDoc)));
	return (CChessDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CChessView message handlers

void CChessView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(m_dgInfo.GetSafeHwnd())
	{
		m_dgInfo.MoveWindow(0, 0, cx, cy);
	}
}

int CChessView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

	return 0;
}

void CChessView::OnEditCopy() 
{
	// TODO: Add your command handler code here
}

void CChessView::OnDraw(CDC* pDC) 
{
	m_dgInfo.SetRefDataSource(NULL);
//	m_dgInfo.ClearFields();
	m_dgInfo.SetRefDataSource((LPUNKNOWN) GetDocument()->m_AdoRecSet.GetRecordset());
//	m_dgInfo.Refresh();	
}
