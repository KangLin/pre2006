/*
  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	TrayIcon.cpp

	版权：Devia@163.com 保留

	描述：本程序主要完成程序任务栏的管理。

	作者：李晓飞(Devia_Li)	2002.12.31

	联系：Tel：13512524180	E_mail：Devia@163.net
  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*/
                   /////////////使 用 说 明//////////////
/*
  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  类使用步骤：Create()-->
              SetMenu()-->ModifyIcon()-->ModifyTipInfo()-->
			  SetActive()  //激活或关闭(退出应用程序时一定要关闭)

  资源  准备：菜单,图标和提示字符串信息。

  消息  影射：<1>
                 在主框架头文件部分添加消息影射函数:
                 LRESULT OnTrayNotification(WPARAM wparam, LPARAM lparam);
                 //{{AFX_MSG(CMainFrame)
	             //}}AFX_MSG
			     但是该函数必须在//{{AFX_MSG(CMainFrame)和//}}AFX_MSG之外定义.

			  <2>
			     在主框架实现部分建立消息和影射函数之间的关系:
				 //{{AFX_MSG_MAP(CMainFrame)
				 ON_MESSAGE(DEFNM_TRAYICON, OnTrayNotification)
				 //}}AFX_MSG_MAP
				 其中DEFNM_TRAYICON就是我们自定义的CTrayIcon类的响应消息.

  消息影射函数：
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
	//初始化Private变量
	hOwner = NULL;
	hPopMenu = NULL;
		
	//NOTIFYICONDATA结构体内容
	memset(&stData, 0, sizeof(NOTIFYICONDATA));
	stData.cbSize = sizeof(NOTIFYICONDATA);
	stData.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
	//响应的自定义消息
	stData.uCallbackMessage = DEFNM_TRAYICON;
	stData.hWnd = NULL;;
	stData.hIcon = NULL;	
	lstrcpy(stData.szTip, LPTSTR("高效,一流"));
	
	//活动状态
	bIsActivity = FALSE;
}

//######################################################################
CTrayIcon::~CTrayIcon()
{
	SetActive(FALSE);
	//释放菜单
	if ( hPopMenu != NULL )
		DestroyMenu( hPopMenu );
}

//######################################################################
BOOL CTrayIcon::Create(HWND hOwnerWnd, UINT uID, HICON hIcon, LPTSTR szTip)
{
	hOwner = hOwnerWnd;	

	//初始化结构体内容
	stData.hWnd = hOwner;
	stData.uID = uID;
	stData.hIcon = hIcon;
	
	//设置提示信息
	if ( szTip )
		lstrcpy(stData.szTip, szTip);
	
	return TRUE;
}

//######################################################################
BOOL CTrayIcon::SetActive(BOOL bActivity )
{
	BOOL bRet = FALSE;
	//打开和关闭CTrayIcon
	if ( bActivity == TRUE )
	{
		//如果打开CTrayIcon则向任务栏区添加图标
		bRet = Shell_NotifyIcon(NIM_ADD, &stData);
		ShowWindow(hOwner, SW_HIDE);
	}
	else
	{
		//如果关闭CTrayIcon则向任务栏区删除图标
		bRet = Shell_NotifyIcon(NIM_DELETE, &stData);
		CRect rcWin;
		::GetWindowRect(hOwner, rcWin);
		::SetWindowPos(hOwner, HWND_TOPMOST, rcWin.left, rcWin.top, rcWin.Width(), rcWin.Height(), SWP_SHOWWINDOW);
		//用ShowWindow(hOwner, SW_SHOW);不能达到最佳效果[特殊情况:当该窗体不是当前活动窗体时]
	}
	//同时设置当前打开关闭CTrayIcon标志
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
	//保留老的设置
	UINT uFlag = stData.uFlags;
	
	//重新设置HICON句柄(NIF_ICON仅仅使图标生效)
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
	//保留老的设置
	UINT uFlag = stData.uFlags;
	
	//重新设置HICON句柄(NIF_ICON仅仅使图标生效)
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