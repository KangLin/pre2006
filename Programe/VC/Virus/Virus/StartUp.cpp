#include "stdafx.h"
#include "StartUp.h"
#include "psapi.h"
#include <TlHelp32.h>
#include "..\..\System\Process\JectDll.h"

#include <string>
using namespace std;

#ifdef _UNICODE
#define _tstring wstring
#else
#define _tstring string
#endif // 结束 #ifdef

#pragma comment(lib, "Psapi.lib")


CStartUp::CStartUp()
{
}

CStartUp::~CStartUp()
{
}

/*!
\brief   判断指定的服务是否安装,如果安装,则返回TRUE,如果没安装或安装为按需启动,则返回FALSE.
\param   LPCTSTR szServiceName：
\return  类型为 BOOL 。
\version 1.0
\author  康  林
\date    2007-6-14 23:27:21
*/
BOOL CStartUp::RegService(LPCTSTR szServiceName)
{
	HKEY hKey;
	_tstring szService = _T("SYSTEM\\CURRENTCONTROLSET\\SERVICES\\");
	szService += szServiceName;
	LONG nRet = ERROR_SUCCESS;
	DWORD dwSize = 0, dwData = 0;
	nRet = RegCreateKeyEx(HKEY_LOCAL_MACHINE,
		szService.c_str(),
		0, 
		NULL, 
		REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS, 
		NULL, 
		&hKey, 
		NULL);
	if(nRet != ERROR_SUCCESS)
	{
		return FALSE;
	}// 结束 if(nRet != ERROR_SUCCESS)

	nRet = RegQueryValueEx(hKey, _T("Start"), NULL, NULL, (LPBYTE)&dwData, &dwSize);
	if(nRet != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return FALSE;
	}// 结束 if(nRet != ERROR_SUCCESS)
	RegCloseKey(hKey);

	if(dwData != SERVICE_DEMAND_START)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	} // 结束 if(dwData != SERVICE_DEMAND_START)
	return TRUE;
}

//--------------------------------------------------------------------- 
//加入注册表自启动项 
BOOL CStartUp::RegStart(LPCTSTR KeyName, LPCTSTR KeyValue)
{ 
	HKEY phkResult; 

	RegCreateKeyEx(HKEY_LOCAL_MACHINE, 
		_T("SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run"),
		0, 
		NULL, 
		REG_OPTION_NON_VOLATILE,KEY_ALL_ACCESS, 
		NULL, 
		&phkResult, 
		NULL); 

	RegSetValueEx(phkResult, 
		KeyName, 
		0, 
		REG_SZ, 
		(unsigned char *)KeyValue, 
		(_tcslen(KeyValue) + 1) * sizeof(TCHAR));

	RegCloseKey(phkResult);

	return TRUE;

} 

/*--------------------------------------------------------------------- 
功能：得到进程名对应的Pid 
要求：win2000以上系统，使用Psapi.dll 
返回值：未找到则返回0，否则返回第一个符合条件的pid 
说明：因为可能有相同进程名的多个实例存在，所以将所有符合条件的 
进程的pid依次存放在aPid数组里 
aPid的值可以为NULL，如果aPid为NULL，函数找到第一个符合条件的pid 
后立即返回 
---------------------------------------------------------------------*/ 

