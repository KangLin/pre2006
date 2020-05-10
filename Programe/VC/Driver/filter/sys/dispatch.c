/*******************************************************************************************************
版权所有 (C) 2007 ；保留所有权利。
文件名：dispatch.c
描  述：
版  本：1.0
作  者：康  林
E_Mail：kl222@126.com
日  期：2007年4月16日
时  间：17:57:00
编译器：Microsoft Visual Studio 8.0 —— C/C++ 8.0
*******************************************************************************************************/
#include "ksfilter.h"

extern PDRIVER_OBJECT gSFilterDriverObject;

NTSTATUS
FilterPass (
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

    IRP - Pointer to the request packet representing the I/O request.

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
	PIO_STACK_LOCATION pIrp = IoGetCurrentIrpStackLocation(Irp);

	ASSERT(IS_MY_DEVICE_OBJECT(DeviceObject));

    //
    //  File systems should NEVER receive a power IRP
    //
    ASSERT(pIrp->MajorFunction != IRP_MJ_POWER);

    //
    //  Get this driver out of the driver stack and get to the next driver as
    //  quickly as possible.
    //
    IoSkipCurrentIrpStackLocation( Irp );

    //
    //  Call the appropriate file system driver with the request.
    //
    return IoCallDriver( ((PDEVICE_EXTENSION) DeviceObject->DeviceExtension)->pNextLowerDriver,
                          Irp );
}

NTSTATUS
FilterCreate(
			 IN PDEVICE_OBJECT DeviceObject,
			 IN PIRP Irp
			 )
{
	PIO_STACK_LOCATION  pIrpStack;
	NTSTATUS            status;
	PDEVICE_EXTENSION pDeviceExtension;

	DebugPrint(("-->FilterCreate.\n"));
	PAGED_CODE();

	status = STATUS_SUCCESS;
	pIrpStack = IoGetCurrentIrpStackLocation(Irp);

	DebugPrint(("<--FilterCreate.\n"));
	return FilterPass(DeviceObject, Irp);
}

NTSTATUS
FilterClose(
			IN PDEVICE_OBJECT DeviceObject,
			IN PIRP Irp
			)
{
	DebugPrint(("-->FilterClose.\n"));
	PAGED_CODE();
	DebugPrint(("<--FilterClose.\n"));
	return FilterPass(DeviceObject, Irp);
}