/*******************************************************************************************************
//以下是由 ---康  林--- 增加于 2004-12-10 : 10:30:51
//
[ 本文属于VC知识库第23期]

一个实用的CToolBar扩展类CToolBarEx


使用方法:
先在CMainFrame中定义变量
CToolBarEx  tbex;

在CMainFrame的OnCreate()函数中加入如下代码:

//先创建ToolBar，取代原来的代码
tbex.CreateEx(this);

//设置按钮个数,分割条也要算一个哦
tbex.SetButtonNumber(5);

//加入图片
thex.AddIcon(IDI_ICON1);
//或
tbex.AddIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME));  
tbex.AddIcon(AfxGetApp()->LoadIcon(IDR_TBTYPE));  
tbex.AddIcon(AfxGetApp()->LoadIcon(IDI_SWIRE)); 
tbex.AddIcon(AfxGetApp()->LoadIcon(IDI_ICON1)); 

//设置每个按钮的位置、ID、图片索引和文字
tbex.SetButton(0,ID_APP_ABOUT,0,"员工");
tbex.SetButton(1,ID_APP_EXIT,1,"进料");

//加入分割条
tbex.AddSeparator (2);
tbex.SetButton(3,ID_APP_ABOUT,2,"Swire");
tbex.SetButton(4,ID_APP_ABOUT,3,"Coca");

//可以设置图像的大小(可选)
m_ToolBar.SetImageSize(16, 16);
//设置图像
m_ToolBar.SetImage();

//设置每个按钮大小(可选)
tbex.SetSize();   //或者tbex.SetDefaultSize()

//对话框中加入
RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
//SDI/MDI中加入(可选)
m_ToolBar.EnableDocking(CBRS_ALIGN_ANY);
EnableDocking(CBRS_ALIGN_ANY);
DockControlBar(&tbex);

//
//以上是由 ---康  林--- 增加于 2004-12-10 : 10:30:51
*******************************************************************************************************/

#if !defined(AFX_TOOLBAREX_H__75249313_031C_4672_A2EA_AB028343E633__INCLUDED_)
#define AFX_TOOLBAREX_H__75249313_031C_4672_A2EA_AB028343E633__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ToolBarEx.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CToolBarEx window

class CToolBarEx : public CToolBar
{
// Construction
public:
	CToolBarEx();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CToolBarEx)
	//}}AFX_VIRTUAL

// Implementation
public:
	//------------------------------------------------------------------------
	//以下是由 ---康  林--- 增加于 2004-12-10 : 11:21:22
	//

	virtual BOOL CreateEx(CWnd* pParentWnd,
		CRect rcBorders = CRect(0, 0, 0, 0),
		DWORD dwCtrlStyle = TBSTYLE_FLAT, 
		DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, 		 
		UINT nID = AFX_IDW_TOOLBAR);	

	//
	//以上是由 ---康  林--- 增加于 2004-12-10 : 11:21:22
	//------------------------------------------------------------------------

	void SetImageSize(int nImageWidth,int nImageHeight);
	int AddBitmap(CBitmap* pbmImage, COLORREF crMask);
	int AddBitmap(CBitmap* pbmImage, CBitmap* pbmMask);
	void SetDefaultSize();
	void AddSeparator(int nButton);
	int AddIcon(HICON hIcon);
	int AddIcon(UINT uIconID);
	void SetSize(int nWidth=50,int nHeight=40);
	void SetButton(int nButton,int nID, int nImage,LPTSTR lpText);
	void SetButton(int nButton,int nID, int nImage);
	void SetButtonNumber(int n);
	void SetImage();
	CImageList img;
	CSize sizeImage;
	virtual ~CToolBarEx();

	// Generated message map functions
protected:
	//{{AFX_MSG(CToolBarEx)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TOOLBAREX_H__75249313_031C_4672_A2EA_AB028343E633__INCLUDED_)
