#include "StdAfx.h"
#include "ToolHelp.h"

// This macro returns TRUE if a number is between two others
#define chINRANGE(low, Num, High)(((low) <= (Num)) && ((Num) <= (High)))

///////////////////////////////////////////////////////////////////////////////


CToolHelp::CToolHelp(DWORD dwFlags, DWORD dwProcessID)
{

	m_hSnapshot = INVALID_HANDLE_VALUE;
	CreateSnapshot(dwFlags, dwProcessID);
}


///////////////////////////////////////////////////////////////////////////////


CToolHelp::~CToolHelp()
{
	if (m_hSnapshot != INVALID_HANDLE_VALUE)
		CloseHandle(m_hSnapshot);
}


///////////////////////////////////////////////////////////////////////////////


BOOL CToolHelp::CreateSnapshot(DWORD dwFlags, DWORD dwProcessID)
{

	if (m_hSnapshot != INVALID_HANDLE_VALUE)
		CloseHandle(m_hSnapshot);

	if (dwFlags == 0) {
		m_hSnapshot = INVALID_HANDLE_VALUE;
	} else {
		m_hSnapshot = CreateToolhelp32Snapshot(dwFlags, dwProcessID);
	}
	return(m_hSnapshot != INVALID_HANDLE_VALUE);
}


///////////////////////////////////////////////////////////////////////////////


BOOL CToolHelp::EnableDebugPrivilege(BOOL fEnable)
{

	// Enabling the debug privilege allows the application to see
	// information about service applications
	BOOL fOk = FALSE;    // Assume function fails
	HANDLE hToken;

	// Try to open this process's access token
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, 
		&hToken)) {

			// Attempt to modify the "Debug" privilege
			TOKEN_PRIVILEGES tp;
			tp.PrivilegeCount = 1;
			LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);
			tp.Privileges[0].Attributes = fEnable ? SE_PRIVILEGE_ENABLED : 0;
			AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
			fOk = (GetLastError() == ERROR_SUCCESS);
			CloseHandle(hToken);
	}
	return(fOk);
}


///////////////////////////////////////////////////////////////////////////////


BOOL CToolHelp::ReadProcessMemory(DWORD dwProcessID, 
										 LPCVOID pvBaseAddress, PVOID pvBuffer, DWORD cbRead, 
										 PDWORD pdwNumberOfBytesRead)
{
	return(Toolhelp32ReadProcessMemory(dwProcessID, pvBaseAddress, pvBuffer, 
		cbRead, pdwNumberOfBytesRead));
}


///////////////////////////////////////////////////////////////////////////////


BOOL CToolHelp::ProcessFirst(PPROCESSENTRY32 ppe)const
{

	BOOL fOk = Process32First(m_hSnapshot, ppe);
	if (fOk && (ppe->th32ProcessID == 0))
		fOk = ProcessNext(ppe); // Remove the "[System Process]" (PID = 0)
	return(fOk);
}


BOOL CToolHelp::ProcessNext(PPROCESSENTRY32 ppe)const
{

	BOOL fOk = Process32Next(m_hSnapshot, ppe);
	if (fOk && (ppe->th32ProcessID == 0))
		fOk = ProcessNext(ppe); // Remove the "[System Process]" (PID = 0)
	return(fOk);
}


BOOL CToolHelp::ProcessFind(DWORD dwProcessId, PPROCESSENTRY32 ppe)const
{

	BOOL fFound = FALSE;
	for (BOOL fOk = ProcessFirst(ppe); fOk; fOk = ProcessNext(ppe)) {
		fFound = (ppe->th32ProcessID == dwProcessId);
		if (fFound) break;
	}
	return(fFound);
}


///////////////////////////////////////////////////////////////////////////////


BOOL CToolHelp::ModuleFirst(PMODULEENTRY32 pme)const
{

	return(Module32First(m_hSnapshot, pme));
}


