// process\ProcessModuleInfo.cpp : implementation file
//

#include "stdafx.h"
#include "..\NetManageView.h"
#include "ProcessModuleInfo.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

// CProcessModuleInfo

IMPLEMENT_DYNAMIC(CProcessModuleInfo, CWnd)

CProcessModuleInfo::CProcessModuleInfo()
{

}

CProcessModuleInfo::~CProcessModuleInfo()
{
}


BEGIN_MESSAGE_MAP(CProcessModuleInfo, CWnd)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_CBN_SELCHANGE(ID_PROCESS_MODULE_INFORMATION_COMOBBOX, OnSelectChange)
END_MESSAGE_MAP()



// CProcessModuleInfo message handlers


void CProcessModuleInfo::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);

	CRect rect;
	GetClientRect(&rect);

	if(m_lstModule.GetSafeHwnd() && m_ComboBox.GetSafeHwnd())
	{
		CRect rectCombox(0, 0, rect.Width(), 250);
		m_ComboBox.MoveWindow(&rectCombox);
		m_ComboBox.GetWindowRect(&rectCombox);
		ScreenToClient(&rectCombox);
		CRect rectList(0, rectCombox.Height(), rect.Width(), rect.Height());
		m_lstModule.MoveWindow(&rectList);
	} // 结束 if(m_lstModule.GetSafeHwnd() && m_ComboBox.GetSafeHwnd())
}

int CProcessModuleInfo::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rect;
	GetClientRect(&rect);
	if(!m_ComboBox.Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, rect, this, ID_PROCESS_MODULE_INFORMATION_COMOBBOX))
	{
		TRACE(_T("Failed create combox box.\n"));
		return -1;
	} // 结束 if(!m_ComboBox.Create(WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL, rect, this, ID_PROCESS_MODULE_INFORMATION_COMOBBOX))

	if(!m_lstModule.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS /*| WS_BORDER*/ | WS_TABSTOP, rect, this, ID_PROCESS_MODULE_INFORMATION))
	{
		TRACE(_T("Failed create list.\n"));
		return -1;
	}// 结束 if(!m_lstModule.Create(WS_CHILD | WS_VISIBLE | LVS_REPORT | LVS_SHOWSELALWAYS | WS_TABSTOP, rect, this, ID_PROCESS_MODULE_INFORMATION))

	m_ComboBox.SetFont(m_lstModule.GetFont());

	m_lstModule.SendMessage(LVM_SETEXTENDEDLISTVIEWSTYLE, 0,
		LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

	int nCol = 0;
	m_lstModule.InsertColumn(nCol++, _T("序号"), LVCFMT_CENTER, 30);
	m_lstModule.InsertColumn(nCol++, _T("模块名"), LVCFMT_CENTER, 100);
	m_lstModule.InsertColumn(nCol++, _T("模块全局引用数"), LVCFMT_CENTER, 80);
	m_lstModule.InsertColumn(nCol++, _T("模块在本进程中的引用数"), LVCFMT_CENTER, 100);
	m_lstModule.InsertColumn(nCol++, _T("基址"), LVCFMT_CENTER, 50);
	m_lstModule.InsertColumn(nCol++, _T("模块尺寸"), LVCFMT_CENTER, 50);
	m_lstModule.InsertColumn(nCol++, _T("模块全路径"), LVCFMT_CENTER, 500);

	return 0;
}

int CProcessModuleInfo::OnInitialUpdate(CNetManageViewDoc * pDocument)
{
	int nRet = S_OK;
	ASSERT(pDocument);
	m_pDocument = pDocument;
	if(m_pDocument)
	{
		CCommand cmd;
		cmd.SetCommand(CMD_QUERY_ALL_PROCESS_MODULE);
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
\date    2007-8-22 9:55:04
*/
int CProcessModuleInfo::ProcessCommand(CCommand & cmd)
{
	int nRet = S_OK;
	if(cmd.GetCommand() == CMD_ANSWER_ALL_PROCESS_MODULE)
	{
		m_Info.clear();
		m_ComboBox.ResetContent();

		CProcessCommand processCmd(&cmd);
		nRet = processCmd.AnswerAllProcessModule(&m_Info);
		vector<CProcessInformation::PROCESS_MODULE_INFO>::iterator it;
		for(it = m_Info.begin(); it != m_Info.end(); it++)
		{
			CProcessInformation::PPROCESS_MODULE_INFO pInfo;
			pInfo = &(*it);
			m_ComboBox.AddString(pInfo->szProcessName.c_str());
		}// 结束 for(it = m_Info.begin(); it != m_Info.end(); it++)

		m_ComboBox.SetCurSel(0);
		OnSelectChange();
	}

	return nRet;
}

void CProcessModuleInfo::OnSelectChange()
{
	int nIndex = 0;
	nIndex = m_ComboBox.GetCurSel();

	try
	{
		if(m_Info.size() == 0 || nIndex >= m_Info.size())
		{
			return;
		}

		m_lstModule.DeleteAllItems();

		int nRows = m_Info.at(nIndex).Module.size();
		for(int i = 0; i < nRows; i++)
		{
			int nCol = 1;
			CProcessInformation::PMODULEINFO pModule;
			pModule = &(m_Info[nIndex].Module.at(i));
			CString szTmp;
			szTmp.Format(_T("%d"), i + 1);
			m_lstModule.InsertItem(i, szTmp);
			m_lstModule.SetItemText(i, nCol++, pModule->szModuleName.c_str());
			szTmp.Format(_T("%d"), pModule->dwGlbUsege);
			m_lstModule.SetItemText(i, nCol++, szTmp);
			szTmp.Format(_T("%d"), pModule->dwProcUsage);
			m_lstModule.SetItemText(i, nCol++, szTmp);
			szTmp.Format(_T("0x%X"), pModule->dwBaseAddr);
			m_lstModule.SetItemText(i, nCol++, szTmp);
			szTmp.Format(_T("%d"), pModule->dwSize);
			m_lstModule.SetItemText(i, nCol++, szTmp);
			m_lstModule.SetItemText(i, nCol++, pModule->szExePath.c_str());
		} // 结束 for(int i = 0; i < nRows; i++)
	}
	catch (...)
	{
		TRACE(_T("异常\n"));
	};
	

}