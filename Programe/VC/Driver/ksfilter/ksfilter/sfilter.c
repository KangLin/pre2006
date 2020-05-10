/*++

Copyright (c) 1989-1993  Microsoft Corporation

Module Name:

    sfilter.c

Abstract:

    This module contains the code that implements the general purpose sample
    file system filter driver.

    As of the Windows XP SP1 IFS Kit version of this sample and later, this
    sample can be built for each build environment released with the IFS Kit
    with no additional modifications.  To provide this capability, additional
    compile-time logic was added -- see the '#if WINVER' locations.  Comments
    tagged with the 'VERSION NOTE' header have also been added as appropriate to
    describe how the logic must change between versions.

    If this sample is built in the Windows XP environment or later, it will run
    on Windows 2000 or later.  This is done by dynamically loading the routines
    that are only available on Windows XP or later and making run-time decisions
    to determine what code to execute.  Comments tagged with 'MULTIVERISON NOTE'
    mark the locations where such logic has been added.

Environment:

    Kernel mode

--*/

#include "sfilter.h"
#include "Support.h"

//
//  Enable these warnings in the code.
//

#pragma warning(error:4100)   // Unreferenced formal parameter
#pragma warning(error:4101)   // Unreferenced local variable


/////////////////////////////////////////////////////////////////////////////
//
//                      Global variables
//
/////////////////////////////////////////////////////////////////////////////

SF_DYNAMIC_FUNCTION_POINTERS gSfDynamicFunctions = {0};

//
//  MULTIVERSION NOTE: For this version of the driver, we need to know the
//  current OS version while we are running to make decisions regarding what
//  logic to use when the logic cannot be the same for all platforms.  We
//  will look up the OS version in DriverEntry and store the values
//  in these global variables.
//
//
//  Here is what the major and minor versions should be for the various OS versions:
//
//  OS Name                                 MajorVersion    MinorVersion
//  ---------------------------------------------------------------------
//  Windows 2000                             5                 0
//  Windows XP                               5                 1
//  Windows Server 2003                      5                 2
//

ULONG gSfOsMajorVersion = 0;
ULONG gSfOsMinorVersion = 0;

//
//  Holds pointer to the driver object for this driver
//

PDRIVER_OBJECT gSFilterDriverObject = NULL;

//
//  Holds pointer to the device object that represents this driver and is used
//  by external programs to access this driver.  This is also known as the
//  "control device object".
//

PDEVICE_OBJECT gSFilterControlDeviceObject = NULL;

//
//  This lock is used to synchronize our attaching to a given device object.
//  This lock fixes a race condition where we could accidently attach to the
//  same device object more then once.  This race condition only occurs if
//  a volume is being mounted at the same time as this filter is being loaded.
//  This problem will never occur if this filter is loaded at boot time before
//  any file systems are loaded.
//
//  This lock is used to atomically test if we are already attached to a given
//  device object and if not, do the attach.
//

FAST_MUTEX gSfilterAttachLock;

BOOLEAN gWriteProtectData;

/////////////////////////////////////////////////////////////////////////////
//
//                      Debug Definitions
//
/////////////////////////////////////////////////////////////////////////////

#ifdef DBG
ULONG SfDebug = SFDEBUG_DIRECTORYCONTROL;
#else
ULONG SfDebug = 0x0;
#endif

extern ARRAYHEAD gFileNameArrayHead;

/////////////////////////////////////////////////////////////////////////////
//
//  Assign text sections for each routine.
//
/////////////////////////////////////////////////////////////////////////////

#ifdef ALLOC_PRAGMA
#pragma alloc_text(INIT, DriverEntry)

#if DBG && WINVER >= 0x0501
#pragma alloc_text(PAGE, DriverUnload)
#endif

#pragma alloc_text(PAGE, SfFsNotification)
#pragma alloc_text(PAGE, SfCreate)
#pragma alloc_text(PAGE, SfRead)
#pragma alloc_text(PAGE, SfWrite)
#pragma alloc_text(PAGE, SfCleanupClose)
#pragma alloc_text(PAGE, SfFsControl)
#pragma alloc_text(PAGE, SfDeviceControl)
#pragma alloc_text(PAGE, SfDirectoryControl)
#pragma alloc_text(PAGE, SfFsControlMountVolume)
#pragma alloc_text(PAGE, SfFsControlMountVolumeComplete)
#pragma alloc_text(PAGE, SfFsControlLoadFileSystem)
#pragma alloc_text(PAGE, SfFsControlLoadFileSystemComplete)
#pragma alloc_text(PAGE, SfFastIoCheckIfPossible)
#pragma alloc_text(PAGE, SfFastIoRead)
#pragma alloc_text(PAGE, SfFastIoWrite)
#pragma alloc_text(PAGE, SfFastIoQueryBasicInfo)
#pragma alloc_text(PAGE, SfFastIoQueryStandardInfo)
#pragma alloc_text(PAGE, SfFastIoLock)
#pragma alloc_text(PAGE, SfFastIoUnlockSingle)
#pragma alloc_text(PAGE, SfFastIoUnlockAll)
#pragma alloc_text(PAGE, SfFastIoUnlockAllByKey)
#pragma alloc_text(PAGE, SfFastIoDeviceControl)
#pragma alloc_text(PAGE, SfFastIoDetachDevice)
#pragma alloc_text(PAGE, SfFastIoQueryNetworkOpenInfo)
#pragma alloc_text(PAGE, SfFastIoMdlRead)
#pragma alloc_text(PAGE, SfFastIoPrepareMdlWrite)
#pragma alloc_text(PAGE, SfFastIoMdlWriteComplete)
#pragma alloc_text(PAGE, SfFastIoReadCompressed)
#pragma alloc_text(PAGE, SfFastIoWriteCompressed)
#pragma alloc_text(PAGE, SfFastIoQueryOpen)
#pragma alloc_text(PAGE, SfAttachDeviceToDeviceStack)
#pragma alloc_text(PAGE, SfAttachToFileSystemDevice)
#pragma alloc_text(PAGE, SfDetachFromFileSystemDevice)
#pragma alloc_text(PAGE, SfAttachToMountedDevice)
#pragma alloc_text(PAGE, SfIsAttachedToDevice)
#pragma alloc_text(PAGE, SfIsAttachedToDeviceW2K)
#pragma alloc_text(INIT, SfReadDriverParameters)
#pragma alloc_text(PAGE, SfIsShadowCopyVolume)

#pragma alloc_text(PAGE, SfQueryFileInformation)
#pragma alloc_text(PAGE, SfQueryFileBasicInformation)
#pragma alloc_text(PAGE, SfSetInformation)
#pragma alloc_text(PAGE, GetFullPath)
#pragma alloc_text(PAGE, SfIsDisableDeleteFile)

#if WINVER >= 0x0501
#pragma alloc_text(INIT, SfLoadDynamicFunctions)
#pragma alloc_text(INIT, SfGetCurrentVersion)
#pragma alloc_text(PAGE, SfEnumerateFileSystemVolumes)
#pragma alloc_text(PAGE, SfIsAttachedToDeviceWXPAndLater)
#endif

#endif


/////////////////////////////////////////////////////////////////////////////
//
//                      Functions
//
/////////////////////////////////////////////////////////////////////////////

NTSTATUS
DriverEntry (
    IN PDRIVER_OBJECT DriverObject,
    IN PUNICODE_STRING RegistryPath
    )

/*++

Routine Description:

    This is the initialization routine for the SFILTER file system filter
    driver.  This routine creates the device object that represents this
    driver in the system and registers it for watching all file systems that
    register or unregister themselves as active file systems.

Arguments:

    DriverObject - Pointer to driver object created by the system.

Return Value:

    The function value is the final status from the initialization operation.

--*/

