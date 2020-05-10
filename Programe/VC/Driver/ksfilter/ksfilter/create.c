/*******************************************************************************************************
版权所有 (C) 2007 康林工作室；保留所有权利。
文件名：create.c
描  述：建立/关闭例程的处理
版  本：1.0
作  者：康  林
E_Mail：kl222@126.com
日  期：2007年4月29日
时  间：13:40:38
编译器：Microsoft Visual Studio 8.0 —— C/C++ 8.0
*******************************************************************************************************/

#include "sfilter.h"
#include "Support.h"

PUNICODE_STRING
SfGetFileName(
    IN PFILE_OBJECT FileObject,
    IN NTSTATUS CreateStatus,
    IN OUT PGET_NAME_CONTROL NameControl
    )
/*++

Routine Description:

    This routine will try and get the name of the given file object.  This
    is guaranteed to always return a printable string (though it may be NULL).
    This will allocate a buffer if it needs to.

Arguments:
    FileObject - the file object we want the name for

    CreateStatus - status of the create operation

    NameControl - control structure used for retrieving the name.  It keeps
        track if a buffer was allocated or if we are using the internal
        buffer.

Return Value:

    Pointer to the unicode string with the name

--*/
{
    POBJECT_NAME_INFORMATION nameInfo;
    NTSTATUS status;
    ULONG size;
    ULONG bufferSize;

    //
    //  Mark we have not allocated the buffer
    //

    NameControl->allocatedBuffer = NULL;

    //
    //  Use the small buffer in the structure (that will handle most cases)
    //  for the name
    //

    nameInfo = (POBJECT_NAME_INFORMATION)NameControl->smallBuffer;
    bufferSize = sizeof(NameControl->smallBuffer);

    //
    //  If the open succeeded, get the name of the file, if it
    //  failed, get the name of the device.
    //
        
    status = ObQueryNameString(
                  (NT_SUCCESS( CreateStatus ) ?
                    (PVOID)FileObject :
                    (PVOID)FileObject->DeviceObject),
                  nameInfo,
                  bufferSize,
                  &size );

    //
    //  See if the buffer was to small
    //

    if (status == STATUS_BUFFER_OVERFLOW) {

        //
        //  The buffer was too small, allocate one big enough
        //

        bufferSize = size + sizeof(WCHAR);

        NameControl->allocatedBuffer = ExAllocatePoolWithTag( 
                                            NonPagedPool,
                                            bufferSize,
                                            SFLT_POOL_TAG );

        if (NULL == NameControl->allocatedBuffer) {

            //
            //  Failed allocating a buffer, return an empty string for the name
            //

            RtlInitEmptyUnicodeString(
                (PUNICODE_STRING)&NameControl->smallBuffer,
                (PWCHAR)(NameControl->smallBuffer + sizeof(UNICODE_STRING)),
                (USHORT)(sizeof(NameControl->smallBuffer) - sizeof(UNICODE_STRING)) );

            return (PUNICODE_STRING)&NameControl->smallBuffer;
        }

        //
        //  Set the allocated buffer and get the name again
        //

        nameInfo = (POBJECT_NAME_INFORMATION)NameControl->allocatedBuffer;

        status = ObQueryNameString(
                      FileObject,
                      nameInfo,
                      bufferSize,
                      &size );
    }

    //
    //  If we got a name and an error opening the file then we
    //  just received the device name.  Grab the rest of the name
    //  from the FileObject (note that this can only be done if being called
    //  from Create).  This only happens if we got an error back from the
    //  create.
    //

    if (NT_SUCCESS( status ) && 
                    !NT_SUCCESS( CreateStatus )) {

        ULONG newSize;
        PCHAR newBuffer;
        POBJECT_NAME_INFORMATION newNameInfo;

        //
        //  Calculate the size of the buffer we will need to hold
        //  the combined names
        //

        newSize = size + FileObject->FileName.Length;

        //
        //  If there is a related file object add in the length
        //  of that plus space for a separator
        //

        if (NULL != FileObject->RelatedFileObject) {

            newSize += FileObject->RelatedFileObject->FileName.Length + 
                       sizeof(WCHAR);
        }

        //
        //  See if it will fit in the existing buffer
        //

        if (newSize > bufferSize) {

            //
            //  It does not fit, allocate a bigger buffer
            //

            newBuffer = ExAllocatePoolWithTag( 
                                    NonPagedPool,
                                    newSize,
                                    SFLT_POOL_TAG );

            if (NULL == newBuffer) {

                //
                //  Failed allocating a buffer, return an empty string for the name
                //

                RtlInitEmptyUnicodeString(
                    (PUNICODE_STRING)&NameControl->smallBuffer,
                    (PWCHAR)(NameControl->smallBuffer + sizeof(UNICODE_STRING)),
                    (USHORT)(sizeof(NameControl->smallBuffer) - sizeof(UNICODE_STRING)) );

                return (PUNICODE_STRING)&NameControl->smallBuffer;
            }

            //
            //  Now initialize the new buffer with the information
            //  from the old buffer.
            //

            newNameInfo = (POBJECT_NAME_INFORMATION)newBuffer;

            RtlInitEmptyUnicodeString(
                &newNameInfo->Name,
                (PWCHAR)(newBuffer + sizeof(OBJECT_NAME_INFORMATION)),
                (USHORT)(newSize - sizeof(OBJECT_NAME_INFORMATION)) );

            RtlCopyUnicodeString( &newNameInfo->Name, 
                                  &nameInfo->Name );

            //
            //  Free the old allocated buffer (if there is one)
            //  and save off the new allocated buffer address.  It
            //  would be very rare that we should have to free the
            //  old buffer because device names should always fit
            //  inside it.
            //

            if (NULL != NameControl->allocatedBuffer) {

                ExFreePool( NameControl->allocatedBuffer );
            }

            //
            //  Readjust our pointers
            //

            NameControl->allocatedBuffer = newBuffer;
            bufferSize = newSize;
            nameInfo = newNameInfo;

        } else {

            //
            //  The MaximumLength was set by ObQueryNameString to
            //  one char larger then the length.  Set it to the
            //  true size of the buffer (so we can append the names)
            //

            nameInfo->Name.MaximumLength = (USHORT)(bufferSize - 
                                  sizeof(OBJECT_NAME_INFORMATION));
        }

        //
        //  If there is a related file object, append that name
        //  first onto the device object along with a separator
        //  character
        //

        if (NULL != FileObject->RelatedFileObject) {

            RtlAppendUnicodeStringToString(
                    &nameInfo->Name,
                    &FileObject->RelatedFileObject->FileName );

            RtlAppendUnicodeToString( &nameInfo->Name, L"\\" );
        }

        //
        //  Append the name from the file object
        //

        RtlAppendUnicodeStringToString(
                &nameInfo->Name,
                &FileObject->FileName );

        ASSERT(nameInfo->Name.Length <= nameInfo->Name.MaximumLength);
    }

    //
    //  Return the name
    //

    return &nameInfo->Name;
}


