// IncludeFile.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Syntax.h"
#include "IncludeFile.h"
#include ".\includefile.h"
#include "resource.h"

// CIncludeFile �Ի���

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


// CIncludeFile ��Ϣ�������
BOOL CIncludeFile::OnInitDialog()
{
    CDialog::OnInitDialog();

    // ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

    // ����:������ʼ��

    return TRUE;  // return TRUE unless you set the focus to a control
    // �쳣: OCX ����ҳӦ���� FALSE
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
	} // ���� if(PathRelativePathTo(m_szRelBuf, m_szDocument, FILE_ATTRIBUTE_NORMAL, m_szFile, FILE_ATTRIBUTE_NORMAL))
	OnOK();
}

void CIncludeFile::OnBnClickedButtonBrown()
{
	CFileDialog fd(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("*.H|*.H"));
	if(fd.DoModal() == IDOK)
	{
		m_szFile = fd.GetPathName();
		UpdateData(FALSE);
	} // ���� if(fd.DoModal() == IDOK)
}
