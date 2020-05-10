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
//#pragma comment(lib,"C:\\NTDDK\\lib\\i386\\free\\setupapi.lib")

#include <regstr.h>
#include <winbase.h>

#include <cfgmgr32.h>
// ��Ҫ����cfgmgr32.lib
//#pragma comment(lib,"C:\\NTDDK\\lib\\i386\\free\\cfgmgr32.lib")

#include <initguid.h>

//������GUID
DEFINE_GUID(GUID_DEVINTERFACE_NET_ADAPTER_DEVICE,
  0x4d36e972L, 0xe325, 0x11ce, 0xbf, 0xc1, 0x08, 0x00, 0x2b, 0xe1, 0x03, 0x18);
#define GUID_CLASS_NET_ADAPTER_DEVICE           GUID_DEVINTERFACE_NET_ADAPTER_DEVICE

BOOL ChangeNetAdapter(DWORD dwStatus)
{
    //IN LPTSTR HardwareId="PCI\\VEN_10EC&DEV_8139&SUBSYS_813910EC&REV_10" ;
	//IN LPTSTR HardwareId="USB\\Vid_0457&Pid_0163";
	IN LPTSTR HardwareClassId="{4d36e972-e325-11ce-bfc1-08002be10318}" ;
	//IN LPTSTR HardwareId="{4D36E972-E325-11CE-BFC1-08002BE10318}" ;
    //Ӳ��ComponentId��ע����ַ��system\currentcontrolset\class\{4D36E972-E325-11CE-BFC1-08002BE10318}\0000

       
	//����ddk����������������    
    DWORD i,err ;
    BOOL Found=FALSE ;
    
    HDEVINFO hDevInfo ;
    SP_DEVINFO_DATA spDevInfoData ;
    
   
    //����ϵͳ��Ӳ����,ö������(�������ӿ���ö��)
    hDevInfo = SetupDiGetClassDevs(&GUID_CLASS_NET_ADAPTER_DEVICE, NULL, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
	//ö��ϵͳ���Ѱ�װ����
	//hDevInfo=SetupDiGetClassDevs(NULL, NULL, NULL, DIGCF_ALLCLASSES | DIGCF_PRESENT);
    if(hDevInfo == INVALID_HANDLE_VALUE)
    {
        printf("����ϵͳӲ������\n");
        return FALSE ;
    }
    
    //ö��Ӳ���������Ҫ�Ľӿ�
	//ms-help://MS.VSCC.v80/MS.MSDN.v80/MS.WIN32COM.v10.en/devio/base/enumerating_current_devices.htm
    spDevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
	BOOL flagEnum;
    for(i = 0; flagEnum = SetupDiEnumDeviceInfo(hDevInfo, i, &spDevInfoData); i++)
    {
#ifdef _DEBUG
		//�õ���ǰӲ���ӿڵ�����,������������ж�,�����Ƿ��������Ӳ���ӿ�
        DWORD DataT ;
        CHAR buffer[256]={0};
		DWORD buffersize=0 ;
        
        //���Ӳ��������ֵ
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
		TRACE(_T("%s\n"), buffer);
#endif
	
		//���ýӿڵ�״̬
		SP_PROPCHANGE_PARAMS spPropChangeParams ;
		
		spPropChangeParams.ClassInstallHeader.cbSize=sizeof(SP_CLASSINSTALL_HEADER);
		spPropChangeParams.ClassInstallHeader.InstallFunction=DIF_PROPERTYCHANGE ;
		spPropChangeParams.Scope=DICS_FLAG_GLOBAL ;
		spPropChangeParams.StateChange=dwStatus ;
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
	}
	
//�˳�ʱ������������
#ifdef _DEBUG
cleanup_DeviceInfo:
#endif
	err=GetLastError();
	SetupDiDestroyDeviceInfoList(hDevInfo);
	SetLastError(err);

	return TRUE ;
}

/*******************************************************************************************************
��������EnableNetAdapter
��  �ܣ����û��������
��  ����
        BOOL bStatus��TRUE:��������;FALSE:��������
����ֵ��BOOL �ɹ�����TRUE;ʧ�ܷ���FALSE.
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2007-6-27
ʱ  �䣺20:46:02
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
��������StartNetAdapter
��  �ܣ���װ��ж������
��  ����
        BOOL bStatus��TRUE:��װ����,FALSE:ж������
����ֵ��BOOL:�ɹ�����TRUE;ʧ�ܷ���FALSE.
��  �ߣ���  ��
��  ����1.0.0.1
��  �ڣ�2007-6-27
ʱ  �䣺20:44:31
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

