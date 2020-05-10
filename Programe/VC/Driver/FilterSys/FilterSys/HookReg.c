/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    HookReg.c
\brief   HOOK 注册表操作函数
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年6月7日  13:49:55
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#include "HookReg.h"
#include "FilterSys.h"

//
// A unicode string constant for the "default" value
//
#define DEFAULTNAMELEN  (9*sizeof(WCHAR))
WCHAR                   DefaultValueString[] = L"(Default)";
UNICODE_STRING          DefaultValue = {
    DEFAULTNAMELEN,
    DEFAULTNAMELEN,
    DefaultValueString
};

//
// Lenghs of rootkeys (filled in at init). This table allows us to translate 
// path names into better-known forms. Current user is treated specially since
// its not a full match.
//
ROOTKEY CurrentUser[2] = {
    { "\\\\REGISTRY\\USER\\S", "HKCU", 0 },
    { "HKU\\S", "HKCU", 0 }
};

ROOTKEY RootKey[NUMROOTKEYS] = {
    { "\\\\REGISTRY\\USER", "HKU", 0 },
    { "\\\\REGISTRY\\MACHINE\\SYSTEM\\CURRENTCONTROLSET\\HARDWARE PROFILES\\CURRENT", 
      "HKCC", 0 },
    { "\\\\REGISTRY\\MACHINE\\SOFTWARE\\CLASSES", "HKCR", 0 },
    { "\\\\REGISTRY\\MACHINE", "HKLM", 0 }
};

//
// Is registry hooked?
//
BOOLEAN g_RegHooked = FALSE;

ARRAYHEAD g_ProtectRegisterNameHead;

//
// Free hash list. Note: we don't use lookaside lists since
// we want to be able to run on NT 3.51 - lookasides were
// introduced in NT 4.0
//
PHASH_ENTRY             FreeHashList = NULL;

//======================================================================
//                   H A S H  R O U T I N E S 
//======================================================================

//----------------------------------------------------------------------
//
// RegmonHashCleanup
//
// Called when we are unloading to free any memory that we have 
// in our possession.
//
//----------------------------------------------------------------------
VOID RegmonHashCleanup()
{
    PHASH_ENTRY             hashEntry, nextEntry;
    ULONG                   i;

    MUTEX_WAIT( HashMutex );    

    //
    // First free the hash table entries
    //       
    for( i = 0; i < NUMHASH; i++ ) {
        hashEntry = HashTable[i];
        while( hashEntry ) {
            nextEntry = hashEntry->Next;
            ExFreePool( hashEntry->FullPathName );
            ExFreePool( hashEntry );
            hashEntry = nextEntry;
        }
    }
    
    hashEntry = FreeHashList;
    while( hashEntry ) {
        nextEntry = hashEntry->Next;
        ExFreePool( hashEntry );
        hashEntry = nextEntry;
    }
    MUTEX_RELEASE( HashMutex );
}

//----------------------------------------------------------------------
//
// RegmonStoreHash
//
// Stores the key and associated fullpath in the hash table.
//
//----------------------------------------------------------------------
VOID RegmonStoreHash( POBJECT object, PCHAR fullname )
{
    PHASH_ENTRY     newEntry;

    MUTEX_WAIT( HashMutex );

    if( FreeHashList ) {

        newEntry = FreeHashList;
        FreeHashList = newEntry->Next;

    } else {

        newEntry = ExAllocatePool( NonPagedPool, sizeof(HASH_ENTRY));
    }

    newEntry->Object                = object;
    newEntry->FullPathName          = ExAllocatePool( NonPagedPool, strlen(fullname)+1 );
	newEntry->nHideNum              = 0;
	newEntry->Next                  = HashTable[ HASHOBJECT( object) ];
    HashTable[ HASHOBJECT(object) ] = newEntry;     
    strcpy( newEntry->FullPathName, fullname );

    MUTEX_RELEASE( HashMutex );
}