DWORD CStartUp::ProcessToPID(LPCTSTR ProcessName, DWORD aPid[]) 
{ 

	typedef BOOL (CALLBACK* EnumProcessesType)(DWORD *,DWORD,DWORD *); 
	typedef BOOL (CALLBACK* EnumProcessModulesType)(HANDLE,HMODULE *,DWORD,LPDWORD); 
	typedef DWORD (CALLBACK* GetModuleBaseNameType)(HANDLE, HMODULE, LPTSTR, DWORD); 

	EnumProcessesType EnumProcesses = NULL;
	EnumProcessModulesType EnumProcessModules = NULL;
	GetModuleBaseNameType GetModuleBaseName = NULL;


	HMODULE hmPsapi = GetModuleHandle(_T("psapi.dll"));

	if (hmPsapi == NULL) 
	{ 
		if((hmPsapi = LoadLibrary(_T("psapi.dll"))) == NULL)
		{ 
#ifdef _DEBUG 
			TRACE(_T("LoadLibrary() error : %d\n"), GetLastError());
#endif 
			return 0; 
		} 

	} 

	EnumProcesses = (EnumProcessesType)GetProcAddress(hmPsapi, "EnumProcesses");
	EnumProcessModules = (EnumProcessModulesType)GetProcAddress(hmPsapi, "EnumProcessModules");
	GetModuleBaseName = (GetModuleBaseNameType)GetProcAddress(hmPsapi, "GetModuleBaseNameW");

#ifdef _DEBUG 
	if(!EnumProcesses) 
		TRACE(_T("EnumProcesses == NULL\n"));
	if(!EnumProcessModules) 
		TRACE(_T("EnumProcessModules == NULL\n"));
	if(!GetModuleBaseName) 
		TRACE(_T("GetModuleBaseName == NULL\n"));
#endif 

	if (!(EnumProcesses && 
		EnumProcessModules && 
		GetModuleBaseName)) 
	{ 
		FreeLibrary(hmPsapi); 

#ifdef _DEBUG 
		TRACE(_T("GetProcAddress() error : %d\n"), GetLastError());
#endif 
		return 0; 
	} 

	DWORD aProcesses[1024], cbNeeded, cProcesses; 
	unsigned int i , j; 
	HANDLE hProcess = NULL;
	HMODULE hMod = NULL;
	TCHAR szProcessName[MAX_PATH] = _T("UnknownProcess");


	// 计算目前有多少进程, aProcesses[]用来存放有效的进程PID 
	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) 
	{ 
#ifdef _DEBUG 
		TRACE(_T("EnumProcesses() error : %d\n"), GetLastError());
#endif 

		FreeLibrary(hmPsapi); 
		return 0; 
	} 

	// 进程数
	cProcesses = cbNeeded / sizeof(DWORD); 

	// 按有效的PID遍历所有的进程 
	for(i = 0, j = 0; i < cProcesses; i++)
	{
		// 打开特定PID的进程 
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | 
			PROCESS_VM_READ, 
			FALSE, 
			aProcesses[i]); 
		// 取得特定PID的进程名 
		if ( hProcess ) 
		{ 
			if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), &cbNeeded) ) 
			{ 
				GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
#ifdef _DEBUG
				TRACE(_T("Module name:%s[%u]\n"), szProcessName, aProcesses[i]);
#endif
	
				//将取得的进程名与输入的进程名比较，如相同则返回进程PID 
				if(!_tcsicmp(szProcessName, ProcessName))
				{ 
					CloseHandle(hProcess);
					hProcess = NULL;

					//如果接收缓冲区有效，就依次填入pid，否则立即返回 
					if (aPid != NULL) 
					{ 
						aPid[j++] = aProcesses[i]; 
					} 
					else 
					{ 
						FreeLibrary(hmPsapi); 
#ifdef _DEBUG 
						TRACE(_T("Pid is %d\n"), aProcesses[i]);
#endif 
						return aProcesses[i]; 
					} // 结束 if(aPid != NULL)

				} // 结束 if(!_tcsicmp(szProcessName, ProcessName))
			}// 结束 if( EnumProcessModules( hProcess, &hMod, sizeof(hMod), &cbNeeded) )

			if(hProcess)
			{
				CloseHandle(hProcess);
			} // 结束 if(hProcess)

		}// 结束 if( hProcess )
	} // 结束 for(i = 0, j = 0; i < cProcesses; i++)

	if (aPid != NULL) 
	{ 
		FreeLibrary(hmPsapi); 
#ifdef _DEBUG 
		TRACE(_T("Pid is %d\n"), aPid[0]);
#endif 
		return aPid[0]; 
	} 

#ifdef _DEBUG 
	TRACE(_T("Not find %s\n"), ProcessName);
#endif 

	FreeLibrary(hmPsapi);
	return 0;
} 

//--------------------------------------------------------------------- 
//为当前进程增加指定的特权 
int CStartUp::AddPrivilege(LPCTSTR Name)
{
	HANDLE hToken; 
	TOKEN_PRIVILEGES tp; 
	LUID Luid; 
	int nRet = 0;

	if(!OpenProcessToken(GetCurrentProcess(),
		TOKEN_ALL_ACCESS/*TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY*/,
		&hToken)) 
	{ 
#ifdef _DEBUG 
		TRACE(_T("OpenProcessToken error.\n"));
#endif
		MessageBox(NULL, _T("OpenProcessToken error."), NULL, MB_OK);
		return 1; 
	} 

	if(!LookupPrivilegeValue(NULL, Name, &Luid))
	{ 
#ifdef _DEBUG 
		TRACE(_T("LookupPrivilegeValue error.\n"));
#endif
		MessageBox(NULL, _T("LookupPrivilegeValue error."), NULL, MB_OK);

		CloseHandle(hToken);
		return 1; 
	} 

	tp.PrivilegeCount = 1; 
	tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED; 
	tp.Privileges[0].Luid = Luid; 

	if (!AdjustTokenPrivileges(hToken, 
		FALSE, 
		&tp, 
		sizeof(TOKEN_PRIVILEGES), 
		NULL, 
		NULL)) 
	{ 
#ifdef _DEBUG 
		TRACE(_T("AdjustTokenPrivileges error.\n"));
#endif
		MessageBox(NULL, _T("AdjustTokenPrivileges error."), NULL, MB_OK);
		nRet = 1;
	}

	CloseHandle(hToken);

	return 0; 
} 

