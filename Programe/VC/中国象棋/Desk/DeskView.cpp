/*******************************************************************************************************
文件名：DeskView.cpp
功  能：桌子视图
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-12-17
时  间：16:22:00

FileName：DeskView.cpp
Function：Desk View
Compiler：Visual C++ 6.0
Author：  KangLin
          Copyright 2004 KangLin
Date：    2004-12-17
Time：    16:22:00
*******************************************************************************************************/
// 中国象棋View.cpp : implementation of the CDeskView class
//

#include "stdafx.h"
#include "..\中国象棋.h"
#include "..\MainFrm.h"
#include "..\中国象棋Doc.h"
#include "deskView.h"
#include ".\deskview.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDeskView

IMPLEMENT_DYNCREATE(CDeskView, CScrollView)

BEGIN_MESSAGE_MAP(CDeskView, CScrollView)
	//{{AFX_MSG_MAP(CDeskView)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
//    ON_WM_CLOSE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDeskView construction/destruction

CDeskView::CDeskView()
{
    m_BlackBitmap.LoadBitmap(IDB_GRASSPLOT);
    
    for(int i = 0; i < DESKNUMBER_ENUM; i++)
    {
        m_pDesk[i] = NULL;
    }
}

CDeskView::~CDeskView()
{
}

BOOL CDeskView::PreCreateWindow(CREATESTRUCT& cs)
{
	// Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs
    
	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CDeskView drawing

void CDeskView::OnDraw(CDC* pDC)
{
	CChessDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	
	// add draw code for native data here
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(&m_BlackBitmap);
	BITMAP bp;
	m_BlackBitmap.GetBitmap(&bp);

    pDC->StretchBlt(0, 0, 
		DESKNUMBER_LINE_ENUM *  CDesk::DESK_WIDTH_ENUM,
		DESKNUMBER_ENUM * CDesk::DESK_HEIGHT_ENUM / DESKNUMBER_LINE_ENUM,
		&dc, 0, 0, bp.bmWidth, bp.bmHeight,
		SRCCOPY);
}

void CDeskView::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = 	DESKNUMBER_LINE_ENUM *  CDesk::DESK_WIDTH_ENUM;
	sizeTotal.cy = DESKNUMBER_ENUM * CDesk::DESK_HEIGHT_ENUM / DESKNUMBER_LINE_ENUM;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

#ifdef _DEBUG
void CDeskView::AssertValid() const
{
	CScrollView::AssertValid();
}

void CDeskView::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CChessDoc* CDeskView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CChessDoc)));
	return (CChessDoc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CDeskView message handlers

int CDeskView::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CScrollView::OnCreate(lpCreateStruct) == -1)
		return -1;

    GetParent()->SetWindowText(_T("桌子"));
	int i = 0, j = 0;
	for(int ii = 0; ii < DESKNUMBER_ENUM; ii++)
	{
		m_pDesk[ii] = new CDesk;
		m_pDesk[ii]->SetDeskNumber(ii + 1);
		m_pDesk[ii]->Create(
			i * CDesk::DESK_WIDTH_ENUM,
			j * CDesk::DESK_HEIGHT_ENUM,
			this
			);
		i++;
		if(i >= DESKNUMBER_LINE_ENUM)
		{
			i = 0;
			j++;
		}
	}

    //设置主框架中桌子视图指针
    CMainFrame* pwnd = (CMainFrame*)AfxGetMainWnd();
    pwnd->m_pDeskView = this;

	return 0;

}

void CDeskView::OnDestroy() 
{
	CScrollView::OnDestroy();
	
	for(int i = 0; i < DESKNUMBER_ENUM; i++)
	{
		::SendMessage(m_pDesk[i]->GetSafeHwnd(), WM_CLOSE, NULL, NULL);
		delete m_pDesk[i];
        m_pDesk[i] = NULL;
	}	
}

