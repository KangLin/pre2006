/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    SupportRoute.c
\brief   支持函数实现文件
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年6月7日  13:53:29
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#include "FilterSys.H"
#include <stdio.h>

//
// Global error string
//
CHAR                    g_Errstring[256];

//======================================================================
//  R E G I S T R Y  P A R A M E T E R  S U P P O R T  R O U T I N E S
//======================================================================

//----------------------------------------------------------------------
//
// ConverToUpper
//
// Obvious.
//
//----------------------------------------------------------------------
VOID ConvertToUpper( PCHAR Dest, PCHAR Source, ULONG Len )
{
    ULONG   i;
    
    for( i = 0; i < Len; i++ ) {
        if( Source[i] >= 'a' && Source[i] <= 'z' ) {

            Dest[i] = Source[i] - 'a' + 'A';

        } else {

            Dest[i] = Source[i];
        }
    }
}

//----------------------------------------------------------------------
// 
// strncatZ
//
// Appends a string to another and attaches a null. NT 3.51 ntoskrnl
// does not export this function so we have to make our own, and give
// it a name that won't conflict with the strncat that NT 4.0 exports.
//
//----------------------------------------------------------------------
PCHAR strncatZ( PCHAR dest, PCHAR source, int length )
{       
    int     origlen = strlen(dest);

    strncpy( dest+origlen, source, length );
    dest[ origlen+length ] = 0;
    return(dest);
}

//----------------------------------------------------------------------
//
// GetPointer
//
// Translates a handle to an object pointer.
//
//----------------------------------------------------------------------
POBJECT GetPointer( HANDLE handle )
{
    POBJECT         pKey;

    //
    // Ignore null handles
    //
    if( !handle ) return NULL;

    //
    // Get the pointer the handle refers to
    //
    if( ObReferenceObjectByHandle( handle, 0, NULL, KernelMode, &pKey, NULL ) !=
        STATUS_SUCCESS ) {

        DbgPrint(("Error %x getting key pointer\n"));
        pKey = NULL;
    } 
    return pKey;
}


//----------------------------------------------------------------------
//
// ReleasePointer
//
// Dereferences the object.
//
//----------------------------------------------------------------------
VOID ReleasePointer( POBJECT object )
{
    if( object ) ObDereferenceObject( object );
}



//----------------------------------------------------------------------
//
// AppendKeyInformation
//
// Appends key enumerate and query information to the output buffer.
//
//----------------------------------------------------------------------
VOID AppendKeyInformation( IN KEY_INFORMATION_CLASS KeyInformationClass,
                           IN PVOID KeyInformation, PCHAR Buffer )
{
    PKEY_BASIC_INFORMATION  pbasicinfo;
    PKEY_FULL_INFORMATION   pfullinfo;
    PKEY_NODE_INFORMATION   pnodeinfo;
    UNICODE_STRING          ukeyname;       
    ANSI_STRING             akeyname;

    switch( KeyInformationClass ) {

    case KeyBasicInformation:
        pbasicinfo = (PKEY_BASIC_INFORMATION) KeyInformation;
        ukeyname.Length = (USHORT) pbasicinfo->NameLength;
        ukeyname.MaximumLength = (USHORT) pbasicinfo->NameLength;
        ukeyname.Buffer = pbasicinfo->Name;
        RtlUnicodeStringToAnsiString( &akeyname, &ukeyname, TRUE );
        sprintf( Buffer, "%s", akeyname.Buffer );
        RtlFreeAnsiString( &akeyname );
        break;

    case KeyFullInformation:
        pfullinfo = (PKEY_FULL_INFORMATION) KeyInformation;
        sprintf( Buffer, "Subkeys = %d", pfullinfo->SubKeys );
        break;  
        
    case KeyNodeInformation:
        pnodeinfo = (PKEY_NODE_INFORMATION) KeyInformation;
        ukeyname.Length = (USHORT) pnodeinfo->NameLength;
        ukeyname.MaximumLength = (USHORT) pnodeinfo->NameLength;
        ukeyname.Buffer = pnodeinfo->Name;
        RtlUnicodeStringToAnsiString( &akeyname, &ukeyname, TRUE );
		sprintf(Buffer, "%s", akeyname.Buffer);
        RtlFreeAnsiString( &akeyname );
        break;

    default:
        sprintf( Buffer, "Unknown Info Class" );
        break;
    }
}