VOID
SfGetFileNameCleanup(
    IN OUT PGET_NAME_CONTROL NameControl
    )
/*++

Routine Description:

    This will see if a buffer was allocated and will free it if it was

Arguments:

    NameControl - control structure used for retrieving the name.  It keeps
        track if a buffer was allocated or if we are using the internal
        buffer.

Return Value:

    None

--*/
{

    if (NULL != NameControl->allocatedBuffer) {

        ExFreePool( NameControl->allocatedBuffer);
        NameControl->allocatedBuffer = NULL;
    }
}

VOID
SfDisplayCreateFileName (
    IN PIRP Irp
    )

/*++

Routine Description:

    This function is called from SfCreate and will display the name of the
    file being created.  This is in a subroutine so that the local name buffer
    on the stack (in nameControl) is not on the stack when we call down to
    the file system for normal operations.

Arguments:

    Irp - Pointer to the I/O Request Packet that represents the operation.

Return Value:

    None.

--*/

{
    PIO_STACK_LOCATION pIrpSp;
	PUNICODE_STRING name;
	GET_NAME_CONTROL nameControl;

    //
    //  Get current IRP stack
    //
	
	pIrpSp = IoGetCurrentIrpStackLocation(Irp);

    //
    //  Get the name of this file object
    //

    name = SfGetFileName( pIrpSp->FileObject, 
                          Irp->IoStatus.Status, 
                          &nameControl );

    //
    //  Display the name
    //

    if (pIrpSp->Parameters.Create.Options & FILE_OPEN_BY_FILE_ID) {

        SF_LOG_PRINT( SFDEBUG_DISPLAY_CREATE_NAMES,
                      ("SFilter!SfDisplayCreateFileName: Opened %08x:%08x %wZ (FID)\n", 
                       Irp->IoStatus.Status,
                       Irp->IoStatus.Information,
                       name) );

    } else {

        SF_LOG_PRINT( SFDEBUG_DISPLAY_CREATE_NAMES,
                      ("SFilter!SfDisplayCreateFileName: Opened %08x:%08x %wZ\n", 
                       Irp->IoStatus.Status,
                       Irp->IoStatus.Information,
                       name) );
    }

    //
    //  Cleanup from getting the name
    //

    SfGetFileNameCleanup( &nameControl );
}