/*******************************************************************************************************
函数名：SetChair
功  能：设置椅子头像、用户名
参  数：
         CCommand *pCmd：信息
返回值：成功返回 TRUE，否则返回 FALSE。
作  者：康  林
版  本：1.0.0.1
日  期：2005-1-2
时  间：10:05:25
*******************************************************************************************************/
BOOL CDeskView::SetChair(CCommand *pCmd)
{
    long no;
    long hand;
    CString szUser;

    szUser = pCmd->GetPara();
    no = pCmd->GetLongPara();
    hand = pCmd->GetLongPara();

    CMainFrame* pwnd = (CMainFrame*)AfxGetMainWnd();
    CChessApp* pApp = (CChessApp*)AfxGetApp();
    if(!szUser.IsEmpty())
    {
        if(szUser == pApp->m_gszUserName && pwnd->m_pChessView)
        {
            pwnd->m_pChessView->m_lChairNo = no;
        }
    }
    CString szFile, sztmp;
    szFile = ((CChessApp*)AfxGetApp())->m_gszImageDir + _T("\\");
    sztmp = pwnd->m_UserInfo.FindValue(szUser, _T("头像"));
    if(sztmp != "")
    {
        szFile += sztmp;
        
    }
    else
    {
        szFile = "";
    }
    
    if(no % 2 == 0)
    {
        m_pDesk[no / 2 -  1]->SetRightUser(szUser, szFile);
    }
    else
    {
        m_pDesk[no / 2]->SetLeftUser(szUser, szFile);
    }
    TRACE(_T("%s(%d) : 桌子信息%d:%s;头像%s\n"), __FILE__, __LINE__, no, szUser, szFile);

    if(hand)
    {
        LONG ChairNo = no;
        if(ChairNo % 2 == 0)
        {
            m_pDesk[ChairNo / 2 - 1]->SetRightHand(::AfxGetApp()->LoadIcon(IDI_RIGHTHAND));
        }
        else
        {
            m_pDesk[ChairNo / 2]->SetLeftHand(::AfxGetApp()->LoadIcon(IDI_LEFTHAND));
        }//结束 if(ChairNo % 2 == 0)
    }
    else
    {
        LONG ChairNo = no;
        if(ChairNo % 2 == 0)
        {
            m_pDesk[ChairNo / 2 - 1]->SetRightHand();
        }
        else
        {
            m_pDesk[ChairNo / 2]->SetLeftHand();
        }//结束 if(ChairNo % 2 == 0)
    }
    return TRUE;
}

/*******************************************************************************************************
函数名：SetHand
描  述：举手
参  数：
         CCommand& cmd：命令参数
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-15 9:38:23
*******************************************************************************************************/
void CDeskView::SetHand(CCommand& cmd)
{
    LONG ChairNo;
    ChairNo = cmd.GetLongPara();
    if(ChairNo % 2 == 0)
    {
        m_pDesk[ChairNo / 2 - 1]->SetRightHand(::AfxGetApp()->LoadIcon(IDI_RIGHTHAND));
    }
    else
    {
        m_pDesk[ChairNo / 2]->SetLeftHand(::AfxGetApp()->LoadIcon(IDI_LEFTHAND));
    }//结束 if(ChairNo % 2 == 0)

}

/*******************************************************************************************************
函数名：StopHand
描  述：停止举手
参  数：
         CCommand& cmd：命令参数
返回值：无
版  本：1.0.0.1
作  者：康  林
时  间：2005-6-15 9:38:46
*******************************************************************************************************/
void CDeskView::StopHand(CCommand& cmd)
{
    LONG ChairNo = cmd.GetLongPara();
    if(ChairNo % 2 == 0)
    {
        m_pDesk[ChairNo / 2 - 1]->SetRightHand();
    }
    else
    {
        m_pDesk[ChairNo / 2]->SetLeftHand();
    }//结束 if(ChairNo % 2 == 0)
}