//----------------------------------------------------------------------
//
// RegmonFreeHashEntry
//
// When we see a key close, we can free the string we had associated
// with the fileobject being closed since we know it won't be used
// again.
//
//----------------------------------------------------------------------
VOID RegmonFreeHashEntry( POBJECT object )
{
    PHASH_ENTRY             hashEntry, prevEntry;

    MUTEX_WAIT( HashMutex );

    //
    // look-up the entry
    //
    hashEntry = HashTable[ HASHOBJECT( object ) ];
    prevEntry = NULL;
    while( hashEntry && hashEntry->Object != object ) {
        prevEntry = hashEntry;
        hashEntry = hashEntry->Next;
    }
  
    //
    // If we fall off (didn''t find it), just return
    //
    if( !hashEntry ) {
        MUTEX_RELEASE( HashMutex );
        return;
    }

    //
    // Remove it from the hash list 
    //
    if( prevEntry ) 
        prevEntry->Next = hashEntry->Next;
    else 
        HashTable[ HASHOBJECT( object )] = hashEntry->Next;

    //
    // Free the memory associated with it
    //
    ExFreePool( hashEntry->FullPathName );
    hashEntry->Next = FreeHashList;
    FreeHashList = hashEntry;

    MUTEX_RELEASE( HashMutex );
}

/*!
\brief   得到指定句柄的 hash 表入口
\param   HANDLE hKey：
\return  类型为 PHASH_ENTRY 。
\version 1.0
\author  康  林
\date    2007-6-18 16:31:26
*/
PHASH_ENTRY RegmonGetHashEntry(HANDLE hKey)
{
	PHASH_ENTRY             hashEntry = NULL;
    POBJECT                 pKey = NULL;

	if( pKey = GetPointer( hKey )) {

		//
		// See if we find the key in the hash table
		//
		ReleasePointer( pKey );
		MUTEX_WAIT( HashMutex );
		hashEntry = HashTable[ HASHOBJECT( pKey ) ];
		while( hashEntry && hashEntry->Object != pKey )
			hashEntry = hashEntry->Next;
		MUTEX_RELEASE(HashMutex);
	}
	return hashEntry;
}

//======================================================================
//                    H O O K  R O U T I N E S
//======================================================================

//----------------------------------------------------------------------
//
// HookRegOpenKey
//
//----------------------------------------------------------------------
NTSTATUS HookRegOpenKey( IN OUT PHANDLE pHandle, IN ACCESS_MASK ReqAccess, 
                         IN POBJECT_ATTRIBUTES pOpenInfo )
{
    NTSTATUS                ntstatus;
    POBJECT                 regobj;
    CHAR                    fullname[MAXPATHLEN], data[MAXDATALEN], name[MAXPROCNAMELEN];

    GetFullName( pOpenInfo->RootDirectory, pOpenInfo->ObjectName, fullname );
	ntstatus = RealRegOpenKey(pHandle, ReqAccess, pOpenInfo);
	//DbgPrint(("RegOpenKey: %s => %x, %x\n", fullname, *pHandle, ntstatus));
	
	data[0] = 0;
	if(NT_SUCCESS(ntstatus))
	{
        regobj = GetPointer( *pHandle );
        RegmonFreeHashEntry( regobj );
        RegmonStoreHash( regobj, fullname );
        //sprintf(data,"Key: 0x%X", regobj );
        ReleasePointer( regobj );
    }
    /*if( FilterDef.logreads && GetProcess( name ) && ApplyNameFilter(fullname) && ErrorString( ntstatus )) {
        UpdateStore( "%s\tOpenKey\t%s\t%s\t%s", name,
                     fullname, ErrorString( ntstatus ), data );
    }*/
    return ntstatus;
}


