/*******************************************************************************************************
�ļ�����SoundPrompt.h
��  �ܣ�
��������Visual C++ 6.0
��  �ߣ���  ��
        ��Ȩ����  ��������Ȩ��
��  ����1.0.0.1
��  �ڣ�2004-12-5
ʱ  �䣺14:38:16
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
