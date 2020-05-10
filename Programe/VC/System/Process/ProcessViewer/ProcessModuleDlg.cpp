// ProcessModuleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProcessViewer.h"
#include "ProcessModuleDlg.h"
#include "..\ProcessViewer.h"

// CProcessModuleDlg dialog

IMPLEMENT_DYNAMIC(CProcessModuleDlg, CDialog)

CProcessModuleDlg::CProcessModuleDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CProcessModuleDlg::IDD, pParent)
{

}

CProcessModuleDlg::~CProcessModuleDlg()
{
}

void CProcessModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PROCESS, m_lstProcess);
	DDX_Control(pDX, IDC_LIST_MODULE, m_lstModule);
}


BEGIN_MESSAGE_MAP(CProcessModuleDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CProcessModuleDlg::OnBnClickedOk)
	ON_LBN_DBLCLK(IDC_LIST_PROCESS, &CProcessModuleDlg::OnLbnDblclkListProcess)
END_MESSAGE_MAP()


// CProcessModuleDlg message handlers

void CProcessModuleDlg::OnBnClickedOk()
{
	int i = 0;
	vector < _tstring > processName;
	vector < DWORD > processID;
	m_lstProcess.ResetContent();
	CProcessViewer p;
	p.ListProcessNameAndID(&processName, &processID);
	for(i = 0; i < processID.size(); i++)
	{
		_tstring name = processName[i];
		m_lstProcess.AddString(name.c_str());
	}// ½áÊø for(i = 0; i < processID.size(); i++)

	UpdateData(TRUE);
	
}

void CProcessModuleDlg::OnLbnDblclkListProcess()
{
	int i = 0;
	CString szTmp;
	m_lstModule.ResetContent();
	m_lstProcess.GetText(m_lstProcess.GetCurSel(), szTmp);
	vector < _tstring > moduleName;
	CProcessViewer p;
	p.GetModulesName(p.GetProcessID(szTmp), &moduleName);
	for(i = 0; i < moduleName.size(); i++)
	{
		m_lstModule.AddString(moduleName[i].c_str());
	} // ½áÊø for(i = 0; i < moduleName.size(); i++)

}

BOOL CProcessModuleDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	OnBnClickedOk();

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
