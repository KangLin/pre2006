#pragma once

#include <vector>
using namespace std;

#ifdef _UNICODE
#define _tstring wstring
#else
#define _tstring string
#endif // ½áÊø #ifdef

class CProcessViewer
{
public:
	CProcessViewer(void);
public:
	~CProcessViewer(void);


	void ListProcessNameAndID(vector < _tstring > *pProcessName, vector < DWORD > *pProcessID);
	_tstring GetProcessName(DWORD processID);
	DWORD GetProcessID(LPCTSTR pProcessName);
	void GetModulesName(DWORD processID, vector < _tstring > * pModuleName);
};
