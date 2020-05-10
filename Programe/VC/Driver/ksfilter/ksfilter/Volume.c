/*******************************************************************************************************
版权所有 (C) 2007 康林工作室；保留所有权利。
文件名：Volume.c
描  述：卷的加载/卸载处理
版  本：1.0
作  者：康  林
E_Mail：kl222@126.com
日  期：2007年4月30日
时  间：15:35:17
编译器：Microsoft Visual Studio 8.0 —— C/C++ 8.0
*******************************************************************************************************/

#include "sfilter.h"

NTSTATUS
SfIsShadowCopyVolume (
    IN PDEVICE_OBJECT StorageStackDeviceObject,
    OUT PBOOLEAN IsShadowCopy
    )
/*++

Routine Description:

    This routine will determine if the given volume is for a ShadowCopy volume
    or some other type of volume.

    VERSION NOTE:

    ShadowCopy volumes were introduced in Windows XP, therefore, if this
    driver is running on W2K, we know that this is not a shadow copy volume.

    Also note that in Windows XP, we need to test to see if the driver name
    of this device object is \Driver\VolSnap in addition to seeing if this
    device is read-only.  For Windows Server 2003, we can infer that
    this is a ShadowCopy by looking for a DeviceType == FILE_DEVICE_VIRTUAL_DISK
    and read-only volume.
    
Arguments:

    StorageStackDeviceObject - pointer to the disk device object
    IsShadowCopy - returns TRUE if this is a shadow copy, FALSE otherwise
        
Return Value:

    The status of the operation.  If this operation fails IsShadowCopy is
    always set to FALSE.

--*/
{

    PAGED_CODE();

    //
    //  Default to NOT a shadow copy volume
    //

    *IsShadowCopy = FALSE;

#if WINVER >= 0x0501
    if (IS_WINDOWS2000()) {
#endif        

        UNREFERENCED_PARAMETER( StorageStackDeviceObject );
        return STATUS_SUCCESS;

#if WINVER >= 0x0501        
    }

    if (IS_WINDOWSXP()) {

        UNICODE_STRING volSnapDriverName;
        WCHAR buffer[MAX_DEVNAME_LENGTH];
        PUNICODE_STRING storageDriverName;
        ULONG returnedLength;
        NTSTATUS status;

        //
        //  In Windows XP, all ShadowCopy devices were of type FILE_DISK_DEVICE.
        //  If this does not have a device type of FILE_DISK_DEVICE, then
        //  it is not a ShadowCopy volume.  Return now.
        //

        if (FILE_DEVICE_DISK != StorageStackDeviceObject->DeviceType) {

            return STATUS_SUCCESS;
        }

        //
        //  Unfortunately, looking for the FILE_DEVICE_DISK isn't enough.  We
        //  need to find out if the name of this driver is \Driver\VolSnap as
        //  well.
        //

        storageDriverName = (PUNICODE_STRING) buffer;
        RtlInitEmptyUnicodeString( storageDriverName, 
                                   Add2Ptr( storageDriverName, sizeof( UNICODE_STRING ) ),
                                   sizeof( buffer ) - sizeof( UNICODE_STRING ) );

        status = ObQueryNameString( StorageStackDeviceObject,
                                    (POBJECT_NAME_INFORMATION)storageDriverName,
                                    storageDriverName->MaximumLength,
                                    &returnedLength );

        if (!NT_SUCCESS( status )) {

            return status;
        }

        RtlInitUnicodeString( &volSnapDriverName, L"\\Driver\\VolSnap" );

        if (RtlEqualUnicodeString( storageDriverName, &volSnapDriverName, TRUE )) {

            //
            // This is a ShadowCopy volume, so set our return parameter to true.
            //

            *IsShadowCopy = TRUE;

        } else {

            //
            //  This is not a ShadowCopy volume, but IsShadowCopy is already 
            //  set to FALSE.  Fall through to return to the caller.
            //

            NOTHING;
        }

        return STATUS_SUCCESS;
        
    } else {

        PIRP irp;
        KEVENT event;
        IO_STATUS_BLOCK iosb;
        NTSTATUS status;

        //
        //  For Windows Server 2003 and later, it is sufficient to test for a
        //  device type fo FILE_DEVICE_VIRTUAL_DISK and that the device
        //  is read-only to identify a ShadowCopy.
        //

        //
        //  If this does not have a device type of FILE_DEVICE_VIRTUAL_DISK, then
        //  it is not a ShadowCopy volume.  Return now.
        //

        if (FILE_DEVICE_VIRTUAL_DISK != StorageStackDeviceObject->DeviceType) {

            return STATUS_SUCCESS;
        }

        //
        //  It has the correct device type, see if it is marked as read only.
        //
        //  NOTE:  You need to be careful which device types you do this operation
        //         on.  It is accurate for this type but for other device
        //         types it may return misleading information.  For example the
        //         current microsoft cdrom driver always returns CD media as
        //         readonly, even if the media may be writable.  On other types
        //         this state may change.
        //

        KeInitializeEvent( &event, NotificationEvent, FALSE );

        irp = IoBuildDeviceIoControlRequest( IOCTL_DISK_IS_WRITABLE,
                                             StorageStackDeviceObject,
                                             NULL,
                                             0,
                                             NULL,
                                             0,
                                             FALSE,
                                             &event,
                                             &iosb );

        //
        //  If we could not allocate an IRP, return an error
        //

        if (irp == NULL) {

            return STATUS_INSUFFICIENT_RESOURCES;
        }

        //
        //  Call the storage stack and see if this is readonly
        //

        status = IoCallDriver( StorageStackDeviceObject, irp );

        if (status == STATUS_PENDING) {

            (VOID)KeWaitForSingleObject( &event,
                                         Executive,
                                         KernelMode,
                                         FALSE,
                                         NULL );

            status = iosb.Status;
        }

        //
        //  If the media is write protected then this is a shadow copy volume
        //

        if (STATUS_MEDIA_WRITE_PROTECTED == status) {

            *IsShadowCopy = TRUE;
            status = STATUS_SUCCESS;
        }

        //
        //  Return the status of the IOCTL.  IsShadowCopy is already set to FALSE
        //  which is what we want if STATUS_SUCCESS was returned or if an error
        //  was returned.
        //

        return status;
    }
#endif    
}

