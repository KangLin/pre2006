
#include "stdafx.h"
#include <windows.h>
#include <stdlib.h>
#include <Winsvc.h>
#include "ManageService.h"

#pragma comment(lib, "Mpr.lib")

/*******************************************************************************************************
函数名：ConnectRemoteMachine
描  述：连接/断开远程机器
参  数：
BOOL bConnect   ：TRUE,连接;FALSE,断开连接
const TCHAR *lpHost    ：远程主机
const TCHAR *lpUserName：用户名
const TCHAR *lpPassword：密码
返回值：类型为 BOOL 。连接成功返回TRUE,失败返回FALSE
版  本：1.0
作  者：康  林
时  间：2007年4月22日 13:13:08
*******************************************************************************************************/
BOOL ConnectRemoteMachine(BOOL bConnect, const TCHAR * lpHost, const TCHAR * lpUserName, const TCHAR * lpPassword)
{
	TCHAR         lpIPC[256];
	DWORD         dwErrorCode;
	NETRESOURCE   NetResource;

	_stprintf(lpIPC, _T("\\\\%s\\ipc$"), lpHost);
	NetResource.lpLocalName  = NULL;
	NetResource.lpRemoteName = lpIPC;
	NetResource.dwType       = RESOURCETYPE_ANY;
	NetResource.lpProvider   = NULL;

	if(!_tcsicmp(lpPassword, _T("NULL")))
	{
		lpPassword=NULL;
	}

	if(bConnect)
	{
		_tprintf(_T("Now Connecting ...... "));
		while(1)
		{
			dwErrorCode = WNetCancelConnection2(lpIPC, CONNECT_UPDATE_PROFILE, TRUE);
			dwErrorCode = WNetAddConnection2(&NetResource, lpPassword, lpUserName, CONNECT_INTERACTIVE);
			if((dwErrorCode == ERROR_ALREADY_ASSIGNED) || (dwErrorCode == ERROR_DEVICE_ALREADY_REMEMBERED))
			{
				WNetCancelConnection2(lpIPC,CONNECT_UPDATE_PROFILE,TRUE);
			}
			else if(dwErrorCode==NO_ERROR)
			{
				_tprintf(_T("Success !\n"));
				break;
			}
			else
			{
				_tprintf(_T("Failure !\n"));
				return FALSE;
			}
			Sleep(10);
		}
	}
	else
	{
		_tprintf(_T("Now Disconnecting ... "));
		dwErrorCode=WNetCancelConnection2(lpIPC,CONNECT_UPDATE_PROFILE,TRUE);
		if(dwErrorCode==NO_ERROR)
		{
			_tprintf(_T("Success !\n"));
		}
		else
		{
			_tprintf(_T("Failure !\n"));
			return FALSE;
		}
	}

	return TRUE;
}

CServiceManage::CServiceManage()
{
	m_hSchSCManager = NULL;
}

CServiceManage::~CServiceManage()
{
	CloseSCManager();
}

BOOL CServiceManage::OpenSCManager(LPCTSTR lpMachineName, LPCTSTR lpDatabaseName, DWORD dwDesiredAccess)
{
	m_hSchSCManager = ::OpenSCManager(lpMachineName, lpDatabaseName, dwDesiredAccess);
	if(m_hSchSCManager == NULL)
	{
		return FALSE;
	}// 结束 if(m_hSchSCManager == NULL)
	return TRUE;
}

BOOL CServiceManage::CloseSCManager()
{
	if(NULL == m_hSchSCManager)
	{
		return TRUE;
	} // 结束 if(NULL == m_hSchSCManager)
	return CloseServiceHandle(m_hSchSCManager);
}

BOOL CServiceManage::InstallService(IN LPCTSTR ServiceExe, IN LPCTSTR ServiceName, DWORD dwServiceType, DWORD dwStartType)
{
	_tstring strServiceName;

	_ASSERT(ServiceExe);

	if(NULL == ServiceName)
	{
		strServiceName = m_strServiceName; 
	}
	else
	{
		strServiceName = ServiceName;
	}// 结束 if(NULL == ServiceName)

	SC_HANDLE  schService;

	//
	// NOTE: This creates an entry for a standalone driver. If this
	//       is modified for use with a driver that requires a Tag,
	//       Group, and/or Dependencies, it may be necessary to
	//       query the registry for existing driver information
	//       (in order to determine a unique Tag, etc.).
	//

	schService = CreateService(m_hSchSCManager,  // SCManager database
		strServiceName.c_str(),                  // name of service
		strServiceName.c_str(),                  // name to display
		SERVICE_ALL_ACCESS,                      // desired access
#ifdef _DEBUG
		SERVICE_INTERACTIVE_PROCESS | SERVICE_KERNEL_DRIVER |
#endif // 结束 #ifdef _DEBUG
		dwServiceType,                           // service type
		dwStartType,                             // start type
		SERVICE_ERROR_NORMAL,                    // error control type
		ServiceExe,                              // service's binary
		NULL,                                    // no load ordering group
		NULL,                                    // no tag identifier
		NULL,                                    // no dependencies
		NULL,                                    // LocalSystem account
		NULL                                     // no password
		);
	if ( schService == NULL )
		return FALSE;

	CloseServiceHandle( schService );

	return TRUE;
}

BOOL CServiceManage::StartService(IN LPCTSTR ServiceName)
{
	SC_HANDLE  schService;
	BOOL       ret;

	_tstring strServiceName;

	if(NULL == ServiceName)
	{
		strServiceName = m_strServiceName; 
	}
	else
	{
		strServiceName = ServiceName;
	}// 结束 if(NULL == ServiceName)

	schService = OpenService(m_hSchSCManager,
		strServiceName.c_str(),
		SERVICE_ALL_ACCESS
		);
	if ( schService == NULL )
		return FALSE;

	ret = ::StartService(schService, 0, NULL)
		|| GetLastError() == ERROR_SERVICE_ALREADY_RUNNING 
		|| GetLastError() == ERROR_SERVICE_DISABLED;

	CloseServiceHandle( schService );

	return ret;
}

BOOL CServiceManage::StopService(IN LPCTSTR ServiceName)
{
	SC_HANDLE       schService;
	BOOL            ret;
	SERVICE_STATUS  serviceStatus;

	_tstring strServiceName;

	if(NULL == ServiceName)
	{
		strServiceName = m_strServiceName; 
	}
	else
	{
		strServiceName = ServiceName;
	}// 结束 if(NULL == ServiceName)
	schService = OpenService(m_hSchSCManager, strServiceName.c_str(), SERVICE_ALL_ACCESS);
	if ( schService == NULL )
		return FALSE;

	ret = ControlService( schService, SERVICE_CONTROL_STOP, &serviceStatus );

	CloseServiceHandle( schService );

	return ret;
}

BOOL CServiceManage::RemoveService(IN LPCTSTR ServiceName)
{
	SC_HANDLE  schService;
	BOOL       ret;

	_tstring strServiceName;

	if(NULL == ServiceName)
	{
		strServiceName = m_strServiceName; 
	}
	else
	{
		strServiceName = ServiceName;
	}// 结束 if(NULL == ServiceName)

	schService = OpenService( m_hSchSCManager,
		strServiceName.c_str(),
		SERVICE_ALL_ACCESS
		);

	if ( schService == NULL )
		return FALSE;

	ret = DeleteService( schService );

	CloseServiceHandle( schService );

	return ret;
}