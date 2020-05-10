/*******************************************************************************************************
��Ȩ���� (C) 2005 ���ֹ����ң���������Ȩ����
�ļ�����Regist.cpp
��  ����ע����
��  ����2005.6.0.1
��  �ߣ���  ��
E_Mail��kl222@126.com
��  �ڣ�2005��7��12��
ʱ  �䣺19:05:54
��������Microsoft Development Environment 7.10 ���� C/C++ 7.10
*******************************************************************************************************/
// D:\Programe\VC\Limit\Regist.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include <comdef.h>
#include "regist.h"
#include ".\regist.h"

// CRegist �Ի���

IMPLEMENT_DYNAMIC(CRegist, CDialog)
CRegist::CRegist(CWnd* pParent /*=NULL*/)
: CDialog(CRegist::IDD, pParent)
{
	m_hIcon = ::AfxGetApp()->LoadIcon(IDI_KL);
	m_dwMachinNo = 0;
	m_dwRegist = 0;

	m_edszThanks = _T("�Ѿ�ע�ᡣлл��ʹ�ñ������");
    m_szTitle = _T("ע��");
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
		} // ���� if(_tcsicmp(data, _T("False")))
	} // ���� if(ERROR_SUCCESS != key.Open(HKEY_LOCAL_MACHINE, szKey))
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


// CRegist ��Ϣ�������

BOOL CRegist::OnInitDialog()
{
    CDialog::OnInitDialog();

	SetWindowText(m_szTitle + _T("����ע��"));

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
	} // ���� if(limit.ValidateRegistNo(limit.GetRegistNoInRegedit()))

	this->UpdateData(FALSE);

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
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
		} // ���� if(ERROR_SUCCESS != key.Create(ERROR_SUCCESS, szKey))
	} // ���� if(ERROR_SUCCESS != key.Open(HKEY_LOCAL_MACHINE, szKey))
	this->UpdateData();
	if(m_bShow)
	{
		key.SetValue("Registry", REG_SZ, _T("True"), sizeof(_T("True"))); 
	}
	else
	{
		key.SetValue("Registry", REG_SZ, _T("False"), sizeof(_T("False")));
	} // ���� if(m_bShow)
	
	key.Close();
}