//----------------------------------------------------------------------
//
// AppendRegValueType
//
// Returns the string form of an registry value type.
//
//----------------------------------------------------------------------
VOID AppendRegValueType( ULONG Type, PCHAR Buffer )
{
    CHAR            tmp[MAXDATALEN];

    switch( Type ) {
    case REG_BINARY:
        strcat( Buffer, "BINARY" );
        break;
    case REG_DWORD_LITTLE_ENDIAN:
        strcat( Buffer, "DWORD_LITTLE_END" );
        break;
    case REG_DWORD_BIG_ENDIAN:
        strcat( Buffer, "DWORD_BIG_END" );
        break;
    case REG_EXPAND_SZ:
        strcat( Buffer, "EXPAND_SZ" );
        break;
    case REG_LINK:
        strcat( Buffer, "LINK" );
        break;
    case REG_MULTI_SZ:
        strcat( Buffer, "MULTI_SZ" );
        break;
    case REG_NONE:
        strcat( Buffer, "NONE" );
        break;
    case REG_SZ:
        strcat( Buffer, "SZ" );
        break;
    case REG_RESOURCE_LIST:
        strcat( Buffer, "RESOURCE_LIST" );
        break;
    case REG_RESOURCE_REQUIREMENTS_LIST:
        strcat( Buffer, "REQ_LIST" );
        break;
    case REG_FULL_RESOURCE_DESCRIPTOR:
        strcat( Buffer, "DESCRIPTOR" );
        break;
    default:
        sprintf( tmp, "UNKNOWN TYPE: %d", Type );
        strcat( Buffer, tmp );
        break;
    }
}


//----------------------------------------------------------------------
//
// AppendRegValueData
//
// We expand certain registry types to provide more information. In
// all cases, calculate the length of the data being copied so 
// we don't overflow the buffer that's passed in. The length of Buffer 
// must be MAXVALLEN.
//
//----------------------------------------------------------------------
VOID AppendRegValueData( IN ULONG Type, IN PVOID Data, IN ULONG Length, 
                         IN OUT PCHAR Buffer )
{
    PWCHAR                  pstring;
    PULONG                  pulong;
    PUCHAR                  pbinary;
    CHAR                    tmp[MAXDATALEN];
    UNICODE_STRING          ukeyname;       
    ANSI_STRING             akeyname;
    int                     len, i;

    switch( Type ) {
    case REG_SZ:    
    case REG_EXPAND_SZ:
    case REG_MULTI_SZ:
        pstring = (PWCHAR) Data;
        ukeyname.Length = (USHORT) Length;
        ukeyname.MaximumLength = (USHORT) Length;
        ukeyname.Buffer = pstring;
        RtlUnicodeStringToAnsiString( &akeyname, 
                                      &ukeyname, TRUE );    
        strcat( Buffer, "\"");
        strncatZ( Buffer+1, akeyname.Buffer, MAXVALLEN - 6);
        if( akeyname.Length > MAXVALLEN - 6 ) strcat( Buffer,"...");
        strcat( Buffer, "\"");
        RtlFreeAnsiString( &akeyname );
        break;

    case REG_DWORD:
        pulong = (PULONG) Data;
        sprintf( tmp, "0x%X", *pulong );
        strcat( Buffer, tmp );
        break;

    case REG_BINARY:
    case REG_RESOURCE_LIST:
    case REG_FULL_RESOURCE_DESCRIPTOR:
    case REG_RESOURCE_REQUIREMENTS_LIST:
        pbinary = (PCHAR) Data;
        if( Length > 8 ) len = 8;
        else len = Length;
        for( i = 0; i < len; i++ ) {
            sprintf( tmp, "%02X ", (UCHAR) pbinary[i]);
            strcat( Buffer, tmp );
        }
        if( Length > 8) strcat( Buffer, "...");
        break;

    default:
        AppendRegValueType( Type, Buffer );
        break;
    }
}