BOOL CToolHelp::ModuleNext(PMODULEENTRY32 pme)const
{

	return(Module32Next(m_hSnapshot, pme));
}

BOOL CToolHelp::ModuleFind(PVOID pvBaseAddr, PMODULEENTRY32 pme)const
{

	BOOL fFound = FALSE;
	for (BOOL fOk = ModuleFirst(pme); fOk; fOk = ModuleNext(pme)) {
		fFound = (pme->modBaseAddr == pvBaseAddr);
		if (fFound) break;
	}
	return(fFound);
}

BOOL CToolHelp::ModuleFind(PCTSTR pszModName, PMODULEENTRY32 pme)const
{
	BOOL fFound = FALSE;
	for (BOOL fOk = ModuleFirst(pme); fOk; fOk = ModuleNext(pme)) {
		fFound = (lstrcmpi(pme->szModule,  pszModName) == 0) || 
			(lstrcmpi(pme->szExePath, pszModName) == 0);
		if (fFound) break;
	}
	return(fFound);
}


///////////////////////////////////////////////////////////////////////////////


BOOL CToolHelp::ThreadFirst(PTHREADENTRY32 pte)const
{

	return(Thread32First(m_hSnapshot, pte));
}


BOOL CToolHelp::ThreadNext(PTHREADENTRY32 pte)const
{

	return(Thread32Next(m_hSnapshot, pte));
}


///////////////////////////////////////////////////////////////////////////////


int CToolHelp::HowManyHeaps()const
{

	int nHowManyHeaps = 0;
	HEAPLIST32 hl = { sizeof(hl) };
	for (BOOL fOk = HeapListFirst(&hl); fOk; fOk = HeapListNext(&hl))
		nHowManyHeaps++;
	return(nHowManyHeaps);
}


int CToolHelp::HowManyBlocksInHeap(DWORD dwProcessID, 
										  DWORD dwHeapID)const
{

	int nHowManyBlocksInHeap = 0;
	HEAPENTRY32 he = { sizeof(he) };
	BOOL fOk = HeapFirst(&he, dwProcessID, dwHeapID);
	for (; fOk; fOk = HeapNext(&he))
		nHowManyBlocksInHeap++;
	return(nHowManyBlocksInHeap);
}


BOOL CToolHelp::HeapListFirst(PHEAPLIST32 phl)const
{

	return(Heap32ListFirst(m_hSnapshot, phl));
}


BOOL CToolHelp::HeapListNext(PHEAPLIST32 phl)const
{

	return(Heap32ListNext(m_hSnapshot, phl));
}


BOOL CToolHelp::HeapFirst(PHEAPENTRY32 phe, DWORD dwProcessID, 
								 UINT_PTR dwHeapID)const
{

	return(Heap32First(phe, dwProcessID, dwHeapID));
}


BOOL CToolHelp::HeapNext(PHEAPENTRY32 phe)const
{

	return(Heap32Next(phe));
}


BOOL CToolHelp::IsAHeap(HANDLE hProcess, PVOID pvBlock, 
							   PDWORD pdwFlags)const
{
	HEAPLIST32 hl = { sizeof(hl) };
	for (BOOL fOkHL = HeapListFirst(&hl); fOkHL; fOkHL = HeapListNext(&hl)) {
		HEAPENTRY32 he = { sizeof(he) };
		BOOL fOkHE = HeapFirst(&he, hl.th32ProcessID, hl.th32HeapID);
		for (; fOkHE; fOkHE = HeapNext(&he)) {
			MEMORY_BASIC_INFORMATION mbi;
			VirtualQueryEx(hProcess, (PVOID) he.dwAddress, &mbi, sizeof(mbi));
			if (chINRANGE(mbi.AllocationBase, pvBlock, 
				(PBYTE) mbi.AllocationBase + mbi.RegionSize)) {

					*pdwFlags = hl.dwFlags;
					return(TRUE);
			}
		}
	}
	return(FALSE);
}

