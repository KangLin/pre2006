#pragma once

class CStartUp
{
public:
	CStartUp();
	~CStartUp();

	BOOL RegStart(LPCTSTR KeyName, LPCTSTR KeyValue);
	BOOL RegService(LPCTSTR szServiceName);

	DWORD ProcessToPID(LPCTSTR ProcessName, DWORD aPid[] = NULL);
	int InjectDll(LPCTSTR FullName, const DWORD Pid);
	int InjectDll(LPCTSTR lpFullFileName, LPCTSTR lpProcessName);
	int UnInjectDll(LPCTSTR lpFileFullName,LPCTSTR lpProcessName);
	int AddPrivilege(LPCTSTR Name);

};

