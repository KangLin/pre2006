/*******************************************************************************************************
版权所有 (C) 2005 康林工作室；保留所有权利。
文件名：Regist.cpp
描  述：注册类
版  本：2005.6.0.1
作  者：康  林
E_Mail：kl222@126.com
日  期：2005年7月12日
时  间：19:05:54
编译器：Microsoft Development Environment 7.10 —— C/C++ 7.10
*******************************************************************************************************/
// D:\Programe\VC\Limit\Regist.cpp : 实现文件
//

#include "stdafx.h"
#include <comdef.h>
#include "regist.h"
#include ".\regist.h"

// CRegist 对话框

IMPLEMENT_DYNAMIC(CRegist, CDialog)
CRegist::CRegist(CWnd* pParent /*=NULL*/)
: CDialog(CRegist::IDD, pParent)
{
	m_hIcon = ::AfxGetApp()->LoadIcon(IDI_KL);
	m_dwMachinNo = 0;
	m_dwRegist = 0;

	m_edszThanks = _T("已经注册。谢谢您使用本软件。");
    m_szTitle = _T("注册");
	CRegKey key;

	CString szKey(_T("SoftWare\\Microsoft\\VisualStudio\\7.1\\AddIns\\VisualStudioNetExtendTools.Connect"));
	if(ERROR_SUCCESS != key.Open(HKEY_LOCAL_MACHINE, szKey))
	{
		m_bShow = TRUE; 
	}
	else
	{
		char data[100];
		ULONG iLen;
		key.QueryStringValue("Registry", data, &iLen);
		if(_tcsicmp(data, _T("False")))
		{
			m_bShow = TRUE;
		}
		else
		{
			m_bShow = FALSE; 
		} // 结束 if(_tcsicmp(data, _T("False")))
	} // 结束 if(ERROR_SUCCESS != key.Open(HKEY_LOCAL_MACHINE, szKey))
}

CRegist::~CRegist()
{
}

void CRegist::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_dwMachinNo);
	DDX_Text(pDX, IDC_EDIT2, m_dwRegist);
	DDX_Check(pDX, IDC_CHECK1, m_bShow);
	DDX_Control(pDX, IDC_EDIT3, m_edThanks);
	DDX_Text(pDX, IDC_EDIT3, m_edszThanks);
}


BEGIN_MESSAGE_MAP(CRegist, CDialog)
	ON_BN_CLICKED(IDC_CHECK1, OnBnClickedShow)
END_MESSAGE_MAP()


// CRegist 消息处理程序

BOOL CRegist::OnInitDialog()
{
    CDialog::OnInitDialog();

	SetWindowText(m_szTitle + _T("——注册"));

	CLimit limit(m_szTitle);
	if(limit.ValidateRegistNo(limit.GetRegistNoInRegedit()))
	{
		m_dwMachinNo = limit.GetMachineNo();
		m_dwRegist = limit.GetRegistNo();
		m_edThanks.ShowWindow(SW_SHOW);
	}
	else
	{
		m_edThanks.ShowWindow(SW_HIDE);
	} // 结束 if(limit.ValidateRegistNo(limit.GetRegistNoInRegedit()))

	this->UpdateData(FALSE);

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}

void CRegist::OnBnClickedShow()
{
	CRegKey key;
	CString szKey(_T("SoftWare\\Microsoft\\VisualStudio\\7.1\\AddIns\\VisualStudioNetExtendTools.Connect"));
	if(ERROR_SUCCESS != key.Open(HKEY_LOCAL_MACHINE, szKey))
	{
		if(ERROR_SUCCESS != key.Create(ERROR_SUCCESS, szKey))
		{
			return;
		} // 结束 if(ERROR_SUCCESS != key.Create(ERROR_SUCCESS, szKey))
	} // 结束 if(ERROR_SUCCESS != key.Open(HKEY_LOCAL_MACHINE, szKey))
	this->UpdateData();
	if(m_bShow)
	{
		key.SetValue("Registry", REG_SZ, _T("True"), sizeof(_T("True"))); 
	}
	else
	{
		key.SetValue("Registry", REG_SZ, _T("False"), sizeof(_T("False")));
	} // 结束 if(m_bShow)
	
	key.Close();
}