/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    ProcessViewer.cpp
\brief   进程浏览
\version 1.0.0.1
\author  康  林 (kl222@126.com)
\date    2007年5月31日  15:29:17
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#include "StdAfx.h"
#include "ProcessViewer.h"
#include "psapi.h"

#pragma comment(lib, "Psapi.lib")

CProcessViewer::CProcessViewer(void)
{
}

CProcessViewer::~CProcessViewer(void)
{
}

void CProcessViewer::GetModulesName(DWORD processID, vector < _tstring > * pModuleName)
{
	HMODULE hMods[1024];
	HANDLE hProcess;
	DWORD cbNeeded;
	unsigned int i;

	// Print the process identifier.

	TRACE(_T("\nProcess ID: %u\n"), processID);

	// Get a list of all the modules in this process.

	hProcess = OpenProcess(  PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID );
	if (NULL == hProcess)
		return;

	if( EnumProcessModules(hProcess, hMods, sizeof(hMods), &cbNeeded))
	{
		for ( i = 0; i < (cbNeeded / sizeof(HMODULE)); i++ )
		{
			TCHAR szModName[MAX_PATH];

			// Get the full path to the module's file.

			if ( GetModuleFileNameEx( hProcess, hMods[i], szModName,
				sizeof(szModName)))
			{
				// Print the module name and handle value.
				TRACE(_T("\tModuel Name:%s (0x%08X)\n"), szModName, hMods[i]);

				pModuleName->push_back(szModName);
			}
		}
	}

	CloseHandle( hProcess );
}

_tstring CProcessViewer::GetProcessName(DWORD processID)
{
	TCHAR szProcessName[MAX_PATH] = TEXT("<unknown>");
	_tstring szRet;

	// Get a handle to the process.

	HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
		PROCESS_VM_READ,
		FALSE, processID );

	// Get the process name.

	if (NULL != hProcess )
	{
		HMODULE hMod;
		DWORD cbNeeded;

		if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), 
			&cbNeeded) )
		{
			GetModuleBaseName( hProcess, hMod, szProcessName, 
				sizeof(szProcessName)/sizeof(TCHAR) );
		}
	}

	// Print the process name and identifier.

	TRACE( TEXT("Process:%s  (PID: %u)\n"), szProcessName, processID );

	CloseHandle(hProcess);

	szRet = szProcessName;

	return szRet;
}

DWORD CProcessViewer::GetProcessID(LPCTSTR pProcessName)
{
	int i = 0;
	vector < _tstring > processName;
	vector < DWORD > processID;
	CProcessViewer p;
	p.ListProcessNameAndID(&processName, &processID);
	for(i = 0; i < processID.size(); i++)
	{
		if(!_tcscmp(processName[i].c_str(), pProcessName))
		{
			return processID[i];
		} // 结束 if(!_tcscmp(processName[i].c_str(), pProcessName))
	}// 结束 for(i = 0; i < processID.size(); i++)
	return - 1;
}

void CProcessViewer::ListProcessNameAndID(vector < _tstring > *pProcessName, vector < DWORD > *pProcessID)
{
	// Get the list of process identifiers.

	DWORD aProcesses[1024], cbNeeded, cProcesses;
	unsigned int i;

	if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
		return;

	// Calculate how many process identifiers were returned.

	cProcesses = cbNeeded / sizeof(DWORD);

	// Print the name and process identifier for each process.

	for(i = 0; i < cProcesses; i++ )
	{
		pProcessName->push_back(GetProcessName(aProcesses[i]));
		pProcessID->push_back(aProcesses[i]);
	} // 结束 for(i = 0; i < cProcesses; i++)
}