//----------------------------------------------------------------------
//
// HookRegCreateKey
//
//----------------------------------------------------------------------
NTSTATUS HookRegCreateKey( OUT PHANDLE pHandle, IN ACCESS_MASK ReqAccess,
                           IN POBJECT_ATTRIBUTES pOpenInfo, IN ULONG TitleIndex,
                           IN PUNICODE_STRING Class, IN ULONG CreateOptions, OUT PULONG Disposition )
{
    NTSTATUS                ntstatus;
    POBJECT                 regobj;
    CHAR                    fullname[MAXPATHLEN], data[MAXDATALEN], name[MAXPROCNAMELEN];

    GetFullName( pOpenInfo->RootDirectory, pOpenInfo->ObjectName, fullname );
	ntstatus = RealRegCreateKey( pHandle, ReqAccess, pOpenInfo, TitleIndex,
                                 Class, CreateOptions, Disposition );
    //DbgPrint(("RegCreateKey: %s => %x, %x\n", fullname, *pHandle, ntstatus ));
    data[0] = 0;
	if(NT_SUCCESS(ntstatus))
	{
        regobj = GetPointer( *pHandle );
        RegmonFreeHashEntry( regobj );
        RegmonStoreHash( regobj, fullname );
        //sprintf(data,"Key: 0x%X", regobj );
        ReleasePointer( regobj );
    }
    /*if( ((NT_SUCCESS( ntstatus ) && 
          (Disposition && *Disposition == REG_CREATED_NEW_KEY && FilterDef.logwrites)) ||
         FilterDef.logreads ) && 
        GetProcess( name ) && ApplyNameFilter(fullname) && ErrorString( ntstatus )) {
        UpdateStore( "%s\tCreateKey\t%s\t%s\t%s", name,
                     fullname, ErrorString( ntstatus ), data);
    }*/
    return ntstatus;
}


//----------------------------------------------------------------------
//
// HookRegCloseKey
//
// This is actually a hook for NtClose which is used for closing any
// object. Therefore, we must ensure that we are seeing a close for 
// a registry object that we know about.
//
//----------------------------------------------------------------------
NTSTATUS HookRegCloseKey( IN HANDLE Handle )
{
    NTSTATUS                ntstatus;
    POBJECT                 regobj;
    CHAR                    name[MAXPROCNAMELEN];
    PCHAR                   fullname, data;
    ULONG                   retlen;
    BOOLEAN                 iskey = FALSE;
    KEY_BASIC_INFORMATION   basicInfo;
    
    //
    // Allocate data from pool since this close routine can be called from other
    // drivers, where the stack space may already be strained
    //
    fullname = ExAllocatePool( NonPagedPool, MAXPATHLEN );
    data     = ExAllocatePool( NonPagedPool, MAXVALLEN );

    //
    // Determine if the object is a key by querying it
    //
    ntstatus = RealRegQueryKey( Handle, KeyBasicInformation, 
                                &basicInfo, 0, &retlen );
    if( ntstatus != STATUS_OBJECT_TYPE_MISMATCH ) {
        iskey = TRUE;        
        GetFullName( Handle, NULL, fullname );

        // get the pointer for later
        regobj = GetPointer( Handle );
        ReleasePointer( regobj );
    }

    ntstatus = RealRegCloseKey( Handle );
    if( iskey ) {
       // DbgPrint(("RegCloseKey: %s => %x, %x\n", fullname, Handle, ntstatus ));
        data[0] = 0;
        if( NT_SUCCESS( ntstatus )) {
            if( regobj ) RegmonFreeHashEntry( regobj );
          /*   sprintf(data,"Key: 0x%X", regobj );
           if( FilterDef.logreads && GetProcess( name ) && ApplyNameFilter(fullname) && ErrorString( ntstatus )) {
                UpdateStore( "%s\tCloseKey\t%s\t%s\t%s", 
                             name, fullname, ErrorString( ntstatus ), data );
							 }*/
        }
    }

	ExFreePool(fullname);
    ExFreePool( data );
    return ntstatus;
}


//----------------------------------------------------------------------
//
// HookRegFlushKey
//
//----------------------------------------------------------------------
NTSTATUS HookRegFlushKey( IN HANDLE Handle )
{
    NTSTATUS                ntstatus;
    CHAR                    fullname[MAXPATHLEN], name[MAXPROCNAMELEN];
    POBJECT                 regobj;

    GetFullName( Handle, NULL, fullname );
    ntstatus = RealRegFlushKey( Handle );
    //DbgPrint(("RegFlushKey: %s => 0x%X\n", fullname, ntstatus ));
    /*regobj = GetPointer( Handle );
    ReleasePointer( regobj );
    if( FilterDef.logwrites && GetProcess( name ) && ApplyNameFilter(fullname) && ErrorString( ntstatus )) {
        UpdateStore( "%s\tFlushKey\t%s\t%s\tKey: 0x%X", 
                     name, fullname, ErrorString( ntstatus ), regobj);
    }*/
    return ntstatus;
}


