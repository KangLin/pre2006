/*
  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	TrayIcon.h

	版权：Devia@163.com(Blue Sky) 保留

	描述：本程序主要完成程序任务栏的管理。

	作者：李晓飞(Devia_Li)	2002.12.31

	联系：Tel：13512524180	E_mail：Devia@163.net
  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*/

#if !defined(_BS_TRAYICON)
#define _BS_TRAYICON

//自定义消息ID
#define DEFNM_TRAYICON		WM_USER+120

class CTrayIcon  
{
protected:
	//拥有者句柄
	HWND hOwner;	
	//菜单句柄
	HMENU hPopMenu;
	//Shell_NotifyIcon的结构体
	NOTIFYICONDATA stData;
	//当前活动标志
	BOOL bIsActivity;
public:
	//构造函数和析构函数
	CTrayIcon();
	virtual ~CTrayIcon();

public:
	//创建函数Create
	BOOL Create(HWND hOwnerWnd, UINT uID, HICON hIcon, LPTSTR szTip);
	//更改图标
	BOOL ModifyIcon(HICON hIcon);
	BOOL ModifyIcon(UINT uResID);
	//更改菜单
	BOOL SetMenu(UINT uMenuID);
	BOOL SetMenu(HMENU hMenu);
	//更改提示信息
	BOOL ModifyTipInfo(LPTSTR szTip);

	//打开和关闭TracyIcon
	BOOL SetActive(BOOL bActivity = TRUE);

	//返回TracyIcon的配置信息
	HMENU GetPopMenu(){ return hPopMenu; };
	LPTSTR GetTipInfo(){ return stData.szTip; };
	HWND GetOwnerWnd(){ return hOwner; };
	BOOL GetActivity(){  return  bIsActivity; }

	//弹出右键菜单
	void PopupMenu();
};

#endif // !defined(_BS_TRAYICON)