//----------------------------------------------------------------------
//
// AppendValueInformation
//
// Appends value enumerate and query information to the output buffer.
//
//----------------------------------------------------------------------
VOID AppendValueInformation( IN KEY_VALUE_INFORMATION_CLASS KeyValueInformationClass,
                             IN PVOID KeyValueInformation, PCHAR Buffer, PCHAR ValueName )
{
    PKEY_VALUE_BASIC_INFORMATION    pbasicinfo;
    PKEY_VALUE_FULL_INFORMATION     pfullinfo;
    PKEY_VALUE_PARTIAL_INFORMATION  ppartinfo;
    UNICODE_STRING                  ukeyname;       
    ANSI_STRING                     akeyname;

    switch( KeyValueInformationClass ) {

    case KeyValueBasicInformation:
        pbasicinfo = (PKEY_VALUE_BASIC_INFORMATION)
            KeyValueInformation;
        sprintf( Buffer, "Type: ");
        AppendRegValueType( pbasicinfo->Type, Buffer );
        strncatZ( Buffer, " Name: ", MAXVALLEN - 1 - strlen(Buffer) );
        ukeyname.Length = (USHORT) pbasicinfo->NameLength;
        ukeyname.MaximumLength = (USHORT) pbasicinfo->NameLength;
        ukeyname.Buffer = pbasicinfo->Name;
        RtlUnicodeStringToAnsiString( &akeyname, &ukeyname, TRUE );
        strncatZ( Buffer, akeyname.Buffer, MAXVALLEN - 1 - strlen(Buffer) );
        if( ValueName ) strncpy( ValueName, akeyname.Buffer, MAXVALLEN - 1 );
        RtlFreeAnsiString( &akeyname );                 
        break;

    case KeyValueFullInformation:   
        pfullinfo = (PKEY_VALUE_FULL_INFORMATION) 
            KeyValueInformation;
        AppendRegValueData( pfullinfo->Type, 
                            (PVOID) ((PCHAR) pfullinfo + pfullinfo->DataOffset), 
                            pfullinfo->DataLength, Buffer );
        if( ValueName ) {
            ukeyname.Length = (USHORT) pfullinfo->NameLength;
            ukeyname.MaximumLength = (USHORT) pfullinfo->NameLength;
            ukeyname.Buffer = pfullinfo->Name;
            RtlUnicodeStringToAnsiString( &akeyname, &ukeyname, TRUE );
            strncpy( ValueName, akeyname.Buffer, MAXVALLEN - 1 );
            RtlFreeAnsiString( &akeyname ); 
        }
        break;

    case KeyValuePartialInformation:
        ppartinfo = (PKEY_VALUE_PARTIAL_INFORMATION)
            KeyValueInformation;
        AppendRegValueData( ppartinfo->Type, 
                            (PVOID) ppartinfo->Data, 
                            ppartinfo->DataLength, Buffer );
        break;

    default:
        sprintf( Buffer, "Unknown Info Class" );
        break;
    }
}

