// SisTestManager.cpp: implementation of the SisTestManager class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SisTestManager.h"
#include "GPIBDevice.h"
#include <iostream>
#include <conio.h>
#include "device.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SisTestManager::SisTestManager()
{
    AFun_AdapterNum=0;
	AFun_OpenedAdapterIndex=0;
	AFun_pAdapter=NULL;
	AFun_pAdaptersInfoBuffer=NULL;
}

SisTestManager::~SisTestManager()
{
    CleanUp();
}

bool SisTestManager::Initialize(int argc, TCHAR* argv[])
{
    m_pGPIB = new GPIBDevice();
    if (!m_pGPIB->Setup())
    {
        return false;
    }

    pUtility = new EepromUtility();
    if (pUtility == NULL)
        return false;
    char buf0[255];
    char buf1[255];
    GetCurrentDirectory(255, buf0);
    strcat(buf0, "\\");
    strcpy(buf1, buf0);
    strcat(buf0, argv[1]);
    strcat(buf1, argv[2]);
    pUtility->SetFilePath(buf0, buf1);    // to modify
    double attPlus = GetPrivateProfileInt("GOLB_VAR", "Additional", 0, buf1);
    m_pGPIB->SetAttPlus(attPlus);
    if (!pUtility->LoadDataFromFile())
    {
        SisLogger::GetInstance()->LogMsg(
            "....Fail to read EEPROM config file\n");
        return false;
    }
    return true;
}

void SisTestManager::CleanUp()
{
    delete pUtility;
}

bool SisTestManager::StartTestItem(int nIndex)
{
    bool bRet;
	m_ItemSet[nIndex]->SetAdapter(AFun_pAdapter);
	m_ItemSet[nIndex]->SetGPIBDevice(m_pGPIB);
    try 
    {
        bRet = m_ItemSet[nIndex]->StartTest();
    }
    catch (...)
    {
        bRet = false;
    }
    return bRet;
}

bool SisTestManager::DoPrepare()
{
	AFun_AdapterNum=0;
	AFun_OpenedAdapterIndex=0;
	AFun_pAdapter=NULL;
	AFun_pAdaptersInfoBuffer=NULL;

    AFun_FindAdapters(&AFun_pAdaptersInfoBuffer,
        &AFun_AdapterNum);
    if (FALSE == AFun_OpenAdapter(0,
        AFun_pAdaptersInfoBuffer,
        &AFun_AdapterNum,
		&AFun_OpenedAdapterIndex,
        &AFun_pAdapter))
    {
		SisLogger::GetInstance()->LogMsg("\n找不到卡。\n");
        return FALSE;
    }

	pUtility->SetAdapter(AFun_pAdapter);
    bool bRet = pUtility->WriteListData();
    if (!bRet)
    {
        SisLogger::GetInstance()->LogMsg(
            "\n写入数据到 EEPROM 失败。\n");
		AFun_CloseCAdapterFun(AFun_pAdaptersInfoBuffer,
			AFun_pAdapter);
        return FALSE;
    }
    
	
	AFun_CloseCAdapterFun(AFun_pAdaptersInfoBuffer,
        AFun_pAdapter);
    
	SisLogger::GetInstance()->LogMsg("\n\n烧录成功。");
	//SisLogger::GetInstance()->LogMsg("\n请断开USB连接。然后重新接上。接上后请按任一键(ENTER)继续。\n");
    //int ch = _getch();
    CDevice dev;
	if(!dev.DisableDevice(true))
	{
		SisLogger::GetInstance()->LogMsg("\n禁用网卡出错。");
		return FALSE;
	}
	
    if(!dev.DisableDevice(false))
	{
		SisLogger::GetInstance()->LogMsg("\n启用网卡出错。");
		return FALSE;
	}

	AFun_AdapterNum=0;
	AFun_OpenedAdapterIndex=0;
	AFun_pAdapter=NULL;
	AFun_pAdaptersInfoBuffer=NULL;

	AFun_FindAdapters(&AFun_pAdaptersInfoBuffer,
        &AFun_AdapterNum);

    if(FALSE == AFun_OpenAdapter(0,
        AFun_pAdaptersInfoBuffer,
        &AFun_AdapterNum,
		&AFun_OpenedAdapterIndex,
        &AFun_pAdapter))
    {
		SisLogger::GetInstance()->LogMsg("\n不能打开驱动。");
        return FALSE;
    }


	SisLogger::GetInstance()->LogMsg(
        "\n开始测试 ..............................................\n");
    SisLogger::GetInstance()->LogEndl();
	
	pUtility->SetAdapter(AFun_pAdapter);

    //Enter testmode
    AFun_TestMode(TRUE, AFun_pAdapter);
    return bRet;
}

bool SisTestManager::DoEndWord(bool result)
{
    char option = 'Y';
	bool bRet = result;
    if (!result)
    {
        std::cout << "Some test item(s) failed, are you still want"
            << " to write MAC address to it?" << std::endl
            << "Y--Yes, N--No: ";
        std::cin >> option;
    }
    else 
    {
        SisLogger::GetInstance()->LogMsg("所有项目测试通过。√√√\n");
    }
    if (option == 'Y' || option == 'y')
	{
		SisLogger::GetInstance()->LogMsg("开始写MAC地址...\n");
		SisLogger::GetInstance()->LogEndl();
		char addr[13];
		bRet = pUtility->ReadMacFromFile(addr);
		if (!bRet)
		{
			SisLogger::GetInstance()->LogMsg("....从文件中读MAC地址失败.\n");
		}
    	char msg[150];
		int i=0;
		do{
			bRet = pUtility->UpdateMacAddr(addr);
		
			if (bRet)
			{
				sprintf(msg, "....MAC地址写入成功 %s √√√\n",addr);
				SisLogger::GetInstance()->LogMsg(msg);
				break;
			}
			else
			{
				i++;
				sprintf(msg, "....MAC地址写入失败 %s ×××\n第 %d 写入MAC地址\n",addr,i+1);
				SisLogger::GetInstance()->LogMsg(msg);
			}			
		}while(i<3);
		if(!bRet)
		{
			sprintf(msg, "....MAC地址写入失败 ×××\n");
			SisLogger::GetInstance()->LogMsg(msg);
		}
		
	}
    AFun_TestMode(FALSE, AFun_pAdapter);
	AFun_CloseCAdapterFun(AFun_pAdaptersInfoBuffer,
        AFun_pAdapter);
    SisLogger::GetInstance()->LogEndl();
    return bRet;
}