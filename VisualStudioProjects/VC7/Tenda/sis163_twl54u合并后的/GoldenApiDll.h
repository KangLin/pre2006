
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the GOLDENAPIDLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// GOLDENAPIDLL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef GOLDENAPIDLL_EXPORTS
#define GOLDENAPIDLL_API __declspec(dllexport)
#else
#define GOLDENAPIDLL_API __declspec(dllimport)
#endif
 
#define STDCALL _stdcall


GOLDENAPIDLL_API char* STDCALL GRUAPI_GoldenAbout(void);

GOLDENAPIDLL_API int STDCALL GRUAPI_GoldenInit(void);

GOLDENAPIDLL_API int STDCALL GRUAPI_GoldenClose(void);

GOLDENAPIDLL_API int STDCALL GRUAPI_SwitchChannel(int channel);

GOLDENAPIDLL_API int STDCALL GRUAPI_StartContinuousTx(int enable);

GOLDENAPIDLL_API int STDCALL GRUAPI_StartCWTx(int enable);

GOLDENAPIDLL_API int STDCALL GRUAPI_CarrierSuppression(int enable); 

GOLDENAPIDLL_API int STDCALL GRUAPI_SelectAntenna(int AntSelection);

GOLDENAPIDLL_API int STDCALL GRUAPI_DataRate(int cmd); 

GOLDENAPIDLL_API int STDCALL GRUAPI_TxMulticastFrame(int dataRate, DWORD pattern, 
							int length, int cnt, int preamble, char Bssid[]);

GOLDENAPIDLL_API int STDCALL GRUAPI_ClearRxPcktCount(void);

GOLDENAPIDLL_API int STDCALL GRUAPI_ReadRxPcktCount(DWORD *RxCount, DWORD *ErrCount);

GOLDENAPIDLL_API int STDCALL GRUAPI_BssidFilterMode(int Mode, char Bssid[]);