NTSTATUS
SfAttachToMountedDevice (
    IN PDEVICE_OBJECT DeviceObject,
    IN PDEVICE_OBJECT SFilterDeviceObject
    )
/*++

Routine Description:

    This will attach to a DeviceObject that represents a mounted volume.

Arguments:

    DeviceObject - The device to attach to

    SFilterDeviceObject - Our device object we are going to attach

Return Value:

    Status of the operation

--*/
{        
    PSFILTER_DEVICE_EXTENSION newDevExt = SFilterDeviceObject->DeviceExtension;
    NTSTATUS status;
    ULONG i;

    PAGED_CODE();
    ASSERT(IS_MY_DEVICE_OBJECT( SFilterDeviceObject ));
#if WINVER >= 0x0501    
    ASSERT(!SfIsAttachedToDevice ( DeviceObject, NULL ));
#endif

    //
    //  Propagate flags from Device Object we are trying to attach to.
    //  Note that we do this before the actual attachment to make sure
    //  the flags are properly set once we are attached (since an IRP
    //  can come in immediately after attachment but before the flags would
    //  be set).
    //

    if (FlagOn( DeviceObject->Flags, DO_BUFFERED_IO )) {

        SetFlag( SFilterDeviceObject->Flags, DO_BUFFERED_IO );
    }

    if (FlagOn( DeviceObject->Flags, DO_DIRECT_IO )) {

        SetFlag( SFilterDeviceObject->Flags, DO_DIRECT_IO );
    }

    //
    //  It is possible for this attachment request to fail because this device
    //  object has not finished initializing.  This can occur if this filter
    //  loaded just as this volume was being mounted.
    //

    for (i=0; i < 8; i++) {
        LARGE_INTEGER interval;

        //
        //  Attach our device object to the given device object
        //  The only reason this can fail is if someone is trying to dismount
        //  this volume while we are attaching to it.
        //

        status = SfAttachDeviceToDeviceStack( SFilterDeviceObject, 
                                              DeviceObject,
                                              &newDevExt->AttachedToDeviceObject );
        if (NT_SUCCESS(status)) {

            //
            //  Finished all initialization of the new device object,  so clear the
            //  initializing flag now.  This allows other filters to now attach
            //  to our device object.
            //

            ClearFlag( SFilterDeviceObject->Flags, DO_DEVICE_INITIALIZING );

            //
            //  Display the name
            //

            SF_LOG_PRINT( SFDEBUG_DISPLAY_ATTACHMENT_NAMES,
                          ("SFilter!SfAttachToMountedDevice:             Attaching to volume        %p \"%wZ\"\n", 
                           newDevExt->AttachedToDeviceObject,
                           &newDevExt->DeviceName) );

            return STATUS_SUCCESS;
        }

        //
        //  Delay, giving the device object a chance to finish its
        //  initialization so we can try again
        //

        interval.QuadPart = (500 * DELAY_ONE_MILLISECOND);      //delay 1/2 second
        KeDelayExecutionThread( KernelMode, FALSE, &interval );
    }

    return status;
}

NTSTATUS
SfFsControlMountVolumeComplete (
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp,
    IN PDEVICE_OBJECT NewDeviceObject
    )
