#include "StdAfx.h"
#include "test.h"
#include <atltime.h>

int OnTestEcho(CCommand * pInCmd, CCommand * pOutCmd)
{
	int nRet = S_OK;
	pOutCmd->SetCommand(CMD_ANSWER_ECHO);
	pOutCmd->AddPara((DWORD)S_OK);
	try
	{
		CTime time = CTime::GetCurrentTime();
		void * para = NULL;
		TCHAR * buf = NULL;
		DWORD dwLen = 0;
		pInCmd->GetPara(&para, &dwLen);
		buf = new TCHAR[20];
		_stprintf(buf, _T("接收时间:%d:%d:%d;"), time.GetHour(), time.GetMinute(), time.GetSecond());
		_tstring szTmp;
		szTmp = buf;
		szTmp += (TCHAR * )para;
		pOutCmd->AddPara(szTmp.c_str());
		TRACE(_T("Test Echo\n"));

	}
	catch (CTException* e)
	{
		TRACE(_T("OnTestEcho exception:%s\n"), e->what());
		nRet = S_FALSE;
	}

	return nRet;
}