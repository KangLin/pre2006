#ifndef __TOOLHELP_H_KL_2008_08_14__
#define __TOOLHELP_H_KL_2008_08_14__

#pragma once

#include <tlhelp32.h>

class CToolHelp
{
public:
	CToolHelp(DWORD dwFlags = 0, DWORD dwProcessID = 0);
	virtual ~CToolHelp(void);

	BOOL CreateSnapshot(DWORD dwFlags, DWORD dwProcessID = 0);

	BOOL ProcessFirst(PPROCESSENTRY32 ppe) const;
	BOOL ProcessNext(PPROCESSENTRY32 ppe) const;
	BOOL ProcessFind(DWORD dwProcessId, PPROCESSENTRY32 ppe) const;

	BOOL ModuleFirst(PMODULEENTRY32 pme) const;
	BOOL ModuleNext(PMODULEENTRY32 pme) const;
	BOOL ModuleFind(PVOID pvBaseAddr, PMODULEENTRY32 pme) const;
	BOOL ModuleFind(PCTSTR pszModName, PMODULEENTRY32 pme) const;

	BOOL ThreadFirst(PTHREADENTRY32 pte) const;
	BOOL ThreadNext(PTHREADENTRY32 pte) const;

	BOOL HeapListFirst(PHEAPLIST32 phl) const;
	BOOL HeapListNext(PHEAPLIST32 phl) const;
	int  HowManyHeaps() const;

	// Note: The heap block functions do not reference a snapshot and
	// just walk the process's heap from the beginning each time. Infinite 
	// loops can occur if the target process changes its heap while the
	// functions below are enumerating the blocks in the heap.
	BOOL HeapFirst(PHEAPENTRY32 phe, DWORD dwProcessID, 
		UINT_PTR dwHeapID) const;
	BOOL HeapNext(PHEAPENTRY32 phe) const;
	int  HowManyBlocksInHeap(DWORD dwProcessID, DWORD dwHeapId) const;
	BOOL IsAHeap(HANDLE hProcess, PVOID pvBlock, PDWORD pdwFlags) const;

public:
	static BOOL EnableDebugPrivilege(BOOL fEnable = TRUE);
	static BOOL ReadProcessMemory(DWORD dwProcessID, LPCVOID pvBaseAddress, 
		PVOID pvBuffer, DWORD cbRead, PDWORD pdwNumberOfBytesRead = NULL);

private:
	HANDLE m_hSnapshot;
};

#endif //__TOOLHELP_H_KL_2008_08_14__