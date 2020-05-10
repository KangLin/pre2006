#ifndef __HOOKPROCESS_H_KL_2007_06_07__
#define __HOOKPROCESS_H_KL_2007_06_07__

#pragma once

#include "ntddk.h"

////////////////////////////////////////////////////////////////////////////////////////////////
//
//                    HOOK PROCESS
//
////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////定义本地结构体//////////////////////////////////////////
typedef struct _SYSTEM_THREADS 
{ 
	LARGE_INTEGER KernelTime; 
	LARGE_INTEGER UserTime; 
	LARGE_INTEGER CreateTime; 
	ULONG WaitTime; 
	PVOID StartAddress; 
	CLIENT_ID ClientIs; 
	KPRIORITY Priority; 
	KPRIORITY BasePriority; 
	ULONG ContextSwitchCount; 
	ULONG ThreadState; 
	KWAIT_REASON WaitReason; 
}SYSTEM_THREADS, *PSYSTEM_THREADS; 

typedef struct _SYSTEM_PROCESSES
{ 
	ULONG NextEntryDelta;
	ULONG ThreadCount; 
	ULONG Reserved[6]; 
	LARGE_INTEGER CreateTime; 
	LARGE_INTEGER UserTime; 
	LARGE_INTEGER KernelTime; 
	UNICODE_STRING ProcessName; 
	KPRIORITY BasePriority; 
	ULONG ProcessId; 
	ULONG InheritedFromProcessId; 
	ULONG HandleCount; 
	ULONG Reserved2[2]; 
	VM_COUNTERS VmCounters; 
	IO_COUNTERS IoCounters; 
	struct _SYSTEM_THREADS Threads[1]; 
}SYSTEM_PROCESSES, *PSYSTEM_PROCESSES; 

///////////////声明Native API///////////////////////////////////////
NTSYSAPI NTSTATUS NTAPI ZwQuerySystemInformation( 
		IN ULONG SystemInformationClass, 
		IN PVOID SystemInformation, 
		IN ULONG SystemInformationLength, 
		OUT PULONG ReturnLength);


NTSTATUS(*RealZwQuerySystemInformation)(
					IN ULONG SystemInformationClass, 
					IN PVOID SystemInformation, 
					IN ULONG SystemInformationLength, 
					OUT PULONG ReturnLength);



NTSTATUS HookZwQuerySystemInformation( 
		IN ULONG SystemInformationClass, 
		IN PVOID SystemInformation, 
		IN ULONG SystemInformationLength, 
		OUT PULONG ReturnLength);

VOID HookProcess();

VOID UnHookProcess();

#endif // __HOOKPROCESS_H_KL_2007_06_07__
