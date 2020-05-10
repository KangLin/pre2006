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
		SisLogger::GetInstance()->LogMsg("\n�Ҳ�������\n");
        return FALSE;
    }

	pUtility->SetAdapter(AFun_pAdapter);
    bool bRet = pUtility->WriteListData();
    if (!bRet)
    {
        SisLogger::GetInstance()->LogMsg(
            "\nд�����ݵ� EEPROM ʧ�ܡ�\n");
		AFun_CloseCAdapterFun(AFun_pAdaptersInfoBuffer,
			AFun_pAdapter);
        return FALSE;
    }
    
	
	AFun_CloseCAdapterFun(AFun_pAdaptersInfoBuffer,
        AFun_pAdapter);
    
	SisLogger::GetInstance()->LogMsg("\n\n��¼�ɹ���");
	//SisLogger::GetInstance()->LogMsg("\n��Ͽ�USB���ӡ�Ȼ�����½��ϡ����Ϻ��밴��һ��(ENTER)������\n");
    //int ch = _getch();
    CDevice dev;
	if(!dev.DisableDevice(true))
	{
		SisLogger::GetInstance()->LogMsg("\n������������");
		return FALSE;
	}
	
    if(!dev.DisableDevice(false))
	{
		SisLogger::GetInstance()->LogMsg("\n������������");
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
		SisLogger::GetInstance()->LogMsg("\n���ܴ�������");
        return FALSE;
    }


	SisLogger::GetInstance()->LogMsg(
        "\n��ʼ���� ..............................................\n");
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
        SisLogger::GetInstance()->LogMsg("������Ŀ����ͨ�����̡̡�\n");
    }
    if (option == 'Y' || option == 'y')
	{
		SisLogger::GetInstance()->LogMsg("��ʼдMAC��ַ...\n");
		SisLogger::GetInstance()->LogEndl();
		char addr[13];
		bRet = pUtility->ReadMacFromFile(addr);
		if (!bRet)
		{
			SisLogger::GetInstance()->LogMsg("....���ļ��ж�MAC��ַʧ��.\n");
		}
    	char msg[150];
		int i=0;
		do{
			bRet = pUtility->UpdateMacAddr(addr);
		
			if (bRet)
			{
				sprintf(msg, "....MAC��ַд��ɹ� %s �̡̡�\n",addr);
				SisLogger::GetInstance()->LogMsg(msg);
				break;
			}
			else
			{
				i++;
				sprintf(msg, "....MAC��ַд��ʧ�� %s ������\n�� %d д��MAC��ַ\n",addr,i+1);
				SisLogger::GetInstance()->LogMsg(msg);
			}			
		}while(i<3);
		if(!bRet)
		{
			sprintf(msg, "....MAC��ַд��ʧ�� ������\n");
			SisLogger::GetInstance()->LogMsg(msg);
		}
		
	}
    AFun_TestMode(FALSE, AFun_pAdapter);
	AFun_CloseCAdapterFun(AFun_pAdaptersInfoBuffer,
        AFun_pAdapter);
    SisLogger::GetInstance()->LogEndl();
    return bRet;
}