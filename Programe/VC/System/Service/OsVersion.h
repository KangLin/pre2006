#pragma once
#include <Windows.h>

extern struct OSVersionInfo : OSVERSIONINFO {
	OSVersionInfo();

	// Is the OS one of the NT family (NT 3.51, NT4.0, 2K, XP, etc.)?
	bool isPlatformNT;
	// Is one of the Windows family?
	bool isPlatformWindows;

	// Is this OS one of those that blue-screens when grabbing another desktop (NT4 pre SP3)?
	bool cannotSwitchDesktop;

} osVersion;
