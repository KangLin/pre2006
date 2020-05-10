/*
  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	TrayIcon.h

	��Ȩ��Devia@163.com(Blue Sky) ����

	��������������Ҫ��ɳ����������Ĺ���

	���ߣ�������(Devia_Li)	2002.12.31

	��ϵ��Tel��13512524180	E_mail��Devia@163.net
  @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
*/

#if !defined(_BS_TRAYICON)
#define _BS_TRAYICON

//�Զ�����ϢID
#define DEFNM_TRAYICON		WM_USER+120

class CTrayIcon  
{
protected:
	//ӵ���߾��
	HWND hOwner;	
	//�˵����
	HMENU hPopMenu;
	//Shell_NotifyIcon�Ľṹ��
	NOTIFYICONDATA stData;
	//��ǰ���־
	BOOL bIsActivity;
public:
	//���캯������������
	CTrayIcon();
	virtual ~CTrayIcon();

public:
	//��������Create
	BOOL Create(HWND hOwnerWnd, UINT uID, HICON hIcon, LPTSTR szTip);
	//����ͼ��
	BOOL ModifyIcon(HICON hIcon);
	BOOL ModifyIcon(UINT uResID);
	//���Ĳ˵�
	BOOL SetMenu(UINT uMenuID);
	BOOL SetMenu(HMENU hMenu);
	//������ʾ��Ϣ
	BOOL ModifyTipInfo(LPTSTR szTip);

	//�򿪺͹ر�TracyIcon
	BOOL SetActive(BOOL bActivity = TRUE);

	//����TracyIcon��������Ϣ
	HMENU GetPopMenu(){ return hPopMenu; };
	LPTSTR GetTipInfo(){ return stData.szTip; };
	HWND GetOwnerWnd(){ return hOwner; };
	BOOL GetActivity(){  return  bIsActivity; }

	//�����Ҽ��˵�
	void PopupMenu();
};

#endif // !defined(_BS_TRAYICON)
