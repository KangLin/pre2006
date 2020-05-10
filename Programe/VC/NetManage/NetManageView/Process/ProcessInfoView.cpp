/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    ProcessInfoView.cpp
\brief   详细描述
\version 1.0.0.1
\author  康  林 (kl222@126.com)
\date    2007年8月23日  22:25:30
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

// ProcessInfoView.cpp : implementation file
//

#include "stdafx.h"
#include "..\NetManageView.h"
#include ".\ProcessView.h"
#include "..\..\plus\Process\ProcessCommand.h"
#include "ProcessInfoView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CProcessInfoView

IMPLEMENT_DYNAMIC(CProcessInfoView, CWnd)

CProcessInfoView::CProcessInfoView()
{
	m_pDocument = NULL;
}

CProcessInfoView::~CProcessInfoView()
{
}


BEGIN_MESSAGE_MAP(CProcessInfoView, CWnd)
	ON_WM_SIZE()
	ON_WM_CREATE()
END_MESSAGE_MAP()



// CProcessInfoView message handlers


void CProcessInfoView::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CRect rect;
	GetClientRect(&rect);
	
	if(m_lstProcess.GetSafeHwnd())
	{
		m_lstProcess.MoveWindow(&rect);
	} // 结束 if(m_lstProcess.GetSafeHwnd())

}

int CProcessInfoView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect(&rect);
	
	if(!m_lstProcess.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS /*| WS_BORDER*/ | WS_TABSTOP, rect, this, ID_PROCESS_INFORMATION))
	{
		TRACE(_T("Failed create list.\n"));
		return - 1;
	}// 结束 if(!m_lstProcess.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS | WS_TABSTOP, rect, this, ID_PROCESS_INFORMATION))

	int nCol = 0;
	m_lstProcess.InsertColumn(nCol++, _T("序号"), LVCFMT_CENTER, 50);
	m_lstProcess.InsertColumn(nCol++, _T("映像名"), LVCFMT_CENTER, 100);
	m_lstProcess.InsertColumn(nCol++, _T("进程 ID"), LVCFMT_CENTER, 50);
	m_lstProcess.InsertColumn(nCol++, _T("父 ID"), LVCFMT_CENTER, 50);
	m_lstProcess.InsertColumn(nCol++, _T("优先级"), LVCFMT_CENTER, 50);
	m_lstProcess.InsertColumn(nCol++, _T("进程引用数"), LVCFMT_CENTER, 100);
	m_lstProcess.InsertColumn(nCol++, _T("线程数"), LVCFMT_CENTER, 50);
	m_lstProcess.InsertColumn(nCol++, _T("路径"), LVCFMT_CENTER, 500);

	m_lstProcess.SendMessage (LVM_SETEXTENDEDLISTVIEWSTYLE, 0,
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
//	m_lstProcess.EnableMarkSortedColumn ();


	//SendMessage(WM_SIZE, NULL, NULL);

	return 0;
}

int CProcessInfoView::OnInitialUpdate(CNetManageViewDoc * pDocument)
{
	int nRet = S_OK;
	ASSERT(pDocument);
	m_pDocument = pDocument;
	if(m_pDocument)
	{
		CCommand cmd;
		cmd.SetCommand(CMD_QUERY_ALL_PROCESS);
		if(pDocument->m_pSocket)
		{
			pDocument->Send(pDocument->m_pSocket, &cmd);
		} // 结束 if(pDocument->m_pSocket)
	} // 结束 if(m_pDocument)

	return nRet;
}

/*!
\brief   处理应答命令
\param   CCommand & cmd：
\return  类型为 int 。
\version 1.0.0.1
\author  康  林
\date    2007-8-22 9:55:19
*/
int CProcessInfoView::ProcessCommand(CCommand & cmd)
{
	int nRet = S_OK;
	
	if(cmd.GetCommand() == CMD_ANSWER_ALL_PROCESS)
	{
		vector < CProcessInformation::PROCESS_INFO > info;
		CProcessCommand processCmd(&cmd);
		nRet = processCmd.AnswerAllProcess(&info);
		if(S_OK != nRet)
		{
			return nRet;
		}// 结束 if(S_OK != nRet)

		m_lstProcess.DeleteAllItems();

		int nRows = info.size();
		for(int i = 0; i < nRows; i++)
		{
			int nCol = 1;
			CProcessInformation::PROCESS_INFO * pInfo = &info[i];
			CString szTmp;
			szTmp.Format(_T("%d"), i + 1);
			m_lstProcess.InsertItem(i, szTmp);
			m_lstProcess.SetItemText(i, nCol++, pInfo->szProcessName.c_str());
			szTmp.Format(_T("%d"), pInfo->dwProcessID);
			m_lstProcess.SetItemText(i, nCol++, szTmp);
			szTmp.Format(_T("%d"), pInfo->dwParentID);
			m_lstProcess.SetItemText(i, nCol++, szTmp);
			szTmp.Format(_T("%d"), pInfo->dwPriority);
			m_lstProcess.SetItemText(i, nCol++, szTmp);
			szTmp.Format(_T("%d"), pInfo->dwUsage);
			m_lstProcess.SetItemText(i, nCol++, szTmp);
			szTmp.Format(_T("%d"), pInfo->dwThreadCount);
			m_lstProcess.SetItemText(i, nCol++, szTmp);
			m_lstProcess.SetItemText(i, nCol++, pInfo->szProcessPath.c_str());
		} // 结束 for(int i = 0; i < nRows; i++)
	} // 结束 if(cmd.GetCommand() == QUERY_ALL_PROCESS)
	return nRet;
}