{
    PFAST_IO_DISPATCH fastIoDispatch;
	UNICODE_STRING nameString;
	UNICODE_STRING deviceLinkUnicodeString;
    NTSTATUS status;
    ULONG i;

	KdPrint(("sfilter: -->DriverEntry\n"));


#if WINVER >= 0x0501
    //
    //  Try to load the dynamic functions that may be available for our use.
    //

    SfLoadDynamicFunctions();

    //
    //  Now get the current OS version that we will use to determine what logic
    //  paths to take when this driver is built to run on various OS version.
    //

    SfGetCurrentVersion();
#endif

    //
    //  Get Registry values
    //

    SfReadDriverParameters( RegistryPath );

    //
    //  Save our Driver Object, set our UNLOAD routine
    //

    gSFilterDriverObject = DriverObject;

#if DBG && WINVER >= 0x0501

    //
    //  MULTIVERSION NOTE:
    //
    //  We can only support unload for testing environments if we can enumerate
    //  the outstanding device objects that our driver has.
    //
    
    //
    //  Unload is useful for development purposes. It is not recommended for
    //  production versions
    //

    if (NULL != gSfDynamicFunctions.EnumerateDeviceObjectList) {
        
        gSFilterDriverObject->DriverUnload = DriverUnload;
    }
#endif

    //
    //  Setup other global variables
    //

	ExInitializeFastMutex(&gSfilterAttachLock);

	// Write protect data
	gWriteProtectData = FALSE;

    //
    //  Create the Control Device Object (CDO).  This object represents this 
    //  driver.  Note that it does not have a device extension.
    //

	RtlInitUnicodeString(&nameString, L"\\FileSystem\\Filters\\KSFilter");

    status = IoCreateDevice( DriverObject,
                             0,                      //has no device extension
                             &nameString,
                             FILE_DEVICE_DISK_FILE_SYSTEM,
                             FILE_DEVICE_SECURE_OPEN,
                             FALSE,
                             &gSFilterControlDeviceObject );

    if (status == STATUS_OBJECT_PATH_NOT_FOUND) {

        //
        //  This must be a version of the OS that doesn't have the Filters
        //  path in its namespace.  This was added in Windows XP.
        //
        //  We will try just putting our control device object in the \FileSystem
        //  portion of the object name space.
        //

        RtlInitUnicodeString( &nameString, L"\\FileSystem\\KSFilterCDO" );

        status = IoCreateDevice( DriverObject,
                                 0,                      //has no device extension
                                 &nameString,
                                 FILE_DEVICE_DISK_FILE_SYSTEM,
                                 FILE_DEVICE_SECURE_OPEN,
                                 FALSE,
                                 &gSFilterControlDeviceObject );

        if (!NT_SUCCESS( status )) {
           
            KdPrint(( "SFilter!DriverEntry: Error creating control device object \"%wZ\", status=%08x\n", &nameString, status ));
            return status;
        }
        
    } else if (!NT_SUCCESS( status )) {

        KdPrint(( "SFilter!DriverEntry: Error creating control device object \"%wZ\", status=%08x\n", &nameString, status ));
        return status;
	}

	//
	// Create a symbolic link that the GUI can specify to gain access
	// to this driver/device
	//
	RtlInitUnicodeString (&deviceLinkUnicodeString,
		L"\\DosDevices\\KSFilter");
	status = IoCreateSymbolicLink (&deviceLinkUnicodeString,
		&nameString);
	if(!NT_SUCCESS(status)) {

		KdPrint (("KSFilter: IoCreateSymbolicLink failed\n"));
		IoDeleteDevice(gSFilterControlDeviceObject);
		return status;
	}
	//
    //  Initialize the driver object with this device driver's entry points.
    //

    for (i = 0; i <= IRP_MJ_MAXIMUM_FUNCTION; i++) {

        DriverObject->MajorFunction[i] = SfPassThrough;
    }

    //
    //  We will use SfCreate for all the create operations
    //

    DriverObject->MajorFunction[IRP_MJ_CREATE] = SfCreate;
	DriverObject->MajorFunction[IRP_MJ_CREATE_NAMED_PIPE] = SfCreate;
    DriverObject->MajorFunction[IRP_MJ_CREATE_MAILSLOT] = SfCreate;

	DriverObject->MajorFunction[IRP_MJ_READ] = SfRead;
	DriverObject->MajorFunction[IRP_MJ_WRITE] = SfWrite;
	DriverObject->MajorFunction[IRP_MJ_SET_INFORMATION] = SfSetInformation;

	DriverObject->MajorFunction[IRP_MJ_FILE_SYSTEM_CONTROL] = SfFsControl;

	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = SfDeviceControl;
	DriverObject->MajorFunction[IRP_MJ_DIRECTORY_CONTROL] = SfDirectoryControl;

	DriverObject->MajorFunction[IRP_MJ_CLEANUP] = SfCleanupClose;
    DriverObject->MajorFunction[IRP_MJ_CLOSE] = SfCleanupClose;

    //
    //  Allocate fast I/O data structure and fill it in.
    //
    //  NOTE:  The following FastIo Routines are not supported:
    //      AcquireFileForNtCreateSection
    //      ReleaseFileForNtCreateSection
    //      AcquireForModWrite
    //      ReleaseForModWrite
    //      AcquireForCcFlush
    //      ReleaseForCcFlush
    //
    //  For historical reasons these FastIO's have never been sent to filters
    //  by the NT I/O system.  Instead, they are sent directly to the base 
    //  file system.  On Windows XP and later OS releases, you can use the new 
    //  system routine "FsRtlRegisterFileSystemFilterCallbacks" if you need to 
    //  intercept these callbacks (see below).
    //

    fastIoDispatch = ExAllocatePoolWithTag( NonPagedPool, sizeof( FAST_IO_DISPATCH ), SFLT_POOL_TAG );
    if (!fastIoDispatch) {

        IoDeleteDevice( gSFilterControlDeviceObject );
        return STATUS_INSUFFICIENT_RESOURCES;
    }

    RtlZeroMemory( fastIoDispatch, sizeof( FAST_IO_DISPATCH ) );

    fastIoDispatch->SizeOfFastIoDispatch = sizeof( FAST_IO_DISPATCH );
    fastIoDispatch->FastIoCheckIfPossible = SfFastIoCheckIfPossible;
    fastIoDispatch->FastIoRead = SfFastIoRead;
    fastIoDispatch->FastIoWrite = SfFastIoWrite;
    fastIoDispatch->FastIoQueryBasicInfo = SfFastIoQueryBasicInfo;
    fastIoDispatch->FastIoQueryStandardInfo = SfFastIoQueryStandardInfo;
    fastIoDispatch->FastIoLock = SfFastIoLock;
    fastIoDispatch->FastIoUnlockSingle = SfFastIoUnlockSingle;
    fastIoDispatch->FastIoUnlockAll = SfFastIoUnlockAll;
    fastIoDispatch->FastIoUnlockAllByKey = SfFastIoUnlockAllByKey;
    fastIoDispatch->FastIoDeviceControl = SfFastIoDeviceControl;
    fastIoDispatch->FastIoDetachDevice = SfFastIoDetachDevice;
    fastIoDispatch->FastIoQueryNetworkOpenInfo = SfFastIoQueryNetworkOpenInfo;
    fastIoDispatch->MdlRead = SfFastIoMdlRead;
    fastIoDispatch->MdlReadComplete = SfFastIoMdlReadComplete;
    fastIoDispatch->PrepareMdlWrite = SfFastIoPrepareMdlWrite;
    fastIoDispatch->MdlWriteComplete = SfFastIoMdlWriteComplete;
    fastIoDispatch->FastIoReadCompressed = SfFastIoReadCompressed;
    fastIoDispatch->FastIoWriteCompressed = SfFastIoWriteCompressed;
    fastIoDispatch->MdlReadCompleteCompressed = SfFastIoMdlReadCompleteCompressed;
    fastIoDispatch->MdlWriteCompleteCompressed = SfFastIoMdlWriteCompleteCompressed;
    fastIoDispatch->FastIoQueryOpen = SfFastIoQueryOpen;

    DriverObject->FastIoDispatch = fastIoDispatch;

//
//  VERSION NOTE:
//
//  There are 6 FastIO routines for which file system filters are bypassed as
//  the requests are passed directly to the base file system.  These 6 routines
//  are AcquireFileForNtCreateSection, ReleaseFileForNtCreateSection,
//  AcquireForModWrite, ReleaseForModWrite, AcquireForCcFlush, and 
//  ReleaseForCcFlush.
//
//  In Windows XP and later, the FsFilter callbacks were introduced to allow
//  filters to safely hook these operations.  See the IFS Kit documentation for
//  more details on how these new interfaces work.
//
//  MULTIVERSION NOTE:
//  
//  If built for Windows XP or later, this driver is built to run on 
//  multiple versions.  When this is the case, we will test
//  for the presence of FsFilter callbacks registration API.  If we have it,
//  then we will register for those callbacks, otherwise, we will not.
//

#if WINVER >= 0x0501

    {
        FS_FILTER_CALLBACKS fsFilterCallbacks;

        if (NULL != gSfDynamicFunctions.RegisterFileSystemFilterCallbacks) {

            //
            //  Setup the callbacks for the operations we receive through
            //  the FsFilter interface.
            //
            //  NOTE:  You only need to register for those routines you really need
            //         to handle.  SFilter is registering for all routines simply to
            //         give an example of how it is done.
            //

            fsFilterCallbacks.SizeOfFsFilterCallbacks = sizeof( FS_FILTER_CALLBACKS );
            fsFilterCallbacks.PreAcquireForSectionSynchronization = SfPreFsFilterPassThrough;
            fsFilterCallbacks.PostAcquireForSectionSynchronization = SfPostFsFilterPassThrough;
            fsFilterCallbacks.PreReleaseForSectionSynchronization = SfPreFsFilterPassThrough;
            fsFilterCallbacks.PostReleaseForSectionSynchronization = SfPostFsFilterPassThrough;
            fsFilterCallbacks.PreAcquireForCcFlush = SfPreFsFilterPassThrough;
            fsFilterCallbacks.PostAcquireForCcFlush = SfPostFsFilterPassThrough;
            fsFilterCallbacks.PreReleaseForCcFlush = SfPreFsFilterPassThrough;
            fsFilterCallbacks.PostReleaseForCcFlush = SfPostFsFilterPassThrough;
            fsFilterCallbacks.PreAcquireForModifiedPageWriter = SfPreFsFilterPassThrough;
            fsFilterCallbacks.PostAcquireForModifiedPageWriter = SfPostFsFilterPassThrough;
            fsFilterCallbacks.PreReleaseForModifiedPageWriter = SfPreFsFilterPassThrough;
            fsFilterCallbacks.PostReleaseForModifiedPageWriter = SfPostFsFilterPassThrough;

            status = (gSfDynamicFunctions.RegisterFileSystemFilterCallbacks)( DriverObject, 
                                                                             &fsFilterCallbacks );

            if (!NT_SUCCESS( status )) {
                
                DriverObject->FastIoDispatch = NULL;
                ExFreePool( fastIoDispatch );
                IoDeleteDevice( gSFilterControlDeviceObject );
                return status;
            }
        }
    }
#endif

    //
    //  The registered callback routine "SfFsNotification" will be called
    //  whenever a new file systems is loaded or when any file system is
    //  unloaded.
    //
    //  VERSION NOTE:
    //
    //  On Windows XP and later this will also enumerate all existing file
    //  systems (except the RAW file systems).  On Windows 2000 this does not
    //  enumerate the file systems that were loaded before this filter was
    //  loaded.
    //

    status = IoRegisterFsRegistrationChange( DriverObject, SfFsNotification );
    if (!NT_SUCCESS( status )) {

        KdPrint(( "SFilter!DriverEntry: Error registering FS change notification, status=%08x\n", status ));

        DriverObject->FastIoDispatch = NULL;
        ExFreePool( fastIoDispatch );
        IoDeleteDevice( gSFilterControlDeviceObject );
        return status;
    }

    //
    //  Attempt to attach to the appropriate RAW file system device objects
    //  since they are not enumerated by IoRegisterFsRegistrationChange.
    //

    {
        PDEVICE_OBJECT rawDeviceObject;
        PFILE_OBJECT fileObject;

        //
        //  Attach to RawDisk device
        //

        RtlInitUnicodeString( &nameString, L"\\Device\\RawDisk" );

        status = IoGetDeviceObjectPointer(
                    &nameString,
                    FILE_READ_ATTRIBUTES,
                    &fileObject,
                    &rawDeviceObject );

        if (NT_SUCCESS( status )) {

            SfFsNotification( rawDeviceObject, TRUE );
            ObDereferenceObject( fileObject );
        }

        //
        //  Attach to the RawCdRom device
        //

        RtlInitUnicodeString( &nameString, L"\\Device\\RawCdRom" );

        status = IoGetDeviceObjectPointer(
                    &nameString,
                    FILE_READ_ATTRIBUTES,
                    &fileObject,
                    &rawDeviceObject );

        if (NT_SUCCESS( status )) {

            SfFsNotification( rawDeviceObject, TRUE );
            ObDereferenceObject( fileObject );
        }
    }

	// Initail the file name array
	InitialArray(&gFileNameArrayHead);

    //
    //  Clear the initializing flag on the control device object since we
    //  have now successfully initialized everything.
    //

    ClearFlag( gSFilterControlDeviceObject->Flags, DO_DEVICE_INITIALIZING );
	
	KdPrint(("sfilter: <--DriverEntry\n"));
    
    return STATUS_SUCCESS;
}

