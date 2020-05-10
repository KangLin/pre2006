/*******************************************************************************************************
版权所有 (C) 2007 康林工作室；保留所有权利。
文件名：function.c
描  述：基本函数
版  本：1.0
作  者：康  林
E_Mail：kl222@126.com
日  期：2007年4月29日
时  间：13:33:29
编译器：Microsoft Visual Studio 8.0 —— C/C++ 8.0
*******************************************************************************************************/

#include "sfilter.h"

#if WINVER >= 0x0501
VOID
SfLoadDynamicFunctions (
    )
/*++

Routine Description:

    This routine tries to load the function pointers for the routines that
    are not supported on all versions of the OS.  These function pointers are
    then stored in the global structure SpyDynamicFunctions.

    This support allows for one driver to be built that will run on all 
    versions of the OS Windows 2000 and greater.  Note that on Windows 2000, 
    the functionality may be limited.
    
Arguments:

    None.
    
Return Value:

    None.

--*/
{
    UNICODE_STRING functionName;

    RtlZeroMemory( &gSfDynamicFunctions, sizeof( gSfDynamicFunctions ) );

    //
    //  For each routine that we would want to use, lookup its address in the
    //  kernel or hal.  If it is not present, that field in our global
    //  SpyDynamicFunctions structure will be set to NULL.
    //

    RtlInitUnicodeString( &functionName, L"FsRtlRegisterFileSystemFilterCallbacks" );
    gSfDynamicFunctions.RegisterFileSystemFilterCallbacks = MmGetSystemRoutineAddress( &functionName );

    RtlInitUnicodeString( &functionName, L"IoAttachDeviceToDeviceStackSafe" );
    gSfDynamicFunctions.AttachDeviceToDeviceStackSafe = MmGetSystemRoutineAddress( &functionName );
    
    RtlInitUnicodeString( &functionName, L"IoEnumerateDeviceObjectList" );
    gSfDynamicFunctions.EnumerateDeviceObjectList = MmGetSystemRoutineAddress( &functionName );

    RtlInitUnicodeString( &functionName, L"IoGetLowerDeviceObject" );
    gSfDynamicFunctions.GetLowerDeviceObject = MmGetSystemRoutineAddress( &functionName );

    RtlInitUnicodeString( &functionName, L"IoGetDeviceAttachmentBaseRef" );
    gSfDynamicFunctions.GetDeviceAttachmentBaseRef = MmGetSystemRoutineAddress( &functionName );

    RtlInitUnicodeString( &functionName, L"IoGetDiskDeviceObject" );
    gSfDynamicFunctions.GetDiskDeviceObject = MmGetSystemRoutineAddress( &functionName );

    RtlInitUnicodeString( &functionName, L"IoGetAttachedDeviceReference" );
    gSfDynamicFunctions.GetAttachedDeviceReference = MmGetSystemRoutineAddress( &functionName );

    RtlInitUnicodeString( &functionName, L"RtlGetVersion" );
    gSfDynamicFunctions.GetVersion = MmGetSystemRoutineAddress( &functionName );

	RtlInitUnicodeString(&functionName, L"IoVolumeDeviceToDosName");
	gSfDynamicFunctions.VolumeDeviceToDosName = MmGetSystemRoutineAddress(&functionName);
}

VOID
SfGetCurrentVersion (
    )
/*++

Routine Description:

    This routine reads the current OS version using the correct routine based
    on what routine is available.

Arguments:

    None.
    
Return Value:

    None.

--*/
{
    if (NULL != gSfDynamicFunctions.GetVersion) {

        RTL_OSVERSIONINFOW versionInfo;
        NTSTATUS status;

        //
        //  VERSION NOTE: RtlGetVersion does a bit more than we need, but
        //  we are using it if it is available to show how to use it.  It
        //  is available on Windows XP and later.  RtlGetVersion and
        //  RtlVerifyVersionInfo (both documented in the IFS Kit docs) allow
        //  you to make correct choices when you need to change logic based
        //  on the current OS executing your code.
        //

        versionInfo.dwOSVersionInfoSize = sizeof( RTL_OSVERSIONINFOW );

        status = (gSfDynamicFunctions.GetVersion)( &versionInfo );

        ASSERT( NT_SUCCESS( status ) );

        gSfOsMajorVersion = versionInfo.dwMajorVersion;
        gSfOsMinorVersion = versionInfo.dwMinorVersion;
        
    } else {

        PsGetVersion( &gSfOsMajorVersion,
                      &gSfOsMinorVersion,
                      NULL,
                      NULL );
    }
}
#endif

