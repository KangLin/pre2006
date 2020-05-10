/*******************************************************************************************************
版权所有 (C) 2007 ；保留所有权利。
文件名：ksfilter.h
描  述：
版  本：1.0
作  者：康  林
E_Mail：kl222@126.com
日  期：2007年4月16日
时  间：17:56:46
编译器：Microsoft Visual Studio 8.0 —— C/C++ 8.0
*******************************************************************************************************/

#include <ntddk.h>
#include <wdmsec.h> // for IoCreateDeviceSecure
#include <initguid.h>


#if DBG
#define DebugPrint(_x_) \
               DbgPrint ("ksfilter"); \
               DbgPrint _x_;

#define TRAP() DbgBreakPoint()

#else
#define DebugPrint(_x_)
#define TRAP()
#endif

//
//  We want ASSERT defined as an expression, which was fixed after Windows 2000
//

//#ifdef ASSERT
//#undef ASSERT
//#if DBG
//#define ASSERT( exp ) \
//    ((!(exp)) ? \
//        (RtlAssert( #exp, __FILE__, __LINE__, NULL ),FALSE) : \
//        TRUE)
//#else
//#define ASSERT( exp ) ((void) 0)
//#endif
//#endif

//
//  Macro to test if this is my device object
//

#define IS_MY_DEVICE_OBJECT(_devObj) \
    (((_devObj) != NULL) && \
     ((_devObj)->DriverObject == gSFilterDriverObject) && \
      ((_devObj)->DeviceExtension != NULL))

//
//  Macro to test if this is my control device object
//

#define IS_MY_CONTROL_DEVICE_OBJECT(_devObj) \
    (((_devObj) == gSFilterControlDeviceObject) ? \
            (ASSERT(((_devObj)->DriverObject == gSFilterDriverObject) && \
                    ((_devObj)->DeviceExtension == NULL)), TRUE) : \
            FALSE)

//
//  Macro to test for device types we want to attach to
//

#define IS_DESIRED_DEVICE_TYPE(_type) \
    (((_type) == FILE_DEVICE_DISK_FILE_SYSTEM) || \
     ((_type) == FILE_DEVICE_CD_ROM_FILE_SYSTEM) || \
     ((_type) == FILE_DEVICE_NETWORK_FILE_SYSTEM))

//
//  Macro to test if FAST_IO_DISPATCH handling routine is valid
//

#define VALID_FAST_IO_DISPATCH_HANDLER(_FastIoDispatchPtr, _FieldName) \
    (((_FastIoDispatchPtr) != NULL) && \
     (((_FastIoDispatchPtr)->SizeOfFastIoDispatch) >= \
            (FIELD_OFFSET(FAST_IO_DISPATCH, _FieldName) + sizeof(void *))) && \
     ((_FastIoDispatchPtr)->_FieldName != NULL))

typedef struct _DEVICE_EXTENSION
{
	PDEVICE_OBJECT pSelf;             //指向本驱动自己的设备指针
	PDEVICE_OBJECT pNextLowerDriver;  //本驱动下层的设备
}DEVICE_EXTENSION, *PDEVICE_EXTENSION;


NTSTATUS
DriverEntry(
    IN PDRIVER_OBJECT  DriverObject,
    IN PUNICODE_STRING RegistryPath
    );

NTSTATUS
FilterAddDevice(
    IN PDRIVER_OBJECT DriverObject,
    IN PDEVICE_OBJECT PhysicalDeviceObject
    );
    
VOID
FilterUnload (
    IN PDRIVER_OBJECT DriverObject
    );
    
NTSTATUS
FilterPass (
    IN PDEVICE_OBJECT DeviceObject,
    IN PIRP Irp
	);

NTSTATUS
FilterCreate(
			 IN PDEVICE_OBJECT DeviceObject,
			 IN PIRP Irp
			 );

NTSTATUS
FilterClose(
			 IN PDEVICE_OBJECT DeviceObject,
			 IN PIRP Irp
			 );