//----------------------------------------------------------------------
//
// ErrorString
//
// Returns the string form of an error code.
//
//----------------------------------------------------------------------
PCHAR ErrorString( NTSTATUS retval )
{
    //
    // Before transating, apply error filter
    //
	if(retval == STATUS_SUCCESS)
	{
		return NULL;
	} // 结束 if(retval == STATUS_SUCCESS)
	if(retval != STATUS_SUCCESS)
	{
		return NULL;
	} // 结束 if(retval != STATUS_SUCCESS)

    //
    // Passed filter, so log it
    //
    switch( retval ) {
    case STATUS_BUFFER_TOO_SMALL:
        return "BUFTOOSMALL";
    case STATUS_SUCCESS:
        return "SUCCESS";
    case STATUS_KEY_DELETED:
        return "KEYDELETED";
    case STATUS_REGISTRY_IO_FAILED:
        return "IOFAILED";
    case STATUS_REGISTRY_CORRUPT:
        return "CORRUPT";
    case STATUS_NO_MEMORY:
        return "OUTOFMEM";
    case STATUS_ACCESS_DENIED:
        return "ACCDENIED";
    case STATUS_NO_MORE_ENTRIES:
        return "NOMORE";
    case STATUS_OBJECT_NAME_NOT_FOUND:
        return "NOTFOUND";
    case STATUS_BUFFER_OVERFLOW:
        return "BUFOVRFLOW";
    case STATUS_OBJECT_PATH_SYNTAX_BAD:
        return "SYNTAXERR";
    default:
		sprintf(g_Errstring, "%x", retval);
		return g_Errstring;
    }
}


//----------------------------------------------------------------------
//
// GetFullName
//
// Returns the full pathname of a key, if we can obtain one, else
// returns a handle.
//
//----------------------------------------------------------------------
void GetFullName( HANDLE hKey, PUNICODE_STRING lpszSubKeyVal, 
                  PCHAR fullname )
{
    PHASH_ENTRY             hashEntry;
    POBJECT                 pKey = NULL;
    CHAR                    tmpkey[16];
    ANSI_STRING             keyname;
    PCHAR                   tmpname;
    CHAR                    cmpname[MAXROOTLEN];
    PCHAR                   nameptr;
    PUNICODE_STRING         fullUniName;
    ULONG                   actualLen;
    int                     i;

    //
    // Allocate a temporary buffer
    //
    tmpname = ExAllocatePool( NonPagedPool, MAXPATHLEN );

    //
    // Translate the hkey into a pointer
    //
    fullname[0] = 0;
    tmpname[0] = 0;

    //
    // Is it a valid handle?
    //
    if( pKey = GetPointer( hKey )) {

        //
        // See if we find the key in the hash table
        //
        ReleasePointer( pKey );
        MUTEX_WAIT( HashMutex );
        hashEntry = HashTable[ HASHOBJECT( pKey ) ];
        while( hashEntry && hashEntry->Object != pKey )
            hashEntry = hashEntry->Next;
        MUTEX_RELEASE( HashMutex );

        if( hashEntry ) {

            strcpy( tmpname, hashEntry->FullPathName );

        } else {

            //
            // We will only get here if key was created before we loaded - ask the Configuration
            // Manager what the name of the key is.
            //
            if( pKey ) {

                fullUniName = ExAllocatePool( NonPagedPool, MAXPATHLEN*2+2*sizeof(ULONG));
                fullUniName->MaximumLength = MAXPATHLEN*2;
        
                if( NT_SUCCESS(ObQueryNameString( pKey, fullUniName, MAXPATHLEN, &actualLen ) )) {

                    RtlUnicodeStringToAnsiString( &keyname, fullUniName, TRUE ); 
                    if( keyname.Buffer[0] ) {         
                        strcpy( tmpname, "\\" );
                        strncatZ( tmpname, keyname.Buffer, MAXPATHLEN -2 );
                    }
                    RtlFreeAnsiString( &keyname );
                }
                ExFreePool( fullUniName );
            }
        }
    }

    //
    // Append subkey and value, if they are there
    //
    if( lpszSubKeyVal ) {
        RtlUnicodeStringToAnsiString( &keyname, lpszSubKeyVal, TRUE );
        if( keyname.Buffer[0] ) {
            strcat( tmpname, "\\" );
            strncatZ( tmpname, keyname.Buffer, MAXPATHLEN - 1 - strlen(tmpname) );
        }
        RtlFreeAnsiString( &keyname );
    }

    //
    // See if it matches current user
    //
    for( i = 0; i < 2; i++ ) {
        ConvertToUpper( cmpname, tmpname, CurrentUser[i].RootNameLen );
        if( !strncmp( cmpname, CurrentUser[i].RootName,
                      CurrentUser[i].RootNameLen )) {

           /* DbgPrint(( " CurrentUser(%d) %s ==> %s\n", i, 
                       tmpname, CurrentUser[i].RootName ));*/

            //
            // Its current user. Process to next slash
            //
            nameptr = tmpname + CurrentUser[i].RootNameLen;
            while( *nameptr && *nameptr != '\\' ) nameptr++;
            strcpy( fullname, CurrentUser[i].RootShort );
            strcat( fullname, nameptr );
            ExFreePool( tmpname );
            return;
        }
    }     

    //
    // Now, see if we can translate a root key name
    //
    for( i = 0; i < NUMROOTKEYS; i++ ) {
        ConvertToUpper( cmpname, tmpname, RootKey[i].RootNameLen );
        if( !strncmp( cmpname, RootKey[i].RootName, 
                      RootKey[i].RootNameLen )) {
            nameptr = tmpname + RootKey[i].RootNameLen;
            strcpy( fullname, RootKey[i].RootShort );
            strcat( fullname, nameptr );
            ExFreePool( tmpname );
            return;
        }
    }

    //
    // No translation
    //
    strcpy( fullname, tmpname );
    ExFreePool( tmpname ); 
}