//----------------------------------------------------------------------
//
// HookRegDeleteKey
//
// Once we've deleted a key, we can remove its reference in the hash 
// table.
//
//----------------------------------------------------------------------
NTSTATUS HookRegDeleteKey( IN HANDLE Handle )
{
    NTSTATUS                ntstatus;
    POBJECT                 regobj;
    CHAR                    fullname[MAXPATHLEN], name[MAXPROCNAMELEN];

    GetFullName( Handle, NULL, fullname );
    regobj = GetPointer( Handle );
    ReleasePointer( regobj );
    ntstatus = RealRegDeleteKey( Handle );
    //DbgPrint(("RegDeleteKey: %s => 0x%X\n", fullname, ntstatus ));
    /*if( FilterDef.logwrites && GetProcess( name ) && ApplyNameFilter(fullname) && ErrorString( ntstatus )) {
        UpdateStore( "%s\tDeleteKey\t%s\t%s\tKey: 0x%X", 
                     name, fullname, 
                     ErrorString( ntstatus ), regobj);
    }*/
    return ntstatus;
}


//----------------------------------------------------------------------
//
// HookRegDeleteValueKey
//
//----------------------------------------------------------------------
NTSTATUS HookRegDeleteValueKey( IN HANDLE Handle, PUNICODE_STRING Name )
{
    NTSTATUS                ntstatus;
    CHAR                    fullname[MAXPATHLEN], name[MAXPROCNAMELEN];
	UNICODE_STRING UnicodeName;
	ANSI_STRING AnsiName;

	GetFullName(Handle, Name, fullname);

	RtlInitAnsiString(&AnsiName, fullname);
	ntstatus = RtlAnsiStringToUnicodeString(&UnicodeName, &AnsiName, TRUE);
	if(!NT_SUCCESS(ntstatus))
	{
		return ntstatus;
	} // 结束 if(!NT_SUCCESS(ntstatus))
	if(IsProtect(&UnicodeName, &g_ProtectRegisterNameHead, CompareCallBack))
	{
		ntstatus = STATUS_ACCESS_DENIED; //STATUS_NOT_FOUND;
	}// 结束 if(IsProtect(&UnicodeName, &g_ProtectRegisterNameHead, CompareCallBack))
	RtlFreeUnicodeString(&UnicodeName);

	if(NT_SUCCESS(ntstatus))
	{
		ntstatus = RealRegDeleteValueKey(Handle, Name);
	} // 结束 if(NT_SUCCESS(ntstatus))
    //DbgPrint(("RegDeleteValueKey: %s => %x\n", fullname, ntstatus ));
    /*if( FilterDef.logwrites && GetProcess( name ) && ApplyNameFilter(fullname) && ErrorString( ntstatus ) ) {
        UpdateStore( "%s\tDeleteValueKey\t%s\t%s\t", 
                     name, fullname, ErrorString( ntstatus ));
    }*/
    return ntstatus;
}


//----------------------------------------------------------------------
//
// HookRegSetValueKey
//
//---------------------------------------------------------------------- 
NTSTATUS HookRegSetValueKey( IN HANDLE KeyHandle, IN PUNICODE_STRING ValueName,
                             IN ULONG TitleIndex, IN ULONG Type, IN PVOID Data, IN ULONG DataSize )
{
    NTSTATUS                ntstatus;
    PUNICODE_STRING         valueName;
    CHAR                    fullname[MAXPATHLEN], data[MAXVALLEN], name[MAXPROCNAMELEN];

    if( !ValueName || !ValueName->Length ) valueName = &DefaultValue;
    else                                   valueName = ValueName;
    GetFullName( KeyHandle, valueName, fullname );
    ntstatus = RealRegSetValueKey( KeyHandle, ValueName, TitleIndex,
                                   Type, Data, DataSize );
    data[0] = 0;
    if( NT_SUCCESS( ntstatus )) 
        AppendRegValueData( Type, Data, DataSize, data );
    //DbgPrint(("SetValue: %s (%s)\n", fullname, data ));
    /*if( FilterDef.logwrites && GetProcess( name ) && ApplyNameFilter(fullname) && ErrorString( ntstatus )) {
        UpdateStore( "%s\tSetValue\t%s\t%s\t%s", 
                     name, fullname, ErrorString( ntstatus ), data );
    }*/
    return ntstatus;
}


