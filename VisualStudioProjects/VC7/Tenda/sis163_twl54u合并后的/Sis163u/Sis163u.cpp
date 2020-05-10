// Sis163u.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Sis163u.h"
#include "..\eepromutility.h"
#include "..\adapterfun.h"
#include <conio.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#pragma comment(lib, "..\\AdapterFun")
/////////////////////////////////////////////////////////////////////////////
// The one and only application object

CWinApp theApp;

using namespace std;

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	int nRetCode = 0;
    char c;	

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		return 0;
	}
	
	c= 0;
	while(1)
	{
		
		
		if(c!=0)
		{
             _tprintf(_T("�Ƿ�����¿���ԣ�����ǰ���һ����ENTER����Ҫ�˳��밴 N ����\n"));
		     c = _getch();
		}
		if(c =='n' || c== 'N')
		{
			return nRetCode;
		}
		else
		{
			c=1;
		}
		

		DWORD   AFun_AdapterNum;
		DWORD   AFun_OpenedAdapterIndex;
		PVOID   AFun_pAdaptersInfoBuffer;
		PVOID   AFun_pAdapter;
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
			_tprintf(_T("�����豸����\n"));
			continue;
		}
		
		
		EepromUtility ee;
		char buf0[255];
		char buf1[255];
		GetCurrentDirectory(255, buf0);
		strcat(buf0, "\\");
		strcpy(buf1, buf0);
		
		strcat(buf1, argv[1]);
		ee.SetFilePath(buf1, NULL);    // to modify
		if (!ee.LoadDataFromFile())
		{
			_tprintf(_T("װ���ļ� %s ʧ�ܡ�\n"), buf1);
			continue;
		}
		ee.SetAdapter(AFun_pAdapter);
		if(ee.WriteListData())
		{
			nRetCode = TRUE;
		}
		else
		{
			nRetCode = FALSE;
		}
		
		AFun_CloseCAdapterFun(AFun_pAdaptersInfoBuffer,
			AFun_pAdapter);
		
		if (!nRetCode)
		{
			_tprintf(_T("д��EEROMP����\n"));
			continue;
		}
		
		_tprintf(_T("����ɹ���\n"));
		_tprintf(_T("��Ͽ�������USB���ߣ�Ȼ���ٽ���,���Ϻ��밴��һ��(ENTER)\n"));
		
		
		c = _getch();
		
		GetCurrentDirectory(255, buf0);
		strcat(buf0, "\\");
		strcat(buf0, _T("sis163.bat"));
		system(buf0);
		
		
	}

	return nRetCode;
}


