#pragma once

#include "FilterSysDevice.h"

class CProcessFilterControl : public CFilterSysDevice
{
public:
	CProcessFilterControl(void);
	~CProcessFilterControl(void);

	BOOL Hook();
	BOOL UnHook();

	BOOL SetProtectContent(LPCTSTR pszContent);
	BOOL RemoveProtectContent(LPCTSTR pszContent);

	BOOL LoadConfig(LPCTSTR lpszFile);
	BOOL SaveConfig(LPCTSTR lpszFile);

};
