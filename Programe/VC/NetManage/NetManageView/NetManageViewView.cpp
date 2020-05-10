// NetManageViewView.cpp : implementation of the CNetManageViewView class
//

#include "stdafx.h"
#include "NetManageView.h"

#include "NetManageViewDoc.h"
#include "NetManageViewView.h"
#include "process\ProcessView.h"
#include "memoryview.h"
#include "systeminfo\SystemInfoView.h"
#include ".\deviceinfo\DeviceInfo.h"

#ifdef _DEBUG
#ifdef DEBUG_NEW
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
#endif

// CNetManageViewView

IMPLEMENT_DYNCREATE(CNetManageViewView, CBCGPTabView)

BEGIN_MESSAGE_MAP(CNetManageViewView, CBCGPTabView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CBCGPTabView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, OnFilePrintPreview)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CBCGPTabView::OnFilePrint)
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CNetManageViewView construction/destruction

CNetManageViewView::CNetManageViewView()
{
	// TODO: add construction code here

}

CNetManageViewView::~CNetManageViewView()
{
}

BOOL CNetManageViewView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CBCGPTabView::PreCreateWindow(cs);
}

// CNetManageViewView drawing

void CNetManageViewView::OnDraw(CDC* /*pDC*/)
{
	CNetManageViewDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	// TODO: add draw code for native data here
}


// CNetManageViewView printing

void CNetManageViewView::OnFilePrintPreview()
{
	BCGPPrintPreview (this);
}

BOOL CNetManageViewView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CNetManageViewView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CNetManageViewView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CNetManageViewView diagnostics

#ifdef _DEBUG
void CNetManageViewView::AssertValid() const
{
	CBCGPTabView::AssertValid();
}

void CNetManageViewView::Dump(CDumpContext& dc) const
{
	CBCGPTabView::Dump(dc);
}

CNetManageViewDoc* CNetManageViewView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNetManageViewDoc)));
	return (CNetManageViewDoc*)m_pDocument;
}
#endif //_DEBUG



int CNetManageViewView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CBCGPTabView::OnCreate(lpCreateStruct) == -1)
		return -1;

	//������ǩλ�õ��Ϸ�
	m_wndTabs.SetLocation(CBCGPTabWnd::LOCATION_TOP);
	m_wndTabs.RecalcLayout();
	m_wndTabs.RedrawWindow();
	//�����Զ����ñ�ǩ��ɫ
	//m_wndTabs.EnableAutoColor(TRUE);
	//��ǩ��ʽ
	m_wndTabs.ModifyTabStyle(CBCGPTabWnd::STYLE_3D);

	//�����������ͼ
	AddView(RUNTIME_CLASS(CProcessView), _T("������Ϣ"), 0);
	AddView(RUNTIME_CLASS(CMemoryView), _T("�ڴ���Ϣ"), 1);
	AddView(RUNTIME_CLASS(CSystemInfoView), _T("ϵͳ��Ϣ"), 2);
	AddView(RUNTIME_CLASS(CDeviceInfo), _T("ϵͳ��Ϣ"), 3);

	return 0;
}


