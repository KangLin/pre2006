/*******************************************************************************************************
版权所有 (C) 2007 康林工作室；保留所有权利。
文件名：FileSystemNotification.c
描  述：当文件系统加载或卸载时的通知与处理函数
版  本：1.0
作  者：康  林
E_Mail：kl222@126.com
日  期：2007年4月30日
时  间：11:33:44
编译器：Microsoft Visual Studio 8.0 —— C/C++ 8.0
*******************************************************************************************************/
/*!
\warning 版权所有 (C) 2007 康林工作室；保留所有权利。
\file    FileSystemNotification.c
\brief   当文件系统加载或卸载时的通知与处理函数
\version 1.0
\author  康  林 (kl222@126.com)
\date    2007年5月17日  13:13:21
\par     编译器:
         Microsoft Visual Studio 8.0 —— C/C++ 8.0
*/

#include "sfilter.h"

NTSTATUS
SfAttachToFileSystemDevice (
    IN PDEVICE_OBJECT DeviceObject,
    IN PUNICODE_STRING DeviceName
    )
/*++

Routine Description:

    This will attach to the given file system device object.  We attach to
    these devices so we will know when new volumes are mounted.

Arguments:

    DeviceObject - The device to attach to

    Name - An already initialized unicode string used to retrieve names.
           This is passed in to reduce the number of strings buffers on
           the stack.

Return Value:

    Status of the operation

--*/
{
    PDEVICE_OBJECT newDeviceObject;
    PSFILTER_DEVICE_EXTENSION devExt;
    UNICODE_STRING fsrecName;
    NTSTATUS status;
    UNICODE_STRING fsName;
    WCHAR tempNameBuffer[MAX_DEVNAME_LENGTH];

    PAGED_CODE();

    //
    //  See if this is a file system type we care about.  If not, return.
    //

    if (!IS_DESIRED_DEVICE_TYPE(DeviceObject->DeviceType)) {

        return STATUS_SUCCESS;
    }

    //
    //  always init NAME buffer
    //

    RtlInitEmptyUnicodeString( &fsName,
                               tempNameBuffer,
                               sizeof(tempNameBuffer) );

    //
    //  See if we should attach to the standard file system recognizer device
    //  or not
    //

    if (!FlagOn(SfDebug,SFDEBUG_ATTACH_TO_FSRECOGNIZER)) {

        //
        //  See if this is one of the standard Microsoft file system recognizer
        //  devices (see if this device is in the FS_REC driver).  If so skip
        //  it.  We no longer attach to file system recognizer devices, we
        //  simply wait for the real file system driver to load.
        //

        RtlInitUnicodeString( &fsrecName, L"\\FileSystem\\Fs_Rec" );

        SfGetObjectName( DeviceObject->DriverObject, &fsName );

        if (RtlCompareUnicodeString( &fsName, &fsrecName, TRUE ) == 0) {

            return STATUS_SUCCESS;
        }
    }

    //
    //  We want to attach to this file system.  Create a new device object we
    //  can attach with.
    //

    status = IoCreateDevice( gSFilterDriverObject,
                             sizeof( SFILTER_DEVICE_EXTENSION ),
                             NULL,
                             DeviceObject->DeviceType,
                             0,
                             FALSE,
                             &newDeviceObject );

    if (!NT_SUCCESS( status )) {

        return status;
    }

    //
    //  Propagate flags from Device Object we are trying to attach to.
    //  Note that we do this before the actual attachment to make sure
    //  the flags are properly set once we are attached (since an IRP
    //  can come in immediately after attachment but before the flags would
    //  be set).
    //

    if ( FlagOn( DeviceObject->Flags, DO_BUFFERED_IO )) {

        SetFlag( newDeviceObject->Flags, DO_BUFFERED_IO );
    }

    if ( FlagOn( DeviceObject->Flags, DO_DIRECT_IO )) {

        SetFlag( newDeviceObject->Flags, DO_DIRECT_IO );
    }

    if ( FlagOn( DeviceObject->Characteristics, FILE_DEVICE_SECURE_OPEN ) ) {

        SetFlag( newDeviceObject->Characteristics, FILE_DEVICE_SECURE_OPEN );
    }

    //
    //  Do the attachment
    //

    devExt = newDeviceObject->DeviceExtension;

    status = SfAttachDeviceToDeviceStack( newDeviceObject, 
                                          DeviceObject, 
                                          &devExt->AttachedToDeviceObject );

    if (!NT_SUCCESS( status )) {

        goto ErrorCleanupDevice;
    }

    //
    //  Set the name
    //

    RtlInitEmptyUnicodeString( &devExt->DeviceName,
                               devExt->DeviceNameBuffer,
                               sizeof(devExt->DeviceNameBuffer) );

	RtlCopyUnicodeString(&devExt->DeviceName, DeviceName);        //Save Name

	// Link Symbol Name setted to NULL
	RtlInitEmptyUnicodeString(&devExt->DeviceLinkSymbolName,
		devExt->DeviceLinkSymbolNameBuffer,
		sizeof(devExt->DeviceLinkSymbolNameBuffer));

	//
    //  Mark we are done initializing
    //

    ClearFlag( newDeviceObject->Flags, DO_DEVICE_INITIALIZING );

    //
    //  Display who we have attached to
    //

    SF_LOG_PRINT( SFDEBUG_DISPLAY_ATTACHMENT_NAMES,
                  ("SFilter!SfAttachToFileSystemDevice:          Attaching to file system   %p \"%wZ\" (%s)\n",
                   DeviceObject,
                   &devExt->DeviceName,
                   GET_DEVICE_TYPE_NAME(newDeviceObject->DeviceType)) );

    //
    //  VERSION NOTE:
    //
    //  In Windows XP, the IO Manager provided APIs to safely enumerate all the
    //  device objects for a given driver.  This allows filters to attach to 
    //  all mounted volumes for a given file system at some time after the
    //  volume has been mounted.  There is no support for this functionality
    //  in Windows 2000.
    //
    //  MULTIVERSION NOTE:
    //
    //  If built for Windows XP or later, this driver is built to run on 
    //  multiple versions.  When this is the case, we will test
    //  for the presence of the new IO Manager routines that allow for volume 
    //  enumeration.  If they are not present, we will not enumerate the volumes
    //  when we attach to a new file system.
    //
    
#if WINVER >= 0x0501

    if (IS_WINDOWSXP_OR_LATER()) {

        ASSERT( NULL != gSfDynamicFunctions.EnumerateDeviceObjectList &&
                NULL != gSfDynamicFunctions.GetDiskDeviceObject &&
                NULL != gSfDynamicFunctions.GetDeviceAttachmentBaseRef &&
                NULL != gSfDynamicFunctions.GetLowerDeviceObject );

        //
        //  Enumerate all the mounted devices that currently
        //  exist for this file system and attach to them.
        //

        status = SfEnumerateFileSystemVolumes( DeviceObject, &fsName );

        if (!NT_SUCCESS( status )) {

            IoDetachDevice( devExt->AttachedToDeviceObject );
            goto ErrorCleanupDevice;
        }
    }
    
#endif

    return STATUS_SUCCESS;

    /////////////////////////////////////////////////////////////////////
    //                  Cleanup error handling
    /////////////////////////////////////////////////////////////////////

    ErrorCleanupDevice:
        SfCleanupMountedDevice( newDeviceObject );
        IoDeleteDevice( newDeviceObject );

    return status;
}

