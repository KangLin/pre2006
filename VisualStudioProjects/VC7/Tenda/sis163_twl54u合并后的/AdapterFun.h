// AdapterFun.h : main header file for the ADAPTERFUN DLL
//

#if !defined(AFX_ADAPTERFUN_H__576BC038_99D9_4C90_82CD_48F4CC12CE27__INCLUDED_)
#define AFX_ADAPTERFUN_H__576BC038_99D9_4C90_82CD_48F4CC12CE27__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#ifdef _STD_CALL
#define STD_CALL _stdcall
#else
#define STD_CALL 
#endif
  
#ifdef ADAPTERFUN_IMPL
   #define CLASS_DECL   __declspec(dllexport)
#else
   #define CLASS_DECL   __declspec(dllimport)
#endif

typedef struct _AdapterStatistics
{
	LONGLONG RxOkCount;
	LONGLONG RxCRCCount;
}AdapterStatistics;

class CAdapterFun  
{
public:
	CLASS_DECL void RFCarrierSuppressionMode(BOOL Start);
	CLASS_DECL void SpectrumFlatnessMode(BOOL Start);
	CLASS_DECL void PowerDensityMode(BOOL Start);
	CLASS_DECL void CentFreqLeakageMode(BOOL Start);
	CLASS_DECL void GetStatistics(AdapterStatistics &statics);
	CLASS_DECL void ResetStatisitics();
	CLASS_DECL void ContinueRxMode(BOOL Start);
	CLASS_DECL void TestMode(BOOL Flag);
	CLASS_DECL void SingleToneMode(BOOL Start);
	CLASS_DECL void ContinueTxMode(BOOL Start);
	CLASS_DECL DWORD StartSendPacket(DWORD WantCount);
	CLASS_DECL void InitSendPacket(BYTE  *buffer,DWORD size);
	CLASS_DECL void SetPreamble(DWORD Preamble);
	CLASS_DECL DWORD GetPreamble();
	CLASS_DECL DWORD GetAntenna();
	CLASS_DECL void SetAntenna(DWORD antenna);
	CLASS_DECL void SetTxPower(DWORD TxPower);
	CLASS_DECL DWORD GetTxPower();
	CLASS_DECL void SetTxRate(WORD Rate);
	CLASS_DECL WORD GetTxRate();
	CLASS_DECL void SetChannel(int channel);
	CLASS_DECL int GetChannel();
	CLASS_DECL void GetAdapterName(int index,char *);
	CLASS_DECL void WriteEEPROM(BYTE Offset,WORD Value);
	CLASS_DECL WORD ReadEEPROM(BYTE  Offset);
	CLASS_DECL BOOL CheckAdapterHandle(int Index);
	CLASS_DECL BOOL OpenAdapter(int Index);
	CLASS_DECL void FindAdapters();
	CLASS_DECL CAdapterFun();
	CLASS_DECL virtual ~CAdapterFun();
	DWORD	AdapterNum;
	DWORD   OpenedAdapterIndex;
private:
	PVOID pAdapter;
	PVOID pAdaptersInfoBuffer;
};
// for borland C
void STD_CALL AFun_CloseCAdapterFun(PVOID AFun_pAdaptersInfoBuffer,PVOID AFun_pAdapter);
void STD_CALL AFun_FindAdapters(PVOID *AFun_pAdaptersInfoBuffer,DWORD *pAFun_AdapterNum);
BOOL STD_CALL AFun_OpenAdapter(int Index, PVOID AFun_pAdaptersInfoBuffer ,DWORD *pAFun_AdapterNum,
							DWORD  *pAFun_OpenedAdapterIndex ,PVOID *AFun_pAdapter);
BOOL STD_CALL AFun_CheckAdapterHandle(int Index, PVOID AFun_pAdaptersInfoBuffer,
				DWORD AFun_AdapterNum);
void STD_CALL AFun_GetAdapterName(int index,char *Buffer, PVOID AFun_pAdaptersInfoBuffer,
						 DWORD AFun_AdapterNum);
WORD STD_CALL AFun_ReadEEPROM(BYTE Offset, PVOID pAdapter);
void STD_CALL AFun_WriteEEPROM(BYTE Offset, WORD Value, PVOID pAdapter);
int STD_CALL AFun_GetChannel(PVOID pAdapter);
void STD_CALL AFun_SetChannel(int channel, PVOID pAdapter);
WORD STD_CALL AFun_GetTxRate(PVOID pAdapter);
void STD_CALL AFun_SetTxRate(WORD Rate, PVOID pAdapter);
DWORD STD_CALL AFun_GetTxPower(PVOID pAdapter);
void STD_CALL AFun_SetTxPower(DWORD TxPower , PVOID pAdapter);
void STD_CALL AFun_SetAntenna(DWORD antenna, PVOID pAdapter);
DWORD STD_CALL AFun_GetAntenna(PVOID pAdapter);
DWORD STD_CALL AFun_GetPreamble(PVOID pAdapter);
void STD_CALL AFun_SetPreamble(DWORD Preamble, PVOID pAdapter);
void STD_CALL AFun_InitSendPacket(BYTE *buffer, DWORD size, PVOID pAdapter);
DWORD STD_CALL AFun_StartSendPacket(DWORD WantCount, PVOID pAdapter);
void STD_CALL AFun_ContinueTxMode(BOOL Start, PVOID pAdapter);
void STD_CALL AFun_TestMode(BOOL Flag, PVOID pAdapter);
void STD_CALL AFun_SingleToneMode(BOOL Start, PVOID pAdapter);
void STD_CALL AFun_ContinueRxMode(BOOL Start, PVOID pAdapter);
void STD_CALL AFun_ResetStatisitics(PVOID pAdapter);
void STD_CALL AFun_GetStatistics(AdapterStatistics &statics, PVOID pAdapter);
void STD_CALL AFun_CentFreqLeakageMode(BOOL Start, PVOID pAdapter);
void STD_CALL AFun_PowerDensityMode(BOOL Start, PVOID pAdapter);
void STD_CALL AFun_SpectrumFlatnessMode(BOOL Start, PVOID pAdapter);
void STD_CALL AFun_RFCarrierSuppressionMode(BOOL Start, PVOID pAdapter);
//DWORD AFun_GetWlanAPCEnableFlag(PVOID pAdapter);
//void AFun_SetWlanAPCEnableFlag(DWORD Flag, PVOID pAdapter);
DWORD STD_CALL AFun_GetWlanDWORD(ULONG Oid, PVOID pAdapter);
void  STD_CALL AFun_SetWlanDWORD(ULONG Oid, DWORD Flag, PVOID pAdapter);
BOOLEAN STD_CALL AFun_SetEvaluteAPC_Mode(DWORD Flag, PVOID pAdapter);
BOOLEAN STD_CALL AFun_GetAPC_level(DWORD *pOutValue, PVOID pAdapter);
void STD_CALL AFun_Power_EVM(BOOLEAN Start, PVOID pAdapter);

void GeneratePN15(PUCHAR pOut);
void GeneratePN15PayLoad();
void stopContinuousTx(PVOID pAdapter);
void STD_CALL AFun_SpecturmMask_A(BOOLEAN Start,DWORD DW_TxRate,PVOID pAdapter);
void STD_CALL AFun_SpecturmMask_B(BOOLEAN Start,DWORD DW_TxRate,PVOID pAdapter);
/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADAPTERFUN_H__576BC038_99D9_4C90_82CD_48F4CC12CE27__INCLUDED_)