/*******************************************************************************************************
函数名：VolumeDeviceToDosName
描  述：从卷设备得到设备名
参  数：
        IN PVOID VolumeDeviceObject：卷设备
		OUT PUNICODE_STRING DosName：设备名
返回值：类型为 NTSTATUS 。
版  本：1.0
作  者：康  林
时  间：2007年4月29日 15:41:18
*******************************************************************************************************/
NTSTATUS
VolumeDeviceToDosName(
					  IN PVOID VolumeDeviceObject,
					  OUT PUNICODE_STRING DosName
					  )
{
#if WINVER >= 0x0501
	if(IS_WINDOWSXP_OR_LATER())
	{
		ASSERT(NULL != gSfDynamicFunctions.VolumeDeviceToDosName);
		return gSfDynamicFunctions.VolumeDeviceToDosName(VolumeDeviceObject, DosName);
	}
	else
	{
		ASSERT(NULL == gSfDynamicFunctions.VolumeDeviceToDosName);
#endif
		return RtlVolumeDeviceToDosName(VolumeDeviceObject, DosName);
#if WINVER >= 0x0501
	} // 结束 if(IS_WINDOWSXP_OR_LATER())
#endif // 结束 #if WINVER >= 0x0501
}

VOID
SfReadDriverParameters (
    IN PUNICODE_STRING RegistryPath
    )
/*++

Routine Description:

    This routine tries to read the sfilter-specific parameters from 
    the registry.  These values will be found in the registry location
    indicated by the RegistryPath passed in.

Arguments:

    RegistryPath - the path key passed to the driver during driver entry.
        
Return Value:

    None.

--*/
{
    OBJECT_ATTRIBUTES attributes;
    HANDLE driverRegKey;
    NTSTATUS status;
    ULONG resultLength;
    UNICODE_STRING valueName;
    UCHAR buffer[sizeof( KEY_VALUE_PARTIAL_INFORMATION ) + sizeof( LONG )];

    PAGED_CODE();

    //
    //  If this value is not the default value then somebody has already
    //  explicitly set it so don't override those settings.
    //

    if (0 == SfDebug) {

        //
        //  Open the desired registry key
        //

        InitializeObjectAttributes( &attributes,
                                    RegistryPath,
                                    OBJ_CASE_INSENSITIVE,
                                    NULL,
                                    NULL );

        status = ZwOpenKey( &driverRegKey,
                            KEY_READ,
                            &attributes );

        if (!NT_SUCCESS( status )) {

            return;
        }

        //
        // Read the DebugDisplay value from the registry.
        //

        RtlInitUnicodeString( &valueName, L"DebugFlags" );
    
        status = ZwQueryValueKey( driverRegKey,
                                  &valueName,
                                  KeyValuePartialInformation,
                                  buffer,
                                  sizeof(buffer),
                                  &resultLength );

        if (NT_SUCCESS( status )) {

            SfDebug = *((PLONG) &(((PKEY_VALUE_PARTIAL_INFORMATION) buffer)->Data));
        } 

        //
        //  Close the registry entry
        //

        ZwClose(driverRegKey);
    }
}

