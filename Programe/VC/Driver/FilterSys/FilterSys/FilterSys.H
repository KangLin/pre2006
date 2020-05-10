/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    FilterSys.H
\brief   驱动的入口与退出函数的头文件
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年6月7日  13:55:03
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#ifndef __REGSYS_H_KL_2007_06_05__
#define __REGSYS_H_KL_2007_06_05__

#pragma once
#include "ntddk.h"
#include "Memory.h"
#include "IoctlCmd.h"
#include "SupportRoute.h"
#include "Array.h"
#include "DataSupport.h"
#include "HookProcess.h"
#include "HookReg.h"

//----------------------------------------------------------------------
//                           DEFINES
//----------------------------------------------------------------------
// print macro that only turns on when debugging is on
#if DBG
#define DbgPrint(arg) DbgPrint arg
#else
#define DbgPrint(arg) 
#endif

//
// Macro for easy hook/unhook. On X86 implementations of Zw* functions, the DWORD
// following the first byte is the system call number, so we reach into the Zw function
// passed as a parameter, and pull the number out. This makes system call hooking
// dependent ONLY on the Zw* function implementation not changing.
//

#if defined(_ALPHA_)
#define SYSCALL(_function)  ServiceTable->ServiceTable[ (*(PULONG)_function)  & 0x0000FFFF ]
#else
#define SYSCALL(_function)  ServiceTable->ServiceTable[ *(PULONG)((PUCHAR)_function+1)]
#endif


//
// Invalid handle
//
#define INVALID_HANDLE_VALUE  ((HANDLE) -1)

//
// Definition for system call service table
//
typedef struct _SRVTABLE {
	PVOID           *ServiceTable;
	ULONG           LowCall;        
	ULONG           HiCall;
	PVOID		    *ArgTable;
}
SRVTABLE, *PSRVTABLE;

//
// Rootkey name translation structure
//
typedef struct _rootkey {
    CHAR                RootName[256];
    CHAR                RootShort[32];
    ULONG               RootNameLen;
} ROOTKEY, *PROOTKEY;

extern ROOTKEY CurrentUser[2];

extern ROOTKEY RootKey[NUMROOTKEYS];

extern UNICODE_STRING          DefaultValue;
//
// Pointer to the image of the system service table
//
extern PSRVTABLE KeServiceDescriptorTable;

extern PSRVTABLE ServiceTable;

extern ULONG ProcessNameOffset;


//
// For displaying messages to the Blue Screen
//
NTSYSAPI
NTSTATUS
NTAPI ZwDisplayString(PUNICODE_STRING Text);

//
// Definition for ObQueryNameString call
//
NTSYSAPI
NTSTATUS
NTAPI ObQueryNameString( POBJECT Object, PUNICODE_STRING Name, ULONG MaximumLength, PULONG ActualLength );


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                                R O U T E
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
NTSTATUS RegFilterDispatch(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);

NTSTATUS RegFilterDeviceControl(IN PDEVICE_OBJECT DeviceObject, IN PIRP Irp);

VOID RegFilterUnload(IN PDRIVER_OBJECT DriverObject);

NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath );

#endif // __REGSYS_H_KL_2007_06_05__