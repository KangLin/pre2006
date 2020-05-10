// SisTestManager.h: interface for the SisTestManager class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SISTESTMANAGER_H__DAC7B65C_A2D3_4079_9396_32BF74EAEE19__INCLUDED_)
#define AFX_SISTESTMANAGER_H__DAC7B65C_A2D3_4079_9396_32BF74EAEE19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include "TestManager.h"
#include "EepromUtility.h"
#include "AdapterFun.h"

class SisTestManager : public TestManager
{
public:
	SisTestManager();
	virtual ~SisTestManager();

    bool Initialize(int argc, TCHAR* argv[]);
    bool DoPrepare();
    bool DoEndWord(bool result);
    bool StartTestItem(int nIndex);
    void CleanUp();

    PVOID   AFun_pAdapter;
protected:
    DWORD   AFun_AdapterNum;
    DWORD   AFun_OpenedAdapterIndex;
    PVOID   AFun_pAdaptersInfoBuffer;

    EepromUtility * pUtility;
};

#endif // !defined(AFX_SISTESTMANAGER_H__DAC7B65C_A2D3_4079_9396_32BF74EAEE19__INCLUDED_)
