// Process.cpp : implementation file
//

#include "stdafx.h"
#include "..\NetManageView.h"
#include "ProcessinfoView.h"
#include "ProcessModuleInfo.h"
#include "ProcessView.h"
#include "..\MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CProcess

IMPLEMENT_DYNCREATE(CProcessView, CNetManageBaseView)

CProcessView::CProcessView()
{

}

CProcessView::~CProcessView()
{
}

BEGIN_MESSAGE_MAP(CProcessView, CNetManageBaseView)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()


// CProcess drawing

void CProcessView::OnDraw(CDC* pDC)
{
	CDocument* pDoc = GetDocument();
	// TODO: add draw code here
}


// CProcess diagnostics

#ifdef _DEBUG
void CProcessView::AssertValid() const
{
	CNetManageBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CProcessView::Dump(CDumpContext& dc) const
{
	CNetManageBaseView::Dump(dc);
}
#endif

CNetManageViewDoc* CProcessView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CNetManageViewDoc)));
	return (CNetManageViewDoc*)m_pDocument;
}
#endif //_DEBUG


// CProcess message handlers
void CProcessView::OnSize(UINT nType, int cx, int cy)
{
	CNetManageBaseView::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(&rect);
	if(m_tabWnd.GetSafeHwnd())
	{
		m_tabWnd.MoveWindow(&rect);
	}// 结束 if(m_tabWnd.GetSafeHwnd())

}

int CProcessView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CNetManageBaseView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect(&rect);
	if(!m_tabWnd.Create(CBCGPTabWnd::STYLE_3D, rect, this, ID_PROCESS_TABWINDOW, CBCGPTabWnd::LOCATION_TOP))
	{
		TRACE(_T("Failed create table window.\n"));
		return - 1;
	}// 结束 if(!m_tabWnd.Create(CBCGPTabWnd::STYLE_3D, rect, this, ID_PROCESS_TABWINDOW, CBCGPTabWnd::LOCATION_TOP))
	//自动调整标签颜色
	//m_tabWnd.EnableAutoColor();


	if(!m_ProcessInfo.Create(NULL, NULL, WS_CHILD | WS_VISIBLE /*| WS_BORDER*/ | WS_TABSTOP, rect, &m_tabWnd, ID_VIEW_PROCESS_INFOMATION))
	{
		TRACE(_T("Failed create process window.\n"));
		return - 1;
	}// 结束 if(!m_ProcessInfo.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | WS_TABSTOP, rect, &m_tabWnd, ID_VIEW_PROCESS_INFOMATION))

	if(!m_ProcessModuleInfo.Create(NULL, NULL, WS_CHILD | WS_VISIBLE /*| WS_BORDER*/ | WS_TABSTOP, rect, &m_tabWnd, ID_VIEW_PROCESS_MODULE_INFOMATION))
	{
		TRACE(_T("Failed create process and module window.\n"));
		return - 1;
	} // 结束 if(!m_ProcessModuleInfo.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_TABSTOP, rect, &m_tabWnd, ID_VIEW_PROCESS_MODULE_INFOMATION))

	if(!m_ProcessHide.Create(NULL, NULL, WS_CHILD | WS_VISIBLE /*| WS_BORDER*/ | WS_TABSTOP, rect, &m_tabWnd, ID_VIEW_PROCESS_HIDE))
	{
		TRACE(_T("Failed create process hide window.\n"));
		return - 1;
	}// 结束 if(!m_ProcessHide.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_TABSTOP, rect, &m_tabWnd, ID_VIEW_PROCESS_HIDE))

	if(!m_ProcessHideList.Create(NULL, NULL, WS_CHILD | WS_VISIBLE /*| WS_BORDER*/ | WS_TABSTOP, rect, &m_tabWnd, ID_VIEW_PROCESS_HIDE_LIST))
	{
		TRACE(_T("Failed create process hide list window.\n"));
		return - 1;
	}// 结束 if(!m_ProcessHideList.Create(NULL, NULL, WS_CHILD | WS_VISIBLE | WS_TABSTOP, rect, &m_tabWnd, ID_VIEW_PROCESS_HIDE_LIST))

	m_tabWnd.AddTab(&m_ProcessInfo, _T("所有进程信息"), 0, FALSE);
	m_tabWnd.AddTab(&m_ProcessModuleInfo, _T("进程和模块信息"), 1, FALSE);
	m_tabWnd.AddTab(&m_ProcessHide, _T("进程隐藏"), 2, FALSE);
	m_tabWnd.AddTab(&m_ProcessHideList, _T("隐藏的进程例表"), 3, FALSE);

	return 0;
}

void CProcessView::OnInitialUpdate()
{
	CNetManageBaseView::OnInitialUpdate();

	//给子视图设置文档
	CNetManageViewDoc * pDoc = GetDocument();
	m_ProcessInfo.OnInitialUpdate(pDoc);
	m_ProcessModuleInfo.OnInitialUpdate(pDoc);
	m_ProcessHide.OnInitialUpdate(pDoc);
	m_ProcessHideList.OnInitialUpdate(pDoc);

}

/*!
\brief   处理应答命令
\param   CCommand & cmd：
\return  类型为 int 。
\version 1.0.0.1
\author  康  林
\date    2007-8-22 9:54:45
*/
int CProcessView::ProcessCommand(CCommand & cmd)
{
	int nRet = S_OK;
	m_ProcessInfo.ProcessCommand(cmd);
	m_ProcessModuleInfo.ProcessCommand(cmd);
	m_ProcessHide.ProcessCommand(cmd);
	m_ProcessHideList.ProcessCommand(cmd);

	return nRet;
}


void CProcessView::OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView)
{
	CNetManageBaseView::OnActivateView(bActivate, pActivateView, pDeactiveView);

	CMainFrame * pMain = (CMainFrame * )::AfxGetMainWnd();
	if(NULL == pMain)
	{
		TRACE(_T("Error AfxGetMainWnd()\n"));
		return;
	} // 结束 if(NULL == pMain)
	if(bActivate)
	{
		pMain->m_wndProcessToolBar.ShowWindow(SW_SHOW);
		TRACE(_T("show window\n"));
	}
	else
	{
		pMain->m_wndProcessToolBar.ShowWindow(SW_HIDE);
		TRACE(_T("hide window\n"));
	} // 结束 if(bActivate)

}
