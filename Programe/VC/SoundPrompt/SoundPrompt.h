/*******************************************************************************************************
文件名：SoundPrompt.h
功  能：
编译器：Visual C++ 6.0
作  者：康  林
        版权所有  保留所有权利
版  本：1.0.0.1
日  期：2004-12-5
时  间：14:38:16
*******************************************************************************************************/

#if !defined(SOUNDPROMPTHOOK_H)
#define SOUNDPROMPTHOOK_H

#pragma once

extern "C" BOOL _stdcall UnInstallHook();
extern "C" BOOL _stdcall InstallHook();

void Speak(WCHAR* Text);

LRESULT CALLBACK GetMsgProc(
  int nCode,       // hook code
  WPARAM wParam,  // removal flag
  LPARAM lParam   // address of structure with message
);

#endif //#if !defined(SOUNDPROMPTHOOK_H)