#if DBG && WINVER >= 0x0501
VOID
DriverUnload (
    IN PDRIVER_OBJECT DriverObject
    )

/*++

Routine Description:

    This routine is called when a driver can be unloaded.  This performs all of
    the necessary cleanup for unloading the driver from memory.  Note that an
    error can NOT be returned from this routine.
    
    When a request is made to unload a driver the IO System will cache that
    information and not actually call this routine until the following states
    have occurred:
    - All device objects which belong to this filter are at the top of their
      respective attachment chains.
    - All handle counts for all device objects which belong to this filter have
      gone to zero.

    WARNING: Microsoft does not officially support the unloading of File
             System Filter Drivers.  This is an example of how to unload
             your driver if you would like to use it during development.
             This should not be made available in production code.

Arguments:

    DriverObject - Driver object for this module

Return Value:

    None.

--*/

{
    PSFILTER_DEVICE_EXTENSION devExt;
    PFAST_IO_DISPATCH fastIoDispatch;
    NTSTATUS status;
    ULONG numDevices;
    ULONG i;
    LARGE_INTEGER interval;
#   define DEVOBJ_LIST_SIZE 64
	PDEVICE_OBJECT devList[DEVOBJ_LIST_SIZE];
	UNICODE_STRING deviceLinkUnicodeString;

	KdPrint(("sfilter: -->DriverUnload\n"));
    
    ASSERT(DriverObject == gSFilterDriverObject);

    //
    //  Log we are unloading
    //

    SF_LOG_PRINT( SFDEBUG_DISPLAY_ATTACHMENT_NAMES,
                  ("SFilter!DriverUnload:                        Unloading driver (%p)\n",
                   DriverObject) );

	// Delete the device/driver symbolic link
	RtlInitUnicodeString(&deviceLinkUnicodeString,
		L"\\DosDevices\\KSFilter");
	IoDeleteSymbolicLink(&deviceLinkUnicodeString);

    //
    //  Don't get anymore file system change notifications
    //

    IoUnregisterFsRegistrationChange( DriverObject, SfFsNotification );

    //
    //  This is the loop that will go through all of the devices we are attached
    //  to and detach from them.  Since we don't know how many there are and
    //  we don't want to allocate memory (because we can't return an error)
    //  we will free them in chunks using a local array on the stack.
    //

    for (;;) {

        //
        //  Get what device objects we can for this driver.  Quit if there
        //  are not any more.  Note that this routine should always be
        //  defined since this routine is only compiled for Windows XP and
        //  later.
        //

        ASSERT( NULL != gSfDynamicFunctions.EnumerateDeviceObjectList );
        status = (gSfDynamicFunctions.EnumerateDeviceObjectList)(
                        DriverObject,
                        devList,
                        sizeof(devList),
                        &numDevices);

        if (numDevices <= 0)  {

            break;
        }

        numDevices = min( numDevices, DEVOBJ_LIST_SIZE );

        //
        //  First go through the list and detach each of the devices.
        //  Our control device object does not have a DeviceExtension and
        //  is not attached to anything so don't detach it.
        //

        for (i=0; i < numDevices; i++) {

            devExt = devList[i]->DeviceExtension;
            if (NULL != devExt) {

                IoDetachDevice( devExt->AttachedToDeviceObject );
            }
        }

        //
        //  The IO Manager does not currently add a reference count to a device
        //  object for each outstanding IRP.  This means there is no way to
        //  know if there are any outstanding IRPs on the given device.
        //  We are going to wait for a reasonable amount of time for pending
        //  irps to complete.  
        //
        //  WARNING: This does not work 100% of the time and the driver may be
        //           unloaded before all IRPs are completed.  This can easily
        //           occur under stress situations and if a long lived IRP is
        //           pending (like oplocks and directory change notifications).
        //           The system will fault when this Irp actually completes.
        //           This is a sample of how to do this during testing.  This
        //           is not recommended for production code.
        //

        interval.QuadPart = (5 * DELAY_ONE_SECOND);      //delay 5 seconds
        KeDelayExecutionThread( KernelMode, FALSE, &interval );

        //
        //  Now go back through the list and delete the device objects.
        //

        for (i=0; i < numDevices; i++) {

            //
            //  See if this is our control device object.  If not then cleanup
            //  the device extension.  If so then clear the global pointer
            //  that references it.
            //

            if (NULL != devList[i]->DeviceExtension) {

                SfCleanupMountedDevice( devList[i] );

            } else {

                ASSERT(devList[i] == gSFilterControlDeviceObject);
                gSFilterControlDeviceObject = NULL;
            }

            //
            //  Delete the device object, remove reference counts added by
            //  IoEnumerateDeviceObjectList.  Note that the delete does
            //  not actually occur until the reference count goes to zero.
            //

            IoDeleteDevice( devList[i] );
            ObDereferenceObject( devList[i] );
        }
    }

    //
    //  Free our FastIO table
    //

    fastIoDispatch = DriverObject->FastIoDispatch;
    DriverObject->FastIoDispatch = NULL;
	ExFreePool(fastIoDispatch);

	// Clear the file name array
	ClearArray(&gFileNameArrayHead, ClearCallBack);

    KdPrint(("sfilter: <--DriverUnload\n"));
}
#endif

