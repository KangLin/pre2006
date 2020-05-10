// SearchView.cpp : implementation of the CSearchView class
//

#include "stdafx.h"
#include "Search.h"
#include "SearchDoc.h"
#include "SearchView.h"
#include "FindEx.h"
#include "Prompt.h"
#include "..\库\浏览文件夹对话框\DirDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSearchView

IMPLEMENT_DYNCREATE(CSearchView, CFormView)

BEGIN_MESSAGE_MAP(CSearchView, CFormView)
	//{{AFX_MSG_MAP(CSearchView)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_BN_CLICKED(IDC_SEARCH, OnSearch)
	ON_BN_CLICKED(IDC_BROWE, OnBrowe)
	ON_LBN_DBLCLK(IDC_FILE, OnDblclkFile)
	ON_COMMAND(IDM_TOOL_FINDFILE, OnToolFindfile)
	ON_COMMAND(IDM_TOOL_WORD, OnToolWord)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSearchView construction/destruction

CSearchView::CSearchView()
	: CFormView(CSearchView::IDD)
{
	//{{AFX_DATA_INIT(CSearchView)
	m_szFileName = _T("");
	m_szPath = _T("");
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CSearchView::~CSearchView()
{
}

void CSearchView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSearchView)
	DDX_Control(pDX, IDC_PATH, m_ctrPath);
	DDX_Control(pDX, IDC_FILENAME, m_ctrFileName);
	DDX_Control(pDX, IDC_SEARCH, m_ctrBtSearch);
	DDX_Control(pDX, IDC_BROWE, m_ctrBtBrowe);
	DDX_Control(pDX, IDC_FILE, m_lstFile);
	DDX_Text(pDX, IDC_FILENAME, m_szFileName);
	DDX_Text(pDX, IDC_PATH, m_szPath);
	//}}AFX_DATA_MAP
}

BOOL CSearchView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CSearchView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

}

/////////////////////////////////////////////////////////////////////////////
// CSearchView printing

BOOL CSearchView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSearchView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSearchView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CSearchView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CSearchView diagnostics

#ifdef _DEBUG
void CSearchView::AssertValid() const
{
	CFormView::AssertValid();
}

void CSearchView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CSearchDoc* CSearchView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSearchDoc)));
	return (CSearchDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CSearchView message handlers

int CSearchView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CFormView::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here

	return 0;
}


void CSearchView::OnSize(UINT nType, int cx, int cy) 
{
	CFormView::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	CRect rect;
	if(m_ctrBtBrowe.GetSafeHwnd()!=NULL)
	{	
		m_ctrBtBrowe.GetWindowRect(&rect);
		ScreenToClient(&rect);
		int w;
		w = rect.Width();
		rect.left = cx - w - 20;
		rect.right = rect.left + w;
		m_ctrBtBrowe.MoveWindow(&rect);
		m_ctrBtSearch.GetWindowRect(&rect);
		ScreenToClient(&rect);
		w = rect.Width();
		rect.left = cx - w - 20;
		rect.right = rect.left + w;
		m_ctrBtSearch.MoveWindow(&rect);
		
	}
	if(m_ctrPath.GetSafeHwnd() !=NULL)
	{
		int right = rect.left;
		m_ctrPath.GetWindowRect(&rect);
		ScreenToClient(&rect);
		rect.right = right - 20;
		m_ctrPath.MoveWindow(&rect);
		m_ctrFileName.GetWindowRect(&rect);
		ScreenToClient(&rect);
        rect.right = right - 20;
		m_ctrFileName.MoveWindow(&rect);
		m_lstFile.GetWindowRect(&rect);
        ScreenToClient(&rect);
		rect.right = cx - 20;
		rect.bottom = cy -20;
        m_lstFile.MoveWindow(&rect);
	}
}

void CSearchView::OnSearch() 
{
	// TODO: Add your control notification handler code here
    UpdateData();
	m_lstFile.ResetContent();
	CPrompt p;
	p.Create(IDD_PROMPT_DIALOG,this);
	CFindEx fe;
	fe.SearchDirectory(m_szPath);
}

void CSearchView::OnBrowe() 
{
	// TODO: Add your control notification handler code here
	//*
	
	CDirDialog dd;
//	dd.m_strInitDir = _T("C:\\Program Files\\Microsoft Visual Studio\\VC98");
	if(dd.DoBrowse(this)==IDOK)
	{
		m_ctrPath.SetWindowText(dd.m_strPath);	
	}
	//*/
    //m_ctrPath.SetWindowText(ShowBrowseFolderDialog(this->GetSafeHwnd()));
}


void CSearchView::OnDblclkFile() 
{
	// TODO: Add your control notification handler code here
	CString szFile;
	m_lstFile.GetText(m_lstFile.GetCurSel(), szFile);
    ShellExecute(GetSafeHwnd(), NULL, szFile, NULL, NULL, SW_SHOW);
}

void CSearchView::OnToolFindfile() 
{
	// TODO: Add your command handler code here
	m_ctrBtSearch.SetWindowText(_T("查找文件(&S)"));	
}

void CSearchView::OnToolWord() 
{
	// TODO: Add your command handler code here
    m_ctrBtSearch.SetWindowText(_T("查找文字(&T)"));	
}

/*******************************************************************************************************
函数名：ShowBrowseFolderDialog
功  能：显示浏览文件夹对话框
参  数：
         HWND hWnd：窗口句柄
返回值：如果成功,返回文件夹的路径,如果失败返回空字符串.
作  者：康  林
版  本：1.0.0.1
日  期：2004-10-31
时  间：10:25:26
*******************************************************************************************************/
CString ShowBrowseFolderDialog(HWND hWnd) 
{
     BROWSEINFO bi;
     TCHAR dispname[MAX_PATH], path[MAX_PATH];
     ITEMIDLIST *pidl;

     bi.hwndOwner = hWnd;
     bi.pidlRoot = 0;
     bi.pszDisplayName = dispname;
     bi.lpszTitle = "请选择查找目录：";
     bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_EDITBOX | BIF_DONTGOBELOWDOMAIN;
     bi.lpfn = 0;
     bi.lParam = 0;
     bi.iImage = 0;
     if(pidl = SHBrowseForFolder(&bi))
     {
        SHGetPathFromIDList(pidl, path);
        return CString(path);
     } 
	 CString str;
	 str.Empty();
     return str;
}