int CStartUp::InjectDll(LPCTSTR lpFullFileName, LPCTSTR ProcessName)
{
	DWORD dwID = 0;
	dwID = ProcessToPID(ProcessName, NULL);
	return !InjectLib(dwID, lpFullFileName);
}

//--------------------------------------------------------------------- 
//将FullName指定的dll文件以远程线程方式插入到Pid指定的进程里 
int CStartUp::InjectDll(LPCTSTR FullName, const DWORD Pid)
{

	int nRet = 0;

	//如果是要打开系统进程，一定要先申请debug权限 
	AddPrivilege(SE_DEBUG_NAME); 

	HANDLE hRemoteProcess = NULL;
	if ((hRemoteProcess = OpenProcess(PROCESS_CREATE_THREAD |  //允许远程创建线程 
		PROCESS_VM_OPERATION |                                 //允许远程VM操作 
		PROCESS_VM_WRITE |                                     //允许远程VM写 
		PROCESS_VM_READ,                                       //允许远程VM读 
		0, 
		Pid)) == NULL) 
	{ 
#ifdef _DEBUG 
		TRACE(_T("OpenProcess() error.\n"));
#endif 
		return 1; 
	} 

	TCHAR * pDllName = NULL;
	__try
	{
		int nLength = (_tcslen(FullName) + 1)* sizeof(TCHAR);
		if((pDllName = (TCHAR * )VirtualAllocEx(hRemoteProcess,
			NULL, 
			nLength,
			MEM_COMMIT, 
			PAGE_READWRITE)) == NULL) 
		{ 
#ifdef _DEBUG 
			TRACE(_T("VirtualAllocEx() error.\n"));
#endif
			nRet = 1;
			__leave;
		} 

		//使用WriteProcessMemory函数将DLL的路径名复制到远程进程的内存空间 
		if (WriteProcessMemory(hRemoteProcess, 
			pDllName, 
			(void *)FullName, 
			nLength,
			NULL) == 0) 
		{ 
#ifdef _DEBUG 
			TRACE(_T("WriteProcessMemory() error.\n"));
#endif
			nRet = 2;
			__leave;
		}

		//计算LoadLibraryA的入口地址 
		PTHREAD_START_ROUTINE pfnStartAddr = NULL;

		if ((pfnStartAddr = (PTHREAD_START_ROUTINE)GetProcAddress( 
			GetModuleHandle(TEXT("kernel32")), "LoadLibraryW")) == NULL)
		{ 
#ifdef _DEBUG 
			TRACE(_T("GetProcAddress() error.\n"));
#endif
			nRet = 3;
			__leave;
		}

		HANDLE hRemoteThread = NULL;
		DWORD ThreadId; 

		if ((hRemoteThread = CreateRemoteThread(hRemoteProcess, //被嵌入的远程进程 
			NULL, 
			0, 
			pfnStartAddr,  //LoadLibraryA的入口地址 
			pDllName, 
			0, 
			&ThreadId)) == NULL) 
		{
#ifdef _DEBUG
			TRACE(_T("CreateRemoteThread() error.\n"));
#endif
			nRet = 4;
			__leave;
		}

		// 等待LoadLibrary加载完毕
		WaitForSingleObject(hRemoteThread, 5000);

		CloseHandle(hRemoteThread);

	}
	__finally
	{
		if(hRemoteProcess)
		{
			CloseHandle(hRemoteProcess);
		}// 结束 if(hRemoteProcess)

		if(pDllName)
		{
			VirtualFreeEx(hRemoteProcess, pDllName, (_tcslen(FullName) + 1) * sizeof(TCHAR), MEM_COMMIT);
		}// 结束 if(pDllName)
	}
	
	return nRet;
}

int CStartUp::UnInjectDll(LPCTSTR lpFileFullName, LPCTSTR lpProcessName)
{
	DWORD dwId = ProcessToPID(lpProcessName);
	return !EjectLib(dwId, lpFileFullName);
}