NTSTATUS
SfAttachDeviceToDeviceStack (
							 IN PDEVICE_OBJECT SourceDevice,
							 IN PDEVICE_OBJECT TargetDevice,
							 IN OUT PDEVICE_OBJECT *AttachedToDeviceObject
							 )
							 /*++

							 Routine Description:

							 This routine attaches the SourceDevice to the TargetDevice's stack and
							 returns the device object SourceDevice was directly attached to in 
							 AttachedToDeviceObject.  Note that the SourceDevice does not necessarily
							 get attached directly to TargetDevice.  The SourceDevice will get attached
							 to the top of the stack of which TargetDevice is a member.

							 VERSION NOTE:

							 In Windows XP, a new API was introduced to close a rare timing window that 
							 can cause IOs to start being sent to a device before its 
							 AttachedToDeviceObject is set in its device extension.  This is possible
							 if a filter is attaching to a device stack while the system is actively
							 processing IOs.  The new API closes this timing window by setting the
							 device extension field that holds the AttachedToDeviceObject while holding
							 the IO Manager's lock that protects the device stack.

							 A sufficient work around for earlier versions of the OS is to set the
							 AttachedToDeviceObject to the device object that the SourceDevice is most
							 likely to attach to.  While it is possible that another filter will attach
							 in between the SourceDevice and TargetDevice, this will prevent the
							 system from bug checking if the SourceDevice receives IOs before the 
							 AttachedToDeviceObject is correctly set.

							 For a driver built in the Windows 2000 build environment, we will always 
							 use the work-around code to attach.  For a driver that is built in the 
							 Windows XP or later build environments (therefore you are building a 
							 multiversion driver), we will determine which method of attachment to use 
							 based on which APIs are available.

							 Arguments:

							 SourceDevice - The device object to be attached to the stack.

							 TargetDevice - The device that we currently think is the top of the stack
							 to which SourceDevice should be attached.

							 AttachedToDeviceObject - This is set to the device object to which 
							 SourceDevice is attached if the attach is successful.

							 Return Value:

							 Return STATUS_SUCCESS if the device is successfully attached.  If 
							 TargetDevice represents a stack to which devices can no longer be attached,
							 STATUS_NO_SUCH_DEVICE is returned.

							 --*/
{

	PAGED_CODE();

#if WINVER >= 0x0501

	if (IS_WINDOWSXP_OR_LATER()) {

		ASSERT( NULL != gSfDynamicFunctions.AttachDeviceToDeviceStackSafe );
		return (gSfDynamicFunctions.AttachDeviceToDeviceStackSafe)( SourceDevice,
			TargetDevice,
			AttachedToDeviceObject );

	} else {

		ASSERT( NULL == gSfDynamicFunctions.AttachDeviceToDeviceStackSafe );
#endif

		*AttachedToDeviceObject = TargetDevice;
		*AttachedToDeviceObject = IoAttachDeviceToDeviceStack( SourceDevice,
			TargetDevice );

		if (*AttachedToDeviceObject == NULL) {

			return STATUS_NO_SUCH_DEVICE;
		}

		return STATUS_SUCCESS;

#if WINVER >= 0x0501
	}
#endif
}

NTSTATUS
SfFsControlCompletion (
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp,
    IN PVOID Context
    )

/*++

Routine Description:

    This routine is invoked for the completion of an FsControl request.  It
    signals an event used to re-sync back to the dispatch routine.

Arguments:

    DeviceObject - Pointer to this driver's device object that was attached to
            the file system device object

    Irp - Pointer to the IRP that was just completed.

    Context - Pointer to the event to signal

--*/

{
    UNREFERENCED_PARAMETER( DeviceObject );
    UNREFERENCED_PARAMETER( Irp );

    ASSERT(IS_MY_DEVICE_OBJECT( DeviceObject ));
    ASSERT(Context != NULL);

#if WINVER >= 0x0501
    if (IS_WINDOWSXP_OR_LATER()) {

        //
        //  On Windows XP or later, the context passed in will be an event
        //  to signal.
        //

        KeSetEvent((PKEVENT)Context, IO_NO_INCREMENT, FALSE);

    } else {
#endif
        //
        //  For Windows 2000, if we are not at passive level, we should 
        //  queue this work to a worker thread using the workitem that is in 
        //  Context.
        //

        if (KeGetCurrentIrql() > PASSIVE_LEVEL) {

            //
            //  We are not at passive level, but we need to be to do our work,
            //  so queue off to the worker thread.
            //
            
            ExQueueWorkItem( (PWORK_QUEUE_ITEM) Context,
                             DelayedWorkQueue );
            
        } else {

            PWORK_QUEUE_ITEM workItem = Context;

            //
            //  We are already at passive level, so we will just call our 
            //  worker routine directly.
            //

            (workItem->WorkerRoutine)(workItem->Parameter);
        }

#if WINVER >= 0x0501
    }
#endif

    return STATUS_MORE_PROCESSING_REQUIRED;
}

