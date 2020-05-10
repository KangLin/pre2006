/*******************************************************************************************************
��Ȩ���� (C) 2006 ����������Ȩ����
�ļ�����Console.cpp
��  ����ʵ�ֿ���̨�ĶԻ��򣬾���Ĺ���ʵ���� CCommandWnd ����ɡ������������һ��ʵ����
��  ����2.0.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2006��11��10��
ʱ  �䣺15:58:00
��������Microsoft Visual Studio 8.0 ���� C/C++ 8.0
*******************************************************************************************************/
// Console\Console.cpp : implementation file
//

#include "stdafx.h"
#include "Console.h"


// CConsoleDlg dialog

//IMPLEMENT_DYNAMIC(CConsoleDlg, CDialog)
IMPLEMENT_DYNCREATE(CConsoleDlg, CDialog)


CConsoleDlg::CConsoleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConsoleDlg::IDD, pParent)
{

}

CConsoleDlg::~CConsoleDlg()
{
}

void CConsoleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CConsoleDlg, CDialog)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CConsoleDlg message handlers

BOOL CConsoleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	TRACE(_T("OninitDialog\n"));

	if(! m_Cmd.CreateEx(NULL, NULL, NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL, CRect(0, 0, 0, 0), this, NULL))
	{
		TRACE(_T("Failed to create console output view\n"));
		return - 1;
	} // ���� if(! m_Cmd.CreateEx(NULL, NULL, NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL, CRect(0, 0, 0, 0), this, NULL))

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}

void CConsoleDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);

	if(m_Cmd.GetSafeHwnd())
	{
		m_Cmd.MoveWindow(0, 0, cx, cy);
	} // ���� if(m_Cmd.GetSafeHwnd())
}

BOOL CConsoleDlg::PreTranslateMessage(MSG* pMsg)
{
	if(pMsg->message == WM_KEYDOWN || pMsg->message == WM_CHAR || pMsg->message == WM_KEYDOWN)
	{
		m_Cmd.SendMessage(pMsg->message, pMsg->wParam, pMsg->lParam);
	}// ���� if(pMsg->message == WM_KEYDOWN || pMsg->message == WM_CHAR || pMsg->message == WM_KEYDOWN)

	return CDialog::PreTranslateMessage(pMsg);
}

void CConsoleDlg::OnOK()
{
	
	//CDialog::OnOK();
}

void CConsoleDlg::OnCancel()
{
	//CDialog::OnCancel();
}