//----------------------------------------------------------------------
//
// HookRegEnumerateKey
//
// This is a documented Zw-class function. 
//
//----------------------------------------------------------------------
NTSTATUS HookRegEnumerateKey( IN HANDLE KeyHandle, IN ULONG Index,
                              IN KEY_INFORMATION_CLASS KeyInformationClass,
                              OUT PVOID KeyInformation, IN ULONG Length, OUT PULONG pResultLength )
{
	NTSTATUS                ntstatus = STATUS_SUCCESS;
	CHAR                    fullname[MAXPATHLEN], data[MAXVALLEN], name[MAXPROCNAMELEN];
	UNICODE_STRING UnicodeName;
	ANSI_STRING AnsiName;
	PHASH_ENTRY pHashEntry = NULL;
	BOOLEAN bExit = FALSE;
	ULONG nIndex = Index;

	pHashEntry = RegmonGetHashEntry(KeyHandle);
	if(NULL == pHashEntry)
	{
		//ASSERT(0);
		ntstatus = RealRegEnumerateKey(KeyHandle, Index, KeyInformationClass,
			KeyInformation, Length, pResultLength);
		return ntstatus;
	}// 结束 if(NULL == pHashEntry)
	
	while(!bExit && NT_SUCCESS(ntstatus))
	{
		nIndex = Index + pHashEntry->nHideNum;
		ntstatus = RealRegEnumerateKey(KeyHandle, nIndex, KeyInformationClass,
			KeyInformation, Length, pResultLength );
		data[0] = 0;
		if(NT_SUCCESS(ntstatus))
		{
			AppendKeyInformation(KeyInformationClass, KeyInformation, data);
			GetFullName(KeyHandle, NULL, fullname);
			strcat(fullname, "\\");
			strncatZ(fullname, data, MAXPATHLEN - 1 - strlen(data));

			RtlInitAnsiString(&AnsiName, fullname);
			ntstatus = RtlAnsiStringToUnicodeString(&UnicodeName, &AnsiName, TRUE);
			if(NT_SUCCESS(ntstatus))
			{
				if(IsProtect(&UnicodeName, &g_ProtectRegisterNameHead, CompareCallBack))
				{
					bExit = FALSE;
					pHashEntry->nHideNum++;
				}
				else
				{
					bExit = TRUE;
				}
				RtlFreeUnicodeString(&UnicodeName);
			} // 结束 if(NT_SUCCESS(ntstatus))
		}// 结束 if(NT_SUCCESS(ntstatus))
	} // 结束 while(!bExit && NT_SUCCESS(ntstatus))

    //DbgPrint(("EnumerateKey: %s (%s) => %x\n", fullname, data, ntstatus ));
    /*if( FilterDef.logreads && GetProcess( name ) && ApplyNameFilter(fullname) && ErrorString( ntstatus )) {
        UpdateStore( "%s\tEnumerateKey\t%s\t%s\t%s", 
                     name, fullname, ErrorString( ntstatus ), data );
    }*/
    return ntstatus;
}


//----------------------------------------------------------------------
//
// HookRegQueryKey
//
// This is a documented Zw-class function. This will get called
// from our CloseKey hook routine, because this is the only easy
// way we can determine if a registry key is being closed. Thus, we
// have to watch for those calls and not log any data about them.
//
//----------------------------------------------------------------------
NTSTATUS HookRegQueryKey( IN HANDLE  KeyHandle, 
                          IN KEY_INFORMATION_CLASS  KeyInformationClass,
                          OUT PVOID  KeyInformation, IN ULONG  Length, 
                          OUT PULONG  pResultLength )
{
    NTSTATUS                ntstatus;
    CHAR                    name[MAXPROCNAMELEN];
    PCHAR                   fullname, data;

    //
    // Allocate data from pool since this routine is called from the HookRegClose routine, 
    // which is called on non-key object and so is likely to be originating in a driver
    // that may already have strained stack space.
    //
    fullname = ExAllocatePool( NonPagedPool, MAXPATHLEN );
    data     = ExAllocatePool( NonPagedPool, MAXVALLEN );

    GetFullName( KeyHandle, NULL, fullname );

    ntstatus = RealRegQueryKey( KeyHandle, KeyInformationClass,
                                KeyInformation, Length, pResultLength );

    // print out different stuff depending on type of info asked for
    data[0] = 0;
    if( NT_SUCCESS( ntstatus )) 
        AppendKeyInformation( KeyInformationClass, KeyInformation, data );

    //DbgPrint(("QueryKey: %s (%s) => %x\n", fullname, data, ntstatus ));
   /* if( FilterDef.logreads && GetProcess( name ) && ApplyNameFilter(fullname) && ErrorString( ntstatus )) {
        UpdateStore( "%s\tQueryKey\t%s\t%s\t%s", 
                     name, fullname, ErrorString( ntstatus ), data );
    }*/

    ExFreePool( fullname );
    ExFreePool( data );
    return ntstatus;
}

