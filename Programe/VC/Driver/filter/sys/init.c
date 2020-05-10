/*******************************************************************************************************
版权所有 (C) 2007 ；保留所有权利。
文件名：init.c
描  述：
版  本：1.0
作  者：康  林
E_Mail：kl222@126.com
日  期：2007年4月16日
时  间：17:57:11
编译器：Microsoft Visual Studio 8.0 —— C/C++ 8.0
*******************************************************************************************************/
#include "ksfilter.h"

/////////////////////////////////////////////////////////////////////////////
//
//  Assign text sections for each routine.
//
/////////////////////////////////////////////////////////////////////////////

#ifdef ALLOC_PRAGMA
#pragma alloc_text(INIT, DriverEntry)
#pragma alloc_text(PAGE, FilterAddDevice)
#pragma alloc_text(PAGE, FilterUnload)
#pragma alloc_text(PAGE, FilterPass)
#pragma alloc_text(PAGE, FilterCreate)
#pragma alloc_text(PAGE, FilterClose)
#endif

PDRIVER_OBJECT gSFilterDriverObject = NULL;

NTSTATUS
DriverEntry(
    IN PDRIVER_OBJECT  DriverObject,
    IN PUNICODE_STRING RegistryPath
    )
/*++

Routine Description:

    Installable driver initialization entry point.
    This entry point is called directly by the I/O system.

Arguments:

    DriverObject - pointer to the driver object

    RegistryPath - pointer to a unicode string representing the path,
                   to driver-specific key in the registry.

Return Value:

    STATUS_SUCCESS if successful,
    STATUS_UNSUCCESSFUL otherwise.

--*/
{
    NTSTATUS            status = STATUS_SUCCESS;
    ULONG               ulIndex;
    PDRIVER_DISPATCH  * dispatch;

	UNREFERENCED_PARAMETER(RegistryPath);

    DebugPrint (("-->Entered the Driver Entry\n"));
    DebugPrint (("RegistryPath = %S\n", RegistryPath));


    //
    // Create dispatch points
    //
    for (ulIndex = 0, dispatch = DriverObject->MajorFunction;
         ulIndex <= IRP_MJ_MAXIMUM_FUNCTION;
		 ulIndex++, dispatch++)
	{
        *dispatch = FilterPass;
    }
    
    DriverObject->DriverExtension->AddDevice           = FilterAddDevice;
    DriverObject->DriverUnload                         = FilterUnload;
	DriverObject->MajorFunction[IRP_MJ_CREATE]         = FilterCreate;
	DriverObject->MajorFunction[IRP_MJ_CLOSE]          = FilterClose; 
	/*
	DriverObject->MajorFunction[IRP_MJ_PNP]            = FilterDispatchPnp;
    DriverObject->MajorFunction[IRP_MJ_POWER]          = FilterDispatchPower;

#ifdef IOCTL_INTERFACE
    //
    // Set the following dispatch points as we will be doing
    // something useful to these requests instead of just
    // passing them down. 
    // 
    
    
    DriverObject->MajorFunction[IRP_MJ_CLEANUP]    = 
    DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = 
                                                        FilterDispatchIo;
    
#endif
*/
	//保存驱动对象
	gSFilterDriverObject = DriverObject;
		
    return status;
}


NTSTATUS
FilterAddDevice(
    IN PDRIVER_OBJECT DriverObject,
    IN PDEVICE_OBJECT PhysicalDeviceObject
    )
/*++

Routine Description:

    The Plug & Play subsystem is handing us a brand new PDO, for which we
    (by means of INF registration) have been asked to provide a driver.

    We need to determine if we need to be in the driver stack for the device.
    Create a function device object to attach to the stack
    Initialize that device object
    Return status success.

    Remember: We can NOT actually send ANY non pnp IRPS to the given driver
    stack, UNTIL we have received an IRP_MN_START_DEVICE.

Arguments:

    DeviceObject - pointer to a device object.

    PhysicalDeviceObject -  pointer to a device object created by the
                            underlying bus driver.

Return Value:

    NT status code.

--*/
{
    NTSTATUS                status = STATUS_SUCCESS;
    PDEVICE_OBJECT          deviceObject = NULL;
    PDEVICE_EXTENSION       deviceExtension;
    ULONG                   deviceType = FILE_DEVICE_UNKNOWN;

	DebugPrint(("-->FilterAddDevice.\n"));

    PAGED_CODE ();


    //
    // IoIsWdmVersionAvailable(1, 0x20) returns TRUE on os after Windows 2000.
    //
    if (!IoIsWdmVersionAvailable(1, 0x20)) {
        //
        // Win2K system bugchecks if the filter attached to a storage device
        // doesn't specify the same DeviceType as the device it's attaching
        // to. This bugcheck happens in the filesystem when you disable
        // the devicestack whose top level deviceobject doesn't have a VPB.
        // To workaround we will get the toplevel object's DeviceType and
        // specify that in IoCreateDevice.
        //
        deviceObject = IoGetAttachedDeviceReference(PhysicalDeviceObject);
        deviceType = deviceObject->DeviceType;
        ObDereferenceObject(deviceObject);
    }

    //
    // Create a filter device object.
    //

    status = IoCreateDevice (DriverObject,
                             sizeof (DEVICE_EXTENSION),
                             NULL,  // No Name
                             deviceType,
                             FILE_DEVICE_SECURE_OPEN,
                             FALSE,
                             &deviceObject);


    if (!NT_SUCCESS (status)) {
        //
        // Returning failure here prevents the entire stack from functioning,
        // but most likely the rest of the stack will not be able to create
        // device objects either, so it is still OK.
        //
        return status;
    }

    DebugPrint (("AddDevice PDO (0x%x) FDO (0x%x)\n",
                    PhysicalDeviceObject, deviceObject));
                    
    //建立联接符号

	//附加到底层设备上
    deviceExtension = (PDEVICE_EXTENSION) deviceObject->DeviceExtension;

    deviceExtension->pNextLowerDriver = IoAttachDeviceToDeviceStack (
                                       deviceObject,
                                       PhysicalDeviceObject);
    //
    // Failure for attachment is an indication of a broken plug & play system.
    //

	if(NULL == deviceExtension->pNextLowerDriver)
	{

        IoDeleteDevice(deviceObject);
        return STATUS_UNSUCCESSFUL;
    }

	deviceObject->Flags |= deviceExtension->pNextLowerDriver->Flags & 
                            (DO_BUFFERED_IO | DO_DIRECT_IO |
                            DO_POWER_PAGABLE );

    deviceObject->DeviceType = deviceExtension->pNextLowerDriver->DeviceType;
    deviceObject->Characteristics =
                          deviceExtension->pNextLowerDriver->Characteristics;
    deviceExtension->pSelf = deviceObject;

	DebugPrint(("<--FilterAddDevice.\n"));

	return STATUS_SUCCESS;

}

VOID
FilterUnload (
    IN PDRIVER_OBJECT DriverObject
    )
{
	DebugPrint(("-->FilterUnload.\n"));

	PAGED_CODE();

	//删除联接符号
	
	//删除对象
    DebugPrint (("unload\n"));
    
	if(DriverObject->DeviceObject)
    {
		IoDeleteDevice(DriverObject->DeviceObject);
	}
	DebugPrint(("<--FilterUnload.\n"));
}