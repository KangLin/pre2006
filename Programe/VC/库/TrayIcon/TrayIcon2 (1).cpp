/*
  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	TrayIcon.cpp

	��Ȩ��Devia@163.com ����

	��������������Ҫ��ɳ����������Ĺ���

	���ߣ�������(Devia_Li)	2002.12.31

	��ϵ��Tel��13512524180	E_mail��Devia@163.net
  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*/
                   /////////////ʹ �� ˵ ��//////////////
/*
  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  ��ʹ�ò��裺Create()-->
              SetMenu()-->ModifyIcon()-->ModifyTipInfo()-->
			  SetActive()  //�����ر�(�˳�Ӧ�ó���ʱһ��Ҫ�ر�)

  ��Դ  ׼�����˵�,ͼ�����ʾ�ַ�����Ϣ��

  ��Ϣ  Ӱ�䣺<1>
                 �������ͷ�ļ����������ϢӰ�亯��:
                 LRESULT OnTrayNotification(WPARAM wparam, LPARAM lparam);
                 //{{AFX_MSG(CMainFrame)
	             //}}AFX_MSG
			     ���Ǹú���������//{{AFX_MSG(CMainFrame)��//}}AFX_MSG֮�ⶨ��.

			  <2>
			     �������ʵ�ֲ��ֽ�����Ϣ��Ӱ�亯��֮��Ĺ�ϵ:
				 //{{AFX_MSG_MAP(CMainFrame)
				 ON_MESSAGE(DEFNM_TRAYICON, OnTrayNotification)
				 //}}AFX_MSG_MAP
				 ����DEFNM_TRAYICON���������Զ����CTrayIcon�����Ӧ��Ϣ.

  ��ϢӰ�亯����
  if ( wparam == GLOBAL_TRAYICON_ID )
  {
		if ( lparam == WM_RBUTTONUP )
		{		
		m_sysTrayIcon.PopupMenu();
		}
		else
		{
		if ( lparam == WM_LBUTTONDBLCLK )
		{
		if ( ::IsWindowVisible(m_sysTrayIcon.GetOwnerWnd()) )
		{
		m_sysTrayIcon.SetActive();
		::ShowWindow(m_sysTrayIcon.GetOwnerWnd(), SW_HIDE);
		}
		else
		{
		m_sysTrayIcon.SetActive(FALSE);
		::ShowWindow(m_sysTrayIcon.GetOwnerWnd(), SW_SHOW);
		}
		}
		}
		}	
		return 1; 
		}

  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*/

#include "stdafx.h"
#include "TrayIcon.h"

//######################################################################
CTrayIcon::CTrayIcon()
{
	//��ʼ��Private����
	hOwner = NULL;
	hPopMenu = NULL;
		
	//NOTIFYICONDATA�ṹ������
	memset(&stData, 0, sizeof(NOTIFYICONDATA));
	stData.cbSize = sizeof(NOTIFYICONDATA);
	stData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	//��Ӧ���Զ�����Ϣ
	stData.uCallbackMessage = DEFNM_TRAYICON;
	stData.hWnd = NULL;;
	stData.hIcon = NULL;	
	lstrcpy(stData.szTip, LPTSTR("��Ч,һ��"));
	
	//�״̬
	bIsActivity = FALSE;
}

//######################################################################
CTrayIcon::~CTrayIcon()
{
	SetActive(FALSE);
	//�ͷŲ˵�
	if ( hPopMenu != NULL )
		DestroyMenu( hPopMenu );
}

//######################################################################
BOOL CTrayIcon::Create(HWND hOwnerWnd, UINT uID, HICON hIcon, LPTSTR szTip)
{
	hOwner = hOwnerWnd;	

	//��ʼ���ṹ������
	stData.hWnd = hOwner;
	stData.uID = uID;
	stData.hIcon = hIcon;
	
	//������ʾ��Ϣ
	if ( szTip )
		lstrcpy(stData.szTip, szTip);
	
	return TRUE;
}

//######################################################################
BOOL CTrayIcon::SetActive(BOOL bActivity )
{
	BOOL bRet = FALSE;
	//�򿪺͹ر�CTrayIcon
	if ( bActivity == TRUE )
	{
		//�����CTrayIcon���������������ͼ��
		bRet = Shell_NotifyIcon(NIM_ADD, &stData);
		ShowWindow(hOwner, SW_HIDE);
	}
	else
	{
		//����ر�CTrayIcon������������ɾ��ͼ��
		bRet = Shell_NotifyIcon(NIM_DELETE, &stData);
		CRect rcWin;
		::GetWindowRect(hOwner, rcWin);
		::SetWindowPos(hOwner, HWND_TOPMOST, rcWin.left, rcWin.top, rcWin.Width(), rcWin.Height(), SWP_SHOWWINDOW);
		//��ShowWindow(hOwner, SW_SHOW);���ܴﵽ���Ч��[�������:���ô��岻�ǵ�ǰ�����ʱ]
	}
	//ͬʱ���õ�ǰ�򿪹ر�CTrayIcon��־
	bIsActivity = bActivity;
	
	return bRet;
}

//######################################################################
BOOL CTrayIcon::SetMenu(HMENU hMenu)
{
	if ( hPopMenu != hMenu && hMenu != NULL )
	{
		hPopMenu = hMenu;
	}
	
	return TRUE;
}

//######################################################################
BOOL CTrayIcon::SetMenu(UINT uMenuID)
{
	HINSTANCE hInstance;
	hInstance = (HINSTANCE)GetWindowLong( hOwner, GWL_HINSTANCE);
	hPopMenu = LoadMenu(hInstance, MAKEINTRESOURCE(uMenuID));
	
	return TRUE;
}

//######################################################################
BOOL CTrayIcon::ModifyIcon(HICON hIcon)
{
	//�����ϵ�����
	UINT uFlag = stData.uFlags;
	
	//��������HICON���(NIF_ICON����ʹͼ����Ч)
	stData.uFlags = NIF_ICON;
	stData.hIcon = hIcon;
	
	BOOL bRet = Shell_NotifyIcon(NIM_MODIFY, &stData);
	stData.uFlags = uFlag;
	
	return bRet;
}

//######################################################################
BOOL CTrayIcon::ModifyIcon(UINT uResID)
{
	HINSTANCE hInstance;
	hInstance = (HINSTANCE)GetWindowLong(hOwner, GWL_HINSTANCE);
	
	HICON hIcon;
	hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(uResID));
	BOOL bRet = ModifyIcon(hIcon);
	
	return bRet;
}

//######################################################################
BOOL CTrayIcon::ModifyTipInfo(LPTSTR szTip)
{
	//�����ϵ�����
	UINT uFlag = stData.uFlags;
	
	//��������HICON���(NIF_ICON����ʹͼ����Ч)
	stData.uFlags = NIF_TIP;
	lstrcpy(stData.szTip, szTip);
	
	BOOL bRet = Shell_NotifyIcon(NIM_MODIFY, &stData);
	stData.uFlags = uFlag;
	
	return bRet;
}

//######################################################################
void CTrayIcon::PopupMenu()
{
	if(!hPopMenu || !hOwner) return;
	
	::SetForegroundWindow(hOwner);
	POINT pt;
	::GetCursorPos(&pt);
	
	HMENU hSubMenu = ::GetSubMenu(hPopMenu, 0);
	TrackPopupMenu(hSubMenu, TPM_RIGHTALIGN | TPM_LEFTBUTTON | TPM_RIGHTBUTTON,
		pt.x, pt.y, 0, hOwner, NULL);
	
	return ;
}