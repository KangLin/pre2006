/*******************************************************************************************************
��������VC֪ʶ���17��, �ʺ��м����� 

ϵͳ���̱����ȫָ�ϣ�һ��
*******************************************************************************************************/

/*******************************************************************************************************
���ߣ�����
1���Ƚ���һ�� CTaryIcon ��ָ��: m_pTrayIcon;
2���������򵼽���WM_CREATE��ӳ����: OnCreate()
int CWXXMDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	m_bRun = TRUE;

    //3������ʵ��
	m_pTrayIcon = new CTrayIcon(IDM_TRAYICON);
	//4��������Ϣͨ����Ϣ
	m_pTrayIcon->SetNotificationWnd(this, IDM_TRAYICON);
	//5������ͨ����ͼ��
	m_pTrayIcon->SetIcon(IDR_MAINFRAME);

	return 0;
}

6��������Ϣӳ��ON_MESSAGE(IDM_TRAYICON, OnTrayNotifiy)
   virtual LRESULT OnTrayNotifiy(WPARAM wID, LPARAM lEvent);

7��������Ϣӳ������
LRESULT CWXXMDlg::OnTrayNotifiy(WPARAM wID, LPARAM lEvent)
{
    //���û���� OnTrayIcon���˺������Ĭ�ϵ�˫�����һ��¼���
	return m_pTrayIcon->OnTrayNotifiy(wID, lEvent);
}

8������ʱ�����ͷ�ָ�룺m_pTrayIcon
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
