/*******************************************************************************************************
//�������� ---��  ��--- ������ 2004-12-10 : 10:30:51
//
[ ��������VC֪ʶ���23��]

һ��ʵ�õ�CToolBar��չ��CToolBarEx


ʹ�÷���:
����CMainFrame�ж������
CToolBarEx  tbex;

��CMainFrame��OnCreate()�����м������´���:

//�ȴ���ToolBar��ȡ��ԭ���Ĵ���
tbex.CreateEx(this);

//���ð�ť����,�ָ���ҲҪ��һ��Ŷ
tbex.SetButtonNumber(5);

//����ͼƬ
thex.AddIcon(IDI_ICON1);
//��
tbex.AddIcon(AfxGetApp()->LoadIcon(IDR_MAINFRAME));  
tbex.AddIcon(AfxGetApp()->LoadIcon(IDR_TBTYPE));  
tbex.AddIcon(AfxGetApp()->LoadIcon(IDI_SWIRE)); 
tbex.AddIcon(AfxGetApp()->LoadIcon(IDI_ICON1)); 

//����ÿ����ť��λ�á�ID��ͼƬ����������
tbex.SetButton(0,ID_APP_ABOUT,0,"Ա��");
tbex.SetButton(1,ID_APP_EXIT,1,"����");

//����ָ���
tbex.AddSeparator (2);
tbex.SetButton(3,ID_APP_ABOUT,2,"Swire");
tbex.SetButton(4,ID_APP_ABOUT,3,"Coca");

//��������ͼ��Ĵ�С(��ѡ)
m_ToolBar.SetImageSize(16, 16);
//����ͼ��
m_ToolBar.SetImage();

//����ÿ����ť��С(��ѡ)
tbex.SetSize();   //����tbex.SetDefaultSize()

//�Ի����м���
RepositionBars(AFX_IDW_CONTROLBAR_FIRST, AFX_IDW_CONTROLBAR_LAST, 0);
//SDI/MDI�м���(��ѡ)
m_ToolBar.EnableDocking(CBRS_ALIGN_ANY);
EnableDocking(CBRS_ALIGN_ANY);
DockControlBar(&tbex);

//
//�������� ---��  ��--- ������ 2004-12-10 : 10:30:51
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
	//�������� ---��  ��--- ������ 2004-12-10 : 11:21:22
	//

	virtual BOOL CreateEx(CWnd* pParentWnd,
		CRect rcBorders = CRect(0, 0, 0, 0),
		DWORD dwCtrlStyle = TBSTYLE_FLAT, 
		DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC, 		 
		UINT nID = AFX_IDW_TOOLBAR);	

	//
	//�������� ---��  ��--- ������ 2004-12-10 : 11:21:22
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
