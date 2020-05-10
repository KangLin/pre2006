/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    HookReg.h
\brief   HOOK 注册表操作函数
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年6月7日  13:50:21
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#ifndef __HOOKREG_H_KL_2007_06_07__
#define __HOOKREG_H_KL_2007_06_07__

#pragma once

#include "ntddk.h"
#include "Array.h"

//
// Number of predefined rootkeys
//
#define NUMROOTKEYS     4


//
// The name of the System process, in which context we're called in our DriverEntry
//
#define SYSNAME         "System"

//
// The maximum length of Registry values that will be copied
//
#define MAXVALLEN      256

//
// Maximum seperate filter components 
//
#define MAXFILTERS 64

//
// The maximum registry path length that will be copied
//
#define MAXPATHLEN     1024

//
// Maximum length of data that will be copied to the "other" field in the display
//
#define MAXDATALEN     32

//
// Length of process name buffer. Process names are at most 16 characters so
// we take into account a trailing NULL.
//
#define MAXPROCNAMELEN  20

//
// Maximum length of root keys that we will produce abbreviations for
//
#define MAXROOTLEN      128

//
// Maximum amount of memory that will be grabbed
//
#define MAXMEM          1000000

//
// We save off pointers to the actual Registry functions in these variables
//
NTSTATUS (*RealRegOpenKey)( IN PHANDLE, IN OUT ACCESS_MASK, IN POBJECT_ATTRIBUTES );
NTSTATUS (*RealRegQueryKey)( IN HANDLE, IN KEY_INFORMATION_CLASS,
                             OUT PVOID, IN ULONG, OUT PULONG );
NTSTATUS (*RealRegQueryValueKey)( IN HANDLE, IN PUNICODE_STRING, 
                                  IN KEY_VALUE_INFORMATION_CLASS,
                                  OUT PVOID, IN ULONG, OUT PULONG );
NTSTATUS (*RealRegEnumerateValueKey)( IN HANDLE, IN ULONG,  
                                      IN KEY_VALUE_INFORMATION_CLASS,
                                      OUT PVOID, IN ULONG, OUT PULONG );
NTSTATUS (*RealRegEnumerateKey)( IN HANDLE, IN ULONG,
                                 IN KEY_INFORMATION_CLASS,
                                 OUT PVOID, IN ULONG, OUT PULONG );
NTSTATUS (*RealRegSetValueKey)( IN HANDLE KeyHandle, IN PUNICODE_STRING ValueName,
                                IN ULONG TitleIndex, IN ULONG Type, 
                                IN PVOID Data, IN ULONG DataSize );
NTSTATUS (*RealRegCreateKey)( OUT PHANDLE, IN ACCESS_MASK,
                              IN POBJECT_ATTRIBUTES , IN ULONG,
                              IN PUNICODE_STRING, IN ULONG, OUT PULONG );
NTSTATUS (*RealRegDeleteValueKey)( IN HANDLE, IN PUNICODE_STRING );
NTSTATUS (*RealRegCloseKey)( IN HANDLE );
NTSTATUS (*RealRegDeleteKey)( IN HANDLE );
NTSTATUS(*RealRegFlushKey)(IN HANDLE);

VOID HookRegistry(void);

VOID UnhookRegistry();

//======================================================================
//                   H A S H  R O U T I N E S 
//======================================================================
typedef PVOID POBJECT;

//
// Structure for our name hash table
//
typedef struct _nameentry {
   POBJECT              Object;
   PCHAR                FullPathName;
   ULONG                nHideNum;     //枚举时,已经隐藏键值的个数
   struct _nameentry    *Next;
} HASH_ENTRY, *PHASH_ENTRY;

//
// Number of hash buckets
//
#define NUMHASH         0x100
#define HASHOBJECT(_regobject)          (((ULONG)_regobject)>>2)%NUMHASH

//
// This is a hash table for keeping names around for quick lookup.
//
PHASH_ENTRY             HashTable[NUMHASH];

//
// Mutex for hash table accesses
//
KMUTEX                  HashMutex;

//
// Convenient mutex macros
//
#define MUTEX_INIT(v)      KeInitializeMutex( &v, 0 )
#define MUTEX_WAIT(v)      KeWaitForMutexObject( &v, Executive, KernelMode, FALSE, NULL )
#define MUTEX_RELEASE(v)   KeReleaseMutex(&v, FALSE)

extern PHASH_ENTRY FreeHashList;

VOID RegmonHashCleanup();
VOID RegmonStoreHash(POBJECT object, PCHAR fullname);
VOID RegmonFreeHashEntry(POBJECT object);
PHASH_ENTRY RegmonGetHashEntry(HANDLE hKey);

#endif // __HOOKREG_H_KL_2007_06_07__
