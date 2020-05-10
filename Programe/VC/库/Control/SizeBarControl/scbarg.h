/*******************************************************************************************************
  VC知识库第十一期
  轻松实现类VC界面
*******************************************************************************************************/


/*******************************************************************************************************
//以下是由 康  林 增加于 2004-12-9 : 16:40:22
//
原理：在主框架窗口中加入一个控制框窗口。以此窗口可以调整大小，托动等操作。如VC6.0的编辑窗口。
      如以此窗口为容器，在此窗口中仅可包含一个一级子窗口。
	  本类自动调整此一级子窗口的大小与本窗口的大小一致。用户可以不用调整此一级子窗口。
	  如果要在本窗口中加入多个子窗口。你就只能在一级窗口上加入。
	  就是说以一级子窗口为容器。在此一级子窗口中加入子窗口。
	  并且此一级子窗口中用户要负责其子窗口的大小、位置的调整。
	  我们一般用一个从CDialog或从CWnd派生出来的类做为此一级子窗口。
	  并在此类中完成其子窗口位置、大小的调整。
用法:
    1、建立对象： CCoolBar m_ControlBar;
	2、重载CMainFrame::OnCreate(LPCRESTESTRUCT lpCreateStruct),在其中加入：
		if (!m_ControlBar.Create(_T("我的控制条"),this,123)) 
		{ TRACE0("Failed to create mybar\n"); return -1; } 
		
		m_ControlBar.EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&m_ControlBar, AFX_IDW_DOCKBAR_LEFT);///停靠在左边
	3、建立一个对话框资源:CDD m_dd;
	    m_dd.Create(IDD_DD_DIALOG, &m_ControlBar);//把对话框加到CCoolBar中
		.......
	4、在类CDD中加入其它子窗口，并在其重载函数CDD::OnSize中调整其子窗口的位置和大小
	5、设置菜单、工具条状态
	   用类向导添加 UPDATA_COMMAND_UI
       void CMainFrame::OnUpdateEditCut(CCmdUI* pCmdUI) 
	   {
	        pCmdUI->SetCheck(m_ControlBar.IsWindowVisible());
	   }
	   
       void CMainFrame::OnEditCut() 
	   {
	        if(m_ControlBar.IsWindowVisible())
		        m_ControlBar.ShowWindow(SW_HIDE);
		    else
		        m_ControlBar.ShowWindow(SW_SHOW);
	   }

//
//以上是由 康  林 增加于 2004-12-9 : 16:40:22
*******************************************************************************************************/

#if !defined(__SCBARG_H__)
#define __SCBARG_H__

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include "sizecbar.h"
/////////////////////////////////////////////////////////////////////////
// CSCBButton (button info) helper class

class CSCBButton
{
public:
    CSCBButton();

    void Move(CPoint ptTo) {ptOrg = ptTo; };
    CRect GetRect() { return CRect(ptOrg, CSize(13, 13)); };
    void Paint(CDC* pDC);

    BOOL    bPushed;
    BOOL    bRaised;

protected:
    CPoint  ptOrg;
};

/////////////////////////////////////////////////////////////////////////
// CSizingControlBar control bar

#ifndef baseCCoolBar
#define baseCCoolBar CSizingControlBar
#endif

class CCoolBar : public baseCCoolBar
{
    DECLARE_DYNAMIC(CCoolBar);

// Construction
public:
    CCoolBar();

// Attributes
public:
    virtual BOOL HasGripper() const;

// Operations
public:

// Overridables
    virtual void OnUpdateCmdUI(CFrameWnd* pTarget, BOOL bDisableIfNoHndler);

// Overrides
public:
    // ClassWizard generated virtual function overrides
    //{{AFX_VIRTUAL(CCoolBar)
    //}}AFX_VIRTUAL

// Implementation
public:
	//------------------------------------------------------------------------
	//以下是由 ---康  林--- 增加于 2004-12-9 : 16:52:35
	//

	virtual BOOL Create(LPCTSTR lpszWindowName, CWnd* pParentWnd,
        CSize sizeDefault, BOOL bHasGripper, UINT nID, 
		DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP
		|CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	virtual BOOL Create(LPCTSTR lpszWindowName, CWnd* pParentWnd,
        UINT nID, DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	//
	//以上是由 ---康  林--- 增加于 2004-12-9 : 16:52:35
	//------------------------------------------------------------------------*/
    
    virtual ~CCoolBar();
    
protected:
    // implementation helpers
    virtual void NcPaintGripper(CDC* pDC, CRect rcClient);
    virtual void NcCalcClient(LPRECT pRc, UINT nDockBarID);

protected:
    int     m_cyGripper;
    CSCBButton m_biHide;
    BOOL    m_bActive; // a child has focus
    CString m_sFontFace;

// Generated message map functions
protected:
    //{{AFX_MSG(CCoolBar)
    afx_msg LRESULT OnNcHitTest(CPoint point);
    afx_msg void OnNcLButtonUp(UINT nHitTest, CPoint point);
    afx_msg LRESULT OnSetText(WPARAM wParam, LPARAM lParam);
    //}}AFX_MSG

    DECLARE_MESSAGE_MAP()
};

#endif // !defined(__SCBARG_H__)