VOID
SfDetachFromFileSystemDevice (
    IN PDEVICE_OBJECT DeviceObject
    )
/*++

Routine Description:

    Given a base file system device object, this will scan up the attachment
    chain looking for our attached device object.  If found it will detach
    us from the chain.

Arguments:

    DeviceObject - The file system device to detach from.

Return Value:

--*/ 
{
    PDEVICE_OBJECT ourAttachedDevice;
    PSFILTER_DEVICE_EXTENSION devExt;

    PAGED_CODE();

    //
    //  Skip the base file system device object (since it can't be us)
    //

    ourAttachedDevice = DeviceObject->AttachedDevice;

    while (NULL != ourAttachedDevice) {

        if (IS_MY_DEVICE_OBJECT( ourAttachedDevice )) {

            devExt = ourAttachedDevice->DeviceExtension;

            //
            //  Display who we detached from
            //

            SF_LOG_PRINT( SFDEBUG_DISPLAY_ATTACHMENT_NAMES,
                          ("SFilter!SfDetachFromFileSystemDevice:        Detaching from file system %p \"%wZ\" (%s)\n",
                           devExt->AttachedToDeviceObject,
                           &devExt->DeviceName,
                           GET_DEVICE_TYPE_NAME(ourAttachedDevice->DeviceType)) );

            //
            //  Detach us from the object just below us
            //  Cleanup and delete the object
            //

            SfCleanupMountedDevice( ourAttachedDevice );
            IoDetachDevice( DeviceObject );
            IoDeleteDevice( ourAttachedDevice );

            return;
        }

        //
        //  Look at the next device up in the attachment chain
        //

        DeviceObject = ourAttachedDevice;
        ourAttachedDevice = ourAttachedDevice->AttachedDevice;
    }
}

VOID
SfFsNotification (
    IN PDEVICE_OBJECT DeviceObject,
    IN BOOLEAN FsActive
    )

/*++

Routine Description:

    This routine is invoked whenever a file system has either registered or
    unregistered itself as an active file system.

    For the former case, this routine creates a device object and attaches it
    to the specified file system's device object.  This allows this driver
    to filter all requests to that file system.  Specifically we are looking
    for MOUNT requests so we can attach to newly mounted volumes.

    For the latter case, this file system's device object is located,
    detached, and deleted.  This removes this file system as a filter for
    the specified file system.

Arguments:

    DeviceObject - Pointer to the file system's device object.

    FsActive - Boolean indicating whether the file system has registered
        (TRUE) or unregistered (FALSE) itself as an active file system.

Return Value:

    None.

--*/

{
    UNICODE_STRING name;
    WCHAR nameBuffer[MAX_DEVNAME_LENGTH];

    PAGED_CODE();

    //
    //  Init local name buffer
    //

    RtlInitEmptyUnicodeString( &name, nameBuffer, sizeof(nameBuffer) );

    SfGetObjectName( DeviceObject, &name );

    //
    //  Display the names of all the file system we are notified of
    //

    SF_LOG_PRINT( SFDEBUG_DISPLAY_ATTACHMENT_NAMES,
                  ("SFilter!SfFsNotification:                    %s   %p \"%wZ\" (%s)\n",
                   (FsActive) ? "Activating file system  " : "Deactivating file system",
                   DeviceObject,
                   &name,
                   GET_DEVICE_TYPE_NAME(DeviceObject->DeviceType)) );

    //
    //  Handle attaching/detaching from the given file system.
    //

    if (FsActive) {

        SfAttachToFileSystemDevice( DeviceObject, &name );

    } else {

        SfDetachFromFileSystemDevice( DeviceObject );
    }
}