/*!
\brief   Set Completion Routine
\param   IN PDEVICE_OBJECT AttachedDeviceObject：Lower Device Object
\param   IN PIRP Irp                           ：
\return  类型为 NTSTATUS 。
\version 1.0
\author  康  林
\date    2007-5-20 13:08:47
*/
NTSTATUS SetCompletionRoutine(IN PDEVICE_OBJECT AttachedDeviceObject, IN PIRP Irp)
{
	NTSTATUS status = STATUS_SUCCESS;
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

	status = IoCallDriver(AttachedDeviceObject, Irp);

	//
	//  Wait for the completion routine to be called
	//

	if(STATUS_PENDING == status)
	{
		status = KeWaitForSingleObject(&waitEvent, Executive, KernelMode, FALSE, NULL);
		ASSERT(NT_SUCCESS(status));
	}

	//
	//  Verify the IoCompleteRequest was called
	//

	ASSERT(KeReadStateEvent(&waitEvent) ||
		 NT_SUCCESS(Irp->IoStatus.Status));

	if(!NT_SUCCESS(Irp->IoStatus.Status))
	{
		status = Irp->IoStatus.Status;
	}// 结束 if(!NT_SUCCESS(Irp->IoStatus.Status))

	return status;
}

NTSTATUS
SfCompletionRoutine (
					 IN PDEVICE_OBJECT DeviceObject,
					 IN PIRP Irp,
					 IN PVOID Context
					 )

					 /*++

					 Routine Description:

					 This function is the create/open completion routine for this filter
					 file system driver.  If debugging is enabled, then this function prints
					 the name of the file that was successfully opened/created by the file
					 system as a result of the specified I/O request.

					 Arguments:

					 DeviceObject - Pointer to the device on which the file was created.

					 Irp - Pointer to the I/O Request Packet the represents the operation.

					 Context - This driver's context parameter - unused;

					 Return Value:

					 The function value is STATUS_SUCCESS.

					 --*/

{
	PKEVENT event = Context;

	UNREFERENCED_PARAMETER( DeviceObject );
	UNREFERENCED_PARAMETER( Irp );

	ASSERT(IS_MY_DEVICE_OBJECT( DeviceObject ));

	KeSetEvent(event, IO_NO_INCREMENT, FALSE);

	return STATUS_MORE_PROCESSING_REQUIRED;
}


////////////////////////////////////////////////////////////////////////////////////////////
//
//                                      File Information
//
////////////////////////////////////////////////////////////////////////////////////////////

/*!
\brief   查询文件信息
\param   PDEVICE_OBJECT DeviceObject                ：设备对象
\param   PFILE_OBJECT FileObject                    ：要查询信息的文件对象
\param   FILE_INFORMATION_CLASS FileInformationClass：要查询的类
\param   PVOID FileInfo                             ：文件信息指针
\param   ULONG FileInfoLength                       ：文件信息的长度
\return  类型为 NTSTATUS 。成功返回 STATUS_SUCCESS,否则返回错误代码。
\version 1.0
\author  康  林
\date    2007-5-16 13:10:27
*/
NTSTATUS
SfQueryFileInformation(
					   PDEVICE_OBJECT DeviceObject, 
					   PFILE_OBJECT FileObject,
					   FILE_INFORMATION_CLASS FileInformationClass,
					   PVOID FileInfo,
					   ULONG FileInfoLength
					   )
{
	PIRP Irp;
	KEVENT event;
	IO_STATUS_BLOCK IoStatusBlock;
	PIO_STACK_LOCATION IoStackLocation;

	PAGED_CODE();
	ASSERT(DeviceObject && FileObject && FileInfo);

	//
	// Initialize the event
	//
	KeInitializeEvent(&event, NotificationEvent, FALSE);

	//
	// 分配一个IRP，用目标设备对象的StackSize作为新创建IRP的堆栈大小，这是
	// 标准的提供堆栈大小的方法。
	//
	Irp = IoAllocateIrp(DeviceObject->StackSize, FALSE);

	if (!Irp)
		return FALSE;

	//
	// 设置IRP头的相关参数，由于我们采用IoAllocateIrp创建的IRP，因此很多
	// 域要自己设置，包括安装输入缓冲区，同步事件以及IRP标志字段，这个字段
	// 对文件信息查询没有太大的用处，对文件读写十分关键。
	//  
	Irp->AssociatedIrp.SystemBuffer = FileInfo;
	Irp->UserEvent = &event;
	Irp->UserIosb = &IoStatusBlock;
	Irp->Tail.Overlay.Thread = PsGetCurrentThread();
	Irp->Tail.Overlay.OriginalFileObject = FileObject;
	Irp->RequestorMode = KernelMode;
	Irp->Flags = 0;

	//
	// 设置IRP堆栈位置中的相关参数，最重要的是MajorFunction，它决定了这个
	// IRP的主要功能，另外Parameters.QueryFile.FileInformationClass定义了
	// 希望查询哪种文件信息。
	//
	IoStackLocation = IoGetNextIrpStackLocation(Irp);
	IoStackLocation->MajorFunction = IRP_MJ_QUERY_INFORMATION;
	IoStackLocation->DeviceObject = DeviceObject;
	IoStackLocation->FileObject = FileObject;
	IoStackLocation->Parameters.QueryFile.Length = FileInfoLength;
	IoStackLocation->Parameters.QueryFile.FileInformationClass = FileInformationClass;

	//
	// 安装IRP完成例程
	//
	IoSetCompletionRoutine(Irp, SfQueryFileInformationCompleted, 0, TRUE, TRUE, TRUE);

	(void) IoCallDriver(DeviceObject, Irp);

	//
	// 等待同步时间返回，我们在IRP的完成例程当中将事件置为信号态
	//
	KeWaitForSingleObject(&event, Executive, KernelMode, TRUE, 0);

	return(IoStatusBlock.Status);
}

