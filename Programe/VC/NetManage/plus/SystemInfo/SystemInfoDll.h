#ifndef __SYSTEMINFODLL_H_KL_2007_08_24__
#define __SYSTEMINFODLL_H_KL_2007_08_24__

#pragma once

extern "C" _stdcall INT DoInitalize();
extern "C" _stdcall INT DoCommand(DWORD dwCmd, CCommand * pCmd);
extern "C" _stdcall INT DoEnd();

extern "C" _stdcall INT SetContext(void * pContext);

#endif //__SYSTEMINFODLL_H_KL_2007_08_24__
