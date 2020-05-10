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
// �����hid.lib

#include <setupapi.h>
// �����setupapi.lib
#pragma comment(lib,"C:\\NTDDK\\lib\\i386\\free\\setupapi")

#include <regstr.h>
#include <winbase.h>

#include <cfgmgr32.h>
// ��Ҫ����cfgmgr32.lib
#pragma comment(lib,"C:\\NTDDK\\lib\\i386\\free\\cfgmgr32")

#include <initguid.h>

DEFINE_GUID(GUID_DEVINTERFACE_USB_DEVICE,
  0xA5DCBF10L, 0x6530, 0x11D2, 0x90, 0x1F, 0x00, 0xC0, 0x4F, 0xB9, 0x51, 0xED);
#define GUID_CLASS_USB_DEVICE           GUID_DEVINTERFACE_USB_DEVICE

BOOL CDevice::DisableDevice(BOOL bStatus)
{
    //IN LPTSTR HardwareId="PCI\\VEN_10EC&DEV_8139&SUBSYS_813910EC&REV_10" ;
	IN LPTSTR HardwareId="USB\\Vid_0457&Pid_0163";
	//IN LPTSTR HardwareId="{4d36e972-e325-11ce-bfc1-08002be10318}" ;
	//IN LPTSTR HardwareId="{4D36E972-E325-11CE-BFC1-08002BE10318}" ;
    //Ӳ��ComponentId��ע����ַ��system\currentcontrolset\class\{4D36E972-E325-11CE-BFC1-08002BE10318}\0000

    DWORD NewState ;
    
	//����ddk����������������    
    DWORD i,err ;
    BOOL Found=FALSE ;
    
    HDEVINFO hDevInfo ;
    SP_DEVINFO_DATA spDevInfoData ;
    
    if(bStatus)
    {
        NewState=DICS_DISABLE ;
        //����
    }
    else 
    {
        NewState=DICS_ENABLE ;
        //����
    }
    //����ϵͳ��Ӳ����
    hDevInfo=SetupDiGetClassDevs(NULL,"USB",NULL,DIGCF_ALLCLASSES|DIGCF_PRESENT);
	//hDevInfo=SetupDiGetClassDevs(&GUID_CLASS_USB_DEVICE,"USB",NULL,DIGCF_ALLCLASSES|DIGCF_PRESENT);
    if(hDevInfo==INVALID_HANDLE_VALUE)
    {
        printf("����ϵͳӲ������\n");
        return FALSE ;
    }
    
    //ö��Ӳ���������Ҫ�Ľӿ�
    spDevInfoData.cbSize=sizeof(SP_DEVINFO_DATA);
	BOOL flagEnum;
    for(i=0;flagEnum = SetupDiEnumDeviceInfo(hDevInfo,i,&spDevInfoData);i++)
    {
        DWORD DataT ;
        CHAR buffer[2400]={0};
		DWORD buffersize=0 ;
        
        //���Ӳ��������ֵ
		buffersize = sizeof(buffer);
        while(!SetupDiGetDeviceRegistryProperty(
				hDevInfo,
				&spDevInfoData,
		        SPDRP_HARDWAREID  ,//SPDRP_CLASSGUID,
				&DataT,
				(PBYTE)buffer,
				buffersize,
				&buffersize))
        {
			DWORD a = GetLastError();
            if(GetLastError()==ERROR_INVALID_DATA)
            {
                //������HardwareID. Continue.
                break ;
            }
            else if(GetLastError()==ERROR_INSUFFICIENT_BUFFER)
            {
                //buffer size����.
                if(buffer)
					LocalFree(buffer);
//                buffer=(char*)LocalAlloc(LPTR,buffersize);
            }
            else 
            {
                //δ֪����
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
		
		//if(!strcmpi(HardwareId,buffer))
		if(strstr(buffer, HardwareId))
        {

			SP_PROPCHANGE_PARAMS spPropChangeParams ;
            
            spPropChangeParams.ClassInstallHeader.cbSize=sizeof(SP_CLASSINSTALL_HEADER);
            spPropChangeParams.ClassInstallHeader.InstallFunction=DIF_PROPERTYCHANGE ;
            spPropChangeParams.Scope=DICS_FLAG_GLOBAL ;
            spPropChangeParams.StateChange=NewState ;
            //���ã�DICS_DISABLE��DICS_ENABLE����
            
            //
            if(!SetupDiSetClassInstallParams(hDevInfo,&spDevInfoData,(SP_CLASSINSTALL_HEADER*)&spPropChangeParams,sizeof(spPropChangeParams)))
            {
                DWORD errorcode=GetLastError();
            }
            
            if(!SetupDiCallClassInstaller(DIF_PROPERTYCHANGE,hDevInfo,&spDevInfoData))
            {
                DWORD errorcode=GetLastError();
            }
            
            switch(NewState)
            {
                case DICS_DISABLE :
					printf("�ɹ���������������\n");
                break ;
                case DICS_ENABLE :
					printf("�ɹ���������������\n");
                break ;
            }
            
            //break ;
        //}
		}
        
    }
    
    //�˳�ʱ������������
cleanup_DeviceInfo :
    err=GetLastError();
    SetupDiDestroyDeviceInfoList(hDevInfo);
    SetLastError(err);
    
    return TRUE ;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDevice::CDevice()
{

}

CDevice::~CDevice()
{

}

