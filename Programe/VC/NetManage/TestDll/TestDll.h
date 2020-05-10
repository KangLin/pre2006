#ifndef __TESTDLL_H_KL_2007_08_29__
#define __TESTDLL_H_KL_2007_08_29__

#pragma once

extern "C" _stdcall INT DoInitalize();
extern "C" _stdcall INT DoCommand(DWORD dwCmd, CCommand * pCmd);
extern "C" _stdcall INT DoEnd();

extern "C" _stdcall INT SetContext(void * pContext);

#endif //__TESTDLL_H_KL_2007_08_29__