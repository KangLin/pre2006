/*******************************************************************************************************
文件名：textmessage.cpp
功  能：实现文本信息的接收和发送
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-12-30
时  间：15:31:11

FileName：textmessage.cpp
Function：
Compiler：Visual C++ 6.0
Author：  KangLin
          Copyright 2004 KangLin
Date：    2004-12-30
Time：    15:31:11
*******************************************************************************************************/

#include "stdafx.h"
#include "..\中国象棋.h"
#include "..\mainfrm.h"
#include "TextMessage.h"
#include <afxctl.h>
#include ".\textmessage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTextMessage dialog
IMPLEMENT_DYNCREATE(CTextMessage, CDialog)

CTextMessage::CTextMessage(CWnd* pParent /*=NULL*/)
	: CDialog(CTextMessage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTextMessage)
	m_szUserName = _T("所有人");
	//}}AFX_DATA_INIT
}


void CTextMessage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTextMessage)
	DDX_Control(pDX, IDC_USERNAME, m_ctrUserName);
	DDX_Control(pDX, IDC_RICHTEXTRECEIVE, m_reReceive);
	DDX_Control(pDX, IDC_RICHTEXTSEND, m_reSend);
	DDX_CBString(pDX, IDC_USERNAME, m_szUserName);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTextMessage, CDialog)
	//{{AFX_MSG_MAP(CTextMessage)
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_BN_CLICKED(IDC_BUTTONSEND, OnSendClick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTextMessage message handlers

void CTextMessage::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	if(m_reSend.GetSafeHwnd())
	{
		m_reSend.MoveWindow(0, cy * 3 / 4, cx, cy / 8);
		m_reReceive.MoveWindow(0, 0, cx, cy * 3 / 4);
		m_btSend.MoveWindow(5 + cx / 2, cy * 7 / 8 + 5, cx / 2 - 5, cy * 1 / 8 - 10);
		CRect rect;
		m_ctrUserName.GetWindowRect(&rect);
        int w = rect.Width();
		int h = rect.Height();
		m_ctrUserName.MoveWindow(0, cy * 15 / 16 - h / 2, cx / 2, cy * 1 / 8 - 10);
	}	
}

int CTextMessage::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	ShowWindow(SW_SHOW);

	m_btSend.Create(_T("发送"), WS_CHILD | WS_VISIBLE, CRect(0, 100, 100, 200), this, IDC_BUTTONSEND);
	m_btSend.SetIcon(IDI_SEND);
	m_btSend.SetRounded(TRUE);
    m_btSend.OffsetColor(CButtonST::BTNST_COLOR_BK_IN, 30);
	m_btSend.SetTooltipText(_T("发送消息(Ctrl + Enter)"));

	return 0;
}

void CTextMessage::OnSendClick()
{
    CString szUserName;
    m_ctrUserName.GetWindowText(szUserName);

    CString sztmp;
    sztmp = szUserName;
    sztmp.MakeLower();
    if(sztmp == _T("all"))
    {
        sztmp = _T("所有人");
        szUserName = sztmp;
    }
#ifndef _DEBUG
    if(sztmp != _T("所有人"))
    {
        if(m_ctrUserName.FindString(0, szUserName) == CB_ERR)
        {
            MessageBox(_T("无此用户"), _T("无此用户"), MB_ICONERROR | MB_OK);
            return;
        }
    }
    if(((CChessApp*)AfxGetApp())->m_gszUserName == szUserName)
    {
        MessageBox(_T("不能向自己发送消息"), _T("选择用户"), MB_ICONERROR | MB_OK);
        return;
    }

#endif
	//发送数据
    m_reSend.SetSelStart(0);
    m_reSend.SetSelText(((CChessApp*)AfxGetApp())->m_gszUserName 
        + _T(" 对 ") + szUserName + _T(" 说：") );
    SetReceiveText(m_reSend.GetTextRTF());
    CCommand cmd;
    cmd.SetCommand(g_cmdSendTextMessage);   //发送文本消息
    cmd.AddPara(((CChessApp*)AfxGetApp())->m_gszUserName);
    cmd.AddPara(szUserName);
    cmd.AddPara(m_reSend.GetTextRTF());
	m_reSend.SetTextRTF(_T(""));
    CMainFrame* pwnd;
    pwnd = (CMainFrame*)AfxGetMainWnd();
    pwnd->SendData(&cmd);
}

BEGIN_EVENTSINK_MAP(CTextMessage, CDialog)
    //{{AFX_EVENTSINK_MAP(CTextMessage)
	ON_EVENT(CTextMessage, IDC_RICHTEXTSEND, -604 /* KeyUp */, OnKeyUpRichtextsend, VTS_PI2 VTS_I2)
	//}}AFX_EVENTSINK_MAP
END_EVENTSINK_MAP()

void CTextMessage::OnKeyUpRichtextsend(short FAR* KeyCode, short Shift) 
{
	if((Shift & CTRL_MASK) && (*KeyCode == VK_RETURN))
	{
		OnSendClick();
	}
}

/*******************************************************************************************************
函数名：SetReceiveText
功  能：设置接收到的文本
参  数：
         LPCSTR lpszText：接收到的文本
返回值：成功返回 TRUE
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-1
时  间：18:15:25
*******************************************************************************************************/
BOOL CTextMessage::SetReceiveText(LPCSTR lpszText)
{
    //增加:调整光标插入点到最后

    m_reReceive.SetSelText(lpszText);
    return TRUE;
}