NTSTATUS
SfQueryFileInformationCompleted(
								PDEVICE_OBJECT DeviceObject,
								PIRP Irp,
								PVOID Context
								)
{
	//
	// Copy the status information back into the "user" IOSB.
	//
	*Irp->UserIosb = Irp->IoStatus;

#ifdef DBG
	if( !NT_SUCCESS(Irp->IoStatus.Status) ) {

		KdPrint(("QueryFileInformationCompleted  ERROR ON IRP: %x\n", Irp->IoStatus.Status));
	}
#endif
	//
	// 在完成例程中设置同步事件为信号态。
	//
	KeSetEvent(Irp->UserEvent, 0, FALSE);

	//
	// 在完成例程里需要自己释放刚刚创建的IRP，因为I/O管理器不会为我们做这个工作
	//
	IoFreeIrp(Irp);

	//
	// 我们返回STATUS_MORE_PROCESSING_REQUIRED，就是告诉I/O管理器这个IRP还有其它
	// 的进程在访问，请不要将其删除，事实上这个IRP应该由我们自己来释放而不是I/O
	// 管理器，所以在自己创建的IRP的完成例程当中必须返回这个值。另外，这个我们不
	// 能为这个IRP调用IoCompleteRequest。
	//
	return STATUS_MORE_PROCESSING_REQUIRED;
}

/*!
\brief   查询文件基本信息
\param   PDEVICE_OBJECT DeviceObject          ：设备对象
\param   PFILE_OBJECT FileObject              ：要查询的文件对象
\param   PFILE_BASIC_INFORMATION FileBasicInfo：文件基本信息结构指针
\return  NTSTATUS
\version 1.0
\author  康  林
\date    2007-5-16 13:26:01
*/
NTSTATUS
SfQueryFileBasicInformation(
							PDEVICE_OBJECT DeviceObject, 
							PFILE_OBJECT FileObject,
							PFILE_BASIC_INFORMATION FileBasicInfo
							)
{
	ASSERT(DeviceObject && FileObject && FileBasicInfo);

	return SfQueryFileInformation(
		DeviceObject, 
		FileObject,
		FileBasicInformation,
		FileBasicInfo,
		sizeof(FILE_BASIC_INFORMATION)
		);
}

/*!
\brief   得到文件名信息
\param   PDEVICE_OBJECT DeviceObject    ：设备对象
\param   PFILE_OBJECT FileObject        ：要查询的文件对象
\param   PFILE_NAME_INFORMATION FileName：文件名信息缓存指针
\param   ULONG dwLen                    ：缓存的长度
\return  类型为 NTSTATUS 。
\version 1.0
\author  康  林
\date    2007-5-21 10:02:19
*/
NTSTATUS
SfQueryFileName(PDEVICE_OBJECT DeviceObject, 
				PFILE_OBJECT FileObject,
				PFILE_NAME_INFORMATION pFileName,
				ULONG dwLen
				)
{
	ASSERT(DeviceObject && FileObject && pFileName);

	return SfQueryFileInformation(
		DeviceObject, 
		FileObject,
		FileNameInformation,
		pFileName,
		dwLen
		);
}