NTSTATUS
SfCreate (
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    )

/*++

Routine Description:

    This function filters create/open operations.  It simply establishes an
    I/O completion routine to be invoked if the operation was successful.

Arguments:

    DeviceObject - Pointer to the target device object of the create/open.

    Irp - Pointer to the I/O Request Packet that represents the operation.

Return Value:

    The function value is the status of the call to the file system's entry
    point.

--*/

{
	NTSTATUS status;
	PIO_STACK_LOCATION pIrpSp;
	GET_NAME_CONTROL nameControl;
	PUNICODE_STRING volName;
	UNICODE_STRING dosName;
	PSFILTER_DEVICE_EXTENSION pExt;

    PAGED_CODE();

    //
	//  If this is for our control device object, allow it to be opened.
	//

    if (IS_MY_CONTROL_DEVICE_OBJECT(DeviceObject)) {

        //
        //  Sfilter doesn't allow for any communication through its control
        //  device object, therefore it fails all requests to open a handle
        //  to its control device object.
        //
        //  See the FileSpy sample for an example of how to allow creates to 
        //  the filter's control device object and manage communication via
        //  that handle.
        //

		Irp->IoStatus.Status = STATUS_SUCCESS; //STATUS_INVALID_DEVICE_REQUEST;
        Irp->IoStatus.Information = 0;

        IoCompleteRequest( Irp, IO_NO_INCREMENT );

        return STATUS_INVALID_DEVICE_REQUEST;
    }

    ASSERT(IS_MY_DEVICE_OBJECT( DeviceObject ));


	pExt = (PSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension;

	// When file create, If file is overwrite, judge it is protected.
	pIrpSp = IoGetCurrentIrpStackLocation(Irp);
	switch(pIrpSp->Parameters.Create.Options >> 24 & 0xFF)
	{
	case FILE_SUPERSEDE:
	case FILE_OVERWRITE:
	case FILE_OVERWRITE_IF:
		{
			PUNICODE_STRING pFileName = NULL;
			status = GetFullPath(DeviceObject, Irp, &pFileName);
			if(NT_SUCCESS(status))
			{
				if(SfIsDisableDeleteFile(pFileName, CompareCallBack))
				{
					status = STATUS_NO_SUCH_FILE; //STATUS_ACCESS_DENIED;
					Irp->IoStatus.Status = status;
					IoCompleteRequest(Irp, IO_NO_INCREMENT);
					FreeBuffer(pFileName);
					return status;
				}// 结束 if(SfIsDisableDeleteFile(pFileName, CompareCallBack))
				FreeBuffer(pFileName);
			}// 结束 if(NT_SUCCESS(status))
		}
		break;
	case FILE_CREATE:
	case FILE_OPEN_IF:
	case FILE_OPEN:
		break;
	default:
		break;
	} // 结束 switch(pIrpSp->Parameters.Create.Options >> 24 & 0xFF)

	

#ifdef DBG
	if(FlagOn(SFDEBUG_CREATE, SfDebug))
	{
		KdPrint(("DeviceObject:%x\n", DeviceObject));
		KdPrint(("pIrpSP->FileObject:%x\n", pIrpSp->FileObject));
		KdPrint(("pExt->AttachedToDeviceObject:%x\n", pExt->AttachedToDeviceObject));
		KdPrint(("pExt->StorageStackDeviceObject:%x\n", pExt->StorageStackDeviceObject));
		KdPrint(("pIrpSP->FileObject->fileName:%wZ\n", &pIrpSp->FileObject->FileName));
		KdPrint(("pIrpSP->DeviceObject:%x\n", pIrpSp->DeviceObject));

		volName = SfGetFileName(pIrpSp->FileObject, 0, &nameControl);
		KdPrint(("pIrpSp->FileObject:%wZ\n", volName));
		pExt = (PSFILTER_DEVICE_EXTENSION)DeviceObject->DeviceExtension;
		KdPrint(("Device Name:%wZ\n", &pExt->DeviceName));
		KdPrint(("Device Dos Name:%wZ\n", &pExt->DeviceLinkSymbolName));

		// error:the first parameter of follow function must be volume object.
		//       otherwise,cause blue screen.
		//status = VolumeDeviceToDosName(pIrpSp->FileObject->DeviceObject, &dosName);
		//if(NT_SUCCESS(status))
		//{
		//	KdPrint(("VolumeDeviceToDosName:%wZ\n", &dosName));
		//	ExFreePool(dosName.Buffer);
		//}// 结束 (NT_SUCCESS(status))
	} // 结束 if(FlagOn(SFDEBUG_CREATE, SfDebug))
#endif

	
    //
    //  If debugging is enabled, do the processing required to see the packet
    //  upon its completion.  Otherwise, let the request go with no further
    //  processing.
    //

    if (!FlagOn( SfDebug, SFDEBUG_DO_CREATE_COMPLETION |
                          SFDEBUG_GET_CREATE_NAMES|
						  SFDEBUG_DISPLAY_CREATE_NAMES))
	{
		//
        //  Don't put us on the stack then call the next driver
		//
		IoSkipCurrentIrpStackLocation(Irp);

        return IoCallDriver( ((PSFILTER_DEVICE_EXTENSION) DeviceObject->DeviceExtension)->AttachedToDeviceObject, Irp );

    } else {
    
        KEVENT waitEvent;

        //
        //  Initialize an event to wait for the completion routine to occur
        //

        KeInitializeEvent( &waitEvent, NotificationEvent, FALSE );

        //
        //  Copy the stack and set our Completion routine
		//

		IoCopyCurrentIrpStackLocationToNext(Irp);

		IoSetCompletionRoutine(
            Irp,
            SfCompletionRoutine,
            &waitEvent,
            TRUE,
            TRUE,
            TRUE );

        //
        //  Call the next driver in the stack.
        //

        status = IoCallDriver( ((PSFILTER_DEVICE_EXTENSION) DeviceObject->DeviceExtension)->AttachedToDeviceObject, Irp );

        //
        //  Wait for the completion routine to be called
        //

	    if (STATUS_PENDING == status) {

            NTSTATUS localStatus = KeWaitForSingleObject(&waitEvent, Executive, KernelMode, FALSE, NULL);
		    ASSERT(STATUS_SUCCESS == localStatus);
	    }

        //
        //  Verify the IoCompleteRequest was called
        //

        ASSERT(KeReadStateEvent(&waitEvent) ||
               NT_SUCCESS(Irp->IoStatus.Status));

        //
        //  Retrieve and display the filename if requested
        //

        if (FlagOn(SfDebug,
                   (SFDEBUG_GET_CREATE_NAMES|SFDEBUG_DISPLAY_CREATE_NAMES))) {

            SfDisplayCreateFileName( Irp );
        }

        //
        //  Save the status and continue processing the IRP
        //

        status = Irp->IoStatus.Status;

        IoCompleteRequest( Irp, IO_NO_INCREMENT );

        return status;
    }
}

NTSTATUS
SfCleanupClose (
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
    )

/*++

Routine Description:

    This routine is invoked whenever a cleanup or a close request is to be
    processed.

Arguments:

    DeviceObject - Pointer to the device object for this driver.

    Irp - Pointer to the request packet representing the I/O request.

Return Value:

    The function value is the status of the operation.

Note:

    See notes for SfPassThrough for this routine.


--*/

{
	NTSTATUS status;

    PAGED_CODE();

    //
	// If this is KSFilter device object.close the handle.
    //
    
	if(IS_MY_CONTROL_DEVICE_OBJECT(DeviceObject))
	{
		status = STATUS_SUCCESS;
		Irp->IoStatus.Status = status;
		Irp->IoStatus.Information = 0;
		IoCompleteRequest(Irp, IO_NO_INCREMENT);
		return status;
	} // 结束 ()

    ASSERT(IS_MY_DEVICE_OBJECT( DeviceObject ));

    //
    //  Get this driver out of the driver stack and get to the next driver as
    //  quickly as possible.
    //

    IoSkipCurrentIrpStackLocation( Irp );

    //
    //  Now call the appropriate file system driver with the request.
    //

    return IoCallDriver( ((PSFILTER_DEVICE_EXTENSION) DeviceObject->DeviceExtension)->AttachedToDeviceObject, Irp );
}