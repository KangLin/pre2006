// sis163.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "sis163.h"
#include "SisLogger.h"
#include "SisTestManager.h"
#include "SisPowerTest.h"
#include "SisMaskTest.h"
#include "GPIBDevice.h"
#include "SisCalibrate.h"
#include <conio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;
TestManager * pTestManager;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
    if (argc < 3)
    {
        SisLogger::GetInstance()->LogMsg("Parameter error!!!\n");
        SisLogger::GetInstance()->LogMsg("Run this program with below form:\n");
        SisLogger::GetInstance()->LogMsg("    sis163 romfile macfile\n");
        system("pause");
        return 0;
    }

	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{

		// do some work for initialize
        pTestManager = new SisTestManager();
        if (pTestManager == NULL || !pTestManager->Initialize(argc, argv))
        {
            SisLogger::GetInstance()->LogMsg("Fail to initialize\n");
            return 0;
        }

        SisCalibrate * pCalibrate = new SisCalibrate(
            15, 0x16, 1, 'B');
        pCalibrate->SetWishPower(16, 18);
        pTestManager->AddTestItem(pCalibrate);
/*
        pCalibrate = new SisCalibrate(
            15, 0x16, 2, 'B');
        pCalibrate->SetWishPower(16, 18);
        pTestManager->AddTestItem(pCalibrate);
*/
        pCalibrate = new SisCalibrate(
            15, 0x16, 3, 'B');
        pCalibrate->SetWishPower(16, 18);
        pTestManager->AddTestItem(pCalibrate); //*/
/*
        pCalibrate = new SisCalibrate(
            15, 0x16, 4, 'B');
        pCalibrate->SetWishPower(16, 18);
        pTestManager->AddTestItem(pCalibrate); //*/
/*
        pCalibrate = new SisCalibrate(
            15, 0x16, 5, 'B');
        pCalibrate->SetWishPower(16, 18);
        pTestManager->AddTestItem(pCalibrate);//*/

        pCalibrate = new SisCalibrate(
            15, 0x16, 6, 'B');
        pCalibrate->SetWishPower(16, 18);
        pTestManager->AddTestItem(pCalibrate); //*/
/*
        pCalibrate = new SisCalibrate(
            15, 0x16, 7, 'B');
        pCalibrate->SetWishPower(16, 18);
        pTestManager->AddTestItem(pCalibrate);//*/
/*
        pCalibrate = new SisCalibrate(
            15, 0x16, 8, 'B');
        pCalibrate->SetWishPower(16, 18);
        pTestManager->AddTestItem(pCalibrate);//*/

        pCalibrate = new SisCalibrate(
            15, 0x16, 9, 'B');
        pCalibrate->SetWishPower(16, 18);
        pTestManager->AddTestItem(pCalibrate); //*/
/*
        pCalibrate = new SisCalibrate(
            15, 0x16, 10, 'B');
        pCalibrate->SetWishPower(16, 18);
        pTestManager->AddTestItem(pCalibrate);//*/

        pCalibrate = new SisCalibrate(
            15, 0x16, 11, 'B');
        pCalibrate->SetWishPower(16, 18);
        pTestManager->AddTestItem(pCalibrate);
/*
        pCalibrate = new SisCalibrate(
            15, 0x16, 12, 'B');
        pCalibrate->SetWishPower(16, 18);
        pTestManager->AddTestItem(pCalibrate);//*/

        pCalibrate = new SisCalibrate(
            15, 0x16, 13, 'B');
        pCalibrate->SetWishPower(16, 18);
        pTestManager->AddTestItem(pCalibrate);
/*
        pCalibrate = new SisCalibrate(
            15, 0x16, 14, 'B');
        pCalibrate->SetWishPower(16, 18);
        pTestManager->AddTestItem(pCalibrate); //*/

		SisPowerTest * pPowerTest = new SisPowerTest(
            15, 0x16, 1, 'B');
		pPowerTest->SetLimit(20.0, 16.0);
        pTestManager->AddTestItem(pPowerTest);	// 1.

		pPowerTest = new SisPowerTest(
            15, 0x6C, 1, 'G');
		pPowerTest->SetLimit(18.0, 14.0);
		pTestManager->AddTestItem(pPowerTest);	// 2.

		pPowerTest = new SisPowerTest(
            15, 0x16, 6, 'B');
		pPowerTest->SetLimit(20.0, 16.0);
		pTestManager->AddTestItem(pPowerTest);	// 3.
		pPowerTest = new SisPowerTest(
            15, 0x6C, 6, 'G');
		pPowerTest->SetLimit(18.0, 14.0);
		pTestManager->AddTestItem(pPowerTest);	// 4.

		pPowerTest = new SisPowerTest(
            15, 0x16, 11, 'B');
		pPowerTest->SetLimit(20.0, 16.0);
		pTestManager->AddTestItem(pPowerTest);	// 5.
		pPowerTest = new SisPowerTest(
            15, 0x6C, 11, 'G');
		pPowerTest->SetLimit(18.0, 14.0);
		pTestManager->AddTestItem(pPowerTest);	// 6.*/



		SisMaskTest * pMaskTest = new SisMaskTest(
            15, 0x16, 1, 'B');
		pMaskTest->SetCmpValue(10);
		pTestManager->AddTestItem(pMaskTest);	// 7.
		pMaskTest = new SisMaskTest(
            15, 0x6C, 1, 'G');
		pMaskTest->SetCmpValue(10);
		pTestManager->AddTestItem(pMaskTest);	// 8.

		pMaskTest = new SisMaskTest(
            15, 0x16, 6, 'B');
		pMaskTest->SetCmpValue(10);
		pTestManager->AddTestItem(pMaskTest);	// 9.
		pMaskTest = new SisMaskTest(
            15, 0x6C, 6, 'G');
		pMaskTest->SetCmpValue(10);
		pTestManager->AddTestItem(pMaskTest);	// 10.
/*
		pMaskTest = new SisMaskTest(
            15, 0x16, 14, 'B');
		pMaskTest->SetCmpValue(0);
		pTestManager->AddTestItem(pMaskTest);	// 11.
		pMaskTest = new SisMaskTest(
            15, 0x6C, 14, 'G');
		pMaskTest->SetCmpValue(0);
		pTestManager->AddTestItem(pMaskTest);	// 12.*/

        // main loop for testing
        char option = '1';
        while (option != 'n' && option !='N')
        {
            //SisLogger::GetInstance()->LogMsg("Test item list:\n");
            SisLogger::GetInstance()->LogMsg("开始请按任一键 ENTER.\n");
            SisLogger::GetInstance()->LogMsg("退出，请按 N 键\n");
            SisLogger::GetInstance()->LogMsg("开始选择：");
            option=_getch();

            if (option == 'N' || option =='n') // start new test
            {
				continue;
			}
            
			pTestManager->StartAll();
            
            //else if (option != '0')
            //{
            //    SisLogger::GetInstance()->LogMsg("Invalid selection!\n");
            //    SisLogger::GetInstance()->LogEndl();
            //}
        }

        // free resource
        delete pTestManager;
	}

	return nRetCode;
}