/*++

Routine Description:

    This does the post-Mount work and must be done at PASSIVE_LEVEL.

Arguments:

    DeviceObject - The device object for this operation,

    Irp - The IRP for this operation that we will complete once we are finished
        with it.
    
Return Value:

    Returns the status of the mount operation.

--*/
{
    PVPB vpb;
    PSFILTER_DEVICE_EXTENSION newDevExt;
    PIO_STACK_LOCATION irpSp;
    PDEVICE_OBJECT attachedDeviceObject;
    NTSTATUS status;

    PAGED_CODE();

    newDevExt = NewDeviceObject->DeviceExtension;
    irpSp = IoGetCurrentIrpStackLocation( Irp );
    
    //
    //  Get the correct VPB from the real device object saved in our
    //  device extension.  We do this because the VPB in the IRP stack
    //  may not be the correct VPB when we get here.  The underlying
    //  file system may change VPBs if it detects a volume it has
    //  mounted previously.
    //

    vpb = newDevExt->StorageStackDeviceObject->Vpb;

    //
    //  Display a message when we detect that the VPB for the given
    //  device object has changed.
    //

    if (vpb != irpSp->Parameters.MountVolume.Vpb) {

        SF_LOG_PRINT( SFDEBUG_DISPLAY_ATTACHMENT_NAMES,
                      ("SFilter!SfFsControlMountVolume:              VPB in IRP stack changed   %p IRPVPB=%p VPB=%p\n",
                       vpb->DeviceObject,
                       irpSp->Parameters.MountVolume.Vpb,
                       vpb) );
    }

    //
    //  See if the mount was successful.
    //

    if (NT_SUCCESS( Irp->IoStatus.Status )) {

        //
        //  Acquire lock so we can atomically test if we area already attached
        //  and if not, then attach.  This prevents a double attach race
        //  condition.
        //

        ExAcquireFastMutex( &gSfilterAttachLock );

        //
        //  The mount succeeded.  If we are not already attached, attach to the
        //  device object.  Note: one reason we could already be attached is
        //  if the underlying file system revived a previous mount.
        //

        if (!SfIsAttachedToDevice( vpb->DeviceObject, &attachedDeviceObject )) {

            //
            //  Attach to the new mounted volume.  The file system device
            //  object that was just mounted is pointed to by the VPB.
            //

            status = SfAttachToMountedDevice( vpb->DeviceObject,
                                              NewDeviceObject );

            if (!NT_SUCCESS( status )) { 

                //
                //  The attachment failed, cleanup.  Since we are in the
                //  post-mount phase, we can not fail this operation.
                //  We simply won't be attached.  The only reason this should
                //  ever happen at this point is if somebody already started
                //  dismounting the volume therefore not attaching should
                //  not be a problem.
                //

                SfCleanupMountedDevice( NewDeviceObject );
                IoDeleteDevice( NewDeviceObject );
            }

            ASSERT( NULL == attachedDeviceObject );

        } else {

            //
            //  We were already attached, handle it
            //

            SF_LOG_PRINT( SFDEBUG_DISPLAY_ATTACHMENT_NAMES,
                          ("SFilter!SfFsControlMountVolume               Mount volume failure for   %p \"%wZ\", already attached\n", 
                           ((PSFILTER_DEVICE_EXTENSION)attachedDeviceObject->DeviceExtension)->AttachedToDeviceObject,
                           &newDevExt->DeviceName) );

            //
            //  Cleanup and delete the device object we created
            //

            SfCleanupMountedDevice( NewDeviceObject );
            IoDeleteDevice( NewDeviceObject );

            //
            //  Dereference the returned attached device object
            //

            ObDereferenceObject( attachedDeviceObject );
        }

        //
        //  Release the lock
        //

        ExReleaseFastMutex( &gSfilterAttachLock );

    } else {

        //
        //  The mount request failed, handle it.
        //

        SF_LOG_PRINT( SFDEBUG_DISPLAY_ATTACHMENT_NAMES,
                      ("SFilter!SfFsControlMountVolume:              Mount volume failure for   %p \"%wZ\", status=%08x\n", 
                       DeviceObject,
                       &newDevExt->DeviceName, 
                       Irp->IoStatus.Status) );

        //
        //  Cleanup and delete the device object we created
        //

        SfCleanupMountedDevice( NewDeviceObject );
        IoDeleteDevice( NewDeviceObject );
    }

    //
    //  Complete the request.  
    //  NOTE:  We must save the status before completing because after
    //         completing the IRP we can not longer access it (it might be
    //         freed).
    //

    status = Irp->IoStatus.Status;

    IoCompleteRequest( Irp, IO_NO_INCREMENT );

    return status;
}

NTSTATUS
SfFsControlMountVolume (
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    )