NTSTATUS ReCallEnumerValueKey(IN HANDLE KeyHandle, IN ULONG Index,
							  IN KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
							  OUT PVOID KeyValueInformation, IN ULONG Length,
							  OUT PULONG pResultLength, OUT ULONG * pnHide)
{
	NTSTATUS ntstatus = STATUS_SUCCESS;
	CHAR                    fullname[MAXPATHLEN], data[MAXVALLEN]; 
	CHAR                    valuename[MAXVALLEN], name[MAXPROCNAMELEN];
	UNICODE_STRING UnicodeName;
	ANSI_STRING AnsiName;
	BOOLEAN bExit = FALSE;
	ULONG nIndex = 0, nHideNum = 0;

	while(nIndex <= Index)
	{
		ntstatus = RealRegEnumerateValueKey(KeyHandle, nIndex++,
			KeyValueInformationClass,
			KeyValueInformation, Length, 
			pResultLength);

		data[0] = 0;

		if(NT_SUCCESS(ntstatus))
		{
			AppendValueInformation( KeyValueInformationClass, 
				KeyValueInformation, data, valuename);
			GetFullName(KeyHandle, NULL, fullname);
			strcat( fullname, "\\" );
			strncatZ(fullname, valuename, MAXPATHLEN - 1 - strlen(fullname));

			RtlInitAnsiString(&AnsiName, fullname);
			ntstatus = RtlAnsiStringToUnicodeString(&UnicodeName, &AnsiName, TRUE);
			if(NT_SUCCESS(ntstatus))
			{
				if(IsProtect(&UnicodeName, &g_ProtectRegisterNameHead, CompareCallBack))
				{
					nHideNum++;
				}// 结束 (IsProtect(&UnicodeName, &g_ProtectRegisterNameHead, CompareCallBack))
				RtlFreeUnicodeString(&UnicodeName);
			} // 结束 if(NT_SUCCESS(ntstatus))
		}
		DbgPrint(("ReCallEnumerValueKey: %s (%s) =>%x\n", fullname, data, ntstatus));
	} // 结束 while(nIndex <= Index)

	*pnHide = nHideNum;

	return ntstatus;
}

