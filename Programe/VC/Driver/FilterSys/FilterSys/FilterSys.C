/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    FilterSys.C
\brief   驱动的入口与退出函数的实现文件
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年6月7日  13:54:23
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#include "FilterSys.H"

extern ARRAYHEAD g_ProtectRegisterNameHead;
extern ARRAYHEAD g_ProtectProcessNameHead;

//
// Pointer to system global service table
//
PSRVTABLE               ServiceTable;

//
// This is the offset into a KPEB of the current process name. This is determined
// dynamically by scanning the process block belonging to the GUI for its name.
//
ULONG                   ProcessNameOffset;

//----------------------------------------------------------------------
//                         GLOBALS
//---------------------------------------------------------------------- 
// our user-inteface device object
PDEVICE_OBJECT g_GUIDevice;
extern BOOLEAN g_ProcessHooked;
extern BOOLEAN g_RegHooked;

//----------------------------------------------------------------------
//
// RegmonUnload
//
// Our job is done - time to leave.
//
//----------------------------------------------------------------------
VOID RegFilterUnload( IN PDRIVER_OBJECT DriverObject )
{
	WCHAR deviceLinkBuffer[] = L"\\DosDevices\\KFilter";
    UNICODE_STRING          deviceLinkUnicodeString;

	DbgPrint(("Regmon.SYS: unloading\n"));

	ClearArray(&g_ProtectRegisterNameHead, ClearCallBack);
	ClearArray(&g_ProtectProcessNameHead, ClearCallBack);

	if(g_ProcessHooked)
	{
		UnHookProcess();
	}// 结束 if(g_ProcessHooked)

	if(g_RegHooked)
	{
		UnhookRegistry();
	}// 结束 if(g_RegHooked)

	//
    // Now we can free any memory we have outstanding
    //
	RegmonHashCleanup();

	//
	// Removes a registered driver from the shutdown notification queue. 
	//
	//IoUnregisterShutdownNotification(g_GUIDevice);

    //
    // Delete the symbolic link for our device
    //
    RtlInitUnicodeString( &deviceLinkUnicodeString, deviceLinkBuffer );
    IoDeleteSymbolicLink( &deviceLinkUnicodeString );

    //
    // Delete the device object
    //
    IoDeleteDevice( DriverObject->DeviceObject );

    DbgPrint(("Regmon.SYS: deleted devices\n"));

}

