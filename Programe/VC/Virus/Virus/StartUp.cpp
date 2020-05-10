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
#endif // ���� #ifdef

#pragma comment(lib, "Psapi.lib")


CStartUp::CStartUp()
{
}

CStartUp::~CStartUp()
{
}

/*!
\brief   �ж�ָ���ķ����Ƿ�װ,�����װ,�򷵻�TRUE,���û��װ��װΪ��������,�򷵻�FALSE.
\param   LPCTSTR szServiceName��
\return  ����Ϊ BOOL ��
\version 1.0
\author  ��  ��
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
	}// ���� if(nRet != ERROR_SUCCESS)

	nRet = RegQueryValueEx(hKey, _T("Start"), NULL, NULL, (LPBYTE)&dwData, &dwSize);
	if(nRet != ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		return FALSE;
	}// ���� if(nRet != ERROR_SUCCESS)
	RegCloseKey(hKey);

	if(dwData != SERVICE_DEMAND_START)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	} // ���� if(dwData != SERVICE_DEMAND_START)
	return TRUE;
}

//--------------------------------------------------------------------- 
//����ע����������� 
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
���ܣ��õ���������Ӧ��Pid 
Ҫ��win2000����ϵͳ��ʹ��Psapi.dll 
����ֵ��δ�ҵ��򷵻�0�����򷵻ص�һ������������pid 
˵������Ϊ��������ͬ�������Ķ��ʵ�����ڣ����Խ����з��������� 
���̵�pid���δ����aPid������ 
aPid��ֵ����ΪNULL�����aPidΪNULL�������ҵ���һ������������pid 
���������� 
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


	// ����Ŀǰ�ж��ٽ���, aProcesses[]���������Ч�Ľ���PID 
	if (!EnumProcesses(aProcesses, sizeof(aProcesses), &cbNeeded)) 
	{ 
#ifdef _DEBUG 
		TRACE(_T("EnumProcesses() error : %d\n"), GetLastError());
#endif 

		FreeLibrary(hmPsapi); 
		return 0; 
	} 

	// ������
	cProcesses = cbNeeded / sizeof(DWORD); 

	// ����Ч��PID�������еĽ��� 
	for(i = 0, j = 0; i < cProcesses; i++)
	{
		// ���ض�PID�Ľ��� 
		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | 
			PROCESS_VM_READ, 
			FALSE, 
			aProcesses[i]); 
		// ȡ���ض�PID�Ľ����� 
		if ( hProcess ) 
		{ 
			if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), &cbNeeded) ) 
			{ 
				GetModuleBaseName(hProcess, hMod, szProcessName, sizeof(szProcessName) / sizeof(TCHAR));
#ifdef _DEBUG
				TRACE(_T("Module name:%s[%u]\n"), szProcessName, aProcesses[i]);
#endif
	
				//��ȡ�õĽ�����������Ľ������Ƚϣ�����ͬ�򷵻ؽ���PID 
				if(!_tcsicmp(szProcessName, ProcessName))
				{ 
					CloseHandle(hProcess);
					hProcess = NULL;

					//������ջ�������Ч������������pid�������������� 
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
					} // ���� if(aPid != NULL)

				} // ���� if(!_tcsicmp(szProcessName, ProcessName))
			}// ���� if( EnumProcessModules( hProcess, &hMod, sizeof(hMod), &cbNeeded) )

			if(hProcess)
			{
				CloseHandle(hProcess);
			} // ���� if(hProcess)

		}// ���� if( hProcess )
	} // ���� for(i = 0, j = 0; i < cProcesses; i++)

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
//Ϊ��ǰ��������ָ������Ȩ 
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
//��FullNameָ����dll�ļ���Զ���̷߳�ʽ���뵽Pidָ���Ľ����� 
int CStartUp::InjectDll(LPCTSTR FullName, const DWORD Pid)
{

	int nRet = 0;

	//�����Ҫ��ϵͳ���̣�һ��Ҫ������debugȨ�� 
	AddPrivilege(SE_DEBUG_NAME); 

	HANDLE hRemoteProcess = NULL;
	if ((hRemoteProcess = OpenProcess(PROCESS_CREATE_THREAD |  //����Զ�̴����߳� 
		PROCESS_VM_OPERATION |                                 //����Զ��VM���� 
		PROCESS_VM_WRITE |                                     //����Զ��VMд 
		PROCESS_VM_READ,                                       //����Զ��VM�� 
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

		//ʹ��WriteProcessMemory������DLL��·�������Ƶ�Զ�̽��̵��ڴ�ռ� 
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

		//����LoadLibraryA����ڵ�ַ 
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

		if ((hRemoteThread = CreateRemoteThread(hRemoteProcess, //��Ƕ���Զ�̽��� 
			NULL, 
			0, 
			pfnStartAddr,  //LoadLibraryA����ڵ�ַ 
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

		// �ȴ�LoadLibrary�������
		WaitForSingleObject(hRemoteThread, 5000);

		CloseHandle(hRemoteThread);

	}
	__finally
	{
		if(hRemoteProcess)
		{
			CloseHandle(hRemoteProcess);
		}// ���� if(hRemoteProcess)

		if(pDllName)
		{
			VirtualFreeEx(hRemoteProcess, pDllName, (_tcslen(FullName) + 1) * sizeof(TCHAR), MEM_COMMIT);
		}// ���� if(pDllName)
	}
	
	return nRet;
}

int CStartUp::UnInjectDll(LPCTSTR lpFileFullName, LPCTSTR lpProcessName)
{
	DWORD dwId = ProcessToPID(lpProcessName);
	return !EjectLib(dwId, lpFileFullName);
}