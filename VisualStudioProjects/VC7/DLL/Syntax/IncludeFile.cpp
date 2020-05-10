// IncludeFile.cpp : 实现文件
//

#include "stdafx.h"
#include "Syntax.h"
#include "IncludeFile.h"
#include ".\includefile.h"
#include "resource.h"

// CIncludeFile 对话框

IMPLEMENT_DYNAMIC(CIncludeFile, CDialog)
CIncludeFile::CIncludeFile(CWnd* pParent /*=NULL*/)
	: CDialog(CIncludeFile::IDD, pParent)
{
	m_szFile = _T("");
    m_hIcon = AfxGetApp()->LoadIcon(IDI_KL);
}

CIncludeFile::~CIncludeFile()
{
}

void CIncludeFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_INPUTFILE, m_szFile);
}


BEGIN_MESSAGE_MAP(CIncludeFile, CDialog)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_BROWN, OnBnClickedButtonBrown)
END_MESSAGE_MAP()


// CIncludeFile 消息处理程序
BOOL CIncludeFile::OnInitDialog()
{
    CDialog::OnInitDialog();

    // 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

    // 增加:其它初始化

    return TRUE;  // return TRUE unless you set the focus to a control
    // 异常: OCX 属性页应返回 FALSE
}
void CIncludeFile::OnBnClickedOk()
{
	UpdateData();
	if(PathRelativePathTo(m_szRelBuf, m_szDocument, FILE_ATTRIBUTE_NORMAL, m_szFile, FILE_ATTRIBUTE_NORMAL))
	{
		m_szRelative = m_szRelBuf; 
	}
    else
	{
		m_szRelative = m_szFile;
	} // 结束 if(PathRelativePathTo(m_szRelBuf, m_szDocument, FILE_ATTRIBUTE_NORMAL, m_szFile, FILE_ATTRIBUTE_NORMAL))
	OnOK();
}

void CIncludeFile::OnBnClickedButtonBrown()
{
	CFileDialog fd(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("*.H|*.H"));
	if(fd.DoModal() == IDOK)
	{
		m_szFile = fd.GetPathName();
		UpdateData(FALSE);
	} // 结束 if(fd.DoModal() == IDOK)
}