//----------------------------------------------------------------------
//
// HookRegEnumerateValueKey
//
// This is a documented Zw-class function.
//
//----------------------------------------------------------------------
NTSTATUS HookRegEnumerateValueKey( IN HANDLE KeyHandle, IN ULONG Index,
                                   IN KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
                                   OUT PVOID KeyValueInformation, IN ULONG Length,
                                   OUT PULONG  pResultLength )
{
	NTSTATUS ntstatus = STATUS_SUCCESS;
	CHAR fullname[MAXPATHLEN], data[MAXVALLEN];
	CHAR valuename[MAXVALLEN], name[MAXPROCNAMELEN];
	UNICODE_STRING UnicodeName;
	ANSI_STRING AnsiName;
	PHASH_ENTRY pHashEntry = NULL;
	BOOLEAN bExit = FALSE;
	ULONG nIndex = Index, nHideNum = 0;

	while(!bExit && NT_SUCCESS(ntstatus))
	{
		nIndex = Index + nHideNum;
		ntstatus = ReCallEnumerValueKey(KeyHandle, nIndex,
			KeyValueInformationClass,
			KeyValueInformation, Length, 
			pResultLength, &nHideNum);

		//if(ntstatus)
		//{
		//	break;
		//}// 结束 if(ntstatus)

		nIndex = Index + nHideNum;
		ntstatus = RealRegEnumerateValueKey(KeyHandle, nIndex,
			KeyValueInformationClass,
			KeyValueInformation, Length, 
			pResultLength);

		data[0] = 0;

		if( NT_SUCCESS( ntstatus )) {
			AppendValueInformation( KeyValueInformationClass, 
				KeyValueInformation, data, valuename);
			GetFullName(KeyHandle, NULL, fullname);
			strcat( fullname, "\\" );
			strncatZ(fullname, valuename, MAXPATHLEN - 1 - strlen(fullname));

			RtlInitAnsiString(&AnsiName, fullname);
			ntstatus = RtlAnsiStringToUnicodeString(&UnicodeName, &AnsiName, TRUE);
			if(NT_SUCCESS(ntstatus))
			{
				if(IsProtect(&UnicodeName, &g_ProtectRegisterNameHead, CompareCallBack))
				{
					bExit = FALSE;
					nHideNum++;
				}
				else
				{
					bExit = TRUE;
				}// 结束 (IsProtect(&UnicodeName, &g_ProtectRegisterNameHead, CompareCallBack))
				RtlFreeUnicodeString(&UnicodeName);
			} // 结束 if(NT_SUCCESS(ntstatus))
		}
		DbgPrint(("EnumerateValue: %s (%s) =>%x\n", fullname, data, ntstatus));
	} // 结束 while(!bExit && NT_SUCCESS(ntstatus))
	

	/*if( FilterDef.logreads && GetProcess( name ) && ApplyNameFilter(fullname) && ErrorString( ntstatus )) {
        UpdateStore( "%s\tEnumerateValue\t%s\t%s\t%s", 
                     name, fullname, ErrorString( ntstatus ), data );
    }*/

    return ntstatus;
}


//----------------------------------------------------------------------
//
// HookRegQueryValueKey
//
// This is a documented Zw-class function.
//
//----------------------------------------------------------------------
NTSTATUS HookRegQueryValueKey( IN HANDLE KeyHandle,
                               IN PUNICODE_STRING ValueName,
                               IN KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
                               OUT PVOID KeyValueInformation, IN ULONG Length,
                               OUT PULONG  pResultLength )
{
    NTSTATUS                ntstatus;
    PUNICODE_STRING         valueName;
    CHAR                    fullname[MAXPATHLEN], data[MAXVALLEN], name[MAXPROCNAMELEN];
	UNICODE_STRING UnicodeName;
	ANSI_STRING AnsiName;

    if( !ValueName || !ValueName->Length ) valueName = &DefaultValue;
    else                                   valueName = ValueName;
	GetFullName(KeyHandle, valueName, fullname);

	RtlInitAnsiString(&AnsiName, fullname);
	ntstatus = RtlAnsiStringToUnicodeString(&UnicodeName, &AnsiName, TRUE);
	if(!NT_SUCCESS(ntstatus))
	{
		return ntstatus;
	} // 结束 if(!NT_SUCCESS(ntstatus))
	//if(IsProtect(&UnicodeName, &g_ProtectRegisterNameHead, CompareCallBack))
	//{
	//	ntstatus = STATUS_ACCESS_DENIED; //STATUS_OBJECT_NAME_NOT_FOUND;
	//}// 结束 if(IsProtect(&UnicodeName, &g_ProtectRegisterNameHead, CompareCallBack))
	RtlFreeUnicodeString(&UnicodeName);

	if(NT_SUCCESS(ntstatus))
	{
		ntstatus = RealRegQueryValueKey(KeyHandle, ValueName,
                                     KeyValueInformationClass,
                                     KeyValueInformation, Length, 
                                     pResultLength );
	}// 结束 if(NT_SUCCESS(ntstatus))

	data[0] = 0;
    if( NT_SUCCESS( ntstatus )) 
        AppendValueInformation( KeyValueInformationClass, 
                                KeyValueInformation, data, FALSE );
    //DbgPrint(("QueryValue: %s (%s) =>%x\n", fullname, data, ntstatus ));
   /* if( FilterDef.logreads && GetProcess( name ) && ApplyNameFilter(fullname) && ErrorString( ntstatus )) {
        UpdateStore( "%s\tQueryValue\t%s\t%s\t%s", 
                     name, fullname, ErrorString( ntstatus ), data );
    }*/
    return ntstatus;
}