/////////////////////////////////////////////////////////////////////////////
//
//                  IRP Handling Routines
//
/////////////////////////////////////////////////////////////////////////////


NTSTATUS
SfPassThrough (
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    )

/*++

Routine Description:

    This routine is the main dispatch routine for the general purpose file
    system driver.  It simply passes requests onto the next driver in the
    stack, which is presumably a disk file system.

Arguments:

    DeviceObject - Pointer to the device object for this driver.

    Irp - Pointer to the request packet representing the I/O request.

Return Value:

    The function value is the status of the operation.

Note:

    A note to file system filter implementers:  
        This routine actually "passes" through the request by taking this
        driver out of the IRP stack.  If the driver would like to pass the
        I/O request through, but then also see the result, then rather than
        taking itself out of the loop it could keep itself in by copying the
        caller's parameters to the next stack location and then set its own
        completion routine.  

        Hence, instead of calling:
    
            IoSkipCurrentIrpStackLocation( Irp );

        You could instead call:

            IoCopyCurrentIrpStackLocationToNext( Irp );
            IoSetCompletionRoutine( Irp, NULL, NULL, FALSE, FALSE, FALSE );


        This example actually NULLs out the caller's I/O completion routine, but
        this driver could set its own completion routine so that it would be
        notified when the request was completed (see SfCreate for an example of
        this).

--*/

{
    //
    //  Sfilter doesn't allow handles to its control device object to be created,
    //  therefore, no other operation should be able to come through.
    //
      
    ASSERT(!IS_MY_CONTROL_DEVICE_OBJECT( DeviceObject ));

    ASSERT(IS_MY_DEVICE_OBJECT( DeviceObject ));

    //
    //  Get this driver out of the driver stack and get to the next driver as
    //  quickly as possible.
    //

    IoSkipCurrentIrpStackLocation( Irp );
    
    //
    //  Call the appropriate file system driver with the request.
    //
   
    return IoCallDriver( ((PSFILTER_DEVICE_EXTENSION) DeviceObject->DeviceExtension)->AttachedToDeviceObject, Irp );
}


NTSTATUS
SfFsControl (
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    )

/*++

Routine Description:

    This routine is invoked whenever an I/O Request Packet (IRP) w/a major
    function code of IRP_MJ_FILE_SYSTEM_CONTROL is encountered.  For most
    IRPs of this type, the packet is simply passed through.  However, for
    some requests, special processing is required.

Arguments:

    DeviceObject - Pointer to the device object for this driver.

    Irp - Pointer to the request packet representing the I/O request.

Return Value:

    The function value is the status of the operation.

--*/

