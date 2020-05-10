// RelativePath.cpp : implementation file
//

#include "stdafx.h"
#include "resource.h"
#include "RelativePath.h"
#include "Afxdlgs.h"
#include "Shlwapi.h"

#pragma comment(lib, "shlwapi")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRelativePath dialog


CRelativePath::CRelativePath(CWnd* pParent /*=NULL*/)
	: CDialog(CRelativePath::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRelativePath)
    m_szSource = _T("");
	m_szDestination = _T("");
	m_szRelative = _T("");
	//}}AFX_DATA_INIT
}


void CRelativePath::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRelativePath)
	DDX_Text(pDX, IDC_EDIT_DIRFILE, m_szSource);
	DDX_Text(pDX, IDC_EDIT_RELATEPATH, m_szRelative);
	DDX_Text(pDX, IDC_EDIT_DESTIONATION, m_szDestination);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRelativePath, CDialog)
	//{{AFX_MSG_MAP(CRelativePath)
	ON_BN_CLICKED(IDC_BUTTON_BROWER, OnButtonBrower)
	ON_BN_CLICKED(IDC_BUTTON_BROWER2, OnButtonBrower2)
	ON_EN_CHANGE(IDC_EDIT_DESTIONATION, OnChangeEditDestionation)
	ON_EN_CHANGE(IDC_EDIT_DIRFILE, OnChangeEditDirfile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRelativePath message handlers

void CRelativePath::OnButtonBrower() 
{
	CFileDialog fd(TRUE);
	if(IDOK == fd.DoModal())
	{
		m_szSource = fd.GetPathName();
		UpdateData(FALSE);
		GetRelativePath();
	}
}

void CRelativePath::OnButtonBrower2() 
{
	CFileDialog fd(TRUE);
	if(IDOK == fd.DoModal())
	{
		m_szDestination = fd.GetPathName();
		UpdateData(FALSE);
		GetRelativePath();
	}
}

BOOL CRelativePath::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
    	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/*******************************************************************************************************
函数名：GetRelativePath
描  述：得到相对路径，并复制到剪切板。
参  数：
         void：无
返回值：
版  本：1.0.0.1
作  者：康  林
时  间：2005-5-16 17:32:14
*******************************************************************************************************/
bool CRelativePath::GetRelativePath(void)
{
    TCHAR szFile[MAX_PATH];
    UpdateData(TRUE);
    if(PathRelativePathTo(szFile, m_szSource, FILE_ATTRIBUTE_NORMAL, m_szDestination, FILE_ATTRIBUTE_NORMAL))
    {
        m_szRelative = szFile;
    }
    else
    {
        m_szRelative = m_szDestination;
    }
    if(m_bClipboard)
    {
        if ( !OpenClipboard() )
        {
            TRACE(_T("%s(%d) : 不能打开剪切板\n"), __FILE__, __LINE__);
            return FALSE;
        }
        // 清空当前剪切板
        if( !EmptyClipboard() )
        {
            TRACE(_T("%s(%d) : 剪切板清空失败。\n"), __FILE__, __LINE__);
            return FALSE;
        }
        LPTSTR lpData;
        HGLOBAL hglbCopy;
        hglbCopy = ::GlobalAlloc(GMEM_MOVEABLE, m_szRelative.GetLength() + sizeof(TCHAR));
        if(hglbCopy == NULL)
        {
            ::CloseClipboard();
            TRACE(_T("%s(%d) : 全局堆分配失败。\n"), __FILE__, __LINE__);
            return FALSE;
        }
        lpData = (LPTSTR) ::GlobalLock(hglbCopy);
        memcpy(lpData, m_szRelative, m_szRelative.GetLength() + sizeof(TCHAR));
        
        // 设置剪切板数据.
        if ( ::SetClipboardData( CF_TEXT, hglbCopy) == NULL )
        {
            TRACE(_T("%s(%d) : 不能设置剪切板数据。\n"), __FILE__, __LINE__);

            CloseClipboard();
            ::GlobalUnlock(hglbCopy);
            GlobalFree(hglbCopy);
            
            return FALSE;
        }
        // 关闭剪切板
        CloseClipboard();
        ::GlobalUnlock(hglbCopy);
        GlobalFree(hglbCopy);
        
    }
    this->UpdateData(FALSE);
    return TRUE;
}

void CRelativePath::OnChangeEditDestionation() 
{
	GetRelativePath();
}

void CRelativePath::OnChangeEditDirfile() 
{
	GetRelativePath();
}
