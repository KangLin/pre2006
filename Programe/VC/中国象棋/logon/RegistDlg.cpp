// RegistDlg.cpp : implementation file
//

#include "stdafx.h"
#include "..\�й�����.h"
#include "..\mainfrm.h"
#include "RegistDlg.h"
#include "LogonDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRegistDlg dialog


CRegistDlg::CRegistDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRegistDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRegistDlg)
	m_uAge = 20;
	m_szPassword = _T("");
	m_szPassword2 = _T("");
	m_szUserName = _T("");
	m_iImage = 0;
	m_iSex = 0;
	//}}AFX_DATA_INIT
}


void CRegistDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRegistDlg)
	DDX_Control(pDX, IDC_COMBOIMAGE, m_ctrlImage);
	DDX_Text(pDX, IDC_EDITAGE, m_uAge);
	DDX_Text(pDX, IDC_EDITPASSWORD, m_szPassword);
	DDX_Text(pDX, IDC_EDITPASSWORD2, m_szPassword2);
	DDX_Text(pDX, IDC_EDITUSERNAME, m_szUserName);
	DDX_CBIndex(pDX, IDC_COMBOIMAGE, m_iImage);
	DDX_CBIndex(pDX, IDC_COMBOSEX, m_iSex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRegistDlg, CDialog)
	//{{AFX_MSG_MAP(CRegistDlg)
	ON_CBN_SELCHANGE(IDC_COMBOIMAGE, OnSelchangeComboimage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRegistDlg message handlers

BOOL CRegistDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CFileFind ff;
	if( ff.FindFile( ((CChessApp*)AfxGetApp())->m_gszImageDir + _T("\\*.*")) )
	{
		while(ff.FindNextFile())
		{
			if( !(ff.IsDots() && ff.IsDirectory()) )
			m_ctrlImage.AddString(ff.GetFileName());
		}
		
	}
	m_iImage = 0;
	CRect rect;
	m_ctrlImage.GetWindowRect(&rect);
	this->ScreenToClient(&rect);
	rect.left = rect.right + 20;
	rect.right = rect.left + 36;
	rect.bottom = rect.top + 36;
	m_staticexImage.Create(NULL, NULL, WS_CHILD | WS_VISIBLE, rect, this, NULL);
	CString szFileName;
	m_ctrlImage.GetLBText(m_iImage, szFileName);
    DisplayImage(szFileName);
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CRegistDlg::DisplayImage(LPCSTR szImageName)
{
	CString szPath;
	szPath = ((CChessApp*)AfxGetApp())->m_gszImageDir + _T("\\");
	szPath += szImageName;
    m_staticexImage.m_BKPicture.Load(szPath);
    m_staticexImage.Invalidate();

	return TRUE;
}

void CRegistDlg::OnSelchangeComboimage() 
{
	// TODO: Add your control notification handler code here
	this->UpdateData();
	CString szFileName;
	m_ctrlImage.GetLBText(m_iImage, szFileName);
    DisplayImage(szFileName);
}

void CRegistDlg::OnOK() 
{
    // TODO: Add extra validation here
    this->UpdateData();
    if(m_szUserName.IsEmpty() || m_szPassword.IsEmpty())
    {
        MessageBox(_T("û�����û��������롣���������롣"), _T("�������"), MB_OK | MB_ICONERROR);
        return;
    }
    
    CString szUser;
    CString szPassword;
    szUser = m_szUserName;
    szPassword = m_szPassword;
    szUser.TrimLeft();    
    szUser.MakeLower();
    szPassword.TrimLeft();
    
    if(szUser == _T("������") || szUser == _T("all"))
    {
        MessageBox(_T("�û�������Ϊ\"������\"��\"ALL\"�����������롣"), _T("�������"), MB_OK | MB_ICONERROR);
        return;
    }
    if(szUser == "" || szPassword == "")
    {
        MessageBox(_T("�û��������벻��Ϊ�ո����������롣"), _T("�������"), MB_OK | MB_ICONERROR);
        return;
    }

#ifndef _DEBUG
    if(m_szPassword != m_szPassword2)
    {
        MessageBox(_T("�����������벻ͬ�����������롣"), _T("�������"), MB_OK | MB_ICONERROR);
        m_szPassword.Empty();
        m_szPassword2.Empty();
        UpdateData(FALSE);
        return;
    }
#endif

    //����������͵�¼��Ϣ
    CMainFrame* pwnd = ((CLogonDlg*)GetParent())->m_pParent;
    CCommand command;
    command.SetCommand(g_cmdRegist);
    command.AddPara(m_szUserName);
    command.AddPara(m_szPassword);
    if(m_iSex == 0)
    {
        command.AddPara(_T("��"));
    }
    else
    {
        command.AddPara(_T("Ů"));
    }
    command.AddPara(m_uAge);
    CString sztmp;
    m_ctrlImage.GetLBText(m_iImage, sztmp);
    command.AddPara(sztmp);
    pwnd->SendData(&command);
	//CDialog::OnOK();
}

/*******************************************************************************************************
��������Receive
��  �ܣ�������������ص�ע������
��  ����
         CCommand *pCmd������
����ֵ����
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2005-1-1
ʱ  �䣺12:33:54
*******************************************************************************************************/
void CRegistDlg::Receive(CCommand *pCmd)
{
    long cmd;
    cmd = pCmd->GetLongPara();
    switch(cmd)
    {
    case g_cmdRegistSuccess:
        {
        CString sztmp(_T("ע��ɹ���\n���ס�û���������\n"));
        sztmp = sztmp + _T("�û�����") + m_szUserName + _T("\n���룺") + m_szPassword;
        MessageBox(sztmp, _T("ע��ɹ�"), MB_OK | MB_ICONWARNING);
        CDialog::OnOK();
        }
        break;
    case g_cmdRegistHadUser:
        MessageBox(_T("�û� ") + m_szUserName + _T(" �Ѵ���"), _T("�û��Ѵ���"), MB_OK | MB_ICONERROR);
        break;
    }
}