//----------------------------------------------------------------------
//
// HookRegistry
//
// Replaces entries in the system service table with pointers to
// our own hook routines. We save off the real routine addresses.
//
//----------------------------------------------------------------------
VOID HookRegistry( void )
{
    if( !g_RegHooked ) {

        //
        // Hook everything
        //

        RealRegOpenKey = SYSCALL( ZwOpenKey );
        SYSCALL( ZwOpenKey ) = (PVOID) HookRegOpenKey;

        RealRegQueryKey = SYSCALL( ZwQueryKey );
        SYSCALL( ZwQueryKey ) = (PVOID) HookRegQueryKey;

        RealRegQueryValueKey = SYSCALL( ZwQueryValueKey );
        SYSCALL( ZwQueryValueKey ) = (PVOID) HookRegQueryValueKey;

        RealRegEnumerateValueKey = SYSCALL( ZwEnumerateValueKey );
        SYSCALL( ZwEnumerateValueKey ) = (PVOID) HookRegEnumerateValueKey;

        RealRegEnumerateKey = SYSCALL( ZwEnumerateKey );
        SYSCALL( ZwEnumerateKey ) = (PVOID) HookRegEnumerateKey;

        RealRegDeleteKey = SYSCALL( ZwDeleteKey );
        SYSCALL( ZwDeleteKey ) = (PVOID) HookRegDeleteKey;

        RealRegFlushKey = SYSCALL( ZwFlushKey );
        SYSCALL( ZwFlushKey ) = (PVOID) HookRegFlushKey;

        RealRegSetValueKey = SYSCALL( ZwSetValueKey );
        SYSCALL( ZwSetValueKey ) = (PVOID) HookRegSetValueKey;

        RealRegCreateKey = SYSCALL( ZwCreateKey );
#if defined(_ALPHA_)
        SYSCALL( ZwCreateKey ) = (PVOID) ((ULONG) HookRegCreateKey + ((ULONG) RealRegCreateKey & 0x00000003));
#else
        SYSCALL( ZwCreateKey ) = (PVOID) HookRegCreateKey;
#endif

        RealRegDeleteValueKey = SYSCALL( ZwDeleteValueKey );
        SYSCALL( ZwDeleteValueKey ) = (PVOID) HookRegDeleteValueKey;

        RealRegCloseKey = SYSCALL( ZwClose );
        SYSCALL( ZwClose ) = (PVOID) HookRegCloseKey;

        g_RegHooked = TRUE;

    }
}


//----------------------------------------------------------------------
//
// UnhookRegistry
//
// Unhooks all registry routines by replacing the hook addresses in 
// the system service table with the real routine addresses that we
// saved off.
//
//----------------------------------------------------------------------
VOID UnhookRegistry( )
{
    if( g_RegHooked ) {

        //
        // Unhook everything
        //
        SYSCALL( ZwOpenKey ) = (PVOID) RealRegOpenKey;
        SYSCALL( ZwQueryKey ) = (PVOID) RealRegQueryKey;
        SYSCALL( ZwQueryValueKey ) = (PVOID) RealRegQueryValueKey;
        SYSCALL( ZwEnumerateValueKey ) = (PVOID) RealRegEnumerateValueKey;
        SYSCALL( ZwEnumerateKey ) = (PVOID) RealRegEnumerateKey;
        SYSCALL( ZwClose ) = (PVOID) RealRegCloseKey;
        SYSCALL( ZwFlushKey ) = (PVOID) RealRegFlushKey;
        SYSCALL( ZwDeleteKey ) = (PVOID) RealRegDeleteKey;
        SYSCALL( ZwSetValueKey ) = (PVOID) RealRegSetValueKey;
        SYSCALL( ZwCreateKey ) = (PVOID) RealRegCreateKey;
        SYSCALL( ZwDeleteValueKey ) = (PVOID) RealRegDeleteValueKey;

        g_RegHooked = FALSE;
	}
}
