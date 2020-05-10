// Device.cpp: implementation of the CDevice class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Device.h"
#include <tchar.h>
#include <stdio.h>
#include <windows.h>
#include <devguid.h>

#define DWORD_PTR DWORD
#define ULONG_PTR DWORD


extern "C" { 
#include <hidsdi.h>
}
// 需加入hid.lib

#include <setupapi.h>
// 需加入setupapi.lib
//#pragma comment(lib,"C:\\NTDDK\\lib\\i386\\free\\setupapi.lib")

#include <regstr.h>
#include <winbase.h>

#include <cfgmgr32.h>
// 需要加入cfgmgr32.lib
//#pragma comment(lib,"C:\\NTDDK\\lib\\i386\\free\\cfgmgr32.lib")

#include <initguid.h>

//网卡类GUID
DEFINE_GUID(GUID_DEVINTERFACE_NET_ADAPTER_DEVICE,
  0x4d36e972L, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);
#define GUID_CLASS_NET_ADAPTER_DEVICE           GUID_DEVINTERFACE_NET_ADAPTER_DEVICE

BOOL ChangeNetAdapter(DWORD dwStatus)
{
    //IN LPTSTR HardwareId="PCI\\VEN_10EC&DEV_8139&SUBSYS_813910EC&REV_10" ;
	//IN LPTSTR HardwareId="USB\\Vid_0457&Pid_0163";
	IN LPTSTR HardwareClassId="{4d36e972-e325-11ce-bfc1-08002be10318}" ;
	//IN LPTSTR HardwareId="{4D36E972-E325-11CE-BFC1-08002BE10318}" ;
    //硬件ComponentId，注册表地址：system\currentcontrolset\class\{4D36E972-E325-11CE-BFC1-08002BE10318}\0000

       
	//调用ddk函数，来禁用网卡    
    DWORD i,err ;
    BOOL Found=FALSE ;
    
    HDEVINFO hDevInfo ;
    SP_DEVINFO_DATA spDevInfoData ;
    
   
    //访问系统的硬件库,枚举网卡(由网卡接口类枚举)
    hDevInfo = SetupDiGetClassDevs(&GUID_CLASS_NET_ADAPTER_DEVICE, NULL, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
	//枚举系统中已安装的类
	//hDevInfo=SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
    if(hDevInfo == INVALID_HANDLE_VALUE)
    {
        printf("访问系统硬件出错！\n");
        return FALSE ;
    }
    
    //枚举硬件，获得需要的接口
	//ms-help://MS.VSCC.v80/MS.MSDN.v80/MS.WIN32COM.v10.en/devio/base/enumerating_current_devices.htm
    spDevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	BOOL flagEnum;
    for(i = 0; flagEnum = SetupDiEnumDeviceInfo(hDevInfo, i, &spDevInfoData); i++)
    {
#ifdef _DEBUG
		//得到当前硬件接口的属性,可以在这进行判断,决定是否是所需的硬件接口
        DWORD DataT ;
        CHAR buffer[256]={0};
		DWORD buffersize=0 ;
        
        //获得硬件的属性值
		buffersize = sizeof(buffer);
        while(!SetupDiGetDeviceRegistryProperty(
				hDevInfo,
				&spDevInfoData,
		        SPDRP_DEVICEDESC  ,//SPDRP_CLASSGUID,
				&DataT,
				(PBYTE)buffer,
				buffersize,
				&buffersize))
        {
			DWORD a = GetLastError();
            if(GetLastError()==ERROR_INVALID_DATA)
            {
                //不存在HardwareID. Continue.
                break ;
            }
            else if(GetLastError()==ERROR_INSUFFICIENT_BUFFER)
            {
                //buffer size不对.
                if(buffer)
					LocalFree(buffer);
//                buffer=(char*)LocalAlloc(LPTR,buffersize);
            }
            else 
            {
                //未知错误
                goto cleanup_DeviceInfo ;
            }
        }
        
        if(GetLastError()==ERROR_INVALID_DATA)
			continue ;
        
		if(NULL == buffer)
		{
		//	LocalFree(buffer);
			
			continue ;
		}
		TRACE(_T("%s\n"), buffer);
#endif
	
		//设置接口的状态
		SP_PROPCHANGE_PARAMS spPropChangeParams ;
		
		spPropChangeParams.ClassInstallHeader.cbSize=sizeof(SP_CLASSINSTALL_HEADER);
		spPropChangeParams.ClassInstallHeader.InstallFunction=DIF_PROPERTYCHANGE ;
		spPropChangeParams.Scope=DICS_FLAG_GLOBAL ;
		spPropChangeParams.StateChange=dwStatus ;
		//禁用：DICS_DISABLE，DICS_ENABLE启用
			
		//
		if(!SetupDiSetClassInstallParams(hDevInfo,&spDevInfoData,(SP_CLASSINSTALL_HEADER*)&spPropChangeParams,sizeof(spPropChangeParams)))
		{
			DWORD errorcode=GetLastError();
		}
		
		if(!SetupDiCallClassInstaller(DIF_PROPERTYCHANGE,hDevInfo,&spDevInfoData))
		{
			DWORD errorcode=GetLastError();
		}
	}
	
//退出时，清理工作环境
#ifdef _DEBUG
cleanup_DeviceInfo:
#endif
	err=GetLastError();
	SetupDiDestroyDeviceInfoList(hDevInfo);
	SetLastError(err);

	return TRUE ;
}

/*******************************************************************************************************
函数名：EnableNetAdapter
功  能：启用或禁用网卡
参  数：
        BOOL bStatus：TRUE:启用网卡;FALSE:禁用网卡
返回值：BOOL 成功返回TRUE;失败返回FALSE.
作  者：康  林
版  本：1.0.0.1
日  期：2007-6-27
时  间：20:46:02
*******************************************************************************************************/
extern "C" BOOL EnableNetAdapter(BOOL bStatus)
{
	BOOL bRet;
	if(bStatus)
	{
		bRet = ChangeNetAdapter(DICS_ENABLE);
	}
	else
	{
		bRet = ChangeNetAdapter(DICS_DISABLE);			
	}
	return bRet;
}

/*******************************************************************************************************
函数名：StartNetAdapter
功  能：安装或卸载网卡
参  数：
        BOOL bStatus：TRUE:安装网卡,FALSE:卸载网卡
返回值：BOOL:成功返回TRUE;失败返回FALSE.
作  者：康  林
版  本：1.0.0.1
日  期：2007-6-27
时  间：20:44:31
*******************************************************************************************************/
extern "C" BOOL StartNetAdapter(BOOL bStatus)
{
	BOOL bRet;
	if(bStatus)
	{
		bRet = ChangeNetAdapter(DICS_START);
	}
	else
	{
		bRet = ChangeNetAdapter(DICS_STOP);			
	}
	return bRet;
}