////----------------------------------------------------------------------
////
//// GetProcessNameOffset
////
//// In an effort to remain version-independent, rather than using a
//// hard-coded into the KPEB (Kernel Process Environment Block), we
//// scan the KPEB looking for the name, which should match that
//// of the GUI process
////
////----------------------------------------------------------------------
//ULONG GetProcessNameOffset()
//{
//    PEPROCESS       curproc;
//    int             i;
//
//    curproc = PsGetCurrentProcess();
//
//    //
//    // Scan for 12KB, hopping the KPEB never grows that big!
//    //
//    for( i = 0; i < 3*PAGE_SIZE; i++ ) {
//     
//        if( !strncmp( SYSNAME, (PCHAR) curproc + i, strlen(SYSNAME) )) {
//
//            return i;
//        }
//    }
//
//    //
//    // Name not found - oh, well
//    //
//    return 0;
//}
//
//
//
////----------------------------------------------------------------------
////
//// GetProcess
////
//// Uses undocumented data structure offsets to obtain the name of the
//// currently executing process.
////
////----------------------------------------------------------------------
//PCHAR GetProcess( PCHAR Name )
//{
//    PEPROCESS       curproc;
//    char            *nameptr;
//    ULONG           i;
//
//    //
//    // We only try and get the name if we located the name offset
//    //
//    if( ProcessNameOffset ) {
//    
//        curproc = PsGetCurrentProcess();
//        nameptr   = (PCHAR) curproc + ProcessNameOffset;
//        strncpy( Name, nameptr, 16 );
//
//    } else {
//     
//        strcpy( Name, "???");
//    }
//
//    //
//    // Apply process name filters
//    //
//    MUTEX_WAIT( FilterMutex );
//    for( i = 0; i < NumProcessExcludeFilters; i++ ) {
//
//        if( MatchWithPattern( ProcessExcludeFilters[i], Name )) {
//
//            MUTEX_RELEASE( FilterMutex );
//            return NULL;
//        }
//    }
//    for( i = 0; i < NumProcessFilters; i++ ) {
//
//        if( MatchWithPattern( ProcessFilters[i], Name ) ) {
//
//            MUTEX_RELEASE( FilterMutex );
//            return Name;
//        }
//    }
//    MUTEX_RELEASE( FilterMutex );
//    return NULL;
//}