/*++

Routine Description:

    This processes a MOUNT VOLUME request.

    NOTE:  The device object in the MountVolume parameters points
           to the top of the storage stack and should not be used.

Arguments:

    DeviceObject - Pointer to the device object for this driver.

    Irp - Pointer to the request packet representing the I/O request.

Return Value:

    The status of the operation.

--*/

{
    PSFILTER_DEVICE_EXTENSION devExt = DeviceObject->DeviceExtension;
    PIO_STACK_LOCATION irpSp = IoGetCurrentIrpStackLocation( Irp );
    PDEVICE_OBJECT newDeviceObject;
    PDEVICE_OBJECT storageStackDeviceObject;
    PSFILTER_DEVICE_EXTENSION newDevExt;
    NTSTATUS status;
    BOOLEAN isShadowCopyVolume;
	PFSCTRL_COMPLETION_CONTEXT completionContext;
	UNICODE_STRING dosName;


    PAGED_CODE();

    ASSERT(IS_MY_DEVICE_OBJECT( DeviceObject ));
    ASSERT(IS_DESIRED_DEVICE_TYPE(DeviceObject->DeviceType));

    //
    //  Get the real device object (also known as the storage stack device
    //  object or the disk device object) pointed to by the vpb parameter
    //  because this vpb may be changed by the underlying file system.
    //  Both FAT and CDFS may change the VPB address if the volume being
    //  mounted is one they recognize from a previous mount.
    //

    storageStackDeviceObject = irpSp->Parameters.MountVolume.Vpb->RealDevice;

    //
    //  Determine if this is a shadow copy volume.  If so don't attach to it.
    //  NOTE:  There is no reason sfilter shouldn't attach to these volumes,
    //         this is simply a sample of how to not attach if you don't want
    //         to
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
                      ("SFilter!SfFsControlMountVolume               Not attaching to Volume    %p \"%wZ\", shadow copy volume\n", 
                       storageStackDeviceObject,
                       &shadowDeviceName) );

        //
        //  Go to the next driver
        //

        IoSkipCurrentIrpStackLocation( Irp );
        return IoCallDriver( devExt->AttachedToDeviceObject, Irp );
    }

    //
    //  This is a mount request.  Create a device object that can be
    //  attached to the file system's volume device object if this request
    //  is successful.  We allocate this memory now since we can not return
    //  an error in the completion routine.  
    //
    //  Since the device object we are going to attach to has not yet been
    //  created (it is created by the base file system) we are going to use
    //  the type of the file system control device object.  We are assuming
    //  that the file system control device object will have the same type
    //  as the volume device objects associated with it.
    //

    status = IoCreateDevice( gSFilterDriverObject,
                             sizeof( SFILTER_DEVICE_EXTENSION ),
                             NULL,
                             DeviceObject->DeviceType,
                             0,
                             FALSE,
                             &newDeviceObject );

    if (!NT_SUCCESS( status )) {

        //
        //  If we can not attach to the volume, then don't allow the volume
        //  to be mounted.
        //

        KdPrint(( "SFilter!SfFsControlMountVolume: Error creating volume device object, status=%08x\n", status ));

        Irp->IoStatus.Information = 0;
        Irp->IoStatus.Status = status;
        IoCompleteRequest( Irp, IO_NO_INCREMENT );

        return status;
    }

    //
    //  We need to save the RealDevice object pointed to by the vpb
    //  parameter because this vpb may be changed by the underlying
    //  file system.  Both FAT and CDFS may change the VPB address if
    //  the volume being mounted is one they recognize from a previous
    //  mount.
    //

    newDevExt = newDeviceObject->DeviceExtension;
    newDevExt->StorageStackDeviceObject = storageStackDeviceObject;

    //
    //  Get the name of this device
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
    //  VERSION NOTE:
    //
    //  On Windows 2000, we cannot simply synchronize back to the dispatch
    //  routine to do our post-mount processing.  We need to do this work at
    //  passive level, so we will queue that work to a worker thread from
    //  the completion routine.
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

        IoCopyCurrentIrpStackLocationToNext ( Irp );

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

        status = SfFsControlMountVolumeComplete( DeviceObject,
                                                 Irp,
                                                 newDeviceObject );

    } else {
#endif    
        //
        //  Initialize our completion routine
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
                                  SfFsControlMountVolumeCompleteWorker, 
                                  completionContext );

            completionContext->DeviceObject = DeviceObject;
            completionContext->Irp = Irp;
            completionContext->NewDeviceObject = newDeviceObject;

            IoCopyCurrentIrpStackLocationToNext( Irp );

            IoSetCompletionRoutine( Irp,
                                    SfFsControlCompletion,
                                    &completionContext->WorkItem, //context parameter
                                    TRUE,
                                    TRUE,
                                    TRUE );

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
