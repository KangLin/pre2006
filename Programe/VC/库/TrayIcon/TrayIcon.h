/*******************************************************************************************************
本文属于VC知识库第17期, 适合中级读者 

系统托盘编程完全指南（一）
*******************************************************************************************************/

/*******************************************************************************************************
作者：康林
1、先建立一个 CTaryIcon 的指针: m_pTrayIcon;
2、再用类向导建立WM_CREATE的映像函数: OnCreate()
int CWXXMDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_bRun = TRUE;

    //3、建立实例
	m_pTrayIcon = new CTrayIcon(IDM_TRAYICON);
	//4、设置消息通告消息
	m_pTrayIcon->SetNotificationWnd(this, IDM_TRAYICON);
	//5、设置通告区图标
	m_pTrayIcon->SetIcon(IDR_MAINFRAME);

	return 0;
}

6、建立消息映像：ON_MESSAGE(IDM_TRAYICON, OnTrayNotifiy)
   virtual LRESULT OnTrayNotifiy(WPARAM wID, LPARAM lEvent);

7、建立消息映像函数：
LRESULT CWXXMDlg::OnTrayNotifiy(WPARAM wID, LPARAM lEvent)
{
    //调用基类的 OnTrayIcon，此函数完成默认的双击或右击事件。
	return m_pTrayIcon->OnTrayNotifiy(wID, lEvent);
}

8、结束时加入释放指针：m_pTrayIcon
void CWXXMDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	if(m_bRun)
	{
		ShowWindow(SW_HIDE);
		return;
	}

	m_pTrayIcon->SetIcon(NULL);
	CDialog::OnClose();
}
*******************************************************************************************************/
////////////////////////////////////////////////////////////////
// CTrayIcon Copyright 1996 Microsoft Systems Journal.
//
// If this code works, it was written by Paul DiLascia.
// If not, I don't know who wrote it.

#ifndef _TRAYICON_H
#define _TRAYICON_H

////////////////
// CTrayIcon manages an icon in the Windows 95 system tray. 
// 
class CTrayIcon : public CCmdTarget {
protected:
	DECLARE_DYNAMIC(CTrayIcon)
	NOTIFYICONDATA m_nid;			// struct for Shell_NotifyIcon args

public:
	CTrayIcon(UINT uID);
	~CTrayIcon();

	// Call this to receive tray notifications
	void SetNotificationWnd(CWnd* pNotifyWnd, UINT uCbMsg);

	// SetIcon functions. To remove icon, call SetIcon(0)
	//
	BOOL SetIcon(UINT uID); // main variant you want to use
	BOOL SetIcon(HICON hicon, LPCSTR lpTip);
	BOOL SetIcon(LPCTSTR lpResName, LPCSTR lpTip)
		{ return SetIcon(lpResName ? 
			AfxGetApp()->LoadIcon(lpResName) : NULL, lpTip); }
	BOOL SetStandardIcon(LPCTSTR lpszIconName, LPCSTR lpTip)
		{ return SetIcon(::LoadIcon(NULL, lpszIconName), lpTip); }

	virtual LRESULT OnTrayNotifiy(WPARAM uID, LPARAM lEvent);
};

#endif