{
    PIO_STACK_LOCATION irpSp = IoGetCurrentIrpStackLocation( Irp );

    PAGED_CODE();

    //
    //  Sfilter doesn't allow handles to its control device object to be created,
    //  therefore, no other operation should be able to come through.
    //
    
    ASSERT(!IS_MY_CONTROL_DEVICE_OBJECT( DeviceObject ));

    ASSERT(IS_MY_DEVICE_OBJECT( DeviceObject ));

    //
    //  Process the minor function code.
    //

    switch (irpSp->MinorFunction) {

        case IRP_MN_MOUNT_VOLUME:

            return SfFsControlMountVolume( DeviceObject, Irp );

        case IRP_MN_LOAD_FILE_SYSTEM:

            return SfFsControlLoadFileSystem( DeviceObject, Irp );

        case IRP_MN_USER_FS_REQUEST:
        {
            switch (irpSp->Parameters.FileSystemControl.FsControlCode) {

                case FSCTL_DISMOUNT_VOLUME:
                {
                    PSFILTER_DEVICE_EXTENSION devExt = DeviceObject->DeviceExtension;

                    SF_LOG_PRINT( SFDEBUG_DISPLAY_ATTACHMENT_NAMES,
                                  ("SFilter!SfFsControl:                         Dismounting volume         %p \"%wZ\"\n",
                                   devExt->AttachedToDeviceObject,
                                   &devExt->DeviceName) );
                    break;
                }
            }
            break;
        }
    }        

    //
    //  Pass all other file system control requests through.
    //

    IoSkipCurrentIrpStackLocation( Irp );
    return IoCallDriver( ((PSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension)->AttachedToDeviceObject, Irp );
}

/*******************************************************************************************************
函数名：SfDeviceControl
描  述：设备控制派遣例程,完成主功能码为 IRP_MJ_DEVICE_CONTROL 的I/O请求
参  数：
        IN PDEVICE_OBJECT DeviceObject：设备对象
		IN PIRP Irp                   ：
返回值：类型为 NTSTATUS 。
版  本：1.0
作  者：康  林
时  间：2007年5月8日 15:31:43
*******************************************************************************************************/
NTSTATUS
SfDeviceControl(
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
	)
{
	PIO_STACK_LOCATION irpSp = IoGetCurrentIrpStackLocation( Irp );
	PCHAR pInBuf = NULL;
	PCHAR pOutBuf = NULL;
	INT * pInPos = NULL;
	int nInLen = 0;
	int nOutLen = 0;
	NTSTATUS status = STATUS_SUCCESS;

    PAGED_CODE();

	pInBuf = Irp->AssociatedIrp.SystemBuffer;
	pOutBuf = Irp->AssociatedIrp.SystemBuffer;
	nInLen = irpSp->Parameters.DeviceIoControl.InputBufferLength;
	nOutLen = irpSp->Parameters.DeviceIoControl.OutputBufferLength;

    //
    //  Process the minor function code.
	//
	if(IS_MY_CONTROL_DEVICE_OBJECT(DeviceObject))
	{
		// 增加:控制功能代码
		switch(irpSp->Parameters.DeviceIoControl.IoControlCode)
		{
		case FSCTL_SET_PROTECT_FILE:
			if(0 == nInLen)
			{
				status = STATUS_INVALID_PARAMETER;
				break;
			}

			if(InsertElement(&gFileNameArrayHead, pInBuf, nInLen))
			{
				status = STATUS_UNSUCCESSFUL; 
			}

			break;
		case FSCTL_REMOVE_PROTECT_FILE:
			if(0 == nInLen)
			{
				status = STATUS_INVALID_PARAMETER;
				break;
			}

			if(RemoveElement(&gFileNameArrayHead, pInBuf, nInLen))
			{
				status = STATUS_UNSUCCESSFUL;
			}
		
			break;
		case FSCTL_GET_POSITION_FILE:
			if(0 == nInLen)
			{
				status = STATUS_INVALID_PARAMETER;
				break;
			}// 结束 if(0 == nInLen)

			pInPos = Irp->AssociatedIrp.SystemBuffer;

			status = GetElement(&gFileNameArrayHead, *pInPos, pOutBuf, &nOutLen);
			Irp->IoStatus.Information = nOutLen;

			break;
		default:
			status = STATUS_INVALID_DEVICE_REQUEST;
			break;
		}// 结束 switch(irpSp->Parameters.DeviceIoControl.IoControlCode)

		Irp->IoStatus.Status = status;

		//
		//  We have completed all processing for this IRP, so tell the 
		//  I/O Manager.  This IRP will not be passed any further down
		//  the stack since no drivers below FileSpy care about this 
		//  I/O operation that was directed to FileSpy.
		//

		IoCompleteRequest(Irp, IO_NO_INCREMENT);
		return status;
	}// 结束 if(IS_MY_CONTROL_DEVICE_OBJECT(DeviceObject))

	//
	//  Other passthrough
	//

	//
	//  Get this driver out of the driver stack and get to the next driver as
	//  quickly as possible.
	//

	IoSkipCurrentIrpStackLocation( Irp );

	//
	//  Call the appropriate file system driver with the request.
	//

	return IoCallDriver( ((PSFILTER_DEVICE_EXTENSION) DeviceObject->DeviceExtension)->AttachedToDeviceObject, Irp );
}

VOID
SfFsControlMountVolumeCompleteWorker (
    IN PFSCTRL_COMPLETION_CONTEXT Context
    )
/*++

Routine Description:

    The worker thread routine that will call our common routine to do the
    post-MountVolume work.

Arguments:

    Context - The context passed to this worker thread.
    
Return Value:

    None.

--*/
{
    ASSERT( Context != NULL );

    SfFsControlMountVolumeComplete( Context->DeviceObject,
                                    Context->Irp,
                                    Context->NewDeviceObject );

    ExFreePoolWithTag( Context, SFLT_POOL_TAG );
}


NTSTATUS
SfFsControlLoadFileSystem (
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    )

/*++

Routine Description:

    This routine is invoked whenever an I/O Request Packet (IRP) w/a major
    function code of IRP_MJ_FILE_SYSTEM_CONTROL is encountered.  For most
    IRPs of this type, the packet is simply passed through.  However, for
    some requests, special processing is required.

Arguments:

    DeviceObject - Pointer to the device object for this driver.

    Irp - Pointer to the request packet representing the I/O request.

Return Value:

    The function value is the status of the operation.

--*/

{
    PSFILTER_DEVICE_EXTENSION devExt = DeviceObject->DeviceExtension;
    NTSTATUS status;
    PFSCTRL_COMPLETION_CONTEXT completionContext;
        

    PAGED_CODE();

    //
    //  This is a "load file system" request being sent to a file system
    //  recognizer device object.  This IRP_MN code is only sent to 
    //  file system recognizers.
    //
    //  NOTE:  Since we no longer are attaching to the standard Microsoft file
    //         system recognizers we will normally never execute this code.
    //         However, there might be 3rd party file systems which have their
    //         own recognizer which may still trigger this IRP.
    //

    SF_LOG_PRINT( SFDEBUG_DISPLAY_ATTACHMENT_NAMES,
                  ("SFilter!SfFscontrolLoadFileSystem:           Loading File System, Detaching from \"%wZ\"\n", 
                   &devExt->DeviceName) );


    //
    //  VERSION NOTE:
    //
    //  On Windows 2000, we cannot simply synchronize back to the dispatch
    //  routine to do our post-load filesystem processing.  We need to do 
    //  this work at passive level, so we will queue that work to a worker 
    //  thread from the completion routine.
    //
    //  For Windows XP and later, we can safely synchronize back to the dispatch
    //  routine.  The code below shows both methods.  Admittedly, the code
    //  would be simplified if you chose to only use one method or the other, 
    //  but you should be able to easily adapt this for your needs.
    //

#if WINVER >= 0x0501
    if (IS_WINDOWSXP_OR_LATER()) {

        KEVENT waitEvent;
        
        KeInitializeEvent( &waitEvent, 
                           NotificationEvent, 
                           FALSE );

        IoCopyCurrentIrpStackLocationToNext( Irp );
        
        IoSetCompletionRoutine( Irp,
                                SfFsControlCompletion,
                                &waitEvent,     //context parameter
                                TRUE,
                                TRUE,
                                TRUE );

        status = IoCallDriver( devExt->AttachedToDeviceObject, Irp );

        //
        //  Wait for the operation to complete
        //

    	if (STATUS_PENDING == status) {

    		status = KeWaitForSingleObject( &waitEvent,
    		                                Executive,
    		                                KernelMode,
    		                                FALSE,
    		                                NULL );
    	    ASSERT( STATUS_SUCCESS == status );
    	}

        //
        //  Verify the IoCompleteRequest was called
        //

        ASSERT(KeReadStateEvent(&waitEvent) ||
               !NT_SUCCESS(Irp->IoStatus.Status));

        status = SfFsControlLoadFileSystemComplete( DeviceObject,
                                                    Irp );

    } else {
#endif    
    
        //
        //  Set a completion routine so we can delete the device object when
        //  the load is complete.
        //

        completionContext = ExAllocatePoolWithTag( NonPagedPool, 
                                                   sizeof( FSCTRL_COMPLETION_CONTEXT ),
                                                   SFLT_POOL_TAG );

        if (completionContext == NULL) {

            //
            //  If we cannot allocate our completion context, we will just pass 
            //  through the operation.  If your filter must be present for data
            //  access to this volume, you should consider failing the operation
            //  if memory cannot be allocated here.
            //

            IoSkipCurrentIrpStackLocation( Irp );
            status = IoCallDriver( devExt->AttachedToDeviceObject, Irp );

        } else {

            ExInitializeWorkItem( &completionContext->WorkItem,
                                  SfFsControlLoadFileSystemCompleteWorker,
                                  completionContext );
            completionContext->DeviceObject = DeviceObject;
            completionContext->Irp = Irp;
            completionContext->NewDeviceObject = NULL;
              
            IoCopyCurrentIrpStackLocationToNext( Irp );

            IoSetCompletionRoutine(
                Irp,
                SfFsControlCompletion,
                completionContext,
                TRUE,
                TRUE,
                TRUE );

            //
            //  Detach from the file system recognizer device object.
            //

            IoDetachDevice( devExt->AttachedToDeviceObject );

            //
            //  Call the driver
            //

            status = IoCallDriver( devExt->AttachedToDeviceObject, Irp );
        }
#if WINVER >= 0x0501        
    }
#endif   
    
    return status;
}

VOID
SfFsControlLoadFileSystemCompleteWorker (
    IN PFSCTRL_COMPLETION_CONTEXT Context
    )
/*++

Routine Description:

    The worker thread routine that will call our common routine to do the
    post-LoadFileSystem work.

Arguments:

    Context - The context passed to this worker thread.
    
Return Value:

    None.

--*/
{
    ASSERT( NULL != Context );

    SfFsControlLoadFileSystemComplete( Context->DeviceObject,
                                       Context->Irp );

    ExFreePoolWithTag( Context, SFLT_POOL_TAG );
}

NTSTATUS
SfFsControlLoadFileSystemComplete (
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    )
/*++

Routine Description:

    This does the post-LoadFileSystem work and must be done as PASSIVE_LEVEL.

Arguments:

    DeviceObject - The device object for this operation,

    Irp - The IRP for this operation that we will complete once we are finished
        with it.
    
Return Value:

    Returns the status of the load file system operation.

--*/
{
    PSFILTER_DEVICE_EXTENSION devExt;
    NTSTATUS status;

    PAGED_CODE();

    devExt = DeviceObject->DeviceExtension;
    
    //
    //  Display the name if requested
    //

    SF_LOG_PRINT( SFDEBUG_DISPLAY_ATTACHMENT_NAMES,
                  ("SFilter!SfFsControlLoadFileSystem:           Detaching from recognizer  %p \"%wZ\", status=%08x\n", 
                   DeviceObject,
                   &devExt->DeviceName,
                   Irp->IoStatus.Status) );

    //
    //  Check status of the operation
    //

    if (!NT_SUCCESS( Irp->IoStatus.Status ) && 
        (Irp->IoStatus.Status != STATUS_IMAGE_ALREADY_LOADED)) {

        //
        //  The load was not successful.  Simply reattach to the recognizer
        //  driver in case it ever figures out how to get the driver loaded
        //  on a subsequent call.  There is not a lot we can do if this
        //  reattach fails.
        //

        SfAttachDeviceToDeviceStack( DeviceObject, 
                                     devExt->AttachedToDeviceObject,
                                     &devExt->AttachedToDeviceObject );

        ASSERT(devExt->AttachedToDeviceObject != NULL);

    } else {

        //
        //  The load was successful, so cleanup this device and delete the 
        //  Device object
        //

        SfCleanupMountedDevice( DeviceObject );
        IoDeleteDevice( DeviceObject );
    }

    //
    //  Continue processing the operation
    //

    status = Irp->IoStatus.Status;

    IoCompleteRequest( Irp, IO_NO_INCREMENT );

    return status;
}

#if WINVER >= 0x0501 /* See comment in DriverEntry */
/////////////////////////////////////////////////////////////////////////////
//
//                  FSFilter callback handling routines
//
/////////////////////////////////////////////////////////////////////////////

NTSTATUS
SfPreFsFilterPassThrough(
    IN PFS_FILTER_CALLBACK_DATA Data,
    OUT PVOID *CompletionContext
    )
/*++

Routine Description:

    This routine is the FS Filter pre-operation "pass through" routine.

Arguments:

    Data - The FS_FILTER_CALLBACK_DATA structure containing the information
        about this operation.
        
    CompletionContext - A context set by this operation that will be passed
        to the corresponding SfPostFsFilterOperation call.
        
Return Value:

    Returns STATUS_SUCCESS if the operation can continue or an appropriate
    error code if the operation should fail.

--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( CompletionContext );

    ASSERT( IS_MY_DEVICE_OBJECT( Data->DeviceObject ) );

    return STATUS_SUCCESS;
}

VOID
SfPostFsFilterPassThrough (
    IN PFS_FILTER_CALLBACK_DATA Data,
    IN NTSTATUS OperationStatus,
    IN PVOID CompletionContext
    )
/*++

Routine Description:

    This routine is the FS Filter post-operation "pass through" routine.

Arguments:

    Data - The FS_FILTER_CALLBACK_DATA structure containing the information
        about this operation.
        
    OperationStatus - The status of this operation.        
    
    CompletionContext - A context that was set in the pre-operation 
        callback by this driver.
        
Return Value:

    None.
    
--*/
{
    UNREFERENCED_PARAMETER( Data );
    UNREFERENCED_PARAMETER( OperationStatus );
    UNREFERENCED_PARAMETER( CompletionContext );

    ASSERT( IS_MY_DEVICE_OBJECT( Data->DeviceObject ) );
}
#endif

/////////////////////////////////////////////////////////////////////////////
//
//                  Support routines
//
/////////////////////////////////////////////////////////////////////////////



#if WINVER >= 0x0501
NTSTATUS
SfEnumerateFileSystemVolumes (
    IN PDEVICE_OBJECT FSDeviceObject,
    IN PUNICODE_STRING Name
    ) 
/*++

Routine Description:

    Enumerate all the mounted devices that currently exist for the given file
    system and attach to them.  We do this because this filter could be loaded
    at any time and there might already be mounted volumes for this file system.

Arguments:

    FSDeviceObject - The device object for the file system we want to enumerate

    Name - An already initialized unicode string used to retrieve names
           This is passed in to reduce the number of strings buffers on
           the stack.

Return Value:

    The status of the operation

--*/
{
    PDEVICE_OBJECT newDeviceObject;
    PSFILTER_DEVICE_EXTENSION newDevExt;
    PDEVICE_OBJECT *devList;
    PDEVICE_OBJECT storageStackDeviceObject;
    NTSTATUS status;
    ULONG numDevices;
    ULONG i;
	BOOLEAN isShadowCopyVolume;
	UNICODE_STRING dosName;

    PAGED_CODE();

    //
    //  Find out how big of an array we need to allocate for the
    //  mounted device list.
    //

    status = (gSfDynamicFunctions.EnumerateDeviceObjectList)(
                    FSDeviceObject->DriverObject,
                    NULL,
                    0,
                    &numDevices);

    //
    //  We only need to get this list of there are devices.  If we
    //  don't get an error there are no devices so go on.
    //

    if (!NT_SUCCESS( status )) {

        ASSERT(STATUS_BUFFER_TOO_SMALL == status);

        //
        //  Allocate memory for the list of known devices
        //

        numDevices += 8;        //grab a few extra slots

        devList = ExAllocatePoolWithTag( NonPagedPool, 
                                         (numDevices * sizeof(PDEVICE_OBJECT)), 
                                         SFLT_POOL_TAG );
        if (NULL == devList) {

            return STATUS_INSUFFICIENT_RESOURCES;
        }

        //
        //  Now get the list of devices.  If we get an error again
        //  something is wrong, so just fail.
        //

        ASSERT( NULL != gSfDynamicFunctions.EnumerateDeviceObjectList );
        status = (gSfDynamicFunctions.EnumerateDeviceObjectList)(
                        FSDeviceObject->DriverObject,
                        devList,
                        (numDevices * sizeof(PDEVICE_OBJECT)),
                        &numDevices);

        if (!NT_SUCCESS( status ))  {

            ExFreePool( devList );
            return status;
        }

        //
        //  Walk the given list of devices and attach to them if we should.
        //

        for (i=0; i < numDevices; i++) {

            //
            //  Initialize state so we can cleanup properly
            //

            storageStackDeviceObject = NULL;

            try {

                //
                //  Do not attach if:
                //      - This is the control device object (the one passed in)
                //      - The device type does not match
                //      - We are already attached to it.
                //

                if ((devList[i] == FSDeviceObject) ||
                    (devList[i]->DeviceType != FSDeviceObject->DeviceType) ||
                    SfIsAttachedToDevice( devList[i], NULL )) {

                    leave;
                }

                //
                //  See if this device has a name.  If so, then it must
                //  be a control device so don't attach to it.  This handles
                //  drivers with more then one control device (like FastFat).
                //

                SfGetBaseDeviceObjectName( devList[i], Name );

                if (Name->Length > 0) {

                    leave;
                }

                //
                //  Get the real (disk,storage stack) device object associated
                //  with this file system device object.  Only try to attach
                //  if we have a disk device object.
                //

                ASSERT( NULL != gSfDynamicFunctions.GetDiskDeviceObject );
                status = (gSfDynamicFunctions.GetDiskDeviceObject)( devList[i], 
                                                                   &storageStackDeviceObject );

                if (!NT_SUCCESS( status )) {

                    leave;
                }

                //
                //  Determine if this is a shadow copy volume.  If so don't
                //  attach to it.
                //  NOTE:  There is no reason sfilter shouldn't attach to these
                //         volumes, this is simply a sample of how to not
                //         attach if you don't want to
                //

                status = SfIsShadowCopyVolume ( storageStackDeviceObject, 
                                                &isShadowCopyVolume );

                if (NT_SUCCESS(status) &&
                    isShadowCopyVolume &&
                    !FlagOn(SfDebug,SFDEBUG_ATTACH_TO_SHADOW_COPIES)) {

                    UNICODE_STRING shadowDeviceName;
                    WCHAR shadowNameBuffer[MAX_DEVNAME_LENGTH];

                    //
                    //  Get the name for the debug display
                    //

                    RtlInitEmptyUnicodeString( &shadowDeviceName, 
                                               shadowNameBuffer, 
                                               sizeof(shadowNameBuffer) );

                    SfGetObjectName( storageStackDeviceObject, 
                                     &shadowDeviceName );

                    SF_LOG_PRINT( SFDEBUG_DISPLAY_ATTACHMENT_NAMES,
                                  ("SFilter!SfEnumerateFileSystemVolumes         Not attaching to Volume    %p \"%wZ\", shadow copy volume\n", 
                                   storageStackDeviceObject,
                                   &shadowDeviceName) );

                    leave;
                }

                //
                //  Allocate a new device object to attach with
                //

                status = IoCreateDevice( gSFilterDriverObject,
                                         sizeof( SFILTER_DEVICE_EXTENSION ),
                                         NULL,
                                         devList[i]->DeviceType,
                                         0,
                                         FALSE,
                                         &newDeviceObject );

                if (!NT_SUCCESS( status )) {

                    leave;
                }

                //
                //  Set disk device object
                //

                newDevExt = newDeviceObject->DeviceExtension;
                newDevExt->StorageStackDeviceObject = storageStackDeviceObject;
        
                //
                //  Set storage stack device name
                //

                RtlInitEmptyUnicodeString( &newDevExt->DeviceName,
                                           newDevExt->DeviceNameBuffer,
                                           sizeof(newDevExt->DeviceNameBuffer) );

                SfGetObjectName( storageStackDeviceObject, 
                                 &newDevExt->DeviceName );

				// Get the Link symbol name of the volume device.(dosName)
				// - Initial Unicode string
				RtlInitEmptyUnicodeString(&newDevExt->DeviceLinkSymbolName,
					newDevExt->DeviceLinkSymbolNameBuffer,
					sizeof(newDevExt->DeviceLinkSymbolNameBuffer));
				// - Get dosName
				status = VolumeDeviceToDosName(storageStackDeviceObject, &dosName);
				if(NT_SUCCESS(status))
				{
					RtlCopyUnicodeString(&newDevExt->DeviceLinkSymbolName, &dosName);
					// free buffer
					ExFreePool(dosName.Buffer);
				}// 结束 (newDevExt->DeviceLinkSymbolNameBuffer)

                //
                //  We have done a lot of work since the last time
                //  we tested to see if we were already attached
                //  to this device object.  Test again, this time
                //  with a lock, and attach if we are not attached.
                //  The lock is used to atomically test if we are
                //  attached, and then do the attach.
                //

                ExAcquireFastMutex( &gSfilterAttachLock );

                if (!SfIsAttachedToDevice( devList[i], NULL )) {

                    //
                    //  Attach to volume.
                    //

                    status = SfAttachToMountedDevice( devList[i], 
                                                      newDeviceObject );
                    
                    if (!NT_SUCCESS( status )) { 

                        //
                        //  The attachment failed, cleanup.  Note that
                        //  we continue processing so we will cleanup
                        //  the reference counts and try to attach to
                        //  the rest of the volumes.
                        //
                        //  One of the reasons this could have failed
                        //  is because this volume is just being
                        //  mounted as we are attaching and the
                        //  DO_DEVICE_INITIALIZING flag has not yet
                        //  been cleared.  A filter could handle
                        //  this situation by pausing for a short
                        //  period of time and retrying the attachment a
                        //  limited number of times.
                        //

                        SfCleanupMountedDevice( newDeviceObject );
                        IoDeleteDevice( newDeviceObject );
                    }

                } else {

                    //
                    //  We were already attached, cleanup this
                    //  device object.
                    //

                    SfCleanupMountedDevice( newDeviceObject );
                    IoDeleteDevice( newDeviceObject );
                }

                //
                //  Release the lock
                //

                ExReleaseFastMutex( &gSfilterAttachLock );

            } finally {

                //
                //  Remove reference added by IoGetDiskDeviceObject.
                //  We only need to hold this reference until we are
                //  successfully attached to the current volume.  Once
                //  we are successfully attached to devList[i], the
                //  IO Manager will make sure that the underlying
                //  storageStackDeviceObject will not go away until
                //  the file system stack is torn down.
                //

                if (storageStackDeviceObject != NULL) {

                    ObDereferenceObject( storageStackDeviceObject );
                }

                //
                //  Dereference the object (reference added by 
                //  IoEnumerateDeviceObjectList)
                //

                ObDereferenceObject( devList[i] );
            }
        }

        //
        //  We are going to ignore any errors received while attaching.  We
        //  simply won't be attached to those volumes if we get an error
        //

        status = STATUS_SUCCESS;

        //
        //  Free the memory we allocated for the list
        //

        ExFreePool( devList );
    }

    return status;
}
#endif

VOID
SfCleanupMountedDevice (
    IN PDEVICE_OBJECT DeviceObject
    )
/*++

Routine Description:

    This cleans up any necessary data in the device extension to prepare for
    this memory to be freed.

Arguments:

    DeviceObject - The device we are cleaning up

Return Value:

    None

--*/
{        

    UNREFERENCED_PARAMETER( DeviceObject );
    ASSERT(IS_MY_DEVICE_OBJECT( DeviceObject ));
}


VOID
SfGetObjectName (
    IN PVOID Object,
    IN OUT PUNICODE_STRING Name
    )
/*++

Routine Description:

    This routine will return the name of the given object.
    If a name can not be found an empty string will be returned.

Arguments:

    Object - The object whose name we want

    Name - A unicode string that is already initialized with a buffer that
           receives the name of the object.

Return Value:

    None

--*/
{
    NTSTATUS status;
    CHAR nibuf[512];        //buffer that receives NAME information and name
    POBJECT_NAME_INFORMATION nameInfo = (POBJECT_NAME_INFORMATION)nibuf;
    ULONG retLength;

    status = ObQueryNameString( Object, nameInfo, sizeof(nibuf), &retLength);

    Name->Length = 0;
    if (NT_SUCCESS( status )) {

        RtlCopyUnicodeString( Name, &nameInfo->Name );
    }
}

//
//  VERSION NOTE:
//
//  This helper routine is only needed when enumerating all volumes in the
//  system, which is only supported on Windows XP and later.
//

#if WINVER >= 0x0501
VOID
SfGetBaseDeviceObjectName (
    IN PDEVICE_OBJECT DeviceObject,
    IN OUT PUNICODE_STRING Name
    )
/*++

Routine Description:

    This locates the base device object in the given attachment chain and then
    returns the name of that object.

    If no name can be found, an empty string is returned.

Arguments:

    Object - The object whose name we want

    Name - A unicode string that is already initialized with a buffer that
           receives the name of the device object.

Return Value:

    None

--*/
{
    //
    //  Get the base file system device object
    //

    ASSERT( NULL != gSfDynamicFunctions.GetDeviceAttachmentBaseRef );
    DeviceObject = (gSfDynamicFunctions.GetDeviceAttachmentBaseRef)( DeviceObject );

    //
    //  Get the name of that object
    //

    SfGetObjectName( DeviceObject, Name );

    //
    //  Remove the reference added by IoGetDeviceAttachmentBaseRef
    //

    ObDereferenceObject( DeviceObject );
}
#endif

//
//  VERSION NOTE:
//  
//  In Windows 2000, the APIs to safely walk an arbitrary file system device 
//  stack were not supported.  If we can guarantee that a device stack won't 
//  be torn down during the walking of the device stack, we can walk from
//  the base file system's device object up to the top of the device stack
//  to see if we are attached.  We know the device stack will not go away if
//  we are in the process of processing a mount request OR we have a file object
//  open on this device.
//  
//  In Windows XP and later, the IO Manager provides APIs that will allow us to
//  walk through the chain safely using reference counts to protect the device 
//  object from going away while we are inspecting it.  This can be done at any
//  time.
//
//  MULTIVERSION NOTE:
//
//  If built for Windows XP or later, this driver is built to run on 
//  multiple versions.  When this is the case, we will test for the presence of
//  the new IO Manager routines that allow for a filter to safely walk the file
//  system device stack and use those APIs if they are present to determine if
//  we have already attached to this volume.  If these new IO Manager routines
//  are not present, we will assume that we are at the bottom of the file
//  system stack and walk up the stack looking for our device object.
//

BOOLEAN
SfIsAttachedToDevice (
    PDEVICE_OBJECT DeviceObject,
    PDEVICE_OBJECT *AttachedDeviceObject OPTIONAL
    )
{

    PAGED_CODE();

#if WINVER >= 0x0501
    if (IS_WINDOWSXP_OR_LATER()) {

        ASSERT( NULL != gSfDynamicFunctions.GetLowerDeviceObject &&
                NULL != gSfDynamicFunctions.GetDeviceAttachmentBaseRef );
        
        return SfIsAttachedToDeviceWXPAndLater( DeviceObject, AttachedDeviceObject );
    } else {
#endif

        return SfIsAttachedToDeviceW2K( DeviceObject, AttachedDeviceObject );

#if WINVER >= 0x0501
    }
#endif    
}

BOOLEAN
SfIsAttachedToDeviceW2K (
    PDEVICE_OBJECT DeviceObject,
    PDEVICE_OBJECT *AttachedDeviceObject OPTIONAL
    )
/*++

Routine Description:

    VERSION: Windows 2000

    This routine walks up the device stack from the DeviceObject passed in
    looking for a device object that belongs to our filter.

    Note:  If AttachedDeviceObject is returned with a non-NULL value,
           there is a reference on the AttachedDeviceObject that must
           be cleared by the caller.

Arguments:

    DeviceObject - The device chain we want to look through

    AttachedDeviceObject - Set to the deviceObject which FileSpy
            has previously attached to DeviceObject.

Return Value:

    TRUE if we are attached, FALSE if not

--*/
{
    PDEVICE_OBJECT currentDevice;

    PAGED_CODE();

    for (currentDevice = DeviceObject;
         currentDevice != NULL;
         currentDevice = currentDevice->AttachedDevice) {

        if (IS_MY_DEVICE_OBJECT( currentDevice )) {

            //
            //  We are attached.  If requested, return the found device object.
            //

            if (ARGUMENT_PRESENT(AttachedDeviceObject)) {

                ObReferenceObject( currentDevice );
                *AttachedDeviceObject = currentDevice;
            }

            return TRUE;
        }
    }

    //
    //  We did not find ourselves on the attachment chain.  Return a NULL
    //  device object pointer (if requested) and return we did not find
    //  ourselves.
    //
    
    if (ARGUMENT_PRESENT(AttachedDeviceObject)) {

        *AttachedDeviceObject = NULL;
    }

    return FALSE;
}

#if WINVER >= 0x0501
BOOLEAN
SfIsAttachedToDeviceWXPAndLater (
    PDEVICE_OBJECT DeviceObject,
    PDEVICE_OBJECT *AttachedDeviceObject OPTIONAL
    )
/*++

Routine Description:

    VERSION: Windows XP and later

    This walks down the attachment chain looking for a device object that
    belongs to this driver.  If one is found, the attached device object
    is returned in AttachedDeviceObject.

Arguments:

    DeviceObject - The device chain we want to look through

    AttachedDeviceObject - The Sfilter device attached to this device.

Return Value:

    TRUE if we are attached, FALSE if not

--*/
{
    PDEVICE_OBJECT currentDevObj;
    PDEVICE_OBJECT nextDevObj;

    PAGED_CODE();
    
    //
    //  Get the device object at the TOP of the attachment chain
    //

    ASSERT( NULL != gSfDynamicFunctions.GetAttachedDeviceReference );
    currentDevObj = (gSfDynamicFunctions.GetAttachedDeviceReference)( DeviceObject );

    //
    //  Scan down the list to find our device object.
    //

    do {
    
        if (IS_MY_DEVICE_OBJECT( currentDevObj )) {

            //
            //  We have found that we are already attached.  If we are
            //  returning the device object, leave it referenced else remove
            //  the reference.
            //

            if (ARGUMENT_PRESENT(AttachedDeviceObject)) {

                *AttachedDeviceObject = currentDevObj;

            } else {

                ObDereferenceObject( currentDevObj );
            }

            return TRUE;
        }

        //
        //  Get the next attached object.  This puts a reference on 
        //  the device object.
        //

        ASSERT( NULL != gSfDynamicFunctions.GetLowerDeviceObject );
        nextDevObj = (gSfDynamicFunctions.GetLowerDeviceObject)( currentDevObj );

        //
        //  Dereference our current device object, before
        //  moving to the next one.
        //

        ObDereferenceObject( currentDevObj );

        currentDevObj = nextDevObj;
        
    } while (NULL != currentDevObj);
    
    //
    //  We did not find ourselves on the attachment chain.  Return a NULL
    //  device object pointer (if requested) and return we did not find
    //  ourselves.
    //

    if (ARGUMENT_PRESENT(AttachedDeviceObject)) {

        *AttachedDeviceObject = NULL;
    }

    return FALSE;
}    
#endif