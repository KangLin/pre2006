/*******************************************************************************************************
  VC֪ʶ���ʮһ��
  ����ʵ����VC����
*******************************************************************************************************/


/*******************************************************************************************************
//�������� ��  �� ������ 2004-12-9 : 16:40:22
//
ԭ��������ܴ����м���һ�����ƿ򴰿ڡ��Դ˴��ڿ��Ե�����С���ж��Ȳ�������VC6.0�ı༭���ڡ�
      ���Դ˴���Ϊ�������ڴ˴����н��ɰ���һ��һ���Ӵ��ڡ�
	  �����Զ�������һ���Ӵ��ڵĴ�С�뱾���ڵĴ�Сһ�¡��û����Բ��õ�����һ���Ӵ��ڡ�
	  ���Ҫ�ڱ������м������Ӵ��ڡ����ֻ����һ�������ϼ��롣
	  ����˵��һ���Ӵ���Ϊ�������ڴ�һ���Ӵ����м����Ӵ��ڡ�
	  ���Ҵ�һ���Ӵ������û�Ҫ�������Ӵ��ڵĴ�С��λ�õĵ�����
	  ����һ����һ����CDialog���CWnd��������������Ϊ��һ���Ӵ��ڡ�
	  ���ڴ�����������Ӵ���λ�á���С�ĵ�����
�÷�:
    1���������� CCoolBar m_ControlBar;
	2������CMainFrame::OnCreate(LPCRESTESTRUCT lpCreateStruct),�����м��룺
		if (!m_ControlBar.Create(_T("�ҵĿ�����"),this,123)) 
		{ TRACE0("Failed to create mybar\n"); return -1; } 
		
		m_ControlBar.EnableDocking(CBRS_ALIGN_ANY);
		DockControlBar(&m_ControlBar, AFX_IDW_DOCKBAR_LEFT);///ͣ�������
	3������һ���Ի�����Դ:CDD m_dd;
	    m_dd.Create(IDD_DD_DIALOG, &m_ControlBar);//�ѶԻ���ӵ�CCoolBar��
		.......
	4������CDD�м��������Ӵ��ڣ����������غ���CDD::OnSize�е������Ӵ��ڵ�λ�úʹ�С
	5�����ò˵���������״̬
	   ��������� UPDATA_COMMAND_UI
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
//�������� ��  �� ������ 2004-12-9 : 16:40:22
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
	//�������� ---��  ��--- ������ 2004-12-9 : 16:52:35
	//

	virtual BOOL Create(LPCTSTR lpszWindowName, CWnd* pParentWnd,
        CSize sizeDefault, BOOL bHasGripper, UINT nID, 
		DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP
		|CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);
	virtual BOOL Create(LPCTSTR lpszWindowName, CWnd* pParentWnd,
        UINT nID, DWORD dwStyle = WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC);

	//
	//�������� ---��  ��--- ������ 2004-12-9 : 16:52:35
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

