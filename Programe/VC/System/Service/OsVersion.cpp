#include "stdafx.h"
#include "OsVersion.h"
#include <tchar.h>

OSVersionInfo::OSVersionInfo() {
	// Get OS Version Info
	ZeroMemory(static_cast<OSVERSIONINFO*>(this), sizeof(this));
	dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	if (!GetVersionEx(this))
		return;
	// Set the special extra flags
	isPlatformNT = dwPlatformId == VER_PLATFORM_WIN32_NT;
	isPlatformWindows = dwPlatformId == VER_PLATFORM_WIN32_WINDOWS;

	cannotSwitchDesktop = isPlatformNT && (dwMajorVersion==4) &&
		((_tcscmp(szCSDVersion, _T("")) == 0) ||
		(_tcscmp(szCSDVersion, _T("Service Pack 1")) == 0) ||
		(_tcscmp(szCSDVersion, _T("Service Pack 2")) == 0));

}

OSVersionInfo osVersion;