//----------------------------------------------------------------------
//
// DriverEntry
//
// Installable driver initialization. Here we just set ourselves up.
//
//----------------------------------------------------------------------
NTSTATUS DriverEntry(IN PDRIVER_OBJECT DriverObject, IN PUNICODE_STRING RegistryPath )
{
    NTSTATUS                ntStatus;
    WCHAR                   deviceNameBuffer[]  = L"\\Device\\KFilter";
    UNICODE_STRING          deviceNameUnicodeString;
    WCHAR                   deviceLinkBuffer[]  = L"\\DosDevices\\KFilter";
    UNICODE_STRING          deviceLinkUnicodeString;    
    WCHAR                   startValueBuffer[] = L"Start";
    UNICODE_STRING          startValueUnicodeString;
    WCHAR                   bootMessage[] = 
        L"\nRegmon is logging Registry activity to \\SystemRoot\\Regmon.log\n\n";
    UNICODE_STRING          bootMessageUnicodeString;
    UNICODE_STRING          registryPath; 
    HANDLE                  driverKey;
    PETHREAD                curthread;
    ULONG                   startType, demandStart;
    RTL_QUERY_REGISTRY_TABLE paramTable[2]; 
    OBJECT_ATTRIBUTES       objectAttributes;
    int                     i;

    DbgPrint (("Regmon.SYS: entering DriverEntry\n"));

    // 
    // Query our start type to see if we are supposed to monitor starting
    // at boot time
    //
    registryPath.Buffer = ExAllocatePool( NonPagedPool, 
                                          RegistryPath->Length + sizeof(UNICODE_NULL)); 
 
    if (!registryPath.Buffer) { 
 
        return STATUS_INSUFFICIENT_RESOURCES; 
    } 
 
    registryPath.Length = RegistryPath->Length + sizeof(UNICODE_NULL); 
    registryPath.MaximumLength = registryPath.Length; 

    RtlZeroMemory( registryPath.Buffer, registryPath.Length ); 
 
    RtlMoveMemory( registryPath.Buffer,  RegistryPath->Buffer, 
                   RegistryPath->Length  ); 

    RtlZeroMemory( &paramTable[0], sizeof(paramTable)); 
    paramTable[0].Flags = RTL_QUERY_REGISTRY_DIRECT; 
    paramTable[0].Name = L"Start"; 
    paramTable[0].EntryContext = &startType;
    paramTable[0].DefaultType = REG_DWORD; 
    paramTable[0].DefaultData = &startType; 
    paramTable[0].DefaultLength = sizeof(ULONG); 

    RtlQueryRegistryValues( RTL_REGISTRY_ABSOLUTE,
                            registryPath.Buffer, &paramTable[0], 
                            NULL, NULL  );

    //
    // Set start type to demand start so that boot logging
    // only happens this boot (unless the user reconfigures it in 
    // the GUI)
    //
    InitializeObjectAttributes( &objectAttributes, RegistryPath,
                                OBJ_CASE_INSENSITIVE, NULL, NULL );
    ntStatus = ZwOpenKey( &driverKey, KEY_WRITE, &objectAttributes );
    if( NT_SUCCESS( ntStatus )) {

        demandStart = SERVICE_DEMAND_START;
        RtlInitUnicodeString( &startValueUnicodeString, startValueBuffer );
        ZwSetValueKey( driverKey, &startValueUnicodeString, 0, REG_DWORD, 
                       &demandStart, sizeof(demandStart ));
        ZwClose( driverKey );
    }

    //
    // Setup our name and symbolic link
    //
    RtlInitUnicodeString (&deviceNameUnicodeString,
                          deviceNameBuffer );
    RtlInitUnicodeString (&deviceLinkUnicodeString,
                          deviceLinkBuffer );

    //
    // Set up the device used for GUI communications
    //
    ntStatus = IoCreateDevice ( DriverObject,
                                0,
                                &deviceNameUnicodeString,
                                FILE_DEVICE_REGFILTER,
                                0,
                                TRUE,
                                &g_GUIDevice );
    if (NT_SUCCESS(ntStatus)) {
                
        //
        // Create a symbolic link that the GUI can specify to gain access
        // to this driver/device
        //
        ntStatus = IoCreateSymbolicLink (&deviceLinkUnicodeString,
                                         &deviceNameUnicodeString );

		for(i = 0; i <= IRP_MJ_MAXIMUM_FUNCTION; i++)
		{
			DriverObject->MajorFunction[i] = RegFilterDispatch;
		}// 结束 for(i = 0; i <= IRP_MJ_MAXIMUM_FUNCTION; i++)

        //
        // Create dispatch points for all routines that must be handled
        //
        DriverObject->MajorFunction[IRP_MJ_SHUTDOWN]        =
        DriverObject->MajorFunction[IRP_MJ_CREATE]          =
        DriverObject->MajorFunction[IRP_MJ_CLOSE]           = RegFilterDispatch;
        DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL]  = RegFilterDeviceControl;
#ifdef DBG
        DriverObject->DriverUnload                          = RegFilterUnload;
#endif
    }
    if (!NT_SUCCESS(ntStatus)) {

        DbgPrint(("Regmon: Failed to create our device!\n"));

        //
        // Something went wrong, so clean up (free resources etc)
        //
        if( g_GUIDevice ) IoDeleteDevice( g_GUIDevice );
        IoDeleteSymbolicLink( &deviceLinkUnicodeString );
        return ntStatus;
    }

	//
    // Initialize our mutexes
    //
	MUTEX_INIT(HashMutex);

    //
    // Initialize rootkey lengths
    //
    for( i = 0; i < NUMROOTKEYS; i++ )
        RootKey[i].RootNameLen = strlen( RootKey[i].RootName );
    for( i = 0; i < 2; i++ )
        CurrentUser[i].RootNameLen = strlen( CurrentUser[i].RootName );

    //
    // Pointer to system table data structure is an NTOSKRNL export
    //
    ServiceTable = KeServiceDescriptorTable;
    DbgPrint(("Hookregistry: Servicetable: %x\n", ServiceTable ));

    //
    // Find the process name offset
    //
	//ProcessNameOffset = GetProcessNameOffset();

    //
    // If we're a boot driver start logging now
    //
    if( startType != SERVICE_DEMAND_START ) {

		HookRegistry();
		HookProcess();

        //
        // Tell the user that boot-logging is on
        //
        /*RtlInitUnicodeString( &bootMessageUnicodeString, bootMessage );
        ZwDisplayString( &bootMessageUnicodeString );*/

    }

	//
	// Register for shutdown notification
	//
	//IoRegisterShutdownNotification(g_GUIDevice);

	InitialArray(&g_ProtectRegisterNameHead);
	InitialArray(&g_ProtectProcessNameHead);

	return STATUS_SUCCESS;

}